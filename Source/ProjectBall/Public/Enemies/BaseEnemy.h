// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Interfaces/Montages/IEnemyMontageCallbacks.h"
#include "BaseEnemy.generated.h"

class UCoreAttributes;
class UBaseEnemyCharacterStatsComponent;
enum class EAttackMontagePlayingStatus : uint8;
class UPawnSensingComponent;
class AAIController;
enum class EEnemyState : uint8;
/**
 * 
 */
UCLASS()
class PROJECTBALL_API ABaseEnemy : public ABaseCharacter, public IEnemyMontageCallbacks
{
	GENERATED_BODY()

public:
	ABaseEnemy();
	
	/** <AActor> */
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	/** </AActor> */
	
	/** <IHitInterface> */
	virtual void GetHit(const FVector& ImpactPoint, const TObjectPtr<AActor> Aggressor) override;
	/** </IHitInterface> */
	
protected:
	/** <AActor> */
	virtual void BeginPlay() override;
	/** </AActor> */

	/** <ABaseCharacter> */
	virtual void WeaponAnimNotifyHandler() const override;
	virtual void Die() override;
	virtual bool CanAttack() const override;
	virtual bool IsAttacking() const override;
	virtual bool CanMove() const override;
	/** </ABaseCharacter> */

	/** <IEnemyMontageCallbacks> */
	virtual void OnAttackEndMontage() override;
	virtual void OnHitReactEndMontage() override;
	virtual void OnDeathEndMontage() override;
	virtual void OnDeathBlendingOutEndMontage(const TObjectPtr<UAnimMontage>& AnimMontage) override;
	/** </IEnemyMontageCallbacks> */

	/** <AI Behaviour> */
	// TODO spl: encapsulate these in their own AIManager or something class.
	void SetEnemyState(EEnemyState NewState);
	void ClearPatrolTimer();
	void MoveToTarget(const TObjectPtr<AActor> Target) const;
	void MoveToLocation(const FVector& Location) const;
	void Attack();
	void CheckPatrolTarget();
	void CheckCombatTarget(); // TODO spl: rename this
	void EnterResettingStatus();
	void OnPatrolTimerFinished() const;
	TObjectPtr<AActor> ChoosePatrolTarget();
	void ChaseTarget();
	void LoseInterest();
	void StartPatrolling();
	void StopAttackAnimation() const;
	void CacheCurrentLocationWhenEnteringCombat();
	void EnterResetState();
	void EnterPatrollingState();
	void ResetEnemy();

	bool IsChasing() const;
	bool IsDead() const;
	bool HasEnemyLostAggro() const;
	bool IsInsideAttackRadius() const;
	bool IsOutsideAttackRadius() const;
	bool IsPreviousAttackPlaying() const;
	bool IsGettingHitAnimationFinished() const;
	bool InTargetRange(const TObjectPtr<AActor>& Target, double AcceptanceRadius) const;
	bool InTargetRange(const FVector& Location, double AcceptanceRadius) const;
	bool IsInResettingState() const; // Should've been IsEvading
	bool IsInCombat() const;
	bool IsPatrolling() const;
	bool DidEnemyChaseTooFar() const;
	bool HasEnemyReachedInitialLocation();
	bool IsInPassiveState() const;
	/** </AI Behaviour> */
	
	/** Callback for OnSeePawn in UPawnSensingComponent */
	UFUNCTION()
	void OnSeePawn(APawn* Pawn);

	/** <AI Navigation> */
	UPROPERTY(EditInstanceOnly, Category = "AI | Navigation");
	TObjectPtr<AActor> ActiveTarget;

	UPROPERTY(EditInstanceOnly, Category = "AI | Navigation");
	TArray<TObjectPtr<AActor>> PatrolTargets;

	UPROPERTY(EditAnywhere, Category = "AI | Navigation | Patrolling")
	double TargetRadius;

	FTimerHandle PatrolTimer;

	UPROPERTY(EditAnywhere, Category = "AI | Navigation | Patrolling")
	float PatrolWaitMin;

	UPROPERTY(EditAnywhere, Category = "AI | Navigation | Patrolling")
	float PatrolWaitMax;
	/** </AI Navigation> */

	/** <Combat >*/
	UPROPERTY(BlueprintReadOnly, Category = Combat)
	TObjectPtr<AActor> CombatTarget;

	UPROPERTY(EditAnywhere, Category = "AI | Behavior | Combat")
	TObjectPtr<UPawnSensingComponent> PawnSensingComponent;

	UPROPERTY(EditAnywhere)
	double AttackRadius;
	/** </Combat >*/

	/** <Enums> */
	EEnemyState EnemyState;
	EAttackMontagePlayingStatus AttackMontagePlayingStatus;
	/** </Enums> */

	/** <AI Behaviour> */
	UPROPERTY()
	TObjectPtr<AAIController> EnemyAIController;

	FVector CurrentLocationWhenEnteredCombat;

	UPROPERTY(EditDefaultsOnly, Category = "AI | Behaviour")
	float MaxChasingDistance;
	/** </AI Behaviour> */

	/** <UBaseEnemyCharacterStatsComponent> */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UBaseEnemyCharacterStatsComponent> BaseEnemyCharacterStatsComponent;
	/** </UBaseEnemyCharacterStatsComponent> */
	
private:
	TObjectPtr<AActor> GetRandomTargetAsActive();
	
public:
	FORCEINLINE EEnemyState GetEnemyState() const { return EnemyState; }
};
