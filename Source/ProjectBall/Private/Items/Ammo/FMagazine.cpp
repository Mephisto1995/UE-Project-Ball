// © 2024 Pulse Core Interactive. All rights reserved.

#include "Items/Ammo/FMagazine.h"

FMagazine::FMagazine() :
Ammo(nullptr)
, AmmoCount(0)
{
	
}

bool FMagazine::HasAmmoInMagazine() const
{
	return AmmoCount > 0;
}

void FMagazine::ConsumeAmmo()
{
	if (AmmoCount > 0)
	{
		--AmmoCount;
	}
}
