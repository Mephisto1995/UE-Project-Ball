// © 2024 Pulse Core Interactive. All rights reserved.


#include "Enemies/BaseEnemy.h"

#include "AIController.h"
#include "Components/Stats/Character/Enemy/BaseEnemyCharacterStatsComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Utilities/Constants/Movement.h"
#include "Utilities/Constants/StringLiterals.h"
#include "Utilities/Constants/Enemy/AI.h"
#include "Utilities/Enums/EnemyCharacter/EEnemyState.h"
#include "Utilities/Enums/Montages/EAttackMontagePlayingStatus.h"
#include "Utilities/Enums/Montages/EMontage.h"

ABaseEnemy::ABaseEnemy() :
 TargetRadius(Constants::Enemy::AI::TARGET_RADIUS) 
, PatrolWaitMin(Constants::Enemy::AI::PATROL_WAIT_MIN)
, PatrolWaitMax(Constants::Enemy::AI::PATROL_WAIT_MAX)
, PawnSensingComponent(CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComponent"))
, AttackRadius(Constants::Enemy::AI::ATTACK_RADIUS)
, EnemyState(EEnemyState::UNKOWN)
, AttackMontagePlayingStatus(EAttackMontagePlayingStatus::UNKOWN)
, CurrentLocationWhenEnteredCombat(FVector::ZeroVector)
, MaxChasingDistance(Constants::Enemy::AI::MAX_DISTANCE_TRAVEL)
, BaseEnemyCharacterStatsComponent(CreateDefaultSubobject<UBaseEnemyCharacterStatsComponent>(TEXT("EnemyStatsComponent")))
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionObjectType(ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	PawnSensingComponent->SightRadius = 4000.f;
	PawnSensingComponent->SetPeripheralVisionAngle(45.f);
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add(Constants::StringLiterals::Tags::TAG_ENEMY_CHARACTER);

	SetEnemyState(EEnemyState::PATROLLING);
	EnemyAIController = Cast<AAIController>(GetController());
	
	if (!ActiveTarget)
	{
		ActiveTarget = GetRandomTargetAsActive();
	}

	MoveToTarget(ActiveTarget);

	PawnSensingComponent->OnSeePawn.AddDynamic(this, &ABaseEnemy::OnSeePawn);
	AttackMontagePlayingStatus = EAttackMontagePlayingStatus::NOT_PLAYING;

	OnAttackEndCallback.BindUObject(this, &ABaseEnemy::OnAttackEndMontage);
	OnHitReactEndedCallback.BindUObject(this, &ABaseEnemy::OnHitReactEndMontage);
	OnDeathEndCallback.BindUObject(this, &ABaseEnemy::OnDeathEndMontage);
	OnDeathBlendingOutCallback.BindUObject(this, &ABaseEnemy::OnDeathBlendingOutEndMontage);
}

void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsDead())
	{
		return;
	}

	if (IsInCombat())
	{
		CheckCombatTarget();

		if (HasEnemyLostAggro())
		{
			LoseInterest();
			EnterResetState();
		}
	}
	else if (IsInPassiveState())
	{
		CheckPatrolTarget();
	}
	
	if (IsInResettingState() && HasEnemyReachedInitialLocation())
	{
		ResetEnemy();
	}
}

void ABaseEnemy::WeaponAnimNotifyHandler() const
{
	// TODO spl: implement this;
}

void ABaseEnemy::Die()
{
	if (IsPreviousAttackPlaying())
	{
		StopAttackAnimation();
	}

	SetEnemyState(EEnemyState::DEAD);
	SetEnabledMeshCollision(ECollisionEnabled::NoCollision);
	SetEnableCapsuleCollision(ECollisionEnabled::NoCollision);
	DeathSectionIndex = FMath::RandRange(0, DeathMontageSections.Max() - 1);
	PlayMontage(DeathMontage, DeathMontageSections[DeathSectionIndex], EMontageCallbackType::DEATH_MONTAGE_CALLBACK);
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

void ABaseEnemy::SetEnemyState(EEnemyState NewState)
{
	switch (NewState)
	{
	case EEnemyState::PATROLLING:
		EnemyState = EEnemyState::PATROLLING;
		GroundSpeed = Constants::Movement::Enemy::WALKING_SPEED;
		GetCharacterMovement()->MaxWalkSpeed = GroundSpeed;
		break;
	case EEnemyState::CHASING:
	case EEnemyState::RESETTING:
		EnemyState = NewState;
		GroundSpeed = Constants::Movement::Enemy::RUNNING_SPEED;
		GetCharacterMovement()->MaxWalkSpeed = GroundSpeed;
		break;
	case EEnemyState::ATTACKING:
	case EEnemyState::DEAD:
	case EEnemyState::GETTING_HIT:
	case EEnemyState::UNKOWN:
	default:
		EnemyState = NewState;
		break;
	}
}

void ABaseEnemy::ClearPatrolTimer()
{
	GetWorldTimerManager().ClearTimer(PatrolTimer);
}

void ABaseEnemy::MoveToTarget(const TObjectPtr<AActor> Target) const
{
	if (!Target || !EnemyAIController || !CanMove())
	{
		return;
	}

	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalActor(Target);
	MoveRequest.SetAcceptanceRadius(50.f);

	EnemyAIController->MoveTo(MoveRequest);
}

void ABaseEnemy::MoveToLocation(const FVector& Location) const
{
	if (!EnemyAIController || !CanMove())
	{
		return;
	}

	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalLocation(Location);
	MoveRequest.SetAcceptanceRadius(50.f);

	EnemyAIController->MoveTo(MoveRequest);
}

bool ABaseEnemy::InTargetRange(const TObjectPtr<AActor>& Target, double AcceptanceRadius) const
{
	if (!Target)
	{
		return false;
	}

	const double DistanceToTarget = (Target->GetActorLocation() - GetActorLocation()).Size();
	return DistanceToTarget <= AcceptanceRadius;
}

bool ABaseEnemy::InTargetRange(const FVector& Location, double AcceptanceRadius) const
{
	const float DistanceToLocation = FVector::Distance(Location, GetActorLocation());
	return DistanceToLocation <= AcceptanceRadius;
}

bool ABaseEnemy::IsInResettingState() const
{
	return EnemyState == EEnemyState::RESETTING;
}

bool ABaseEnemy::IsInCombat() const
{
	return EnemyState == EEnemyState::CHASING ||
		EnemyState == EEnemyState::ATTACKING;
}

bool ABaseEnemy::IsPatrolling() const
{
	return EnemyState == EEnemyState::PATROLLING;
}

bool ABaseEnemy::DidEnemyChaseTooFar() const
{
	const float DistanceTravelled = FVector::Distance(CurrentLocationWhenEnteredCombat, GetActorLocation());
	return DistanceTravelled >= MaxChasingDistance;
}

bool ABaseEnemy::HasEnemyReachedInitialLocation()
{
	return InTargetRange(CurrentLocationWhenEnteredCombat, TargetRadius);
}

bool ABaseEnemy::IsInPassiveState() const
{
	return EnemyState == EEnemyState::IDLE ||
		EnemyState == EEnemyState::PATROLLING;
}

void ABaseEnemy::CheckPatrolTarget()
{
	if (InTargetRange(ActiveTarget, TargetRadius))
	{
		EnterPatrollingState();
	}
}

void ABaseEnemy::Attack()
{
	SetEnemyState(EEnemyState::ATTACKING);
	AttackMontagePlayingStatus = EAttackMontagePlayingStatus::PLAYING;
	PlayMontage(AttackMontage, AttackMontageSections, EMontageCallbackType::ATTACK_MONTAGE_CALLBACK);
}

void ABaseEnemy::CheckCombatTarget()
{
	if (IsOutsideAttackRadius())
	{
		ChaseTarget();
	}
	else if (CanAttack())
	{
		Attack();
	}
}

void ABaseEnemy::EnterResettingStatus()
{
	if (InTargetRange(this, TargetRadius))
	{
		ResetEnemy();
	}
}

void ABaseEnemy::OnPatrolTimerFinished() const
{
	MoveToTarget(ActiveTarget);
}

TObjectPtr<AActor> ABaseEnemy::ChoosePatrolTarget()
{
	TArray<TObjectPtr<AActor>> ValidTargets;
	for (const auto& Target : PatrolTargets)
	{
		if (Target != ActiveTarget)
		{
			ValidTargets.AddUnique(Target);
		}
	}

	if (ValidTargets.IsEmpty())
	{
		return nullptr;
	}

	return ValidTargets[FMath::RandRange(0, ValidTargets.Num() - 1)];
}

void ABaseEnemy::ChaseTarget()
{
	SetEnemyState(EEnemyState::CHASING);
	MoveToTarget(CombatTarget);
}

void ABaseEnemy::LoseInterest()
{
	CombatTarget = nullptr;
}

void ABaseEnemy::StartPatrolling()
{
	SetEnemyState(EEnemyState::PATROLLING);
	MoveToTarget(ActiveTarget);
}

bool ABaseEnemy::IsChasing() const
{
	return EnemyState == EEnemyState::CHASING;
}

bool ABaseEnemy::IsDead() const
{
	return EnemyState == EEnemyState::DEAD;
}

bool ABaseEnemy::HasEnemyLostAggro() const
{
	return DidEnemyChaseTooFar();
}

bool ABaseEnemy::IsInsideAttackRadius() const
{
	return InTargetRange(CombatTarget, AttackRadius);
}

bool ABaseEnemy::IsOutsideAttackRadius() const
{
	return !IsInsideAttackRadius();
}

bool ABaseEnemy::IsPreviousAttackPlaying() const
{
	return AttackMontagePlayingStatus == EAttackMontagePlayingStatus::PLAYING;
}

bool ABaseEnemy::IsGettingHitAnimationFinished() const
{
	return EnemyState != EEnemyState::GETTING_HIT;
}

void ABaseEnemy::StopAttackAnimation() const
{
	if (!CharacterAnimInstance)
	{
		return;
	}

	if (CharacterAnimInstance->Montage_IsPlaying(AttackMontage))
	{
		CharacterAnimInstance->Montage_GetEndedDelegate()->Unbind();
		CharacterAnimInstance->Montage_Stop(0, AttackMontage);
	}
}

void ABaseEnemy::CacheCurrentLocationWhenEnteringCombat()
{
	CurrentLocationWhenEnteredCombat = GetActorLocation();
}

void ABaseEnemy::EnterResetState()
{
	SetEnemyState(EEnemyState::RESETTING);
	MoveToLocation(CurrentLocationWhenEnteredCombat);

	SetEnableCapsuleCollision(ECollisionEnabled::QueryOnly);
	SetEnabledMeshCollision(ECollisionEnabled::NoCollision);
}

void ABaseEnemy::EnterPatrollingState()
{
	SetEnemyState(EEnemyState::PATROLLING);
	ActiveTarget = ChoosePatrolTarget();
	const uint32 PatrolWaitTime = FMath::RandRange(PatrolWaitMin, PatrolWaitMax);
	GetWorldTimerManager().SetTimer(
		PatrolTimer,
		this,
		&ABaseEnemy::OnPatrolTimerFinished,
		PatrolWaitTime
	);
}

void ABaseEnemy::ResetEnemy()
{
	SetEnableCapsuleCollision(ECollisionEnabled::QueryOnly);
	SetEnabledMeshCollision(ECollisionEnabled::QueryOnly);
	EnterPatrollingState();
}

void ABaseEnemy::OnSeePawn(APawn* Pawn)
{
	const bool bShouldChaseTarget = Pawn &&
		Pawn->ActorHasTag(Constants::StringLiterals::Tags::TAG_PLAYER_CHARACTER) &&
		!IsChasing() &&
		!IsAttacking() &&
		!IsDead();

	if (bShouldChaseTarget)
	{
		CombatTarget = Pawn;
		ChaseTarget();
	}
}

TObjectPtr<AActor> ABaseEnemy::GetRandomTargetAsActive()
{
	if (PatrolTargets.IsEmpty())
	{
		return nullptr;
	}
	
	return PatrolTargets[FMath::RandRange(0, PatrolTargets.Max() - 1)];
}

float ABaseEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                             AActor* DamageCauser)
{
	HandleDamage(DamageAmount);
	return DamageAmount;
}

void ABaseEnemy::GetHit(const FVector& ImpactPoint, const TObjectPtr<AActor> Aggressor)
{
	Super::GetHit(ImpactPoint, Aggressor);

	ClearPatrolTimer();
	CombatTarget = Aggressor;
	ChaseTarget();
	
	SetEnemyState(EEnemyState::GETTING_HIT);
	AttackMontagePlayingStatus = EAttackMontagePlayingStatus::NOT_PLAYING;
	CacheCurrentLocationWhenEnteringCombat();
}

bool ABaseEnemy::CanAttack() const
{
	return IsInsideAttackRadius()
		&& IsGettingHitAnimationFinished()
		&& !IsPreviousAttackPlaying()
		&& !IsDead();
}

bool ABaseEnemy::IsAttacking() const
{
	return EnemyState == EEnemyState::ATTACKING;
}

bool ABaseEnemy::CanMove() const
{
	return !IsAttacking() && !IsPreviousAttackPlaying();
}

void ABaseEnemy::OnAttackEndMontage()
{
	AttackMontagePlayingStatus = EAttackMontagePlayingStatus::NOT_PLAYING;
	CheckCombatTarget();
}

void ABaseEnemy::OnHitReactEndMontage()
{
	ChaseTarget();
	CheckCombatTarget();
}

void ABaseEnemy::OnDeathEndMontage()
{
	SetLifeSpan(DeathLifeSpan);
}

void ABaseEnemy::OnDeathBlendingOutEndMontage(const TObjectPtr<UAnimMontage>& AnimMontage)
{
	if (!CharacterAnimInstance)
	{
		return;
	}
	
	const FName& DeathMontageSectionName = DeathMontage->GetSectionName(DeathSectionIndex);
	float SectionStart;
	float SectionEnd;
	DeathMontage->GetSectionStartAndEndTime(DeathSectionIndex, SectionStart, SectionEnd);

	CharacterAnimInstance->Montage_Play(DeathMontage);
	CharacterAnimInstance->Montage_JumpToSection(DeathMontageSectionName, DeathMontage);
	CharacterAnimInstance->Montage_SetPosition(
		DeathMontage,
		SectionStart + DeathMontage->GetSectionLength(DeathSectionIndex) - 0.0001f
	);
	
	CharacterAnimInstance->Montage_SetPlayRate(DeathMontage, 0.0f);
}
