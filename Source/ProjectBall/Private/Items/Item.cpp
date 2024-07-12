// © 2024 Pulse Core Interactive. All rights reserved.


#include "Items/Item.h"

#include "Characters/PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/Stats/AttributesModifier.h"
#include "Components/Stats/Item/ItemStatsComponent.h"
#include "Utilities/Enums/Items/EItemState.h"
#include "Utilities/Enums/Items/EItemType.h"

AItem::AItem() :
ItemMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent")))
, SphereComponent(CreateDefaultSubobject<USphereComponent>(TEXT("SphereOverlapComponent")))
, ItemState(EItemState::EIS_UNKOWN)
, ItemType(EItemType::EIT_ITEM)
, ItemStatsComponent(CreateDefaultSubobject<UItemStatsComponent>(TEXT("ItemStatsComponent")))
, BaseZ(0.0f)
, FloatingHeight(20.f)
, FloatingSpeed(2.f)
, RotationSpeed(45.f)
{
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(ItemMesh);
	ItemMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	SphereComponent->SetupAttachment(GetRootComponent());
	SphereComponent->SetVisibility(true);
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	BaseZ = GetActorLocation().Z;

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSphereEndOverlap);
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CanAnimate())
	{
		FloatItem();
		RotateItem(DeltaTime);
	}
}

void AItem::PickupItem(const TObjectPtr<USceneComponent>& Parent, const TObjectPtr<AActor>& NewOwner,
	const TObjectPtr<APawn> NewInstigator)
{
	CurrentParent = Parent;
	CurrentOwner = NewOwner;
	CurrentInstigator = NewInstigator;

	SetOwner(CurrentOwner);
	SetInstigator(CurrentInstigator);
}

void AItem::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (const TObjectPtr<APlayerCharacter> PlayerCharacter = Cast<APlayerCharacter>(OtherActor))
	{
		PlayerCharacter->SetOverlappingItem(this);
	}
}

void AItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (const TObjectPtr<APlayerCharacter> PlayerCharacter = Cast<APlayerCharacter>(OtherActor))
	{
		PlayerCharacter->SetOverlappingItem(nullptr);
	}
}

void AItem::FloatItem()
{
	const float Time = GetWorld()->GetTimeSeconds();
	const float NewZ = BaseZ + FMath::Sin(Time * FloatingSpeed) * FloatingHeight;

	FVector NewLocation = GetActorLocation();
	NewLocation.Z = NewZ;
	SetActorLocation(NewLocation);
}

void AItem::RotateItem(float DeltaTime)
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += RotationSpeed * DeltaTime; // Increment yaw by RotationSpeed * DeltaTime
	SetActorRotation(NewRotation);
}

void AItem::ApplyItemStats(const TObjectPtr<UCoreAttributes>& CoreAttributes)
{
	if (!ItemStatsComponent)
	{
		return;
	}

	ItemStatsComponent->GetAttributeModifier()->ApplyModifications(CoreAttributes);
}

bool AItem::CanAnimate() const
{
	return ItemState != EItemState::EIS_EQUIPPED && ItemType != EItemType::EIT_AMMO;
}
