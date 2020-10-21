#pragma once
#include"Components.h"
#include"FiniteStateMachine.h"


class GameEntity{
public:



	// Basic components for an Entity.
	CMPIdentifier* m_IDCmp = nullptr;
	CMPTransform* m_TransformCmp = nullptr;
	CMPPhysics* m_PhysicsCmp = nullptr;
	CMPGraphics* m_GraphicsCmp = nullptr;
	CMPArtificialIntelligence* m_AICmp = nullptr;
	FiniteStateMachine* m_FSM = nullptr;
};




struct EntitiesStorage {




	void AddGameEntitie(GameEntity* e) {
		m_GameEntitiesVec.push_back(e);
	}

	void DeleteGameEntitie(GameEntity* e) {

		std::vector< GameEntity* >::iterator iterator = std::find(m_GameEntitiesVec.begin(), m_GameEntitiesVec.end(), e);

		if (iterator != m_GameEntitiesVec.end()) {
			m_GameEntitiesVec.erase(iterator);
		}
	}

	void DeleteGameEntitie(CMPIdentifier* id) {

		GameEntity* e = nullptr;
		for (auto it : m_GameEntitiesVec) {
			if (it->m_IDCmp->m_ID == id->m_ID) e = it;
		}

		DeleteGameEntitie(e);
	}


	static  EntitiesStorage* Get() {

		if (!m_EntitiesStorage) {
			m_EntitiesStorage = new EntitiesStorage();
			return m_EntitiesStorage;
		}
		else {
			return m_EntitiesStorage;
		}

	}

	static void Del() {
		if (m_EntitiesStorage) delete m_EntitiesStorage;
	}

private:
	static EntitiesStorage* m_EntitiesStorage;

	std::vector< GameEntity* > m_GameEntitiesVec; // Holds all entities ingame.
};
