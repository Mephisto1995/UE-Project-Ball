// © 2024 Pulse Core Interactive. All rights reserved.


#include "Components/Stats/Item/Ammo/AmmoStatsComponent.h"

UAmmoStatsComponent::UAmmoStatsComponent()
{
}

void UAmmoStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAmmoStatsComponent::BeginPlay()
{
	Super::BeginPlay();
}
