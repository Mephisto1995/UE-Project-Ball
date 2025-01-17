// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseStatsComponent.generated.h"


UCLASS( Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTBALL_API UBaseStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBaseStatsComponent();

	/** <UActorComponent> */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/** </UActorComponent> */
protected:
	/** <UActorComponent> */
	virtual void BeginPlay() override;
	/** </UActorComponent> */

	/** <UObject> */
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
	/** </UObject> */
};
