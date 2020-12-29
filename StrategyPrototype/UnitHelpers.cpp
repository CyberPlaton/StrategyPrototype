// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include"UnitHelpers.h"

UnitNames* UnitNames::g_pUnitNames = nullptr;


std::string UnitNames::m_HumanNames[10] = {
	"Walter", "Fred", "Azazel", "Samuel", "Peter",
	"Azamat", "Johann", "Alexander", "Antoine", "Martin"
};

std::string UnitNames::m_DwarfNames[10] = {
	"Khenduirmog", "Drormun", "Idrugs", "Togdimik", "Mildhourn",
	"Arrus", "Brolder", "Erdudor", "Amiahr", "Kongil"
};

std::string UnitNames::m_GnomeNames[10] = {
		"Glomlish", "Mibic", "Caban", "Ireti", "Beetlatirn",
		"Monorn", "Cirlee", "Danlus", "Amiahr", "Kongil"
};

std::string UnitNames::m_HighelfNames[10] = {
		"Larenril", "Lannath", "Parlen", "Itanis", "Nornis",
		"Toric", "Ketheol", "Rahash", "Paald", "Alathar"
};


std::string UnitNames::m_DarkelfNames[10] = {
		"Keanal", "Evethas", "Denathir", "Myriel", "Eryeth",
		"Barinis", "Kariel", "Elendaar", "Kethae", "Felodren"
};

std::string UnitNames::m_GoblinNames[10] = {
		"Anba", "Zyxdekle", "Kweelbygeld", "Dozmil", "Jeeshas",
		"Salval", "Joza", "Qynk", "Ives", "Vaveqald"
};

std::string UnitNames::m_OrcNames[10] = {
			"Grolgul", "Drerl", "Thras", "Atorn", "Krohlgaldorn",
			"Kas", "Mamgomm", "Qynk", "Kruz", "Hargorimm"
};

std::string UnitNames::m_TrollNames[10] = {
			"Tudaro", "Ug´zun", "Rhaa´de", "Weghonjak", "Tzoxu",
			"Poje", "Dra´gan", "Oya", "Sas´zash", "Ozaapen"
};



std::string UnitNames::GetRandomTrollName() {

	int r = Random() % m_TrollNames->size();

	return m_TrollNames[r];
}


std::string UnitNames::GetRandomHumanName() {

	int r = Random() % m_HumanNames->size();

	return m_HumanNames[r];
}

std::string UnitNames::GetRandomHighelfName() {

	int r = Random() % m_HighelfNames->size();

	return m_HighelfNames[r];
}

std::string UnitNames::GetRandomDarkelfName() {

	int r = Random() % m_DarkelfNames->size();

	return m_DarkelfNames[r];
}

std::string UnitNames::GetRandomOrcName() {

	int r = Random() % m_OrcNames->size();

	return m_OrcNames[r];
}

std::string UnitNames::GetRandomGnomeName() {

	int r = Random() % m_GnomeNames->size();

	return m_GnomeNames[r];
}

std::string UnitNames::GetRandomDwarfName() {

	int r = Random() % m_DwarfNames->size();

	return m_DwarfNames[r];
}

std::string UnitNames::GetRandomGoblinName() {

	int r = Random() % m_GoblinNames->size();

	return m_GoblinNames[r];
}
