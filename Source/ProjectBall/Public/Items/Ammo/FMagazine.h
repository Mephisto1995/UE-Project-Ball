// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "BaseAmmo.h"
#include "FMagazine.generated.h"

class ABaseAmmo;

USTRUCT()
struct FMagazine
{
	GENERATED_USTRUCT_BODY()
	FMagazine();

	bool HasAmmoInMagazine() const;
	void ConsumeAmmo();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABaseAmmo> Ammo;
	
	UPROPERTY(EditDefaultsOnly)
	int32 AmmoCount;
};
