// © 2024 Pulse Core Interactive. All rights reserved.


#include "Components/Stats/Character/BaseCharacterStatsComponent.h"

#include "Characters/BaseCharacter.h"
#include "Components/Stats/CoreAttributes.h"
#include "Misc/DataValidation.h"

UBaseCharacterStatsComponent::UBaseCharacterStatsComponent():
CurrentHealth(0.f)
, MaxHealth(0.f)
, MovementSpeed(0.f)
, CoreAttributes(NewObject<UCoreAttributes>())
{
	PrimaryComponentTick.bCanEverTick = true;
	
	// TODO spl: This is done to override the adding on values of previous game sessions, so the player always starts with default values. 
	Debug_InitializeWithDefaultValues();
}

void UBaseCharacterStatsComponent::BeginPlay()
{
	Super::BeginPlay();
}

EDataValidationResult UBaseCharacterStatsComponent::IsDataValid(FDataValidationContext& Context) const
{
	if (const TObjectPtr<AActor>& Owner = GetOwner())
	{
		if (Owner->IsA(ABaseCharacter::StaticClass()))
		{
			return EDataValidationResult::Valid;
		}
		else
		{
            FText ErrorMsg = FText::Format(NSLOCTEXT("YourNamespace", "InvalidOwner", "Owner of {0} is not a ABaseCharacter or derived class."), FText::FromString(GetNameSafe(this)));
			Context.AddError(ErrorMsg);
			return EDataValidationResult::Invalid;
		}
	}

	FText ErrorMsg = FText::Format(NSLOCTEXT("YourNamespace", "NoOwner", "{0} has no owner, which is required."), FText::FromString(GetNameSafe(this)));
	Context.AddError(ErrorMsg);
	return EDataValidationResult::Invalid;
}

void UBaseCharacterStatsComponent::Debug_InitializeWithDefaultValues()
{
	CurrentHealth = 100.f;
	MaxHealth = 100.f;

	if (CoreAttributes)
	{
		CoreAttributes->Debug_ModifyAll(10);
	}
	
}

void UBaseCharacterStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                 FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
