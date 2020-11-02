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

				region = new MapTileRegion();
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

void City::ReclaimRegions() {

	_unclaimRegions();
	ClaimRegions();
}


void City::ClaimRegions() {


	// First, claim tile the city is on.
	// We assume, cities are not built on claimed tiles...
	// Be it own claimed tiles or of another player.

	int city_pos[2];
	city_pos[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	city_pos[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];


	// Normal
	int right[2], left[2], up[2], down[2];
	int right_2[2], left_2[2], up_2[2], down_2[2];


	// Diagonal
	int left_up[2], right_up[2], left_down[2], right_down[2];


	// Get according maptile coords for claiming.
	right[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 1;
	right[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];

	left[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 1;
	left[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];

	up[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	up[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 1;

	down[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	down[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 1;

	right_2[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 2;
	right_2[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];

	left_2[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 2;
	left_2[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];

	up_2[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	up_2[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 2;

	down_2[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	down_2[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 2;

	left_up[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 1;
	left_up[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 1;

	right_up[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 1;
	right_up[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 1;

	left_down[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 1;
	left_down[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 1;

	right_down[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 1;
	right_down[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 1;


	// Now claim associated regions of the maptiles for which we got coords.
	MapTile* m0, *m1, * m2, * m3, * m4,* m5, * m6,* m7, * m8, * m9, * m10, * m11, * m12;
	m0 = GetMapTileAtWorldPosition(city_pos[0], city_pos[1]);
	m1 = GetMapTileAtWorldPosition(right[0], right[1]);
	m2 = GetMapTileAtWorldPosition(left[0], left[1]);
	m3 = GetMapTileAtWorldPosition(up[0], up[1]);
	m4 = GetMapTileAtWorldPosition(down[0], down[1]);
	m5 = GetMapTileAtWorldPosition(right_2[0], right_2[1]);
	m6 = GetMapTileAtWorldPosition(left_2[0], left_2[1]);
	m7 = GetMapTileAtWorldPosition(up_2[0], up_2[1]);
	m8 = GetMapTileAtWorldPosition(down_2[0], down_2[1]);


	// No need for nullptr test here.
	m_ClaimedRegions.push_back(m0->m_AssociatedRegion);

	// Here we must test whether the tile is valid.
	if (m1 != nullptr) {
		
		if (_isRegionClaimedAlreadyByThisCity(m1->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m1->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m1->m_AssociatedRegion);
		}
	}
	if (m2 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m2->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m2->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m2->m_AssociatedRegion);
		}
	}
	if (m3 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m3->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m3->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m3->m_AssociatedRegion);
		}
	}
	if (m4 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m4->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m4->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m4->m_AssociatedRegion);
		}
	}
	if (m5 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m5->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m5->m_AssociatedRegion) == false) {


			m_ClaimedRegions.push_back(m5->m_AssociatedRegion);
		}
	}
	if (m6 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m6->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m6->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m6->m_AssociatedRegion);
		}
	}
	if (m7 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m7->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m7->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m7->m_AssociatedRegion);
		}
	}
	if (m8 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m8->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m8->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m8->m_AssociatedRegion);
		}
	}


	m9 = GetMapTileAtWorldPosition(left_up[0], left_up[1]);
	m10 = GetMapTileAtWorldPosition(right_up[0], right_up[1]);
	m11 = GetMapTileAtWorldPosition(left_down[0], left_down[1]);
	m12 = GetMapTileAtWorldPosition(right_down[0], right_down[1]);

	if (m9 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m9->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m9->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m9->m_AssociatedRegion);
		}
	}
	if (m10 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m10->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m10->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m10->m_AssociatedRegion);
		}
	}
	if (m11 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m11->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m11->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m11->m_AssociatedRegion);
		}
	}
	if (m12 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m12->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m12->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m12->m_AssociatedRegion);
		}
	}

	_setSpriteForClaimedRegion();
	

	// Set region owner for claimed regions.
	for (auto it : m_ClaimedRegions) {

		it->SetAssociatedPlayer(m_AssociatedPlayer);
	}
}

bool City::_isRegionClaimedAlreadyByThisCity(MapTileRegion* region) {

	std::vector<MapTileRegion*> vec = m_ClaimedRegions;
	MapTileRegion* r = nullptr;

	for (auto it = vec.begin(); it != vec.end(); ++it) {

		r = *it;

		if (COMPARE_STRINGS_2(r->m_IDCmp->m_ID, region->m_IDCmp->m_ID) == 0) return true;
	}

	return false;
}


bool City::_isRegionClaimedByOtherCity(MapTileRegion* region) {

	if (region == nullptr) throw;

	if (region->m_AssociatedPlayer == nullptr) return false;
	else return true;
}


void City::_setSpriteForClaimedRegion() {

	for (auto it : m_ClaimedRegions) {

		it->m_GraphicsCmp->m_SpriteName = m_ClaimedRegionsSpriteName;
	}
}



void EntitiesStorage::RemovePlayer(std::string playername) {

	for (auto it : *m_PlayersVec) {
		if (COMPARE_STRINGS_2(it->m_PlayerName, playername) == 0) {
			RemovePlayer(it);
		}
	}
}

void EntitiesStorage::RemovePlayer(Player* p) {

	std::vector<Player*>::iterator it = std::find(m_PlayersVec->begin(), m_PlayersVec->end(), p);
	if (it != m_PlayersVec->end()) m_PlayersVec->erase(it);
}

City::City(std::string cityname, std::string spritename, Player* player, int xpos, int ypos, int citySize) {

	m_IDCmp->m_DynamicTypeName = "City";


	m_CityName = cityname;
	m_CitySize = citySize;
	_updateCitySizeClass();


	m_GraphicsCmp = new CMPGraphics();
	m_GraphicsCmp->m_DrawingLayer = "layer2";
	m_GraphicsCmp->m_SpriteName = spritename;

	m_TransformCmp->m_PosX = xpos;
	m_TransformCmp->m_PosY = ypos;


	m_AICmp = new CMPArtificialIntelligence(this);

	m_AssociatedPlayer = player;
	player->AddCity(this);
	_determineMapCell(m_AssociatedPlayer->m_PlayerColor);
}



bool Player::_isMapTileSurroundedByOwnTiles(MapTile* tile) {

	MapTile* other_tile = nullptr;

	bool up = false, down = false, left = false, right = false;

	int up_tile[2], down_tile[2], left_tile[2], right_tile[2];

	up_tile[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0];
	up_tile[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1] - 1;

	down_tile[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0];
	down_tile[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1] + 1;

	left_tile[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0] - 1;
	left_tile[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1];

	right_tile[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0] + 1;
	right_tile[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1];



	if (IsIndexOutOfBound(up_tile[0], up_tile[1]) == false) {

		other_tile = GetMapTileAtWorldPosition(up_tile[0], up_tile[1]);
		if (other_tile) {

			if (_belongMapTileToThisPlayer(other_tile) == false) {

				// The up tile belongs to us, thus no border in up diretion.
				up = false;
			}
			else {

				// MAptile does not belong to us, thus border in up dir.
				up = true;

			}
		}

	}
	else {
		// Map end in up direction means its a border.
		up = true;
	}


	other_tile = nullptr;
	if (IsIndexOutOfBound(down_tile[0], down_tile[1]) == false) {

		other_tile = GetMapTileAtWorldPosition(down_tile[0], down_tile[1]);
		if (other_tile) {

			if (_belongMapTileToThisPlayer(other_tile) == false) {

				// The up tile belongs to us, thus no border in up diretion.
				down = false;
			}
			else {

				// MAptile does not belong to us, thus border in up dir.
				down = true;

			}
		}

	}
	else {
		// Map end in up direction means its a border.
		down = true;
	}


	other_tile = nullptr;
	if (IsIndexOutOfBound(left_tile[0], left_tile[1]) == false) {

		other_tile = GetMapTileAtWorldPosition(left_tile[0], left_tile[1]);
		if (other_tile) {

			if (_belongMapTileToThisPlayer(other_tile) == false) {

				// The up tile belongs to us, thus no border in up diretion.
				left = false;
			}
			else {

				// MAptile does not belong to us, thus border in up dir.
				left = true;

			}
		}

	}
	else {
		// Map end in up direction means its a border.
		left = true;
	}


	other_tile = nullptr;
	if (IsIndexOutOfBound(right_tile[0], right_tile[1]) == false) {

		other_tile = GetMapTileAtWorldPosition(right_tile[0], right_tile[1]);
		if (other_tile) {

			if (_belongMapTileToThisPlayer(other_tile) == false) {

				// The up tile belongs to us, thus no border in up diretion.
				right = false;
			}
			else {

				// MAptile does not belong to us, thus border in up dir.
				right = true;

			}
		}

	}
	else {
		// Map end in up direction means its a border.
		right = true;
	}


	return (up && right && left && down);
}

bool Player::_belongMapTileToThisPlayer(MapTile* tile) {

	MapTile* maptile = nullptr;

	for (auto it : m_PlayerCities) {

		for (auto iter : it->m_ClaimedRegions) {

			
			for (auto itr : iter->m_MapTileRegionTiles) {

				maptile = itr;

				if (maptile == tile) return true;
			}

		}

	}

	return false;

}


void City::_determineCityBorderTiles() {

	// Iterate through each regions maptiles.
	MapTileRegion* region = nullptr;
	MapTile* tile = nullptr;

	int tile_up[2], tile_down[2], tile_right[2], tile_left[2];

	bool up = false, down = false, right = false, left = false;


	for (auto it = m_ClaimedRegions.begin(); it != m_ClaimedRegions.end(); ++it) {

		region = *it;

		for (auto iter = region->m_MapTileRegionTiles.begin(); iter != region->m_MapTileRegionTiles.end(); ++iter) {

			tile = *iter;


			tile_up[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0];
			tile_up[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1] - 1;

			tile_down[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0];
			tile_down[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1] + 1;

			tile_right[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0] + 1;
			tile_right[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1];

			tile_left[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0] - 1;
			tile_left[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1];



			if (_isMapTileClaimedByCity(GetMapTileAtWorldPosition(tile_up[0], tile_up[1]))) { // true, if up is own maptile.
				up = true;
			}

			if (_isMapTileClaimedByCity(GetMapTileAtWorldPosition(tile_down[0], tile_down[1]))) {
				down = true;
			}

			if (_isMapTileClaimedByCity(GetMapTileAtWorldPosition(tile_right[0], tile_right[1]))) {
				right = true;
			}

			if (_isMapTileClaimedByCity(GetMapTileAtWorldPosition(tile_left[0], tile_left[1]))) {
				left = true;
			}





			if (up && down && right && left){
				// Means, this tile is surrounded by own, so no border tile.

				// reset for next tile.
				up = down = left = right = false;
				continue;
			}
			else {
				m_CityBorderMapTileVec.push_back(tile);
				up = down = left = right = false;
			}
		}
	}
}


void City::_determineMapTilesBorderDirection() {

	// Iterate through all border tiles.
	MapTile* tile = nullptr;
	int tile_up[2], tile_down[2], tile_right[2], tile_left[2];

	bool border_up = false, border_down = false, border_right = false, border_left = false;


	for (auto it = m_CityBorderMapTileVec.begin(); it != m_CityBorderMapTileVec.end(); ++it) {

		tile = *it;

		tile_up[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0];
		tile_up[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1] - 1;

		tile_down[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0];
		tile_down[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1] + 1;

		tile_right[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0] + 1;
		tile_right[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1];

		tile_left[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0] - 1;
		tile_left[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1];


		// Determine the border direction.
		if (_isMapTileClaimedByCity(GetMapTileAtWorldPosition(tile_up[0], tile_up[1])) == false) {

			// .. border in up direction.
			border_up = true;
		}
		
		if (_isMapTileClaimedByCity(GetMapTileAtWorldPosition(tile_down[0], tile_down[1])) == false) {
			
			// .. border in down direction.
			border_down = true;
		}
		
		if (_isMapTileClaimedByCity(GetMapTileAtWorldPosition(tile_right[0], tile_right[1])) == false) {
			
			// .. border in right direction.
			border_right = true;
		}
		
		if (_isMapTileClaimedByCity(GetMapTileAtWorldPosition(tile_left[0], tile_left[1])) == false) {
			
			// .. border in left direction.
			border_left = true;
		}

		
		// Define decal for appropriate bordertype.
		// In order to get valid results, we must iterate backwards all possibilities.
		if (border_up && border_down && border_right && !border_left) { // Three borders.
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_down_up_right"));

		}
		else if (!border_up && border_down && border_right && border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_left_right_down"));

		}
		else if (border_up && border_down && !border_right && border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_left_up_down"));

		}
		else if (border_up && !border_down && border_right && border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_left_up_right"));

		}
		else if (border_up && border_down && !border_right && !border_left) { // Two borders
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_up_down"));

		}
		else if (border_up && !border_down && border_right && !border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_up_right"));

		}
		else if (border_up && !border_down && !border_right && border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_up_left"));

		}
		else if (!border_up && border_down && border_right && !border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_down_right"));

		}
		else if (!border_up && border_down && !border_right && border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_down_left"));

		}
		else if (!border_up && !border_down && border_right && border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_left_right"));

		}
		else if (border_up && !border_down && !border_right && !border_left) { // One border.
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_up"));

		}
		else if (!border_up && border_down && !border_right && !border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_down"));

		}
		else if (!border_up && !border_down && border_right && !border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_right"));

		}
		else if (!border_up && !border_down && !border_right && border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_left"));

		}
		else {
			throw;
		}


		// Reset border flags...
		border_up = false, border_down = false, border_right = false, border_left = false;
	}
}


bool City::_isMapTileClaimedByCity(MapTile* maptile) {

	if (maptile == nullptr) return false;

	/*
	MapTile* other_tile = nullptr;

	// See whether we have claimed the region that has this maptile.
	for (auto it : this->m_ClaimedRegions) {
		for (auto iter : it->m_MapTileRegionTiles) {

			other_tile = iter;
			if (other_tile == maptile) return true;
		}
	}
	*/
	
	for (auto it : this->m_ClaimedRegions) {
		for (auto iter : it->m_MapTileRegionTiles) {
			if (maptile->m_AssociatedRegion == iter->m_AssociatedRegion) return true;
		}
	}
	
	return false;
}