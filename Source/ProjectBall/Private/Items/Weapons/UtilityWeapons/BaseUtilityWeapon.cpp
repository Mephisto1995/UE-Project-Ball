// © 2024 Pulse Core Interactive. All rights reserved.


#include "Items/Weapons/UtilityWeapons/BaseUtilityWeapon.h"

#include "Components/BoxComponent.h"
#include "Components/Stats/Item/Weapon/WeaponStatsComponent.h"
#include "Utilities/Enums/Items/Weapons/EWeaponType.h"

ABaseUtilityWeapon::ABaseUtilityWeapon() :
AmmoSpawningPoint(CreateDefaultSubobject<UBoxComponent>(TEXT("AmmoSpawningPoint")))
{
	PrimaryActorTick.bCanEverTick = true;
	AmmoSpawningPoint->SetupAttachment(GetRootComponent());
	
	DamageMin = 0.f;
	DamageMax = 0.f;
	WeaponType = EWeaponType::EWT_UTILITY;
}

void ABaseUtilityWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseUtilityWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseUtilityWeapon::UseWeapon()
{
	Super::UseWeapon();
}

bool ABaseUtilityWeapon::CanUseWeapon() const
{
	return Super::CanUseWeapon();
}
