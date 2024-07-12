// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	EWT_UNKNOWN,
	
	EWT_MELEE,
	EWT_RANGED,
	EWT_UTILITY,

	NUM_EWT
};