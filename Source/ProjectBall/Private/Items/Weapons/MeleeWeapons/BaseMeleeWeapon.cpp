// © 2024 Pulse Core Interactive. All rights reserved.


#include "Items/Weapons/MeleeWeapons/BaseMeleeWeapon.h"

#include "Components/BoxComponent.h"
#include "Interfaces/HitInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Utilities/Constants/StringLiterals.h"
#include "Utilities/Enums/Items/Weapons/EWeaponType.h"

ABaseMeleeWeapon::ABaseMeleeWeapon() :
BoxTraceExtent(FVector(5.f))
, bShowDebugBox(false)
, WeaponBoxComponent(CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponBox")))
, BoxTraceStart(CreateDefaultSubobject<USceneComponent>("BoxTraceStart"))
, BoxTraceEnd(CreateDefaultSubobject<USceneComponent>("BoxTraceEnd"))
{
	PrimaryActorTick.bCanEverTick = true;
	WeaponType = EWeaponType::EWT_MELEE;
	
	WeaponBoxComponent->SetupAttachment(GetRootComponent());
	WeaponBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponBoxComponent->SetCollisionObjectType(ECC_WorldDynamic);
	WeaponBoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	WeaponBoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	
	// Critical for generating directional reacts from attacks.
	// Critical for root motion and directional hit react!!!
	WeaponBoxComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	WeaponBoxComponent->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	
	BoxTraceStart->SetupAttachment(GetRootComponent());
	BoxTraceEnd->SetupAttachment(GetRootComponent());
}

void ABaseMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();
	WeaponBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseMeleeWeapon::OnBoxOverlap);
}

void ABaseMeleeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseMeleeWeapon::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	InflictDamage(OtherActor);
}

void ABaseMeleeWeapon::InflictDamage(const TObjectPtr<AActor>& OtherActor)
{
	if (ActorIsSameType(OtherActor))
	{
		return;
	}

	FHitResult BoxHit;
	BoxTrace(BoxHit);

	if (BoxHit.GetActor())
	{
		if (ActorIsSameType(BoxHit.GetActor()))
		{
			return;
		}
		
		UGameplayStatics::ApplyDamage(
			BoxHit.GetActor(),
			FMath::RandRange(DamageMin, DamageMax),
			GetInstigator()->GetController(),
			this,
			UDamageType::StaticClass()
			);
		
		ExecuteGetHit(BoxHit, OtherActor);
	}
}

void ABaseMeleeWeapon::BoxTrace(FHitResult& BoxHit)
{
	const FVector& Start = BoxTraceStart->GetComponentLocation();
	const FVector& End = BoxTraceEnd->GetComponentLocation();
	
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.AddUnique(GetOwner());

	for (const auto& Actor : IgnoreActors)
	{
		ActorsToIgnore.AddUnique(Actor);
	}

	UKismetSystemLibrary::BoxTraceSingle(
		this,
		Start,
		End,
		BoxTraceExtent,
		BoxTraceStart->GetComponentRotation(),
		TraceTypeQuery1,
		false,
		ActorsToIgnore,
		bShowDebugBox ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
		BoxHit,
		true
		);
	
	if (!BoxHit.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("BoxHit GetActor was nullptr"));
		return;
	}

	IgnoreActors.AddUnique(BoxHit.GetActor());
}

void ABaseMeleeWeapon::ExecuteGetHit(const FHitResult& BoxHit, const TObjectPtr<AActor>& OtherActor)
{
	if (const TObjectPtr<AActor> HitActor = BoxHit.GetActor())
	{
		if (HitActor->GetClass()->ImplementsInterface(UHitInterface::StaticClass()))
		{
			Cast<IHitInterface>(HitActor)->GetHit(BoxHit.ImpactPoint, GetOwner());
		}
	}
}

bool ABaseMeleeWeapon::ActorIsSameType(const TObjectPtr<AActor>& OtherActor) const
{
	return GetOwner()->ActorHasTag(Constants::StringLiterals::Tags::TAG_ENEMY_CHARACTER)
		&& OtherActor->ActorHasTag(Constants::StringLiterals::Tags::TAG_ENEMY_CHARACTER);
}

void ABaseMeleeWeapon::SetEnableWeaponBoxCollision(ECollisionEnabled::Type value)
{
	if (WeaponBoxComponent)
	{
		WeaponBoxComponent->SetCollisionEnabled(value);
	}
}

void ABaseMeleeWeapon::EmptyIgnoreActors()
{
	IgnoreActors.Empty();
}
