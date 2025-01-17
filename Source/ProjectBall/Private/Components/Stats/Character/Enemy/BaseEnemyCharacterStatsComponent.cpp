// © 2024 Pulse Core Interactive. All rights reserved.


#include "Components/Stats/Character/Enemy/BaseEnemyCharacterStatsComponent.h"

UBaseEnemyCharacterStatsComponent::UBaseEnemyCharacterStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBaseEnemyCharacterStatsComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBaseEnemyCharacterStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}