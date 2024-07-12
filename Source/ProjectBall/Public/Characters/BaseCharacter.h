// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"
#include "BaseCharacter.generated.h"

class UBaseCharacterStatsComponent;
enum class EAttackType : uint8;
class UAttributeComponent;
class ABaseWeapon;
enum class EMontageCallbackType : uint8;

DECLARE_DELEGATE(FDelegateNoParam)
DECLARE_DELEGATE_OneParam(FDelegateOneParam, const TObjectPtr<UAnimMontage>&);

UCLASS(Abstract)
class PROJECTBALL_API ABaseCharacter : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	/** AActor */
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	/** /AActor */
	
	/** /IHitInterface */
	virtual void GetHit(const FVector& ImpactPoint, const TObjectPtr<AActor> Aggressor) override;
	/** /IHitInterface */

	bool IsMoving() const;

protected:
	/** AActor */
	virtual void BeginPlay() override;
	/** /AActor */

	/** <Overridable functions> */
	virtual void WeaponAnimNotifyHandler() const;
	virtual void Die();
	virtual bool CanAttack() const;
	virtual bool IsAttacking() const;
	virtual bool CanMove() const;
	/** </Overridable functions> */

	/** <Montages> */
	void PlayMontage(const TObjectPtr<UAnimMontage>& AnimMontage, const TArray<FName>& SectionNames, EMontageCallbackType MontageType);
	void PlayMontage(const TObjectPtr<UAnimMontage>& AnimMontage, const FName& SectionName, EMontageCallbackType MontageType);
	/** </Montages> */
	
	void CalculateGroundSpeed();
	void DirectionalHitReact(const FVector& ImpactPoint);
	void HandleDamage(float DamageAmount) const;
	void SetEnabledMeshCollision(ECollisionEnabled::Type CollisionResponse) const;
	void SetEnableCapsuleCollision(ECollisionEnabled::Type CollisionResponse) const;

	bool IsAlive() const;

	/** <ABaseWeapon> */
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	TObjectPtr<ABaseWeapon> Weapon;
	/** </ABaseWeapon> */
	
	/** <AnimInstance> */
	UPROPERTY()
	TObjectPtr<UAnimInstance> CharacterAnimInstance;
	/** </AnimInstance> */
	
	float GroundSpeed;

	/** <Callback delegates> */
	FDelegateNoParam OnAttackEndCallback;
	FDelegateNoParam OnSheatheEndCallback;
	FDelegateNoParam OnUnsheatheEndCallback;
	FDelegateNoParam OnDeathEndCallback;
	FDelegateOneParam OnDeathBlendingOutCallback;
	FDelegateNoParam OnHitReactEndedCallback;
	/** </Callback delegates> */

	/** <Attributes> */
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAttributeComponent> Attributes_DEPREC; // TODO spl: remove this
	/** </Attributes> */

	/** <Montages> */
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	TObjectPtr<UAnimMontage> AttackMontage;
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	TObjectPtr<UAnimMontage> DeathMontage;
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	TObjectPtr<UAnimMontage> HitReactMontage;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	TArray<FName> AttackMontageSections;
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	TArray<FName> DeathMontageSections;
	
	int DeathSectionIndex;

	/** How long the corpse will remain on the ground after it died */
	UPROPERTY(EditDefaultsOnly, Category = "Montages | Death")
	float DeathLifeSpan;
	/** </Montages> */
	
private:
	/** <Montages> */
	void PlayRandomMontageSection(const TObjectPtr<UAnimMontage>& AnimMontage, const TArray<FName>& SectionNames);
	void PlayMontageSection(const TObjectPtr<UAnimMontage>& AnimMontage, const FName& SectionName);
	void OnMontageEnded(UAnimMontage* AnimMontage, bool bInterrupted);
	void OnBlendingOutStarted(UAnimMontage* AnimMontage, bool bInterrupted);
	
	EMontageCallbackType MontageCallbackType;
	/** </Montages> */
	
public:
	FORCEINLINE float GetGroundSpeed() const { return GroundSpeed; }
};
