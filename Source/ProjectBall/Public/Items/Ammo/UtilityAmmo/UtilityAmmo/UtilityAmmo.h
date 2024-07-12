// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/Ammo/UtilityAmmo/BaseUtilityAmmo.h"
#include "UtilityAmmo.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBALL_API AUtilityAmmo : public ABaseUtilityAmmo
{
	GENERATED_BODY()

public:
	AUtilityAmmo();

	/** <AActor> */
	virtual void Tick(float DeltaTime) override;
	/** </AActor> */
	
protected:
	/** <AActor> */
	virtual void BeginPlay() override;
	/** </AActor> */
};
