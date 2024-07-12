// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

UENUM(BlueprintType)
enum class EPlayerAnimationPose : uint8
{
	UNKOWN,

	NOT_HOLDING UMETA(DisplayName = "Not Holding"),
	HOLDING_MELEE_WEAPON UMETA(DisplayName = "Holding Melee Weapon"),
	HOLDING_RANGED_WEAPON UMETA(DisplayName = "Holding Range Weapon"),
	AIMING_RANGED_WEAPON UMETA(DisplayName = "Aiming Range Weapon"),
	AIMING_AND_RUNNING_WITH_RANGED_WEAPON UMETA(DisplayName = "Aiming and Running with Range Weapon"),

	NUM_EWHS
};