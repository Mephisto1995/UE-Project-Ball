// © 2024 Pulse Core Interactive. All rights reserved.


#include "Items/Ammo/RangeAmmo/RangeAmmo/RifleAmmo.h"

ARifleAmmo::ARifleAmmo()
{
	DamageMin = 10.f; // TODO spl: create values in the Utilities/Constants
	DamageMax = 15.f; // TODO spl: create values in the Utilities/Constants
}

void ARifleAmmo::BeginPlay()
{
	Super::BeginPlay();
}

void ARifleAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}