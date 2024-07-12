#pragma once

UENUM(Blueprintable)
enum class EAmmoType : uint8
{
	UNKOWN,
	
	AMMO_RIFLE UMETA(DisplayName = "Rifle ammo"),
	AMMO_UTILITY UMETA(DisplayName = "Utility ammo"),

	NUM_AMMO
};