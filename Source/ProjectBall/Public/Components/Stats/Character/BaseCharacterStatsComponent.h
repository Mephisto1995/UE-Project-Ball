// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Stats/BaseStatsComponent.h"
#include "BaseCharacterStatsComponent.generated.h"

class UCoreAttributes;
/**
 * 
 */
UCLASS(Abstract)
class PROJECTBALL_API UBaseCharacterStatsComponent : public UBaseStatsComponent
{
	GENERATED_BODY()

public:
	UBaseCharacterStatsComponent();

	/** <UActorComponent> */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/** </UActorComponent> */
	
protected:
	/** <UActorComponent> */
	virtual void BeginPlay() override;
	/** </UActorComponent> */

	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;

private:
	// TODO spl: Debug purposes, please remove after.
	void Debug_InitializeWithDefaultValues();
	
	UPROPERTY(EditDefaultsOnly, Category = "Base Character Stats")
	float CurrentHealth;
	
	UPROPERTY(EditDefaultsOnly, Category = "Base Character Stats")
	float MaxHealth;

	UPROPERTY(EditDefaultsOnly, Category = "Base Character Stats")
	float MovementSpeed;

	UPROPERTY(Instanced, VisibleAnywhere, Category = "Base Character Stats")
	TObjectPtr<UCoreAttributes> CoreAttributes;

public:
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	FORCEINLINE TObjectPtr<UCoreAttributes> GetCoreAttributes() const { return CoreAttributes; }
};