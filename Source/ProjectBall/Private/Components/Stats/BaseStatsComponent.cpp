// © 2024 Pulse Core Interactive. All rights reserved.


#include "Components/Stats/BaseStatsComponent.h"

UBaseStatsComponent::UBaseStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBaseStatsComponent::BeginPlay()
{
	Super::BeginPlay();
}

EDataValidationResult UBaseStatsComponent::IsDataValid(FDataValidationContext& Context) const
{
	return Super::IsDataValid(Context);
}

void UBaseStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
