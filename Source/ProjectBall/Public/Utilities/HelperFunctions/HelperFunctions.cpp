// © 2024 Pulse Core Interactive. All rights reserved.

#include "HelperFunctions.h"

#include "Items/Item.h"
#include "Utilities/Constants/StringLiterals.h"
#include "Utilities/Enums/Montages/EAnimNotify.h"

EAnimNotifyState HelperFunctions::GetAnimNotifyState(const TObjectPtr<UAnimInstance>& AnimInstance)
{
	if(AnimInstance->WasAnimNotifyNameTriggeredInAnyState(Constants::StringLiterals::NotifyTracks::DETACH_FROM_HAND))
	{
		return EAnimNotifyState::DETACH_FROM_HAND;
	}
	
	if (AnimInstance->WasAnimNotifyNameTriggeredInAnyState(Constants::StringLiterals::NotifyTracks::ATTACH_TO_HAND))
	{
		return EAnimNotifyState::ATTACH_TO_HAND;
	}

	if (AnimInstance->WasAnimNotifyNameTriggeredInAnyState(Constants::StringLiterals::NotifyTracks::ACTIVATE_WEAPON))
	{
		return EAnimNotifyState::ACTIVATE_WEAPON;
	}

	if (AnimInstance->WasAnimNotifyNameTriggeredInAnyState(Constants::StringLiterals::NotifyTracks::DEACTIVATE_WEAPON))
	{
		return EAnimNotifyState::DEACTIVATE_WEAPON;
	}

	return EAnimNotifyState::UNKOWN;
}

void HelperFunctions::DebugDisplayOverlappingOrNotWithItem(TObjectPtr<AItem> OverlappingItem)
{
	if (!GEngine)
	{
		return;
	}

	const FString& DebugMessage = OverlappingItem ? OverlappingItem->GetName() : "No overlapping item";
	GEngine->AddOnScreenDebugMessage(2, 10.f, FColor::Emerald, DebugMessage);
}

void HelperFunctions::DrawDebugSpheresForAttackAndCombatRadius(const UWorld* World, const FVector& Location, const float& CombatRadius, const float& AttackRadius)
{
	DrawDebugSphere(
		World,
		Location,
		CombatRadius,
		24, // Sphere complexity (number of segments)
		FColor::Red,
		false, // Persistent (set to false so it only shows for one frame)
		0, // How long to display (0 means just for this frame)
		0, // Depth priority
		1.0f // Thickness
	);

	// Draw the Attack Radius in green
	DrawDebugSphere(
		World,
		Location,
		AttackRadius,
		24, // Sphere complexity
		FColor::Green,
		false, // Persistent
		0, // Duration
		0, // Depth priority
		1.0f // Thickness
	);
}
