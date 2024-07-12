// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

class AItem;
enum class EPlayerCombatState : uint8;
enum class EAnimNotifyState : uint8;

class HelperFunctions
{
public:
	static EAnimNotifyState GetAnimNotifyState(const TObjectPtr<UAnimInstance>& AnimInstance);
	static void DebugDisplayOverlappingOrNotWithItem(TObjectPtr<AItem> OverlappingItem);
	static void DrawDebugSpheresForAttackAndCombatRadius(const UWorld* World, const FVector& Location, const float& CombatRadius, const float& AttackRadius);
};
