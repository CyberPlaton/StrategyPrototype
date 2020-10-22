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
			m_MapDefinitions->at(i).at(j) = new MapTile();

			m_MapDefinitions->at(i).at(j)->m_GraphicsCmp->m_SpriteName = "null";
			m_MapDefinitions->at(i).at(j)->m_GraphicsCmp->m_DrawingLayer = "layer1"; // Draw ground tiles first.

			storage->AddGameEntitie(m_MapDefinitions->at(i).at(j)); // Add Maptile to EntitiesStorage.
		}
	}

	int r;
	Forest* f = nullptr;


	// Map definition.
	for (int i = 0; i <= m_MapWidth; i++) {


		for (int j = 0; j <= m_MapHeight; j++) {

			// Define map as purely temperate ground
			m_MapDefinitions->at(i).at(j)->m_GraphicsCmp->m_SpriteName = "temperate";


			// Add forest entities.
			/*
			r = rand() % 3;
			switch (r) {
			case 0:
				f = new Forest("forest_scarce");
				f->m_GraphicsCmp->m_DrawingLayer = "layer2";

				m_MapDefinitions->at(i).at(j)->m_MapTileEntities->push_back(f);
				break;
			case 1:
				f = new Forest("forest_norm");
				f->m_GraphicsCmp->m_DrawingLayer = "layer2";

				m_MapDefinitions->at(i).at(j)->m_MapTileEntities->push_back(f);
				break;
			case 2:
				f = new Forest("forest_deep");
				f->m_GraphicsCmp->m_DrawingLayer = "layer2";

				m_MapDefinitions->at(i).at(j)->m_MapTileEntities->push_back(f);
				break;
			}
			*/
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