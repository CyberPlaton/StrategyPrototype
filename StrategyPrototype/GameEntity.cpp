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

			
			m_MapDefinitions->at(i).at(j) = new MapTile("MapTile", "layer4", i*SPRITES_WIDTH_AND_HEIGHT, j* SPRITES_WIDTH_AND_HEIGHT);

			// Define map as purely temperate ground
			m_MapDefinitions->at(i).at(j)->m_GraphicsCmp->m_SpriteName = "temperate";

			storage->AddGameEntitie(m_MapDefinitions->at(i).at(j)); // Add Maptile to EntitiesStorage.

		}
	}


	// Map definition.
	for (int i = 0; i <= m_MapWidth; i++) {

		for (int j = 0; j <= m_MapHeight; j++) {

			
			if ((i + j) % 3 == 0) {

				Forest* f = new Forest("forest_scarce", "layer3", i * SPRITES_WIDTH_AND_HEIGHT, j * SPRITES_WIDTH_AND_HEIGHT);

				m_MapDefinitions->at(i).at(j)->m_MapTileEntities->push_back(f);
				storage->AddGameEntitie(f);

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


void Forest::Update() {


	// Change graphics accordingly to own type.
	switch (m_ForestType) {
	case ForestType::FOREST_SCARCE:
		m_GraphicsCmp->m_SpriteName = "forest_scarce";

		break;
	case ForestType::FOREST_NORMAL:
		m_GraphicsCmp->m_SpriteName = "forest_normal";

		break;
	case ForestType::FOREST_DEEP:
		m_GraphicsCmp->m_SpriteName = "forest_deep";

		break;
	case ForestType::FOREST_DYING:
		m_GraphicsCmp->m_SpriteName = "forest_dying";

		break;
	case ForestType::FOREST_INVALID: // Forests lifetime ended or other error occured. So delete this instance from game.

		EntitiesStorage::Get()->DeleteGameEntitie(this);
		break;
	default:
		break;
	}
}