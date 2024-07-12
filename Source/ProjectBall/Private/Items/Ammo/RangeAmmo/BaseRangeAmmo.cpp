// © 2024 Pulse Core Interactive. All rights reserved.


#include "Items/Ammo/RangeAmmo/BaseRangeAmmo.h"

#include "Components/SphereComponent.h"
#include "Interfaces/HitInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Utilities/Enums/Items/EItemType.h"
#include "Utilities/Enums/Items/Ammo/EAmmoType.h"

ABaseRangeAmmo::ABaseRangeAmmo() :
bShowDebugBox(false)
, SphereTraceStart(CreateDefaultSubobject<USceneComponent>(TEXT("SphereTraceStart")))
, SphereTraceEnd(CreateDefaultSubobject<USceneComponent>(TEXT("SphereTraceEnd")))
{
	ItemType = EItemType::EIT_AMMO;
	DamageMin = 0.f;
	DamageMax = 0.f;

	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionObjectType(ECC_WorldDynamic);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	
	// Critical for root motion and directional hit react!!!
	SphereComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block); 

	SphereTraceStart->SetupAttachment(GetRootComponent());
	SphereTraceEnd->SetupAttachment(GetRootComponent());
}

void ABaseRangeAmmo::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseRangeAmmo::OnSphereOverlap);
}

void ABaseRangeAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseRangeAmmo::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	InflictDamage(OtherActor);
	Destroy();
}

void ABaseRangeAmmo::InflictDamage(const TObjectPtr<AActor>& OtherActor)
{
	FHitResult SphereHit;
	SphereTrace(SphereHit);

	if (SphereHit.GetActor())
	{
		if (!GetInstigator())
		{
			return;
		}
		
		UGameplayStatics::ApplyDamage(
			SphereHit.GetActor(),
			FMath::RandRange(DamageMin, DamageMax),
			GetInstigator()->GetController(),
			this,
			UDamageType::StaticClass()
			);
		
		ExecuteGetHit(SphereHit, OtherActor);
	}
}

void ABaseRangeAmmo::SphereTrace(FHitResult& SphereHit) const
{
	const FVector& Start = SphereTraceStart->GetComponentLocation();
	const FVector& End = SphereTraceEnd->GetComponentLocation();

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.AddUnique(GetOwner());
	
	UKismetSystemLibrary::SphereTraceSingle(
		this,
		Start,
		End,
		500.f,
		TraceTypeQuery1,
		false,
		ActorsToIgnore,
		bShowDebugBox ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
		SphereHit,
		true
		);
}

void ABaseRangeAmmo::ExecuteGetHit(const FHitResult& BoxHit, const TObjectPtr<AActor>& OtherActor) const
{
	if (const TObjectPtr<AActor> HitActor = BoxHit.GetActor())
	{
		if (HitActor->GetClass()->ImplementsInterface(UHitInterface::StaticClass()))
		{
			Cast<IHitInterface>(HitActor)->GetHit(BoxHit.ImpactPoint, GetOwner());
		}
	}
}
