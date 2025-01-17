// © 2024 Pulse Core Interactive. All rights reserved.


#include "Components/Stats/AttributesModifier.h"

#include "Components/Stats/CoreAttributes.h"
#include "Utilities/Enums/Components/Stats/EAttributeToModify.h"

UAttributeModifier::UAttributeModifier()
{
}

void UAttributeModifier::ApplyModifications(const TObjectPtr<UCoreAttributes>& CoreAttributesComponent)
{
	if (!CoreAttributesComponent)
	{
		return;
	}

	for (const auto& Modification : AttributeModifications)
	{
		switch (Modification.AttributeToModify)
		{
		case EAttributeToModify::STRENGTH:
			CoreAttributesComponent->ModifyStrength(Modification.NewValue);
			break;
		case EAttributeToModify::STAMINA:
			CoreAttributesComponent->ModifyStamina(Modification.NewValue);
			break;
		case EAttributeToModify::AGILITY:
			CoreAttributesComponent->ModifyAgility(Modification.NewValue);
			break;
		case EAttributeToModify::INTELLECT:
			CoreAttributesComponent->ModifyIntellect(Modification.NewValue);
			break;
		case EAttributeToModify::SPIRIT:
			CoreAttributesComponent->ModifySpirit(Modification.NewValue);
			break;
		case EAttributeToModify::ARMOR:
			CoreAttributesComponent->ModifyArmor(Modification.NewValue);
			break;
		case EAttributeToModify::MELEE_ATTACK_POWER:
			CoreAttributesComponent->ModifyMeleeAttackPower(Modification.NewValue);
			break;
		case EAttributeToModify::RANGED_ATTACK_POWER:
			CoreAttributesComponent->ModifyRangeAttackPower(Modification.NewValue);
			break;
		case EAttributeToModify::CRIT_CHANCE:
			CoreAttributesComponent->ModifyCritChance(Modification.NewValue);
			break;
		case EAttributeToModify::ARMOR_PENETRATION:
			CoreAttributesComponent->ModifyArmorPenetration(Modification.NewValue);
			break;
		default:
			break;
		}
	}
}
