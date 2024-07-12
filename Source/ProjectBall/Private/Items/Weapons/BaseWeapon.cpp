// © 2024 Pulse Core Interactive. All rights reserved.


#include "Items/Weapons/BaseWeapon.h"

#include "Characters/PlayerCharacter.h"
#include "Utilities/Constants/StringLiterals.h"
#include "Utilities/Enums/Items/EItemState.h"
#include "Components/SphereComponent.h"
#include "Components/Stats/AttributesModifier.h"
#include "Components/Stats/Character/Player/PlayerCharacterStatsComponent.h"
#include "Components/Stats/Item/Weapon/WeaponStatsComponent.h"
#include "Items/Ammo/FMagazine.h"
#include "Utilities/Enums/Items/EItemType.h"
#include "Utilities/Enums/Items/Weapons/EWeaponState.h"
#include "Utilities/Enums/Items/Weapons/EWeaponType.h"

ABaseWeapon::ABaseWeapon() :
WeaponType(EWeaponType::EWT_UNKNOWN)
, WeaponState(EWeaponState::EWS_NOT_PICKED_UP)
, WeaponSheathingState(EWeaponSheathingState::EWSS_UNKOWN)
, DamageMin(0.f)
, DamageMax(0.f)
{
	ItemType = EItemType::EIT_WEAPON;
	ItemState = EItemState::EIS_UNNEQUIPPED;

	if (ItemStatsComponent != nullptr)
	{
		ItemStatsComponent->DestroyComponent();
	}
	
	ItemStatsComponent = CreateDefaultSubobject<UWeaponStatsComponent>(TEXT("Weapon stats component"));
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseWeapon::Sheathe(const TObjectPtr<USceneComponent>& InParent) const
{
	DetachMeshFromSocket();
	AttachMeshToSocket(InParent, Constants::StringLiterals::Sockets::BACK_SOCKET);
}

void ABaseWeapon::Unsheathe(const TObjectPtr<USceneComponent>& InParent) const
{
	DetachMeshFromSocket();
	AttachMeshToSocket(InParent, Constants::StringLiterals::Sockets::HAND_SOCKET);
}

void ABaseWeapon::PickupItem(const TObjectPtr<USceneComponent>& InParent, const TObjectPtr<AActor>& NewOwner,
	const TObjectPtr<APawn> NewInstigator)
{
	/**
	 * TODO spl:
	 * At the moment, when we equip a weapon, we directly attach it to the hand socket, as in the weapon is unsheathed.
	 * Moving forward, I'd like for this behavior to be that when a player picks-up an item, it's set directly in his inventory.
	 * Inventory not yet implemented, will implement soon™.
	 * Might be better to move the logic of adding to inventory in Item class, needs investigation.
	 */
	Super::PickupItem(InParent, NewOwner, NewInstigator);

	if (CurrentOwner)
	{
		if (const TObjectPtr<APlayerCharacter>& PlayerCharacter = Cast<APlayerCharacter>(CurrentOwner))
		{
			ApplyItemStats(PlayerCharacter->GetPlayerCharacterStats()->GetCoreAttributes());
		}
	}

	AttachMeshToSocket(InParent, Constants::StringLiterals::Sockets::HAND_SOCKET);
	ItemState = EItemState::EIS_EQUIPPED; // setting this to stop bouncing && floating animations;
	WeaponState = EWeaponState::EWS_IN_PLAYERS_POSSESSION;

	DisableSphereCollision();
}

void ABaseWeapon::UseWeapon()
{
}

bool ABaseWeapon::CanUseWeapon() const
{
	return false;
}

void ABaseWeapon::DetachMeshFromSocket() const
{
	const FDetachmentTransformRules DetachmentTransformRules = FDetachmentTransformRules(EDetachmentRule::KeepWorld, false);
	ItemMesh->DetachFromComponent(DetachmentTransformRules);
}

void ABaseWeapon::AttachMeshToSocket(const TObjectPtr<USceneComponent>& InParent, const FName& InSocketName) const
{
	const FAttachmentTransformRules& AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
	ItemMesh->AttachToComponent(InParent, AttachmentTransformRules, InSocketName);
}

void ABaseWeapon::DisableSphereCollision()
{
	if (SphereComponent)
	{
		SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}
