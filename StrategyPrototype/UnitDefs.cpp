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


void UnitClassArcher::_defineStats() {

	// Attributes.
	m_UnitAttributes->SetAttribute("Strength", 10);
	m_UnitAttributes->SetAttribute("Agility", 10);

	m_UnitAttributes->SetAttribute("Intelligence", 5);
	m_UnitAttributes->SetAttribute("Willpower", 5);
	m_UnitAttributes->SetAttribute("Speed", 5);
	m_UnitAttributes->SetAttribute("Endurance", 5);
	m_UnitAttributes->SetAttribute("Personality", 5);

	// Skills.
	m_UnitSkills->SetSkill("Marksman", 10);
	m_UnitSkills->SetSkill("Light Armor", 10);
	m_UnitSkills->SetSkill("Medium Armor", 5);
	m_UnitSkills->SetSkill("Spear", 5);
	m_UnitSkills->SetSkill("Long Blade", 10);
	m_UnitSkills->SetSkill("Block", 10);
	m_UnitSkills->SetSkill("Athletics", 10);
	m_UnitSkills->SetSkill("Unarmored", 5);
	m_UnitSkills->SetSkill("Restoration", 5);

}

void UnitClassArcher::_undefStats() {

	// Attributes.
	// major
	m_UnitAttributes->UnsetAttribute("Strength", 10);
	m_UnitAttributes->UnsetAttribute("Agility", 10);

	// minor
	m_UnitAttributes->UnsetAttribute("Intelligence", 5);
	m_UnitAttributes->UnsetAttribute("Willpower", 5);
	m_UnitAttributes->UnsetAttribute("Speed", 5);
	m_UnitAttributes->UnsetAttribute("Endurance", 5);
	m_UnitAttributes->UnsetAttribute("Personality", 5);

	// Skills.
	m_UnitSkills->UnsetSkill("Marksman", 10);
	m_UnitSkills->UnsetSkill("Light Armor", 10);
	m_UnitSkills->UnsetSkill("Medium Armor", 5);
	m_UnitSkills->UnsetSkill("Spear", 5);
	m_UnitSkills->UnsetSkill("Long Blade", 10);
	m_UnitSkills->UnsetSkill("Block", 10);
	m_UnitSkills->UnsetSkill("Athletics", 10);
	m_UnitSkills->UnsetSkill("Unarmored", 5);
	m_UnitSkills->UnsetSkill("Restoration", 5);
}


void UnitClassSpy::_defineStats() {

	// Attributes.
	m_UnitAttributes->SetAttribute("Strength", 5);
	m_UnitAttributes->SetAttribute("Agility", 10);
	m_UnitAttributes->SetAttribute("Intelligence", 5);
	m_UnitAttributes->SetAttribute("Willpower", 5);
	m_UnitAttributes->SetAttribute("Speed", 5);
	m_UnitAttributes->SetAttribute("Endurance", 5);
	m_UnitAttributes->SetAttribute("Personality", 10);

	// Skills.
	m_UnitSkills->SetSkill("Light Armor", 10);
	m_UnitSkills->SetSkill("Marksman", 5);
	m_UnitSkills->SetSkill("Athletics", 5);
	m_UnitSkills->SetSkill("Sneak", 10);
	m_UnitSkills->SetSkill("Unarmored", 10);
}


void UnitClassSpy::_undefStats() {

	// Attributes.
	m_UnitAttributes->UnsetAttribute("Strength", 5);
	m_UnitAttributes->UnsetAttribute("Agility", 10);
	m_UnitAttributes->UnsetAttribute("Intelligence", 5);
	m_UnitAttributes->UnsetAttribute("Willpower", 5);
	m_UnitAttributes->UnsetAttribute("Speed", 5);
	m_UnitAttributes->UnsetAttribute("Endurance", 5);
	m_UnitAttributes->UnsetAttribute("Personality", 10);

	// Skills.
	m_UnitSkills->UnsetSkill("Light Armor", 10);
	m_UnitSkills->UnsetSkill("Marksman", 5);
	m_UnitSkills->UnsetSkill("Athletics", 5);
	m_UnitSkills->UnsetSkill("Sneak", 10);
	m_UnitSkills->UnsetSkill("Unarmored", 10);
}


void UnitClassAssassin::_defineStats() {

	// Attributes.
	m_UnitAttributes->SetAttribute("Strength", 5);
	m_UnitAttributes->SetAttribute("Agility", 10);
	m_UnitAttributes->SetAttribute("Intelligence", 5);
	m_UnitAttributes->SetAttribute("Willpower", 5);
	m_UnitAttributes->SetAttribute("Speed", 10);
	m_UnitAttributes->SetAttribute("Endurance", 5);
	m_UnitAttributes->SetAttribute("Personality", 5);


	// Skills
	m_UnitSkills->SetSkill("Light Armor", 10);
	m_UnitSkills->SetSkill("Unarmored", 10);
	m_UnitSkills->SetSkill("Short Blade", 10);
	m_UnitSkills->SetSkill("Sneak", 10);

	m_UnitSkills->SetSkill("Block", 5);
}


void UnitClassAssassin::_undefStats() {

	// Attributes.
	m_UnitAttributes->UnsetAttribute("Strength", 5);
	m_UnitAttributes->UnsetAttribute("Agility", 10);
	m_UnitAttributes->UnsetAttribute("Intelligence", 5);
	m_UnitAttributes->UnsetAttribute("Willpower", 5);
	m_UnitAttributes->UnsetAttribute("Speed", 10);
	m_UnitAttributes->UnsetAttribute("Endurance", 5);
	m_UnitAttributes->UnsetAttribute("Personality", 5);


	// Skills
	m_UnitSkills->UnsetSkill("Light Armor", 10);
	m_UnitSkills->UnsetSkill("Unarmored", 10);
	m_UnitSkills->UnsetSkill("Short Blade", 10);
	m_UnitSkills->UnsetSkill("Sneak", 10);
	m_UnitSkills->UnsetSkill("Block", 5);
}



void UnitClassRogue::_defineStats() {

	// Attributes.
	m_UnitAttributes->SetAttribute("Strength", 5);
	m_UnitAttributes->SetAttribute("Agility", 10);
	m_UnitAttributes->SetAttribute("Intelligence", 5);
	m_UnitAttributes->SetAttribute("Willpower", 5);
	m_UnitAttributes->SetAttribute("Speed", 10);
	m_UnitAttributes->SetAttribute("Endurance", 5);
	m_UnitAttributes->SetAttribute("Personality", 5);


	// Skills
	m_UnitSkills->SetSkill("Light Armor", 10);
	m_UnitSkills->SetSkill("Medium Armor", 10);

	m_UnitSkills->SetSkill("Short Blade", 10);
	m_UnitSkills->SetSkill("Axe", 10);

	m_UnitSkills->SetSkill("Block", 5);

}


void UnitClassRogue::_undefStats() {

	// Attributes.
	m_UnitAttributes->UnsetAttribute("Strength", 5);
	m_UnitAttributes->UnsetAttribute("Agility", 10);
	m_UnitAttributes->UnsetAttribute("Intelligence", 5);
	m_UnitAttributes->UnsetAttribute("Willpower", 5);
	m_UnitAttributes->UnsetAttribute("Speed", 10);
	m_UnitAttributes->UnsetAttribute("Endurance", 5);
	m_UnitAttributes->UnsetAttribute("Personality", 5);


	// Skills
	m_UnitSkills->UnsetSkill("Light Armor", 10);
	m_UnitSkills->UnsetSkill("Medium Armor", 10);

	m_UnitSkills->UnsetSkill("Short Blade", 10);
	m_UnitSkills->UnsetSkill("Axe", 10);

	m_UnitSkills->UnsetSkill("Block", 5);
}


void UnitClassScout::_defineStats() {


	// Attributes.
	m_UnitAttributes->SetAttribute("Strength", 5);
	m_UnitAttributes->SetAttribute("Agility", 5);
	m_UnitAttributes->SetAttribute("Intelligence", 5);
	m_UnitAttributes->SetAttribute("Willpower", 5);
	m_UnitAttributes->SetAttribute("Speed", 10);
	m_UnitAttributes->SetAttribute("Endurance", 10);
	m_UnitAttributes->SetAttribute("Personality", 5);


	// Skills
	m_UnitSkills->SetSkill("Athletics", 10);
	m_UnitSkills->SetSkill("Acrobatics", 10);
	m_UnitSkills->SetSkill("Unarmored", 10);

	m_UnitSkills->SetSkill("Block", 5);
}


void UnitClassScout::_undefStats() {

	// Attributes.
	m_UnitAttributes->UnsetAttribute("Strength", 5);
	m_UnitAttributes->UnsetAttribute("Agility", 5);
	m_UnitAttributes->UnsetAttribute("Intelligence", 5);
	m_UnitAttributes->UnsetAttribute("Willpower", 5);
	m_UnitAttributes->UnsetAttribute("Speed", 10);
	m_UnitAttributes->UnsetAttribute("Endurance", 10);
	m_UnitAttributes->UnsetAttribute("Personality", 5);


	// Skills
	m_UnitSkills->UnsetSkill("Athletics", 10);
	m_UnitSkills->UnsetSkill("Acrobatics", 10);
	m_UnitSkills->UnsetSkill("Unarmored", 10);

	m_UnitSkills->UnsetSkill("Block", 5);
}



void UnitClassBarbarian::_defineStats() {

	// Attributes.
	m_UnitAttributes->SetAttribute("Strength", 10);
	m_UnitAttributes->SetAttribute("Agility", 5);
	m_UnitAttributes->SetAttribute("Intelligence", 5);
	m_UnitAttributes->SetAttribute("Willpower", 5);
	m_UnitAttributes->SetAttribute("Speed", 10);
	m_UnitAttributes->SetAttribute("Endurance", 5);
	m_UnitAttributes->SetAttribute("Personality", 5);


	// Skills
	m_UnitSkills->SetSkill("Medium Armor", 10);
	m_UnitSkills->SetSkill("Blunt Weapon", 10);
	m_UnitSkills->SetSkill("Unarmored", 10);
	m_UnitSkills->SetSkill("Athletics", 10);

	m_UnitSkills->SetSkill("Block", 5);
}


void UnitClassBarbarian::_undefStats() {

	// Attributes.
	m_UnitAttributes->UnsetAttribute("Strength", 10);
	m_UnitAttributes->UnsetAttribute("Agility", 5);
	m_UnitAttributes->UnsetAttribute("Intelligence", 5);
	m_UnitAttributes->UnsetAttribute("Willpower", 5);
	m_UnitAttributes->UnsetAttribute("Speed", 10);
	m_UnitAttributes->UnsetAttribute("Endurance", 5);
	m_UnitAttributes->UnsetAttribute("Personality", 5);


	// Skills
	m_UnitSkills->UnsetSkill("Medium Armor", 10);
	m_UnitSkills->UnsetSkill("Blunt Weapon", 10);
	m_UnitSkills->UnsetSkill("Unarmored", 10);
	m_UnitSkills->UnsetSkill("Athletics", 10);

	m_UnitSkills->UnsetSkill("Block", 5);
}


void UnitClassWarrior::_defineStats() {

	// Attributes.
	m_UnitAttributes->SetAttribute("Strength", 15);
	m_UnitAttributes->SetAttribute("Agility", 5);
	m_UnitAttributes->SetAttribute("Intelligence", 5);
	m_UnitAttributes->SetAttribute("Willpower", 5);
	m_UnitAttributes->SetAttribute("Speed", 15);
	m_UnitAttributes->SetAttribute("Endurance", 5);
	m_UnitAttributes->SetAttribute("Personality", 5);


	// Skills
	m_UnitSkills->SetSkill("Medium Armor", 15);
	m_UnitSkills->SetSkill("Heavy Armor", 15);
	m_UnitSkills->SetSkill("Athletics", 10);
	m_UnitSkills->SetSkill("Long Blade", 10);

	m_UnitSkills->SetSkill("Block", 5);
}

void UnitClassWarrior::_undefStats() {

	// Attributes.
	m_UnitAttributes->UnsetAttribute("Strength", 15);
	m_UnitAttributes->UnsetAttribute("Agility", 5);
	m_UnitAttributes->UnsetAttribute("Intelligence", 5);
	m_UnitAttributes->UnsetAttribute("Willpower", 5);
	m_UnitAttributes->UnsetAttribute("Speed", 15);
	m_UnitAttributes->UnsetAttribute("Endurance", 5);
	m_UnitAttributes->UnsetAttribute("Personality", 5);


	// Skills
	m_UnitSkills->UnsetSkill("Medium Armor", 15);
	m_UnitSkills->UnsetSkill("Heavy Armor", 15);
	m_UnitSkills->UnsetSkill("Athletics", 10);
	m_UnitSkills->UnsetSkill("Long Blade", 10);

	m_UnitSkills->UnsetSkill("Block", 5);
}


void UnitClassKnight::_defineStats() {

	// Attributes.
	m_UnitAttributes->SetAttribute("Strength", 20);
	m_UnitAttributes->SetAttribute("Agility", 5);
	m_UnitAttributes->SetAttribute("Intelligence", 5);
	m_UnitAttributes->SetAttribute("Willpower", 5);
	m_UnitAttributes->SetAttribute("Speed", 5);
	m_UnitAttributes->SetAttribute("Endurance", 15);
	m_UnitAttributes->SetAttribute("Personality", 5);


	// Skills
	m_UnitSkills->SetSkill("Heavy Armor", 15);
	m_UnitSkills->SetSkill("Athletics", 5);
	m_UnitSkills->SetSkill("Long Blade", 15);
	m_UnitSkills->SetSkill("Block", 10);
	m_UnitSkills->SetSkill("Axe", 10);

	m_UnitSkills->SetSkill("Restoration", 10);

}

void UnitClassKnight::_undefStats() {

	// Attributes.
	m_UnitAttributes->UnsetAttribute("Strength", 20);
	m_UnitAttributes->UnsetAttribute("Agility", 5);
	m_UnitAttributes->UnsetAttribute("Intelligence", 5);
	m_UnitAttributes->UnsetAttribute("Willpower", 5);
	m_UnitAttributes->UnsetAttribute("Speed", 5);
	m_UnitAttributes->UnsetAttribute("Endurance", 15);
	m_UnitAttributes->UnsetAttribute("Personality", 5);


	// Skills
	m_UnitSkills->UnsetSkill("Heavy Armor", 15);
	m_UnitSkills->UnsetSkill("Athletics", 5);
	m_UnitSkills->UnsetSkill("Long Blade", 15);
	m_UnitSkills->UnsetSkill("Axe", 10);
	m_UnitSkills->UnsetSkill("Block", 10);

	m_UnitSkills->UnsetSkill("Restoration", 10);
}


void UnitClassPaladin::_defineStats() {


	// Attributes.
	m_UnitAttributes->SetAttribute("Strength", 20);
	m_UnitAttributes->SetAttribute("Agility", 5);
	m_UnitAttributes->SetAttribute("Intelligence", 5);
	m_UnitAttributes->SetAttribute("Willpower", 5);
	m_UnitAttributes->SetAttribute("Speed", 5);
	m_UnitAttributes->SetAttribute("Endurance", 20);
	m_UnitAttributes->SetAttribute("Personality", 5);


	// Skills
	m_UnitSkills->SetSkill("Heavy Armor", 20);
	m_UnitSkills->SetSkill("Athletics", 5);
	m_UnitSkills->SetSkill("Long Blade", 20);
	m_UnitSkills->SetSkill("Block", 15);
	m_UnitSkills->SetSkill("Blunt Weapon", 15);

	m_UnitSkills->SetSkill("Restoration", 15);
}

void UnitClassPaladin::_undefStats() {

	// Attributes.
	m_UnitAttributes->UnsetAttribute("Strength", 20);
	m_UnitAttributes->UnsetAttribute("Agility", 5);
	m_UnitAttributes->UnsetAttribute("Intelligence", 5);
	m_UnitAttributes->UnsetAttribute("Willpower", 5);
	m_UnitAttributes->UnsetAttribute("Speed", 5);
	m_UnitAttributes->UnsetAttribute("Endurance", 20);
	m_UnitAttributes->UnsetAttribute("Personality", 5);


	// Skills
	m_UnitSkills->UnsetSkill("Heavy Armor", 20);
	m_UnitSkills->UnsetSkill("Athletics", 5);
	m_UnitSkills->UnsetSkill("Long Blade", 20);
	m_UnitSkills->UnsetSkill("Block", 15);
	m_UnitSkills->UnsetSkill("Blunt Weapon", 15);

	m_UnitSkills->UnsetSkill("Restoration", 15);
}


void UnitClassSpellsword::_defineStats() {

	// Attributes.
	m_UnitAttributes->SetAttribute("Strength", 5);
	m_UnitAttributes->SetAttribute("Agility", 5);
	m_UnitAttributes->SetAttribute("Intelligence", 5);
	m_UnitAttributes->SetAttribute("Willpower", 10);
	m_UnitAttributes->SetAttribute("Speed", 5);
	m_UnitAttributes->SetAttribute("Endurance", 10);
	m_UnitAttributes->SetAttribute("Personality", 5);


	// Skills
	m_UnitSkills->SetSkill("Medium Armor", 10);
	m_UnitSkills->SetSkill("Short Blade", 5);
	m_UnitSkills->SetSkill("Block", 10);

	m_UnitSkills->SetSkill("Restoration", 10);
	m_UnitSkills->SetSkill("Destruction", 10);
	m_UnitSkills->SetSkill("Alteration", 10);

}

void UnitClassSpellsword::_undefStats() {

	// Attributes.
	m_UnitAttributes->UnsetAttribute("Strength", 5);
	m_UnitAttributes->UnsetAttribute("Agility", 5);
	m_UnitAttributes->UnsetAttribute("Intelligence", 5);
	m_UnitAttributes->UnsetAttribute("Willpower", 10);
	m_UnitAttributes->UnsetAttribute("Speed", 5);
	m_UnitAttributes->UnsetAttribute("Endurance", 10);
	m_UnitAttributes->UnsetAttribute("Personality", 5);


	// Skills
	m_UnitSkills->UnsetSkill("Medium Armor", 10);
	m_UnitSkills->UnsetSkill("Short Blade", 5);
	m_UnitSkills->UnsetSkill("Block", 10);

	m_UnitSkills->UnsetSkill("Restoration", 10);
	m_UnitSkills->UnsetSkill("Destruction", 10);
	m_UnitSkills->UnsetSkill("Alteration", 10);
}


void UnitClassBattlemage::_defineStats() {

	// Attributes.
	m_UnitAttributes->SetAttribute("Strength", 10);
	m_UnitAttributes->SetAttribute("Agility", 5);
	m_UnitAttributes->SetAttribute("Intelligence", 10);
	m_UnitAttributes->SetAttribute("Willpower", 5);
	m_UnitAttributes->SetAttribute("Speed", 5);
	m_UnitAttributes->SetAttribute("Endurance", 5);
	m_UnitAttributes->SetAttribute("Personality", 5);


	// Skills
	m_UnitSkills->SetSkill("Heavy Armor", 15);
	m_UnitSkills->SetSkill("Axe", 10);
	m_UnitSkills->SetSkill("Block", 10);

	m_UnitSkills->SetSkill("Restoration", 15);
	m_UnitSkills->SetSkill("Destruction", 15);
	m_UnitSkills->SetSkill("Alteration", 15);
	m_UnitSkills->SetSkill("Conjuration", 15);

}

void UnitClassBattlemage::_undefStats() {


	// Attributes.
	m_UnitAttributes->UnsetAttribute("Strength", 10);
	m_UnitAttributes->UnsetAttribute("Agility", 5);
	m_UnitAttributes->UnsetAttribute("Intelligence", 10);
	m_UnitAttributes->UnsetAttribute("Willpower", 5);
	m_UnitAttributes->UnsetAttribute("Speed", 5);
	m_UnitAttributes->UnsetAttribute("Endurance", 5);
	m_UnitAttributes->UnsetAttribute("Personality", 5);


	// Skills
	m_UnitSkills->UnsetSkill("Heavy Armor", 15);
	m_UnitSkills->UnsetSkill("Axe", 10);
	m_UnitSkills->UnsetSkill("Block", 10);

	m_UnitSkills->UnsetSkill("Restoration", 15);
	m_UnitSkills->UnsetSkill("Destruction", 15);
	m_UnitSkills->UnsetSkill("Alteration", 15);
	m_UnitSkills->UnsetSkill("Conjuration", 15);
}


void UnitClassNightblade::_defineStats() {

	// Attributes.
	m_UnitAttributes->SetAttribute("Strength", 5);
	m_UnitAttributes->SetAttribute("Agility", 5);
	m_UnitAttributes->SetAttribute("Intelligence", 5);
	m_UnitAttributes->SetAttribute("Willpower", 15);
	m_UnitAttributes->SetAttribute("Speed", 15);
	m_UnitAttributes->SetAttribute("Endurance", 5);
	m_UnitAttributes->SetAttribute("Personality", 5);


	// Skills
	m_UnitSkills->SetSkill("Light Armor", 10);
	m_UnitSkills->SetSkill("Short Blade", 30);
	m_UnitSkills->SetSkill("Block", 10);

	m_UnitSkills->SetSkill("Mysticism", 20);
	m_UnitSkills->SetSkill("Alteration", 15);
	m_UnitSkills->SetSkill("Conjuration", 20);
}

void UnitClassNightblade::_undefStats() {

	// Attributes.
	m_UnitAttributes->UnsetAttribute("Strength", 5);
	m_UnitAttributes->UnsetAttribute("Agility", 5);
	m_UnitAttributes->UnsetAttribute("Intelligence", 5);
	m_UnitAttributes->UnsetAttribute("Willpower", 15);
	m_UnitAttributes->UnsetAttribute("Speed", 15);
	m_UnitAttributes->UnsetAttribute("Endurance", 5);
	m_UnitAttributes->UnsetAttribute("Personality", 5);


	// Skills
	m_UnitSkills->UnsetSkill("Light Armor", 10);
	m_UnitSkills->UnsetSkill("Short Blade", 30);
	m_UnitSkills->UnsetSkill("Block", 10);

	m_UnitSkills->UnsetSkill("Mysticism", 20);
	m_UnitSkills->UnsetSkill("Alteration", 15);
	m_UnitSkills->UnsetSkill("Conjuration", 20);
}



void UnitClassInquisitor::_defineStats() {

	// Attributes.
	m_UnitAttributes->SetAttribute("Strength", 5);
	m_UnitAttributes->SetAttribute("Agility", 15);
	m_UnitAttributes->SetAttribute("Intelligence", 15);
	m_UnitAttributes->SetAttribute("Willpower", 5);
	m_UnitAttributes->SetAttribute("Speed", 5);
	m_UnitAttributes->SetAttribute("Endurance", 5);
	m_UnitAttributes->SetAttribute("Personality", 5);


	// Skills
	m_UnitSkills->SetSkill("Light Armor", 20);
	m_UnitSkills->SetSkill("Blunt Weapon", 10);
	m_UnitSkills->SetSkill("Block", 20);

	m_UnitSkills->SetSkill("Mysticism", 20);
	m_UnitSkills->SetSkill("Conjuration", 20);
}

void UnitClassInquisitor::_undefStats() {

	// Attributes.
	m_UnitAttributes->UnsetAttribute("Strength", 5);
	m_UnitAttributes->UnsetAttribute("Agility", 15);
	m_UnitAttributes->UnsetAttribute("Intelligence", 15);
	m_UnitAttributes->UnsetAttribute("Willpower", 5);
	m_UnitAttributes->UnsetAttribute("Speed", 5);
	m_UnitAttributes->UnsetAttribute("Endurance", 5);
	m_UnitAttributes->UnsetAttribute("Personality", 5);


	// Skills
	m_UnitSkills->UnsetSkill("Light Armor", 20);
	m_UnitSkills->UnsetSkill("Blunt Weapon", 10);
	m_UnitSkills->UnsetSkill("Block", 20);

	m_UnitSkills->UnsetSkill("Mysticism", 20);
	m_UnitSkills->UnsetSkill("Conjuration", 20);
}


void UnitClassMage::_defineStats() {

	// Attributes.
	m_UnitAttributes->SetAttribute("Strength", 5);
	m_UnitAttributes->SetAttribute("Agility", 5);
	m_UnitAttributes->SetAttribute("Intelligence", 10);
	m_UnitAttributes->SetAttribute("Willpower", 10);
	m_UnitAttributes->SetAttribute("Speed", 5);
	m_UnitAttributes->SetAttribute("Endurance", 5);
	m_UnitAttributes->SetAttribute("Personality", 5);


	// Skills
	m_UnitSkills->SetSkill("Mysticism", 10);
	m_UnitSkills->SetSkill("Conjuration", 10);
	m_UnitSkills->SetSkill("Alteration", 10);
	m_UnitSkills->SetSkill("Destruction", 10);
	m_UnitSkills->SetSkill("Illusion", 10);

	m_UnitSkills->SetSkill("Restoration", 5);

}

void UnitClassMage::_undefStats() {

	// Attributes.
	m_UnitAttributes->UnsetAttribute("Strength", 5);
	m_UnitAttributes->UnsetAttribute("Agility", 5);
	m_UnitAttributes->UnsetAttribute("Intelligence", 10);
	m_UnitAttributes->UnsetAttribute("Willpower", 10);
	m_UnitAttributes->UnsetAttribute("Speed", 5);
	m_UnitAttributes->UnsetAttribute("Endurance", 5);
	m_UnitAttributes->UnsetAttribute("Personality", 5);


	// Skills
	m_UnitSkills->UnsetSkill("Mysticism", 10);
	m_UnitSkills->UnsetSkill("Conjuration", 10);
	m_UnitSkills->UnsetSkill("Alteration", 10);
	m_UnitSkills->UnsetSkill("Destruction", 10);
	m_UnitSkills->UnsetSkill("Illusion", 10);

	m_UnitSkills->UnsetSkill("Restoration", 5);
}


void UnitClassSorcerer::_defineStats() {

	// Attributes.
	m_UnitAttributes->SetAttribute("Strength", 5);
	m_UnitAttributes->SetAttribute("Agility", 5);
	m_UnitAttributes->SetAttribute("Intelligence", 10);
	m_UnitAttributes->SetAttribute("Willpower", 5);
	m_UnitAttributes->SetAttribute("Speed", 5);
	m_UnitAttributes->SetAttribute("Endurance", 10);
	m_UnitAttributes->SetAttribute("Personality", 5);


	// Skills
	m_UnitSkills->SetSkill("Mysticism", 10);
	m_UnitSkills->SetSkill("Conjuration", 15);
	m_UnitSkills->SetSkill("Alteration", 10);
	m_UnitSkills->SetSkill("Destruction", 10);
	m_UnitSkills->SetSkill("Enchant", 10);

	m_UnitSkills->SetSkill("Restoration", 5);
}

void UnitClassSorcerer::_undefStats() {

	// Attributes.
	m_UnitAttributes->UnsetAttribute("Strength", 5);
	m_UnitAttributes->UnsetAttribute("Agility", 5);
	m_UnitAttributes->UnsetAttribute("Intelligence", 10);
	m_UnitAttributes->UnsetAttribute("Willpower", 5);
	m_UnitAttributes->UnsetAttribute("Speed", 5);
	m_UnitAttributes->UnsetAttribute("Endurance", 10);
	m_UnitAttributes->UnsetAttribute("Personality", 5);


	// Skills
	m_UnitSkills->UnsetSkill("Mysticism", 10);
	m_UnitSkills->UnsetSkill("Conjuration", 15);
	m_UnitSkills->UnsetSkill("Alteration", 10);
	m_UnitSkills->UnsetSkill("Destruction", 10);
	m_UnitSkills->UnsetSkill("Enchant", 10);

	m_UnitSkills->UnsetSkill("Restoration", 5);
}


void UnitClassHealer::_defineStats() {

	// Attributes.
	m_UnitAttributes->SetAttribute("Strength", 5);
	m_UnitAttributes->SetAttribute("Agility", 5);
	m_UnitAttributes->SetAttribute("Intelligence", 10);
	m_UnitAttributes->SetAttribute("Willpower", 15);
	m_UnitAttributes->SetAttribute("Speed", 5);
	m_UnitAttributes->SetAttribute("Endurance", 5);
	m_UnitAttributes->SetAttribute("Personality", 5);


	// Skills
	m_UnitSkills->SetSkill("Mysticism", 10);
	m_UnitSkills->SetSkill("Alteration", 10);
	m_UnitSkills->SetSkill("Destruction", 5);
	m_UnitSkills->SetSkill("Illusion", 10);

	m_UnitSkills->SetSkill("Restoration", 15);
	m_UnitSkills->SetSkill("Block", 5);

}

void UnitClassHealer::_undefStats() {

	// Attributes.
	m_UnitAttributes->UnsetAttribute("Strength", 5);
	m_UnitAttributes->UnsetAttribute("Agility", 5);
	m_UnitAttributes->UnsetAttribute("Intelligence", 10);
	m_UnitAttributes->UnsetAttribute("Willpower", 15);
	m_UnitAttributes->UnsetAttribute("Speed", 5);
	m_UnitAttributes->UnsetAttribute("Endurance", 5);
	m_UnitAttributes->UnsetAttribute("Personality", 5);


	// Skills
	m_UnitSkills->UnsetSkill("Mysticism", 10);
	m_UnitSkills->UnsetSkill("Alteration", 10);
	m_UnitSkills->UnsetSkill("Destruction", 5);
	m_UnitSkills->UnsetSkill("Illusion", 10);

	m_UnitSkills->UnsetSkill("Restoration", 15);
	m_UnitSkills->UnsetSkill("Block", 5);

}