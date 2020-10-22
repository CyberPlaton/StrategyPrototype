#include "GameEntity.h"

EntitiesStorage* EntitiesStorage::m_EntitiesStorage = nullptr;


WorldMap* WorldMap::m_WorldMapInstance = nullptr;

void WorldMap::SetMapOptions(WorldMapDrawingOptions* worldDef) {

	m_MapDrawOptions = worldDef;
	m_WorldMap = worldDef->m_MapDefinitions;
}


void WorldMapDrawingOptions::_createMap() {


	m_MapDefinitions = new MapTileArray();

	EntitiesStorage* storage = new EntitiesStorage();


	// MapTileArray initialization
	for (int i = 0; i <= m_MapWidth; i++) {


		for (int j = 0; j <= m_MapHeight; j++) {

			// "Zeroed" out MapTileArray
			m_MapDefinitions->at(i).at(j)->m_GraphicsCmp->m_SpriteName = "null";
			m_MapDefinitions->at(i).at(j)->m_GraphicsCmp->m_SpritePath = "null";
			m_MapDefinitions->at(i).at(j)->m_GraphicsCmp->m_DrawingLayer = "layer1"; // Draw ground tiles first.

			storage->AddGameEntitie(m_MapDefinitions->at(i).at(j)); // Add Maptile to EntitiesStorage.
		}
	}

	int r = rand() % 3;

	// Map definition.
	for (int i = 0; i <= m_MapWidth; i++) {


		for (int j = 0; j <= m_MapHeight; j++) {

			// Define map as purely temperate ground
			m_MapDefinitions->at(i).at(j)->m_GraphicsCmp->m_SpriteName = "temperate";
			m_MapDefinitions->at(i).at(j)->m_GraphicsCmp->m_SpritePath = "assets/map/temperate.png";



			// Add forest entities.
			switch (r) {
			case 0:
				m_MapDefinitions->at(i).at(j)->m_MapTileEntities->push_back(new Forest("forest_scarce"));
				break;
			case 1:
				m_MapDefinitions->at(i).at(j)->m_MapTileEntities->push_back(new Forest("forest_norm"));
				break;
			case 2:
				m_MapDefinitions->at(i).at(j)->m_MapTileEntities->push_back(new Forest("forest_deep"));
				break;
			}
		}
	}
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