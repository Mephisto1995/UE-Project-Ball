// © 2024 Pulse Core Interactive. All rights reserved.


#include "Items/Ammo/BaseAmmo.h"

#include "Components/Stats/Item/Ammo/AmmoStatsComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Utilities/Constants/Ammo.h"
#include "Utilities/Enums/Items/EItemState.h"
#include "Utilities/Enums/Items/EItemType.h"

ABaseAmmo::ABaseAmmo() :
ProjectileMovementComponent(CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent")))
, DamageMin(0.f)
, DamageMax(0.f)
, MaximumDistanceTravel(3000.f) // TODO spl: create values in the Utilities/Constants
, AmmoStatsComponent(CreateDefaultSubobject<UAmmoStatsComponent>(TEXT("AmmoStatsComponent")))
{
	ProjectileMovementComponent->InitialSpeed = Constants::Ammo::PMC::INITIAL_SPEED;
	ProjectileMovementComponent->MaxSpeed = Constants::Ammo::PMC::MAX_SPEED;
	ProjectileMovementComponent->ProjectileGravityScale = Constants::Ammo::PMC::PROJECTILE_GRAVITY_SCALE;

	ItemState = EItemState::EIS_UNNEQUIPPED;
	ItemType = EItemType::EIT_AMMO;
}

void ABaseAmmo::BeginPlay()
{
	Super::BeginPlay();
	InitialLocation = GetActorLocation();
}

void ABaseAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckMaxDistanceTravelled();
}

void ABaseAmmo::CheckMaxDistanceTravelled()
{
	const double DistanceTravelled = FVector::Dist(InitialLocation, GetActorLocation());

	if (DistanceTravelled >= MaximumDistanceTravel)
	{
		Destroy();
	}
}