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

	int random_num;

	// MapTileArray initialization
	for (int i = 0; i <= m_MapWidth; i++) {

		for (int j = 0; j <= m_MapHeight; j++) {

			if (i < 10) {
				m_MapDefinitions->at(i).at(j) = new MapTile("temperate", "layer4", i * SPRITES_WIDTH_AND_HEIGHT, j * SPRITES_WIDTH_AND_HEIGHT);
			}
			else if (i >= 10 && i < 15) {
				m_MapDefinitions->at(i).at(j) = new MapTile("savannah", "layer4", i * SPRITES_WIDTH_AND_HEIGHT, j * SPRITES_WIDTH_AND_HEIGHT);
			}
			else if(i >= 15){
				m_MapDefinitions->at(i).at(j) = new MapTile("tundra", "layer4", i * SPRITES_WIDTH_AND_HEIGHT, j * SPRITES_WIDTH_AND_HEIGHT);
			}

			storage->AddGameEntitie(m_MapDefinitions->at(i).at(j)); // Add Maptile to EntitiesStorage.

			// Define regions for map and add to storage
			/*
			NOTE:
			Every maptile must(!) be associated to  region.
			Do it like 

			m_MapDefinitions->at(i).at(j)->AssociateToMapTileRegion(region);

			Thus the particular maptile will belong to a region.
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


void Forest::Update() {


	// Change graphics accordingly to own type.
	switch (m_ForestType) {
	case ForestType::FOREST_SCARCE:

		switch (m_ForestClass) {
		case ForestClass::FOREST_CLASS_TEMPERATE:
			m_GraphicsCmp->m_SpriteName = "forest_temperate_scarce";
			break;
		case ForestClass::FOREST_CLASS_JUNGLE:
			m_GraphicsCmp->m_SpriteName = "forest_jungle_scarce";
			break;
		case ForestClass::FOREST_CLASS_TUNDRA:
			m_GraphicsCmp->m_SpriteName = "forest_tundra_scarce";
			break;
		case ForestClass::FOREST_CLASS_SAVANNAH:
			m_GraphicsCmp->m_SpriteName = "forest_savannah_scarce";
			break;
		default:
			break;
		}

		break;
	case ForestType::FOREST_NORMAL:

		switch (m_ForestClass) {
		case ForestClass::FOREST_CLASS_TEMPERATE:
			m_GraphicsCmp->m_SpriteName = "forest_temperate_normal";
			break;
		case ForestClass::FOREST_CLASS_JUNGLE:
			m_GraphicsCmp->m_SpriteName = "forest_jungle_normal";
			break;
		case ForestClass::FOREST_CLASS_TUNDRA:
			m_GraphicsCmp->m_SpriteName = "forest_tundra_normal";
			break;
		case ForestClass::FOREST_CLASS_SAVANNAH:
			m_GraphicsCmp->m_SpriteName = "forest_savannah_normal";
			break;
		default:
			break;
		}

		break;
	case ForestType::FOREST_DEEP:
		switch (m_ForestClass) {
		case ForestClass::FOREST_CLASS_TEMPERATE:
			m_GraphicsCmp->m_SpriteName = "forest_temperate_deep";
			break;
		case ForestClass::FOREST_CLASS_JUNGLE:
			m_GraphicsCmp->m_SpriteName = "forest_jungle_deep";
			break;
		case ForestClass::FOREST_CLASS_TUNDRA:
			m_GraphicsCmp->m_SpriteName = "forest_tundra_deep";
			break;
		case ForestClass::FOREST_CLASS_SAVANNAH:
			m_GraphicsCmp->m_SpriteName = "forest_savannah_deep";
			break;
		default:
			break;
		}
		break;
	case ForestType::FOREST_DYING:
		switch (m_ForestClass) {
		case ForestClass::FOREST_CLASS_TEMPERATE:
			m_GraphicsCmp->m_SpriteName = "forest_temperate_dying";
			break;
		case ForestClass::FOREST_CLASS_JUNGLE:
			m_GraphicsCmp->m_SpriteName = "forest_jungle_dying";
			break;
		case ForestClass::FOREST_CLASS_TUNDRA:
			m_GraphicsCmp->m_SpriteName = "forest_tundra_dying";
			break;
		case ForestClass::FOREST_CLASS_SAVANNAH:
			m_GraphicsCmp->m_SpriteName = "forest_savannah_dying";
			break;
		default:
			break;
		}
		break;
	case ForestType::FOREST_INVALID: // Forests lifetime ended or other error occured. So delete this instance from game.

		EntitiesStorage::Get()->DeleteGameEntitie(this);
		break;
	default:
		break;
	}
}


void City::ClaimRegions() {

	MapTileRegion* region = new MapTileRegion("map_cell_orange");

	// Here we claim TILES, not REGIONS.
	// This needs to be redone...

	// Normal
	region->AddTileToRegion(GetMapTileAtWorldPosition(1, 0));
	region->AddTileToRegion(GetMapTileAtWorldPosition(2, 0));

	region->AddTileToRegion(GetMapTileAtWorldPosition(-1, 0));
	region->AddTileToRegion(GetMapTileAtWorldPosition(-2, 0));

	region->AddTileToRegion(GetMapTileAtWorldPosition(0, 1));
	region->AddTileToRegion(GetMapTileAtWorldPosition(0, 2));

	region->AddTileToRegion(GetMapTileAtWorldPosition(0, -1));
	region->AddTileToRegion(GetMapTileAtWorldPosition(0, -2));
	
	// Diagonal
	region->AddTileToRegion(GetMapTileAtWorldPosition(1, 1));
	region->AddTileToRegion(GetMapTileAtWorldPosition(-1, -1));
	region->AddTileToRegion(GetMapTileAtWorldPosition(1, -1));
	region->AddTileToRegion(GetMapTileAtWorldPosition(-1, 1));


	m_ClaimedRegions.push_back(region);
}