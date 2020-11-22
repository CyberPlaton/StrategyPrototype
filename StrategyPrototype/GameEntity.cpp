#include "GameEntity.h"

EntitiesStorage* EntitiesStorage::m_EntitiesStorage = nullptr;
WorldMap* WorldMap::m_WorldMapInstance = nullptr;


void Unit::_defineUnitName() {

	switch (m_EntityRaceCmp->m_EntityRace) {
	case CMPEntityRace::Race::RACE_INVALID:
		break;
	case CMPEntityRace::Race::RACE_HUMAN:
		m_Name = UnitNames::Get()->GetRandomHumanName();
		break;
	case CMPEntityRace::Race::RACE_TROLL:
		m_Name = UnitNames::Get()->GetRandomTrollName();

		break;
	case CMPEntityRace::Race::RACE_DWARF:
		m_Name = UnitNames::Get()->GetRandomDwarfName();

		break;
	case CMPEntityRace::Race::RACE_ORC:
		m_Name = UnitNames::Get()->GetRandomOrcName();

		break;
	case CMPEntityRace::Race::RACE_HIGHELF:
		m_Name = UnitNames::Get()->GetRandomHighelfName();

		break;
	case CMPEntityRace::Race::RACE_DARKELF:
		m_Name = UnitNames::Get()->GetRandomDarkelfName();

		break;
	case CMPEntityRace::Race::RACE_GOBLIN:
		m_Name = UnitNames::Get()->GetRandomGoblinName();

		break;
	case CMPEntityRace::Race::RACE_GNOME:
		m_Name = UnitNames::Get()->GetRandomGnomeName();

		break;
	default:
		break;
	}
	

}


bool Unit::SetDerivedStats() {

	if (this->m_EntityRaceCmp == nullptr) return false;
	if (COMPARE_STRINGS(m_Birthsign, "NULL") == 0) return false;
	if (m_UnitClass == nullptr) return false;


	_defineStatsBasedOnUnitRace();
	_defineStatsBasedOnUnitBirthsign();
	_defineDerivedAttributes();

	return true;
}

void Unit::_defineRandomUnitTalents() {

	// NOTE:
	// We define 1 attribute and 1 skill to be increased or decreased with 0-5 Points.
	// Samewise, we do the same with 1 other attribute and 1 other skill, but revert the value...

	using namespace std;

	// Randomize attributes
	int random_index_attr = Random() % GetUnitAttributes()->size();
	int random_index_attr_2 = Random() % GetUnitAttributes()->size();


	// Randomize skills
	int random_index_skills = Random() % GetUnitSkills()->size();
	int random_index_skills_2 = Random() % GetUnitSkills()->size();



	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();


	int random_value = 1 + Random() % 6;
	int random_direction = random_value % 2;

	if (random_direction == 0) {
		random_value = (-random_value);


		// Attribute 1
		UnitAttributesEnum a = UnitAttributesEnum(random_index_attr);
		attr->SetAttribute(GetUnitAttributes(), AttributeToString(a), random_value);

		// Skill 1
		UnitSkillsEnum s = UnitSkillsEnum(random_index_skills);
		skills->SetSkill(GetUnitSkills(), SkillToString(s), random_value);


		// Attribute 2
		UnitAttributesEnum aa = UnitAttributesEnum(random_index_attr_2);
		attr->SetAttribute(GetUnitAttributes(), AttributeToString(aa), -random_value);

		// Skill 2
		UnitSkillsEnum ss = UnitSkillsEnum(random_index_skills_2);
		skills->SetSkill(GetUnitSkills(), SkillToString(ss), -random_value);


		cout << color(colors::DARKRED) << endl;
		cout << "Random Talent: Attribute \"" << AttributeToString(a) << "\" ::= " << std::to_string(random_value) << endl;
		cout << "Random Talent: Skill \"" << SkillToString(s) << "\" ::= " << std::to_string(random_value) << endl;
		cout << "Random Talent: Attribute \"" << AttributeToString(aa) << "\" ::= " << std::to_string(-random_value) << endl;
		cout << "Random Talent: Skill \"" << SkillToString(ss) << "\" ::= " << std::to_string(-random_value) << endl;
		cout << white << endl;


	}
	else {

		// Attribute 1
		UnitAttributesEnum a = UnitAttributesEnum(random_index_attr);
		attr->SetAttribute(GetUnitAttributes(), AttributeToString(a), random_value);

		// Skill 1
		UnitSkillsEnum s = UnitSkillsEnum(random_index_skills);
		skills->SetSkill(GetUnitSkills(), SkillToString(s), random_value);


		// Attribute 2
		UnitAttributesEnum aa = UnitAttributesEnum(random_index_attr_2);
		attr->SetAttribute(GetUnitAttributes(), AttributeToString(aa), -random_value);

		// Skill 2
		UnitSkillsEnum ss = UnitSkillsEnum(random_index_skills_2);
		skills->SetSkill(GetUnitSkills(), SkillToString(ss), -random_value);


		cout << color(colors::DARKRED) << endl;
		cout << "Random Talent: Attribute \"" << AttributeToString(a) << "\" ::= " << std::to_string(random_value) << endl;
		cout << "Random Talent: Skill \"" << SkillToString(s) << "\" ::= " << std::to_string(random_value) << endl;
		cout << "Random Talent: Attribute \"" << AttributeToString(aa) << "\" ::= " << std::to_string(-random_value) << endl;
		cout << "Random Talent: Skill \"" << SkillToString(ss) << "\" ::= " << std::to_string(-random_value) << endl;
		cout << white << endl;
	}

}

GameEntity::~GameEntity() {

	delete m_IDCmp; m_IDCmp = nullptr;
	delete m_TransformCmp; m_TransformCmp = nullptr;
	delete m_PhysicsCmp; m_PhysicsCmp = nullptr;
	delete m_GraphicsCmp; m_GraphicsCmp = nullptr;
	delete m_FSM; m_FSM = nullptr;
	delete m_MovementCostCmp; m_MovementCostCmp = nullptr;
	delete m_EntityRaceCmp; m_EntityRaceCmp = nullptr;
}


void Unit::_defineStandardBeginningStats() {

	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_HEAVY_ARMOR, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_MEDIUM_ARMOR, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_LIGHT_ARMOR, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_SPEAR, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_AXE, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_BLUNT_WEAPON, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_LONG_BLADE, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_SHORT_BLADE, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_BLOCK, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_MARKSMAN, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_ACROBATICS, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_ATHLETICS, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_SNEAK, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_UNARMORED, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_ILLUSION, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_MERCANTILE, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_SPEECHCRAFT, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_ALCHEMY, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_CONJURATION, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_ENCHANT, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_ALTERATION, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_DESTRUCTION, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_MYSTICISM, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_RESTORATION, 8));


	GetUnitAttributes()->insert(std::make_pair(UnitAttributesEnum::UNIT_ATTRIBUTE_STRENGTH, 8));
	GetUnitAttributes()->insert(std::make_pair(UnitAttributesEnum::UNIT_ATTRIBUTE_INTELLIGENCE, 8));
	GetUnitAttributes()->insert(std::make_pair(UnitAttributesEnum::UNIT_ATTRIBUTE_WILLPOWER, 8));
	GetUnitAttributes()->insert(std::make_pair(UnitAttributesEnum::UNIT_ATTRIBUTE_AGILITY, 8));
	GetUnitAttributes()->insert(std::make_pair(UnitAttributesEnum::UNIT_ATTRIBUTE_SPEED, 8));
	GetUnitAttributes()->insert(std::make_pair(UnitAttributesEnum::UNIT_ATTRIBUTE_ENDURANCE, 8));
	GetUnitAttributes()->insert(std::make_pair(UnitAttributesEnum::UNIT_ATTRIBUTE_PERSONALITY, 8));

	GetUnitAttributes()->insert(std::make_pair(UnitAttributesEnum::UNIT_ATTRIBUTE_HEALTH, 10));
	GetUnitAttributes()->insert(std::make_pair(UnitAttributesEnum::UNIT_ATTRIBUTE_MAGICKA, 10));
	GetUnitAttributes()->insert(std::make_pair(UnitAttributesEnum::UNIT_ATTRIBUTE_FATIGUE, 10));

	
	_defineRandomUnitTalents();
}

void Unit::_defineDerivedAttributes() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// NOTE:
	// Define derived attributes after standard attributes and
	// after the birthsign and race were defined...


	// Define health.
	// .. define multiplier
	int health_multiplier = 1;
	if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_HIGHELF) {
		health_multiplier -= 0.5f;
	}
	else if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_ORC) {
		health_multiplier += 2;
	}
	else if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_DWARF) {
		health_multiplier += 1.5f;
	}
	else if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_TROLL) {
		health_multiplier += 1;
	}


	int strength = GetUnitAttributes()->at(UnitAttributesEnum::UNIT_ATTRIBUTE_STRENGTH);
	int endurance = GetUnitAttributes()->at(UnitAttributesEnum::UNIT_ATTRIBUTE_ENDURANCE);
	
	int health = int((strength * health_multiplier + endurance) / 2);
	attr->SetAttribute(GetUnitAttributes(), "Health", health);



	// Define magicka.

	// Define multiplier..
	// .. based on race.
	int multiplier = 1;
	if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_HIGHELF) {
		multiplier += 1;
	}
	else if(this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_DARKELF) {
		multiplier += 0.5f;
	}
	else if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_ORC) {
		multiplier -= 0.5f;
	}
	else if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_DWARF) {
		multiplier -= 0.5f;
	}
	else if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_GOBLIN) {
		multiplier -= 0.7f;
	}

	// .. based on birthsign.
	if (COMPARE_STRINGS(this->m_Birthsign, "The Mage") == 0) {
		multiplier += 0.5f;
	}
	else if (COMPARE_STRINGS(this->m_Birthsign, "The Sorcerer") == 0) {
		multiplier += 1.0f;
	}
	else if (COMPARE_STRINGS(this->m_Birthsign, "The Ritual") == 0) {
		multiplier += 0.3f;
	}

	int intelligence = GetUnitAttributes()->at(UnitAttributesEnum::UNIT_ATTRIBUTE_INTELLIGENCE);
	int willpower = GetUnitAttributes()->at(UnitAttributesEnum::UNIT_ATTRIBUTE_WILLPOWER);

	int magicka = int(multiplier * (intelligence + willpower));
	attr->SetAttribute(GetUnitAttributes(), "Magicka", magicka);




	// Define Fatigue.
	// .. define multiplier
	int fatigue_multiplier = 1;
	if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_HIGHELF) {
		fatigue_multiplier += 0.2f;
	}
	else if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_ORC) {
		fatigue_multiplier += 1;
	}
	else if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_DWARF) {
		fatigue_multiplier += 0.7f;
	}
	else if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_TROLL) {
		fatigue_multiplier += 1.5f;
	}
	else if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_GNOME) {
		fatigue_multiplier -= 0.5f;
	}
	else if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_DWARF) {
		fatigue_multiplier -= 0.5f;
	}
	else if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_GOBLIN) {
		fatigue_multiplier -= 0.5f;
	}


	int agility = GetUnitAttributes()->at(UnitAttributesEnum::UNIT_ATTRIBUTE_AGILITY);
	int fatigue = int(fatigue_multiplier * (agility + willpower + endurance + strength));

	attr->SetAttribute(GetUnitAttributes(), "Fatigue", fatigue);
}


void  Unit::_defineStatsBasedOnUnitBirthsign() {


	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();


	if (COMPARE_STRINGS(this->m_Birthsign, "The Warrior") == 0) {


		attr->SetAttribute(GetUnitAttributes(), "Strength", 10);
		attr->UnsetAttribute(GetUnitAttributes(), "Intelligence", 5);

	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Mage") == 0) {

		attr->SetAttribute(GetUnitAttributes(), "Magicka", 20);
		attr->SetAttribute(GetUnitAttributes(), "Intelligence", 5);

		attr->UnsetAttribute(GetUnitAttributes(), "Strength", 5);

	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Thief") == 0) {

		attr->SetAttribute(GetUnitAttributes(), "Speed", 5);
		skills->SetSkill(GetUnitSkills(), "Sneak", 10);

		skills->UnsetSkill(GetUnitSkills(), "Personality", 10);

	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Tower") == 0) {


		attr->SetAttribute(GetUnitAttributes(), "Health", 10);
		attr->SetAttribute(GetUnitAttributes(), "Speed", 2);
		skills->SetSkill(GetUnitSkills(), "Sneak", 5);

	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Lover") == 0) {

		attr->SetAttribute(GetUnitAttributes(), "Personality", 10);

	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Guard") == 0) {


		attr->SetAttribute(GetUnitAttributes(), "Health", 15);
		attr->SetAttribute(GetUnitAttributes(), "Strength", 5);
		attr->SetAttribute(GetUnitAttributes(), "Endurance", 5);

		skills->SetSkill(GetUnitSkills(), "Heavy Armor", 10);
		skills->UnsetSkill(GetUnitSkills(), "Sneak", 10);

	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Sorcerer") == 0) {

		attr->SetAttribute(GetUnitAttributes(), "Intelligence", 5);
		attr->SetAttribute(GetUnitAttributes(), "Magicka", 5);

		skills->SetSkill(GetUnitSkills(), "Destruction", 10);
		skills->UnsetSkill(GetUnitSkills(), "Heavy Armor", 10);
	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Shadow") == 0) {

		attr->SetAttribute(GetUnitAttributes(), "Speed", 10);
		attr->SetAttribute(GetUnitAttributes(), "Health", 5);

		skills->SetSkill(GetUnitSkills(), "Unarmored", 5);
		skills->UnsetSkill(GetUnitSkills(), "Sneak", 20);
	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Lightfeet") == 0) {

		attr->SetAttribute(GetUnitAttributes(), "Speed", 20);
		attr->SetAttribute(GetUnitAttributes(), "Endurance", 5);

		attr->UnsetAttribute(GetUnitAttributes(), "Strength", 5);
		attr->UnsetAttribute(GetUnitAttributes(), "Health", 5);


		skills->SetSkill(GetUnitSkills(), "Athletics", 15);
		skills->SetSkill(GetUnitSkills(), "Acrobatics", 10);

		skills->UnsetSkill(GetUnitSkills(), "Heavy Armor", 15);
		skills->UnsetSkill(GetUnitSkills(), "Medium Armor", 10);

	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Ritual") == 0) {

		skills->SetSkill(GetUnitSkills(), "Mysticism", 15);

	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Paladin") == 0) {

		skills->SetSkill(GetUnitSkills(), "Heavy Armor", 20);
		skills->SetSkill(GetUnitSkills(), "Personality", 15);

		attr->SetAttribute(GetUnitAttributes(), "Strength", 5);

		skills->UnsetSkill(GetUnitSkills(), "Light Armor", 10);
		skills->UnsetSkill(GetUnitSkills(), "Sneak", 20);
	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Mechanist") == 0) {

		attr->SetAttribute(GetUnitAttributes(), "Intelligence", 10);

	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Ignorant") == 0) {

		attr->UnsetAttribute(GetUnitAttributes(), "Intelligence", 10);

	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Lord") == 0) {

		attr->SetAttribute(GetUnitAttributes(), "Intelligence", 5);
		attr->SetAttribute(GetUnitAttributes(), "Personality", 20);

		attr->UnsetAttribute(GetUnitAttributes(), "Speed", 10);
		attr->UnsetAttribute(GetUnitAttributes(), "Willpower", 5);

		skills->UnsetSkill(GetUnitSkills(), "Short Sword", 5);
		skills->UnsetSkill(GetUnitSkills(), "Axe", 5);
		skills->UnsetSkill(GetUnitSkills(), "Blunt Weapon", 5);
		skills->UnsetSkill(GetUnitSkills(), "Spear", 5);

	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Protector") == 0) {
		
		skills->SetSkill(GetUnitSkills(), "Short Sword", 5);
		skills->SetSkill(GetUnitSkills(), "Axe", 5);
		skills->SetSkill(GetUnitSkills(), "Blunt Weapon", 5);
		skills->SetSkill(GetUnitSkills(), "Spear", 5);

	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Stubborn") == 0) {

		attr->UnsetAttribute(GetUnitAttributes(), "Intelligence", 20);
		attr->UnsetAttribute(GetUnitAttributes(), "Magicka", 10);

		attr->SetAttribute(GetUnitAttributes(), "Endurance", 20);
		attr->SetAttribute(GetUnitAttributes(), "Strength", 5);


	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Serpent") == 0) {

		attr->SetAttribute(GetUnitAttributes(), "Intelligence", 50);
		attr->SetAttribute(GetUnitAttributes(), "Willpower", 25);

		skills->SetSkill(GetUnitSkills(), "Sneak", 25);
		skills->SetSkill(GetUnitSkills(), "Mysticism", 25);
		skills->SetSkill(GetUnitSkills(), "Destruction", 25);
	}
}


void Unit::_defineStatsBasedOnUnitRace() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();


	if (m_EntityRaceCmp == nullptr) return;



	switch (m_EntityRaceCmp->m_EntityRace) {
		{
	case CMPEntityRace::Race::RACE_INVALID:
		break;
	case CMPEntityRace::Race::RACE_HUMAN:
		// Bonuses
		attr->SetAttribute(m_UnitAttributesMap, "Strength", 2);
		attr->SetAttribute(m_UnitAttributesMap, "Intelligence", 5);
		attr->SetAttribute(m_UnitAttributesMap, "Personality", 5);

		// Minuses
		attr->UnsetAttribute(m_UnitAttributesMap, "Endurance", 3);




		skills->SetSkill(m_UnitSkillsMap, "Light Armor", 10);
		skills->SetSkill(m_UnitSkillsMap, "Long Blade", 10);
		skills->SetSkill(m_UnitSkillsMap, "Restoration", 5);
		skills->SetSkill(m_UnitSkillsMap, "Destruction", 5);
		skills->SetSkill(m_UnitSkillsMap, "Medium Armor", 5);


		break;
	case CMPEntityRace::Race::RACE_TROLL:
		// Bonuses
		attr->SetAttribute(m_UnitAttributesMap, "Strength", 5);
		attr->SetAttribute(m_UnitAttributesMap, "Agility", 5);

		// Minuses
		// none.


		skills->SetSkill(m_UnitSkillsMap, "Unarmored", 10);
		skills->SetSkill(m_UnitSkillsMap, "Short Blade", 5);
		skills->SetSkill(m_UnitSkillsMap, "Mercantile", 10);
		skills->SetSkill(m_UnitSkillsMap, "Speechcraft", 5);
		skills->SetSkill(m_UnitSkillsMap, "Acrobatics", 5);

		break;
	case CMPEntityRace::Race::RACE_DWARF:
		// Bonuses
		attr->SetAttribute(m_UnitAttributesMap, "Endurance", 5);
		attr->SetAttribute(m_UnitAttributesMap, "Strength", 5);
		attr->SetAttribute(m_UnitAttributesMap, "Personality", 5);

		// Minuses
		attr->UnsetAttribute(m_UnitAttributesMap, "Agility", 5);


		skills->SetSkill(m_UnitSkillsMap, "Mercantile", 10);
		skills->SetSkill(m_UnitSkillsMap, "Blunt Weapon", 10);
		skills->SetSkill(m_UnitSkillsMap, "Heavy Armor", 10);
		skills->SetSkill(m_UnitSkillsMap, "Athletics", 5);
		skills->SetSkill(m_UnitSkillsMap, "Axe", 5);

		break;
	case CMPEntityRace::Race::RACE_ORC:
		// Bonuses
		attr->SetAttribute(m_UnitAttributesMap, "Strength", 10);
		attr->SetAttribute(m_UnitAttributesMap, "Endurance", 7);

		// Minuses
		attr->UnsetAttribute(m_UnitAttributesMap, "Intelligence", 4);


		skills->SetSkill(m_UnitSkillsMap, "Medium Armor", 10);
		skills->SetSkill(m_UnitSkillsMap, "Axe", 10);
		skills->SetSkill(m_UnitSkillsMap, "Heavy Armor", 10);
		skills->SetSkill(m_UnitSkillsMap, "Block", 5);
		skills->SetSkill(m_UnitSkillsMap, "Mysticism", 5);

		break;
	case CMPEntityRace::Race::RACE_HIGHELF:
		// Bonuses
		attr->SetAttribute(m_UnitAttributesMap, "Intelligence", 10);
		attr->SetAttribute(m_UnitAttributesMap, "Agility", 3);

		// Minuses
		attr->UnsetAttribute(m_UnitAttributesMap, "Strength", 3);


		skills->SetSkill(m_UnitSkillsMap, "Medium Armor", 5);
		skills->SetSkill(m_UnitSkillsMap, "Restoration", 10);
		skills->SetSkill(m_UnitSkillsMap, "Illusion", 5);
		skills->SetSkill(m_UnitSkillsMap, "Conjuration", 10);
		skills->SetSkill(m_UnitSkillsMap, "Enchant", 5);

		break;
	case CMPEntityRace::Race::RACE_DARKELF:
		// Bonuses
		attr->SetAttribute(m_UnitAttributesMap, "Speed", 7);
		attr->SetAttribute(m_UnitAttributesMap, "Agility", 10);

		// Minuses
		attr->UnsetAttribute(m_UnitAttributesMap, "Personality", 2);


		skills->SetSkill(m_UnitSkillsMap, "Light Armor", 5);
		skills->SetSkill(m_UnitSkillsMap, "Destruction", 10);
		skills->SetSkill(m_UnitSkillsMap, "Mysticism", 10);
		skills->SetSkill(m_UnitSkillsMap, "Conjuration", 5);
		skills->SetSkill(m_UnitSkillsMap, "Short Blade", 5);

		break;
	case CMPEntityRace::Race::RACE_GOBLIN:
		// Bonuses
		attr->SetAttribute(m_UnitAttributesMap, "Intelligence", 10);
		attr->SetAttribute(m_UnitAttributesMap, "Personality", 4);

		// Minuses
		attr->UnsetAttribute(m_UnitAttributesMap, "Strength", 5);


		skills->SetSkill(m_UnitSkillsMap, "Light Armor", 5);
		skills->SetSkill(m_UnitSkillsMap, "Illusion", 10);
		skills->SetSkill(m_UnitSkillsMap, "Speechcraft", 5);
		skills->SetSkill(m_UnitSkillsMap, "Alteration", 10);
		skills->SetSkill(m_UnitSkillsMap, "Conjuration", 5);

		break;
	case CMPEntityRace::Race::RACE_GNOME:
		// Bonuses
		attr->SetAttribute(m_UnitAttributesMap, "Intelligence", 10);
		attr->SetAttribute(m_UnitAttributesMap, "Agility", 5);
		attr->SetAttribute(m_UnitAttributesMap, "Speed", 3);

		// Minuses
		attr->UnsetAttribute(m_UnitAttributesMap, "Strength", 5);


		skills->SetSkill(m_UnitSkillsMap, "Unarmored", 10);
		skills->SetSkill(m_UnitSkillsMap, "Illusion", 5);
		skills->SetSkill(m_UnitSkillsMap, "Mysticism", 5);
		skills->SetSkill(m_UnitSkillsMap, "Alteration", 10);
		skills->SetSkill(m_UnitSkillsMap, "Short Blade", 5);

		break;
	default:
		break;
		}
	}
}


void Unit::_defineMaxAge() {

	int r = Random() % 10;
	int r2 = Random() % 2;

	if (r2 == 0) {
		m_MaxAge = 70 + r;
	}
	else {
		m_MaxAge = 70 - r;

	}
}

void Unit::Update() {

	int x = m_AgeInternal; // Flag.
	m_AgeInternal = (m_AgeInternal + 1) % 4;

	// One year lived...
	if (x == 3 && m_AgeInternal == 0) {
		m_Age++;
	}

	if (m_Age > m_MaxAge) {

		EntitiesStorage::Get()->DeleteGameEntitie(this);
	}

}

void Unit::_determineUnitRibbonColor() {
	if (COMPARE_STRINGS(m_AssociatedPlayer->m_PlayerColor, "red") == 0) {
		m_UnitPlayerColor = "unit_player_color_red";
	}
	else if (COMPARE_STRINGS(m_AssociatedPlayer->m_PlayerColor, "blue") == 0) {
		m_UnitPlayerColor = "unit_player_color_blue";
	}
	else if (COMPARE_STRINGS(m_AssociatedPlayer->m_PlayerColor, "magenta") == 0) {
		m_UnitPlayerColor = "unit_player_color_magenta";
	}
	else if (COMPARE_STRINGS(m_AssociatedPlayer->m_PlayerColor, "green") == 0) {
		m_UnitPlayerColor = "unit_player_color_green";
	}
	else if (COMPARE_STRINGS(m_AssociatedPlayer->m_PlayerColor, "brown") == 0) {
		m_UnitPlayerColor = "unit_player_color_brown";
	}
	else if (COMPARE_STRINGS(m_AssociatedPlayer->m_PlayerColor, "black") == 0) {
		m_UnitPlayerColor = "unit_player_color_black";
	}
	else if (COMPARE_STRINGS(m_AssociatedPlayer->m_PlayerColor, "orange") == 0) {
		m_UnitPlayerColor = "unit_player_color_orange";
	}
	else if (COMPARE_STRINGS(m_AssociatedPlayer->m_PlayerColor, "yellow") == 0) {
		m_UnitPlayerColor = "unit_player_color_yellow";
	}
	else {
		m_UnitPlayerColor = "NULL"; // Indicates an error.
	}
}

bool Unit::SetClass(std::string c) {

	// First, make sure we reset the class setting.
	if (m_UnitClass) {
		delete m_UnitClass;
	}


	// Second, make new class definitions.
	if (COMPARE_STRINGS(c, "Archer") == 0) {
		m_UnitClass = new UnitClassArcher(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else if (COMPARE_STRINGS(c, "Assassin") == 0) {
		m_UnitClass = new UnitClassAssassin(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else if (COMPARE_STRINGS(c, "Barbarian") == 0) {
		m_UnitClass = new UnitClassBarbarian(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else if (COMPARE_STRINGS(c, "Battlemage") == 0) {
		m_UnitClass = new UnitClassBattlemage(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else if (COMPARE_STRINGS(c, "Healer") == 0) {
		m_UnitClass = new UnitClassHealer(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else if (COMPARE_STRINGS(c, "Inquisitor") == 0) {
		m_UnitClass = new UnitClassInquisitor(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else if (COMPARE_STRINGS(c, "Knight") == 0) {
		m_UnitClass = new UnitClassKnight(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else if (COMPARE_STRINGS(c, "Mage") == 0) {
		m_UnitClass = new UnitClassMage(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else if (COMPARE_STRINGS(c, "Nightblade") == 0) {
		m_UnitClass = new UnitClassNightblade(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else if (COMPARE_STRINGS(c, "Paladin") == 0) {
		m_UnitClass = new UnitClassPaladin(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else if (COMPARE_STRINGS(c, "Rogue") == 0) {
		m_UnitClass = new UnitClassRogue(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else if (COMPARE_STRINGS(c, "Scout") == 0) {
		m_UnitClass = new UnitClassScout(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else if (COMPARE_STRINGS(c, "Sorcerer") == 0) {
		m_UnitClass = new UnitClassSorcerer(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else if (COMPARE_STRINGS(c, "Spellsword") == 0) {
		m_UnitClass = new UnitClassSpellsword(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else if (COMPARE_STRINGS(c, "Spy") == 0) {
		m_UnitClass = new UnitClassSpy(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else if (COMPARE_STRINGS(c, "Warrior") == 0) {
		m_UnitClass = new UnitClassWarrior(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else {
		return false;
	}


	if (m_UnitClass != nullptr) return true;
	else return false;
}


bool Forest::IsCityOnForest() {

	MapTile* maptile = GetMapTileAtWorldPosition(m_TransformCmp->m_GameWorldSpaceCell[0], m_TransformCmp->m_GameWorldSpaceCell[1]);

	for (auto it : *maptile->m_MapTileEntities) {

		if (COMPARE_STRINGS(it->m_IDCmp->m_DynamicTypeName, "City") == 0) return true;
	}

	return false;
}


void WorldMap::SetMapOptions(WorldMapDrawingOptions* worldDef) {

	m_MapDrawOptions = worldDef;
	m_WorldMap = worldDef->m_MapDefinitions;
}


void WorldMapDrawingOptions::_createMap() {


	m_MapDefinitions = new MapTileArray();

	EntitiesStorage* storage = EntitiesStorage::Get();

	using namespace std;

	ifstream map("assets/map/worldmap_alpha.txt", fstream::in);

	string line;
	string token;
	string token_two;

	int xpos = 0;
	int ypos = 0;

	// Width and Height must always be 1 less then defined in the loaded mapfile. Else errors occur.
	int mapwidth = 19;
	int mapheight = 19;

	MapTile* maptile = nullptr;

	std::vector<MapTileRegion*> regions_vec;
	MapTileRegion* region = nullptr;


	while (getline(map, line)) {


		//cout << line << endl;



		// Read the textfile line by line.
		if (IsSubstringInString("maptiles", line)) { // Defining the ground maptiles.

			cout << APP_COLOR;
			cout << "CREATING MAPTILES." << white << endl;


			if (COMPARE_STRINGS(line, "maptiles;") == 0) getline(map, line); // Read next line for maptiles definition.


			cout << APP_ERROR_COLOR;
			cout << line << white << endl;

			/*
			For: every token do:
			...

			*/
			// First, identify tokens.
			string token = "";
			bool escape_code = false;
			bool line_end_escape_code = false; // Means, the end of the line was reached, the delimiter ";" was found, thus move to next line.

			for (auto it = line.begin(); it != line.end(); ++it) {

				if (*it == ',') { // escape code
					escape_code = true;
				}
				else if (*it == ';') {
					line_end_escape_code = true;
				}
				else {
					token.push_back((*it)); // At char to string.
				}


				// Now check for definitions an create new maptiles.
				// Escape code means, we found our delimiter and can check the word for maptile definition.
				if (escape_code) {


					if (IsSubstringInString("_shallow", token)) {
						maptile = new MapTile("water_shallow", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);
						maptile->m_TransformCmp->m_GameWorldSpaceCell[0] = xpos;
						maptile->m_TransformCmp->m_GameWorldSpaceCell[1] = ypos;

						m_MapDefinitions->at(xpos).at(ypos) = maptile;

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.


						cout << APP_SUCCESS_COLOR;
						cout << "Create WATER_SHALLOW at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("_deep", token)) {
						maptile = new MapTile("water_deep", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);
						maptile->m_TransformCmp->m_GameWorldSpaceCell[0] = xpos;
						maptile->m_TransformCmp->m_GameWorldSpaceCell[1] = ypos;

						m_MapDefinitions->at(xpos).at(ypos) = maptile;

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create WATER_DEEP at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("temperate", token)) {
						maptile = new MapTile("temperate", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);
						maptile->m_TransformCmp->m_GameWorldSpaceCell[0] = xpos;
						maptile->m_TransformCmp->m_GameWorldSpaceCell[1] = ypos;

						m_MapDefinitions->at(xpos).at(ypos) = maptile;

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create TEMPERATE at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("jungle", token)) {
						maptile = new MapTile("jungle", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);
						maptile->m_TransformCmp->m_GameWorldSpaceCell[0] = xpos;
						maptile->m_TransformCmp->m_GameWorldSpaceCell[1] = ypos;

						m_MapDefinitions->at(xpos).at(ypos) = maptile;

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create JUNGLE at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("tundra", token)) {
						maptile = new MapTile("tundra", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);

						maptile->m_TransformCmp->m_GameWorldSpaceCell[0] = xpos;
						maptile->m_TransformCmp->m_GameWorldSpaceCell[1] = ypos;

						m_MapDefinitions->at(xpos).at(ypos) = maptile;

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create TUNDRA at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("savannah", token)) {
						maptile = new MapTile("savannah", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);

						maptile->m_TransformCmp->m_GameWorldSpaceCell[0] = xpos;
						maptile->m_TransformCmp->m_GameWorldSpaceCell[1] = ypos;

						m_MapDefinitions->at(xpos).at(ypos) = maptile;

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create SAVANNAH at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("snow", token)) {
						maptile = new MapTile("snow", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);

						maptile->m_TransformCmp->m_GameWorldSpaceCell[0] = xpos;
						maptile->m_TransformCmp->m_GameWorldSpaceCell[1] = ypos;

						m_MapDefinitions->at(xpos).at(ypos) = maptile;

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create SNOW at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("ice", token)) {
						maptile = new MapTile("ice", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);

						maptile->m_TransformCmp->m_GameWorldSpaceCell[0] = xpos;
						maptile->m_TransformCmp->m_GameWorldSpaceCell[1] = ypos;

						m_MapDefinitions->at(xpos).at(ypos) = maptile;

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create ICE at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("sand", token)) {
						maptile = new MapTile("sand", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);

						maptile->m_TransformCmp->m_GameWorldSpaceCell[0] = xpos;
						maptile->m_TransformCmp->m_GameWorldSpaceCell[1] = ypos;

						m_MapDefinitions->at(xpos).at(ypos) = maptile;

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create SAND at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}


					// Custom double for-loop iterator...
					// To get the right cell position of the next tile.
					cout << color(colors::MAGENTA);
					cout << "X " << xpos << " Y " << ypos << white << endl;

					++xpos;
					if (xpos > mapwidth) {

						// Move on to the next line.
						++ypos;
						if (ypos > mapheight) {
							ypos = 0; // Set to 0 or reset it...
						}


						// Reset xpos.
						xpos = 0;
					}



					cout << color(colors::MAGENTA);
					cout << "X " << xpos << " Y " << ypos << white << endl;

				}
				else if (line_end_escape_code) {
					continue;
				}



			}

		}
		else if (IsSubstringInString("overlay", line)) { // Defining forests, hills, mountains etc.

		Forest* forest = nullptr;

		cout << APP_COLOR;
		cout << "CREATING OVERLAY." << white << endl;

		cout << xpos << ypos << endl;



		string token = ""; // The next word.
		bool escape_code = false;
		bool line_end_escape_code = false; // Means, the end of the line was reached, the delimiter ";" was found, thus move to next line.


		if (COMPARE_STRINGS(line, "overlay;") == 0) getline(map, line); // Read next line for maptiles definition.

		
		cout << line << endl;


		for (auto it = line.begin(); it != line.end(); ++it) {

				if (*it == ',') { // escape code
					escape_code = true;
				}
				else if (*it == ';') {
					line_end_escape_code = true;
				}
				else {
					token.push_back((*it)); // At char to string.
				}



				if (escape_code) {

					if (IsSubstringInString("forest_tundra", token)) {

						// Create forest.
						forest = MakeNewForest("forest_tundra_deep", xpos, ypos);
						storage->AddGameEntitie(forest);



						cout << token << endl;
						// Custom double for-loop iterator...
						// To get the right cell position of the next tile.
						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						++xpos;
						if (xpos > mapwidth) {

							// Move on to the next line.
							++ypos;
							if (ypos > mapheight) {
								ypos = 0; // Set to 0 or reset it...
							}


							// Reset xpos.
							xpos = 0;
						}



						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;
						cout << color(colors::CYAN);
						cout << "Create FOREST_TUNDRA at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("forest_jungle", token)) {

						// Create forest.
						forest = MakeNewForest("forest_jungle_deep", xpos, ypos);
						storage->AddGameEntitie(forest);

						cout << token << endl;


						// Custom double for-loop iterator...
						// To get the right cell position of the next tile.
						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						++xpos;
						if (xpos > mapwidth) {

							// Move on to the next line.
							++ypos;
							if (ypos > mapheight) {
								ypos = 0; // Set to 0 or reset it...
							}


							// Reset xpos.
							xpos = 0;
						}



						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						cout << color(colors::CYAN);
						cout << "Create FOREST_JUNGLE at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("forest_temperate", token)) {

						// Create forest.
						forest = MakeNewForest("forest_temperate_deep", xpos, ypos);
						storage->AddGameEntitie(forest);

						cout << token << endl;


						// Custom double for-loop iterator...
						// To get the right cell position of the next tile.
						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						++xpos;
						if (xpos > mapwidth) {

							// Move on to the next line.
							++ypos;
							if (ypos > mapheight) {
								ypos = 0; // Set to 0 or reset it...
							}


							// Reset xpos.
							xpos = 0;
						}



						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						cout << color(colors::CYAN);
						cout << "Create FOREST_TEMPERATE at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("forest_savannah", token)) {

						// Create forest.
						forest = MakeNewForest("forest_savannah_deep", xpos, ypos);
						storage->AddGameEntitie(forest);

						cout << token << endl;


						// Custom double for-loop iterator...
						// To get the right cell position of the next tile.
						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						++xpos;
						if (xpos > mapwidth) {

							// Move on to the next line.
							++ypos;
							if (ypos > mapheight) {
								ypos = 0; // Set to 0 or reset it...
							}


							// Reset xpos.
							xpos = 0;
						}



						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						cout << color(colors::CYAN);
						cout << "Create FOREST_SAVANNAH at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("hill", token)) {

						cout << token << endl;

						Hills* hills = MakeNewHill("hills", xpos, ypos);
						storage->AddGameEntitie(hills);

						// Custom double for-loop iterator...
						// To get the right cell position of the next tile.
						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						++xpos;
						if (xpos > mapwidth) {

							// Move on to the next line.
							++ypos;
							if (ypos > mapheight) {
								ypos = 0; // Set to 0 or reset it...
							}


							// Reset xpos.
							xpos = 0;
						}



						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						cout << color(colors::CYAN);
						cout << "Create HILLS at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("mountain", token)) {

						cout << token << endl;

						Mountains* mountains = MakeNewMountain("highmountain", xpos, ypos);
						storage->AddGameEntitie(mountains);


						// Custom double for-loop iterator...
						// To get the right cell position of the next tile.
						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						++xpos;
						if (xpos > mapwidth) {

							// Move on to the next line.
							++ypos;
							if (ypos > mapheight) {
								ypos = 0; // Set to 0 or reset it...
							}


							// Reset xpos.
							xpos = 0;
						}



						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						cout << color(colors::CYAN);
						cout << "Create MOUNTAINS at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("none", token)) {

						cout << token << endl;


						// Custom double for-loop iterator...
						// To get the right cell position of the next tile.
						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						++xpos;
						if (xpos > mapwidth) {

							// Move on to the next line.
							++ypos;
							if (ypos > mapheight) {
								ypos = 0; // Set to 0 or reset it...
							}


							// Reset xpos.
							xpos = 0;
						}



						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						cout << color(colors::CYAN);
						cout << "Create NONE at Position " << xpos << ":" << ypos << white << endl;
						// Nothing...


						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (line_end_escape_code) {
						continue;
					}



				}

			} // end for overlay


		}
		else if (IsSubstringInString("region;", line)) { // Defining maptileregions for the map.

				// Regions are defined like
				// region;
				// 1:0, 2:0, 1:1,; ...
				int map_tile[2];
				bool first_digit_defined = false;

				region = new MapTileRegion();
				regions_vec.push_back(region);


				cout << APP_COLOR;
				cout << "CREATING REGIONS" << white << endl;

				string token = ""; // The next word.
				bool escape_code = false;
				bool token_escape_code = false;
				bool token_end_of_maptile_definition = false;
				bool line_end_escape_code = false; // Means, the end of the line was reached, the delimiter ";" was found, thus move to next line.


				if (COMPARE_STRINGS(line, "region;") == 0) getline(map, line); // Read next line for maptiles definition.


				cout << APP_ERROR_COLOR;
				cout << line << white << endl;

				// Iterate through line
				for (auto it = line.begin(); it != line.end(); ++it) {

					if (*it == ',') { // escape code
						escape_code = true;
					}
					else if (*it == ';') {
						line_end_escape_code = true;
					}
					else {
						token.push_back((*it)); // At char to string.
					}


					// Check tokens.
					if (escape_code) {

						cout << APP_ERROR_COLOR;
						cout << token << white << endl;

						// Extract numbers out of token
						string first_number, second_number;
						bool delimiter_reached = false;

						for (auto it = token.begin(); it != token.end(); ++it) {

							if (*it == ':') delimiter_reached = true;

							if (*it != ':' && delimiter_reached == false) {

								first_number.push_back(*it);
							}
							else if(*it != ':'){
								second_number.push_back(*it);
							}

						}


						// Convert first_number and second_number to a maptile position.
						map_tile[0] = atoi(first_number.c_str());
						map_tile[1] = atoi(second_number.c_str());


						region->AddTileToRegion(GetMapTileAtWorldPosition(map_tile[0], map_tile[1]));


						cout << APP_ERROR_COLOR;
						cout << "First: "<<first_number << " Second: " << second_number << white << endl;
						first_number.clear();
						second_number.clear();



						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;

					}
					else if (line_end_escape_code) {
						continue;
					}




				}

		}
		else if (IsSubstringInString("rivers;", line)) {

		/*
		TODO: 
		Theres a bug in rivers mapfile definitions.
		The positions in file e.g. 9:9 are not 8:8 in game, there is an offset of 1 as I remember.

		Eliminate this bug later with a mapeditor. Because mapdefinitions like this are crappy hell...
		*/
			
			cout << APP_COLOR;
			cout << "CREATING RIVERS." << white << endl;

			cout << xpos << ypos << endl;

			string token = ""; // The next word.
			bool escape_code = false;
			bool line_end_escape_code = false; // Means, the end of the line was reached, the delimiter ";" was found, thus move to next line.

			if (COMPARE_STRINGS(line, "rivers;") == 0) getline(map, line); // Read next line for rivers definition.

			cout << line << endl;


			for (auto it = line.begin(); it != line.end(); ++it) {

				if (*it == ',') { // escape code
					escape_code = true;
				}
				else if (*it == ';') {
					line_end_escape_code = true;
				}
				else {
					token.push_back((*it)); // At char to string.
				}

				// Check tokens.
				if (escape_code) {

					cout << APP_ERROR_COLOR;
					cout << token << white << endl;

					// Make river.
				if (IsSubstringInString("up_right_left_down", token)) {

					River* r = MakeNewRiver("river_up_right_left_down", xpos, ypos);
					storage->AddGameEntitie(r);

					/*
					++xpos;
					if (xpos > mapwidth) {

						// Move on to the next line.
						++ypos;
						if (ypos > mapheight) {
							ypos = -1; // Set to 0 or reset it...
						}


						// Reset xpos.
						xpos = 0;
					}
					*/
				}
				else if (IsSubstringInString("up_right_left", token)) {

					River* r = MakeNewRiver("river_up_right_left", xpos, ypos);
					storage->AddGameEntitie(r);

					/*
					++xpos;
					if (xpos > mapwidth) {

						// Move on to the next line.
						++ypos;
						if (ypos > mapheight) {
							ypos = -1; // Set to 0 or reset it...
						}


						// Reset xpos.
						xpos = 0;
					}
					*/
				}
				else if (IsSubstringInString("up_right_down", token)) {

					River* r = MakeNewRiver("river_up_right_down", xpos, ypos);
					storage->AddGameEntitie(r);

					/*
					++xpos;
					if (xpos > mapwidth) {

						// Move on to the next line.
						++ypos;
						if (ypos > mapheight) {
							ypos = -1; // Set to 0 or reset it...
						}


						// Reset xpos.
						xpos = 0;
					}
					*/
				}
				else if (IsSubstringInString("down_left", token)) {

						River* r = MakeNewRiver("river_down_left", xpos, ypos);
						storage->AddGameEntitie(r);

						/*
						++xpos;
						if (xpos > mapwidth) {

							// Move on to the next line.
							++ypos;
							if (ypos > mapheight) {
								ypos = -1; // Set to 0 or reset it...
							}


							// Reset xpos.
							xpos = 0;
						}
						*/
					}
					else if (IsSubstringInString("down_right", token)) {

						River* r = MakeNewRiver("river_down_right", xpos, ypos);
						storage->AddGameEntitie(r);


						/*
						++xpos;
						if (xpos > mapwidth) {

							// Move on to the next line.
							++ypos;
							if (ypos > mapheight) {
								ypos = -1; // Set to 0 or reset it...
							}


							// Reset xpos.
							xpos = 0;
						}
						*/
					}
					else if (IsSubstringInString("left_right", token)) {

						River* r = MakeNewRiver("river_left_right", xpos, ypos);
						storage->AddGameEntitie(r);

						/*
						++xpos;
						if (xpos > mapwidth) {

							// Move on to the next line.
							++ypos;
							if (ypos > mapheight) {
								ypos = -1; // Set to 0 or reset it...
							}


							// Reset xpos.
							xpos = 0;
						}
						*/
					}
					else if (IsSubstringInString("left_right_down", token)) {

						River* r = MakeNewRiver("river_left_right_down", xpos, ypos);
						storage->AddGameEntitie(r);


						/*
						++xpos;
						if (xpos > mapwidth) {

							// Move on to the next line.
							++ypos;
							if (ypos > mapheight) {
								ypos = -1; // Set to 0 or reset it...
							}


							// Reset xpos.
							xpos = 0;
						}
						*/
					}
					else if (IsSubstringInString("left_up_down", token)) {

						River* r = MakeNewRiver("river_left_up_down", xpos, ypos);
						storage->AddGameEntitie(r);

						/*
						++xpos;
						if (xpos > mapwidth) {

							// Move on to the next line.
							++ypos;
							if (ypos > mapheight) {
								ypos = -1; // Set to 0 or reset it...
							}


							// Reset xpos.
							xpos = 0;
						}
						*/
					}
					else if (IsSubstringInString("up_down", token)) {

						River* r = MakeNewRiver("river_up_down", xpos, ypos);
						storage->AddGameEntitie(r);

						/*
						++xpos;
						if (xpos > mapwidth) {

							// Move on to the next line.
							++ypos;
							if (ypos > mapheight) {
								ypos = -1; // Set to 0 or reset it...
							}


							// Reset xpos.
							xpos = 0;
						}
						*/
					}
					else if (IsSubstringInString("up_left", token)) {

						River* r = MakeNewRiver("river_up_left", xpos, ypos);
						storage->AddGameEntitie(r);

						/*
						++xpos;
						if (xpos > mapwidth) {

							// Move on to the next line.
							++ypos;
							if (ypos > mapheight) {
								ypos = -1; // Set to 0 or reset it...
							}


							// Reset xpos.
							xpos = 0;
						}
						*/
					}
					else if (IsSubstringInString("up_right", token)) {

						River* r = MakeNewRiver("river_up_right", xpos, ypos);
						storage->AddGameEntitie(r);


						/*
						++xpos;
						if (xpos > mapwidth) {

							// Move on to the next line.
							++ypos;
							if (ypos > mapheight) {
								ypos = -1; // Set to 0 or reset it...
							}


							// Reset xpos.
							xpos = 0;
						}
						*/
					}
					else if (IsSubstringInString("none", token)) {
						/*
						// No river defined here.
						++xpos;
						if (xpos > mapwidth) {

							// Move on to the next line.
							++ypos;
							if (ypos > mapheight) {
								ypos = -1; // Set to 0 or reset it...
							}


							// Reset xpos.
							xpos = 0;
						}
						continue;
						*/
					}




					++xpos;
					if (xpos > mapwidth) {

						// Move on to the next line.
						++ypos;
						if (ypos > mapheight) {
							ypos = 0; // Set to 0 or reset it...
						}


						// Reset xpos.
						xpos = 0;
					}


					// Reset the reading token and escape_code
					token.clear();
					escape_code = false;

				}
				else if (line_end_escape_code) {
					continue;
				}

		}


		}
		else {
			continue;
		}
	}


	// At last, add regions made to storage.
	for (auto it : regions_vec) {

		storage->AddGameEntitie(it);
	}
	

	regions_vec.clear();
	map.close();
}


WorldMap* WorldMap::Get() {
	if (!m_WorldMapInstance) {
		m_WorldMapInstance = new WorldMap();

		return m_WorldMapInstance;
	}
	else {
		return m_WorldMapInstance;
	}
}


void WorldMap::Del() {

	if (m_WorldMapInstance) delete m_WorldMapInstance;
}


void Forest::Update() {


	// Change graphics accordingly to own type.
	switch (m_ForestType) {
	case ForestType::FOREST_SCARCE:

		switch (m_ForestClass) {
		case ForestClass::FOREST_CLASS_TEMPERATE:
			m_GraphicsCmp->m_SpriteName = "forest_temperate_scarce";
			break;
		case ForestClass::FOREST_CLASS_JUNGLE:
			m_GraphicsCmp->m_SpriteName = "forest_jungle_scarce";
			break;
		case ForestClass::FOREST_CLASS_TUNDRA:
			m_GraphicsCmp->m_SpriteName = "forest_tundra_scarce";
			break;
		case ForestClass::FOREST_CLASS_SAVANNAH:
			m_GraphicsCmp->m_SpriteName = "forest_savannah_scarce";
			break;
		default:
			break;
		}

		break;
	case ForestType::FOREST_NORMAL:

		switch (m_ForestClass) {
		case ForestClass::FOREST_CLASS_TEMPERATE:
			m_GraphicsCmp->m_SpriteName = "forest_temperate_normal";
			break;
		case ForestClass::FOREST_CLASS_JUNGLE:
			m_GraphicsCmp->m_SpriteName = "forest_jungle_normal";
			break;
		case ForestClass::FOREST_CLASS_TUNDRA:
			m_GraphicsCmp->m_SpriteName = "forest_tundra_normal";
			break;
		case ForestClass::FOREST_CLASS_SAVANNAH:
			m_GraphicsCmp->m_SpriteName = "forest_savannah_normal";
			break;
		default:
			break;
		}

		break;
	case ForestType::FOREST_DEEP:
		switch (m_ForestClass) {
		case ForestClass::FOREST_CLASS_TEMPERATE:
			m_GraphicsCmp->m_SpriteName = "forest_temperate_deep";
			break;
		case ForestClass::FOREST_CLASS_JUNGLE:
			m_GraphicsCmp->m_SpriteName = "forest_jungle_deep";
			break;
		case ForestClass::FOREST_CLASS_TUNDRA:
			m_GraphicsCmp->m_SpriteName = "forest_tundra_deep";
			break;
		case ForestClass::FOREST_CLASS_SAVANNAH:
			m_GraphicsCmp->m_SpriteName = "forest_savannah_deep";
			break;
		default:
			break;
		}
		break;
	case ForestType::FOREST_DYING:
		switch (m_ForestClass) {
		case ForestClass::FOREST_CLASS_TEMPERATE:
			m_GraphicsCmp->m_SpriteName = "forest_temperate_dying";
			break;
		case ForestClass::FOREST_CLASS_JUNGLE:
			m_GraphicsCmp->m_SpriteName = "forest_jungle_dying";
			break;
		case ForestClass::FOREST_CLASS_TUNDRA:
			m_GraphicsCmp->m_SpriteName = "forest_tundra_dying";
			break;
		case ForestClass::FOREST_CLASS_SAVANNAH:
			m_GraphicsCmp->m_SpriteName = "forest_savannah_dying";
			break;
		default:
			break;
		}
		break;
	case ForestType::FOREST_INVALID: // Forests lifetime ended or other error occured. So delete this instance from game.

		EntitiesStorage::Get()->DeleteGameEntitie(this);
		break;
	default:
		break;
	}
}

void City::ReclaimRegions() {

	_unclaimRegions();
	ClaimRegions();
}

/*
void City::ClaimRegions() {


	// First, claim tile the city is on.
	// We assume, cities are not built on claimed tiles...
	// Be it own claimed tiles or of another player.

	int city_pos[2];
	city_pos[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	city_pos[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];


	// Normal
	int right[2], left[2], up[2], down[2];
	int right_2[2], left_2[2], up_2[2], down_2[2];


	// Diagonal
	int left_up[2], right_up[2], left_down[2], right_down[2];


	// Get according maptile coords for claiming.
	right[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 1;
	right[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];

	left[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 1;
	left[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];

	up[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	up[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 1;

	down[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	down[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 1;

	right_2[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 2;
	right_2[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];

	left_2[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 2;
	left_2[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];

	up_2[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	up_2[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 2;

	down_2[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	down_2[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 2;

	left_up[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 1;
	left_up[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 1;

	right_up[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 1;
	right_up[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 1;

	left_down[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 1;
	left_down[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 1;

	right_down[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 1;
	right_down[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 1;


	// Now claim associated regions of the maptiles for which we got coords.
	MapTile* m0, *m1, * m2, * m3, * m4,* m5, * m6,* m7, * m8, * m9, * m10, * m11, * m12;
	m0 = GetMapTileAtWorldPosition(city_pos[0], city_pos[1]);
	m1 = GetMapTileAtWorldPosition(right[0], right[1]);
	m2 = GetMapTileAtWorldPosition(left[0], left[1]);
	m3 = GetMapTileAtWorldPosition(up[0], up[1]);
	m4 = GetMapTileAtWorldPosition(down[0], down[1]);
	m5 = GetMapTileAtWorldPosition(right_2[0], right_2[1]);
	m6 = GetMapTileAtWorldPosition(left_2[0], left_2[1]);
	m7 = GetMapTileAtWorldPosition(up_2[0], up_2[1]);
	m8 = GetMapTileAtWorldPosition(down_2[0], down_2[1]);


	// No need for nullptr test here.
	m_ClaimedRegions.push_back(m0->m_AssociatedRegion);

	// Here we must test whether the tile is valid.
	if (m1 != nullptr) {
		
		if (_isRegionClaimedAlreadyByThisCity(m1->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m1->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m1->m_AssociatedRegion);
		}
	}
	if (m2 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m2->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m2->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m2->m_AssociatedRegion);
		}
	}
	if (m3 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m3->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m3->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m3->m_AssociatedRegion);
		}
	}
	if (m4 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m4->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m4->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m4->m_AssociatedRegion);
		}
	}
	if (m5 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m5->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m5->m_AssociatedRegion) == false) {


			m_ClaimedRegions.push_back(m5->m_AssociatedRegion);
		}
	}
	if (m6 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m6->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m6->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m6->m_AssociatedRegion);
		}
	}
	if (m7 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m7->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m7->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m7->m_AssociatedRegion);
		}
	}
	if (m8 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m8->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m8->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m8->m_AssociatedRegion);
		}
	}


	m9 = GetMapTileAtWorldPosition(left_up[0], left_up[1]);
	m10 = GetMapTileAtWorldPosition(right_up[0], right_up[1]);
	m11 = GetMapTileAtWorldPosition(left_down[0], left_down[1]);
	m12 = GetMapTileAtWorldPosition(right_down[0], right_down[1]);

	if (m9 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m9->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m9->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m9->m_AssociatedRegion);
		}
	}
	if (m10 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m10->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m10->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m10->m_AssociatedRegion);
		}
	}
	if (m11 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m11->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m11->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m11->m_AssociatedRegion);
		}
	}
	if (m12 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m12->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m12->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m12->m_AssociatedRegion);
		}
	}

	_setSpriteForClaimedRegion();
	

	// Set region owner for claimed regions.
	for (auto it : m_ClaimedRegions) {

		it->SetAssociatedPlayer(m_AssociatedPlayer);
	}
}
*/

void City::Update() {

	// Later make that this city ceases if population is smaller than 1.
	// For now, we just skip this and do not let the city die.
	if (m_CitySize < 1) m_CitySize = 1;

	CitySizeClass size = this->m_CitySizeClass;

	_updateCitySizeClass();

	if (m_CitySizeClass != size) {
		ReclaimRegions();
		MakeCityBorders();
	}
}



void City::_deriveCityLandscapeType() {

	/*
	NOTE: How do we handle rivers.

	Rivers are additional to cities landscape. As rivers can be on hills, forests and plain.
	Thus, we give for a river a boolean, that is true, if a river is present on the cities tile.
	*/

	MapTile* city_tile = GetMapTileAtWorldPosition(this->m_TransformCmp->m_GameWorldSpaceCell[0], this->m_TransformCmp->m_GameWorldSpaceCell[1]);

	bool mountain = false, hill = false, forest = false;

	// First, check for mountains.
	for (auto it : *city_tile->m_MapTileEntities) {

		if (COMPARE_STRINGS(it->m_IDCmp->m_DynamicTypeName, "Mountains") == 0) {
			mountain = true;
		}
		// .. check for hills.
		else if (COMPARE_STRINGS(it->m_IDCmp->m_DynamicTypeName, "Hills") == 0) {
			hill = true;

		}
		// .. check for river.
		else if (COMPARE_STRINGS(it->m_IDCmp->m_DynamicTypeName, "River") == 0) {
			m_RiverPresentInCity = true;

		}
		// .. check for forest
		else if (COMPARE_STRINGS(it->m_IDCmp->m_DynamicTypeName, "Forest") == 0) {
			forest = true;
		}


	}

	if (mountain) {
		m_CityLandscapeType = new CityLandscapeType(CityLandscapeType::CITY_LANDSCAPE_MOUNTAINS);
	}
	else if (hill) {
		m_CityLandscapeType = new CityLandscapeType(CityLandscapeType::CITY_LANDSCAPE_HILLS);
	}
	else if (forest) {
		m_CityLandscapeType = new CityLandscapeType(CityLandscapeType::CITY_LANDSCAPE_FOREST);
	}
	// .. lastly, if nothing present, define as plain city.
	else {
		m_CityLandscapeType = new CityLandscapeType(CityLandscapeType::CITY_LANDSCAPE_PLAIN);
	}



	// Check whether coastal city.
	MapTile* m1, *m2, *m3, *m4;

	m1 = GetMapTileAtWorldPosition(m_TransformCmp->m_GameWorldSpaceCell[0]+1, m_TransformCmp->m_GameWorldSpaceCell[1]);
	m2 = GetMapTileAtWorldPosition(m_TransformCmp->m_GameWorldSpaceCell[0]-1, m_TransformCmp->m_GameWorldSpaceCell[1]);
	m3 = GetMapTileAtWorldPosition(m_TransformCmp->m_GameWorldSpaceCell[0], m_TransformCmp->m_GameWorldSpaceCell[1]+1);
	m4 = GetMapTileAtWorldPosition(m_TransformCmp->m_GameWorldSpaceCell[0], m_TransformCmp->m_GameWorldSpaceCell[1]-1);


	if (m1) {
		if (m1->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_WATER_SHALLOW) {
			m_CoastalCity = true;
		}
	}
	if (m2) {
		if (m2->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_WATER_SHALLOW) {
			m_CoastalCity = true;
		}
	}
	if (m3) {
		if (m3->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_WATER_SHALLOW) {
			m_CoastalCity = true;
		}
	}
	if (m4) {
		if (m4->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_WATER_SHALLOW) {
			m_CoastalCity = true;
		}
	}

}



void City::_unclaimRegions() {

	for (auto it : m_ClaimedRegions) {

		it->SetAssociatedPlayer(nullptr);
		
	}

	if (m_ClaimedRegions.size() > 0) {
		m_ClaimedRegions.clear();
		m_CityBorderMapTileVec.clear();
		m_MapTileBorderDirectionMap.clear();
	}
}


void City::_claimRegions() {

	using namespace std;
	cout << APP_SUCCESS_COLOR;
	cout << "_claimRegions() for " << m_CityName;

	switch (m_CityType){
	case CityType::CITY_TYPE_CITY:
		switch (m_CitySizeClass) {
		case CitySizeClass::CITY_SIZE_CLASS_SMALL:
			_claimPrimaryRegions();


			cout << ". Claim _claimPrimaryRegions()." << white << endl;
			break;
		case CitySizeClass::CITY_SIZE_CLASS_NORMAL:
			_claimPrimaryRegions();
			_claimSecondaryRegions();


			cout << ". Claim up to _claimSecondaryRegions()." << white << endl;
			break;
		case CitySizeClass::CITY_SIZE_CLASS_BIG:
			_claimPrimaryRegions();
			_claimSecondaryRegions();
			_claimTertiaryReions();


			cout << ". Claim up to _claimTertiaryReions()." << white << endl;
			break;
		case CitySizeClass::CITY_SIZE_CLASS_HUGE:
			_claimPrimaryRegions();
			_claimSecondaryRegions();
			_claimTertiaryReions();
			_claimQuartaryRegions();

			cout << ". Claim up to _claimQuartaryRegions()." << white << endl;
			break;
		default:
			break;
		}
		break;
	case CityType::CITY_TYPE_FORT:// Test for castles, they claim only half of cities max regions. Till secondary...
		switch (m_CitySizeClass) {
		case CitySizeClass::CITY_SIZE_CLASS_SMALL:
			_claimPrimaryRegions();
			break;
		case CitySizeClass::CITY_SIZE_CLASS_NORMAL:
			_claimPrimaryRegions();
			_claimSecondaryRegions();
			break;
		case CitySizeClass::CITY_SIZE_CLASS_BIG:
			_claimPrimaryRegions();
			_claimSecondaryRegions();
			//_claimTertiaryReions();
			break;
		case CitySizeClass::CITY_SIZE_CLASS_HUGE:
			_claimPrimaryRegions();
			_claimSecondaryRegions();
			//_claimTertiaryReions(); 
			// Fort does not claim quartary tiles.
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}



	_setSpriteForClaimedRegion();

	// Set region owner for claimed regions.
	for (auto it : m_ClaimedRegions) {

		it->SetAssociatedPlayer(m_AssociatedPlayer);
	}
}


void City::_claimPrimaryRegions() {

	// Primary regions are at tiles around city.
	// Those are 4.
	int city_pos[2];
	city_pos[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	city_pos[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];

	int right[2], left[2], up[2], down[2];

	right[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 1;
	right[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];

	left[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 1;
	left[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];

	up[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	up[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 1;

	down[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	down[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 1;

	MapTile* m0, * m1, * m2, * m3, * m4;
	m0 = GetMapTileAtWorldPosition(city_pos[0], city_pos[1]);
	m1 = GetMapTileAtWorldPosition(right[0], right[1]);
	m2 = GetMapTileAtWorldPosition(left[0], left[1]);
	m3 = GetMapTileAtWorldPosition(up[0], up[1]);
	m4 = GetMapTileAtWorldPosition(down[0], down[1]);


	// No need for nullptr test here.
	m_ClaimedRegions.push_back(m0->m_AssociatedRegion);

	// Here we must test whether the tile is valid.
	if (m1 != nullptr) {

		if (_isRegionClaimedAlreadyByThisCity(m1->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m1->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m1->m_AssociatedRegion);
		}
	}
	if (m2 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m2->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m2->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m2->m_AssociatedRegion);
		}
	}
	if (m3 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m3->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m3->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m3->m_AssociatedRegion);
		}
	}
	if (m4 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m4->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m4->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m4->m_AssociatedRegion);
		}
	}
}


void City::_claimSecondaryRegions() {

	// Secondary regions are at tiles 2 tiles away around city.
	// Those are 8.
	int city_pos[2];
	city_pos[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	city_pos[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];

	int up[2], right[2], down[2], left[2], left_up[2], right_up[2], down_left[2], down_right[2];

	right[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 2;
	right[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];

	left[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 2;
	left[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];

	up[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	up[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 2;

	down[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	down[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 2;

	down_right[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 1;
	down_right[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 1;

	down_left[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 1;
	down_left[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 1;

	right_up[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 1;
	right_up[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 1;

	left_up[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 1;
	left_up[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 1;


	MapTile* m1, * m2, * m3, * m4, * m5, * m6, * m7, * m8;
	m1 = GetMapTileAtWorldPosition(right[0], right[1]);
	m2 = GetMapTileAtWorldPosition(left[0], left[1]);
	m3 = GetMapTileAtWorldPosition(up[0], up[1]);
	m4 = GetMapTileAtWorldPosition(down[0], down[1]);
	m5 = GetMapTileAtWorldPosition(down_right[0], down_right[1]);
	m6 = GetMapTileAtWorldPosition(down_left[0], down_left[1]);
	m7 = GetMapTileAtWorldPosition(right_up[0], right_up[1]);
	m8 = GetMapTileAtWorldPosition(left_up[0], left_up[1]);

	// Here we must test whether the tile is valid.
	if (m1 != nullptr) {

		if (_isRegionClaimedAlreadyByThisCity(m1->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m1->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m1->m_AssociatedRegion);
		}
	}
	if (m2 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m2->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m2->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m2->m_AssociatedRegion);
		}
	}
	if (m3 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m3->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m3->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m3->m_AssociatedRegion);
		}
	}
	if (m4 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m4->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m4->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m4->m_AssociatedRegion);
		}
	}
	if (m5 != nullptr) {

		if (_isRegionClaimedAlreadyByThisCity(m5->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m5->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m5->m_AssociatedRegion);
		}
	}
	if (m6 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m6->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m6->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m6->m_AssociatedRegion);
		}
	}
	if (m7 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m7->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m7->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m7->m_AssociatedRegion);
		}
	}
	if (m8 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m8->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m8->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m8->m_AssociatedRegion);
		}
	}
}


void City::_claimTertiaryReions() {

	// Tertiry regions are that tiles, that are 3 tiles away around city.
	// Those are 12.
	int city_pos[2];
	city_pos[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	city_pos[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];

	int up[2], right[2], down[2], left[2],
		left_up[2], right_up[2], down_left[2], down_right[2],
		left_up_2[2], right_up_2[2], down_left_2[2], down_right_2[2];

	right[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 3;
	right[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];

	left[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 3;
	left[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];

	up[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	up[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 3;

	down[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	down[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 3;


	left_up[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 1;
	left_up[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 2;

	right_up[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 1;
	right_up[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 2;

	down_left[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 1;
	down_left[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 2;

	down_right[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 1;
	down_right[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 2;


	left_up_2[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] -2;
	left_up_2[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 1;

	right_up_2[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 2;
	right_up_2[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 1;

	down_left_2[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 2;
	down_left_2[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 1;

	down_right_2[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 2;
	down_right_2[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 1;



	MapTile* m1, * m2, * m3, * m4, * m5, * m6, * m7, * m8,* m9, * m10, * m11, * m12;
	m1 = GetMapTileAtWorldPosition(right[0], right[1]);
	m2 = GetMapTileAtWorldPosition(left[0], left[1]);
	m3 = GetMapTileAtWorldPosition(up[0], up[1]);
	m4 = GetMapTileAtWorldPosition(down[0], down[1]);
	m5 = GetMapTileAtWorldPosition(down_right[0], down_right[1]);
	m6 = GetMapTileAtWorldPosition(down_left[0], down_left[1]);
	m7 = GetMapTileAtWorldPosition(right_up[0], right_up[1]);
	m8 = GetMapTileAtWorldPosition(left_up[0], left_up[1]);
	m9 = GetMapTileAtWorldPosition(left_up_2[0], left_up_2[1]);
	m10 = GetMapTileAtWorldPosition(right_up_2[0], right_up_2[1]);
	m11 = GetMapTileAtWorldPosition(down_left_2[0], down_left_2[1]);
	m12 = GetMapTileAtWorldPosition(down_right_2[0], down_right_2[1]);

	// Here we must test whether the tile is valid.
	if (m1 != nullptr) {

		if (_isRegionClaimedAlreadyByThisCity(m1->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m1->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m1->m_AssociatedRegion);
		}
	}
	if (m2 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m2->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m2->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m2->m_AssociatedRegion);
		}
	}
	if (m3 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m3->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m3->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m3->m_AssociatedRegion);
		}
	}
	if (m4 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m4->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m4->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m4->m_AssociatedRegion);
		}
	}
	if (m5 != nullptr) {

		if (_isRegionClaimedAlreadyByThisCity(m5->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m5->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m5->m_AssociatedRegion);
		}
	}
	if (m6 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m6->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m6->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m6->m_AssociatedRegion);
		}
	}
	if (m7 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m7->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m7->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m7->m_AssociatedRegion);
		}
	}
	if (m8 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m8->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m8->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m8->m_AssociatedRegion);
		}
	}
	if (m9 != nullptr) {

		if (_isRegionClaimedAlreadyByThisCity(m9->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m9->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m9->m_AssociatedRegion);
		}
	}
	if (m10 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m10->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m10->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m10->m_AssociatedRegion);
		}
	}
	if (m11 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m11->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m11->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m11->m_AssociatedRegion);
		}
	}
	if (m12 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m12->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m12->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m12->m_AssociatedRegion);
		}
	}
}



void City::_claimQuartaryRegions() {

	// Tertiry regions are that tiles, that are 3 tiles away around city.
	// Those are 16.
	int city_pos[2];
	city_pos[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	city_pos[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];


	int up[2], right[2], down[2], left[2],
		left_up[2], right_up[2], down_left[2], down_right[2],
		left_up_2[2], right_up_2[2], down_left_2[2], down_right_2[2],
		left_up_3[2], right_up_3[2], down_left_3[2], down_right_3[2];



	right[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 4;
	right[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];

	left[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 4;
	left[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];

	up[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	up[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 4;

	down[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	down[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 4;


	left_up[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 1;
	left_up[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 3;

	right_up[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 1;
	right_up[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 3;

	down_left[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 1;
	down_left[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 3;

	down_right[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 1;
	down_right[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 3;


	left_up_2[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 2;
	left_up_2[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 2;

	right_up_2[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 2;
	right_up_2[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 2;

	down_left_2[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 2;
	down_left_2[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 2;

	down_right_2[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 2;
	down_right_2[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 2;

	left_up_3[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 3;
	left_up_3[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 1;

	right_up_3[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 3;
	right_up_3[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 1;

	down_left_3[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 3;
	down_left_3[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 1;

	down_right_3[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 3;
	down_right_3[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 1;



	MapTile* m1, * m2, * m3, * m4, * m5, * m6, * m7, * m8, * m9, * m10, * m11, * m12, * m13, * m14, * m15, * m16;
	m1 = GetMapTileAtWorldPosition(right[0], right[1]);
	m2 = GetMapTileAtWorldPosition(left[0], left[1]);
	m3 = GetMapTileAtWorldPosition(up[0], up[1]);
	m4 = GetMapTileAtWorldPosition(down[0], down[1]);

	m5 = GetMapTileAtWorldPosition(down_right[0], down_right[1]);
	m6 = GetMapTileAtWorldPosition(down_left[0], down_left[1]);
	m7 = GetMapTileAtWorldPosition(right_up[0], right_up[1]);
	m8 = GetMapTileAtWorldPosition(left_up[0], left_up[1]);

	m9 = GetMapTileAtWorldPosition(left_up_2[0], left_up_2[1]);
	m10 = GetMapTileAtWorldPosition(right_up_2[0], right_up_2[1]);
	m11 = GetMapTileAtWorldPosition(down_left_2[0], down_left_2[1]);
	m12 = GetMapTileAtWorldPosition(down_right_2[0], down_right_2[1]);

	m13 = GetMapTileAtWorldPosition(left_up_3[0], left_up_3[1]);
	m14 = GetMapTileAtWorldPosition(right_up_3[0], right_up_3[1]);
	m15 = GetMapTileAtWorldPosition(down_left_3[0], down_left_3[1]);
	m16 = GetMapTileAtWorldPosition(down_right_3[0], down_right_3[1]);


	// Here we must test whether the tile is valid.
	if (m1 != nullptr) {

		if (_isRegionClaimedAlreadyByThisCity(m1->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m1->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m1->m_AssociatedRegion);
		}
	}
	if (m2 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m2->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m2->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m2->m_AssociatedRegion);
		}
	}
	if (m3 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m3->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m3->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m3->m_AssociatedRegion);
		}
	}
	if (m4 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m4->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m4->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m4->m_AssociatedRegion);
		}
	}
	if (m5 != nullptr) {

		if (_isRegionClaimedAlreadyByThisCity(m5->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m5->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m5->m_AssociatedRegion);
		}
	}
	if (m6 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m6->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m6->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m6->m_AssociatedRegion);
		}
	}
	if (m7 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m7->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m7->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m7->m_AssociatedRegion);
		}
	}
	if (m8 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m8->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m8->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m8->m_AssociatedRegion);
		}
	}
	if (m9 != nullptr) {

		if (_isRegionClaimedAlreadyByThisCity(m9->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m9->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m9->m_AssociatedRegion);
		}
	}
	if (m10 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m10->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m10->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m10->m_AssociatedRegion);
		}
	}
	if (m11 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m11->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m11->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m11->m_AssociatedRegion);
		}
	}
	if (m12 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m12->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m12->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m12->m_AssociatedRegion);
		}
	}
	if (m13 != nullptr) {

		if (_isRegionClaimedAlreadyByThisCity(m13->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m13->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m13->m_AssociatedRegion);
		}
	}
	if (m14 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m14->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m14->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m14->m_AssociatedRegion);
		}
	}
	if (m15 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m15->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m15->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m15->m_AssociatedRegion);
		}
	}
	if (m16 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m16->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m16->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m16->m_AssociatedRegion);
		}
	}
}







bool City::_isRegionClaimedAlreadyByThisCity(MapTileRegion* region) {

	std::vector<MapTileRegion*> vec = m_ClaimedRegions;
	MapTileRegion* r = nullptr;

	for (auto it = vec.begin(); it != vec.end(); ++it) {

		r = *it;

		if (COMPARE_STRINGS_2(r->m_IDCmp->m_ID, region->m_IDCmp->m_ID) == 0) return true;
	}

	return false;
}


bool City::_isRegionClaimedByOtherCity(MapTileRegion* region) {

	if (region == nullptr) throw;

	if (region->m_AssociatedPlayer == nullptr) return false;
	else return true;
}


void City::_setSpriteForClaimedRegion() {

	for (auto it : m_ClaimedRegions) {

		it->m_GraphicsCmp->m_SpriteName = m_ClaimedRegionsSpriteName;
	}
}



void EntitiesStorage::RemovePlayer(std::string playername) {

	for (auto it : *m_PlayersVec) {
		if (COMPARE_STRINGS_2(it->m_PlayerName, playername) == 0) {
			RemovePlayer(it);
		}
	}
}

void EntitiesStorage::RemovePlayer(Player* p) {

	std::vector<Player*>::iterator it = std::find(m_PlayersVec->begin(), m_PlayersVec->end(), p);
	if (it != m_PlayersVec->end()) m_PlayersVec->erase(it);
}


std::string City::GetCurrentCitySprite() {

	switch (m_CitySizeClass)
	{
	case CitySizeClass::CITY_SIZE_CLASS_SMALL:
		return m_CitySpritesStorage->m_SmallCitySprite;
		break;
	case CitySizeClass::CITY_SIZE_CLASS_NORMAL:
		return m_CitySpritesStorage->m_NormalCitySprite;
		break;
	case CitySizeClass::CITY_SIZE_CLASS_BIG:
		return m_CitySpritesStorage->m_BigCitySprite;
		break;
	case CitySizeClass::CITY_SIZE_CLASS_HUGE:
		return m_CitySpritesStorage->m_HugeCitySprite;
		break;

	default:
		break;
	}
	
}


City::City(std::string cityname, bool city, CMPEntityRace::Race race, Player* player, int xpos, int ypos, int citySize) {

	m_IDCmp->m_DynamicTypeName = "City";


	m_CityName = cityname;
	m_CitySize = citySize;
	_updateCitySizeClass();

	m_CityRaceCmp = new CMPEntityRace(CMPEntityRace::Race::RACE_INVALID);
	_deriveCityRace(race); // Initializes the race for the city.

	m_CityType = (city == true) ? City::CityType::CITY_TYPE_CITY : City::CityType::CITY_TYPE_FORT;


	m_GraphicsCmp = new CMPGraphics();
	m_GraphicsCmp->m_DrawingLayer = "layer2";
	m_CitySpritesStorage = new CitySpritesHolder();
	_deriveCitySprites(); // Derives the cities sprites for the specific race.

	m_TransformCmp->m_PosX = xpos;
	m_TransformCmp->m_PosY = ypos;


	m_AICmp = new CMPArtificialIntelligence(this);

	m_AssociatedPlayer = player;
	player->AddCity(this);
	_determineMapCell(m_AssociatedPlayer->m_PlayerColor);
}


std::string City::GetCityLandscapeTypeString() {
	switch (*m_CityLandscapeType) {
	case CityLandscapeType::CITY_LANDSCAPE_FOREST:
		return "Forest";
		break;
	case CityLandscapeType::CITY_LANDSCAPE_MOUNTAINS:
		return "Mountains";
		break;
	case CityLandscapeType::CITY_LANDSCAPE_HILLS:
		return "Hills";
		break;
	case CityLandscapeType::CITY_LANDSCAPE_PLAIN:
		return "Plain";
		break;
	default:
		throw;
		break;
	}
}


City::CityLandscapeType City::GetCityLandscapeType() {
	return *m_CityLandscapeType;
}



bool Player::_isMapTileSurroundedByOwnTiles(MapTile* tile) {

	MapTile* other_tile = nullptr;

	bool up = false, down = false, left = false, right = false;

	int up_tile[2], down_tile[2], left_tile[2], right_tile[2];

	up_tile[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0];
	up_tile[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1] - 1;

	down_tile[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0];
	down_tile[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1] + 1;

	left_tile[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0] - 1;
	left_tile[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1];

	right_tile[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0] + 1;
	right_tile[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1];



	if (IsIndexOutOfBound(up_tile[0], up_tile[1]) == false) {

		other_tile = GetMapTileAtWorldPosition(up_tile[0], up_tile[1]);
		if (other_tile) {

			if (_belongMapTileToThisPlayer(other_tile) == false) {

				// The up tile belongs to us, thus no border in up diretion.
				up = false;
			}
			else {

				// MAptile does not belong to us, thus border in up dir.
				up = true;

			}
		}

	}
	else {
		// Map end in up direction means its a border.
		up = true;
	}


	other_tile = nullptr;
	if (IsIndexOutOfBound(down_tile[0], down_tile[1]) == false) {

		other_tile = GetMapTileAtWorldPosition(down_tile[0], down_tile[1]);
		if (other_tile) {

			if (_belongMapTileToThisPlayer(other_tile) == false) {

				// The up tile belongs to us, thus no border in up diretion.
				down = false;
			}
			else {

				// MAptile does not belong to us, thus border in up dir.
				down = true;

			}
		}

	}
	else {
		// Map end in up direction means its a border.
		down = true;
	}


	other_tile = nullptr;
	if (IsIndexOutOfBound(left_tile[0], left_tile[1]) == false) {

		other_tile = GetMapTileAtWorldPosition(left_tile[0], left_tile[1]);
		if (other_tile) {

			if (_belongMapTileToThisPlayer(other_tile) == false) {

				// The up tile belongs to us, thus no border in up diretion.
				left = false;
			}
			else {

				// MAptile does not belong to us, thus border in up dir.
				left = true;

			}
		}

	}
	else {
		// Map end in up direction means its a border.
		left = true;
	}


	other_tile = nullptr;
	if (IsIndexOutOfBound(right_tile[0], right_tile[1]) == false) {

		other_tile = GetMapTileAtWorldPosition(right_tile[0], right_tile[1]);
		if (other_tile) {

			if (_belongMapTileToThisPlayer(other_tile) == false) {

				// The up tile belongs to us, thus no border in up diretion.
				right = false;
			}
			else {

				// MAptile does not belong to us, thus border in up dir.
				right = true;

			}
		}

	}
	else {
		// Map end in up direction means its a border.
		right = true;
	}


	return (up && right && left && down);
}

bool Player::_belongMapTileToThisPlayer(MapTile* tile) {

	MapTile* maptile = nullptr;

	for (auto it : m_PlayerCities) {

		for (auto iter : it->m_ClaimedRegions) {

			
			for (auto itr : iter->m_MapTileRegionTiles) {

				maptile = itr;

				if (maptile == tile) return true;
			}

		}

	}

	return false;

}


void City::_determineCityBorderTiles() {

	// Iterate through each regions maptiles.
	MapTileRegion* region = nullptr;
	MapTile* tile = nullptr;

	int tile_up[2], tile_down[2], tile_right[2], tile_left[2];

	bool up = false, down = false, right = false, left = false;


	for (auto it = m_ClaimedRegions.begin(); it != m_ClaimedRegions.end(); ++it) {

		region = *it;

		for (auto iter = region->m_MapTileRegionTiles.begin(); iter != region->m_MapTileRegionTiles.end(); ++iter) {

			tile = *iter;


			tile_up[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0];
			tile_up[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1] - 1;

			tile_down[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0];
			tile_down[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1] + 1;

			tile_right[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0] + 1;
			tile_right[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1];

			tile_left[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0] - 1;
			tile_left[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1];



			if (_isMapTileClaimedByCity(GetMapTileAtWorldPosition(tile_up[0], tile_up[1]))) { // true, if up is own maptile.
				up = true;
			}

			if (_isMapTileClaimedByCity(GetMapTileAtWorldPosition(tile_down[0], tile_down[1]))) {
				down = true;
			}

			if (_isMapTileClaimedByCity(GetMapTileAtWorldPosition(tile_right[0], tile_right[1]))) {
				right = true;
			}

			if (_isMapTileClaimedByCity(GetMapTileAtWorldPosition(tile_left[0], tile_left[1]))) {
				left = true;
			}





			if (up && down && right && left){
				// Means, this tile is surrounded by own, so no border tile.

				// reset for next tile.
				up = down = left = right = false;
				continue;
			}
			else {
				m_CityBorderMapTileVec.push_back(tile);
				up = down = left = right = false;
			}
		}
	}
}


void City::_determineMapTilesBorderDirection() {

	// Iterate through all border tiles.
	MapTile* tile = nullptr;
	int tile_up[2], tile_down[2], tile_right[2], tile_left[2];

	bool border_up = false, border_down = false, border_right = false, border_left = false;


	for (auto it = m_CityBorderMapTileVec.begin(); it != m_CityBorderMapTileVec.end(); ++it) {

		tile = *it;

		tile_up[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0];
		tile_up[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1] - 1;

		tile_down[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0];
		tile_down[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1] + 1;

		tile_right[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0] + 1;
		tile_right[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1];

		tile_left[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0] - 1;
		tile_left[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1];


		// Determine the border direction.
		if (_isMapTileClaimedByCity(GetMapTileAtWorldPosition(tile_up[0], tile_up[1])) == false) {

			// .. border in up direction.
			border_up = true;
		}
		
		if (_isMapTileClaimedByCity(GetMapTileAtWorldPosition(tile_down[0], tile_down[1])) == false) {
			
			// .. border in down direction.
			border_down = true;
		}
		
		if (_isMapTileClaimedByCity(GetMapTileAtWorldPosition(tile_right[0], tile_right[1])) == false) {
			
			// .. border in right direction.
			border_right = true;
		}
		
		if (_isMapTileClaimedByCity(GetMapTileAtWorldPosition(tile_left[0], tile_left[1])) == false) {
			
			// .. border in left direction.
			border_left = true;
		}

		
		// Define decal for appropriate bordertype.
		// In order to get valid results, we must iterate backwards all possibilities.
		if (border_up && border_down && border_right && !border_left) { // Three borders.
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_down_up_right"));

		}
		else if (!border_up && border_down && border_right && border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_left_right_down"));

		}
		else if (border_up && border_down && !border_right && border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_left_up_down"));

		}
		else if (border_up && !border_down && border_right && border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_left_up_right"));

		}
		else if (border_up && border_down && !border_right && !border_left) { // Two borders
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_up_down"));

		}
		else if (border_up && !border_down && border_right && !border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_up_right"));

		}
		else if (border_up && !border_down && !border_right && border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_up_left"));

		}
		else if (!border_up && border_down && border_right && !border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_down_right"));

		}
		else if (!border_up && border_down && !border_right && border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_down_left"));

		}
		else if (!border_up && !border_down && border_right && border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_left_right"));

		}
		else if (border_up && !border_down && !border_right && !border_left) { // One border.
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_up"));

		}
		else if (!border_up && border_down && !border_right && !border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_down"));

		}
		else if (!border_up && !border_down && border_right && !border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_right"));

		}
		else if (!border_up && !border_down && !border_right && border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_left"));

		}
		else {
			//throw;
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_down_up_right"));
		}


		// Reset border flags...
		border_up = false, border_down = false, border_right = false, border_left = false;
	}
}


bool City::_isMapTileClaimedByCity(MapTile* maptile) {

	if (maptile == nullptr) return false;

	/*
	MapTile* other_tile = nullptr;

	// See whether we have claimed the region that has this maptile.
	for (auto it : this->m_ClaimedRegions) {
		for (auto iter : it->m_MapTileRegionTiles) {

			other_tile = iter;
			if (other_tile == maptile) return true;
		}
	}
	*/
	
	for (auto it : this->m_ClaimedRegions) {
		for (auto iter : it->m_MapTileRegionTiles) {
			if (maptile->m_AssociatedRegion == iter->m_AssociatedRegion) return true;
		}
	}
	
	return false;
}

unsigned int  Unit::_determineMovementPoints() {

	int fatigue = this->m_UnitAttributesMap->at(UnitAttributesEnum::UNIT_ATTRIBUTE_FATIGUE);
	int speed = this->m_UnitAttributesMap->at(UnitAttributesEnum::UNIT_ATTRIBUTE_SPEED);

	m_MovementPoints = int((fatigue * speed) / 10 );

	return m_MovementPoints;
}

void  Unit::_resetMovementPoints() {

	m_MovementPoints = _determineMovementPoints();
}


bool Unit::DetermineTilesInMovementRange2(std::map<MapTile*, int>* storage) {

	using namespace std;
	cout << APP_SUCCESS_COLOR << endl;

	// NOTE:
	// We associate every maptile with a cost, and store it in given map.

	std::vector<MapTile*>* vec = nullptr;
	std::vector<MapTile*>* sec_vec = nullptr;
	std::vector<MapTile*>* third_vec = nullptr;
	std::vector<MapTile*>* fourth_vec = nullptr;



	vec = _getNeighbouringMapTiles(m_TransformCmp->m_GameWorldSpaceCell[0], m_TransformCmp->m_GameWorldSpaceCell[1]); // Has neighbors.


	MapTile* maptile = nullptr;
	MapTile* sec_maptile = nullptr;
	MapTile* third_maptile = nullptr;
	MapTile* fourth_maptile = nullptr;



	// Some test.
	// Try insert cost for immediate neighbors right now.
	for (auto it = vec->begin(); it != vec->end(); ++it) {

		maptile = *it;

		int cost = maptile->m_MovementCostCmp->GetRaceModifiedMovementCost(m_EntityRaceCmp->m_EntityRaceString);

		if (m_MovementPoints - (cost) >= 0) { // Very probably it will be true.

			storage->insert(std::make_pair(maptile, cost));

			cout << APP_SUCCESS_COLOR;
			cout << "Inserted " << maptile->m_IDCmp->m_DynamicTypeName << " at (" << maptile->m_TransformCmp->m_GameWorldSpaceCell[0] << ":" << maptile->m_TransformCmp->m_GameWorldSpaceCell[1] << ") ";
			cout << " with cost of " << cost << "." << white << endl;
		}
	}


	maptile = nullptr;


	while (vec->size() > 0) {

		// Iterate reverse -> easier to delete checked maptile.
		maptile = vec->back();
		int maptile_cost = maptile->m_MovementCostCmp->GetRaceModifiedMovementCost(m_EntityRaceCmp->m_EntityRaceString);

		if (m_MovementPoints - (maptile_cost) >= 0) {

			storage->insert(std::make_pair(maptile, maptile_cost));

			cout << APP_SUCCESS_COLOR;
			cout << "Inserted " << maptile->m_IDCmp->m_DynamicTypeName << " at ("<<maptile->m_TransformCmp->m_GameWorldSpaceCell[0] << ":" << maptile->m_TransformCmp->m_GameWorldSpaceCell[1] <<") ";
			cout << " with cost of " << maptile_cost << "." << white << endl;
		}


		// Neighbors of checked maptile.
		sec_vec = _getNeighbouringMapTiles(maptile->m_TransformCmp->m_GameWorldSpaceCell[0], maptile->m_TransformCmp->m_GameWorldSpaceCell[1]);

		// Delete first "alpha_maptile" from sec_vec
		//_removeAlphaTileFromNeighboringMapTiles(maptile, sec_vec);


		while (sec_vec->size() > 0) {

			sec_maptile = sec_vec->back();

			// Maptile we are standing on are zero movement cost.
			if (_isMapTileWeAreStandingOn(sec_maptile)) {
				if (_isMapTileAlreadyInserted(sec_maptile, storage) == false) {

					storage->insert(std::make_pair(sec_maptile, 0));

					cout << APP_SUCCESS_COLOR;
					cout << "Inserted " << sec_maptile->m_IDCmp->m_DynamicTypeName << " at (" << sec_maptile->m_TransformCmp->m_GameWorldSpaceCell[0] << ":" << sec_maptile->m_TransformCmp->m_GameWorldSpaceCell[1] << ") ";
					cout << " with cost of " << 0 << "." << white << endl;
				}
				
				
				// Loop breaking. 
				sec_vec->pop_back();
				continue;
			}



			int sec_maptile_ost = sec_maptile->m_MovementCostCmp->GetRaceModifiedMovementCost(m_EntityRaceCmp->m_EntityRaceString);


			if ((m_MovementPoints - (sec_maptile_ost + maptile_cost)) >= 0) {

				if (_isMapTileAlreadyInserted(sec_maptile, storage) == false) {
					
					storage->insert(std::make_pair(sec_maptile, sec_maptile_ost + maptile_cost));

					cout << APP_SUCCESS_COLOR;
					cout << "Inserted " << sec_maptile->m_IDCmp->m_DynamicTypeName << " at (" << sec_maptile->m_TransformCmp->m_GameWorldSpaceCell[0] << ":" << sec_maptile->m_TransformCmp->m_GameWorldSpaceCell[1] << ") ";
					cout << " with cost of " << sec_maptile_ost + maptile_cost << "." << white << endl;
				}
			}




			// Third loop, teriatry checked tiles.
			third_vec = _getNeighbouringMapTiles(sec_maptile->m_TransformCmp->m_GameWorldSpaceCell[0], sec_maptile->m_TransformCmp->m_GameWorldSpaceCell[1]);

			while (third_vec->size() > 0) {

				third_maptile = third_vec->back();

				// No need to erase tile we are standing on, because it is not possible!
				// But we need to check for "alpha_maptile" for each new one.
				//if (COMPARE_STRINGS_2(third_maptile->m_IDCmp->m_ID, sec_maptile->m_IDCmp->m_ID) == 0) continue;


				// Get cost for tertiary maptile
				int third_maptile_cost = third_maptile->m_MovementCostCmp->GetRaceModifiedMovementCost(m_EntityRaceCmp->m_EntityRaceString);

				if ((m_MovementPoints - (third_maptile_cost + sec_maptile_ost + maptile_cost)) >= 0) {

					if (_isMapTileAlreadyInserted(third_maptile, storage) == false) {

						storage->insert(std::make_pair(third_maptile, third_maptile_cost + sec_maptile_ost + maptile_cost));

						cout << APP_SUCCESS_COLOR;
						cout << "Inserted " << third_maptile->m_IDCmp->m_DynamicTypeName << " at (" << third_maptile->m_TransformCmp->m_GameWorldSpaceCell[0] << ":" << third_maptile->m_TransformCmp->m_GameWorldSpaceCell[1] << ") ";
						cout << " with cost of " << third_maptile_cost + sec_maptile_ost + maptile_cost << "." << white << endl;
					}					
				}


				// Fourth Loop.
				// Get Neighbors.
				fourth_vec = _getNeighbouringMapTiles(third_maptile->m_TransformCmp->m_GameWorldSpaceCell[0], third_maptile->m_TransformCmp->m_GameWorldSpaceCell[1]);
				while (fourth_vec->size() > 0) {

					fourth_maptile = fourth_vec->back();



					// Get cost.
					int fourth_maptile_cost = fourth_maptile->m_MovementCostCmp->GetRaceModifiedMovementCost(m_EntityRaceCmp->m_EntityRaceString);

					if ((m_MovementPoints - (fourth_maptile_cost + third_maptile_cost + sec_maptile_ost + maptile_cost)) >= 0) {

						if (_isMapTileAlreadyInserted(fourth_maptile, storage) == false) {

							storage->insert(std::make_pair(fourth_maptile, fourth_maptile_cost + third_maptile_cost + sec_maptile_ost + maptile_cost));

							cout << APP_SUCCESS_COLOR;
							cout << "Inserted " << fourth_maptile->m_IDCmp->m_DynamicTypeName << " at (" << fourth_maptile->m_TransformCmp->m_GameWorldSpaceCell[0] << ":" << fourth_maptile->m_TransformCmp->m_GameWorldSpaceCell[1] << ") ";
							cout << " with cost of " << fourth_maptile_cost + third_maptile_cost + sec_maptile_ost + maptile_cost << "." << white << endl;
						}
					}



					// Loop breaking.
					fourth_vec->pop_back();

				}


				// Loop breaking.
				third_vec->pop_back();
			}



			// Loop breaking.
			sec_vec->pop_back();
		}



		// Loop breaking.
		vec->pop_back();
	}

	
	return true;
}


bool Unit::_isMapTileAlreadyInserted(MapTile* m, std::map<MapTile*, int>* storage) {

	for (auto it : *storage) {

		if (COMPARE_STRINGS_2(m->m_IDCmp->m_ID, it.first->m_IDCmp->m_ID) == 0) {

			return true;
		}
	}

	return false;
}


bool Unit::DetermineTilesInMovementRange(std::vector<MapTile*>* storage){

	// Check tiles if unit can reach them.
	// If we get only tiles we cant reach, then stop.

	// 1) Check tiles around unit.
	// 2) Check tiles 2 tiles around unit.
	// and so on.

	MapTile* maptile = nullptr;
	int move_cost = 0;

	std::vector<MapTile*> neighbors_vec = *_getNeighbouringMapTiles(this->m_TransformCmp->m_GameWorldSpaceCell[0], this->m_TransformCmp->m_GameWorldSpaceCell[1]);

	
	for (auto it = neighbors_vec.begin(); it != neighbors_vec.end(); ++it) {

		maptile = *it;
		move_cost = maptile->m_MovementCostCmp->GetRaceModifiedMovementCost(this->m_EntityRaceCmp->m_EntityRaceString);

		if ((m_MovementPoints - move_cost) >= 0) {

			storage->push_back(maptile);
		}
	}

	neighbors_vec.clear();

	return((storage->size() > 0) ? true : false);
}


bool Unit::_isMapTileWeAreStandingOn(MapTile* m) {

	if (m->m_TransformCmp->m_GameWorldSpaceCell[0] == m_TransformCmp->m_GameWorldSpaceCell[0] &&
		m->m_TransformCmp->m_GameWorldSpaceCell[1] == m_TransformCmp->m_GameWorldSpaceCell[1]) {

		return true;
	}

	return false;
}


void Unit::_removeAlphaTileFromNeighboringMapTiles(MapTile* alpha, std::vector<MapTile*>* storage) {

	GameEntity* entt = nullptr;

	for (auto it = storage->begin(); it != storage->end(); ++it) {

		entt = *it;

		if (COMPARE_STRINGS_2(alpha->m_IDCmp->m_ID, entt->m_IDCmp->m_ID) == 0) {

			storage->erase(it);
		}
	}

	/*
	std::vector<MapTile*>::iterator it = std::find(storage->begin(), storage->end(), alpha);

	if (it != storage->end()) {
		storage->erase(it);
	}
	*/
}

void Unit::_removeAlphaTileFromNeighboringMapTiles(MapTile* alpha, std::map<MapTile*, int>* storage) {

	GameEntity* entt = nullptr;

	for (auto it = storage->begin(); it != storage->end(); ++it) {

		entt = it->first;

		if (COMPARE_STRINGS_2(alpha->m_IDCmp->m_ID, entt->m_IDCmp->m_ID) == 0) {

			storage->erase(it);
		}
	}

	/*
	for (auto it : *storage) {
		if (COMPARE_STRINGS_2(alpha->m_IDCmp->m_ID, it.first->m_IDCmp->m_ID)) {
			storage->erase(it.first);
		}
	}
	*/
}


int Unit::_getCurrentCostForTile(int previously_accumulated_cost, MapTile* maptile) {

	int tile_cost = maptile->m_MovementCostCmp->GetRaceModifiedMovementCost(m_EntityRaceCmp->m_EntityRaceString);
	return previously_accumulated_cost + tile_cost;
}


std::vector<MapTile*>* Unit::_getNeighbouringMapTiles(int xpos, int ypos) {

	std::vector<MapTile*>* vec = new std::vector<MapTile*>();

	int up[2], down[2], right[2], left[2];

	up[0] = xpos;
	up[1] = ypos-1;

	down[0] = xpos;
	down[1] = ypos+1;

	right[0] = xpos+1;
	right[1] = ypos;

	left[0] = xpos-1;
	left[1] = ypos;

	MapTile* tile = nullptr;

	tile = GetMapTileAtWorldPosition(up[0], up[1]);
	if (tile) vec->push_back(tile);
	tile = nullptr;

	tile = GetMapTileAtWorldPosition(down[0], down[1]);
	if (tile) vec->push_back(tile);
	tile = nullptr;

	tile = GetMapTileAtWorldPosition(right[0], right[1]);
	if (tile) vec->push_back(tile);
	tile = nullptr;

	tile = GetMapTileAtWorldPosition(left[0], left[1]);
	if (tile) vec->push_back(tile);
	tile = nullptr;


	return vec;
}


// Move unit to a location.
void Unit::MoveTo(int x_cell, int y_cell) {

	using namespace std;

	/*
	NOTE:
	We need to move from one tile to next.
	Not from x,y to x´,y´.

	Moreover we need to move so many tiles every TURN, not immediately.
	Furthermore we need to have a defined "way" of moving, that is PATH.
	

	But for now, we test moving directly to destination.
	*/
	int curr_pos_x, curr_pos_y;
	curr_pos_x = m_TransformCmp->m_PosX;
	curr_pos_y = m_TransformCmp->m_PosY;

	int curr_tile[2];
	curr_tile[0] = m_TransformCmp->m_GameWorldSpaceCell[0];
	curr_tile[1] = m_TransformCmp->m_GameWorldSpaceCell[1];



	MapTile* tile = GetMapTileAtWorldPosition(x_cell, y_cell);
	if (tile == nullptr) return;

	int tile_pos[2] = { tile->m_TransformCmp->m_PosX, tile->m_TransformCmp->m_PosY }; // Destination tilepos in x,y position.

	// Instant teleportation to that position.
	m_TransformCmp->m_PosX = tile_pos[0];
	m_TransformCmp->m_PosY = tile_pos[1];

	m_TransformCmp->m_GameWorldSpaceCell[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0];
	m_TransformCmp->m_GameWorldSpaceCell[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1];



	cout << APP_ERROR_COLOR << endl;
	cout << "Unit " << this->m_Name << " moved from (" << curr_pos_x << ":" << curr_pos_y << ") ::= (" << curr_tile[0] << ":" << curr_tile[1] << ") to" << endl;
	cout << "(" << m_TransformCmp->m_PosX << ":" << m_TransformCmp->m_PosY << ") ::= (" << m_TransformCmp->m_GameWorldSpaceCell[0] << ":" << m_TransformCmp->m_GameWorldSpaceCell[1] << ")." << white << endl;
}

// Unit cease to exist.
void Unit::Die() {

}


















/*
UNIT AI LOGIC.
*/

UnitWaitLogic::UnitWaitLogic(CMPArtificialIntelligence& ai) {

	m_AICmp = &ai;
	m_ManagedUnit = static_cast<Unit*>(m_AICmp->m_ManagedObject);
}

UnitWaitLogic::~UnitWaitLogic() {

}

UnitPatrolLogic::UnitPatrolLogic(CMPArtificialIntelligence& ai, bool circle, States endpointstate) {

	// Specify endpoint state.
	m_TransitState = endpointstate;
	if (circle == false) { // Enforce a valid state to transit to.
		if (m_TransitState == States::STATE_INVALID) throw std::runtime_error(std::string("INVALID OR NO TRANSIT STATE SPECIFIED."));
	}


	m_AICmp = &ai;
	m_ManagedUnit = static_cast<Unit*>(m_AICmp->m_ManagedObject);
}

UnitPatrolLogic::~UnitPatrolLogic() {

}

UnitMoveLogic::UnitMoveLogic(CMPArtificialIntelligence& ai) {

	m_AICmp = &ai;
	m_ManagedUnit = static_cast<Unit*>(m_AICmp->m_ManagedObject);
}

UnitMoveLogic::~UnitMoveLogic() {

}

UnitAttackLogic::UnitAttackLogic(CMPArtificialIntelligence& ai) {

	m_AICmp = &ai;
	m_ManagedUnit = static_cast<Unit*>(m_AICmp->m_ManagedObject);
}

UnitAttackLogic::~UnitAttackLogic() {

}


UnitDefendLogic::UnitDefendLogic(CMPArtificialIntelligence& ai) {

	m_AICmp = &ai;
	m_ManagedUnit = static_cast<Unit*>(m_AICmp->m_ManagedObject);
}

UnitDefendLogic::~UnitDefendLogic() {

}

UnitDieLogic::UnitDieLogic(CMPArtificialIntelligence& ai) {

	m_AICmp = &ai;
	m_ManagedUnit = static_cast<Unit*>(m_AICmp->m_ManagedObject);
}

UnitDieLogic::~UnitDieLogic() {

}


UnitSearchLogic::UnitSearchLogic(CMPArtificialIntelligence& ai) {

	m_AICmp = &ai;
	m_ManagedUnit = static_cast<Unit*>(m_AICmp->m_ManagedObject);
}

UnitSearchLogic::~UnitSearchLogic() {

}


UnitFleeLogic::UnitFleeLogic(CMPArtificialIntelligence& ai) {

	m_AICmp = &ai;
	m_ManagedUnit = static_cast<Unit*>(m_AICmp->m_ManagedObject);
}

UnitFleeLogic::~UnitFleeLogic() {

}








void UnitFleeLogic::executeStateLogic() {

	using namespace std;



	cout << color(colors::DARKGREEN);
	cout << "UnitFleeLogic::executeStateLogic() executed for ";
	cout << this->m_ManagedUnit->m_Name << white << endl;
}

void UnitSearchLogic::executeStateLogic() {

	using namespace std;




	cout << color(colors::DARKGREEN);
	cout << "UnitSearchLogic::executeStateLogic() executed for ";
	cout << this->m_ManagedUnit->m_Name << white << endl;
}

void UnitDieLogic::executeStateLogic() {

	using namespace std;




	cout << color(colors::DARKGREEN);
	cout << "UnitDieLogic::executeStateLogic() executed for ";
	cout << this->m_ManagedUnit->m_Name << white << endl;
}

void UnitDefendLogic::executeStateLogic() {

	using namespace std;




	cout << color(colors::DARKGREEN);
	cout << "UnitDefendLogic::executeStateLogic() executed for ";
	cout << this->m_ManagedUnit->m_Name << white << endl;
}

void UnitAttackLogic::executeStateLogic() {

	using namespace std;




	cout << color(colors::DARKGREEN);
	cout << "UnitAttackLogic::executeStateLogic() executed for ";
	cout << this->m_ManagedUnit->m_Name << white << endl;
}

void UnitMoveLogic::executeStateLogic() {

	using namespace std;




	cout << color(colors::DARKGREEN);
	cout << "UnitMoveLogic::executeStateLogic() executed for ";
	cout << this->m_ManagedUnit->m_Name << white << endl;
}

void UnitPatrolLogic::executeStateLogic() {

	using namespace olc;
	using namespace std;

	cout << color(colors::DARKGREEN);
	cout << "UnitPatrolLogic::executeStateLogic() executed for ";
	cout << this->m_ManagedUnit->m_Name << white << endl;



	Unit* object = m_ManagedUnit;

	if (object) {

		cout << color(colors::DARKGREEN);
		cout << "Begin Patroling routine for " << object->m_Name << "." << white << endl;

		if (m_PatrolPointReached == false) {

			//object->physicsCmp->m_Acceleration += 1.5f;

			
			vi2d p1 = vi2d(m_PatrolPoints[0].x, m_PatrolPoints[0].y); // Point to reach, coordinates are maptile positions.
			vi2d p2 = vi2d(object->m_TransformCmp->m_GameWorldSpaceCell[0], object->m_TransformCmp->m_GameWorldSpaceCell[1]); // Where we are.

			/*
			vi2d endpoint = p1 - p2;
			*/
			vi2d endpoint;

			if (p1.x > p2.x) endpoint.x = p2.x + 1;
			if (p1.x < p2.x) endpoint.x = p2.x - 1;
			if (p1.x == p2.x) endpoint.x = p2.x; // X position reached.

			if (p1.y > p2.y) endpoint.y = p2.y + 1;
			if (p1.y < p2.y) endpoint.y = p2.y - 1;
			if (p1.y == p2.y) endpoint.y = p2.y; // Y position reached.


			// We are giving the worldmap cell coordinates which we wish to reach.
			object->MoveTo(endpoint.x, endpoint.y);

			vi2d left = (p1 - p2);
			cout << color(colors::CYAN) << object->m_Name << " left to reach patrolpoint ::= " << left.str() << white << endl;

			if ((endpoint - p2) == vi2d(0, 0)) m_PatrolPointReached = true;

		}
		else {

			if (m_TransitState != States::STATE_INVALID && m_PatrolPoints.size() > 0) { // Valid transit state given => no looping of patrol route.

				if (m_PatrolPoints.size() > 0) { // Not all points reached, patrol further.

					m_PatrolPoints.erase(m_PatrolPoints.begin());
					m_PatrolPointReached = false;


					if (m_PatrolPoints.size() == 0) { // All patrol points reached, change state.

						object->m_AICmp->ChangeState(m_TransitState);

						cout << color(colors::DARKGREEN);
						cout << "Patroling routine for " << object->m_Name << " complete." << white << endl;
					}
				}
			}
			else { // circle = true => looping of patrol route.

				// Append the current reached patrol point to the end.
				m_PatrolPoints.push_back(m_PatrolPoints[0]);
				m_PatrolPoints.erase(m_PatrolPoints.begin());

				m_PatrolPointReached = false;

				cout << color(colors::DARKGREEN);
				cout << "Patroling point reached for " << object->m_Name << ". Continue to next Patroling point." << white << endl;
			}
		}

	}
	else {
		return;
	}
}

void UnitWaitLogic::executeStateLogic() {

	using namespace std;




	cout << color(colors::DARKGREEN);
	cout << "UnitWaitLogic::executeStateLogic() executed for ";
	cout << this->m_ManagedUnit->m_Name << white << endl;
}