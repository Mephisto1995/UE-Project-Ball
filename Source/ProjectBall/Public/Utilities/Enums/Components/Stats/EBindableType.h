#pragma once

UENUM(Blueprintable)
enum class EBindableType : uint8
{
	UNKOWN,

	NO_BIND UMETA(DisplayName = "No bind"),
	BIND_ON_EQUIP UMETA(DisplayName = "Bind on equip"),
	BIND_ON_PICKUP UMETA(DisplayName = "Bind on pickup"),

	NUM_BINDS
};