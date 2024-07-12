// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

UENUM(BlueprintType)
enum class EItemState : uint8
{
	EIS_UNKOWN,

	EIS_UNNEQUIPPED,
	EIS_EQUIPPED,

	NUM_EIS
};