// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

UENUM(Blueprintable)
enum class EMontageCallbackType : uint8
{
	UNKOWN,

	ATTACK_MONTAGE_CALLBACK,
	SHEATHE_MONTAGE_CALLBACK,
	UNSHEATHE_MONTAGE_CALLBACK,
	HIT_REACT_MONTAGE_CALLBACK,
	DEATH_MONTAGE_CALLBACK,

	NUM_MONTAGE_TYPES
};