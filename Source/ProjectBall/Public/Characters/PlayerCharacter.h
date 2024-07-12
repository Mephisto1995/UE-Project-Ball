// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Interfaces/Montages/IPlayerMontageCallbacks.h"
#include "PlayerCharacter.generated.h"

class UInventoryComponent;
class UPlayerCharacterStatsComponent;
enum class EPlayerCombatState : uint8;
enum class EActionState : uint8;
enum class EPlayerAnimationPose : uint8;
enum class EWeaponSheathingState : uint8;
class ABaseWeapon;
class AItem;
class UCameraComponent;
class USpringArmComponent;
class UInputAction;
struct FInputActionValue;
class UInputMappingContext;

UCLASS()
class PROJECTBALL_API APlayerCharacter : public ABaseCharacter, public IPlayerMontageCallbacks
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	
	/** <AActor> */
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override; // Can be removed
	/** </AActor> */

	/** <IHitInterface> */
	virtual void GetHit(const FVector& ImpactPoint, const TObjectPtr<AActor> Aggressor) override;
	/** </IHitInterface> */
	
	void ExecuteAction(EActionState NewAction);
	virtual bool CanMove() const override;

protected:
	/** <AActor> */
	virtual void BeginPlay() override;
	/** <AActor> */

	/** <Montages> */
	void PlaySheatheUnsheatheMontage();
	/** </Montages> */

	/** <IPlayerMontageCallbacks> */
	virtual void OnAttackEndMontage() override;
	virtual void OnHitReactEndMontage() override;
	virtual void OnDeathEndMontage() override;
	virtual void OnDeathBlendingOutEndMontage(const TObjectPtr<UAnimMontage>& AnimMontage) override;
	virtual void OnSheatheEndMontage() override;
	virtual void OnUnsheatheEndMontage() override;
	/** </IPlayerMontageCallbacks> */

private:
	void HandleShootingAndRunningAttackMontageIfPlayerStoppedOrStoppedAiming() const;
	
	// This can be made virtual and protected, if we decide that PlayerCharacter class can have children.
	void OnActionReceived(EActionState NewAction);
	void OnPickUpWeaponAction();
	void OnShootingAction();
	void OnAttackingAction();
	void OnMeleeAttackingAction();
	void OnShootingAndRunningAction();
	void OnJumpingAnimation();
	void OnAimingAction();
	void OnIdleRangedWeaponAction();
	void OnIdleMeleeWeaponAction();
	void OnIdleUnarmedAction();
	void OnAimingAndRunningAction();
	void OnSheathingUnsheathingAction();

	bool IsHoldingInHandAWeapon() const;
	bool IsHoldingInHandRangeWeapon() const;
	bool IsHoldingInHandMeleeWeapon() const;
	bool IsEquippedWithRangeWeapon() const;
	bool IsEquippedWithMeleeWeapon() const;
	bool IsAiming() const;
	bool IsAimingAndRunning() const;
	bool IsAimingOrAimingAndRunning() const;
	bool CanWeaponShoot() const;
	bool CanShoot() const;
	bool IsShooting() const;
	bool IsShootingAndRunning() const;
	bool IsShootingOrShootingAndRunning() const;
	bool CanMeleeAttack() const;
	bool IsMeleeAttacking() const;
	bool IsSheathing() const;
	bool IsUnsheathing() const;

	void SetPlayerCombatState(EPlayerCombatState NewState);
	void SetPlayerAnimationPose(EPlayerAnimationPose NewState);
	void RetrieveWeapon();
	void ResetAction();
	
	/** <Camera> */
	UPROPERTY(EditDefaultsOnly, Category = Camera)
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(EditDefaultsOnly, Category = Camera)
	TObjectPtr<UCameraComponent> CameraComponent;
	/** </Camera> */

	/** <AItem> */
	UPROPERTY(VisibleInstanceOnly)
	TObjectPtr<AItem> OverlappingItem;
	/** </AItem> */

	/** <States> */
	EPlayerCombatState PlayerCombatState;
	EPlayerAnimationPose PlayerAnimationPose;
	EActionState ActionState;
	/** </States> */

	/** <Montages> */
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	TObjectPtr<UAnimMontage> RangeAttackMontage;
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	TObjectPtr<UAnimMontage> RangeSheatheUnsheatheMontage;
	/** </Montages> */

	/** <UPlayerCharacterStatsComponent> */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UPlayerCharacterStatsComponent> PlayerCharacterStatsComponent;
	/** </UPlayerCharacterStatsComponent> */
	
public:
	FORCEINLINE EPlayerAnimationPose GetPlayerAnimationPose() const { return PlayerAnimationPose; }
	FORCEINLINE void SetOverlappingItem(const TObjectPtr<AItem> Item) { OverlappingItem = Item; }
	FORCEINLINE TObjectPtr<UPlayerCharacterStatsComponent> GetPlayerCharacterStats() const { return PlayerCharacterStatsComponent; }
};
