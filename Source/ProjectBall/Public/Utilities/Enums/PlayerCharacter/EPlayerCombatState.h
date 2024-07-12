// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

UENUM(BlueprintType)
enum class EPlayerCombatState : uint8
{
	UNKOWN,

	UNENGAGED,
	AIMING,
	AIMING_AND_RUNNING,
	SHOOTING,
	SHOOTING_AND_RUNNING,
	MELEE_ATTACKING, 
	SHEATHING,
	UNSHEATHING,

	NUM_EPS
};