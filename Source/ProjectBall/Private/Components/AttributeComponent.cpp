// © 2024 Pulse Core Interactive. All rights reserved.


#include "Components/AttributeComponent.h"

#include "Utilities/Constants/Attributes.h"

UAttributeComponent::UAttributeComponent() :
CurrentHealth(Constants::Attributes::Health::CURRENT_HEALTH) 
, MaxHealth(Constants::Attributes::Health::MAX_HEALTH)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAttributeComponent::ReceiveDamage(float Damage)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.f, MaxHealth);
}

bool UAttributeComponent::IsAlive() const
{
	return CurrentHealth != 0.f;
}

