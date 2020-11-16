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
	UNIT_ATTRIBUTE_PERSONALITY = 6
};


struct UnitSkills {

	void UnsetSkill(std::string skill, int num) {

		UnitSkillsEnum s = SkillStringtoEnum(skill);

		for (auto it : m_UnitSkillsMap) {
			if (it.first == s) {
				m_UnitSkillsMap.at(it.first) -= num;
			}
		}
	}

	void SetSkill(std::string skill, int num) {

		UnitSkillsEnum s = SkillStringtoEnum(skill);

		for (auto it : m_UnitSkillsMap) {
			if (it.first == s) {
				m_UnitSkillsMap.at(it.first) += num;
			}
		}
	}

	std::map<UnitSkillsEnum, int> m_UnitSkillsMap;
};


struct UnitAttributes {


	void UnsetAttribute(std::string attr, int num) {

		UnitAttributesEnum a = AttributeStringtoEnum(attr);

		for (auto it : m_UnitAttributesMap) {
			if (it.first == a) {
				m_UnitAttributesMap.at(it.first) -= num;
			}
		}
	}


	void SetAttribute(std::string attr, int num) {

		UnitAttributesEnum a = AttributeStringtoEnum(attr);
				
		for (auto it : m_UnitAttributesMap) {
			if (it.first == a) {
				m_UnitAttributesMap.at(it.first) += num;
			}
		}
	}

	std::map<UnitAttributesEnum, int> m_UnitAttributesMap;
};


struct UnitClass {

	UnitAttributes* m_UnitAttributes = nullptr;
	UnitSkills* m_UnitSkills = nullptr;

	std::string m_UnitClassSpritename = "NULL";
	std::string m_UnitClassName = "NULL";
};


struct UnitClassArcher : public UnitClass {
	UnitClassArcher() {

		m_UnitAttributes = new UnitAttributes();
		m_UnitSkills = new UnitSkills();

		// For drawing class ribbon.
		m_UnitClassSpritename = "unit_class_archer";
		m_UnitClassName = "Archer";

		// Zero out stats.
		for(auto it: m_UnitAttributes->m_UnitAttributesMap){
			
			it.second = 0;
		}

		for (auto it : m_UnitSkills->m_UnitSkillsMap) {

			it.second = 0;
		}


		_defineStats();
	}


	~UnitClassArcher() {

		_undefStats();
	}


private:


private:
	void _defineStats() {


		// Attributes.
		m_UnitAttributes->SetAttribute("Strength", 30);
		m_UnitAttributes->SetAttribute("Agility", 30);
		m_UnitAttributes->SetAttribute("Intelligence", 10);
		m_UnitAttributes->SetAttribute("Willpower", 10);
		m_UnitAttributes->SetAttribute("Agility", 10);
		m_UnitAttributes->SetAttribute("Speed", 10);
		m_UnitAttributes->SetAttribute("Endurance", 10);
		m_UnitAttributes->SetAttribute("Personality", 10);

		// Skills.
		m_UnitSkills->SetSkill("Heavy Armor", 1);
		m_UnitSkills->SetSkill("Light Armor", 20);
		m_UnitSkills->SetSkill("Medium Armor", 10);
		m_UnitSkills->SetSkill("Spear", 10);
		m_UnitSkills->SetSkill("Axe", 1);
		m_UnitSkills->SetSkill("Blunt Weapon", 1);
		m_UnitSkills->SetSkill("Long Blade", 20);
		m_UnitSkills->SetSkill("Short Blade", 1);
		m_UnitSkills->SetSkill("Block", 20);
		m_UnitSkills->SetSkill("Marksman", 20);
		m_UnitSkills->SetSkill("Acrobatics", 1);
		m_UnitSkills->SetSkill("Athletics", 20);
		m_UnitSkills->SetSkill("Sneak", 1);
		m_UnitSkills->SetSkill("Unarmored", 10);
		m_UnitSkills->SetSkill("Illusion", 1);
		m_UnitSkills->SetSkill("Mercantile", 1);
		m_UnitSkills->SetSkill("Speechcraft", 1);
		m_UnitSkills->SetSkill("Alchemy", 1);
		m_UnitSkills->SetSkill("Conjuration", 1);
		m_UnitSkills->SetSkill("Enchant", 1);
		m_UnitSkills->SetSkill("Alteration", 1);
		m_UnitSkills->SetSkill("Destruction", 1);
		m_UnitSkills->SetSkill("Restoration", 10);

	}


	void _undefStats() {

		// Attributes.
		m_UnitAttributes->UnsetAttribute("Strength", 30);
		m_UnitAttributes->UnsetAttribute("Agility", 30);
		m_UnitAttributes->UnsetAttribute("Intelligence", 10);
		m_UnitAttributes->UnsetAttribute("Willpower", 10);
		m_UnitAttributes->UnsetAttribute("Agility", 10);
		m_UnitAttributes->UnsetAttribute("Speed", 10);
		m_UnitAttributes->UnsetAttribute("Endurance", 10);
		m_UnitAttributes->UnsetAttribute("Personality", 10);

		// Skills.
		m_UnitSkills->UnsetSkill("Heavy Armor", 1);
		m_UnitSkills->UnsetSkill("Light Armor", 20);
		m_UnitSkills->UnsetSkill("Medium Armor", 10);
		m_UnitSkills->UnsetSkill("Spear", 10);
		m_UnitSkills->UnsetSkill("Axe", 1);
		m_UnitSkills->UnsetSkill("Blunt Weapon", 1);
		m_UnitSkills->UnsetSkill("Long Blade", 20);
		m_UnitSkills->UnsetSkill("Short Blade", 1);
		m_UnitSkills->UnsetSkill("Block", 20);
		m_UnitSkills->UnsetSkill("Marksman", 20);
		m_UnitSkills->UnsetSkill("Acrobatics", 1);
		m_UnitSkills->UnsetSkill("Athletics", 20);
		m_UnitSkills->UnsetSkill("Sneak", 1);
		m_UnitSkills->UnsetSkill("Unarmored", 10);
		m_UnitSkills->UnsetSkill("Illusion", 1);
		m_UnitSkills->UnsetSkill("Mercantile", 1);
		m_UnitSkills->UnsetSkill("Speechcraft", 1);
		m_UnitSkills->UnsetSkill("Alchemy", 1);
		m_UnitSkills->UnsetSkill("Conjuration", 1);
		m_UnitSkills->UnsetSkill("Enchant", 1);
		m_UnitSkills->UnsetSkill("Alteration", 1);
		m_UnitSkills->UnsetSkill("Destruction", 1);
		m_UnitSkills->UnsetSkill("Restoration", 10);
	}
};