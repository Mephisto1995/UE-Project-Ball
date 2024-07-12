// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/BaseWeapon.h"
#include "BaseMeleeWeapon.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBALL_API ABaseMeleeWeapon : public ABaseWeapon
{
	GENERATED_BODY()

public:
	ABaseMeleeWeapon();

	/** AActor */
	virtual void Tick(float DeltaTime) override;
	/** /AActor */

	void SetEnableWeaponBoxCollision(ECollisionEnabled::Type value);
	void EmptyIgnoreActors();

protected:
	/** AActor */
	virtual void BeginPlay() override;
	/** /AActor */

	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
								 const FHitResult& SweepResult);

	void InflictDamage(const TObjectPtr<AActor>& OtherActor);
	void BoxTrace(FHitResult& BoxHit);
	void ExecuteGetHit(const FHitResult& BoxHit, const TObjectPtr<AActor>& OtherActor);

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	FVector BoxTraceExtent;
	
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	bool bShowDebugBox;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	TObjectPtr<UBoxComponent> WeaponBoxComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> BoxTraceStart;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> BoxTraceEnd;

	TArray<TObjectPtr<AActor>> IgnoreActors;

private:
	bool ActorIsSameType(const TObjectPtr<AActor>& OtherActor) const;
};
