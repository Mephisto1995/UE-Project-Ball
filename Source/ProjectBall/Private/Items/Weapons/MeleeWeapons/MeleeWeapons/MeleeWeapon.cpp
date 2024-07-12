// © 2024 Pulse Core Interactive. All rights reserved.


#include "Items/Weapons/MeleeWeapons/MeleeWeapons/MeleeWeapon.h"

AMeleeWeapon::AMeleeWeapon()
{
	DamageMin = 10.f;
	DamageMax = 12.f;
}

void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AMeleeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
