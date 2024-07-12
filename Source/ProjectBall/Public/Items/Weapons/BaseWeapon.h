// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Stats/Item/Weapon/WeaponStatsComponent.h"
#include "Items/Item.h"
#include "Utilities/Enums/Items/Weapons/EWeaponSheathingState.h"
#include "BaseWeapon.generated.h"

class UWeaponStatsComponent;
class ABaseAmmo;
class UBoxComponent;
enum class EWeaponState : uint8;
enum class EWeaponType : uint8;

/**
 * 
 */
UCLASS()
class PROJECTBALL_API ABaseWeapon : public AItem
{
	GENERATED_BODY()

public:
	ABaseWeapon();

	/** AActor */
	virtual void Tick(float DeltaTime) override;
	/** /AActor */

	void Sheathe(const TObjectPtr<USceneComponent>& InParent) const; // leave it here
	void Unsheathe(const TObjectPtr<USceneComponent>& InParent) const; // leave it here

	/**
	 * TODO spl:
	 * At the moment, when we equip a weapon, we directly attach it to the hand socket, as in the weapon is unsheathed.
	 * Moving forward, I'd like for this behavior to be that when a player picks-up an item, it's set directly in his inventory.
	 * Inventory not yet implemented, will implement soon™.
	 * Might be better to move the logic of adding to inventory in Item class, needs investigation.
	 */
	virtual void PickupItem(const TObjectPtr<USceneComponent>& InParent, 
		const TObjectPtr<AActor>& NewOwner,
		const TObjectPtr<APawn> NewInstigator) override;
	
	virtual void UseWeapon();
	virtual bool CanUseWeapon() const;

protected:
	/** AActor */
	virtual void BeginPlay() override;
	/** /AActor */

	UPROPERTY(VisibleAnywhere)
	EWeaponType WeaponType; // This will be set in child classes of this class

	UPROPERTY(VisibleAnywhere)
	EWeaponState WeaponState; // This will be set in child classes of this class.

	UPROPERTY(VisibleAnywhere)
	EWeaponSheathingState WeaponSheathingState; // Consider moving this to ABaseWeapon
	
	UPROPERTY(EditAnywhere, Category = Damage)
	float DamageMin;
	UPROPERTY(EditAnywhere, Category = Damage)
	float DamageMax;
	
	UWeaponStatsComponent* GetWeaponStatsComponent() { return StaticCast<UWeaponStatsComponent*>(ItemStatsComponent.Get()); }
private:
	void DetachMeshFromSocket() const; // leave it here
	void AttachMeshToSocket(const TObjectPtr<USceneComponent>& InParent, const FName& InSocketName) const;
	void DisableSphereCollision(); // leave it here

public:
	FORCEINLINE EWeaponState GetWeaponState() const { return WeaponState; }
	FORCEINLINE EWeaponType GetWeaponType() const { return WeaponType; }
	FORCEINLINE EWeaponSheathingState GetWeaponSheathingState() const { return WeaponSheathingState; }
	FORCEINLINE void SetWeaponSheathingState(EWeaponSheathingState NewState) { WeaponSheathingState = NewState; }
};

