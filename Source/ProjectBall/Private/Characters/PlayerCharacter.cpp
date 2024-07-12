// © 2024 Pulse Core Interactive. All rights reserved.

#include "Characters/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/Stats/Character/Player/PlayerCharacterStatsComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Items/Item.h"
#include "Items/Weapons/BaseWeapon.h"
#include "Items/Weapons/MeleeWeapons/MeleeWeapons/MeleeWeapon.h"
#include "Items/Weapons/RangeWeapons/RangeWeapons/RifleWeapon.h"
#include "Utilities/Constants/StringLiterals.h"
#include "Utilities/Enums/Items/Weapons/EWeaponSheathingState.h"
#include "Utilities/Enums/Items/Weapons/EWeaponState.h"
#include "Utilities/Enums/Items/Weapons/EWeaponType.h"
#include "Utilities/Enums/Montages/EMontage.h"
#include "Utilities/Enums/PlayerCharacter/EPlayerCombatState.h"
#include "Utilities/Enums/PlayerCharacter/EActionState.h"
#include "Utilities/Enums/PlayerCharacter/EPlayerAnimationPose.h"
#include "Utilities/HelperFunctions/HelperFunctions.h"

APlayerCharacter::APlayerCharacter() :
CameraBoom(CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom")))
, CameraComponent(CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent")))
, PlayerCharacterStatsComponent(CreateDefaultSubobject<UPlayerCharacterStatsComponent>(TEXT("PlayerCharacterStatsComponent")))
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.f;
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetPlayerAnimationPose(EPlayerAnimationPose::NOT_HOLDING);
	Tags.Add(Constants::StringLiterals::Tags::TAG_PLAYER_CHARACTER);

	OnAttackEndCallback.BindUObject(this, &APlayerCharacter::OnAttackEndMontage);
	OnSheatheEndCallback.BindUObject(this, &APlayerCharacter::OnSheatheEndMontage);
	OnUnsheatheEndCallback.BindUObject(this, &APlayerCharacter::OnUnsheatheEndMontage);
	OnDeathEndCallback.BindUObject(this, &APlayerCharacter::OnDeathEndMontage);
	OnDeathBlendingOutCallback.BindUObject(this, &APlayerCharacter::OnDeathBlendingOutEndMontage);
	OnHitReactEndedCallback.BindUObject(this, &APlayerCharacter::OnHitReactEndMontage);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacter::GetHit(const FVector& ImpactPoint, const TObjectPtr<AActor> Aggressor)
{
	// TODO spl: implement this
	Super::GetHit(ImpactPoint, Aggressor);
	UE_LOG(LogTemp, Warning, TEXT("APlayerCharacter::GetHit"));
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	HandleShootingAndRunningAttackMontageIfPlayerStoppedOrStoppedAiming();

	HelperFunctions::DebugDisplayOverlappingOrNotWithItem(OverlappingItem);
}

void APlayerCharacter::HandleShootingAndRunningAttackMontageIfPlayerStoppedOrStoppedAiming() const
{
	if (!CharacterAnimInstance)
	{
		return;
	}
	
	if (CharacterAnimInstance->Montage_IsPlaying(RangeAttackMontage))
	{
		const bool bIsAttackRunningMontage = CharacterAnimInstance->Montage_GetCurrentSection() == Constants::StringLiterals::Attacking::ATTACK_RUNNING;
		const bool bDidPlayerStopRunning = bIsAttackRunningMontage && GroundSpeed == 0.f;
		const bool bDidPlayerStopAiming = bIsAttackRunningMontage && !IsAimingOrAimingAndRunning();
		
		const bool bStopAnimationConditions = bDidPlayerStopRunning || bDidPlayerStopAiming;
			
		if (bStopAnimationConditions)
		{
			CharacterAnimInstance->Montage_Stop(0.01);
		}
	}
}

void APlayerCharacter::OnActionReceived(EActionState NewAction)
{
	UE_LOG(LogTemp, Warning, TEXT("Action state: %d"), static_cast<int32>(NewAction));
	
	switch (NewAction)
	{
	case EActionState::ACTION_IDLE_UNARMED:
		OnIdleUnarmedAction();
		break;
	case EActionState::ACTION_IDLE_RANGED_WEAPON:
		OnIdleRangedWeaponAction();
		break;
	case EActionState::ACTION_IDLE_MELEE_WEAPON:
		OnIdleMeleeWeaponAction();
		break;
	case EActionState::ACTION_AIMING:
		OnAimingAction();
		break;
	case EActionState::ACTION_AIMING_AND_RUNNING:
		OnAimingAndRunningAction();
		break;
	case EActionState::ACTION_SHOOTING:
		OnShootingAction();
		break;
	case EActionState::ACTION_ATTACKING:
		OnAttackingAction();
		break;
	case EActionState::ACTION_MELEE_ATTACKING:
		OnMeleeAttackingAction();
		break;
	case EActionState::ACTION_SHOOTING_AND_RUNNING:
		OnShootingAndRunningAction();
		break;
	case EActionState::ACTION_JUMPING:
		OnJumpingAnimation();
		break;
	case EActionState::ACTION_PICKING_UP_WEAPON:
		OnPickUpWeaponAction();
		break;
	case EActionState::ACTION_SHEATHING_UNSHEATHING:
		OnSheathingUnsheathingAction();
		break;
	default:
		break;
	}

	ResetAction();
}

void APlayerCharacter::OnPickUpWeaponAction()
{
	if (IsHoldingInHandAWeapon())
	{
		return;
	}
	
	RetrieveWeapon();
	
	if (!Weapon)
	{
		ExecuteAction(EActionState::ACTION_IDLE_UNARMED);
		return;
	}

	/**
	 * TODO spl: this sounds wrong, Weapon->PickupItem.
	 * A player picks up an item, maybe some renaming or relogic is needed?
	 */
	Weapon->PickupItem(GetMesh(), this, this);

	if (IsEquippedWithRangeWeapon())
	{
		ExecuteAction(EActionState::ACTION_IDLE_RANGED_WEAPON);
	}
	else if (IsEquippedWithMeleeWeapon())
	{
		ExecuteAction(EActionState::ACTION_IDLE_MELEE_WEAPON);
	}
}

void APlayerCharacter::OnShootingAction()
{
	if (CanShoot())
	{
		SetPlayerCombatState(EPlayerCombatState::SHOOTING);
		PlayMontage(RangeAttackMontage, Constants::StringLiterals::Attacking::ATTACK_STANDING_STILL, EMontageCallbackType::ATTACK_MONTAGE_CALLBACK);
		Weapon->UseWeapon();
	}
}

void APlayerCharacter::OnAttackingAction()
{
	if (IsHoldingInHandRangeWeapon())
	{
		if (IsAimingAndRunning())
		{
			ExecuteAction(EActionState::ACTION_SHOOTING_AND_RUNNING);
		}
		else if (IsAiming())
		{
			ExecuteAction(EActionState::ACTION_SHOOTING);
		}
	}
	else if (IsHoldingInHandMeleeWeapon())
	{
		ExecuteAction(EActionState::ACTION_MELEE_ATTACKING);
	}
}

void APlayerCharacter::OnMeleeAttackingAction()
{
	if (CanMeleeAttack())
	{
		SetPlayerCombatState(EPlayerCombatState::MELEE_ATTACKING);
		PlayMontage(AttackMontage, AttackMontageSections, EMontageCallbackType::ATTACK_MONTAGE_CALLBACK);
	}
}

void APlayerCharacter::OnShootingAndRunningAction()
{
	if (CanShoot())
	{
		SetPlayerCombatState(EPlayerCombatState::SHOOTING_AND_RUNNING);
		PlayMontage(RangeAttackMontage, Constants::StringLiterals::Attacking::ATTACK_RUNNING, EMontageCallbackType::ATTACK_MONTAGE_CALLBACK);
		Weapon->UseWeapon();
	}
}

void APlayerCharacter::PlaySheatheUnsheatheMontage()
{
	if (!CharacterAnimInstance || !Weapon)
	{
		return;
	}
	
	CharacterAnimInstance->Montage_Play(RangeSheatheUnsheatheMontage);

	if (Weapon->GetWeaponSheathingState() == EWeaponSheathingState::EWSS_SHEATHED)
	{
		Weapon->SetWeaponSheathingState(EWeaponSheathingState::EWSS_UNSHEATHED);
		PlayMontage(RangeSheatheUnsheatheMontage,
			Constants::StringLiterals::SectionNames::UNSHEATHE,
			EMontageCallbackType::UNSHEATHE_MONTAGE_CALLBACK);
	}
	else if (Weapon->GetWeaponSheathingState() == EWeaponSheathingState::EWSS_UNSHEATHED)
	{
		Weapon->SetWeaponSheathingState(EWeaponSheathingState::EWSS_SHEATHED);
		PlayMontage(RangeSheatheUnsheatheMontage,
			Constants::StringLiterals::SectionNames::SHEATHE,
			EMontageCallbackType::SHEATHE_MONTAGE_CALLBACK);
	}
}

void APlayerCharacter::OnAttackEndMontage()
{
	if (IsHoldingInHandRangeWeapon())
	{
		ExecuteAction(EActionState::ACTION_IDLE_RANGED_WEAPON);
	}
	else if (IsHoldingInHandMeleeWeapon())
	{
		ExecuteAction(EActionState::ACTION_IDLE_MELEE_WEAPON);
	}
}

void APlayerCharacter::OnHitReactEndMontage()
{
	// TODO spl: implement this
}

void APlayerCharacter::OnDeathEndMontage()
{
	// TODO spl: implement this
}

void APlayerCharacter::OnDeathBlendingOutEndMontage(const TObjectPtr<UAnimMontage>& AnimMontage)
{
	// TODO spl: implement this
}

void APlayerCharacter::OnSheatheEndMontage()
{
	ExecuteAction(EActionState::ACTION_IDLE_UNARMED);
}

void APlayerCharacter::OnUnsheatheEndMontage()
{
	if (IsEquippedWithRangeWeapon())
	{
		ExecuteAction(EActionState::ACTION_IDLE_RANGED_WEAPON);
	}
	else if (IsEquippedWithMeleeWeapon())
	{
		ExecuteAction(EActionState::ACTION_IDLE_MELEE_WEAPON);
	}
}

void APlayerCharacter::OnJumpingAnimation()
{
	Jump();
}

void APlayerCharacter::OnIdleRangedWeaponAction()
{
	if (IsEquippedWithRangeWeapon())
	{
		SetPlayerCombatState(EPlayerCombatState::UNENGAGED);
		SetPlayerAnimationPose(EPlayerAnimationPose::HOLDING_RANGED_WEAPON);
	}
}

void APlayerCharacter::OnIdleMeleeWeaponAction()
{
	if (IsEquippedWithMeleeWeapon())
	{
		SetPlayerCombatState(EPlayerCombatState::UNENGAGED);
		SetPlayerAnimationPose(EPlayerAnimationPose::HOLDING_MELEE_WEAPON);
	}
}

void APlayerCharacter::OnIdleUnarmedAction()
{
	SetPlayerCombatState(EPlayerCombatState::UNENGAGED);
	SetPlayerAnimationPose(EPlayerAnimationPose::NOT_HOLDING);
}

void APlayerCharacter::OnAimingAction()
{
	if (IsHoldingInHandRangeWeapon())
	{
		SetPlayerCombatState(EPlayerCombatState::AIMING);
		SetPlayerAnimationPose(EPlayerAnimationPose::AIMING_RANGED_WEAPON);
	}
}

void APlayerCharacter::OnAimingAndRunningAction()
{
	if (IsHoldingInHandRangeWeapon())
	{
		SetPlayerCombatState(EPlayerCombatState::AIMING_AND_RUNNING);
		SetPlayerAnimationPose(EPlayerAnimationPose::AIMING_AND_RUNNING_WITH_RANGED_WEAPON);
	}
}

void APlayerCharacter::OnSheathingUnsheathingAction()
{
	PlaySheatheUnsheatheMontage();
}

void APlayerCharacter::ExecuteAction(EActionState NewAction)
{
	ActionState = NewAction;
	OnActionReceived(ActionState);
}

void APlayerCharacter::ResetAction()
{
	ActionState = EActionState::ACTION_UNOCCUPIED;
}

bool APlayerCharacter::IsHoldingInHandAWeapon() const
{
	return IsHoldingInHandMeleeWeapon() || IsHoldingInHandRangeWeapon();
}

bool APlayerCharacter::IsHoldingInHandRangeWeapon() const
{
	// We can't just check for Holding_Ranged_Weapon because Aiming actions also count as holding a range weapon
	return PlayerAnimationPose != EPlayerAnimationPose::NOT_HOLDING &&
		PlayerAnimationPose != EPlayerAnimationPose::HOLDING_MELEE_WEAPON;
}

bool APlayerCharacter::IsHoldingInHandMeleeWeapon() const
{
	return PlayerAnimationPose == EPlayerAnimationPose::HOLDING_MELEE_WEAPON;
}

bool APlayerCharacter::IsEquippedWithRangeWeapon() const
{
	if (!Weapon)
	{
		return false;
	}

	return Weapon->GetWeaponType() == EWeaponType::EWT_RANGED && 
	 Weapon->GetWeaponState() == EWeaponState::EWS_IN_PLAYERS_POSSESSION;
}

bool APlayerCharacter::IsEquippedWithMeleeWeapon() const
{
	if (!Weapon)
	{
		return false;
	}
	
	return Weapon->GetWeaponType() == EWeaponType::EWT_MELEE && 
	 Weapon->GetWeaponState() == EWeaponState::EWS_IN_PLAYERS_POSSESSION;
}

bool APlayerCharacter::IsAiming() const
{
	return PlayerCombatState == EPlayerCombatState::AIMING;
}

bool APlayerCharacter::IsAimingAndRunning() const
{
	return PlayerCombatState == EPlayerCombatState::AIMING_AND_RUNNING;
}

bool APlayerCharacter::IsAimingOrAimingAndRunning() const
{
	return IsAiming() || IsAimingAndRunning();
}

bool APlayerCharacter::CanWeaponShoot() const
{
	return Weapon->CanUseWeapon();
}

bool APlayerCharacter::CanShoot() const
{
	return IsEquippedWithRangeWeapon() &&
		IsAimingOrAimingAndRunning() &&
		!IsShooting() &&
		CanWeaponShoot();
}

bool APlayerCharacter::IsShooting() const
{
	return PlayerCombatState == EPlayerCombatState::SHOOTING;
}

bool APlayerCharacter::IsShootingAndRunning() const
{
	return PlayerCombatState == EPlayerCombatState::SHOOTING_AND_RUNNING;
}

bool APlayerCharacter::IsShootingOrShootingAndRunning() const
{
	return IsShooting() || IsShootingAndRunning();
}

bool APlayerCharacter::CanMeleeAttack() const
{
	return IsHoldingInHandMeleeWeapon() && !IsMeleeAttacking();
}

bool APlayerCharacter::IsMeleeAttacking() const
{
	return PlayerCombatState == EPlayerCombatState::MELEE_ATTACKING;
}

bool APlayerCharacter::IsSheathing() const
{
	return PlayerCombatState == EPlayerCombatState::SHEATHING;
}

bool APlayerCharacter::IsUnsheathing() const
{
	return PlayerCombatState == EPlayerCombatState::UNSHEATHING;
}

bool APlayerCharacter::CanMove() const
{
	return !IsSheathing() && !IsUnsheathing() && !IsMeleeAttacking();
}

void APlayerCharacter::SetPlayerCombatState(EPlayerCombatState NewState)
{
	PlayerCombatState = NewState;
}

void APlayerCharacter::SetPlayerAnimationPose(EPlayerAnimationPose NewState)
{
	PlayerAnimationPose = NewState;
}

void APlayerCharacter::RetrieveWeapon()
{
	// Casting directly to concrete classes
	if (const TObjectPtr<ABaseWeapon> OverlappingWeapon = Cast<ARifleWeapon>(OverlappingItem))
	{
		Weapon = OverlappingWeapon;
		SetPlayerAnimationPose(EPlayerAnimationPose::HOLDING_RANGED_WEAPON);
		Weapon->SetWeaponSheathingState(EWeaponSheathingState::EWSS_UNSHEATHED);
		OverlappingItem = nullptr;
		return;
	}

	if (const TObjectPtr<ABaseWeapon> OverlappingWeapon = Cast<AMeleeWeapon>(OverlappingItem))
	{
		Weapon = OverlappingWeapon;
		Weapon->SetWeaponSheathingState(EWeaponSheathingState::EWSS_UNSHEATHED);
		SetPlayerAnimationPose(EPlayerAnimationPose::HOLDING_MELEE_WEAPON);
		OverlappingItem = nullptr;
		return; // Redundant, but keeping it for consistency's sake.
	}
}
