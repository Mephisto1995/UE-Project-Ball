#pragma once

/** Keep in sync with CoreAttributesComponent!!! */
UENUM(Blueprintable)
enum class EAttributeToModify : uint8
{
	UNKOWN,

	STRENGTH UMETA(DisplayName = "Strength"),
	STAMINA UMETA(DisplayName = "Stamina"),
	AGILITY UMETA(DisplayName = "Agility"),
	INTELLECT UMETA(DisplayName = "Intellect"),
	SPIRIT UMETA(DisplayName = "Spirit"),
	ARMOR UMETA(DisplayName = "Armor"),
	MELEE_ATTACK_POWER UMETA(DisplayName = "Melee Attack Power"),
	RANGED_ATTACK_POWER UMETA(DisplayName = "Ranged Attack Power"),
	CRIT_CHANCE UMETA(DisplayName = "Critical Chance"),
	ARMOR_PENETRATION UMETA(DisplayName = "Armor Penetration"),

	NUM_ATTRIBUTES,
};
