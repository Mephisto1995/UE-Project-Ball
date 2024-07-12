// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

namespace Constants::StringLiterals
{
	namespace Sockets
	{
		const FName HAND_SOCKET = FName("hand_socket");
		const FName BACK_SOCKET = FName("back_socket");
	}

	namespace Montages
	{
		const FName AIM_IDLE_SECTION = FName("AimIdle");
		const FName AIM_RUNNING_SECTION = FName("AimRun");
	}

	namespace SectionNames
	{
		const FName SHEATHE = FName("Sheathe");
		const FName UNSHEATHE = FName("Unsheathe");
	}

	namespace NotifyTracks
	{
		const FName ATTACH_TO_HAND = FName("AttachToHand");
		const FName DETACH_FROM_HAND = FName("DetachFromHand");
		const FName ACTIVATE_WEAPON = FName("ActivateWeapon");
		const FName DEACTIVATE_WEAPON = FName("DeactivateWeapon");
	}

	namespace Tags
	{
		const FName TAG_PLAYER_CHARACTER = FName("PlayerCharacter");
		const FName TAG_ENEMY_CHARACTER = FName("EnemyCharacter");
	}
	
	namespace Attacking
	{
		const FName ATTACK_STANDING_STILL = FName("Attack1");
		const FName ATTACK_RUNNING = FName("Attack2");
	}
}