// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/MeleeWeapons/BaseMeleeWeapon.h"
#include "MeleeWeapon.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBALL_API AMeleeWeapon : public ABaseMeleeWeapon
{
	GENERATED_BODY()

public:
	AMeleeWeapon();

	/** AActor */
	virtual void Tick(float DeltaTime) override;
	/** /AActor */

protected:
	/** AActor */
	virtual void BeginPlay() override;
	/** /AActor */
};
