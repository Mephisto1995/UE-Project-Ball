// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Stats/Item/ItemStatsComponent.h"
#include "AmmoStatsComponent.generated.h"

enum class EAmmoType : uint8;
/**
 * 
 */
UCLASS()
class PROJECTBALL_API UAmmoStatsComponent : public UItemStatsComponent
{
	GENERATED_BODY()

public:
	UAmmoStatsComponent();

	/** <UActorComponent> */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/** </UActorComponent> */

protected:
	/** <UActorComponent> */
	virtual void BeginPlay() override;
	/** </UActorComponent> */

private:
	/** Ammo type. */
	UPROPERTY(EditDefaultsOnly, Category = "Ammo stats")
	EAmmoType AmmoType;
	
	/** Ammo range. How far the bullet travels until it disappears. */
	UPROPERTY(EditDefaultsOnly, Category = "Ammo stats")
	float AmmoRange;
	
	/** Ammo damage min. */
	UPROPERTY(EditDefaultsOnly, Category = "Ammo stats")
	float AmmoDamageMin;
	
	/** Ammo damage min. */
	UPROPERTY(EditDefaultsOnly, Category = "Ammo stats")
	float AmmoDamageMax;
	
public:
	FORCEINLINE EAmmoType GetAmmoType() const {return AmmoType; }
	FORCEINLINE float GetAmmoRange() const {return AmmoRange; }
	FORCEINLINE float GetAmmoDamageMin() const {return AmmoDamageMin; }
	FORCEINLINE float GetAmmoDamageMax() const {return AmmoDamageMax; }
};
