// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once
#include "IBaseMontageCallbacks.h"

class IPlayerMontageCallbacks : public IBaseMontageCallbacks
{
public:
	virtual void OnSheatheEndMontage() = 0;
	virtual void OnUnsheatheEndMontage() = 0;
};
