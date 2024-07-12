// © 2024 Pulse Core Interactive. All rights reserved.


#include "Items/Weapons/RangeWeapons/BaseRangeWeapon.h"

#include "Components/BoxComponent.h"
#include "Components/Stats/Item/Weapon/WeaponStatsComponent.h"
#include "Utilities/Enums/Items/Weapons/EWeaponType.h"

ABaseRangeWeapon::ABaseRangeWeapon() : 
AmmoSpawningPoint(CreateDefaultSubobject<UBoxComponent>(TEXT("AmmoSpawningPoint")))
{
	PrimaryActorTick.bCanEverTick = true;
	AmmoSpawningPoint->SetupAttachment(GetRootComponent());
	
	DamageMin = 0.f;
	DamageMax = 0.f;
	WeaponType = EWeaponType::EWT_RANGED;
}

void ABaseRangeWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseRangeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseRangeWeapon::UseWeapon()
{
	Super::UseWeapon();
}

bool ABaseRangeWeapon::CanUseWeapon() const
{
	return Super::CanUseWeapon();
}