// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	UNKOWN,

	IDLE UMETA(DisplayName = "Idle"),
	DEAD UMETA(DisplayName = "Dead"),
	PATROLLING UMETA(DisplayName = "Patrolling"),
	GETTING_HIT UMETA(DisplayName = "Getting hit"),
	RESETTING UMETA(DisplayName = "Reseting"),
	CHASING UMETA(DisplayName = "Chasing"),
	ATTACKING UMETA(DisplayName = "Attacking"),

	NUM_EES
};