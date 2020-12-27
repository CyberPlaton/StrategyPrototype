#include"UnitDefs.h"




/*
// OLD

void UnitClass::_setMajorSkillsAttributes(std::string major_attr1, std::string major_attr2,
	std::string major_skill1, std::string major_skill2, std::string major_skill3) {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	int multiplier = GetMultiplierFromUnitClassTier(m_ClassTier);

	int major_value = 4 * multiplier;

	// Define Major/Minor skill-attribute set.
	attr->SetAttribute(m_AttrMap, major_attr1, major_value);
	attr->SetAttribute(m_AttrMap, major_attr2, major_value);
	skills->SetSkill(m_SkillsMap, major_skill1, major_value);
	skills->SetSkill(m_SkillsMap, major_skill2, major_value);
	skills->SetSkill(m_SkillsMap, major_skill3, major_value);
}


void UnitClass::_setMinorSkillsAttributes(std::string minor_skill1, std::string minor_skill2,
	std::string minor_skill3, std::string minor_skill4, std::string minor_skill5) {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	int multiplier = GetMultiplierFromUnitClassTier(m_ClassTier);

	int minor_value = 2 * multiplier;


	skills->SetSkill(m_SkillsMap, minor_skill1, minor_value);
	skills->SetSkill(m_SkillsMap, minor_skill2, minor_value);
	skills->SetSkill(m_SkillsMap, minor_skill3, minor_value);
	skills->SetSkill(m_SkillsMap, minor_skill4, minor_value);
	skills->SetSkill(m_SkillsMap, minor_skill5, minor_value);
}



void UnitClass::_unsetMajorSkillsAttributes(std::string major_attr1, std::string major_attr2,
	std::string major_skill1, std::string major_skill2, std::string major_skill3) {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	int multiplier = GetMultiplierFromUnitClassTier(m_ClassTier);

	int major_value = 4 * multiplier;

	// Define Major/Minor skill-attribute set.
	attr->UnsetAttribute(m_AttrMap, major_attr1, major_value);
	attr->UnsetAttribute(m_AttrMap, major_attr2, major_value);
	skills->UnsetSkill(m_SkillsMap, major_skill1, major_value);
	skills->UnsetSkill(m_SkillsMap, major_skill2, major_value);
	skills->UnsetSkill(m_SkillsMap, major_skill3, major_value);
}

void UnitClass::_unsetMinorSkillsAttributes(std::string minor_skill1, std::string minor_skill2,
	std::string minor_skill3, std::string minor_skill4, std::string minor_skill5) {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	int multiplier = GetMultiplierFromUnitClassTier(m_ClassTier);

	int minor_value = 2 * multiplier;


	skills->UnsetSkill(m_SkillsMap, minor_skill1, minor_value);
	skills->UnsetSkill(m_SkillsMap, minor_skill2, minor_value);
	skills->UnsetSkill(m_SkillsMap, minor_skill3, minor_value);
	skills->UnsetSkill(m_SkillsMap, minor_skill4, minor_value);
	skills->UnsetSkill(m_SkillsMap, minor_skill5, minor_value);
}

// Function for training skills/attributes defined as Major/Minor for this class.
void UnitClass::_trainSkills() {

}

void UnitClass::_trainAttributes() {

}




int GetMultiplierFromUnitClassTier(UnitClassTier tier) {

	switch (tier) {
	case UnitClassTier::UNIT_CLASS_TIER_0:
		return 1;
		break;
	case UnitClassTier::UNIT_CLASS_TIER_1:
		return 2;
		break;
	case UnitClassTier::UNIT_CLASS_TIER_2:
		return 3;
		break;
	case UnitClassTier::UNIT_CLASS_TIER_3:
		return 4;
		break;
	case UnitClassTier::UNIT_CLASS_TIER_4:
		return 5;
		break;
	default:
		return -1;
		break;
	}
}



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

	case UnitAttributesEnum::UNIT_ATTRIBUTE_HEALTH:
		return "Health";

		break;
	case UnitAttributesEnum::UNIT_ATTRIBUTE_MAGICKA:
		return "Magicka";

		break;
	case UnitAttributesEnum::UNIT_ATTRIBUTE_FATIGUE:
		return "Fatigue";

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
	else if (COMPARE_STRINGS(attr, "Health") == 0) {
		return UnitAttributesEnum::UNIT_ATTRIBUTE_HEALTH;

	}
	else if (COMPARE_STRINGS(attr, "Magicka") == 0) {
		return UnitAttributesEnum::UNIT_ATTRIBUTE_MAGICKA;

	}
	else if (COMPARE_STRINGS(attr, "Fatigue") == 0) {
		return UnitAttributesEnum::UNIT_ATTRIBUTE_FATIGUE;

	}
	else {
		return UnitAttributesEnum::UNIT_ATTRIBUTE_INVALID;
	}
}


void UnitClassArcher::_defineStats() {

	// Define Major/Minor skill-attribute set.

	_setMajorSkillsAttributes("Strength", "Agility",
		"Marksman", "Light Armor", "Athletics");

	_setMinorSkillsAttributes("Unarmored", "Medium Armor", "Block", "Restoration", "Acrobatics");
}

void UnitClassArcher::_undefStats() {

	_unsetMajorSkillsAttributes("Strength", "Agility",
		"Marksman", "Light Armor", "Athletics");

	_unsetMinorSkillsAttributes("Unarmored", "Medium Armor", "Block", "Restoration", "Acrobatics");
}


void UnitClassSpy::_defineStats() {

	// Define Major/Minor skill-attribute set.

	_setMajorSkillsAttributes("Speed", "Agility",
		"Sneak", "Light Armor", "Unarmored");

	_setMinorSkillsAttributes("Athelitcs", "Marksman", "Block", "Illusion", "Acrobatics");
}

void UnitClassSpy::_undefStats() {

	_unsetMajorSkillsAttributes("Speed", "Agility",
		"Sneak", "Light Armor", "Unarmored");

	_unsetMinorSkillsAttributes("Athelitcs", "Marksman", "Block", "Illusion", "Acrobatics");
}

void UnitClassAssassin::_defineStats() {

	// Define Major/Minor skill-attribute set.

	_setMajorSkillsAttributes("Agility", "Speed",
		"Sneak", "Light Armor", "Short Blade");

	_setMinorSkillsAttributes("Athletics", "Alchemy", "Block", "Marksman", "Acrobatics");
}

void UnitClassAssassin::_undefStats() {

	_unsetMajorSkillsAttributes("Agility", "Speed",
		"Sneak", "Light Armor", "Short Blade");

	_unsetMinorSkillsAttributes("Athletics", "Alchemy", "Block", "Marksman", "Acrobatics");
}


void UnitClassBarbarian::_defineStats() {

	// Define Major/Minor skill-attribute set.

	_setMajorSkillsAttributes("Strength", "Speed",
		"Blunt Weapon", "Medium Armor", "Athletics");

	_setMinorSkillsAttributes("Unarmored", "Heavy Armor", "Block", "Axe", "Acrobatics");
}

void UnitClassBarbarian::_undefStats() {

	_unsetMajorSkillsAttributes("Strength", "Speed",
		"Blunt Weapon", "Medium Armor", "Athletics");

	_unsetMinorSkillsAttributes("Unarmored", "Heavy Armor", "Block", "Axe", "Acrobatics");
}


void UnitClassBattlemage::_defineStats() {

	// Define Major/Minor skill-attribute set.

	_setMajorSkillsAttributes("Strength", "Intelligence",
		"Heavy Armor", "Destruction", "Axe");

	_setMinorSkillsAttributes("Conjuration", "Alteration", "Block", "Restoration", "Blunt Weapon");
}

void UnitClassBattlemage::_undefStats() {

	_unsetMajorSkillsAttributes("Strength", "Intelligence",
		"Heavy Armor", "Destruction", "Axe");

	_unsetMinorSkillsAttributes("Conjuration", "Alteration", "Block", "Restoration", "Blunt Weapon");
}


void UnitClassPaladin::_defineStats() {

	// Define Major/Minor skill-attribute set.

	_setMajorSkillsAttributes("Strength", "Endurance",
		"Blunt Weapon", "Heavy Armor", "Restoration");

	_setMinorSkillsAttributes("Athletics", "Mysticism", "Block", "Alteration", "Long Blade");
}

void UnitClassPaladin::_undefStats() {

	_unsetMajorSkillsAttributes("Strength", "Endurance",
		"Blunt Weapon", "Heavy Armor", "Restoration");

	_unsetMinorSkillsAttributes("Athletics", "Mysticism", "Block", "Alteration", "Long Blade");
}



void UnitClassHealer::_defineStats() {

	// Define Major/Minor skill-attribute set.

	_setMajorSkillsAttributes("Intelligence", "Willpower",
		"Restoration", "Alteration", "Illusion");

	_setMinorSkillsAttributes("Unarmored", "Light Armor", "Block", "Mysticism", "Destruction");
}

void UnitClassHealer::_undefStats() {

	_unsetMajorSkillsAttributes("Intelligence", "Willpower",
		"Restoration", "Alteration", "Illusion");

	_unsetMinorSkillsAttributes("Unarmored", "Light Armor", "Block", "Mysticism", "Destruction");
}


void UnitClassKnight::_defineStats() {

	// Define Major/Minor skill-attribute set.

	_setMajorSkillsAttributes("Strength", "Endurance",
		"Restoration", "Heavy Armor", "Long Blade");

	_setMinorSkillsAttributes("Athletics", "Axe", "Block", "Enchant", "Medium Armor");
}

void UnitClassKnight::_undefStats() {

	_unsetMajorSkillsAttributes("Strength", "Endurance",
		"Restoration", "Heavy Armor", "Long Blade");

	_unsetMinorSkillsAttributes("Athletics", "Axe", "Block", "Enchant", "Medium Armor");
}


void UnitClassMage::_defineStats() {

	// Define Major/Minor skill-attribute set.

	_setMajorSkillsAttributes("Intelligence", "Willpower",
		"Alteration", "Illusion", "Destruction");

	_setMinorSkillsAttributes("Unarmored", "Conjuration", "Mysticism", "Restoration", "Blunt Weapon");
}

void UnitClassMage::_undefStats() {

	_unsetMajorSkillsAttributes("Intelligence", "Willpower",
		"Alteration", "Illusion", "Destruction");

	_unsetMinorSkillsAttributes("Unarmored", "Conjuration", "Mysticism", "Restoration", "Blunt Weapon");
}




void UnitClassNightblade::_defineStats() {

	// Define Major/Minor skill-attribute set.

	_setMajorSkillsAttributes("Speed", "Willpower",
		"Short Blade", "Sneak", "Conjuration");

	_setMinorSkillsAttributes("Light Armor", "Mysticism", "Block", "Athletics", "Acrobatics");
}

void UnitClassNightblade::_undefStats() {

	_unsetMajorSkillsAttributes("Speed", "Willpower",
		"Short Blade", "Sneak", "Conjuration");

	_unsetMinorSkillsAttributes("Light Armor", "Mysticism", "Block", "Athletics", "Acrobatics");
}



void UnitClassRogue::_defineStats() {

	// Define Major/Minor skill-attribute set.

	_setMajorSkillsAttributes("Speed", "Agility",
		"Short Blade", "Light Armor", "Medium Armor");

	_setMinorSkillsAttributes("Athletics", "Axe", "Block", "Acrobatics", "Long Blade");
}

void UnitClassRogue::_undefStats() {

	_unsetMajorSkillsAttributes("Speed", "Agility",
		"Short Blade", "Light Armor", "Medium Armor");

	_unsetMinorSkillsAttributes("Athletics", "Axe", "Block", "Acrobatics", "Long Blade");
}


void UnitClassScout::_defineStats() {

	// Define Major/Minor skill-attribute set.

	_setMajorSkillsAttributes("Speed", "Endurance",
		"Acrobatics", "Unarmored", "Athletics");

	_setMinorSkillsAttributes("Spear", "Short Blade", "Block", "Axe", "Sneak");
}

void UnitClassScout::_undefStats() {

	_unsetMajorSkillsAttributes("Speed", "Endurance",
		"Acrobatics", "Unarmored", "Athletics");

	_unsetMinorSkillsAttributes("Spear", "Short Blade", "Block", "Axe", "Sneak");
}



void UnitClassSorcerer::_defineStats() {

	// Define Major/Minor skill-attribute set.

	_setMajorSkillsAttributes("Endurance", "Intelligence",
		"Enchant", "Destruction", "Conjuration");

	_setMinorSkillsAttributes("Mysticism", "Medium Armor", "Alteration", "Restoration", "Blunt Weapon");
}

void UnitClassSorcerer::_undefStats() {

	_unsetMajorSkillsAttributes("Endurance", "Intelligence",
		"Enchant", "Destruction", "Conjuration");

	_unsetMinorSkillsAttributes("Mysticism", "Medium Armor", "Alteration", "Restoration", "Blunt Weapon");
}


void UnitClassSpellsword::_defineStats() {

	// Define Major/Minor skill-attribute set.

	_setMajorSkillsAttributes("Endurance", "Willpower",
		"Destruction", "Medium Armor", "Restoration");

	_setMinorSkillsAttributes("Alteration", "Heavy Armor", "Block", "Restoration", "Short Blade");
}

void UnitClassSpellsword::_undefStats() {

	_unsetMajorSkillsAttributes("Endurance", "Willpower",
		"Destruction", "Medium Armor", "Restoration");

	_unsetMinorSkillsAttributes("Alteration", "Heavy Armor", "Block", "Restoration", "Short Blade");
}


void UnitClassWarrior::_defineStats() {

	// Define Major/Minor skill-attribute set.

	_setMajorSkillsAttributes("Strength", "Speed",
		"Long Blade", "Medium Armor", "Athletics");

	_setMinorSkillsAttributes("Blunt Weapon", "Heavy Armor", "Block", "Spear", "Axe");
}

void UnitClassWarrior::_undefStats() {

	_unsetMajorSkillsAttributes("Strength", "Speed",
		"Long Blade", "Medium Armor", "Athletics");

	_unsetMinorSkillsAttributes("Blunt Weapon", "Heavy Armor", "Block", "Spear", "Axe");
}


void UnitClassInquisitor::_defineStats() {

	// Define Major/Minor skill-attribute set.

	_setMajorSkillsAttributes("Intelligence", "Agility",
		"Mysticism", "Light Armor", "Block");

	_setMinorSkillsAttributes("Conjuration", "Heavy Armor", "Blunt Weapon", "Spear", "Alteration");
}

void UnitClassInquisitor::_undefStats() {

	_unsetMajorSkillsAttributes("Intelligence", "Agility",
		"Mysticism", "Light Armor", "Block");

	_unsetMinorSkillsAttributes("Conjuration", "Heavy Armor", "Blunt Weapon", "Spear", "Alteration");
}
*/