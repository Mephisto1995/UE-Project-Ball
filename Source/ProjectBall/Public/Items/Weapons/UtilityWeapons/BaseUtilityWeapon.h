// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/BaseWeapon.h"
#include "Items/Ammo/FMagazine.h"
#include "BaseUtilityWeapon.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBALL_API ABaseUtilityWeapon : public ABaseWeapon
{
	GENERATED_BODY()

public:
	ABaseUtilityWeapon();

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

	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	FMagazine Magazine;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> AmmoSpawningPoint;

private:
};