// © 2024 Pulse Core Interactive. All rights reserved.


#include "Characters/BaseCharacter.h"

#include "Components/AttributeComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/Stats/Character/BaseCharacterStatsComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Items/Weapons/BaseWeapon.h"
#include "Items/Weapons/MeleeWeapons/BaseMeleeWeapon.h"
#include "Kismet/KismetMathLibrary.h"
#include "Utilities/Constants/Montages.h"
#include "Utilities/Enums/Montages/EAnimNotify.h"
#include "Utilities/Enums/Montages/EMontage.h"
#include "Utilities/HelperFunctions/HelperFunctions.h"

ABaseCharacter::ABaseCharacter() :
GroundSpeed(0.f)
, Attributes_DEPREC(CreateDefaultSubobject<UAttributeComponent>(TEXT("Attributes_DEPRECATED")))
, DeathSectionIndex(-1)
, DeathLifeSpan(Constants::Montages::Death::DEATH_LIFE_SPAN)
, MontageCallbackType(EMontageCallbackType::UNKOWN)
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionObjectType(ECC_Pawn);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	GetMesh()->SetCollisionResponseToAllChannels(ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	// Critical for generating directional reacts from attacks.
	// Critical for root motion and directional hit react!!!
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	CharacterAnimInstance = GetMesh()->GetAnimInstance();
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CalculateGroundSpeed();
	WeaponAnimNotifyHandler();
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseCharacter::GetHit(const FVector& ImpactPoint, const TObjectPtr<AActor> Aggressor)
{
	IsAlive() ? DirectionalHitReact(ImpactPoint) : Die();
}

bool ABaseCharacter::IsMoving() const
{
	return GroundSpeed > 0.f;
}

bool ABaseCharacter::CanAttack() const
{
	return false;
}

bool ABaseCharacter::IsAttacking() const
{
	return false;
}

bool ABaseCharacter::CanMove() const
{
	return false;
}

void ABaseCharacter::PlayMontage(const TObjectPtr<UAnimMontage>& AnimMontage, const TArray<FName>& SectionNames, EMontageCallbackType MontageType)
{
	this->MontageCallbackType = MontageType;
	PlayRandomMontageSection(AnimMontage, SectionNames);
}

void ABaseCharacter::PlayMontage(const TObjectPtr<UAnimMontage>& AnimMontage, const FName& SectionName, EMontageCallbackType MontageType)
{
	this->MontageCallbackType = MontageType;
	PlayMontageSection(AnimMontage, SectionName);
}

void ABaseCharacter::PlayRandomMontageSection(const TObjectPtr<UAnimMontage>& AnimMontage,
                                              const TArray<FName>& SectionNames)
{
	if (!CharacterAnimInstance)
	{
		return;
	}

	const uint32 SectionIndex = FMath::RandRange(0, SectionNames.Num() - 1);
	PlayMontageSection(AnimMontage, SectionNames[SectionIndex]);
}

void ABaseCharacter::PlayMontageSection(const TObjectPtr<UAnimMontage>& AnimMontage, const FName& SectionName)
{
	if (!CharacterAnimInstance)
	{
		return;
	}

	FOnMontageEnded OnMontageEnded;
	FOnMontageBlendingOutStarted OnMontageBlendingOutStarted;
	OnMontageEnded.BindUObject(this, &ABaseCharacter::OnMontageEnded);
	OnMontageBlendingOutStarted.BindUObject(this, &ABaseCharacter::OnBlendingOutStarted);
	
	CharacterAnimInstance->Montage_Play(AnimMontage);
	CharacterAnimInstance->Montage_JumpToSection(SectionName);
	CharacterAnimInstance->Montage_SetEndDelegate(OnMontageEnded);
	CharacterAnimInstance->Montage_SetBlendingOutDelegate(OnMontageBlendingOutStarted);
}

void ABaseCharacter::OnMontageEnded(UAnimMontage* AnimMontage, bool bInterrupted)
{
	switch (MontageCallbackType)
	{
	case EMontageCallbackType::ATTACK_MONTAGE_CALLBACK:
		OnAttackEndCallback.ExecuteIfBound();
		break;
	case EMontageCallbackType::SHEATHE_MONTAGE_CALLBACK:
		OnSheatheEndCallback.ExecuteIfBound();
		break;
	case EMontageCallbackType::UNSHEATHE_MONTAGE_CALLBACK:
		OnUnsheatheEndCallback.ExecuteIfBound();
		break;
	case EMontageCallbackType::HIT_REACT_MONTAGE_CALLBACK:
		OnHitReactEndedCallback.ExecuteIfBound();
		break;
	case EMontageCallbackType::DEATH_MONTAGE_CALLBACK:
		OnDeathEndCallback.ExecuteIfBound();
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("ABaseCharacter::OnMontageEnded(): Callback delegate not bound!"));
		break;
	}
}

void ABaseCharacter::OnBlendingOutStarted(UAnimMontage* AnimMontage, bool bInterrupted)
{
	if (MontageCallbackType == EMontageCallbackType::DEATH_MONTAGE_CALLBACK)
	{
		OnDeathBlendingOutCallback.ExecuteIfBound(AnimMontage);
	}
}

void ABaseCharacter::WeaponAnimNotifyHandler() const
{
	if (!Weapon || !CharacterAnimInstance)
	{
		return;
	}

	switch (HelperFunctions::GetAnimNotifyState(CharacterAnimInstance))
	{
	case EAnimNotifyState::DETACH_FROM_HAND:
		Weapon->Sheathe(GetMesh());
		break;
	case EAnimNotifyState::ATTACH_TO_HAND:
		Weapon->Unsheathe(GetMesh());
		break;
	case EAnimNotifyState::ACTIVATE_WEAPON:
		if (const TObjectPtr<ABaseMeleeWeapon>& MeleeWeapon = Cast<ABaseMeleeWeapon>(Weapon))
		{
			MeleeWeapon->SetEnableWeaponBoxCollision(ECollisionEnabled::QueryOnly);
		}
		break;
	case EAnimNotifyState::DEACTIVATE_WEAPON:
		if (const TObjectPtr<ABaseMeleeWeapon>& MeleeWeapon = Cast<ABaseMeleeWeapon>(Weapon))
		{
			MeleeWeapon->SetEnableWeaponBoxCollision(ECollisionEnabled::NoCollision);
			MeleeWeapon->EmptyIgnoreActors();
		}
		break;
	default:
		break;
	}
}

void ABaseCharacter::Die()
{
}

void ABaseCharacter::DirectionalHitReact(const FVector& ImpactPoint)
{
	const FVector ImpactLowered(ImpactPoint.X, ImpactPoint.Y, GetActorLocation().Z);
	const FVector& ToHit = (ImpactLowered - GetActorLocation()).GetSafeNormal();

	const FVector Front = FVector(GetActorForwardVector()).GetSafeNormal();
	const FVector Right = FVector(GetActorRightVector()).GetSafeNormal();
	const FVector Left = -Right;
	const FVector Back = -Front;

	const float FrontAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(Front, ToHit)));
	const float RightAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(Right, ToHit)));
	const float LeftAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(Left, ToHit)));
	const float BackAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(Back, ToHit)));

	FName SectionName;
	if (-45.f <= FrontAngle && FrontAngle <= 45.f)
	{
		SectionName = FName("FromFront");
	}
	else if (-45.f <= RightAngle && RightAngle <= 45.f)
	{
		SectionName = FName("FromRight");
	}
	else if (-45.f <= LeftAngle && LeftAngle <= 45.f)
	{
		SectionName = FName("FromLeft");
	}
	else if (-45.f <= BackAngle && BackAngle <= 45.f)
	{
		SectionName = FName("FromBack");
	}
	
	PlayMontage(HitReactMontage, SectionName, EMontageCallbackType::HIT_REACT_MONTAGE_CALLBACK);
}

void ABaseCharacter::HandleDamage(float DamageAmount) const
{
	if (Attributes_DEPREC)
	{
		Attributes_DEPREC->ReceiveDamage(DamageAmount);
	}
}

bool ABaseCharacter::IsAlive() const
{
	return Attributes_DEPREC && Attributes_DEPREC->IsAlive();
}

void ABaseCharacter::SetEnabledMeshCollision(ECollisionEnabled::Type CollisionResponse) const
{
	GetMesh()->SetCollisionEnabled(CollisionResponse);
}

void ABaseCharacter::SetEnableCapsuleCollision(ECollisionEnabled::Type CollisionResponse) const
{
	GetCapsuleComponent()->SetCollisionEnabled(CollisionResponse);
}

void ABaseCharacter::CalculateGroundSpeed()
{
	GroundSpeed = UKismetMathLibrary::VSizeXY(GetCharacterMovement()->Velocity);
}
