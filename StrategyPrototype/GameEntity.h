#pragma once
#include"Components.h"
#include"FiniteStateMachine.h"

class MapTile;
typedef std::array<std::array<MapTile*, 20>, 20> MapTileArray;

#define COMPARE_STRINGS(x, y) strcmp(x.c_str(), y) // Utility.
#define COMPARE_STRINGS_2(x, y) strcmp(x.c_str(), y.c_str()) // Utility.




class GameEntity{
public:

	GameEntity() {
		m_IDCmp = new CMPIdentifier();
		m_TransformCmp = new CMPTransform();
		m_PhysicsCmp = new CMPPhysics();
		m_GraphicsCmp = new CMPGraphics();
		m_AICmp = new CMPArtificialIntelligence();
		m_FSM = new FiniteStateMachine();
	}


	// Basic components for an Entity.
	CMPIdentifier* m_IDCmp = nullptr;
	CMPTransform* m_TransformCmp = nullptr;
	CMPPhysics* m_PhysicsCmp = nullptr;
	CMPGraphics* m_GraphicsCmp = nullptr;
	CMPArtificialIntelligence* m_AICmp = nullptr;
	FiniteStateMachine* m_FSM = nullptr;
};



class Forest : public GameEntity {
public:
	Forest(std::string name, std::string layer, int xpos, int ypos) {
		m_TransformCmp->m_PosX = xpos;
		m_TransformCmp->m_PosY = ypos;
		m_GraphicsCmp->m_DrawingLayer = layer;
		m_GraphicsCmp->m_SpriteName = name;
	}

};



class MapTile : public GameEntity {
public:
	MapTile(std::string name, std::string layer, int xpos, int ypos) {
		
		m_MapTileEntities = new std::vector<GameEntity*>();

		m_MapTileName = name;
		m_TransformCmp->m_PosX = xpos;
		m_TransformCmp->m_PosY = ypos;
		m_GraphicsCmp->m_DrawingLayer = layer;

	}


	std::vector<GameEntity*>* m_MapTileEntities = nullptr;
	std::string m_MapTileName;
};



struct EntitiesStorage {


	std::vector< GameEntity* >* GetStorage() { return m_GameEntitiesVec; }


	void AddGameEntitie(GameEntity* e) {
		m_GameEntitiesVec->push_back(e);
	}

	void DeleteGameEntitie(GameEntity* e) {

		std::vector< GameEntity* >::iterator iterator = std::find(m_GameEntitiesVec->begin(), m_GameEntitiesVec->end(), e);

		if (iterator != m_GameEntitiesVec->end()) {
			m_GameEntitiesVec->erase(iterator);
		}
	}

	void DeleteGameEntitie(CMPIdentifier* id) {

		std::vector<GameEntity*> *vec = m_GameEntitiesVec;

		GameEntity* e = nullptr;
		for (auto const& it : *vec) {
			if (it->m_IDCmp->m_ID == id->m_ID) e = it;
		}

		DeleteGameEntitie(e);
	}

	// The only accessible constructor for this class.
	static  EntitiesStorage* Get() {

		if (!m_EntitiesStorage) {
			m_EntitiesStorage = new EntitiesStorage();
			m_EntitiesStorage->_initGameEntitiesVector();
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

	std::vector< GameEntity* >* m_GameEntitiesVec; // Holds all entities ingame.


private:
	EntitiesStorage() = default;
	EntitiesStorage(const EntitiesStorage&) = default;
	~EntitiesStorage() = default;


	void _initGameEntitiesVector() {
		m_GameEntitiesVec = new std::vector< GameEntity*>();
	}
};



struct WorldMapDrawingOptions {
	WorldMapDrawingOptions(int width, int height) {
		m_MapWidth = width;
		m_MapHeight = height;
		_createMap();
	}

	std::string IndexAsString(int i, int j) {
		return "";
	}

	int m_MapWidth;
	int m_MapHeight;

	MapTileArray* m_MapDefinitions;

private:

	void _createMap();
};




class WorldMap {
public:
	WorldMap() = default;
	~WorldMap() = default;


	void SetMapOptions(WorldMapDrawingOptions* worldDef);
	static WorldMap* Get();
	static void Del();


private:
	static WorldMap* m_WorldMapInstance;
	WorldMapDrawingOptions* m_MapDrawOptions = nullptr;
	MapTileArray* m_WorldMap = nullptr;

private:

};