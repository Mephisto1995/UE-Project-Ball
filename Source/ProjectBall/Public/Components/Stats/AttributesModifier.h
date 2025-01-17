// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributesModifier.generated.h"


enum class EAttributeToModify : uint8;
class UCoreAttributes;

USTRUCT(BlueprintType)
struct FAttributeModification
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EAttributeToModify AttributeToModify;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float NewValue;
};

UCLASS(DefaultToInstanced, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTBALL_API UAttributeModifier : public UObject
{
	GENERATED_BODY()

public:	
	UAttributeModifier();
	void ApplyModifications(const TObjectPtr<UCoreAttributes>& CoreAttributesComponent);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Attributes Modifier")
	TArray<FAttributeModification> AttributeModifications;
};
