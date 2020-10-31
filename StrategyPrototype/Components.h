#pragma once
#include"Platform.h"
#include"ColorConsole.h"
#include"FiniteStateMachine.h"

class MapTile;

struct CMPIdentifier {
	CMPIdentifier() {

		// Stringify the own physical address or the GUID.
		std::stringstream stream;
		stream << static_cast<const void*>(this);
		m_ID = stream.str();

	}

	std::string m_ID;
	std::string m_DynamicTypeName;
};


struct CMPGraphics{



	std::string m_DrawingLayer;

	std::string m_SpriteName;
};


struct CMPTransform {



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



/*
Purpose:

Each player has an Empire, thus an empireborder (=CMPEmpireBorder).

We add to this Border the maptiles coords to define the border tiles.

Lastly we use an algorithm to draw adjacent tiles of the border to display the borderlines.
*/
struct BorderMapTile;
struct CMPEmprieBorder {

	// to determine in which direciton the border is looking to.
	enum class BorderDirection {
		BORDER_DIRECTION_INVALID = -1,
		BORDER_DIRECTION_LEFT = 0,
		BORDER_DIRECTION_RIGHT = 1,
		BORDER_DIRECTION_DOWN = 2,
		BORDER_DIRECTION_UP = 3
	};

	void AddMapTileToBorder(MapTile* maptile) {
		m_BorderTiles.push_back(maptile);
	}

	void RemoveMapTileFromBorder(MapTile* maptile) {

		std::vector<MapTile*>::iterator it = std::find(m_BorderTiles.begin(), m_BorderTiles.end(), maptile);

		if (it != m_BorderTiles.end()) m_BorderTiles.erase(it);

	}

	std::vector<MapTile*> m_BorderTiles;
	//std::map< MapTile*, BorderDirection> m_BorderTileWithBorderDirectionMap;


};

// For drawing specific border decal.
// Specifying in which directions the border is looking to, means
// to define which sprite should be used for drawing the border.
struct BorderMapTileRepresentation {
	BorderMapTileRepresentation() {
		m_GraphicsCMP = new CMPGraphics();
		m_GraphicsCMP->m_DrawingLayer = "layer1";
		m_GraphicsCMP->m_SpriteName = "NULL";
	}

	// Size of this should be max of 4.
	std::vector<CMPEmprieBorder::BorderDirection*> m_BorderDirectionsVec;
	CMPGraphics* m_GraphicsCMP = nullptr;

private:
	void _setBorderSprite(std::string spritename) { m_GraphicsCMP->m_SpriteName = spritename; }
	void _determineBorderSprite() {

		bool border_up = false, border_down = false, border_right = false, border_left = false;

		// 1. Base cases
		if (border_up && border_down == false && border_right == false && border_left == false) { // only up border
			_setBorderSprite();

		}
		else if (border_down && border_up == false && border_right == false && border_left == false) {// only down border
			_setBorderSprite();

		}
		else if (border_right && border_up == false && border_down == false && border_left == false) {// only right border
			_setBorderSprite();

		}
		else if (border_left && border_up == false && border_down == false && border_right == false) {// only left border
			_setBorderSprite();

		}


		// 2. double border cases.
		if (border_up && border_down  && border_right == false && border_left == false) { // up and down border
			_setBorderSprite();

		}
		else if (border_down && border_right && border_up == false && border_left == false) {// down and right border
			_setBorderSprite();

		}
		else if (border_right && border_up && border_down == false && border_left == false) {// right and up border
			_setBorderSprite();

		}
		else if (border_left && border_up && border_down == false && border_right == false) {// left and up border
			_setBorderSprite();

		}
		else if (border_left && border_right && border_down == false && border_up == false) {// left and right border
			_setBorderSprite();

		}
		else if (border_down && border_left && border_up == false && border_right == false) {// down and left border
			_setBorderSprite();

		}

		// 3. Threesome border cases.
		if (border_up && border_down && border_right && border_left == false) { // up and down and right
			_setBorderSprite();

		}
		else if (border_down && border_right && border_left && border_up == false) {// down and right and left border
			_setBorderSprite();

		}
		else if (border_left && border_up && border_down && border_right == false) {// right and up border
			_setBorderSprite();

		}
		else if (border_left && border_up && border_right && border_down == false) {// left and up and right border
			_setBorderSprite();

		}

	}
};