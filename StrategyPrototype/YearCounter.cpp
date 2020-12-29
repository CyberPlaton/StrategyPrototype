// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include"YearCounter.h"


YearCounter* YearCounter::g_pYearCounter = nullptr;


std::string YearCounter::GetCurrentBirthsign() {
	return m_CurrentBirthsign;
}


void YearCounter::_advanceTurn() {

	bool nextyear_transition = false;
	nextyear_transition = (m_CurrentQuartalInternal == 3) ? true : false;

	// Advance one quartal. And check for boundaries 0-3.
	m_CurrentQuartalInternal = (++m_CurrentQuartalInternal > 3) ? 0 : m_CurrentQuartalInternal;

	// Likewise, get next public quartal.
	m_CurrentQuartal = (++m_CurrentQuartal > 3) ? 0 : m_CurrentQuartal;


	int quartal = m_CurrentQuartalInternal % 4;

	//Check whether to advance one year. Based on flag and current year.
	if (nextyear_transition && (m_CurrentQuartalInternal == 0)) { // ... we crossed the last quartal and reset to 0, thus, next year.
	
		// Advance one year. And check for boundaries 0-3.
		m_CurrentYearInternal = (++m_CurrentYearInternal > 3) ? 0 : m_CurrentYearInternal;

		// Advance one year globally.
		m_CurrentYear++;
	}



	// Set current to return birthsign. 2 Dimensional switch.
	// .. for the 17. birthsign, there will be a randomization.
	int r = Random() % 99;
	if (r == 0) {
		m_CurrentBirthsign = "The Serpent";
		return;
	}

	switch (m_CurrentYearInternal) {
	case 0:
		switch (m_CurrentQuartalInternal) {
		case 0:
			m_CurrentBirthsign = "The Warrior";
			break;
		case 1:
			m_CurrentBirthsign = "The Mage";
			break;
		case 2:
			m_CurrentBirthsign = "The Thief";
			break;
		case 3:
			m_CurrentBirthsign = "The Tower";
			break;
		}
		break;
	case 1:
		switch (m_CurrentQuartalInternal) {
		case 0:
			m_CurrentBirthsign = "The Lover";
			break;
		case 1:
			m_CurrentBirthsign = "The Guard";
			break;
		case 2:
			m_CurrentBirthsign = "The Sorcerer";
			break;
		case 3:
			m_CurrentBirthsign = "The Shadow";
			break;
		}
		break;
	case 2:
		switch (m_CurrentQuartalInternal) {
		case 0:
			m_CurrentBirthsign = "The Lightfeet";
			break;
		case 1:
			m_CurrentBirthsign = "The Ritual";
			break;
		case 2:
			m_CurrentBirthsign = "The Paladin";
			break;
		case 3:
			m_CurrentBirthsign = "The Mechanist";
			break;
		}
		break;
	case 3:
		switch (m_CurrentQuartalInternal) {
		case 0:
			m_CurrentBirthsign = "The Ignorant";
			break;
		case 1:
			m_CurrentBirthsign = "The Stubborn";
			break;
		case 2:
			m_CurrentBirthsign = "The Lord";
			break;
		case 3:
			m_CurrentBirthsign = "The Protector";
			break;
		}
		break;


	default:
		break;
	}
}
