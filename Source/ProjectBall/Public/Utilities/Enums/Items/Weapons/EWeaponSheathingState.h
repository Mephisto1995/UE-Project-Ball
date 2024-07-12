// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

UENUM(BlueprintType)
enum class EWeaponSheathingState : uint8
{
	EWSS_UNKOWN,

	EWSS_SHEATHED,
	EWSS_UNSHEATHED,

	NUM_EWSS
};