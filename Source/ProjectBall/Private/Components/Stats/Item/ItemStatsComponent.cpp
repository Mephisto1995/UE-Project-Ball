// © 2024 Pulse Core Interactive. All rights reserved.


#include "Components/Stats/Item/ItemStatsComponent.h"

#include "Components/Stats/AttributesModifier.h"

UItemStatsComponent::UItemStatsComponent():
ItemLevel(0)
, BindType()
, bIsUnique(false)
, MinLevelRequirement(0)
, AttributeModifier(CreateDefaultSubobject<UAttributeModifier>("Attribute Modifier Component"))
{
}

void UItemStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UItemStatsComponent::BeginPlay()
{
	Super::BeginPlay();
}
