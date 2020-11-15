#include"UnitDefs.h"

std::string SkillToString(UnitSkillsEnum skill) {
	switch (skill) {
	case UnitSkillsEnum::UNIT_SKILL_HEAVY_ARMOR:
		return "Heavy Armor";
		break;
	case UnitSkillsEnum::UNIT_SKILL_MEDIUM_ARMOR:
		return "Medium Armor";

		break;
	case UnitSkillsEnum::UNIT_SKILL_LIGHT_ARMOR:
		return "Light Armor";

		break;
	case UnitSkillsEnum::UNIT_SKILL_SPEAR:
		return "Spear";

		break;
	case UnitSkillsEnum::UNIT_SKILL_AXE:
		return "Axe";

		break;
	case UnitSkillsEnum::UNIT_SKILL_BLUNT_WEAPON:
		return "Blunt Weapon";

		break;
	case UnitSkillsEnum::UNIT_SKILL_LONG_BLADE:
		return "Long Blade";

		break;
	case UnitSkillsEnum::UNIT_SKILL_SHORT_BLADE:
		return "Short Blade";

		break;
	case UnitSkillsEnum::UNIT_SKILL_BLOCK:
		return "Block";

		break;
	case UnitSkillsEnum::UNIT_SKILL_MARKSMAN:
		return "Marksman";

		break;
	case UnitSkillsEnum::UNIT_SKILL_ACROBATICS:
		return "Acrobatics";

		break;
	case UnitSkillsEnum::UNIT_SKILL_ATHLETICS:
		return "Athletics";

		break;
	case UnitSkillsEnum::UNIT_SKILL_SNEAK:
		return "Sneak";

		break;
	case UnitSkillsEnum::UNIT_SKILL_UNARMORED:
		return "Unarmored";

		break;
	case UnitSkillsEnum::UNIT_SKILL_ILLUSION:
		return "Illusion";

		break;
	case UnitSkillsEnum::UNIT_SKILL_MERCANTILE:
		return "Mercantile";

		break;
	case UnitSkillsEnum::UNIT_SKILL_SPEECHCRAFT:
		return "Speechcraft";

		break;
	case UnitSkillsEnum::UNIT_SKILL_ALCHEMY:
		return "Alchemy";

		break;
	case UnitSkillsEnum::UNIT_SKILL_CONJURATION:
		return "Conjuration";

		break;
	case UnitSkillsEnum::UNIT_SKILL_ENCHANT:
		return "Enchant";

		break;
	case UnitSkillsEnum::UNIT_SKILL_ALTERATION:
		return "Altertion";

		break;
	case UnitSkillsEnum::UNIT_SKILL_DESTRUCTION:
		return "Destruction";

		break;
	case UnitSkillsEnum::UNIT_SKILL_MYSTICISM:
		return "Mysticism";

		break;
	case UnitSkillsEnum::UNIT_SKILL_RESTORATION:
		return "Restoration";

		break;
	}
}


std::string AttributeToString(UnitAttributesEnum attr) {
	switch (attr) {
	case UnitAttributesEnum::UNIT_ATTRIBUTE_STRENGTH:
		return "Strength";

		break;
	case UnitAttributesEnum::UNIT_ATTRIBUTE_INTELLIGENCE:
		return "Intelligence";

		break;
	case UnitAttributesEnum::UNIT_ATTRIBUTE_WILLPOWER:
		return "Willpower";

		break;
	case UnitAttributesEnum::UNIT_ATTRIBUTE_AGILITY:
		return "Agility";

		break;
	case UnitAttributesEnum::UNIT_ATTRIBUTE_SPEED:
		return "Speed";

		break;
	case UnitAttributesEnum::UNIT_ATTRIBUTE_ENDURANCE:
		return "Endurance";

		break;
	case UnitAttributesEnum::UNIT_ATTRIBUTE_PERSONALITY:
		return "Personality";

		break;

	}
}


UnitSkillsEnum SkillStringtoEnum(std::string skill) {

	if (COMPARE_STRINGS(skill, "Heavy Armor") == 0) {
		return UnitSkillsEnum::UNIT_SKILL_HEAVY_ARMOR;
	}
	else if (COMPARE_STRINGS(skill, "Medium Armor") == 0) {
		return UnitSkillsEnum::UNIT_SKILL_MEDIUM_ARMOR;

	}
	else if (COMPARE_STRINGS(skill, "Light Armor") == 0) {
		return UnitSkillsEnum::UNIT_SKILL_LIGHT_ARMOR;

	}
	else if (COMPARE_STRINGS(skill, "Spear") == 0) {
		return UnitSkillsEnum::UNIT_SKILL_SPEAR;

	}
	else if (COMPARE_STRINGS(skill, "Axe") == 0) {
		return UnitSkillsEnum::UNIT_SKILL_AXE;

	}
	else if (COMPARE_STRINGS(skill, "Blunt Weapon") == 0) {
		return UnitSkillsEnum::UNIT_SKILL_BLUNT_WEAPON;

	}
	else if (COMPARE_STRINGS(skill, "Long Blade") == 0) {
		return UnitSkillsEnum::UNIT_SKILL_LONG_BLADE;

	}
	else if (COMPARE_STRINGS(skill, "Short Blade") == 0) {
		return UnitSkillsEnum::UNIT_SKILL_SHORT_BLADE;

	}
	else if (COMPARE_STRINGS(skill, "Block") == 0) {
		return UnitSkillsEnum::UNIT_SKILL_BLOCK;

	}
	else if (COMPARE_STRINGS(skill, "Marksman") == 0) {
		return UnitSkillsEnum::UNIT_SKILL_MARKSMAN;

	}
	else if (COMPARE_STRINGS(skill, "Acrobatics") == 0) {
		return UnitSkillsEnum::UNIT_SKILL_ACROBATICS;

	}
	else if (COMPARE_STRINGS(skill, "Athletics") == 0) {
		return UnitSkillsEnum::UNIT_SKILL_ATHLETICS;

	}
	else if (COMPARE_STRINGS(skill, "Sneak") == 0) {
		return UnitSkillsEnum::UNIT_SKILL_SNEAK;

	}
	else if (COMPARE_STRINGS(skill, "Unarmored") == 0) {
		return UnitSkillsEnum::UNIT_SKILL_UNARMORED;

	}
	else if (COMPARE_STRINGS(skill, "Illusion") == 0) {
		return UnitSkillsEnum::UNIT_SKILL_ILLUSION;

	}
	else if (COMPARE_STRINGS(skill, "Mercantile") == 0) {
		return UnitSkillsEnum::UNIT_SKILL_MERCANTILE;

	}
	else if (COMPARE_STRINGS(skill, "Speechcraft") == 0) {
		return UnitSkillsEnum::UNIT_SKILL_SPEECHCRAFT;

	}
	else if (COMPARE_STRINGS(skill, "Alchemy") == 0) {
		return UnitSkillsEnum::UNIT_SKILL_ALCHEMY;

	}
	else if (COMPARE_STRINGS(skill, "Conjuration") == 0) {
		return UnitSkillsEnum::UNIT_SKILL_CONJURATION;

	}
	else if (COMPARE_STRINGS(skill, "Enchant") == 0) {
		return UnitSkillsEnum::UNIT_SKILL_ENCHANT;

	}
	else if (COMPARE_STRINGS(skill, "Alteration") == 0) {
		return UnitSkillsEnum::UNIT_SKILL_ALTERATION;

	}
	else if (COMPARE_STRINGS(skill, "Destruction") == 0) {
		return UnitSkillsEnum::UNIT_SKILL_DESTRUCTION;

	}
	else if (COMPARE_STRINGS(skill, "Mysticism") == 0) {
		return UnitSkillsEnum::UNIT_SKILL_MYSTICISM;

	}
	else if (COMPARE_STRINGS(skill, "Restoration") == 0) {
		return UnitSkillsEnum::UNIT_SKILL_RESTORATION;
	}
	else {
		return UnitSkillsEnum::UNIT_SKILL_INVALID;
	}

}


UnitAttributesEnum AttributeStringtoEnum(std::string attr) {
	if (COMPARE_STRINGS(attr, "Strength") == 0) {
		return UnitAttributesEnum::UNIT_ATTRIBUTE_STRENGTH;
	}
	else if (COMPARE_STRINGS(attr, "Intelligence") == 0) {
		return UnitAttributesEnum::UNIT_ATTRIBUTE_INTELLIGENCE;

	}
	else if (COMPARE_STRINGS(attr, "Willpower") == 0) {
		return UnitAttributesEnum::UNIT_ATTRIBUTE_WILLPOWER;

	}
	else if (COMPARE_STRINGS(attr, "Agility") == 0) {
		return UnitAttributesEnum::UNIT_ATTRIBUTE_AGILITY;

	}
	else if (COMPARE_STRINGS(attr, "Speed") == 0) {
		return UnitAttributesEnum::UNIT_ATTRIBUTE_SPEED;

	}
	else if (COMPARE_STRINGS(attr, "Endurance") == 0) {
		return UnitAttributesEnum::UNIT_ATTRIBUTE_ENDURANCE;

	}
	else if (COMPARE_STRINGS(attr, "Personality") == 0) {
		return UnitAttributesEnum::UNIT_ATTRIBUTE_PERSONALITY;

	}
	else {
		return UnitAttributesEnum::UNIT_ATTRIBUTE_INVALID;
	}
}