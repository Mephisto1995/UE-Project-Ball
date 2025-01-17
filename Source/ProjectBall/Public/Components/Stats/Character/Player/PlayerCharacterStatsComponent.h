// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Stats/Character/BaseCharacterStatsComponent.h"
#include "PlayerCharacterStatsComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBALL_API UPlayerCharacterStatsComponent : public UBaseCharacterStatsComponent
{
	GENERATED_BODY()

public:
	UPlayerCharacterStatsComponent();

	/** <UActorComponent> */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/** </UActorComponent> */

protected:
	/** <UActorComponent> */
	virtual void BeginPlay() override;
	/** </UActorComponent> */
};
