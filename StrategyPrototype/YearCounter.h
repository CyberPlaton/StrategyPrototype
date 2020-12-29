#pragma once
// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include"Platform.h"

/*
struct Birthsigns {

	void AddBirthsign(std::string name) {
		m_BirthsignsVec.push_back(name);
	}

	std::vector<std::string> m_BirthsignsVec;
};
*/

struct YearCounter {

	static YearCounter* Get() {
		if (g_pYearCounter) {
			return g_pYearCounter;
		}
		else {
			g_pYearCounter = new YearCounter();
			return g_pYearCounter;
		}
	}

	static void Del() {
		if (g_pYearCounter) delete g_pYearCounter;
	}

	~YearCounter() = default;

	// Defines the logic for transiting from one turn to another.
	void AdvanceOneTurn() {
		_advanceTurn();
	}

	// Returns the birthsign based on quartal and year...
	std::string GetCurrentBirthsign();

	int GetYear() { return m_CurrentYear; }
	int GetQuartal() { return m_CurrentQuartal; }



	// For returning globally ingame.
	int m_CurrentYear = -1;
	int m_CurrentQuartal = -1;

private:
	static YearCounter* g_pYearCounter;


	// Years for internal usage.
	int m_CurrentYearInternal = -1;
	int m_CurrentQuartalInternal = -1;


	// Defined birthsings
	//Birthsigns* m_Birthsigns = nullptr;
	std::string m_CurrentBirthsign; // .. the sign that will be return for current year and quartal.

private:
	YearCounter() {
		/*
		// Define in here all ingame birthsigns.
		m_Birthsigns = new Birthsigns();


		m_Birthsigns->AddBirthsign("The Warrior");
		m_Birthsigns->AddBirthsign("The Mage");
		m_Birthsigns->AddBirthsign("The Thief");
		m_Birthsigns->AddBirthsign("The Tower");
		m_Birthsigns->AddBirthsign("The Lover");
		m_Birthsigns->AddBirthsign("The Guard");
		m_Birthsigns->AddBirthsign("The Sorcerer");
		m_Birthsigns->AddBirthsign("The Shadow");
		m_Birthsigns->AddBirthsign("The Lightfeet");
		m_Birthsigns->AddBirthsign("The Ritual");
		m_Birthsigns->AddBirthsign("The Paladin");
		m_Birthsigns->AddBirthsign("The Mechanist");
		m_Birthsigns->AddBirthsign("The Ignorant");
		m_Birthsigns->AddBirthsign("The Lord");
		m_Birthsigns->AddBirthsign("The Protector");
		m_Birthsigns->AddBirthsign("The Stubborn");

		m_Birthsigns->AddBirthsign("The Serpent"); // 17. additional birthsign.
		*/

		m_CurrentQuartalInternal = 0;
		m_CurrentYearInternal = 0;

		m_CurrentYear = 0;
		m_CurrentQuartal = 0;
	}



	void _advanceTurn();

};
