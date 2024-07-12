// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "BaseAmmo.generated.h"

class UAmmoStatsComponent;
class UProjectileMovementComponent;
/**
 * 
 */
UCLASS()
class PROJECTBALL_API ABaseAmmo : public AItem
{
	GENERATED_BODY()

public:
	ABaseAmmo();

	/** <AActor> */
	virtual void Tick(float DeltaTime) override;
	/** </AActor> */
	
protected:
	/** <AActor> */
	virtual void BeginPlay() override;
	/** </AActor> */

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, Category = Damage)
	float DamageMin;
	UPROPERTY(EditAnywhere, Category = Damage)
	float DamageMax;

	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	float MaximumDistanceTravel;

	UPROPERTY(VisibleInstanceOnly, Category = Ammo)
	FVector InitialLocation;

	/** <UAmmoStatsComponent> */
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	TObjectPtr<UAmmoStatsComponent> AmmoStatsComponent;
	/** </UAmmoStatsComponent> */

private:
	void CheckMaxDistanceTravelled();
};
