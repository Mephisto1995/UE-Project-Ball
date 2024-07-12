// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once


/**
 * Every enum entry you add here, don't forget to create a use case in 
 * HelperFunctions::GetAnimNotifyState
 * 
 */
enum class EAnimNotifyState : uint8
{
	UNKOWN,

	DETACH_FROM_HAND,
	ATTACH_TO_HAND,
	ACTIVATE_WEAPON,
	DEACTIVATE_WEAPON,

	NUM_EMT
};