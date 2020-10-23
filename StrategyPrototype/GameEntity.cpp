#include "GameEntity.h"

EntitiesStorage* EntitiesStorage::m_EntitiesStorage = nullptr;


WorldMap* WorldMap::m_WorldMapInstance = nullptr;

void WorldMap::SetMapOptions(WorldMapDrawingOptions* worldDef) {

	m_MapDrawOptions = worldDef;
	m_WorldMap = worldDef->m_MapDefinitions;
}


void WorldMapDrawingOptions::_createMap() {


	m_MapDefinitions = new MapTileArray();

	EntitiesStorage* storage = EntitiesStorage::Get();


	// MapTileArray initialization
	for (int i = 0; i <= m_MapWidth; i++) {

		for (int j = 0; j <= m_MapHeight; j++) {

			// "Zeroed" out MapTileArray
			m_MapDefinitions->at(i).at(j) = new MapTile("MapTile", "layer4", i*256, j*256);

			m_MapDefinitions->at(i).at(j)->m_GraphicsCmp->m_SpriteName = "null";
			storage->AddGameEntitie(m_MapDefinitions->at(i).at(j)); // Add Maptile to EntitiesStorage.

		}
	}


	// Map definition.
	for (int i = 0; i <= m_MapWidth; i++) {

		for (int j = 0; j <= m_MapHeight; j++) {

			// Define map as purely temperate ground
			m_MapDefinitions->at(i).at(j)->m_GraphicsCmp->m_SpriteName = "temperate";
			
			m_MapDefinitions->at(i).at(j)->m_MapTileEntities->push_back(new Forest("forest_scarce", "layer3", i * 256, j * 256));

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