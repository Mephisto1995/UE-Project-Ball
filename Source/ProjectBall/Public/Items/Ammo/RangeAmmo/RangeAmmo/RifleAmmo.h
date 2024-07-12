// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/Ammo/RangeAmmo/BaseRangeAmmo.h"
#include "RifleAmmo.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBALL_API ARifleAmmo : public ABaseRangeAmmo
{
	GENERATED_BODY()

public:
	ARifleAmmo();
	
	/** <AActor> */
	virtual void Tick(float DeltaTime) override;
	/** </AActor> */
	
protected:
	/** <AActor> */
	virtual void BeginPlay() override;
	/** </AActor> */
};
