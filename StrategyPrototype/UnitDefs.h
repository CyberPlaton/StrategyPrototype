#pragma once
#include"Platform.h"

// NEW
enum class UnitTier {
	UNIT_TIER_INVALID = -1,
	UNIT_TIER_1 = 1,
	UNIT_TIER_2 = 2,
	UNIT_TIER_3 = 3,
};

enum class UnitLevel {
	UNIT_LEVEL_INVALID = -1,
	UNIT_LEVEL_1 = 1,
	UNIT_LEVEL_2 = 2,
	UNIT_LEVEL_3 = 3,
	UNIT_LEVEL_4 = 4,
	UNIT_LEVEL_5 = 5,
	UNIT_LEVEL_6 = 6,
	UNIT_LEVEL_7 = 7,
	UNIT_LEVEL_8 = 8,
	UNIT_LEVEL_9 = 9,
	UNIT_LEVEL_10 = 10
};

struct UnitStats { // Define maximal health, magicka and fatigue.
	
	size_t m_Health = -1;
	size_t m_Magicka = -1;
	size_t m_Fatigue = -1;
};


struct UnitBase {

	std::string m_UnitClassName;

	UnitTier m_UnitTier = UnitTier::UNIT_TIER_INVALID;
	UnitLevel m_UnitLevel = UnitLevel::UNIT_LEVEL_INVALID;
	UnitStats* m_UnitStats = nullptr;
	std::vector<std::string> m_TechnologyRequirements;


	std::string LevelToString() {

		int level = -1;
		switch (m_UnitLevel) {
		case UnitLevel::UNIT_LEVEL_1:
			level = 1;
				break;
		case UnitLevel::UNIT_LEVEL_2:
			level = 2;

			break;
		case UnitLevel::UNIT_LEVEL_3:
			level = 3;

			break;
		case UnitLevel::UNIT_LEVEL_4:
			level = 4;

			break;
		case UnitLevel::UNIT_LEVEL_5:
			level = 5;

			break;
		case UnitLevel::UNIT_LEVEL_6:
			level = 6;

			break;
		case UnitLevel::UNIT_LEVEL_7:
			level = 7;

			break;
		case UnitLevel::UNIT_LEVEL_8:
			level = 8;

			break;
		case UnitLevel::UNIT_LEVEL_9:
			level = 9;

			break;
		case UnitLevel::UNIT_LEVEL_10:
			level = 10;

			break;

		}

		return (std::to_string(level));
	}
};


struct UnitCitizen : public UnitBase {
	UnitCitizen() {

		m_UnitClassName = "Citizen";

		m_UnitTier = UnitTier::UNIT_TIER_1;
		m_UnitLevel = UnitLevel::UNIT_LEVEL_1;


		m_UnitStats = new UnitStats();
		m_UnitStats->m_Fatigue = 6;
		m_UnitStats->m_Magicka = 0;
		m_UnitStats->m_Health = 10;
	}
};



struct UnitWoodCutter : public UnitBase {
	UnitWoodCutter() {

		m_UnitClassName = "Woodcutter";

		m_UnitTier = UnitTier::UNIT_TIER_1;
		m_UnitLevel = UnitLevel::UNIT_LEVEL_1;


		m_UnitStats = new UnitStats();
		m_UnitStats->m_Fatigue = 6;
		m_UnitStats->m_Magicka = 0;
		m_UnitStats->m_Health = 10;


		m_TechnologyRequirements.push_back("Wood Working");
	}
};



struct UnitFarmer : public UnitBase {
	UnitFarmer() {

		m_UnitClassName = "Farmer";

		m_UnitTier = UnitTier::UNIT_TIER_1;
		m_UnitLevel = UnitLevel::UNIT_LEVEL_1;


		m_UnitStats = new UnitStats();
		m_UnitStats->m_Fatigue = 6;
		m_UnitStats->m_Magicka = 0;
		m_UnitStats->m_Health = 10;

		// No tech req.
	}
};


struct UnitHunter : public UnitBase {
	UnitHunter() {

		m_UnitClassName = "Hunter";

		m_UnitTier = UnitTier::UNIT_TIER_1;
		m_UnitLevel = UnitLevel::UNIT_LEVEL_1;


		m_UnitStats = new UnitStats();
		m_UnitStats->m_Fatigue = 6;
		m_UnitStats->m_Magicka = 0;
		m_UnitStats->m_Health = 10;

		m_TechnologyRequirements.push_back("Hunting");

	}
};


struct UnitFisher : public UnitBase {
	UnitFisher() {

		m_UnitClassName = "Fisher";

		m_UnitTier = UnitTier::UNIT_TIER_1;
		m_UnitLevel = UnitLevel::UNIT_LEVEL_1;


		m_UnitStats = new UnitStats();
		m_UnitStats->m_Fatigue = 6;
		m_UnitStats->m_Magicka = 0;
		m_UnitStats->m_Health = 10;


		m_TechnologyRequirements.push_back("Fishing");
	}
};



struct UnitClayMiner : public UnitBase {
	UnitClayMiner() {

		m_UnitClassName = "Clayminer";

		m_UnitTier = UnitTier::UNIT_TIER_1;
		m_UnitLevel = UnitLevel::UNIT_LEVEL_1;


		m_UnitStats = new UnitStats();
		m_UnitStats->m_Fatigue = 6;
		m_UnitStats->m_Magicka = 0;
		m_UnitStats->m_Health = 10;


		m_TechnologyRequirements.push_back("Pottery");
	}
};


struct UnitBronzeMiner : public UnitBase {
	UnitBronzeMiner() {

		m_UnitClassName = "Bronze Miner";

		m_UnitTier = UnitTier::UNIT_TIER_1;
		m_UnitLevel = UnitLevel::UNIT_LEVEL_1;


		m_UnitStats = new UnitStats();
		m_UnitStats->m_Fatigue = 6;
		m_UnitStats->m_Magicka = 0;
		m_UnitStats->m_Health = 10;


		m_TechnologyRequirements.push_back("Bronze Working");
	}
};



struct UnitIronMiner : public UnitBase {
	UnitIronMiner() {

		m_UnitClassName = "Iron Miner";

		m_UnitTier = UnitTier::UNIT_TIER_1;
		m_UnitLevel = UnitLevel::UNIT_LEVEL_1;


		m_UnitStats = new UnitStats();
		m_UnitStats->m_Fatigue = 6;
		m_UnitStats->m_Magicka = 0;
		m_UnitStats->m_Health = 10;


		m_TechnologyRequirements.push_back("Iron Working");
	}
};



// OLD

/*
enum class UnitSkillsEnum;
enum class UnitAttributesEnum;
enum class UnitClassTier;


std::string SkillToString(UnitSkillsEnum skill);
std::string AttributeToString(UnitAttributesEnum attr);


UnitSkillsEnum SkillStringtoEnum(std::string skill);
UnitAttributesEnum AttributeStringtoEnum(std::string attr);


int GetMultiplierFromUnitClassTier(UnitClassTier tier);


enum class UnitClassTier {
	UNIT_CLASS_TIER_INVALID = -1,
	UNIT_CLASS_TIER_0 = 0,
	UNIT_CLASS_TIER_1 = 1,
	UNIT_CLASS_TIER_2 = 2,
	UNIT_CLASS_TIER_3 = 3,
	UNIT_CLASS_TIER_4 = 4
};

struct MajorMinorSkills {

	std::string m_MajorAttribute1;
	std::string m_MajorAttribute2;
	std::string m_MajorSkill1;
	std::string m_MajorSkill2;
	std::string m_MajorSkill3;

	std::string m_MinorSkill1;
	std::string m_MinorSkill2;
	std::string m_MinorSkill3;
	std::string m_MinorSkill4;
	std::string m_MinorSkill5;
};


enum class UnitSkillsEnum {
	UNIT_SKILL_INVALID = -1,

	UNIT_SKILL_HEAVY_ARMOR = 0,
	UNIT_SKILL_MEDIUM_ARMOR = 1,
	UNIT_SKILL_LIGHT_ARMOR = 2,
	UNIT_SKILL_SPEAR = 3,
	UNIT_SKILL_AXE = 4,
	UNIT_SKILL_BLUNT_WEAPON = 5,
	UNIT_SKILL_LONG_BLADE = 6,
	UNIT_SKILL_SHORT_BLADE = 7,
	UNIT_SKILL_BLOCK = 8,
	UNIT_SKILL_MARKSMAN = 9,
	UNIT_SKILL_ACROBATICS = 10,
	UNIT_SKILL_ATHLETICS = 11,
	UNIT_SKILL_SNEAK = 12,
	UNIT_SKILL_UNARMORED = 13,
	UNIT_SKILL_ILLUSION = 14,
	UNIT_SKILL_MERCANTILE = 15,
	UNIT_SKILL_SPEECHCRAFT = 16,
	UNIT_SKILL_ALCHEMY = 17,
	UNIT_SKILL_CONJURATION = 18,
	UNIT_SKILL_ENCHANT = 19,
	UNIT_SKILL_ALTERATION = 20,
	UNIT_SKILL_DESTRUCTION = 21,
	UNIT_SKILL_MYSTICISM = 22,
	UNIT_SKILL_RESTORATION = 23
};


enum class UnitAttributesEnum {

	UNIT_ATTRIBUTE_INVALID = -1,
	UNIT_ATTRIBUTE_STRENGTH = 0,
	UNIT_ATTRIBUTE_INTELLIGENCE = 1,
	UNIT_ATTRIBUTE_WILLPOWER = 2,
	UNIT_ATTRIBUTE_AGILITY = 3,
	UNIT_ATTRIBUTE_SPEED = 4,
	UNIT_ATTRIBUTE_ENDURANCE = 5,
	UNIT_ATTRIBUTE_PERSONALITY = 6,

	UNIT_ATTRIBUTE_HEALTH = 7,
	UNIT_ATTRIBUTE_MAGICKA = 8,
	UNIT_ATTRIBUTE_FATIGUE = 9
};


struct UnitSkills {

	void UnsetSkill(std::map<UnitSkillsEnum, int>* skillsmap, std::string skill, int num) {

		UnitSkillsEnum s = SkillStringtoEnum(skill);

		for (auto it : *skillsmap) {
			if (it.first == s) {

				// We define every skill to be >= 5.
				// Thus, check for it.
				if ((skillsmap->at(it.first) -= num) < 5) {
					skillsmap->at(it.first) = 5;
				}
				else {
					skillsmap->at(it.first) -= num;
				}
			}
		}
	}

	void SetSkill(std::map<UnitSkillsEnum, int>* skillsmap, std::string skill, int num) {

		UnitSkillsEnum s = SkillStringtoEnum(skill);

		for (auto it : *skillsmap) {
			if (it.first == s) {


				// We define the maximum for a skill as 100.
				// Thus, check for it.
				if ((skillsmap->at(it.first) += num) > 100) {
					skillsmap->at(it.first) = 100;
				}
				else {
					skillsmap->at(it.first) += num;
				}
			}
		}
	}
};



struct UnitAttributes {


	void UnsetAttribute(std::map<UnitAttributesEnum, int>* attrmap, std::string attr, int num) {

		UnitAttributesEnum a = AttributeStringtoEnum(attr);

		for (auto it : *attrmap) {
			if (it.first == a) {

				// We define every attr to be >= 5.
				// Thus, check for it.
				if ((attrmap->at(it.first) -= num) < 5) {
					attrmap->at(it.first) = 5;
				}
				else {
					attrmap->at(it.first) -= num;
				}
			}
		}
	}


	void SetAttribute(std::map<UnitAttributesEnum, int>* attrmap, std::string attr, int num) {

		UnitAttributesEnum a = AttributeStringtoEnum(attr);
				
		for (auto it : *attrmap) {
			if (it.first == a) {

				// We define the maximum for a skill as 100.
				// Thus, check for it.
				if ((attrmap->at(it.first) += num) > 100) {
					attrmap->at(it.first) = 100;
				}
				else {
					attrmap->at(it.first) += num;
				}
			}
		}
	}
};



struct UnitClass {

	std::string m_UnitClassSpritename = "NULL";
	std::string m_UnitClassName = "NULL";

	bool m_ZoneOfControl = false; // Whether this class-unit has a zoc.
	bool m_IgnoresZoneOfControl = false; // Whether this class-unit ignores another units zoc.


	UnitClassTier m_ClassTier = UnitClassTier::UNIT_CLASS_TIER_INVALID;

	// Pointers to units skills and attributes map.
	std::map<UnitSkillsEnum, int>* m_SkillsMap = nullptr;
	std::map<UnitAttributesEnum, int>* m_AttrMap = nullptr;

	void _setMajorSkillsAttributes(std::string major_attr1, std::string major_attr2,
		std::string major_skill1, std::string major_skill2, std::string major_skill3);

	void _setMinorSkillsAttributes(std::string minor_skill1, std::string minor_skill2,
		std::string minor_skill3, std::string minor_skill4, std::string minor_skill5);

	void _unsetMajorSkillsAttributes(std::string major_attr1, std::string major_attr2,
		std::string major_skill1, std::string major_skill2, std::string major_skill3);

	void _unsetMinorSkillsAttributes(std::string minor_skill1, std::string minor_skill2,
		std::string minor_skill3, std::string minor_skill4, std::string minor_skill5);


	// Function for training skills/attributes defined as Major/Minor for this class.
	void _trainSkills();
	void _trainAttributes();

	// Used for training functions.
	MajorMinorSkills* m_MajorMinorSkillsDefs;
};



// CLASSES DEFINITIONS
// 1.) Support classes.
struct UnitClassArcher : public UnitClass {
	UnitClassArcher(std::map<UnitSkillsEnum, int>* skillsmap,
		std::map<UnitAttributesEnum, int>* attrmap) {

		m_ZoneOfControl = true;
		m_IgnoresZoneOfControl = false;

		m_AttrMap = attrmap;
		m_SkillsMap = skillsmap;

		// For drawing class ribbon.
		m_UnitClassSpritename = "unit_class_archer";
		m_UnitClassName = "Archer";


		m_ClassTier = UnitClassTier::UNIT_CLASS_TIER_0;

		_defineStats();
	}


	~UnitClassArcher() {

		_undefStats();
	}


private:

private:
	void _defineStats();
	void _undefStats();
};



struct UnitClassSpy : public UnitClass {
	UnitClassSpy(std::map<UnitSkillsEnum, int>* skillsmap,
		std::map<UnitAttributesEnum, int>* attrmap) {

		m_ZoneOfControl = false;
		m_IgnoresZoneOfControl = true;

		m_AttrMap = attrmap;
		m_SkillsMap = skillsmap;

		// For drawing class ribbon.
		m_UnitClassSpritename = "unit_class_spy";
		m_UnitClassName = "Spy";

		_defineStats();
	}


	~UnitClassSpy() {

		_undefStats();
	}


private:

private:
	void _defineStats();
	void _undefStats();
};



struct UnitClassAssassin : public UnitClass {
	UnitClassAssassin(std::map<UnitSkillsEnum, int>* skillsmap,
		std::map<UnitAttributesEnum, int>* attrmap) {

		m_ZoneOfControl = false;
		m_IgnoresZoneOfControl = true;

		m_AttrMap = attrmap;
		m_SkillsMap = skillsmap;

		// For drawing class ribbon.
		m_UnitClassSpritename = "unit_class_assassin";
		m_UnitClassName = "Assassin";

		_defineStats();
	}


	~UnitClassAssassin() {

		_undefStats();
	}


private:

private:
	void _defineStats();
	void _undefStats();
};



struct UnitClassRogue : public UnitClass {
	UnitClassRogue(std::map<UnitSkillsEnum, int>* skillsmap,
		std::map<UnitAttributesEnum, int>* attrmap) {

		m_ZoneOfControl = false;
		m_IgnoresZoneOfControl = true;

		m_AttrMap = attrmap;
		m_SkillsMap = skillsmap;

		// For drawing class ribbon.
		m_UnitClassSpritename = "unit_class_rogue";
		m_UnitClassName = "Rogue";

		_defineStats();
	}


	~UnitClassRogue() {

		_undefStats();
	}


private:

private:
	void _defineStats();
	void _undefStats();

};



struct UnitClassScout : public UnitClass {
	UnitClassScout(std::map<UnitSkillsEnum, int>* skillsmap,
		std::map<UnitAttributesEnum, int>* attrmap) {

		m_ZoneOfControl = false;
		m_IgnoresZoneOfControl = true;

		m_AttrMap = attrmap;
		m_SkillsMap = skillsmap;

		// For drawing class ribbon.
		m_UnitClassSpritename = "unit_class_scout";
		m_UnitClassName = "Scout";

		_defineStats();
	}


	~UnitClassScout() {

		_undefStats();
	}


private:

private:
	void _defineStats();
	void _undefStats();
};


// 2.) Fighters - Melee.

struct UnitClassBarbarian : public UnitClass {
	UnitClassBarbarian(std::map<UnitSkillsEnum, int>* skillsmap,
		std::map<UnitAttributesEnum, int>* attrmap) {

		m_ZoneOfControl = false;
		m_IgnoresZoneOfControl = false;

		m_AttrMap = attrmap;
		m_SkillsMap = skillsmap;

		// For drawing class ribbon.
		m_UnitClassSpritename = "unit_class_barbarian";
		m_UnitClassName = "Barbarian";

		_defineStats();
	}


	~UnitClassBarbarian() {

		_undefStats();
	}


private:


private:
	void _defineStats();
	void _undefStats();
};



struct UnitClassWarrior : public UnitClass {
	UnitClassWarrior(std::map<UnitSkillsEnum, int>* skillsmap,
		std::map<UnitAttributesEnum, int>* attrmap) {

		m_ZoneOfControl = true;
		m_IgnoresZoneOfControl = false;

		m_AttrMap = attrmap;
		m_SkillsMap = skillsmap;

		// For drawing class ribbon.
		m_UnitClassSpritename = "unit_class_warrior";
		m_UnitClassName = "Warrior";

		_defineStats();
	}


	~UnitClassWarrior() {

		_undefStats();
	}


private:

private:
	void _defineStats();
	void _undefStats();
};


struct UnitClassKnight : public UnitClass {
	UnitClassKnight(std::map<UnitSkillsEnum, int>* skillsmap,
		std::map<UnitAttributesEnum, int>* attrmap) {

		m_ZoneOfControl = true;
		m_IgnoresZoneOfControl = false;

		m_AttrMap = attrmap;
		m_SkillsMap = skillsmap;

		// For drawing class ribbon.
		m_UnitClassSpritename = "unit_class_knight";
		m_UnitClassName = "Knight";

		_defineStats();
	}


	~UnitClassKnight() {

		_undefStats();
	}


private:


private:
	void _defineStats();
	void _undefStats();
};


struct UnitClassPaladin : public UnitClass {
	UnitClassPaladin(std::map<UnitSkillsEnum, int>* skillsmap,
		std::map<UnitAttributesEnum, int>* attrmap) {

		m_ZoneOfControl = true;
		m_IgnoresZoneOfControl = false;

		m_AttrMap = attrmap;
		m_SkillsMap = skillsmap;

		// For drawing class ribbon.
		m_UnitClassSpritename = "unit_class_paladin";
		m_UnitClassName = "Paladin";

		_defineStats();
	}


	~UnitClassPaladin() {

		_undefStats();
	}


private:

private:
	void _defineStats();
	void _undefStats();
};



// 3.) Battlemages.

struct UnitClassSpellsword : public UnitClass {
	UnitClassSpellsword(std::map<UnitSkillsEnum, int>* skillsmap,
		std::map<UnitAttributesEnum, int>* attrmap) {

		m_ZoneOfControl = true;
		m_IgnoresZoneOfControl = false;

		m_AttrMap = attrmap;
		m_SkillsMap = skillsmap;

		// For drawing class ribbon.
		m_UnitClassSpritename = "unit_class_spellsword";
		m_UnitClassName = "Spellsword";

		_defineStats();
	}


	~UnitClassSpellsword() {

		_undefStats();
	}


private:

private:
	void _defineStats();
	void _undefStats();
};



struct UnitClassBattlemage : public UnitClass {
	UnitClassBattlemage(std::map<UnitSkillsEnum, int>* skillsmap,
		std::map<UnitAttributesEnum, int>* attrmap) {

		m_ZoneOfControl = true;
		m_IgnoresZoneOfControl = false;

		m_AttrMap = attrmap;
		m_SkillsMap = skillsmap;

		// For drawing class ribbon.
		m_UnitClassSpritename = "unit_class_battlemage";
		m_UnitClassName = "Battlemage";

		_defineStats();
	}


	~UnitClassBattlemage() {

		_undefStats();
	}


private:

private:
	void _defineStats();
	void _undefStats();
};



struct UnitClassNightblade : public UnitClass {
	UnitClassNightblade(std::map<UnitSkillsEnum, int>* skillsmap,
		std::map<UnitAttributesEnum, int>* attrmap) {

		m_ZoneOfControl = false;
		m_IgnoresZoneOfControl = true;

		m_AttrMap = attrmap;
		m_SkillsMap = skillsmap;

		// For drawing class ribbon.
		m_UnitClassSpritename = "unit_class_nightblade";
		m_UnitClassName = "Nightblade";

		_defineStats();
	}


	~UnitClassNightblade() {

		_undefStats();
	}


private:

private:
	void _defineStats();
	void _undefStats();
};


struct UnitClassInquisitor : public UnitClass {
	UnitClassInquisitor(std::map<UnitSkillsEnum, int>* skillsmap,
		std::map<UnitAttributesEnum, int>* attrmap) {

		m_ZoneOfControl = false;
		m_IgnoresZoneOfControl = true;

		m_AttrMap = attrmap;
		m_SkillsMap = skillsmap;

		// For drawing class ribbon.
		m_UnitClassSpritename = "unit_class_inquisitor";
		m_UnitClassName = "Inquisitor";

		_defineStats();
	}


	~UnitClassInquisitor() {

		_undefStats();
	}


private:


private:
	void _defineStats();
	void _undefStats();
};


// 4.) Mages.

struct UnitClassMage : public UnitClass {
	UnitClassMage(std::map<UnitSkillsEnum, int>* skillsmap,
		std::map<UnitAttributesEnum, int>* attrmap) {

		m_ZoneOfControl = false;
		m_IgnoresZoneOfControl = false;

		m_AttrMap = attrmap;
		m_SkillsMap = skillsmap;

		// For drawing class ribbon.
		m_UnitClassSpritename = "unit_class_mage";
		m_UnitClassName = "Mage";

		_defineStats();
	}


	~UnitClassMage() {

		_undefStats();
	}


private:



private:
	void _defineStats();
	void _undefStats();

};


struct UnitClassSorcerer : public UnitClass {
	UnitClassSorcerer(std::map<UnitSkillsEnum, int>* skillsmap,
		std::map<UnitAttributesEnum, int>* attrmap) {

		m_ZoneOfControl = false;
		m_IgnoresZoneOfControl = false;

		m_AttrMap = attrmap;
		m_SkillsMap = skillsmap;

		// For drawing class ribbon.
		m_UnitClassSpritename = "unit_class_sorcerer";
		m_UnitClassName = "Sorcerer";

		_defineStats();
	}


	~UnitClassSorcerer() {

		_undefStats();
	}


private:


private:
	void _defineStats();
	void _undefStats();
};


struct UnitClassHealer : public UnitClass {
	UnitClassHealer(std::map<UnitSkillsEnum, int>* skillsmap,
		std::map<UnitAttributesEnum, int>* attrmap) {

		m_ZoneOfControl = false;
		m_IgnoresZoneOfControl = false;

		m_AttrMap = attrmap;
		m_SkillsMap = skillsmap;

		// For drawing class ribbon.
		m_UnitClassSpritename = "unit_class_healer";
		m_UnitClassName = "Healer";

		_defineStats();
	}


	~UnitClassHealer() {

		_undefStats();
	}


private:


private:
	void _defineStats();
	void _undefStats();

};



// Civilian Unit classes.
// Those define not stats, but "abilities", means
// what can this type of unit do, like
// builder can build imporovements, forest chop down trees etc.
// Further civilian units got a "level" of theyre work and it gives certain bonuses...

struct UnitClassCitizen : public UnitClass {
	UnitClassCitizen(std::map<UnitSkillsEnum, int>* skillsmap,
		std::map<UnitAttributesEnum, int>* attrmap) {

		m_ZoneOfControl = false;
		m_IgnoresZoneOfControl = false;

		m_AttrMap = attrmap;
		m_SkillsMap = skillsmap;

		// For drawing class ribbon.
		m_UnitClassSpritename = "unit_class_citizen";
		m_UnitClassName = "Citizen";

		_defineStats();
	}


	~UnitClassCitizen() {

		_undefStats();
	}


private:

	// Pointers to units skills and attributes map.
	std::map<UnitSkillsEnum, int>* m_SkillsMap = nullptr;
	std::map<UnitAttributesEnum, int>* m_AttrMap = nullptr;

private:
	void _defineStats() {

	}

	void _undefStats() {

	}
};
*/