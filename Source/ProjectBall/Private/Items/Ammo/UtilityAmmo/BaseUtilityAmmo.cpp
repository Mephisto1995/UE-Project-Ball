// © 2024 Pulse Core Interactive. All rights reserved.


#include "Items/Ammo/UtilityAmmo/BaseUtilityAmmo.h"

#include "Utilities/Enums/Items/EItemType.h"

ABaseUtilityAmmo::ABaseUtilityAmmo()
{
	ItemType = EItemType::EIT_AMMO;
	DamageMin = 0.f;
	DamageMax = 0.f;
}

void ABaseUtilityAmmo::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseUtilityAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}