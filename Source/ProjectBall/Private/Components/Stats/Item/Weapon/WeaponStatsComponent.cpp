// © 2024 Pulse Core Interactive. All rights reserved.


#include "Components/Stats/Item/Weapon/WeaponStatsComponent.h"

#include "Utilities/Enums/Items/Weapons/EWeaponType.h"

UWeaponStatsComponent::UWeaponStatsComponent():
WeaponType(EWeaponType::EWT_UNKNOWN)
, WeaponDurability(0)
, WeaponDamageMin(0)
, WeaponDamageMax(0)
{
}

void UWeaponStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWeaponStatsComponent::BeginPlay()
{
	Super::BeginPlay();
}
