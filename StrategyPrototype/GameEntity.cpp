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

	using namespace std;

	ifstream map("assets/map/worldmap_alpha.txt", fstream::in);

	string line;
	string token;
	string token_two;

	int xpos = 0;
	int ypos = 0;

	// Width and Height must always be 1 less then defined in the loaded mapfile. Else errors occur.
	int mapwidth = 19;
	int mapheight = 19;

	MapTile* maptile = nullptr;

	std::vector<MapTileRegion*> regions_vec;
	MapTileRegion* region = nullptr;


	while (getline(map, line)) {


		//cout << line << endl;



		// Read the textfile line by line.
		if (IsSubstringInString("maptiles", line)) { // Defining the ground maptiles.

			cout << APP_COLOR;
			cout << "CREATING MAPTILES." << white << endl;


			if (COMPARE_STRINGS(line, "maptiles;") == 0) getline(map, line); // Read next line for maptiles definition.


			cout << APP_ERROR_COLOR;
			cout << line << white << endl;

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
						maptile = new MapTile("water_shallow", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);
						maptile->m_TransformCmp->m_GameWorldSpaceCell[0] = xpos;
						maptile->m_TransformCmp->m_GameWorldSpaceCell[1] = ypos;

						m_MapDefinitions->at(xpos).at(ypos) = maptile;

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.


						cout << APP_SUCCESS_COLOR;
						cout << "Create WATER_SHALLOW at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("_deep", token)) {
						maptile = new MapTile("water_deep", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);
						maptile->m_TransformCmp->m_GameWorldSpaceCell[0] = xpos;
						maptile->m_TransformCmp->m_GameWorldSpaceCell[1] = ypos;

						m_MapDefinitions->at(xpos).at(ypos) = maptile;

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create WATER_DEEP at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("temperate", token)) {
						maptile = new MapTile("temperate", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);
						maptile->m_TransformCmp->m_GameWorldSpaceCell[0] = xpos;
						maptile->m_TransformCmp->m_GameWorldSpaceCell[1] = ypos;

						m_MapDefinitions->at(xpos).at(ypos) = maptile;

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create TEMPERATE at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("jungle", token)) {
						maptile = new MapTile("jungle", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);
						maptile->m_TransformCmp->m_GameWorldSpaceCell[0] = xpos;
						maptile->m_TransformCmp->m_GameWorldSpaceCell[1] = ypos;

						m_MapDefinitions->at(xpos).at(ypos) = maptile;

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create JUNGLE at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("tundra", token)) {
						maptile = new MapTile("tundra", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);

						maptile->m_TransformCmp->m_GameWorldSpaceCell[0] = xpos;
						maptile->m_TransformCmp->m_GameWorldSpaceCell[1] = ypos;

						m_MapDefinitions->at(xpos).at(ypos) = maptile;

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create TUNDRA at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("savannah", token)) {
						maptile = new MapTile("savannah", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);

						maptile->m_TransformCmp->m_GameWorldSpaceCell[0] = xpos;
						maptile->m_TransformCmp->m_GameWorldSpaceCell[1] = ypos;

						m_MapDefinitions->at(xpos).at(ypos) = maptile;

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create SAVANNAH at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("snow", token)) {
						maptile = new MapTile("snow", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);

						maptile->m_TransformCmp->m_GameWorldSpaceCell[0] = xpos;
						maptile->m_TransformCmp->m_GameWorldSpaceCell[1] = ypos;

						m_MapDefinitions->at(xpos).at(ypos) = maptile;

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create SNOW at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("ice", token)) {
						maptile = new MapTile("ice", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);

						maptile->m_TransformCmp->m_GameWorldSpaceCell[0] = xpos;
						maptile->m_TransformCmp->m_GameWorldSpaceCell[1] = ypos;

						m_MapDefinitions->at(xpos).at(ypos) = maptile;

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create ICE at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("sand", token)) {
						maptile = new MapTile("sand", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);

						maptile->m_TransformCmp->m_GameWorldSpaceCell[0] = xpos;
						maptile->m_TransformCmp->m_GameWorldSpaceCell[1] = ypos;

						m_MapDefinitions->at(xpos).at(ypos) = maptile;

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create SAND at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}


					// Custom double for-loop iterator...
					// To get the right cell position of the next tile.
					cout << color(colors::MAGENTA);
					cout << "X " << xpos << " Y " << ypos << white << endl;

					++xpos;
					if (xpos > mapwidth) {

						// Move on to the next line.
						++ypos;
						if (ypos > mapheight) {
							ypos = 0; // Set to 0 or reset it...
						}


						// Reset xpos.
						xpos = 0;
					}



					cout << color(colors::MAGENTA);
					cout << "X " << xpos << " Y " << ypos << white << endl;

				}
				else if (line_end_escape_code) {
					continue;
				}



			}

		}
		else if (IsSubstringInString("overlay", line)) { // Defining forests, hills, mountains etc.

		Forest* forest = nullptr;

		cout << APP_COLOR;
		cout << "CREATING OVERLAY." << white << endl;

		cout << xpos << ypos << endl;



		string token = ""; // The next word.
		bool escape_code = false;
		bool line_end_escape_code = false; // Means, the end of the line was reached, the delimiter ";" was found, thus move to next line.


		if (COMPARE_STRINGS(line, "overlay;") == 0) getline(map, line); // Read next line for maptiles definition.

		
		cout << line << endl;


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



				if (escape_code) {

					if (IsSubstringInString("forest_tundra", token)) {

						// Create forest.
						forest = MakeNewForest("forest_tundra_deep", xpos, ypos);
						storage->AddGameEntitie(forest);



						cout << token << endl;
						// Custom double for-loop iterator...
						// To get the right cell position of the next tile.
						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						++xpos;
						if (xpos > mapwidth) {

							// Move on to the next line.
							++ypos;
							if (ypos > mapheight) {
								ypos = -1; // Set to 0 or reset it...
							}


							// Reset xpos.
							xpos = 0;
						}



						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;
						cout << color(colors::CYAN);
						cout << "Create FOREST_TUNDRA at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("forest_jungle", token)) {

						// Create forest.
						forest = MakeNewForest("forest_jungle_deep", xpos, ypos);
						storage->AddGameEntitie(forest);

						cout << token << endl;


						// Custom double for-loop iterator...
						// To get the right cell position of the next tile.
						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						++xpos;
						if (xpos > mapwidth) {

							// Move on to the next line.
							++ypos;
							if (ypos > mapheight) {
								ypos = -1; // Set to 0 or reset it...
							}


							// Reset xpos.
							xpos = 0;
						}



						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						cout << color(colors::CYAN);
						cout << "Create FOREST_JUNGLE at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("forest_temperate", token)) {

						// Create forest.
						forest = MakeNewForest("forest_temperate_deep", xpos, ypos);
						storage->AddGameEntitie(forest);

						cout << token << endl;


						// Custom double for-loop iterator...
						// To get the right cell position of the next tile.
						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						++xpos;
						if (xpos > mapwidth) {

							// Move on to the next line.
							++ypos;
							if (ypos > mapheight) {
								ypos = -1; // Set to 0 or reset it...
							}


							// Reset xpos.
							xpos = 0;
						}



						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						cout << color(colors::CYAN);
						cout << "Create FOREST_TEMPERATE at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("forest_savannah", token)) {

						// Create forest.
						forest = MakeNewForest("forest_savannah_deep", xpos, ypos);
						storage->AddGameEntitie(forest);

						cout << token << endl;


						// Custom double for-loop iterator...
						// To get the right cell position of the next tile.
						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						++xpos;
						if (xpos > mapwidth) {

							// Move on to the next line.
							++ypos;
							if (ypos > mapheight) {
								ypos = -1; // Set to 0 or reset it...
							}


							// Reset xpos.
							xpos = 0;
						}



						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						cout << color(colors::CYAN);
						cout << "Create FOREST_SAVANNAH at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("hill", token)) {

						cout << token << endl;

						Hills* hills = MakeNewHill("hills", xpos, ypos);
						storage->AddGameEntitie(hills);

						// Custom double for-loop iterator...
						// To get the right cell position of the next tile.
						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						++xpos;
						if (xpos > mapwidth) {

							// Move on to the next line.
							++ypos;
							if (ypos > mapheight) {
								ypos = -1; // Set to 0 or reset it...
							}


							// Reset xpos.
							xpos = 0;
						}



						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						cout << color(colors::CYAN);
						cout << "Create HILLS at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("mountain", token)) {

						cout << token << endl;

						Mountains* mountains = MakeNewMountain("highmountain", xpos, ypos);
						storage->AddGameEntitie(mountains);


						// Custom double for-loop iterator...
						// To get the right cell position of the next tile.
						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						++xpos;
						if (xpos > mapwidth) {

							// Move on to the next line.
							++ypos;
							if (ypos > mapheight) {
								ypos = -1; // Set to 0 or reset it...
							}


							// Reset xpos.
							xpos = 0;
						}



						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						cout << color(colors::CYAN);
						cout << "Create MOUNTAINS at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("none", token)) {

						cout << token << endl;


						// Custom double for-loop iterator...
						// To get the right cell position of the next tile.
						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						++xpos;
						if (xpos > mapwidth) {

							// Move on to the next line.
							++ypos;
							if (ypos > mapheight) {
								ypos = -1; // Set to 0 or reset it...
							}


							// Reset xpos.
							xpos = 0;
						}



						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						cout << color(colors::CYAN);
						cout << "Create NONE at Position " << xpos << ":" << ypos << white << endl;
						// Nothing...


						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (line_end_escape_code) {
						continue;
					}



				}

			} // end for overlay


		}
		else if (IsSubstringInString("region;", line)) { // Defining maptileregions for the map.

				// Regions are defined like
				// region;
				// 1:0, 2:0, 1:1,; ...
				int map_tile[2];
				bool first_digit_defined = false;

				region = new MapTileRegion("map_cell_red");
				regions_vec.push_back(region);


				cout << APP_COLOR;
				cout << "CREATING REGIONS" << white << endl;

				string token = ""; // The next word.
				bool escape_code = false;
				bool token_escape_code = false;
				bool token_end_of_maptile_definition = false;
				bool line_end_escape_code = false; // Means, the end of the line was reached, the delimiter ";" was found, thus move to next line.


				if (COMPARE_STRINGS(line, "region;") == 0) getline(map, line); // Read next line for maptiles definition.


				cout << APP_ERROR_COLOR;
				cout << line << white << endl;

				// Iterate through line
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


					// Check tokens.
					if (escape_code) {

						cout << APP_ERROR_COLOR;
						cout << token << white << endl;

						// Extract numbers out of token
						string first_number, second_number;
						bool delimiter_reached = false;

						for (auto it = token.begin(); it != token.end(); ++it) {

							if (*it == ':') delimiter_reached = true;

							if (*it != ':' && delimiter_reached == false) {

								first_number.push_back(*it);
							}
							else if(*it != ':'){
								second_number.push_back(*it);
							}

						}


						// Convert first_number and second_number to a maptile position.
						map_tile[0] = atoi(first_number.c_str());
						map_tile[1] = atoi(second_number.c_str());


						region->AddTileToRegion(GetMapTileAtWorldPosition(map_tile[0], map_tile[1]));


						cout << APP_ERROR_COLOR;
						cout << "First: "<<first_number << " Second: " << second_number << white << endl;
						first_number.clear();
						second_number.clear();



						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;

					}
					else if (line_end_escape_code) {
						continue;
					}




				}

		}
		else {
			continue;
		}
	}


	// At last, add regions made to storage.
	for (auto it : regions_vec) {

		storage->AddGameEntitie(it);
	}
	

	regions_vec.clear();
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