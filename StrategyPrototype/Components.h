#pragma once
#include"Platform.h"
#include"ColorConsole.h"
#include"FiniteStateMachine.h"

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