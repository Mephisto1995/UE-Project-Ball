// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/Ammo/BaseAmmo.h"
#include "BaseRangeAmmo.generated.h"

class UCapsuleComponent;
/**
 * 
 */
UCLASS()
class PROJECTBALL_API ABaseRangeAmmo : public ABaseAmmo
{
	GENERATED_BODY()

public:
	ABaseRangeAmmo();
	
	/** AActor */
	virtual void Tick(float DeltaTime) override;
	/** /AActor */
	
protected:
	/** AActor */
	virtual void BeginPlay() override;
	/** /AActor */

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								 UPrimitiveComponent* OtherComp,
								 int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	void InflictDamage(const TObjectPtr<AActor>& OtherActor);
	void SphereTrace(FHitResult& SphereHit) const;
	void ExecuteGetHit(const FHitResult& BoxHit, const TObjectPtr<AActor>& OtherActor) const;
	
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	bool bShowDebugBox;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SphereTraceStart;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SphereTraceEnd;
};