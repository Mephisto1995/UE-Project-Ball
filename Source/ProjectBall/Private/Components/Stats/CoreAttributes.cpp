// © 2024 Pulse Core Interactive. All rights reserved.


#include "Components/Stats/CoreAttributes.h"

#include "Utilities/MacroFunctions/PCIMacros.h"

UCoreAttributes::UCoreAttributes():
Strength(0)
, Stamina(0)
, Agility(0)
, Intellect(0)
, Spirit(0)
, Armor(0)
, MeleeAttackPower(0)
, RangeAttackPower(0)
, CritChance(0.f)
, ArmorPenetration(0.f)
{
}

void UCoreAttributes::ModifyStrength(float NewValue)
{
    PCI_Log(Warning, "UCoreAttributesComponent::ModifyStrength() Old value: %d, New value: %d", Strength, NewValue);
	Strength += NewValue;
}

void UCoreAttributes::ModifyStamina(float NewValue)
{
	PCI_Log(Warning, "UCoreAttributesComponent::ModifyStamina() Old value: %d, New value: %d", Stamina, NewValue);
	Stamina += NewValue;
}

void UCoreAttributes::ModifyAgility(float NewValue)
{
	PCI_Log(Warning, "UCoreAttributesComponent::ModifyAgility() Old value: %d, New value: %d", Agility, NewValue);
	Agility += NewValue;
}

void UCoreAttributes::ModifyIntellect(float NewValue)
{
	PCI_Log(Warning, "UCoreAttributesComponent::ModifyIntellect() Old value: %d, New value: %d", Intellect, NewValue);
	Intellect += NewValue;
}

void UCoreAttributes::ModifySpirit(float NewValue)
{
	PCI_Log(Warning, "UCoreAttributesComponent::ModifySpirit() Old value: %d, New value: %d", Spirit, NewValue);
	Spirit += NewValue;
}

void UCoreAttributes::ModifyArmor(float NewValue)
{
	PCI_Log(Warning, "UCoreAttributesComponent::ModifyArmor() Old value: %d, New value: %d", Armor, NewValue);
	Armor += NewValue;
}

void UCoreAttributes::ModifyMeleeAttackPower(float NewValue)
{
	PCI_Log(Warning, "UCoreAttributesComponent::ModifyMAP() Old value: %d, New value: %d", MeleeAttackPower, NewValue);
	MeleeAttackPower += NewValue;
}

void UCoreAttributes::ModifyRangeAttackPower(float NewValue)
{
	PCI_Log(Warning, "UCoreAttributesComponent::ModifyRAP() Old value: %d, New value: %d", RangeAttackPower, NewValue);
	RangeAttackPower += NewValue;
}

void UCoreAttributes::ModifyCritChance(float NewValue)
{
	PCI_Log(Warning, "UCoreAttributesComponent::ModifyCritChance() Old value: %d, New value: %d", CritChance, NewValue);
	CritChance += NewValue;
}

void UCoreAttributes::ModifyArmorPenetration(float NewValue)
{
	PCI_Log(Warning, "UCoreAttributesComponent::ModifyArP() Old value: %d, New value: %d", ArmorPenetration, NewValue);
	ArmorPenetration += NewValue;
}

void UCoreAttributes::Debug_ModifyAll(float NewValue)
{
	ModifyStrength(NewValue);
	ModifyStamina(NewValue);
	ModifyAgility(NewValue);
	ModifyIntellect(NewValue);
	ModifySpirit(NewValue);
	ModifyArmor(NewValue);
	ModifyMeleeAttackPower(NewValue);
	ModifyRangeAttackPower(NewValue);
	ModifyCritChance(NewValue);
	ModifyArmorPenetration(NewValue);
}
