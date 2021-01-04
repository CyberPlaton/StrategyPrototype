// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include"UnitDefs.h"


// Map valid ressources for each unit that it produces.
//static std::map<std::string, std::vector<std::string>*> g_pUnitClassRessourceMap;

// Maps each ressource that is made from another, what is made of what.
static std::map<std::string, std::string> g_pRefinedRessourceRawRessourceDemand;

// Vector holds all defined ressources. If it aint here it aint exist...
static std::vector<std::string> g_pIngameRessourcesVec;

std::map<std::string, std::string> GetRefinedRawRessourceDemandMap() {
	return g_pRefinedRessourceRawRessourceDemand;
}

void InitializeUnitClassRessources() {

	// First, define all existent ressources...
	g_pIngameRessourcesVec.push_back("Grapes");
	g_pIngameRessourcesVec.push_back("Alcohol");

	g_pIngameRessourcesVec.push_back("Wood");
	g_pIngameRessourcesVec.push_back("Planks");
	g_pIngameRessourcesVec.push_back("Clay");
	g_pIngameRessourcesVec.push_back("Bricks");
	g_pIngameRessourcesVec.push_back("Food");
	g_pIngameRessourcesVec.push_back("Leather");
	g_pIngameRessourcesVec.push_back("Clothing");
	g_pIngameRessourcesVec.push_back("Raw Stone");
	g_pIngameRessourcesVec.push_back("Stone Blocks");
	g_pIngameRessourcesVec.push_back("Bronze Ore");
	g_pIngameRessourcesVec.push_back("Bronze Bars");
	g_pIngameRessourcesVec.push_back("Iron Bars");
	g_pIngameRessourcesVec.push_back("Iron Ore");
	g_pIngameRessourcesVec.push_back("Steel Bars");
	g_pIngameRessourcesVec.push_back("Adamantium Ore");
	g_pIngameRessourcesVec.push_back("Adamantium Bars");
	g_pIngameRessourcesVec.push_back("Malachite Ore");
	g_pIngameRessourcesVec.push_back("Malachite Bars");
	g_pIngameRessourcesVec.push_back("Bronze Armor");
	g_pIngameRessourcesVec.push_back("Bronze Weapons");
	g_pIngameRessourcesVec.push_back("Iron Armor");
	g_pIngameRessourcesVec.push_back("Iron Weapons");
	g_pIngameRessourcesVec.push_back("Steel Armor");
	g_pIngameRessourcesVec.push_back("Steel Weapons");
	g_pIngameRessourcesVec.push_back("Adamantium Armor");
	g_pIngameRessourcesVec.push_back("Adamantium Weapons");
	g_pIngameRessourcesVec.push_back("Malachite Armor");
	g_pIngameRessourcesVec.push_back("Malachite Weapons");
	g_pIngameRessourcesVec.push_back("Horses");
	g_pIngameRessourcesVec.push_back("Salt");
	g_pIngameRessourcesVec.push_back("Silver Ore");
	g_pIngameRessourcesVec.push_back("Silver Bars");
	g_pIngameRessourcesVec.push_back("Gold Ore");
	g_pIngameRessourcesVec.push_back("Gold Bars");
	g_pIngameRessourcesVec.push_back("Silver Armor");
	g_pIngameRessourcesVec.push_back("Silver Weapons");
	g_pIngameRessourcesVec.push_back("Gold Armor");
	g_pIngameRessourcesVec.push_back("Gold Weapons");
	g_pIngameRessourcesVec.push_back("Jewelry");
	g_pIngameRessourcesVec.push_back("Tools");


	// Special in game ressources like knowledge or direct mooney.
	g_pIngameRessourcesVec.push_back("Denars");
	g_pIngameRessourcesVec.push_back("Civilian Knowledge");
	g_pIngameRessourcesVec.push_back("Military Knowledge");
	g_pIngameRessourcesVec.push_back("Magick Knowledge");
	g_pIngameRessourcesVec.push_back("Technical Knowledge");




	// Second, deifne req. for refined ressources...
	g_pRefinedRessourceRawRessourceDemand.emplace("Alcohol", "Grapes");
	g_pRefinedRessourceRawRessourceDemand.emplace("Clothing", "Leather");
	g_pRefinedRessourceRawRessourceDemand.emplace("Planks", "Wood");
	g_pRefinedRessourceRawRessourceDemand.emplace("Bricks", "Clay");
	g_pRefinedRessourceRawRessourceDemand.emplace("Stone Blocks", "Raw Stone");
	g_pRefinedRessourceRawRessourceDemand.emplace("Bronze Bars", "Bronze Ore");
	g_pRefinedRessourceRawRessourceDemand.emplace("Iron Bars", "Iron Ore");
	g_pRefinedRessourceRawRessourceDemand.emplace("Steel Bars", "Iron Ore");
	g_pRefinedRessourceRawRessourceDemand.emplace("Adamantium Bars", "Adamantium Ore");
	g_pRefinedRessourceRawRessourceDemand.emplace("Malachite Bars", "Malachite Ore");
	g_pRefinedRessourceRawRessourceDemand.emplace("Silver Bars", "Silver Ore");
	g_pRefinedRessourceRawRessourceDemand.emplace("Gold Bars", "Gold Ore");
	g_pRefinedRessourceRawRessourceDemand.emplace("Jewelry", "Silver Bars");
	g_pRefinedRessourceRawRessourceDemand.emplace("Bronze Armor", "Bronze Bars");
	g_pRefinedRessourceRawRessourceDemand.emplace("Bronze Weapons", "Bronze Bars");
	g_pRefinedRessourceRawRessourceDemand.emplace("Iron Armor", "Iron Bars");
	g_pRefinedRessourceRawRessourceDemand.emplace("Iron Weapons", "Iron Bars");
	g_pRefinedRessourceRawRessourceDemand.emplace("Steel Armor", "Steel Bars");
	g_pRefinedRessourceRawRessourceDemand.emplace("Steel Weapons", "Steel Bars");
	g_pRefinedRessourceRawRessourceDemand.emplace("Gold Armor", "Gold Bars");
	g_pRefinedRessourceRawRessourceDemand.emplace("Gold Weapons", "Gold Bars");
	g_pRefinedRessourceRawRessourceDemand.emplace("Adamantium Armor", "Adamantium Bars");
	g_pRefinedRessourceRawRessourceDemand.emplace("Adamantium Weapons", "Adamantium Bars");
	g_pRefinedRessourceRawRessourceDemand.emplace("Malachite Armor", "Malachite Bars");
	g_pRefinedRessourceRawRessourceDemand.emplace("Malachite Weapons", "Malachite Bars");
	g_pRefinedRessourceRawRessourceDemand.emplace("Horses", "Food");
	g_pRefinedRessourceRawRessourceDemand.emplace("Tools", "Bronze Bars");
	g_pRefinedRessourceRawRessourceDemand.emplace("Denars", "Gold Bars");




	/*
	// Lastly, define which ressource what profession creates...
	std::vector<std::string> *vec = new std::vector<std::string>();

	g_pUnitClassRessourceMap.emplace("Citizen", vec);

	vec->push_back("Wood");
	g_pUnitClassRessourceMap.emplace("Woodcutter", vec);
	vec->clear();


	vec->push_back("Food");
	g_pUnitClassRessourceMap.emplace("Farmer", vec);
	vec->clear();


	vec->push_back("Food");
	vec->push_back("Leather");
	g_pUnitClassRessourceMap.emplace("Hunter", vec);
	vec->clear();


	vec->push_back("Food");
	g_pUnitClassRessourceMap.emplace("Fisher", vec);
	vec->clear();


	vec->push_back("Clay");
	g_pUnitClassRessourceMap.emplace("Clayminer", vec);
	vec->clear();


	vec->push_back("Bronze Ore");
	g_pUnitClassRessourceMap.emplace("Bronze Miner", vec);
	vec->clear();


	vec->push_back("Iron Ore");
	g_pUnitClassRessourceMap.emplace("Iron Miner", vec);
	vec->clear();


	vec->push_back("Malachite Ore");
	g_pUnitClassRessourceMap.emplace("Malachite Miner", vec);
	vec->clear();


	vec->push_back("Adamantium Ore");
	g_pUnitClassRessourceMap.emplace("Adamantium Miner", vec);
	vec->clear();


	vec->push_back("Salt");
	g_pUnitClassRessourceMap.emplace("Salt Miner", vec);
	vec->clear();


	vec->push_back("Raw Stone");
	g_pUnitClassRessourceMap.emplace("Stone Miner", vec);
	vec->clear();


	vec->push_back("Planks");
	g_pUnitClassRessourceMap.emplace("Carpenter", vec);
	vec->clear();


	vec->push_back("Bricks");
	g_pUnitClassRessourceMap.emplace("Brick Burner", vec);
	vec->clear();


	vec->push_back("Food");
	g_pUnitClassRessourceMap.emplace("Gatherer", vec);
	vec->clear();


	vec->push_back("Stone Blocks");
	g_pUnitClassRessourceMap.emplace("Mason", vec);
	vec->clear();
	*/
}

void DeinitializeUnitClassRessources() {


	//g_pUnitClassRessourceMap.clear();
	g_pIngameRessourcesVec.clear();
	g_pRefinedRessourceRawRessourceDemand.clear();
}






static std::map<std::string, std::string> g_TechnologyRequirementsMap;


std::string GetTechnologyRequirementsForUnit(UnitBase* unit) {

	return g_TechnologyRequirementsMap.at(unit->m_UnitClassName);
}

std::string GetTechnologyRequirementsForUnit(std::string tech) {

	return g_TechnologyRequirementsMap.at(tech);
}


void DeinitializeUnitTechnologyRequirements() {

	g_TechnologyRequirementsMap.clear();
}

void InitializeUnitTechnologyRequirements() {

	g_TechnologyRequirementsMap.emplace("Citizen", "All");
	g_TechnologyRequirementsMap.emplace("Woodcutter", "Wood Working");
	g_TechnologyRequirementsMap.emplace("Farmer", "Farming");
	g_TechnologyRequirementsMap.emplace("Hunter", "Hunting");
	g_TechnologyRequirementsMap.emplace("Fisher", "Fishing");
	g_TechnologyRequirementsMap.emplace("Clayminer", "All");
	g_TechnologyRequirementsMap.emplace("Bronze Miner", "All");
	g_TechnologyRequirementsMap.emplace("Iron Miner", "All");
	g_TechnologyRequirementsMap.emplace("Malachite Miner", "All");
	g_TechnologyRequirementsMap.emplace("Adamantium Miner", "All");
	g_TechnologyRequirementsMap.emplace("Salt Miner", "All");
	g_TechnologyRequirementsMap.emplace("Stone Miner", "All");
	g_TechnologyRequirementsMap.emplace("Carpenter", "Wood Working");
	g_TechnologyRequirementsMap.emplace("Brick Burner", "Brick Making");
	g_TechnologyRequirementsMap.emplace("Gatherer", "All");
	g_TechnologyRequirementsMap.emplace("Mason", "Stone Working");
	g_TechnologyRequirementsMap.emplace("Aristocrat", "All");
	g_TechnologyRequirementsMap.emplace("Merchant", "All");
	g_TechnologyRequirementsMap.emplace("Magick Researcher", "All");
	g_TechnologyRequirementsMap.emplace("Military Researcher", "All");
	g_TechnologyRequirementsMap.emplace("Technical Researcher", "All");
	g_TechnologyRequirementsMap.emplace("Civilian Researcher", "All");
	g_TechnologyRequirementsMap.emplace("Brewer", "All");
	g_TechnologyRequirementsMap.emplace("Tool Smith", "All");
	g_TechnologyRequirementsMap.emplace("Horse Catcher", "All");
	g_TechnologyRequirementsMap.emplace("Rancher", "All");
	g_TechnologyRequirementsMap.emplace("Goldsmith", "All");
	g_TechnologyRequirementsMap.emplace("Weapon Smith", "All");
	g_TechnologyRequirementsMap.emplace("Armor Smith", "All");
	g_TechnologyRequirementsMap.emplace("Smelter", "All");
	g_TechnologyRequirementsMap.emplace("Tailor", "All");
}



void UnitBase::SetYieldOfRessource(std::string ressource, int yield, UnitRessourceProduction* cmp) {

	for (int i = 0; i < cmp->m_ProducedRessource.size(); i++) {

		if (COMPARE_STRINGS_2(ressource, cmp->m_ProducedRessource[i]) == 0) {

			// Ressource found..
			cmp->m_ProductionYield[i] = yield;
			return;
		}
	}
}

void UnitBase::SetDemandOfRessource(std::string ressource, int demand, UnitRessourceProduction* cmp) {

	for (int i = 0; i < cmp->m_DemandedRawRessourceForProduction.size(); i++) {

		if (COMPARE_STRINGS_2(ressource, cmp->m_DemandedRawRessourceForProduction[i]) == 0) {

			// Ressource found..
			cmp->m_DemandValue[i] = demand;
			return;
		}
	}
}

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