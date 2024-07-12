// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/RangeWeapons/BaseRangeWeapon.h"
#include "RifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBALL_API ARifleWeapon : public ABaseRangeWeapon
{
	GENERATED_BODY()

public:
	ARifleWeapon();

	/** AActor */
	virtual void Tick(float DeltaTime) override;
	/** /AActor */
	
	/** ABaseWeapon */
	virtual void UseWeapon() override;
	virtual bool CanUseWeapon() const override; // Use the Magazine.HasAmmo logic.
	/** /ABaseWeapon */

protected:
	/** AActor */
	virtual void BeginPlay() override;
	/** /AActor */
};
