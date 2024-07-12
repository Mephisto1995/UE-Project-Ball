// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseEnemyAnimInstance.generated.h"

enum class EEnemyState : uint8;
class UCharacterMovementComponent;
class ABaseEnemy;
/**
 * 
 */
UCLASS()
class PROJECTBALL_API UBaseEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float GroundSpeed;

private:
	TObjectPtr<ABaseEnemy> BaseEnemy;
};
