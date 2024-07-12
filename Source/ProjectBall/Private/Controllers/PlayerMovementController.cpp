// © 2024 Pulse Core Interactive. All rights reserved.


#include "Controllers/PlayerMovementController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Characters/PlayerCharacter.h"
#include "Utilities/Constants/CameraOffsets.h"
#include "Utilities/Enums/PlayerCharacter/EActionState.h"

APlayerMovementController::APlayerMovementController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerMovementController::BeginPlay()
{
	Super::BeginPlay();
	check(PlayerContext);
	
	const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(PlayerContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

	ControlledPlayer = CastChecked<APlayerCharacter>(GetPawn());
	SendAction(EActionState::ACTION_IDLE_UNARMED);
}

void APlayerMovementController::SetupInputComponent()
{
	Super::SetupInputComponent();

	const TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerMovementController::MoveStarted);
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &APlayerMovementController::Attack);
	EnhancedInputComponent->BindAction(SheatheUnsheatheWeaponAction, ETriggerEvent::Triggered, this, &APlayerMovementController::SheatheUnsheatheWeapon);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerMovementController::JumpStarted);
	EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Triggered, this, &APlayerMovementController::AimStarted);
	EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &APlayerMovementController::AimFinished);
	EnhancedInputComponent->BindAction(PickUpWeaponAction, ETriggerEvent::Triggered, this, &APlayerMovementController::PickUpWeapon);
}

void APlayerMovementController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotateCharacterToCursor();
}

void APlayerMovementController::MoveStarted(const FInputActionValue& Value)
{
	if (!ControlledPlayer)
	{
		return;
	}

	if (!ControlledPlayer->CanMove())
	{
		return;
	}
	
	const FVector2D& MovementVector = Value.Get<FVector2D>();
	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
	const FVector& ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector& RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	ControlledPlayer->AddMovementInput(ForwardDirection, MovementVector.X); // Forward direction
	ControlledPlayer->AddMovementInput(RightDirection, MovementVector.Y); // Right direction
}

void APlayerMovementController::Attack()
{
	SendAction(EActionState::ACTION_ATTACKING);
}

void APlayerMovementController::SheatheUnsheatheWeapon()
{
	SendAction(EActionState::ACTION_SHEATHING_UNSHEATHING);
}

void APlayerMovementController::JumpStarted()
{
	SendAction(EActionState::ACTION_JUMPING);
}

void APlayerMovementController::AimStarted()
{
	UE_LOG(LogTemp, Warning, TEXT("AimStarted"));
	
	if (!ControlledPlayer)
	{
		return;
	}

	if (ControlledPlayer->IsMoving())
	{
		SendAction(EActionState::ACTION_AIMING_AND_RUNNING);
		return;
	}
	
	SendAction(EActionState::ACTION_AIMING);
}

void APlayerMovementController::AimFinished()
{
	SendAction(EActionState::ACTION_IDLE_RANGED_WEAPON);
}

void APlayerMovementController::PickUpWeapon()
{
	SendAction(EActionState::ACTION_PICKING_UP_WEAPON);
}

void APlayerMovementController::RotateCharacterToCursor() const
{
	check(ControlledPlayer);
	
	FVector WorldLocation, WorldDirection;
	if (DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	{
		// Trace from the camera to find the world position under the cursor
		FVector StartLocation = WorldLocation;
		FVector EndLocation = WorldLocation + WorldDirection * Constants::CameraOffsets::CURSOR_TRACE_EXTENT; // Use a sufficiently large value
		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility);

		if (HitResult.bBlockingHit)
		{
			FVector TargetLocation = HitResult.Location;
			FRotator TargetRotation = FRotationMatrix::MakeFromX(TargetLocation - ControlledPlayer->GetActorLocation()).Rotator();
			ControlledPlayer->SetActorRotation(FRotator(0.0f, TargetRotation.Yaw, 0.0f));
		}
	}
}

void APlayerMovementController::SendAction(EActionState NewAction) const
{
	if (!ControlledPlayer)
	{
		return;
	}

	ControlledPlayer->ExecuteAction(NewAction);
}
