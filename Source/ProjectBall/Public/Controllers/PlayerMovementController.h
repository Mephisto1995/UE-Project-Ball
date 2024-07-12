// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerMovementController.generated.h"

enum class EActionState : uint8;
enum class EPlayerCombatState : uint8;
class APlayerCharacter;
class UInputAction;
struct FInputActionValue;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class PROJECTBALL_API APlayerMovementController : public APlayerController
{
	GENERATED_BODY()

public:
	APlayerMovementController();
	
protected:
	/** AActor */
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;
	/** /AActor */

	/** Callback functions */
	void MoveStarted(const FInputActionValue& Value);
	void Attack();
	void SheatheUnsheatheWeapon();
	void JumpStarted();
	void AimStarted();
	void AimFinished();
	void PickUpWeapon();
	/** /Callback functions */
	
private:
	/** Input */
	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputMappingContext> PlayerContext;
	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputAction> AttackAction;
	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputAction> SheatheUnsheatheWeaponAction;
	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputAction> JumpAction;
	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputAction> AimAction;
	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputAction> PickUpWeaponAction;
	/** /Input */
	
	/** APlayerCharacter */
	UPROPERTY(VisibleDefaultsOnly, Category = PlayerData)
	TObjectPtr<APlayerCharacter> ControlledPlayer;
	/** /APlayerCharacter */

	void RotateCharacterToCursor() const;
	void SendAction(EActionState NewAction) const;
};
