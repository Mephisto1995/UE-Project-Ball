// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	EWS_UNKOWN,

	EWS_NOT_PICKED_UP,
	EWS_IN_PLAYERS_POSSESSION,

	NUM_EWS
};