#pragma once
#include"Platform.h"

struct UnitNames {

	static UnitNames* Get() {

		if (g_pUnitNames) {
			return g_pUnitNames;
		}
		else {
			g_pUnitNames = new UnitNames();
			return g_pUnitNames;
		}
	}


	static void Del() {
		if (g_pUnitNames) {
			delete g_pUnitNames;
		}
	}


	static std::string GetRandomHumanName();
	static std::string GetRandomHighelfName();
	static std::string GetRandomDarkelfName();
	static std::string GetRandomOrcName();
	static std::string GetRandomGnomeName();
	static std::string GetRandomDwarfName();
	static std::string GetRandomGoblinName();
	static std::string GetRandomTrollName();

private:

	static std::string m_HumanNames[10];
	static std::string m_DwarfNames[10];
	static std::string m_GnomeNames[10];
	static std::string m_HighelfNames[10];
	static std::string m_DarkelfNames[10];
	static std::string m_GoblinNames[10];
	static std::string m_OrcNames[10];
	static std::string m_TrollNames[10];


	static UnitNames* g_pUnitNames;

private:

};
