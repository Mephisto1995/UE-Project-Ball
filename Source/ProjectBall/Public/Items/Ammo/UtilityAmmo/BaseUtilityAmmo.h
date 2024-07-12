// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/Ammo/BaseAmmo.h"
#include "BaseUtilityAmmo.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBALL_API ABaseUtilityAmmo : public ABaseAmmo
{
	GENERATED_BODY()

public:
	ABaseUtilityAmmo();

	/** AActor */
	virtual void Tick(float DeltaTime) override;
	/** /AActor */
	
protected:
	/** AActor */
	virtual void BeginPlay() override;
	/** /AActor */
};
