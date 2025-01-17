// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Stats/BaseStatsComponent.h"
#include "ItemStatsComponent.generated.h"

class UAttributeModifier;
enum class EBindableType : uint8;
/**
 * 
 */
UCLASS()
class PROJECTBALL_API UItemStatsComponent : public UBaseStatsComponent
{
	GENERATED_BODY()

public:
	UItemStatsComponent();

	/** <UActorComponent> */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/** </UActorComponent> */

protected:
	/** <UActorComponent> */
	virtual void BeginPlay() override;
	/** </UActorComponent> */
	
private:
	/** Item name. */
	UPROPERTY(EditDefaultsOnly, Category = "Item stats")
	FName ItemName;

	/** Item description. Can be skipped. */
	UPROPERTY(EditDefaultsOnly, Category = "Item stats")
	FString ItemDescription;
	
	/** Item level. How powerful an item can be. */
	UPROPERTY(EditDefaultsOnly, Category = "Item stats")
	float ItemLevel;

	/** Bind type. */
	UPROPERTY(EditDefaultsOnly, Category = "Item stats")
	EBindableType BindType;

	/** Is unique refers to if player can dual wield 2 swords of same type
	 * Basically if the player can equip 2 identical items.
	 * If this is true, then it cannot.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Item stats")
	bool bIsUnique;

	/** Minimum level required for the player to have in order to equip that item. */
	UPROPERTY(EditDefaultsOnly, Category = "Item stats")
	int MinLevelRequirement;

	/** Add stats modifiers here (+2 strength and +3 stamina, etc. ). */
	UPROPERTY(Instanced, VisibleDefaultsOnly, Category = "Item stats")
	TObjectPtr<UAttributeModifier> AttributeModifier;

public:
	FORCEINLINE FName GetItemName() const { return ItemName; }
	FORCEINLINE FString GetItemDescription() const { return ItemDescription; }
	FORCEINLINE float GetItemLevel() const { return ItemLevel; }
	FORCEINLINE EBindableType GetBindType() const { return BindType; }
	FORCEINLINE bool GetIsUnique() const { return bIsUnique; }
	FORCEINLINE int GetMinLevelRequirement() const { return MinLevelRequirement; }
	FORCEINLINE TObjectPtr<UAttributeModifier> GetAttributeModifier() const { return AttributeModifier; }
};
