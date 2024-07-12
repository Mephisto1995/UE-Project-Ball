// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

UENUM(Blueprintable)
enum class EAttackMontagePlayingStatus : uint8
{
	UNKOWN,

	NOT_PLAYING UMETA(DisplayName = "Not Playing"),
	PLAYING UMETA(DisplayName = "Playing"),

	NUM_EAMPS
};