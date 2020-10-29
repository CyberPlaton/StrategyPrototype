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
	
	/*
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
			
			//NOTE:
			//Every maptile must(!) be associated to  region.
			//Do it like 
			//
			//m_MapDefinitions->at(i).at(j)->AssociateToMapTileRegion(region);
			//
			//Thus the particular maptile will belong to a region.
			
		}
	}
	*/


	using namespace std;

	ifstream map("assets/map/worldmap_testing.txt", fstream::in);

	string line;
	string token;
	string token_two;

	int xpos = 0;
	int ypos = 0;
	int mapwidth = 18;
	int mapheight = 13;

	while (getline(map, line)) {

		
		//cout << line << endl;



		// Read the textfile line by line.
		if (IsSubstringInString("maptiles", line)) { // Defining the ground maptiles.

			cout << APP_COLOR;
			cout << "CREATING MAPTILES." << white << endl;


			if (COMPARE_STRINGS(line, "maptiles;") == 0) getline(map, line); // Read next line for maptiles definition.

			/*
			For: every token do:
			...

			*/
			// First, identify tokens.
			string token = "";
			bool escape_code = false;
			bool line_end_escape_code = false; // Means, the end of the line was reached, the delimiter ";" was found, thus move to next line.

			for (auto it = line.begin(); it != line.end(); ++it) {

				if (*it == ',') { // escape code
					escape_code = true;
				}
				else if (*it == ';') {
					line_end_escape_code = true;
				}
				else {
					token.push_back((*it)); // At char to string.
				}


				// Now check for definitions an create new maptiles.
				// Escape code means, we found our delimiter and can check the word for maptile definition.
				if (escape_code) {


					if (IsSubstringInString("_shallow", token)) {
						m_MapDefinitions->at(xpos).at(ypos) = new MapTile("water_shallow", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.


						cout << APP_SUCCESS_COLOR;
						cout << "Create WATER_SHALLOW at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("_deep", token)) {
						m_MapDefinitions->at(xpos).at(ypos) = new MapTile("water_deep", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create WATER_DEEP at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("temperate", token)) {
						m_MapDefinitions->at(xpos).at(ypos) = new MapTile("temperate", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create TEMPERATE at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("tundra", token)) {
						m_MapDefinitions->at(xpos).at(ypos) = new MapTile("tundra", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create TUNDRA at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("savannah", token)) {
						m_MapDefinitions->at(xpos).at(ypos) = new MapTile("savannah", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create SAVANNAH at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("snow", token)) {
						m_MapDefinitions->at(xpos).at(ypos) = new MapTile("snow", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create SNOW at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("ice", token)) {
						m_MapDefinitions->at(xpos).at(ypos) = new MapTile("ice", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create ICE at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("sand", token)) {
						m_MapDefinitions->at(xpos).at(ypos) = new MapTile("sand", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create SAND at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("none", token)) {
						// Do nothing.

						cout << APP_ERROR_COLOR;
						cout << "NONE created at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}



					// Custom double for-loop iterator...
					// To get the right cell position of the next tile.
					xpos++;
					if (xpos > mapwidth) {

						xpos = 0;
						ypos++;
						if (ypos > mapheight) {
							ypos = 0;
						}
					}




				}
				else if (line_end_escape_code) {
					continue;
				}



			}


		}
		else if (IsSubstringInString("overlay", line)) { // Defining forests, hills, mountains etc.


			if (IsSubstringInString("forest", line)) {

			}
			else if (IsSubstringInString("hill", line)) {

			}
			else if (IsSubstringInString("mountain", line)) {

			}
			else if (IsSubstringInString("none", line)) {
				continue; // Nothing...
			}



			// Custom double for-loop iterator...
			// To get the right cell position of the next tile.
			xpos++;
			if (xpos >= mapwidth) {

				xpos = 0;
				ypos++;
				if (ypos >= mapheight) {
					ypos = 0;
				}
			}

		}
		else if (IsSubstringInString("regions", line)) { // Defining maptileregions for the map.




		}
		else {
			continue;
		}
	}



	map.close();
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