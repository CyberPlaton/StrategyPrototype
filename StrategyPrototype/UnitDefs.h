#pragma once
#include"Platform.h"

enum class UnitSkillsEnum;
enum class UnitAttributesEnum;


std::string SkillToString(UnitSkillsEnum skill);
std::string AttributeToString(UnitAttributesEnum attr);


UnitSkillsEnum SkillStringtoEnum(std::string skill);
UnitAttributesEnum AttributeStringtoEnum(std::string attr);


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
				skillsmap->at(it.first) -= num;
			}
		}
	}

	void SetSkill(std::map<UnitSkillsEnum, int>* skillsmap, std::string skill, int num) {

		UnitSkillsEnum s = SkillStringtoEnum(skill);

		for (auto it : *skillsmap) {
			if (it.first == s) {
				skillsmap->at(it.first) += num;
			}
		}
	}

	//std::map<UnitSkillsEnum, int> m_UnitSkillsMap;
};



struct UnitAttributes {


	void UnsetAttribute(std::map<UnitAttributesEnum, int>* attrmap, std::string attr, int num) {

		UnitAttributesEnum a = AttributeStringtoEnum(attr);

		for (auto it : *attrmap) {
			if (it.first == a) {
				attrmap->at(it.first) -= num;
			}
		}
	}


	void SetAttribute(std::map<UnitAttributesEnum, int>* attrmap, std::string attr, int num) {

		UnitAttributesEnum a = AttributeStringtoEnum(attr);
				
		for (auto it : *attrmap) {
			if (it.first == a) {
				attrmap->at(it.first) += num;
			}
		}
	}

	//std::map<UnitAttributesEnum, int> m_UnitAttributesMap;
};



/*
NOTE: 

On definition we add to unit skills a defined amount of classskills value,
same with attributes.

On class change the unit looses same amount of value as we set it.

Major skills, like the primary ones, give a bonus of 10 to skills.
Minor skills, like the secondary ones, give a bonus of 5 to skills.

Major and minor attributes do the same.
*/
struct UnitClass {


	//UnitAttributes* m_UnitAttributes = nullptr;
	//UnitSkills* m_UnitSkills = nullptr;

	std::string m_UnitClassSpritename = "NULL";
	std::string m_UnitClassName = "NULL";

	bool m_ZoneOfControl = false; // Whether this class-unit has a zoc.
	bool m_IgnoresZoneOfControl = false; // Whether this class-unit ignores another units zoc.
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

		_defineStats();
	}


	~UnitClassArcher() {

		_undefStats();
	}


private:

	// Pointers to units skills and attributes map.
	std::map<UnitSkillsEnum, int>* m_SkillsMap = nullptr;
	std::map<UnitAttributesEnum, int>* m_AttrMap= nullptr;

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

		/*
		// Zero out stats.
		for(auto it: m_UnitAttributes->m_UnitAttributesMap){

			it.second = 0;
		}

		for (auto it : m_UnitSkills->m_UnitSkillsMap) {

			it.second = 0;
		}
		*/


		_defineStats();
	}


	~UnitClassSpy() {

		_undefStats();
	}


private:

	// Pointers to units skills and attributes map.
	std::map<UnitSkillsEnum, int>* m_SkillsMap = nullptr;
	std::map<UnitAttributesEnum, int>* m_AttrMap = nullptr;

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

		/*
		// Zero out stats.
		for(auto it: m_UnitAttributes->m_UnitAttributesMap){

			it.second = 0;
		}

		for (auto it : m_UnitSkills->m_UnitSkillsMap) {

			it.second = 0;
		}
		*/


		_defineStats();
	}


	~UnitClassAssassin() {

		_undefStats();
	}


private:

	// Pointers to units skills and attributes map.
	std::map<UnitSkillsEnum, int>* m_SkillsMap = nullptr;
	std::map<UnitAttributesEnum, int>* m_AttrMap = nullptr;

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

		/*
		// Zero out stats.
		for(auto it: m_UnitAttributes->m_UnitAttributesMap){

			it.second = 0;
		}

		for (auto it : m_UnitSkills->m_UnitSkillsMap) {

			it.second = 0;
		}
		*/


		_defineStats();
	}


	~UnitClassRogue() {

		_undefStats();
	}


private:

	// Pointers to units skills and attributes map.
	std::map<UnitSkillsEnum, int>* m_SkillsMap = nullptr;
	std::map<UnitAttributesEnum, int>* m_AttrMap = nullptr;


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

		/*
		// Zero out stats.
		for(auto it: m_UnitAttributes->m_UnitAttributesMap){

			it.second = 0;
		}

		for (auto it : m_UnitSkills->m_UnitSkillsMap) {

			it.second = 0;
		}
		*/


		_defineStats();
	}


	~UnitClassScout() {

		_undefStats();
	}


private:

	// Pointers to units skills and attributes map.
	std::map<UnitSkillsEnum, int>* m_SkillsMap = nullptr;
	std::map<UnitAttributesEnum, int>* m_AttrMap = nullptr;

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

		/*
		// Zero out stats.
		for(auto it: m_UnitAttributes->m_UnitAttributesMap){

			it.second = 0;
		}

		for (auto it : m_UnitSkills->m_UnitSkillsMap) {

			it.second = 0;
		}
		*/


		_defineStats();
	}


	~UnitClassBarbarian() {

		_undefStats();
	}


private:

	// Pointers to units skills and attributes map.
	std::map<UnitSkillsEnum, int>* m_SkillsMap = nullptr;
	std::map<UnitAttributesEnum, int>* m_AttrMap = nullptr;

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

		/*
		// Zero out stats.
		for(auto it: m_UnitAttributes->m_UnitAttributesMap){

			it.second = 0;
		}

		for (auto it : m_UnitSkills->m_UnitSkillsMap) {

			it.second = 0;
		}
		*/


		_defineStats();
	}


	~UnitClassWarrior() {

		_undefStats();
	}


private:

	// Pointers to units skills and attributes map.
	std::map<UnitSkillsEnum, int>* m_SkillsMap = nullptr;
	std::map<UnitAttributesEnum, int>* m_AttrMap = nullptr;

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

		/*
		// Zero out stats.
		for(auto it: m_UnitAttributes->m_UnitAttributesMap){

			it.second = 0;
		}

		for (auto it : m_UnitSkills->m_UnitSkillsMap) {

			it.second = 0;
		}
		*/


		_defineStats();
	}


	~UnitClassKnight() {

		_undefStats();
	}


private:

	// Pointers to units skills and attributes map.
	std::map<UnitSkillsEnum, int>* m_SkillsMap = nullptr;
	std::map<UnitAttributesEnum, int>* m_AttrMap = nullptr;

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

		/*
		// Zero out stats.
		for(auto it: m_UnitAttributes->m_UnitAttributesMap){

			it.second = 0;
		}

		for (auto it : m_UnitSkills->m_UnitSkillsMap) {

			it.second = 0;
		}
		*/


		_defineStats();
	}


	~UnitClassPaladin() {

		_undefStats();
	}


private:

	// Pointers to units skills and attributes map.
	std::map<UnitSkillsEnum, int>* m_SkillsMap = nullptr;
	std::map<UnitAttributesEnum, int>* m_AttrMap = nullptr;

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

		/*
		// Zero out stats.
		for(auto it: m_UnitAttributes->m_UnitAttributesMap){

			it.second = 0;
		}

		for (auto it : m_UnitSkills->m_UnitSkillsMap) {

			it.second = 0;
		}
		*/


		_defineStats();
	}


	~UnitClassSpellsword() {

		_undefStats();
	}


private:

	// Pointers to units skills and attributes map.
	std::map<UnitSkillsEnum, int>* m_SkillsMap = nullptr;
	std::map<UnitAttributesEnum, int>* m_AttrMap = nullptr;

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

		/*
		// Zero out stats.
		for(auto it: m_UnitAttributes->m_UnitAttributesMap){

			it.second = 0;
		}

		for (auto it : m_UnitSkills->m_UnitSkillsMap) {

			it.second = 0;
		}
		*/


		_defineStats();
	}


	~UnitClassBattlemage() {

		_undefStats();
	}


private:

	// Pointers to units skills and attributes map.
	std::map<UnitSkillsEnum, int>* m_SkillsMap = nullptr;
	std::map<UnitAttributesEnum, int>* m_AttrMap = nullptr;

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

		/*
		// Zero out stats.
		for(auto it: m_UnitAttributes->m_UnitAttributesMap){

			it.second = 0;
		}

		for (auto it : m_UnitSkills->m_UnitSkillsMap) {

			it.second = 0;
		}
		*/


		_defineStats();
	}


	~UnitClassNightblade() {

		_undefStats();
	}


private:

	// Pointers to units skills and attributes map.
	std::map<UnitSkillsEnum, int>* m_SkillsMap = nullptr;
	std::map<UnitAttributesEnum, int>* m_AttrMap = nullptr;

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

		/*
		// Zero out stats.
		for(auto it: m_UnitAttributes->m_UnitAttributesMap){

			it.second = 0;
		}

		for (auto it : m_UnitSkills->m_UnitSkillsMap) {

			it.second = 0;
		}
		*/


		_defineStats();
	}


	~UnitClassInquisitor() {

		_undefStats();
	}


private:

	// Pointers to units skills and attributes map.
	std::map<UnitSkillsEnum, int>* m_SkillsMap = nullptr;
	std::map<UnitAttributesEnum, int>* m_AttrMap = nullptr;

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

		/*
		// Zero out stats.
		for(auto it: m_UnitAttributes->m_UnitAttributesMap){

			it.second = 0;
		}

		for (auto it : m_UnitSkills->m_UnitSkillsMap) {

			it.second = 0;
		}
		*/


		_defineStats();
	}


	~UnitClassMage() {

		_undefStats();
	}


private:

	// Pointers to units skills and attributes map.
	std::map<UnitSkillsEnum, int>* m_SkillsMap = nullptr;
	std::map<UnitAttributesEnum, int>* m_AttrMap = nullptr;

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

		/*
		// Zero out stats.
		for(auto it: m_UnitAttributes->m_UnitAttributesMap){

			it.second = 0;
		}

		for (auto it : m_UnitSkills->m_UnitSkillsMap) {

			it.second = 0;
		}
		*/


		_defineStats();
	}


	~UnitClassSorcerer() {

		_undefStats();
	}


private:

	// Pointers to units skills and attributes map.
	std::map<UnitSkillsEnum, int>* m_SkillsMap = nullptr;
	std::map<UnitAttributesEnum, int>* m_AttrMap = nullptr;

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

		/*
		// Zero out stats.
		for(auto it: m_UnitAttributes->m_UnitAttributesMap){

			it.second = 0;
		}

		for (auto it : m_UnitSkills->m_UnitSkillsMap) {

			it.second = 0;
		}
		*/


		_defineStats();
	}


	~UnitClassHealer() {

		_undefStats();
	}


private:

	// Pointers to units skills and attributes map.
	std::map<UnitSkillsEnum, int>* m_SkillsMap = nullptr;
	std::map<UnitAttributesEnum, int>* m_AttrMap = nullptr;

private:
	void _defineStats();
	void _undefStats();
};