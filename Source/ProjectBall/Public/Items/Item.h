// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class UCoreAttributes;
class UItemStatsComponent;
class USphereComponent;
enum class EItemState : uint8;
enum class EItemType : uint8;

UCLASS()
class PROJECTBALL_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();
	
	/** AActor */
	virtual void Tick(float DeltaTime) override;
	/** /AActor */

	/**
	 * TODO spl:
	 * At the moment, when we equip a weapon, we directly attach it to the hand socket, as in the weapon is unsheathed.
	 * Moving forward, I'd like for this behavior to be that when a player picks-up an item, it's set directly in his inventory.
	 * Inventory not yet implemented, will implement soon™.
	 * Might be better to move the logic of adding to inventory in Item class, needs investigation.
	 */
	virtual void PickupItem(const TObjectPtr<USceneComponent>& Parent, 
		const TObjectPtr<AActor>& NewOwner,
		const TObjectPtr<APawn> NewInstigator);
protected:
	/** AActor */
	virtual void BeginPlay() override;
	/** /AActor */

	UFUNCTION()
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								 UPrimitiveComponent* OtherComp,
								 int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
									UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool CanAnimate() const;
	void FloatItem();
	void RotateItem(float DeltaTime);
	void ApplyItemStats(const TObjectPtr<UCoreAttributes>& CoreAttributes);

	UPROPERTY(EditDefaultsOnly, Category = "Items")
	FName ItemName;

	UPROPERTY(EditDefaultsOnly, Category = "Items")
	FString ItemDescription;

	UPROPERTY(VisibleAnywhere, Category = "Items")
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	UPROPERTY(VisibleAnywhere, Category = "Items")
	TObjectPtr<USphereComponent> SphereComponent;
	
	EItemState ItemState;
	EItemType ItemType;

	/** <UItemStatsComponent> */
	UPROPERTY(VisibleDefaultsOnly, Category = "Items | Components")
	TObjectPtr<UItemStatsComponent> ItemStatsComponent;
	/** </UItemStatsComponent> */

	UPROPERTY(VisibleAnywhere, Category = "Items")
	TObjectPtr<USceneComponent> CurrentParent;
	UPROPERTY(VisibleAnywhere, Category = "Items")
	TObjectPtr<AActor> CurrentOwner;
	UPROPERTY(VisibleAnywhere, Category = "Items")
	TObjectPtr<APawn> CurrentInstigator;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Items")
	bool bCanStack;

	/** <Floating items logic> */
	float BaseZ;

	UPROPERTY(EditDefaultsOnly, Category = "Items | Animation | Floating")
	float FloatingHeight;

	UPROPERTY(EditDefaultsOnly, Category = "Items | Animation | Floating")
	float FloatingSpeed;
	
	UPROPERTY(EditDefaultsOnly, Category = "Items | Animation | Rotating")
	float RotationSpeed;
	/** </Floating items logic> */

public:
	FORCEINLINE FName GetItemName() const { return ItemName; }
	FORCEINLINE FString GetItemDescription() const { return ItemDescription; }
	FORCEINLINE bool GetCanStack() const { return bCanStack; }
};
