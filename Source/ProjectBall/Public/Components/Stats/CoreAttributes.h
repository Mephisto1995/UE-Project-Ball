// © 2024 Pulse Core Interactive. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CoreAttributes.generated.h"


UCLASS( DefaultToInstanced, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTBALL_API UCoreAttributes : public UObject
{
	GENERATED_BODY()

public:	
	UCoreAttributes();
	
	void ModifyStrength(float NewValue);
	void ModifyStamina(float NewValue);
	void ModifyAgility(float NewValue);
	void ModifyIntellect(float NewValue);
	void ModifySpirit(float NewValue);
	void ModifyArmor(float NewValue);
	void ModifyMeleeAttackPower(float NewValue);
	void ModifyRangeAttackPower(float NewValue);
	void ModifyCritChance(float NewValue);
	void ModifyArmorPenetration(float NewValue);

	void Debug_ModifyAll(float NewValue);

protected:
	
private:
	/** Increases melee attack power. */
	UPROPERTY(EditAnywhere, Category = "Core Attribute Components | Core Stats")
	float Strength;

	/** Increases Health. 1 Stamina point = 10 HP. */
	UPROPERTY(EditAnywhere, Category = "Core Attribute Components | Core Stats")
	float Stamina;

	/** Increases Ranged Attack Power and Crit Chance. Not yet implemented. */
	UPROPERTY(EditAnywhere, Category = "Core Attribute Components | Core Stats")
	float Agility;

	/** Increases Mana. 1 Intellect = 15 MP. */
	UPROPERTY(EditAnywhere, Category = "Core Attribute Components | Core Stats")
	float Intellect;

	/** Increases HP and Mana regeneration. Not yet implemented. */
	UPROPERTY(EditAnywhere, Category = "Core Attribute Components | Core Stats")
	float Spirit;

	/** Reduces physical damage by a percentage. Not yet implemented. */
	UPROPERTY(EditDefaultsOnly, Category = "Core Attribute Components | Core Stats")
	float Armor;

	/** Impact of your melee attacks. */
	UPROPERTY(EditAnywhere, Category = "Core Attribute Components | Core Stats")
	float MeleeAttackPower;

	/** Impact of your ranged attacks. */
	UPROPERTY(EditAnywhere, Category = "Core Attribute Components | Core Stats")
	float RangeAttackPower;

	/** Values are in percent, so if you input 50, it'll be 50%. */
	/** Crit damage does double damage. */
	UPROPERTY(EditAnywhere, Category = "Core Attribute Components | Core Stats")
	float CritChance;

	/** Values are in percent, so if you input 50, it'll be 50%. */
	/** Armor Penetration ignores a percentage of the target's armor. */
	UPROPERTY(EditAnywhere, Category = "Core Attribute Components | Core Stats")
	float ArmorPenetration;

public:
	FORCEINLINE float GetStrength() const { return Strength; }
	FORCEINLINE float GetStamina() const { return Stamina; }
	FORCEINLINE float GetAgility() const { return Agility; }
	FORCEINLINE float GetIntellect() const { return Intellect; }
	FORCEINLINE float GetSpirit() const { return Spirit; }
	FORCEINLINE float GetArmor() const { return Armor; }
	FORCEINLINE float GetMAP() const { return MeleeAttackPower; }
	FORCEINLINE float GetRAP() const { return RangeAttackPower; }
	FORCEINLINE float GetCritChance() const { return CritChance; }
	FORCEINLINE float GetArP() const { return ArmorPenetration; }
};