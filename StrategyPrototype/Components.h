#pragma once
#include"Platform.h"
#include"ColorConsole.h"
#include"FiniteStateMachine.h"

class MapTile;

struct TimeCounter {

	void Start() {
		m_TimeNow = std::clock();
	}

	void SetTimerForSeconds(unsigned int seconds) {
		m_Timer = seconds;
	}

	bool TimeOut() {

		auto duration = (std::clock() - m_TimeNow) / (double)CLOCKS_PER_SEC;
		if (duration > m_Timer) {

			m_TimeNow = std::clock();
			return true;
		}

		else return false;
	}

	int m_TimeNow = 0;
	int m_Timer = 0;
};


struct CMPIdentifier {
	CMPIdentifier() {

		// Stringify the own physical address or the GUID.
		std::stringstream stream;
		stream << static_cast<const void*>(this);
		m_ID = stream.str();

	}

	~CMPIdentifier() {
		m_ID.erase();
		m_DynamicTypeName.erase();
	}

	std::string m_ID;
	std::string m_DynamicTypeName;
};


struct CMPGraphics{


	~CMPGraphics() {
		m_DrawingLayer.erase();
		m_SpriteName.erase();
	}

	std::string m_DrawingLayer;
	std::string m_SpriteName;
};


struct CMPTransform {

	~CMPTransform() {
		m_Height = m_Width = m_PosX = m_PosY = 0;
		m_Cell[0] = m_Cell[1] = m_GameWorldSpaceCell[0] = m_GameWorldSpaceCell[1] = 0;
	}


	int m_PosX;
	int m_PosY;


	int m_Width;
	int m_Height;

	int m_Cell[2]; // The Cell is dependent on the camera position.
				   // Means, in the left upper windwow corner is always the cell 0,0

	int m_GameWorldSpaceCell[2]; // This Cell on the other hand is global defined and does
								 // not change despite cameras movement.
};


struct CMPPhysics {

};

class GameEntity;
struct CMPArtificialIntelligence {

	CMPArtificialIntelligence(GameEntity* e) {
		m_ManagedObject = e;
		m_StateMachine = new FiniteStateMachine(States::STATE_INVALID);
	}

	// Maps a statename to specific logicfunction (functor).
	void MapState(std::string name, IStateLogic* logic) {

		m_StateLogicMap.insert(std::make_pair(name, logic));
	}

	// Removes mapping from a given logicfunc.
	void UnmapLogic(std::string name) {

		m_StateLogicMap.erase(m_StateLogicMap.find(name));
	}


	void ChangeState(States newState) {
		m_StateMachine->ChangeState(newState);
	}


	bool TryExecuteStateLogic() {
		
		// Guards against unneeded computing.
		if (m_StateLogicMap.size() == 0) return false;

		if (m_StateMachine->GetCurrentState() == States::STATE_INVALID ||
			m_StateMachine->GetCurrentState() == States::STATE_INVALID_END) return false;

		// Make a string out of current state
		std::string state_string;
		switch (m_StateMachine->GetCurrentState()) {
		case States::STATE_PATROL:
			state_string = "state_patrol";

			break;
		case States::STATE_SEARCH:
			state_string = "state_search";

			break;
		case States::STATE_ATTACK:
			state_string = "state_attack";

			break;
		case States::STATE_DEFEND:
			state_string = "state_defend";

			break;
		case States::STATE_FLEE:
			state_string = "state_flee";

			break;
		case States::STATE_DIE:
			state_string = "state_die";

			break;
		
		default:
			break;
		}

		// Try executing the mapped logic.
		try {
			m_StateLogicMap.at(state_string)->executeStateLogic();
		}
		catch (char* err) {
			using namespace std;


			cout << APP_ERROR_COLOR;
			cout << "Error on TryExecuteStateLogic()" << " .\n";
			cout << "Error code:  " + std::to_string(*err) << white <<endl;
		}
	}


	~CMPArtificialIntelligence() {
		m_StateLogicMap.clear();
		m_ManagedObject = nullptr;
		m_StateMachine = nullptr;
	}

	std::map<std::string, IStateLogic*> m_StateLogicMap;
	GameEntity* m_ManagedObject = nullptr;;
	FiniteStateMachine* m_StateMachine = nullptr;;
};


struct CMPInput {


	virtual void HandleKeyboard();
	virtual void HandleMouse();
};


struct CMPEntityRace {
	
	enum class Race {
		RACE_INVALID = -1,
		RACE_HUMAN = 0,
		RACE_TROLL = 1,
		RACE_DWARF = 2,
		RACE_ORC = 3,
		RACE_HIGHELF = 4,
		RACE_DARKELF = 5,
		RACE_GOBLIN = 6,
		RACE_GNOME = 7
	};

	CMPEntityRace(Race race) {
		switch (race)
		{
		case CMPEntityRace::Race::RACE_INVALID:
			break;
		case CMPEntityRace::Race::RACE_HUMAN:
			m_EntityRaceString = "Human";
			break;
		case CMPEntityRace::Race::RACE_TROLL:
			m_EntityRaceString = "Human";
			break;
		case CMPEntityRace::Race::RACE_DWARF:
			m_EntityRaceString = "Dwarf";
			break;
		case CMPEntityRace::Race::RACE_ORC:
			m_EntityRaceString = "Orc";
			break;
		case CMPEntityRace::Race::RACE_HIGHELF:
			m_EntityRaceString = "High Elf";
			break;
		case CMPEntityRace::Race::RACE_DARKELF:
			m_EntityRaceString = "Dark Elf";
			break;
		case CMPEntityRace::Race::RACE_GOBLIN:
			m_EntityRaceString = "Goblin";
			break;
		case CMPEntityRace::Race::RACE_GNOME:
			m_EntityRaceString = "Gnome";
			break;
		default:
			break;
		}
	}

	~CMPEntityRace() {
		m_EntityRace = Race::RACE_INVALID;
		m_EntityRaceString.clear();
	}

	Race m_EntityRace = Race::RACE_INVALID;
	std::string m_EntityRaceString = "";
};


// This struct defines the movement cost for a specific maptileentity.
// It gives the movement cost back, based on the race of the entity.
struct CMPMovementCostModifier {

	// This function should be used to get the actual movement cost for a unit trespassing on this terrain.
	// It returns the basemovementcost modified by the racial abilities etc. of a unit.
	int GetRaceModifiedMovementCost(std::string race) {

		if (COMPARE_STRINGS(race, "Human") == 0) {
			return _getRaceModifierValue(CMPEntityRace::Race::RACE_HUMAN);
		}
		else if (COMPARE_STRINGS(race, "Orc") == 0) {
			return _getRaceModifierValue(CMPEntityRace::Race::RACE_ORC);
		}
		else if (COMPARE_STRINGS(race, "High Elf") == 0) {
			return _getRaceModifierValue(CMPEntityRace::Race::RACE_HIGHELF);
		}
		else if (COMPARE_STRINGS(race, "Dark Elf") == 0) {
			return _getRaceModifierValue(CMPEntityRace::Race::RACE_DARKELF);
		}
		else if (COMPARE_STRINGS(race, "Dwarf") == 0) {
			return _getRaceModifierValue(CMPEntityRace::Race::RACE_DWARF);
		}
		else if (COMPARE_STRINGS(race, "Gnome") == 0) {
			return _getRaceModifierValue(CMPEntityRace::Race::RACE_GNOME);
		}
		else if (COMPARE_STRINGS(race, "Goblin") == 0) {
			return _getRaceModifierValue(CMPEntityRace::Race::RACE_GOBLIN);
		}
		else if (COMPARE_STRINGS(race, "Troll") == 0) {
			return _getRaceModifierValue(CMPEntityRace::Race::RACE_TROLL);
		}

	}

	void SetRaceSpecificMovementCostModifier(CMPEntityRace::Race race, int modifier) {
		switch (race) {
		case CMPEntityRace::Race::RACE_HUMAN:
			m_RaceModifierHuman = modifier;
			break;
		case CMPEntityRace::Race::RACE_ORC:
			m_RaceModifierOrc = modifier;
			break;
		case CMPEntityRace::Race::RACE_HIGHELF:
			m_RaceModifierHighElf = modifier;
			break;
		case CMPEntityRace::Race::RACE_DARKELF:
			m_RaceModifierDarkElf = modifier;
			break;
		case CMPEntityRace::Race::RACE_TROLL:
			m_RaceModifierTroll = modifier;
			break;
		case CMPEntityRace::Race::RACE_GNOME:
			m_RaceModifierGnome = modifier;
			break;
		case CMPEntityRace::Race::RACE_DWARF:
			m_RaceModifierDwarf = modifier;
			break;
		case CMPEntityRace::Race::RACE_GOBLIN:
			m_RaceModifierGoblin = modifier;
			break;
		default:
			break;
		}

	}

	void SetBaseMovementCost(unsigned int n) { m_BaseMovementCost = n; }
	int GetBaseMovementCost() { return m_BaseMovementCost; }

	~CMPMovementCostModifier() {
		m_BaseMovementCost = 0;
		m_RaceModifierDarkElf = 0;
		m_RaceModifierHuman = 0;
		m_RaceModifierHighElf = 0;
		m_RaceModifierTroll = 0;
		m_RaceModifierGnome = 0;
		m_RaceModifierGoblin = 0;
		m_RaceModifierDwarf = 0;
	}

	int m_BaseMovementCost = -1;

private:
	int m_RaceModifierHuman = 0;
	int m_RaceModifierOrc = 0;
	int m_RaceModifierHighElf = 0;
	int m_RaceModifierDarkElf = 0;
	int m_RaceModifierTroll = 0;
	int m_RaceModifierGnome = 0;
	int m_RaceModifierGoblin = 0;
	int m_RaceModifierDwarf = 0;


private:

	int _getRaceModifierValue(CMPEntityRace::Race race) {
		switch (race){
		case CMPEntityRace::Race::RACE_HUMAN:
			return m_RaceModifierHuman;
			break;
		case CMPEntityRace::Race::RACE_ORC:
			return m_RaceModifierOrc;
			break;
		case CMPEntityRace::Race::RACE_HIGHELF:
			return m_RaceModifierHighElf;
			break;
		case CMPEntityRace::Race::RACE_DARKELF:
			return m_RaceModifierDarkElf;
			break;
		case CMPEntityRace::Race::RACE_TROLL:
			return m_RaceModifierTroll;
			break;
		case CMPEntityRace::Race::RACE_GNOME:
			return m_RaceModifierGnome;
			break;
		case CMPEntityRace::Race::RACE_DWARF:
			return m_RaceModifierDwarf;
			break;
		case CMPEntityRace::Race::RACE_GOBLIN:
			return m_RaceModifierGoblin;
			break;
		default:
			return 0;
			break;
		}
	}

};