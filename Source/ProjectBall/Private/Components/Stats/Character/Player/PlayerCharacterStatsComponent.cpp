// © 2024 Pulse Core Interactive. All rights reserved.


#include "Components/Stats/Character/Player/PlayerCharacterStatsComponent.h"

UPlayerCharacterStatsComponent::UPlayerCharacterStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerCharacterStatsComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UPlayerCharacterStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}