// © 2024 Pulse Core Interactive. All rights reserved.


#include "Enemies/BaseEnemyAnimInstance.h"

#include "Enemies/BaseEnemy.h"

void UBaseEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	BaseEnemy = Cast<ABaseEnemy>(TryGetPawnOwner()); 
}

void UBaseEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (BaseEnemy)
	{
		GroundSpeed = BaseEnemy->GetGroundSpeed();
	}
}
