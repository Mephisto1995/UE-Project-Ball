// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BallAnimInstance.generated.h"

enum class EPlayerAnimationPose : uint8;
class UCharacterMovementComponent;
class APlayerCharacter;
/**
 * 
 */
UCLASS()
class PROJECTBALL_API UBallAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerCharacter> Player;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	TObjectPtr<UCharacterMovementComponent> PlayerMovementComponent;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Movement | Weapon State")
	EPlayerAnimationPose WeaponHoldingState;
};
