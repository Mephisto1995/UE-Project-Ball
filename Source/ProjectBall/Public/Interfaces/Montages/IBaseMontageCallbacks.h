// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

class IBaseMontageCallbacks
{
public:
	virtual ~IBaseMontageCallbacks() {}
	
	virtual void OnAttackEndMontage() = 0;
	virtual void OnHitReactEndMontage() = 0;
	virtual void OnDeathEndMontage() = 0;

	// TODO spl: remove the parameter and use no param callback type for it. You have DeathMontage, use it.
	virtual void OnDeathBlendingOutEndMontage(const TObjectPtr<UAnimMontage>& AnimMontage) = 0;
};
