// © 2024 Pulse Core Interactive. All rights reserved.


#include "Items/Weapons/RangeWeapons/RangeWeapons/RifleWeapon.h"

#include "Components/BoxComponent.h"
#include "Components/Stats/Item/Weapon/WeaponStatsComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Items/Ammo/BaseAmmo.h"
#include "Items/Ammo/FMagazine.h"
#include "Items/Ammo/RangeAmmo/RangeAmmo/RifleAmmo.h"

ARifleWeapon::ARifleWeapon()
{
	DamageMin = 30.f;
	DamageMax = 35.f;
}

void ARifleWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ARifleWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARifleWeapon::UseWeapon()
{
	Super::UseWeapon();
	
	if (!AmmoSpawningPoint)
	{
		return;
	}

	const FVector& SpawnedLocation = AmmoSpawningPoint->GetComponentLocation();
	FRotator SpawnedRotation = AmmoSpawningPoint->GetComponentRotation();

	SpawnedRotation.Pitch = 0.0f;
	SpawnedRotation.Roll = 0.0f;

	// This makes sense because we want to know who fired the shot.
	// If I shoot somebody, the owner of the weapon AND bullet will be me.
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.Owner = CurrentOwner;
	ActorSpawnParameters.Instigator = CurrentInstigator;

	if (const TObjectPtr<ABaseRangeAmmo> SpawnedAmmo = GetWorld()->SpawnActor<ABaseRangeAmmo>(Magazine.Ammo, SpawnedLocation, SpawnedRotation, ActorSpawnParameters))
	{
		if (const TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent = SpawnedAmmo->FindComponentByClass<UProjectileMovementComponent>())
		{
			ProjectileMovementComponent->bIsHomingProjectile = false;
			ProjectileMovementComponent->Velocity = SpawnedRotation.Vector() * ProjectileMovementComponent->InitialSpeed;

			Magazine.ConsumeAmmo();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ProjectileMovementComponent not found on the spawned ammo."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn ammo."));
	}
}

bool ARifleWeapon::CanUseWeapon() const
{
	return Magazine.HasAmmoInMagazine();
}
