// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"

// TODO spl: This is deprecated, please remove AFTER you've ported the functionality accordingly
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTBALL_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAttributeComponent();

	/** <AActor> */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/** </AActor> */

	void ReceiveDamage(float Damage); // Move to BaseCharacterStatsComponent
	bool IsAlive() const; // Move to BaseCharacterStatsComponent
protected:
	/** <AActor> */
	virtual void BeginPlay() override;
	/** </AActor> */

private:
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float CurrentHealth; // Move to BaseCharacterStatsComponent
	
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float MaxHealth; // Move to BaseCharacterStatsComponent
};
