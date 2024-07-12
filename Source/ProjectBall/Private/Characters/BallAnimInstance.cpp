// © 2024 Pulse Core Interactive. All rights reserved.


#include "Characters/BallAnimInstance.h"

#include "Characters/PlayerCharacter.h"

void UBallAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Player = Cast<APlayerCharacter>(TryGetPawnOwner());
	
	if (Player)
	{
		PlayerMovementComponent = Player->GetCharacterMovement();
	}
}

void UBallAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (Player)
	{
		GroundSpeed = Player->GetGroundSpeed();
		WeaponHoldingState = Player->GetPlayerAnimationPose();
	}
}
