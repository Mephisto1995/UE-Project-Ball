// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Stats/Item/ItemStatsComponent.h"
#include "WeaponStatsComponent.generated.h"

enum class EWeaponType : uint8;
/**
 * 
 */
UCLASS()
class PROJECTBALL_API UWeaponStatsComponent : public UItemStatsComponent
{
	GENERATED_BODY()

public:
	UWeaponStatsComponent();

	/** <UActorComponent> */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/** </UActorComponent> */

protected:
	/** <UActorComponent> */
	virtual void BeginPlay() override;
	/** </UActorComponent> */

private:
	/** Weapon type (melee, ranged, utility). */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon stats")
	EWeaponType WeaponType;
	
	/** Durability of weapon. How long will a weapon resist until you must repair before use it. Not yet implemented*/
	UPROPERTY(EditDefaultsOnly, Category = "Weapon stats")
	float WeaponDurability;
	
	/** Damage min. */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon stats")
	float WeaponDamageMin;
	
	/** Damage max. */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon stats")
	float WeaponDamageMax;

public:
	FORCEINLINE EWeaponType GetWeaponType() const { return WeaponType; }
	FORCEINLINE float GetWeaponDurability() const { return WeaponDurability; }
	FORCEINLINE float GetWeaponDamageMin() const { return WeaponDamageMin; }
	FORCEINLINE float GetWeaponDamageMax() const { return WeaponDamageMax; }
};
