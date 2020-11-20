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

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->SetAttribute(m_AttrMap, "Strength", 10);
	attr->SetAttribute(m_AttrMap, "Agility", 10);

	attr->SetAttribute(m_AttrMap, "Intelligence", 5);
	attr->SetAttribute(m_AttrMap, "Willpower", 5);
	attr->SetAttribute(m_AttrMap, "Speed", 5);
	attr->SetAttribute(m_AttrMap, "Endurance", 5);
	attr->SetAttribute(m_AttrMap, "Personality", 5);

	// Skills.
	skills->SetSkill(m_SkillsMap, "Marksman", 10);
	skills->SetSkill(m_SkillsMap, "Light Armor", 10);
	skills->SetSkill(m_SkillsMap, "Medium Armor", 5);
	skills->SetSkill(m_SkillsMap, "Spear", 5);
	skills->SetSkill(m_SkillsMap, "Long Blade", 10);
	skills->SetSkill(m_SkillsMap, "Block", 10);
	skills->SetSkill(m_SkillsMap, "Athletics", 10);
	skills->SetSkill(m_SkillsMap, "Unarmored", 5);
	skills->SetSkill(m_SkillsMap, "Restoration", 5);

}

void UnitClassArcher::_undefStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	// major
	attr->UnsetAttribute(m_AttrMap, "Strength", 10);
	attr->UnsetAttribute(m_AttrMap, "Agility", 10);

	// minor
	attr->UnsetAttribute(m_AttrMap, "Intelligence", 5);
	attr->UnsetAttribute(m_AttrMap, "Willpower", 5);
	attr->UnsetAttribute(m_AttrMap, "Speed", 5);
	attr->UnsetAttribute(m_AttrMap, "Endurance", 5);
	attr->UnsetAttribute(m_AttrMap, "Personality", 5);

	// Skills.
	skills->UnsetSkill(m_SkillsMap, "Marksman", 10);
	skills->UnsetSkill(m_SkillsMap, "Light Armor", 10);
	skills->UnsetSkill(m_SkillsMap, "Medium Armor", 5);
	skills->UnsetSkill(m_SkillsMap, "Spear", 5);
	skills->UnsetSkill(m_SkillsMap, "Long Blade", 10);
	skills->UnsetSkill(m_SkillsMap, "Block", 10);
	skills->UnsetSkill(m_SkillsMap, "Athletics", 10);
	skills->UnsetSkill(m_SkillsMap, "Unarmored", 5);
	skills->UnsetSkill(m_SkillsMap, "Restoration", 5);
}


void UnitClassSpy::_defineStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->SetAttribute(m_AttrMap, "Strength", 5);
	attr->SetAttribute(m_AttrMap, "Agility", 10);
	attr->SetAttribute(m_AttrMap, "Intelligence", 5);
	attr->SetAttribute(m_AttrMap, "Willpower", 5);
	attr->SetAttribute(m_AttrMap, "Speed", 5);
	attr->SetAttribute(m_AttrMap, "Endurance", 5);
	attr->SetAttribute(m_AttrMap, "Personality", 10);

	// Skills.
	skills->SetSkill(m_SkillsMap, "Light Armor", 10);
	skills->SetSkill(m_SkillsMap, "Marksman", 5);
	skills->SetSkill(m_SkillsMap, "Athletics", 5);
	skills->SetSkill(m_SkillsMap, "Sneak", 10);
	skills->SetSkill(m_SkillsMap, "Unarmored", 10);
}


void UnitClassSpy::_undefStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->UnsetAttribute(m_AttrMap, "Strength", 5);
	attr->UnsetAttribute(m_AttrMap, "Agility", 10);
	attr->UnsetAttribute(m_AttrMap, "Intelligence", 5);
	attr->UnsetAttribute(m_AttrMap, "Willpower", 5);
	attr->UnsetAttribute(m_AttrMap, "Speed", 5);
	attr->UnsetAttribute(m_AttrMap, "Endurance", 5);
	attr->UnsetAttribute(m_AttrMap, "Personality", 10);

	// Skills.
	skills->UnsetSkill(m_SkillsMap, "Light Armor", 10);
	skills->UnsetSkill(m_SkillsMap, "Marksman", 5);
	skills->UnsetSkill(m_SkillsMap, "Athletics", 5);
	skills->UnsetSkill(m_SkillsMap, "Sneak", 10);
	skills->UnsetSkill(m_SkillsMap, "Unarmored", 10);
}


void UnitClassAssassin::_defineStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->SetAttribute(m_AttrMap, "Strength", 5);
	attr->SetAttribute(m_AttrMap, "Agility", 10);
	attr->SetAttribute(m_AttrMap, "Intelligence", 5);
	attr->SetAttribute(m_AttrMap, "Willpower", 5);
	attr->SetAttribute(m_AttrMap, "Speed", 10);
	attr->SetAttribute(m_AttrMap, "Endurance", 5);
	attr->SetAttribute(m_AttrMap, "Personality", 5);


	// Skills
	skills->SetSkill(m_SkillsMap, "Light Armor", 10);
	skills->SetSkill(m_SkillsMap, "Unarmored", 10);
	skills->SetSkill(m_SkillsMap, "Short Blade", 10);
	skills->SetSkill(m_SkillsMap, "Sneak", 10);

	skills->SetSkill(m_SkillsMap, "Block", 5);
}


void UnitClassAssassin::_undefStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->UnsetAttribute(m_AttrMap, "Strength", 5);
	attr->UnsetAttribute(m_AttrMap, "Agility", 10);
	attr->UnsetAttribute(m_AttrMap, "Intelligence", 5);
	attr->UnsetAttribute(m_AttrMap, "Willpower", 5);
	attr->UnsetAttribute(m_AttrMap, "Speed", 10);
	attr->UnsetAttribute(m_AttrMap, "Endurance", 5);
	attr->UnsetAttribute(m_AttrMap, "Personality", 5);


	// Skills
	skills->UnsetSkill(m_SkillsMap, "Light Armor", 10);
	skills->UnsetSkill(m_SkillsMap, "Unarmored", 10);
	skills->UnsetSkill(m_SkillsMap, "Short Blade", 10);
	skills->UnsetSkill(m_SkillsMap, "Sneak", 10);
	skills->UnsetSkill(m_SkillsMap, "Block", 5);
}



void UnitClassRogue::_defineStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->SetAttribute(m_AttrMap, "Strength", 5);
	attr->SetAttribute(m_AttrMap, "Agility", 10);
	attr->SetAttribute(m_AttrMap, "Intelligence", 5);
	attr->SetAttribute(m_AttrMap, "Willpower", 5);
	attr->SetAttribute(m_AttrMap, "Speed", 10);
	attr->SetAttribute(m_AttrMap, "Endurance", 5);
	attr->SetAttribute(m_AttrMap, "Personality", 5);


	// Skills
	skills->SetSkill(m_SkillsMap, "Light Armor", 10);
	skills->SetSkill(m_SkillsMap, "Medium Armor", 10);

	skills->SetSkill(m_SkillsMap, "Short Blade", 10);
	skills->SetSkill(m_SkillsMap, "Axe", 10);

	skills->SetSkill(m_SkillsMap, "Block", 5);

}


void UnitClassRogue::_undefStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->UnsetAttribute(m_AttrMap, "Strength", 5);
	attr->UnsetAttribute(m_AttrMap, "Agility", 10);
	attr->UnsetAttribute(m_AttrMap, "Intelligence", 5);
	attr->UnsetAttribute(m_AttrMap, "Willpower", 5);
	attr->UnsetAttribute(m_AttrMap, "Speed", 10);
	attr->UnsetAttribute(m_AttrMap, "Endurance", 5);
	attr->UnsetAttribute(m_AttrMap, "Personality", 5);


	// Skills
	skills->UnsetSkill(m_SkillsMap, "Light Armor", 10);
	skills->UnsetSkill(m_SkillsMap, "Medium Armor", 10);

	skills->UnsetSkill(m_SkillsMap, "Short Blade", 10);
	skills->UnsetSkill(m_SkillsMap, "Axe", 10);

	skills->UnsetSkill(m_SkillsMap, "Block", 5);
}


void UnitClassScout::_defineStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->SetAttribute(m_AttrMap, "Strength", 5);
	attr->SetAttribute(m_AttrMap, "Agility", 5);
	attr->SetAttribute(m_AttrMap, "Intelligence", 5);
	attr->SetAttribute(m_AttrMap, "Willpower", 5);
	attr->SetAttribute(m_AttrMap, "Speed", 10);
	attr->SetAttribute(m_AttrMap, "Endurance", 10);
	attr->SetAttribute(m_AttrMap, "Personality", 5);


	// Skills
	skills->SetSkill(m_SkillsMap, "Athletics", 10);
	skills->SetSkill(m_SkillsMap, "Acrobatics", 10);
	skills->SetSkill(m_SkillsMap, "Unarmored", 10);

	skills->SetSkill(m_SkillsMap, "Block", 5);
}


void UnitClassScout::_undefStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->UnsetAttribute(m_AttrMap, "Strength", 5);
	attr->UnsetAttribute(m_AttrMap, "Agility", 5);
	attr->UnsetAttribute(m_AttrMap, "Intelligence", 5);
	attr->UnsetAttribute(m_AttrMap, "Willpower", 5);
	attr->UnsetAttribute(m_AttrMap, "Speed", 10);
	attr->UnsetAttribute(m_AttrMap, "Endurance", 10);
	attr->UnsetAttribute(m_AttrMap, "Personality", 5);


	// Skills
	skills->UnsetSkill(m_SkillsMap, "Athletics", 10);
	skills->UnsetSkill(m_SkillsMap, "Acrobatics", 10);
	skills->UnsetSkill(m_SkillsMap, "Unarmored", 10);

	skills->UnsetSkill(m_SkillsMap, "Block", 5);
}



void UnitClassBarbarian::_defineStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->SetAttribute(m_AttrMap, "Strength", 10);
	attr->SetAttribute(m_AttrMap, "Agility", 5);
	attr->SetAttribute(m_AttrMap, "Intelligence", 5);
	attr->SetAttribute(m_AttrMap, "Willpower", 5);
	attr->SetAttribute(m_AttrMap, "Speed", 10);
	attr->SetAttribute(m_AttrMap, "Endurance", 5);
	attr->SetAttribute(m_AttrMap, "Personality", 5);


	// Skills
	skills->SetSkill(m_SkillsMap, "Medium Armor", 10);
	skills->SetSkill(m_SkillsMap, "Blunt Weapon", 10);
	skills->SetSkill(m_SkillsMap, "Unarmored", 10);
	skills->SetSkill(m_SkillsMap, "Athletics", 10);

	skills->SetSkill(m_SkillsMap, "Block", 5);
}


void UnitClassBarbarian::_undefStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->UnsetAttribute(m_AttrMap, "Strength", 10);
	attr->UnsetAttribute(m_AttrMap, "Agility", 5);
	attr->UnsetAttribute(m_AttrMap, "Intelligence", 5);
	attr->UnsetAttribute(m_AttrMap, "Willpower", 5);
	attr->UnsetAttribute(m_AttrMap, "Speed", 10);
	attr->UnsetAttribute(m_AttrMap, "Endurance", 5);
	attr->UnsetAttribute(m_AttrMap, "Personality", 5);


	// Skills
	skills->UnsetSkill(m_SkillsMap, "Medium Armor", 10);
	skills->UnsetSkill(m_SkillsMap, "Blunt Weapon", 10);
	skills->UnsetSkill(m_SkillsMap, "Unarmored", 10);
	skills->UnsetSkill(m_SkillsMap, "Athletics", 10);

	skills->UnsetSkill(m_SkillsMap, "Block", 5);
}


void UnitClassWarrior::_defineStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->SetAttribute(m_AttrMap, "Strength", 15);
	attr->SetAttribute(m_AttrMap, "Agility", 5);
	attr->SetAttribute(m_AttrMap, "Intelligence", 5);
	attr->SetAttribute(m_AttrMap, "Willpower", 5);
	attr->SetAttribute(m_AttrMap, "Speed", 15);
	attr->SetAttribute(m_AttrMap, "Endurance", 5);
	attr->SetAttribute(m_AttrMap, "Personality", 5);


	// Skills
	skills->SetSkill(m_SkillsMap, "Medium Armor", 15);
	skills->SetSkill(m_SkillsMap, "Heavy Armor", 15);
	skills->SetSkill(m_SkillsMap, "Athletics", 10);
	skills->SetSkill(m_SkillsMap, "Long Blade", 10);

	skills->SetSkill(m_SkillsMap, "Block", 5);
}

void UnitClassWarrior::_undefStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->UnsetAttribute(m_AttrMap, "Strength", 15);
	attr->UnsetAttribute(m_AttrMap, "Agility", 5);
	attr->UnsetAttribute(m_AttrMap, "Intelligence", 5);
	attr->UnsetAttribute(m_AttrMap, "Willpower", 5);
	attr->UnsetAttribute(m_AttrMap, "Speed", 15);
	attr->UnsetAttribute(m_AttrMap, "Endurance", 5);
	attr->UnsetAttribute(m_AttrMap, "Personality", 5);


	// Skills
	skills->UnsetSkill(m_SkillsMap, "Medium Armor", 15);
	skills->UnsetSkill(m_SkillsMap, "Heavy Armor", 15);
	skills->UnsetSkill(m_SkillsMap, "Athletics", 10);
	skills->UnsetSkill(m_SkillsMap, "Long Blade", 10);

	skills->UnsetSkill(m_SkillsMap, "Block", 5);
}


void UnitClassKnight::_defineStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->SetAttribute(m_AttrMap, "Strength", 20);
	attr->SetAttribute(m_AttrMap, "Agility", 5);
	attr->SetAttribute(m_AttrMap, "Intelligence", 5);
	attr->SetAttribute(m_AttrMap, "Willpower", 5);
	attr->SetAttribute(m_AttrMap, "Speed", 5);
	attr->SetAttribute(m_AttrMap, "Endurance", 15);
	attr->SetAttribute(m_AttrMap, "Personality", 5);


	// Skills
	skills->SetSkill(m_SkillsMap, "Heavy Armor", 15);
	skills->SetSkill(m_SkillsMap, "Athletics", 5);
	skills->SetSkill(m_SkillsMap, "Long Blade", 15);
	skills->SetSkill(m_SkillsMap, "Block", 10);
	skills->SetSkill(m_SkillsMap, "Axe", 10);

	skills->SetSkill(m_SkillsMap, "Restoration", 10);

}

void UnitClassKnight::_undefStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->UnsetAttribute(m_AttrMap, "Strength", 20);
	attr->UnsetAttribute(m_AttrMap, "Agility", 5);
	attr->UnsetAttribute(m_AttrMap, "Intelligence", 5);
	attr->UnsetAttribute(m_AttrMap, "Willpower", 5);
	attr->UnsetAttribute(m_AttrMap, "Speed", 5);
	attr->UnsetAttribute(m_AttrMap, "Endurance", 15);
	attr->UnsetAttribute(m_AttrMap, "Personality", 5);


	// Skills
	skills->UnsetSkill(m_SkillsMap, "Heavy Armor", 15);
	skills->UnsetSkill(m_SkillsMap, "Athletics", 5);
	skills->UnsetSkill(m_SkillsMap, "Long Blade", 15);
	skills->UnsetSkill(m_SkillsMap, "Axe", 10);
	skills->UnsetSkill(m_SkillsMap, "Block", 10);

	skills->UnsetSkill(m_SkillsMap, "Restoration", 10);
}


void UnitClassPaladin::_defineStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->SetAttribute(m_AttrMap, "Strength", 20);
	attr->SetAttribute(m_AttrMap, "Agility", 5);
	attr->SetAttribute(m_AttrMap, "Intelligence", 5);
	attr->SetAttribute(m_AttrMap, "Willpower", 5);
	attr->SetAttribute(m_AttrMap, "Speed", 5);
	attr->SetAttribute(m_AttrMap, "Endurance", 20);
	attr->SetAttribute(m_AttrMap, "Personality", 5);


	// Skills
	skills->SetSkill(m_SkillsMap, "Heavy Armor", 20);
	skills->SetSkill(m_SkillsMap, "Athletics", 5);
	skills->SetSkill(m_SkillsMap, "Long Blade", 20);
	skills->SetSkill(m_SkillsMap, "Block", 15);
	skills->SetSkill(m_SkillsMap, "Blunt Weapon", 15);

	skills->SetSkill(m_SkillsMap, "Restoration", 15);
}

void UnitClassPaladin::_undefStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->UnsetAttribute(m_AttrMap, "Strength", 20);
	attr->UnsetAttribute(m_AttrMap, "Agility", 5);
	attr->UnsetAttribute(m_AttrMap, "Intelligence", 5);
	attr->UnsetAttribute(m_AttrMap, "Willpower", 5);
	attr->UnsetAttribute(m_AttrMap, "Speed", 5);
	attr->UnsetAttribute(m_AttrMap, "Endurance", 20);
	attr->UnsetAttribute(m_AttrMap, "Personality", 5);


	// Skills
	skills->UnsetSkill(m_SkillsMap, "Heavy Armor", 20);
	skills->UnsetSkill(m_SkillsMap, "Athletics", 5);
	skills->UnsetSkill(m_SkillsMap, "Long Blade", 20);
	skills->UnsetSkill(m_SkillsMap, "Block", 15);
	skills->UnsetSkill(m_SkillsMap, "Blunt Weapon", 15);

	skills->UnsetSkill(m_SkillsMap, "Restoration", 15);
}


void UnitClassSpellsword::_defineStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->SetAttribute(m_AttrMap, "Strength", 5);
	attr->SetAttribute(m_AttrMap, "Agility", 5);
	attr->SetAttribute(m_AttrMap, "Intelligence", 5);
	attr->SetAttribute(m_AttrMap, "Willpower", 10);
	attr->SetAttribute(m_AttrMap, "Speed", 5);
	attr->SetAttribute(m_AttrMap, "Endurance", 10);
	attr->SetAttribute(m_AttrMap, "Personality", 5);


	// Skills
	skills->SetSkill(m_SkillsMap, "Medium Armor", 10);
	skills->SetSkill(m_SkillsMap, "Short Blade", 5);
	skills->SetSkill(m_SkillsMap, "Block", 10);

	skills->SetSkill(m_SkillsMap, "Restoration", 10);
	skills->SetSkill(m_SkillsMap, "Destruction", 10);
	skills->SetSkill(m_SkillsMap, "Alteration", 10);

}

void UnitClassSpellsword::_undefStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->UnsetAttribute(m_AttrMap, "Strength", 5);
	attr->UnsetAttribute(m_AttrMap, "Agility", 5);
	attr->UnsetAttribute(m_AttrMap, "Intelligence", 5);
	attr->UnsetAttribute(m_AttrMap, "Willpower", 10);
	attr->UnsetAttribute(m_AttrMap, "Speed", 5);
	attr->UnsetAttribute(m_AttrMap, "Endurance", 10);
	attr->UnsetAttribute(m_AttrMap, "Personality", 5);


	// Skills
	skills->UnsetSkill(m_SkillsMap, "Medium Armor", 10);
	skills->UnsetSkill(m_SkillsMap, "Short Blade", 5);
	skills->UnsetSkill(m_SkillsMap, "Block", 10);

	skills->UnsetSkill(m_SkillsMap, "Restoration", 10);
	skills->UnsetSkill(m_SkillsMap, "Destruction", 10);
	skills->UnsetSkill(m_SkillsMap, "Alteration", 10);
}


void UnitClassBattlemage::_defineStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->SetAttribute(m_AttrMap, "Strength", 10);
	attr->SetAttribute(m_AttrMap, "Agility", 5);
	attr->SetAttribute(m_AttrMap, "Intelligence", 10);
	attr->SetAttribute(m_AttrMap, "Willpower", 5);
	attr->SetAttribute(m_AttrMap, "Speed", 5);
	attr->SetAttribute(m_AttrMap, "Endurance", 5);
	attr->SetAttribute(m_AttrMap, "Personality", 5);


	// Skills
	skills->SetSkill(m_SkillsMap, "Heavy Armor", 15);
	skills->SetSkill(m_SkillsMap, "Axe", 10);
	skills->SetSkill(m_SkillsMap, "Block", 10);

	skills->SetSkill(m_SkillsMap, "Restoration", 15);
	skills->SetSkill(m_SkillsMap, "Destruction", 15);
	skills->SetSkill(m_SkillsMap, "Alteration", 15);
	skills->SetSkill(m_SkillsMap, "Conjuration", 15);

}

void UnitClassBattlemage::_undefStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->UnsetAttribute(m_AttrMap, "Strength", 10);
	attr->UnsetAttribute(m_AttrMap, "Agility", 5);
	attr->UnsetAttribute(m_AttrMap, "Intelligence", 10);
	attr->UnsetAttribute(m_AttrMap, "Willpower", 5);
	attr->UnsetAttribute(m_AttrMap, "Speed", 5);
	attr->UnsetAttribute(m_AttrMap, "Endurance", 5);
	attr->UnsetAttribute(m_AttrMap, "Personality", 5);


	// Skills
	skills->UnsetSkill(m_SkillsMap, "Heavy Armor", 15);
	skills->UnsetSkill(m_SkillsMap, "Axe", 10);
	skills->UnsetSkill(m_SkillsMap, "Block", 10);

	skills->UnsetSkill(m_SkillsMap, "Restoration", 15);
	skills->UnsetSkill(m_SkillsMap, "Destruction", 15);
	skills->UnsetSkill(m_SkillsMap, "Alteration", 15);
	skills->UnsetSkill(m_SkillsMap, "Conjuration", 15);
}


void UnitClassNightblade::_defineStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->SetAttribute(m_AttrMap, "Strength", 5);
	attr->SetAttribute(m_AttrMap, "Agility", 5);
	attr->SetAttribute(m_AttrMap, "Intelligence", 5);
	attr->SetAttribute(m_AttrMap, "Willpower", 15);
	attr->SetAttribute(m_AttrMap, "Speed", 15);
	attr->SetAttribute(m_AttrMap, "Endurance", 5);
	attr->SetAttribute(m_AttrMap, "Personality", 5);


	// Skills
	skills->SetSkill(m_SkillsMap, "Light Armor", 10);
	skills->SetSkill(m_SkillsMap, "Short Blade", 30);
	skills->SetSkill(m_SkillsMap, "Block", 10);

	skills->SetSkill(m_SkillsMap, "Mysticism", 20);
	skills->SetSkill(m_SkillsMap, "Alteration", 15);
	skills->SetSkill(m_SkillsMap, "Conjuration", 20);
}

void UnitClassNightblade::_undefStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->UnsetAttribute(m_AttrMap, "Strength", 5);
	attr->UnsetAttribute(m_AttrMap, "Agility", 5);
	attr->UnsetAttribute(m_AttrMap, "Intelligence", 5);
	attr->UnsetAttribute(m_AttrMap, "Willpower", 15);
	attr->UnsetAttribute(m_AttrMap, "Speed", 15);
	attr->UnsetAttribute(m_AttrMap, "Endurance", 5);
	attr->UnsetAttribute(m_AttrMap, "Personality", 5);


	// Skills
	skills->UnsetSkill(m_SkillsMap, "Light Armor", 10);
	skills->UnsetSkill(m_SkillsMap, "Short Blade", 30);
	skills->UnsetSkill(m_SkillsMap, "Block", 10);

	skills->UnsetSkill(m_SkillsMap, "Mysticism", 20);
	skills->UnsetSkill(m_SkillsMap, "Alteration", 15);
	skills->UnsetSkill(m_SkillsMap, "Conjuration", 20);
}



void UnitClassInquisitor::_defineStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->SetAttribute(m_AttrMap, "Strength", 5);
	attr->SetAttribute(m_AttrMap, "Agility", 15);
	attr->SetAttribute(m_AttrMap, "Intelligence", 15);
	attr->SetAttribute(m_AttrMap, "Willpower", 5);
	attr->SetAttribute(m_AttrMap, "Speed", 5);
	attr->SetAttribute(m_AttrMap, "Endurance", 5);
	attr->SetAttribute(m_AttrMap, "Personality", 5);


	// Skills
	skills->SetSkill(m_SkillsMap, "Light Armor", 20);
	skills->SetSkill(m_SkillsMap, "Blunt Weapon", 10);
	skills->SetSkill(m_SkillsMap, "Block", 20);

	skills->SetSkill(m_SkillsMap, "Mysticism", 20);
	skills->SetSkill(m_SkillsMap, "Conjuration", 20);
}

void UnitClassInquisitor::_undefStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->UnsetAttribute(m_AttrMap, "Strength", 5);
	attr->UnsetAttribute(m_AttrMap, "Agility", 15);
	attr->UnsetAttribute(m_AttrMap, "Intelligence", 15);
	attr->UnsetAttribute(m_AttrMap, "Willpower", 5);
	attr->UnsetAttribute(m_AttrMap, "Speed", 5);
	attr->UnsetAttribute(m_AttrMap, "Endurance", 5);
	attr->UnsetAttribute(m_AttrMap, "Personality", 5);


	// Skills
	skills->UnsetSkill(m_SkillsMap, "Light Armor", 20);
	skills->UnsetSkill(m_SkillsMap, "Blunt Weapon", 10);
	skills->UnsetSkill(m_SkillsMap, "Block", 20);

	skills->UnsetSkill(m_SkillsMap, "Mysticism", 20);
	skills->UnsetSkill(m_SkillsMap, "Conjuration", 20);
}


void UnitClassMage::_defineStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->SetAttribute(m_AttrMap, "Strength", 5);
	attr->SetAttribute(m_AttrMap, "Agility", 5);
	attr->SetAttribute(m_AttrMap, "Intelligence", 10);
	attr->SetAttribute(m_AttrMap, "Willpower", 10);
	attr->SetAttribute(m_AttrMap, "Speed", 5);
	attr->SetAttribute(m_AttrMap, "Endurance", 5);
	attr->SetAttribute(m_AttrMap, "Personality", 5);


	// Skills
	skills->SetSkill(m_SkillsMap, "Mysticism", 10);
	skills->SetSkill(m_SkillsMap, "Conjuration", 10);
	skills->SetSkill(m_SkillsMap, "Alteration", 10);
	skills->SetSkill(m_SkillsMap, "Destruction", 10);
	skills->SetSkill(m_SkillsMap, "Illusion", 10);

	skills->SetSkill(m_SkillsMap, "Restoration", 5);

}

void UnitClassMage::_undefStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->UnsetAttribute(m_AttrMap, "Strength", 5);
	attr->UnsetAttribute(m_AttrMap, "Agility", 5);
	attr->UnsetAttribute(m_AttrMap, "Intelligence", 10);
	attr->UnsetAttribute(m_AttrMap, "Willpower", 10);
	attr->UnsetAttribute(m_AttrMap, "Speed", 5);
	attr->UnsetAttribute(m_AttrMap, "Endurance", 5);
	attr->UnsetAttribute(m_AttrMap, "Personality", 5);


	// Skills
	skills->UnsetSkill(m_SkillsMap, "Mysticism", 10);
	skills->UnsetSkill(m_SkillsMap, "Conjuration", 10);
	skills->UnsetSkill(m_SkillsMap, "Alteration", 10);
	skills->UnsetSkill(m_SkillsMap, "Destruction", 10);
	skills->UnsetSkill(m_SkillsMap, "Illusion", 10);

	skills->UnsetSkill(m_SkillsMap, "Restoration", 5);
}


void UnitClassSorcerer::_defineStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->SetAttribute(m_AttrMap, "Strength", 5);
	attr->SetAttribute(m_AttrMap, "Agility", 5);
	attr->SetAttribute(m_AttrMap, "Intelligence", 10);
	attr->SetAttribute(m_AttrMap, "Willpower", 5);
	attr->SetAttribute(m_AttrMap, "Speed", 5);
	attr->SetAttribute(m_AttrMap, "Endurance", 10);
	attr->SetAttribute(m_AttrMap, "Personality", 5);


	// Skills
	skills->SetSkill(m_SkillsMap, "Mysticism", 10);
	skills->SetSkill(m_SkillsMap, "Conjuration", 15);
	skills->SetSkill(m_SkillsMap, "Alteration", 10);
	skills->SetSkill(m_SkillsMap, "Destruction", 10);
	skills->SetSkill(m_SkillsMap, "Enchant", 10);

	skills->SetSkill(m_SkillsMap, "Restoration", 5);
}

void UnitClassSorcerer::_undefStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->UnsetAttribute(m_AttrMap, "Strength", 5);
	attr->UnsetAttribute(m_AttrMap, "Agility", 5);
	attr->UnsetAttribute(m_AttrMap, "Intelligence", 10);
	attr->UnsetAttribute(m_AttrMap, "Willpower", 5);
	attr->UnsetAttribute(m_AttrMap, "Speed", 5);
	attr->UnsetAttribute(m_AttrMap, "Endurance", 10);
	attr->UnsetAttribute(m_AttrMap, "Personality", 5);


	// Skills
	skills->UnsetSkill(m_SkillsMap, "Mysticism", 10);
	skills->UnsetSkill(m_SkillsMap, "Conjuration", 15);
	skills->UnsetSkill(m_SkillsMap, "Alteration", 10);
	skills->UnsetSkill(m_SkillsMap, "Destruction", 10);
	skills->UnsetSkill(m_SkillsMap, "Enchant", 10);

	skills->UnsetSkill(m_SkillsMap, "Restoration", 5);
}


void UnitClassHealer::_defineStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->SetAttribute(m_AttrMap, "Strength", 5);
	attr->SetAttribute(m_AttrMap, "Agility", 5);
	attr->SetAttribute(m_AttrMap, "Intelligence", 10);
	attr->SetAttribute(m_AttrMap, "Willpower", 15);
	attr->SetAttribute(m_AttrMap, "Speed", 5);
	attr->SetAttribute(m_AttrMap, "Endurance", 5);
	attr->SetAttribute(m_AttrMap, "Personality", 5);


	// Skills
	skills->SetSkill(m_SkillsMap, "Mysticism", 10);
	skills->SetSkill(m_SkillsMap, "Alteration", 10);
	skills->SetSkill(m_SkillsMap, "Destruction", 5);
	skills->SetSkill(m_SkillsMap, "Illusion", 10);

	skills->SetSkill(m_SkillsMap, "Restoration", 15);
	skills->SetSkill(m_SkillsMap, "Block", 5);

}

void UnitClassHealer::_undefStats() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Attributes.
	attr->UnsetAttribute(m_AttrMap, "Strength", 5);
	attr->UnsetAttribute(m_AttrMap, "Agility", 5);
	attr->UnsetAttribute(m_AttrMap, "Intelligence", 10);
	attr->UnsetAttribute(m_AttrMap, "Willpower", 15);
	attr->UnsetAttribute(m_AttrMap, "Speed", 5);
	attr->UnsetAttribute(m_AttrMap, "Endurance", 5);
	attr->UnsetAttribute(m_AttrMap, "Personality", 5);


	// Skills
	skills->UnsetSkill(m_SkillsMap, "Mysticism", 10);
	skills->UnsetSkill(m_SkillsMap, "Alteration", 10);
	skills->UnsetSkill(m_SkillsMap, "Destruction", 5);
	skills->UnsetSkill(m_SkillsMap, "Illusion", 10);

	skills->UnsetSkill(m_SkillsMap, "Restoration", 15);
	skills->UnsetSkill(m_SkillsMap, "Block", 5);

}