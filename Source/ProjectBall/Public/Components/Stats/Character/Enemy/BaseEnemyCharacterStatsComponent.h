// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Stats/Character/BaseCharacterStatsComponent.h"
#include "BaseEnemyCharacterStatsComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBALL_API UBaseEnemyCharacterStatsComponent : public UBaseCharacterStatsComponent
{
	GENERATED_BODY()
	
public:
	UBaseEnemyCharacterStatsComponent();

	/** <UActorComponent> */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/** </UActorComponent> */

protected:
	/** <UActorComponent> */
	virtual void BeginPlay() override;
	/** </UActorComponent> */
};
