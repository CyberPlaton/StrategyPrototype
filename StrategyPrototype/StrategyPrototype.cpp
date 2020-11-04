#include"StrategyPrototype.h"

static olc::vf2d g_vi2dCameraPosition = olc::vf2d(0.0f, 0.0f);
static int ColorValue = 0;


River* MakeNewRiver(std::string spritename, int x_cell_pos, int y_cell_pos) {

	// TODO:
	// Define later on which layer to render rivers...
	River* r = new River(spritename, "layer3", int(x_cell_pos * SPRITES_WIDTH_AND_HEIGHT), int(y_cell_pos * SPRITES_WIDTH_AND_HEIGHT));
	r->m_TransformCmp->m_GameWorldSpaceCell[0] = x_cell_pos;
	r->m_TransformCmp->m_GameWorldSpaceCell[1] = y_cell_pos;

	return r;
}

bool HasMapTileRiver(MapTile* maptile) {

	GameEntity* entity = nullptr;

	for (auto it = maptile->m_MapTileEntities->begin(); it != maptile->m_MapTileEntities->end(); ++it) {

		entity = *it;
		if (COMPARE_STRINGS(entity->m_IDCmp->m_DynamicTypeName, "River") == 0) return true;
	}

	return false;
}

int GetXPositionOfMapTile(MapTile* tile) {
	return(tile->m_TransformCmp->m_PosX);
}

int GetYPositionOfMapTile(MapTile* tile) {
	return(tile->m_TransformCmp->m_PosY);
}

void SpawnRandomCity() {

	int cell[2];

	cell[0] = Random() % 19;
	cell[1] = Random() % 19;


	int probability = Random() % 2;

	if (probability == 0) {

		if (GetMapTileAtWorldPosition(cell[0], cell[1])->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_TEMPERATE ||
			GetMapTileAtWorldPosition(cell[0], cell[1])->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_TUNDRA ||
			GetMapTileAtWorldPosition(cell[0], cell[1])->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_SAVANNAH ||
			GetMapTileAtWorldPosition(cell[0], cell[1])->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_JUNGLE)
		{

			int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(cell[0], cell[1]));
			int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(cell[0], cell[1]));

			/*
 			City* city = MakeNewCityAtPos("Village", "city_human_small", *EntitiesStorage::Get()->GetPlayersVec()->begin(), xpos, ypos, cell[0], cell[1]);
			city->ClaimRegions();
			
			EntitiesStorage::Get()->AddGameEntitie(city);
			
			using namespace std;
			cout << APP_SUCCESS_COLOR;
			cout << "City created at  XY-(" << city->m_TransformCmp->m_PosX << ":" << city->m_TransformCmp->m_PosY << ") "
				<< " --  Cell-(" << city->m_TransformCmp->m_GameWorldSpaceCell[0] << ":" << city->m_TransformCmp->m_GameWorldSpaceCell[1] << ") ." << white << endl;
			*/
		}

	}
}


Player* GetPlayer(std::string name) {
	
	for (auto it : *EntitiesStorage::Get()->GetPlayersVec()) {

		if (COMPARE_STRINGS_2(name, it->m_PlayerName) == 0) {
			return it;
		}
	}
}


MapTile* GetMaptileAtMousePosition(int x, int y) {

	int x_cell = int((x + g_vi2dCameraPosition.x) / SPRITES_WIDTH_AND_HEIGHT);
	int y_cell = int((y + g_vi2dCameraPosition.y) / SPRITES_WIDTH_AND_HEIGHT);

	if (IsIndexOutOfBound(x_cell, y_cell) == false) {
		return (GetMapTileAtWorldPosition(x_cell, y_cell));
	}

	return nullptr;
}



MapTileRegion* GetRegionAtWorldPosition(int x, int y) {

	int x_cell = int((x + g_vi2dCameraPosition.x)/ SPRITES_WIDTH_AND_HEIGHT);
	int y_cell = int((y + g_vi2dCameraPosition.y) / SPRITES_WIDTH_AND_HEIGHT);

	if (IsIndexOutOfBound(x_cell, y_cell) == false) {
		return (GetMapTileAtWorldPosition(x_cell, y_cell)->m_AssociatedRegion);
	}

	return nullptr;
}


bool RaiseDeepForestRandomly() {

	int r = Random() % 999;
	return ((r == 0) ? true : false);
}


Mountains* MakeNewMountain(std::string spritename, int x_cell_pos, int y_cell_pos) {

	// We draw standardized forests on layer3, so skip this part from the user...
	Mountains* mountain = new Mountains(spritename, "layer2", x_cell_pos * SPRITES_WIDTH_AND_HEIGHT, y_cell_pos * SPRITES_WIDTH_AND_HEIGHT);

	mountain->m_TransformCmp->m_GameWorldSpaceCell[0] = x_cell_pos;
	mountain->m_TransformCmp->m_GameWorldSpaceCell[1] = y_cell_pos;

	return mountain;
}



City* MakeNewCity(bool city, std::string cityname, CMPEntityRace::Race race, Player* player, int x_cell_pos, int y_cell_pos, int citySize) {

	City* c = new City(cityname, city, race, player, x_cell_pos * SPRITES_WIDTH_AND_HEIGHT, y_cell_pos * SPRITES_WIDTH_AND_HEIGHT, citySize);

	c->m_TransformCmp->m_GameWorldSpaceCell[0] = x_cell_pos;
	c->m_TransformCmp->m_GameWorldSpaceCell[1] = y_cell_pos;


	c->ClaimRegions();
	c->MakeCityBorders();

	return c;
}

// This function is very useful for dynamically creating a city, especially
// if the user is moving the camera. With it we can reliably determine the right x-y-position
// for the new city and the right x-y-cell.
City* MakeNewCityAtPos(bool city, std::string cityname, CMPEntityRace::Race race, Player* player, int xpos, int ypos, int set_x_cell_pos, int set_y_cell_pos, int citySize) {

	City* c = new City(cityname, city, race, player, xpos, ypos, citySize);

	c->m_TransformCmp->m_GameWorldSpaceCell[0] = set_x_cell_pos;
	c->m_TransformCmp->m_GameWorldSpaceCell[1] = set_y_cell_pos;

	c->ClaimRegions();
	c->MakeCityBorders();

	return c;

}


Hills* MakeNewHill(std::string spritename, int x_cell_pos, int y_cell_pos) {

	// We draw standardized forests on layer3, so skip this part from the user...
	Hills* hills = new Hills(spritename, "layer2", x_cell_pos * SPRITES_WIDTH_AND_HEIGHT, y_cell_pos * SPRITES_WIDTH_AND_HEIGHT);

	hills->m_TransformCmp->m_GameWorldSpaceCell[0] = x_cell_pos;
	hills->m_TransformCmp->m_GameWorldSpaceCell[1] = y_cell_pos;

	return hills;
}


MapTile* GetMapTileAtXYPosition(int x, int y) {

	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* > vec = *storage->GetMapTilesStorage();

	MapTile* maptile = nullptr;

 	for (auto it = vec.begin(); it != vec.end(); ++it) {
		
		maptile = reinterpret_cast<MapTile*>(*it);

		if (maptile->m_TransformCmp->m_PosX == x && maptile->m_TransformCmp->m_PosY == y) return maptile;
	}

	return nullptr;
}

bool IsMapTilePartOfRegion(MapTile* tile) {

	if (!nullptr) return false;
	if (IsIndexOutOfBound(tile->m_TransformCmp->m_GameWorldSpaceCell[0], tile->m_TransformCmp->m_GameWorldSpaceCell[1])) return false;

	// This MapTile is already part of a region.
	if (tile->m_AssociatedRegion == nullptr) return true;

	return false;
}


olc::Pixel* Game::RandomColor(){

	int r = Random() % 6;

	switch (r){
	case 0:
		return &olc::Pixel(olc::BLUE);
		break;
	case 1:
		return &olc::Pixel(olc::GREEN);
		break;
	case 2:
		return &olc::Pixel(olc::RED);
		break;
	case 3:
		return &olc::Pixel(olc::MAGENTA);
		break;
	case 4:
		return &olc::Pixel(olc::YELLOW);
		break;
	case 5:
		return &olc::Pixel(olc::CYAN);
		break;
	default:
		break;
	}
}


std::string MapTileTypeToString(MapTile* tile) {

	if (tile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_ICE) return "ICE";
	else if (tile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_SAND) return "SAND";
	else if (tile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_SAVANNAH) return "SAVANNAH";
	else if (tile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_SNOW) return "SNOW";
	else if (tile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_TEMPERATE) return "TEMPERATE";
	else if (tile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_TUNDRA) return "TUNDRA";
	else if (tile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_WATER_DEEP) return "WATER_DEEP";
	else if (tile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_WATER_SHALLOW) return "WATER_SHALLOW";
	else if (tile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_JUNGLE) return "JUNGLE";


	else return "TYPE_INVALID";
}

bool MapTileAppropriteForForest(MapTile* tile, Forest* forest) {

	/*
	switch (tile->m_MapTileType) {
	case MapTile::MapTileType::MAPTILE_TYPE_ICE:
		return false;
		break;
	case  MapTile::MapTileType::MAPTILE_TYPE_SAND:
		return false;
		break;
	case MapTile::MapTileType::MAPTILE_TYPE_SAVANNAH:
		if (forest->m_ForestClass == Forest::ForestClass::FOREST_CLASS_SAVANNAH) return true;
		else return false;
		break;
	case  MapTile::MapTileType::MAPTILE_TYPE_SNOW:
		return false;
		break;
	case MapTile::MapTileType::MAPTILE_TYPE_TEMPERATE:
		if (forest->m_ForestClass == Forest::ForestClass::FOREST_CLASS_TEMPERATE) return true;
		else return false;
		break;
	case MapTile::MapTileType::MAPTILE_TYPE_JUNGLE:
		if (forest->m_ForestClass == Forest::ForestClass::FOREST_CLASS_JUNGLE) return true;
		else return false;
		break;
	case  MapTile::MapTileType::MAPTILE_TYPE_TUNDRA:
		if (forest->m_ForestClass == Forest::ForestClass::FOREST_CLASS_TUNDRA) return true;
		else return false;
		break;
	case MapTile::MapTileType::MAPTILE_TYPE_WATER_DEEP:
		return false;
		break;
	case  MapTile::MapTileType::MAPTILE_TYPE_WATER_SHALLOW:
		return false;
		break;

	}
	*/
	bool tile_type_ok = false;
	bool tile_free = true;

	// Check whether maptile is appropriate for forest type.
	switch (tile->m_MapTileType) {
	case MapTile::MapTileType::MAPTILE_TYPE_SAVANNAH:
		if (forest->m_ForestClass == Forest::ForestClass::FOREST_CLASS_SAVANNAH) tile_type_ok =  true;
		break;
	case MapTile::MapTileType::MAPTILE_TYPE_TEMPERATE:
		if (forest->m_ForestClass == Forest::ForestClass::FOREST_CLASS_TEMPERATE) tile_type_ok =  true;
		break;
	case MapTile::MapTileType::MAPTILE_TYPE_JUNGLE:
		if (forest->m_ForestClass == Forest::ForestClass::FOREST_CLASS_JUNGLE) tile_type_ok =  true;
		break;
	case  MapTile::MapTileType::MAPTILE_TYPE_TUNDRA:
		if (forest->m_ForestClass == Forest::ForestClass::FOREST_CLASS_TUNDRA) tile_type_ok = true;
		break;
	default:
		break;
	}


	// Now check whether there is a mountain or city etc.
	for (auto it : *tile->m_MapTileEntities) {

		if (COMPARE_STRINGS(it->m_IDCmp->m_DynamicTypeName, "Mountains") == 0) {
			tile_free = false;
		}
		else if (COMPARE_STRINGS(it->m_IDCmp->m_DynamicTypeName, "Hills") == 0) {
			tile_free = false;
		}
		else if (COMPARE_STRINGS(it->m_IDCmp->m_DynamicTypeName, "City") == 0) {
			tile_free = false;
		}

	}


	return (tile_type_ok && tile_free);
}


Forest* MakeNewForest(std::string name, int x_cell_pos, int y_cell_pos) {

	// We draw standardized forests on layer3, so skip this part from the user...
	Forest* forest = new Forest(name, "layer3", x_cell_pos * SPRITES_WIDTH_AND_HEIGHT, y_cell_pos * SPRITES_WIDTH_AND_HEIGHT);

	forest->m_TransformCmp->m_GameWorldSpaceCell[0] = x_cell_pos;
	forest->m_TransformCmp->m_GameWorldSpaceCell[1] = y_cell_pos;

	// Forests AI is standardized, only one state is legal and every forests has an AI, thus skip this part from the user...
	forest->m_AICmp->ChangeState(States::STATE_SEARCH);
	forest->m_AICmp->MapState("state_search", new ForestSearch(*forest->m_AICmp));

	return ((forest == nullptr) ? nullptr : forest);
}


Forest* MakeNewForestAtPos(std::string name, int xpos, int ypos, int set_x_cell, int set_y_cell){

	// We draw standardized forests on layer3, so skip this part from the user...
	Forest* forest = new Forest(name, "layer3", xpos, ypos);

	forest->m_TransformCmp->m_GameWorldSpaceCell[0] = set_x_cell;
	forest->m_TransformCmp->m_GameWorldSpaceCell[1] = set_y_cell;

	// Forests AI is standardized, only one state is legal and every forests has an AI, thus skip this part from the user...
	forest->m_AICmp->ChangeState(States::STATE_SEARCH);
	forest->m_AICmp->MapState("state_search", new ForestSearch(*forest->m_AICmp));

	return ((forest == nullptr) ? nullptr : forest);

}


bool IsSubstringInString(std::string substring, std::string string) {

	if (string.find(substring) != std::string::npos) {
		return true;
	}
	return false;
}


bool IsIndexOutOfBound(int x, int y) {

	if (x < 0 || y < 0) return true;

	// Mapsize counts from 1,..20 for example,
	// thus we need to check for x > MAP_SIZE - 1...

	if (x > MAP_SIZE - 1 ||
		y > MAP_SIZE - 1) return true;


	return false;
}


int GetTotalForestsCount() {

	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* > vec = *storage->GetStorage();
	GameEntity* entt = nullptr;


	int forest_count = 0;
	for (auto it = vec.begin(); it != vec.end(); ++it) {

		entt = *it;

		if (COMPARE_STRINGS(entt->m_IDCmp->m_DynamicTypeName, "Forest") == 0) forest_count++;
	}

	return forest_count;
}


MapTile* GetMapTileAtWorldPosition(int x, int y) {

	if (x < 0 || y < 0) return nullptr;


	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* > vec = *storage->GetMapTilesStorage();
	GameEntity* entity = nullptr;

	for (auto it = vec.begin(); it != vec.end(); ++it) {

		entity = *it;

		if (entity->m_TransformCmp->m_GameWorldSpaceCell[0] == x && entity->m_TransformCmp->m_GameWorldSpaceCell[1] == y) {
			return static_cast<MapTile*>(entity);
		}
	}

	// Nothing found. Means not valid index for maptile or some other weird error.
	return nullptr;
}


// The DynamicType of an Entity is basically its Class Name.
GameEntity* IsGameEntityTypeOnMapTile(MapTile* maptile, std::string dynamicTypeName) {

	if (maptile == nullptr) return nullptr;


	std::vector< GameEntity* > vec = *maptile->m_MapTileEntities;
	GameEntity* entt = nullptr;


	for (auto it = vec.begin(); it != vec.end(); ++it) {

		entt = *it;

		if (COMPARE_STRINGS_2(entt->m_IDCmp->m_DynamicTypeName, dynamicTypeName) == 0) return entt;
	}

	// Entity not present.
	return nullptr;
}


std::vector<GameEntity*> GetForestEntities() {

	std::vector<GameEntity*> return_vector;

	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* > vec = *storage->GetMapTilesStorage();
	
	MapTile* maptile = nullptr;
	GameEntity* entity = nullptr;

	for (auto it = vec.begin(); it != vec.end(); ++it) {

		maptile = reinterpret_cast<MapTile*>(*it);

		entity = IsGameEntityTypeOnMapTile(maptile, "Forest");

		if (entity) {

			return_vector.push_back(entity);
		}
	}

	return return_vector;

}







void CMPCameraInput::HandleKeyboard(Camera* cam) {

	Game* context = cam->m_Game;

	switch (context->m_Renderer->m_RenderMode) {
	case Renderer::RenderMode::RENDERMODE_CITYVIEW:
		_handleCityViewKeyboard(cam);
		break;
	case Renderer::RenderMode::RENDERMODE_MAPVIEW:
		_handleMapViewKeyBoard(cam);
		break;
	default:
		break;
	}
}


void CMPCameraInput::_handleMapViewKeyBoard(Camera* cam) {

	Game* context = cam->m_Game;

	int speed = 4;

	if (context->GetKey(olc::Key::ENTER).bReleased) {
		context->m_Renderer->ChangeRenderMode();
	}

	if (context->GetKey(olc::Key::CTRL).bHeld) {

		if (context->GetKey(olc::Key::G).bPressed) {

			context->m_DebugDrawGrid = (context->m_DebugDrawGrid == true) ? false : true;
		}

		if (context->GetKey(olc::Key::TAB).bPressed) {
			context->m_DebugDrawGeneralOptions = (context->m_DebugDrawGeneralOptions == true) ? false : true;
		}

		if (context->GetKey(olc::Key::M).bPressed) {
			context->m_DebugDrawMapTileInfo = (context->m_DebugDrawMapTileInfo == true) ? false : true;
		}

		if (context->GetKey(olc::Key::F).bPressed) {
			context->m_DebugDrawForestInfo = (context->m_DebugDrawForestInfo == true) ? false : true;
		}

		if (context->GetKey(olc::Key::R).bPressed) {
			context->m_DebugDrawRegions = (context->m_DebugDrawRegions == true) ? false : true;
		}

		if (context->GetKey(olc::Key::T).bPressed) {
			context->m_TimeModeTurnBased = (context->m_TimeModeTurnBased == true) ? false : true;
		}


		if (context->GetKey(olc::Key::P).bPressed) {

			using namespace std;
			cout << APP_COLOR;
			cout << "Players in game: " << endl;

			for (auto it : *EntitiesStorage::Get()->GetPlayersVec()) {

				cout << "NAME: " << it->m_PlayerName << endl;
				cout << "COLOR: " << it->m_PlayerColor << endl;
				cout << "CITIES: " << it->m_PlayerCities.size() << endl;

			}


		}


		if (context->GetKey(olc::Key::SPACE).bPressed) {
			Player* p = GetPlayer("Bogdan");

			for (auto it : p->m_PlayerCities) {
				ColorValue = (ColorValue + 1) % 8;
				it->m_CityBorderColor = City::CityBorderColor(ColorValue);
			}
		}

	}

	if (context->GetKey(olc::Key::P).bPressed) {

		City* city = nullptr;
		for (auto it : *EntitiesStorage::Get()->GetCitiesVec()) {
			
			city = reinterpret_cast<City*>(it);

			/*
			if (COMPARE_STRINGS(city->m_CityName, "Stormhaven") == 0) {

				city->m_CitySize--;
				city->Update();
			}
			else {

				city->m_CitySize++;
				city->Update();
			}
			*/
			city->m_CitySize++;
			city->Update();
		}

	}

	if (context->GetKey(olc::Key::O).bPressed) {

		City* city = nullptr;
		for (auto it : *EntitiesStorage::Get()->GetCitiesVec()) {

			city = reinterpret_cast<City*>(it);

			city->m_CitySize--;
			city->Update();
		}

	}

	if (context->GetKey(olc::Key::M).bPressed) {

		context->m_PoliticalMap = (context->m_PoliticalMap == false) ? true : false;
	}

	if (context->GetKey(olc::Key::SPACE).bReleased) {

		if (context->m_TimeModeTurnBased == false) return;

		using namespace std;

		int turn = context->m_TurnCount;

		cout << APP_ERROR_COLOR;
		cout << "EXECUTING TURN " << turn << " AI LOGIC." << white << endl;

		context->AdvanceOneTurn();

		cout << APP_ERROR_COLOR;
		cout << "EXECUTED TURN " << turn << " AI LOGIC." << white << endl << endl << endl;

	}

	if (context->GetKey(olc::Key::SHIFT).bHeld) {
		speed = 4;
	}


	if (context->GetKey(olc::Key::W).bHeld) {

		if (g_vi2dCameraPosition.y <= 0) {
			g_vi2dCameraPosition.y = 0; return;
		}


		g_vi2dCameraPosition.y -= 1 * speed;

		for (auto it : *EntitiesStorage::Get()->GetMapTilesStorage()) {

			it->m_TransformCmp->m_PosY += 1 * speed;

			if (static_cast<MapTile*>(it)->m_MapTileEntities != nullptr) {
				if (static_cast<MapTile*>(it)->m_MapTileEntities->size() > 0) {


					for (auto iter : *static_cast<MapTile*>(it)->m_MapTileEntities) {

						iter->m_TransformCmp->m_PosY += 1 * speed;
					}
				}
			}
		}
	}

	if (context->GetKey(olc::Key::A).bHeld) {

		if (g_vi2dCameraPosition.x <= 0) {
			g_vi2dCameraPosition.x = 0; return;
		}


		g_vi2dCameraPosition.x -= 1 * speed;

		for (auto it : *EntitiesStorage::Get()->GetMapTilesStorage()) {

			it->m_TransformCmp->m_PosX += 1 * speed;


			if (static_cast<MapTile*>(it)->m_MapTileEntities != nullptr) {
				if (static_cast<MapTile*>(it)->m_MapTileEntities->size() > 0) {


					for (auto iter : *static_cast<MapTile*>(it)->m_MapTileEntities) {

						iter->m_TransformCmp->m_PosX += 1 * speed;
					}
				}
			}
		}
	}

	if (context->GetKey(olc::Key::S).bHeld) {

		if (g_vi2dCameraPosition.y >= MAP_SIZE * SPRITES_WIDTH_AND_HEIGHT) {
			g_vi2dCameraPosition.y = MAP_SIZE * SPRITES_WIDTH_AND_HEIGHT; return;
		}


		g_vi2dCameraPosition.y += 1 * speed;

		for (auto it : *EntitiesStorage::Get()->GetMapTilesStorage()) {

			it->m_TransformCmp->m_PosY -= 1 * speed;


			if (static_cast<MapTile*>(it)->m_MapTileEntities != nullptr) {
				if (static_cast<MapTile*>(it)->m_MapTileEntities->size() > 0) {


					for (auto iter : *static_cast<MapTile*>(it)->m_MapTileEntities) {

						iter->m_TransformCmp->m_PosY -= 1 * speed;
					}
				}
			}
		}
	}

	if (context->GetKey(olc::Key::D).bHeld) {

		if (g_vi2dCameraPosition.x >= MAP_SIZE * SPRITES_WIDTH_AND_HEIGHT) {
			g_vi2dCameraPosition.x = MAP_SIZE * SPRITES_WIDTH_AND_HEIGHT; return;
		}

		g_vi2dCameraPosition.x += 1 * speed;

		for (auto it : *EntitiesStorage::Get()->GetMapTilesStorage()) {

			it->m_TransformCmp->m_PosX -= 1 * speed;


			if (static_cast<MapTile*>(it)->m_MapTileEntities != nullptr) {
				if (static_cast<MapTile*>(it)->m_MapTileEntities->size() > 0) {


					for (auto iter : *static_cast<MapTile*>(it)->m_MapTileEntities) {

						iter->m_TransformCmp->m_PosX -= 1 * speed;
					}
				}
			}
		}
	}


	if (context->GetKey(olc::Key::ESCAPE).bReleased) {

		exit(0);
	}
}


void CMPCameraInput::_handleCityViewKeyboard(Camera* cam) {

	Game* context = cam->m_Game;


	if (context->GetKey(olc::Key::ESCAPE).bReleased) {

		context->m_Renderer->ChangeRenderMode();
	}

}


void CMPCameraInput::_handleMapViewMouse(Camera* cam) {

	Game* context = cam->m_Game;


	// Draw Region around mouse position.
	MapTileRegion* region = nullptr;

	region = GetRegionAtWorldPosition(context->GetMouseX(), context->GetMouseY());

	if (region != nullptr) {

		for (auto it : region->m_MapTileRegionTiles) {


			context->DrawDecal(olc::vi2d(it->m_TransformCmp->m_PosX, it->m_TransformCmp->m_PosY),
				context->m_SpriteResourceMap.at("map_cell_white"));

		}
	}

	MapTile* tile = nullptr;
	if (context->GetMouse(0).bPressed) {

		tile = GetMaptileAtMousePosition(context->GetMouseX(), context->GetMouseY());

		for (auto it : *tile->m_MapTileEntities) {

			if (COMPARE_STRINGS(it->m_IDCmp->m_DynamicTypeName, "City") == 0) {

				context->m_Renderer->ChangeRenderMode();

			}
		}
	}
}


void CMPCameraInput::_handleCityViewMouse(Camera* cam) {

	Game* context = cam->m_Game;


}


void CMPCameraInput::HandleMouse(Camera* cam) {

	Game* context = cam->m_Game;

	switch (context->m_Renderer->m_RenderMode) {
	case Renderer::RenderMode::RENDERMODE_CITYVIEW:
		_handleCityViewMouse(cam);
		break;
	case Renderer::RenderMode::RENDERMODE_MAPVIEW:
		_handleMapViewMouse(cam);
		break;
	default:
		break;
	}
}



void Game::_loadSpriteResources() {

	using namespace olc;
	
	// Loading sprites and decals.
	Sprite* s1 = new Sprite("assets/map/forest_temperate_normal.png");
	Sprite* s2 = new Sprite("assets/map/forest_temperate_deep.png");
	Sprite* s3 = new Sprite("assets/map/forest_temperate_scarce.png");
	Sprite* s5 = new Sprite("assets/map/forest_tundra_normal.png");
	Sprite* s6 = new Sprite("assets/map/forest_tundra_deep.png");
	Sprite* s7 = new Sprite("assets/map/forest_tundra_scarce.png");
	Sprite* s8 = new Sprite("assets/map/highmountain.png");
	Sprite* s9 = new Sprite("assets/map/hills.png");
	Sprite* s10 = new Sprite("assets/map/ice.png");
	Sprite* s12 = new Sprite("assets/map/sand.png");
	Sprite* s13 = new Sprite("assets/map/savannah.png");
	Sprite* s14 = new Sprite("assets/map/snow.png");
	Sprite* s15 = new Sprite("assets/map/temperate.png");
	Sprite* s16 = new Sprite("assets/map/tundra.png");
	Sprite* s17 = new Sprite("assets/map/water_deep.png");
	Sprite* s18 = new Sprite("assets/map/water_shallow.png");
	Sprite* s0 = new Sprite("assets/map/jungle.png");

	
	Sprite* s19 = new Sprite("assets/map/forest_temperate_dying.png");
	Sprite* s20 = new Sprite("assets/map/forest_tundra_dying.png");


	Sprite* s21 = new Sprite("assets/map/forest_savannah_scarce.png");
	Sprite* s4 = new Sprite("assets/map/forest_savannah_normal.png");
	Sprite* s22 = new Sprite("assets/map/forest_savannah_deep.png");
	Sprite* s23 = new Sprite("assets/map/forest_savannah_dying.png");


	Sprite* s24 = new Sprite("assets/map/forest_jungle_scarce.png");
	Sprite* s11 = new Sprite("assets/map/forest_jungle_normal.png");
	Sprite* s25 = new Sprite("assets/map/forest_jungle_deep.png");
	Sprite* s26 = new Sprite("assets/map/forest_jungle_dying.png");




	// Load colored cells
	Sprite* c1 = new Sprite("assets/map/overlay_cell/map_cell_black.png");
	Sprite* c2 = new Sprite("assets/map/overlay_cell/map_cell_blue.png");
	Sprite* c3 = new Sprite("assets/map/overlay_cell/map_cell_brown.png");
	Sprite* c4 = new Sprite("assets/map/overlay_cell/map_cell_green.png");
	Sprite* c5 = new Sprite("assets/map/overlay_cell/map_cell_magenta.png");
	Sprite* c6 = new Sprite("assets/map/overlay_cell/map_cell_orange.png");
	Sprite* c7 = new Sprite("assets/map/overlay_cell/map_cell_red.png");
	Sprite* c8 = new Sprite("assets/map/overlay_cell/map_cell_yellow.png");
	Sprite* c9 = new Sprite("assets/map/overlay_cell/map_cell_white.png");


	// Borders cells
	Sprite* c10 = new Sprite("assets/map/overlay_cell/map_cell_border_down.png");
	Sprite* c11 = new Sprite("assets/map/overlay_cell/map_cell_border_down_left.png");
	Sprite* c12 = new Sprite("assets/map/overlay_cell/map_cell_border_down_right.png");
	Sprite* c13 = new Sprite("assets/map/overlay_cell/map_cell_border_down_up_right.png");
	Sprite* c14 = new Sprite("assets/map/overlay_cell/map_cell_border_left.png");
	Sprite* c15 = new Sprite("assets/map/overlay_cell/map_cell_border_left_right.png");
	Sprite* c16 = new Sprite("assets/map/overlay_cell/map_cell_border_left_right_down.png");
	Sprite* c17 = new Sprite("assets/map/overlay_cell/map_cell_border_left_up_down.png");
	Sprite* c18 = new Sprite("assets/map/overlay_cell/map_cell_border_left_up_right.png");
	Sprite* c19 = new Sprite("assets/map/overlay_cell/map_cell_border_right.png");
	Sprite* c20 = new Sprite("assets/map/overlay_cell/map_cell_border_up.png");
	Sprite* c21 = new Sprite("assets/map/overlay_cell/map_cell_border_up_down.png");
	Sprite* c22 = new Sprite("assets/map/overlay_cell/map_cell_border_up_left.png");
	Sprite* c23 = new Sprite("assets/map/overlay_cell/map_cell_border_up_right.png");


	m_SpriteStorage.push_back(c1);
	m_SpriteStorage.push_back(c2);
	m_SpriteStorage.push_back(c3);
	m_SpriteStorage.push_back(c4);
	m_SpriteStorage.push_back(c5);
	m_SpriteStorage.push_back(c6);
	m_SpriteStorage.push_back(c7);
	m_SpriteStorage.push_back(c8);
	m_SpriteStorage.push_back(c9);

	m_SpriteStorage.push_back(c10);
	m_SpriteStorage.push_back(c11);
	m_SpriteStorage.push_back(c12);
	m_SpriteStorage.push_back(c13);
	m_SpriteStorage.push_back(c14);
	m_SpriteStorage.push_back(c15);
	m_SpriteStorage.push_back(c16);
	m_SpriteStorage.push_back(c17);
	m_SpriteStorage.push_back(c18);
	m_SpriteStorage.push_back(c19);
	m_SpriteStorage.push_back(c20);
	m_SpriteStorage.push_back(c21);
	m_SpriteStorage.push_back(c22);
	m_SpriteStorage.push_back(c23);


	Decal* dec10 = new Decal(c10);
	Decal* dec11 = new Decal(c11);
	Decal* dec12 = new Decal(c12);
	Decal* dec13 = new Decal(c13);
	Decal* dec14 = new Decal(c14);
	Decal* dec15 = new Decal(c15);
	Decal* dec16 = new Decal(c16);
	Decal* dec17 = new Decal(c17);
	Decal* dec18 = new Decal(c18);
	Decal* dec19 = new Decal(c19);
	Decal* dec20 = new Decal(c20);
	Decal* dec21 = new Decal(c21);
	Decal* dec22 = new Decal(c22);
	Decal* dec23 = new Decal(c23);

	m_SpriteResourceMap.insert(std::make_pair("map_cell_border_down", dec10));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_border_down_left", dec11));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_border_down_right", dec12));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_border_down_up_right", dec13));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_border_left", dec14));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_border_left_right", dec15));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_border_left_right_down", dec16));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_border_left_up_down", dec17));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_border_left_up_right", dec18));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_border_right", dec19));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_border_up", dec20));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_border_up_down", dec21));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_border_up_left", dec22));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_border_up_right", dec23));


	// River tiles.
	Sprite* rv1 = new Sprite("assets/map/river_down_left.png");
	Sprite* rv2 = new Sprite("assets/map/river_down_right.png");
	Sprite* rv3 = new Sprite("assets/map/river_left_right.png");
	Sprite* rv4 = new Sprite("assets/map/river_left_right_down.png");
	Sprite* rv5 = new Sprite("assets/map/river_left_up_down.png");
	Sprite* rv6 = new Sprite("assets/map/river_up_down.png");
	Sprite* rv7 = new Sprite("assets/map/river_up_left.png");
	Sprite* rv8 = new Sprite("assets/map/river_up_right.png");
	Sprite* rv9 = new Sprite("assets/map/river_up_right_down.png");
	Sprite* rv10 = new Sprite("assets/map/river_up_right_left.png");
	Sprite* rv11 = new Sprite("assets/map/river_up_right_left_down.png");

	m_SpriteStorage.push_back(rv1);
	m_SpriteStorage.push_back(rv2);
	m_SpriteStorage.push_back(rv3);
	m_SpriteStorage.push_back(rv4);
	m_SpriteStorage.push_back(rv5);
	m_SpriteStorage.push_back(rv6);
	m_SpriteStorage.push_back(rv7);
	m_SpriteStorage.push_back(rv8);
	m_SpriteStorage.push_back(rv9);
	m_SpriteStorage.push_back(rv10);
	m_SpriteStorage.push_back(rv11);

	Decal* drv1 = new Decal(rv1);
	Decal* drv2 = new Decal(rv2);
	Decal* drv3 = new Decal(rv3);
	Decal* drv4 = new Decal(rv4);
	Decal* drv5 = new Decal(rv5);
	Decal* drv6 = new Decal(rv6);
	Decal* drv7 = new Decal(rv7);
	Decal* drv8 = new Decal(rv8);
	Decal* drv9 = new Decal(rv9);
	Decal* drv10 = new Decal(rv10);
	Decal* drv11 = new Decal(rv11);

	m_SpriteResourceMap.insert(std::make_pair("river_down_left", drv1));
	m_SpriteResourceMap.insert(std::make_pair("river_down_right", drv2));
	m_SpriteResourceMap.insert(std::make_pair("river_left_right", drv3));
	m_SpriteResourceMap.insert(std::make_pair("river_left_right_down", drv4));
	m_SpriteResourceMap.insert(std::make_pair("river_left_up_down", drv5));
	m_SpriteResourceMap.insert(std::make_pair("river_up_down", drv6));
	m_SpriteResourceMap.insert(std::make_pair("river_up_left", drv7));
	m_SpriteResourceMap.insert(std::make_pair("river_up_right", drv8));
	m_SpriteResourceMap.insert(std::make_pair("river_up_right_down", drv9));
	m_SpriteResourceMap.insert(std::make_pair("river_up_right_left", drv10));
	m_SpriteResourceMap.insert(std::make_pair("river_up_right_left_down", drv11));



	// Mapview Ressources
	Sprite* r1 = new Sprite("assets/ressources/mapview/ressource_map_bear.png");
	Sprite* r2 = new Sprite("assets/ressources/mapview/ressource_map_boar.png");
	Sprite* r3 = new Sprite("assets/ressources/mapview/ressource_map_deer.png");
	Sprite* r4 = new Sprite("assets/ressources/mapview/ressource_map_horse.png");
	Sprite* r5 = new Sprite("assets/ressources/mapview/ressource_map_raptor.png");
	Sprite* r6 = new Sprite("assets/ressources/mapview/ressource_map_guar.png");


	m_SpriteStorage.push_back(r1);
	m_SpriteStorage.push_back(r2);
	m_SpriteStorage.push_back(r3);
	m_SpriteStorage.push_back(r4);
	m_SpriteStorage.push_back(r5);
	m_SpriteStorage.push_back(r6);



	// Decals for mapressources
	Decal* dr1 = new Decal(r1);
	Decal* dr2 = new Decal(r2);
	Decal* dr3 = new Decal(r3);
	Decal* dr4 = new Decal(r4);
	Decal* dr5 = new Decal(r5);
	Decal* dr6 = new Decal(r6);


	m_SpriteResourceMap.insert(std::make_pair("ressource_map_bear", dr1));
	m_SpriteResourceMap.insert(std::make_pair("ressource_map_boar", dr2));
	m_SpriteResourceMap.insert(std::make_pair("ressource_map_deer", dr3));
	m_SpriteResourceMap.insert(std::make_pair("ressource_map_horse", dr4));
	m_SpriteResourceMap.insert(std::make_pair("ressource_map_raptor", dr5));
	m_SpriteResourceMap.insert(std::make_pair("ressource_map_guar", dr6));




	// Decals for colored cells
	Decal* dc1 = new Decal(c1);
	Decal* dc2 = new Decal(c2);
	Decal* dc3 = new Decal(c3);
	Decal* dc4 = new Decal(c4);
	Decal* dc5 = new Decal(c5);
	Decal* dc6 = new Decal(c6);
	Decal* dc7 = new Decal(c7);
	Decal* dc8 = new Decal(c8);
	Decal* dc9 = new Decal(c9);



	m_SpriteStorage.push_back(s0);
	m_SpriteStorage.push_back(s1);
	m_SpriteStorage.push_back(s2);
	m_SpriteStorage.push_back(s3);
	m_SpriteStorage.push_back(s4);
	m_SpriteStorage.push_back(s5);
	m_SpriteStorage.push_back(s6);
	m_SpriteStorage.push_back(s7);
	m_SpriteStorage.push_back(s8);
	m_SpriteStorage.push_back(s9);
	m_SpriteStorage.push_back(s10);
	m_SpriteStorage.push_back(s11);
	m_SpriteStorage.push_back(s12);
	m_SpriteStorage.push_back(s13);
	m_SpriteStorage.push_back(s14);
	m_SpriteStorage.push_back(s15);
	m_SpriteStorage.push_back(s16);
	m_SpriteStorage.push_back(s17);
	m_SpriteStorage.push_back(s18);
	m_SpriteStorage.push_back(s19);
	m_SpriteStorage.push_back(s20);
	m_SpriteStorage.push_back(s21);
	m_SpriteStorage.push_back(s22);
	m_SpriteStorage.push_back(s23);
	m_SpriteStorage.push_back(s24);
	m_SpriteStorage.push_back(s25);
	m_SpriteStorage.push_back(s26);




	Decal* d0 = new Decal(s0);
	Decal* d1 = new Decal(s1);
	Decal* d2 = new Decal(s2);
	Decal* d3 = new Decal(s3);
	Decal* d4 = new Decal(s4);
	Decal* d5 = new Decal(s5);
	Decal* d6 = new Decal(s6);
	Decal* d7 = new Decal(s7);
	Decal* d8 = new Decal(s8);
	Decal* d9 = new Decal(s9);
	Decal* d10 = new Decal(s10);
	Decal* d11 = new Decal(s11);
	Decal* d12 = new Decal(s12);
	Decal* d13 = new Decal(s13);
	Decal* d14 = new Decal(s14);
	Decal* d15 = new Decal(s15);
	Decal* d16 = new Decal(s16);
	Decal* d17 = new Decal(s17);
	Decal* d18 = new Decal(s18);
	Decal* d19 = new Decal(s19);
	Decal* d20 = new Decal(s20);
	Decal* d21 = new Decal(s21);
	Decal* d22 = new Decal(s22);
	Decal* d23 = new Decal(s23);
	Decal* d24 = new Decal(s24);
	Decal* d25 = new Decal(s25);
	Decal* d26 = new Decal(s26);





	// Create Decals from sprites.
	m_SpriteResourceMap.insert(std::make_pair("jungle", d0));
	m_SpriteResourceMap.insert(std::make_pair("forest_temperate_normal", d1));
	m_SpriteResourceMap.insert(std::make_pair("forest_temperate_deep", d2));
	m_SpriteResourceMap.insert(std::make_pair("forest_temperate_scarce", d3));
	m_SpriteResourceMap.insert(std::make_pair("forest_savannah_normal", d4));
	m_SpriteResourceMap.insert(std::make_pair("forest_tundra_normal", d5));
	m_SpriteResourceMap.insert(std::make_pair("forest_tundra_deep", d6));
	m_SpriteResourceMap.insert(std::make_pair("forest_tundra_scarce", d7));
	m_SpriteResourceMap.insert(std::make_pair("highmountain", d8));
	m_SpriteResourceMap.insert(std::make_pair("hills", d9));
	m_SpriteResourceMap.insert(std::make_pair("ice", d10));
	m_SpriteResourceMap.insert(std::make_pair("forest_jungle_normal", d11));
	m_SpriteResourceMap.insert(std::make_pair("sand", d12));
	m_SpriteResourceMap.insert(std::make_pair("savannah", d13));
	m_SpriteResourceMap.insert(std::make_pair("snow", d14));
	m_SpriteResourceMap.insert(std::make_pair("temperate", d15));
	m_SpriteResourceMap.insert(std::make_pair("tundra", d16));
	m_SpriteResourceMap.insert(std::make_pair("water_deep", d17));
	m_SpriteResourceMap.insert(std::make_pair("water_shallow", d18));
	m_SpriteResourceMap.insert(std::make_pair("forest_temperate_dying", d19));
	m_SpriteResourceMap.insert(std::make_pair("forest_tundra_dying", d20));


	m_SpriteResourceMap.insert(std::make_pair("forest_savannah_scarce", d21));
	m_SpriteResourceMap.insert(std::make_pair("forest_savannah_deep", d22));
	m_SpriteResourceMap.insert(std::make_pair("forest_savannah_dying", d23));

	m_SpriteResourceMap.insert(std::make_pair("forest_jungle_scarce", d24));
	m_SpriteResourceMap.insert(std::make_pair("forest_jungle_deep", d25));
	m_SpriteResourceMap.insert(std::make_pair("forest_jungle_dying", d26));




	// Map colored cells.
	m_SpriteResourceMap.insert(std::make_pair("map_cell_black", dc1));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_blue", dc2));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_brown", dc3));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_green", dc4));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_magenta", dc5));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_orange", dc6));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_red", dc7));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_yellow", dc8));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_white", dc9));




	// Load cities
	Sprite* city1 = new Sprite("assets/city/orc/city_orc_huge.png");
	Sprite* city2 = new Sprite("assets/city/human/city_human_huge.png");
	Sprite* city3 = new Sprite("assets/city/human/city_human_small.png");
	Sprite* city4 = new Sprite("assets/city/highelf/city_highelf_small.png");
	Sprite* city5 = new Sprite("assets/city/orc/city_orc_small.png");
	Sprite* city6 = new Sprite("assets/city/orc/city_orc_normal.png");
	Sprite* city7 = new Sprite("assets/city/orc/city_orc_big.png");
	Sprite* city8 = new Sprite("assets/city/human/city_human_normal.png");
	Sprite* city9 = new Sprite("assets/city/human/city_human_big.png");

	
	m_SpriteStorage.push_back(city1);
	m_SpriteStorage.push_back(city2);
	m_SpriteStorage.push_back(city3);
	m_SpriteStorage.push_back(city4);
	m_SpriteStorage.push_back(city5);
	m_SpriteStorage.push_back(city6);
	m_SpriteStorage.push_back(city7);
	m_SpriteStorage.push_back(city8);
	m_SpriteStorage.push_back(city9);


	Decal* dcity1 = new Decal(city1);
	Decal* dcity2 = new Decal(city2);
	Decal* dcity3 = new Decal(city3);
	Decal* dcity4 = new Decal(city4);
	Decal* dcity5 = new Decal(city5);
	Decal* dcity6 = new Decal(city6);
	Decal* dcity7 = new Decal(city7);
	Decal* dcity8 = new Decal(city8);
	Decal* dcity9 = new Decal(city9);


	m_SpriteResourceMap.insert(std::make_pair("city_orc_huge", dcity1));
	m_SpriteResourceMap.insert(std::make_pair("city_human_huge", dcity2));
	m_SpriteResourceMap.insert(std::make_pair("city_human_small", dcity3));
	m_SpriteResourceMap.insert(std::make_pair("city_highelf_small", dcity4));
	m_SpriteResourceMap.insert(std::make_pair("city_orc_small", dcity5));
	m_SpriteResourceMap.insert(std::make_pair("city_orc_normal", dcity6));
	m_SpriteResourceMap.insert(std::make_pair("city_orc_big", dcity7));
	m_SpriteResourceMap.insert(std::make_pair("city_human_normal", dcity8));
	m_SpriteResourceMap.insert(std::make_pair("city_human_big", dcity9));


	// Forts
	Sprite* fort1 = new Sprite("assets/fort/human/fort_human_small.png");

	m_SpriteStorage.push_back(fort1);

	Decal* dfort1 = new Decal(fort1);

	m_SpriteResourceMap.insert(std::make_pair("fort_human_small", dfort1));



	// Cityview sprites
	/*
	* NOTE:
	* 
	* Load city view sprites like this...
	* 
	Sprite* cityview1 = new Sprite("assets/city/human/city_human_normal_cityview.jpg");

	Decal* dcityview1 = new Decal(cityview1);

	m_SpriteResourceMap.insert(std::make_pair("city_human_normal_cityview", dcityview1));
	*/

}


void Game::_initializeMap() {

	m_WorldMap = WorldMap::Get();
	WorldMapDrawingOptions* mapOpt = new WorldMapDrawingOptions(19, 19);
	
	m_WorldMap->SetMapOptions(mapOpt);
}


void Game::_initialize() {

	_loadSpriteResources();
	_initializeMap();

}


bool Game::OnUserCreate() {

	_initialize();
	_initializeMapTileCellCoords();

	m_TimeCounter = new TimeCounter();

	Camera* cam = new Camera(this, 0, 0);
	m_Renderer = new Renderer(this, cam);

	m_Renderer->m_Layer1 = CreateLayer();
	m_Renderer->m_Layer2 = CreateLayer();
	m_Renderer->m_Layer3 = CreateLayer();
	m_Renderer->m_Layer4 = CreateLayer();


	EntitiesStorage* storage = EntitiesStorage::Get();


	/*
	Mountains* m = new Mountains("highmountain", "layer2", 128, 128);
	
	Hills* h = new Hills("hills", "layer2", 256, 128);


	EntitiesStorage* storage = EntitiesStorage::Get();
	
	storage->AddGameEntitie(m);
	storage->AddGameEntitie(h);
	*/


	/*
	// Create some forests for testing.
	Forest* f, * f2, * f3;

	f = MakeNewForest("forest_temperate_deep", 3, 3);
	f2 = MakeNewForest("forest_temperate_deep", 4, 4);
	f3 = MakeNewForest("forest_temperate_deep", 5, 5);
	

	EntitiesStorage* storage = EntitiesStorage::Get();
	storage->AddGameEntitie(f);
	storage->AddGameEntitie(f2);
	storage->AddGameEntitie(f3);


	// Ressources are just a sprite on the map.
	MapRessource* r1 = new MapRessource("Bear", "ressource_map_bear", 384, 128);
	MapRessource* r2 = new MapRessource("Raptor", "ressource_map_raptor", 128, 384);
	MapRessource* r3 = new MapRessource("Horse", "ressource_map_horse", 128, 0);
	MapRessource* r4 = new MapRessource("Boar", "ressource_map_boar", 384, 128);
	MapRessource* r5 = new MapRessource("Guar", "ressource_map_guar", 512, 384);
	MapRessource* r6 = new MapRessource("Deer", "ressource_map_deer", 512, 128);



	r1->MapRessourceYield("Meat", 3);
	r1->MapRessourceYield("Hide", 5);
	r2->MapRessourceYield("Meat", 3);
	r2->MapRessourceYield("Hide", 5);
	r3->MapRessourceYield("Meat", 3);
	r3->MapRessourceYield("Hide", 5);


	storage->AddGameEntitie(r1);
	storage->AddGameEntitie(r2);
	storage->AddGameEntitie(r3);
	storage->AddGameEntitie(r4);
	storage->AddGameEntitie(r5);
	storage->AddGameEntitie(r6);
	*/	


	// Testing creation of player.
	Player* player = new Player("Bogdan", "blue");
	Player* player2 = new Player("AI", "red");
	storage->AddPlayer(player);
	storage->AddPlayer(player2);


	City* city2 = MakeNewCity(true, "Stormhaven", CMPEntityRace::Race::RACE_HUMAN, player, 5, 3, 3);
	City* city3 = MakeNewCity(true, "Under Stormhaven", CMPEntityRace::Race::RACE_ORC, player2, 8, 4, 3);
	//City* city4 = MakeNewCity(true, "Faerograd", CMPEntityRace::Race::RACE_HUMAN, player, 13, 6, 32);

	//City *city = MakeNewCity(true, "Gnarmol", CMPEntityRace::Race::RACE_ORC, player2, 6, 12, 32);
	//City* city5 = MakeNewCity(true, "Gundrassil", CMPEntityRace::Race::RACE_HIGHELF, player2, 15, 2, 5);


	storage->AddGameEntitie(city2);
	storage->AddGameEntitie(city3);
	//storage->AddGameEntitie(city4);

	//storage->AddGameEntitie(city);
	//storage->AddGameEntitie(city5);


	// TimeCounter
	m_TimeCounter->SetTimerForSeconds(1);
	m_TimeCounter->Start();

	return true;
}


bool Game::OnUserUpdate(float fElapsedTime) {


	if (m_TimeModeTurnBased == false) {
		
		if (m_TimeCounter->TimeOut()) {
			AdvanceOneTurn();
		}
	}


	// Update Entities MapCell
	_updateLocalMapTileCellCoords();


	// Do we need this every loop? The gameworld cells are to be defined once,
	// and always updated for entities which move, like units...
	//_updateEntitiesMapTileCoords(); // This will be very inefficient for looping every turn.

	// Input handling.
	m_Renderer->m_MainCam->m_CamInput->HandleKeyboard(m_Renderer->m_MainCam);
	m_Renderer->m_MainCam->m_CamInput->HandleMouse(m_Renderer->m_MainCam);


	m_Renderer->Render();


	return true;
}

void Renderer::Render() {
	switch (m_RenderMode) {
	case RenderMode::RENDERMODE_CITYVIEW:

		// Layered rendering.
		RenderCityLayer1();  // 
		RenderCityLayer2();  // 
		RenderCityLayer3();  // 
		RenderCityLayer4();  // 
		RenderCityLayer0();  // 

		break;
	case RenderMode::RENDERMODE_MAPVIEW:

		// Layered rendering.
		Render2Layer1();  // units layer.
		Render2Layer2();  // buildings, cities...
		Render2Layer3();  // terrain, hills ...
		Render2Layer4();  // ground maptiles
		RenderLayer0();  // effects, general things...

		if (m_Game->m_DebugDraw) m_Game->DebugDrawStats();

		break;
	default:
		break;
	}
}


void Renderer::RenderCityLayer0() {

	m_Game->Clear(olc::BLANK);



}


void Renderer::RenderCityLayer1() {

	m_Game->SetDrawTarget(m_Layer1);
	m_Game->Clear(olc::BLANK);





	m_Game->EnableLayer(m_Layer1, true);
	m_Game->SetDrawTarget(nullptr);
}


void Renderer::RenderCityLayer2() {

	m_Game->SetDrawTarget(m_Layer2);
	m_Game->Clear(olc::BLANK);


	m_Game->EnableLayer(m_Layer2, true);
	m_Game->SetDrawTarget(nullptr);
}


void Renderer::RenderCityLayer3() {

	m_Game->SetDrawTarget(m_Layer3);
	m_Game->Clear(olc::BLANK);

	using namespace olc;




	m_Game->EnableLayer(m_Layer3, true);
	m_Game->SetDrawTarget(nullptr);
}


void Renderer::RenderCityLayer4() {

	m_Game->SetDrawTarget(m_Layer4);
	m_Game->Clear(olc::BLANK);





	m_Game->EnableLayer(m_Layer4, true);
	m_Game->SetDrawTarget(nullptr);
}






void Game::DebugDrawStats() {

	if (!m_DebugDraw) return;

	if (!m_DebugDrawGeneralOptions) {

		std::string turncount = "Turn " + std::to_string(m_TurnCount);
		DrawString(olc::vi2d(2, 10), turncount, olc::BLACK, 1.0f);

		std::string political_map, political_map_on_off;
		political_map_on_off = (m_PoliticalMap == true) ? "On" : "Off";
		political_map = "Political Map ( M ): " + political_map_on_off;
		DrawString(olc::vi2d(2, 20), political_map, olc::BLACK, 1.0f);


	}






	if (m_DebugDrawGeneralOptions) {

		std::string s2 = "Camera Position " + std::to_string(g_vi2dCameraPosition.x) + " : " + std::to_string(g_vi2dCameraPosition.y);
		DrawString(olc::vi2d(2, 10), s2, olc::RED, 2.0f);

		std::string turncount = "Turn " + std::to_string(m_TurnCount);
		DrawString(olc::vi2d(2, 30), turncount, olc::RED, 2.0f);

		std::string on_off = (m_DebugDrawGrid == true) ? "On" : "Off";
		std::string debuggrid = "Grid (Ctrl + G): " + on_off;
		DrawString(olc::vi2d(2, 50), debuggrid, olc::RED, 2.0f);

		std::string maptile_info = (m_DebugDrawMapTileInfo == true) ? "On" : "Off";
		std::string maptile_info_2 = "Maptile Info (Ctrl + M): " + maptile_info;
		DrawString(olc::vi2d(2, 70), maptile_info_2, olc::RED, 2.0f);

		std::string forest_info = (m_DebugDrawForestInfo == true) ? "On" : "Off";
		std::string forest_info_2 = "Forest Info (Ctrl + F): " + forest_info;
		DrawString(olc::vi2d(2, 90), forest_info_2, olc::RED, 2.0f);

		/*
		std::string regions = (m_DebugDrawRegions == true) ? "On" : "Off";
		std::string regions_info = "Regions Info (Ctrl + R): " + regions;
		DrawString(olc::vi2d(2, 110), regions_info, olc::RED, 2.0f);
		*/

		std::string timemode = (m_TimeModeTurnBased == true) ? "Turn-Based" : "Real-Time";
		std::string timemode_info = "Timemode (Ctrl + T): " + timemode;
		DrawString(olc::vi2d(2, 110), timemode_info, olc::RED, 2.0f);
	}

	if (m_DebugDrawRegions) {

		MapTileRegion* region = nullptr;

		std::vector< GameEntity* > vec = *EntitiesStorage::Get()->GetMapTileRegions();
		m_DebugDrawRegionsCount =  std::to_string(vec.size());

		std::string regions_count = "Regions Count: " + m_DebugDrawRegionsCount;
		DrawString(olc::vi2d(2, 130), regions_count, olc::RED, 2.0f);

	}


	if (m_DebugDrawMapTileInfo) {

		// Draw each maptiles mapcell with position
		std::string s3, s4, tilepos, tilepos_2;
		for (auto it : *EntitiesStorage::Get()->GetMapTilesStorage()) {


			if (it->m_TransformCmp->m_Cell[0] > VISIBLE_MAP_WIDTH ||
				it->m_TransformCmp->m_Cell[1] > VISIBLE_MAP_HEIGHT) continue;


			// Camera dependent Cell 
			s3 = std::to_string(it->m_TransformCmp->m_Cell[0]) + " : " + std::to_string(it->m_TransformCmp->m_Cell[1]);
			DrawString(olc::vi2d(it->m_TransformCmp->m_PosX, it->m_TransformCmp->m_PosY), s3, olc::RED, 1.0f);

			// Gameworld Cell
			s4 = std::to_string(it->m_TransformCmp->m_GameWorldSpaceCell[0]) + " : " + std::to_string(it->m_TransformCmp->m_GameWorldSpaceCell[1]);
			DrawString(olc::vi2d(it->m_TransformCmp->m_PosX, it->m_TransformCmp->m_PosY + 10), s4, olc::DARK_RED, 1.0f);


			tilepos = "X: " + std::to_string(it->m_TransformCmp->m_PosX);
			DrawString(olc::vi2d(it->m_TransformCmp->m_PosX, it->m_TransformCmp->m_PosY + 20), tilepos, olc::BLACK, 1.0f);


			/*
			tiletype = MapTileTypeToString(reinterpret_cast<MapTile*>(it));
			DrawString(olc::vi2d(it->m_TransformCmp->m_PosX, it->m_TransformCmp->m_PosY + 30), tiletype, olc::RED, 1.0f);
			*/
			tilepos_2 = "Y: " + std::to_string(it->m_TransformCmp->m_PosY);
			DrawString(olc::vi2d(it->m_TransformCmp->m_PosX, it->m_TransformCmp->m_PosY + 30), tilepos_2, olc::BLACK, 1.0f);

		}

	}


	if (m_DebugDrawForestInfo) {

		std::string forestcount = "Forests " + std::to_string(GetTotalForestsCount());
		DrawString(olc::vi2d(2, 50), forestcount, olc::RED, 2.0f);

		// DrawForests and its Lifetime
		std::string s5, s6, s7, foresttype, cell, pos, forestclass, hasAI;
		std::vector< GameEntity* > vec = GetForestEntities();
		Forest* f = nullptr;
		for (auto it = vec.begin(); it != vec.end(); ++it) {

			f = reinterpret_cast<Forest*>(*it);

			switch (f->m_ForestType) {
			case Forest::ForestType::FOREST_NORMAL:
				foresttype = "NORMAL";
				break;
			case Forest::ForestType::FOREST_DYING:
				foresttype = "DYING";
				break;
			case Forest::ForestType::FOREST_SCARCE:
				foresttype = "SCARCE";
				break;
			case Forest::ForestType::FOREST_DEEP:
				foresttype = "DEEP";
				break;
			default:
				break;
			}


			switch (f->m_ForestClass) {
			case Forest::ForestClass::FOREST_CLASS_TUNDRA:
				forestclass = "CLASS_TUNDRA";
				break;
			case Forest::ForestClass::FOREST_CLASS_JUNGLE:
				forestclass = "CLASS_JUNGLE";
				break;
			case Forest::ForestClass::FOREST_CLASS_TEMPERATE:
				forestclass = "CLASS_TEMPERATE";
				break;
			case Forest::ForestClass::FOREST_CLASS_SAVANNAH:
				forestclass = "CLASS_SAVANNAH";
				break;
			default:
				forestclass = "CLASS_INVALID";
				break;
			}


			s5 = "LifeT.: " + std::to_string(f->m_ForestLifeTimeNow);
			s6 = " MaxLifeT.: " + std::to_string(f->m_ForestLifetime);
			s7 = " Type: " + foresttype;
			DrawString(olc::vi2d(f->m_TransformCmp->m_PosX, f->m_TransformCmp->m_PosY + 30), s5, olc::CYAN, 1);
			DrawString(olc::vi2d(f->m_TransformCmp->m_PosX, f->m_TransformCmp->m_PosY + 40), s6, olc::CYAN, 1);
			DrawString(olc::vi2d(f->m_TransformCmp->m_PosX, f->m_TransformCmp->m_PosY + 50), s7, olc::CYAN, 1);

			pos = "X: " + std::to_string(f->m_TransformCmp->m_PosX) + " Y: " + std::to_string(f->m_TransformCmp->m_PosY);
			cell = "(" + std::to_string(f->m_TransformCmp->m_GameWorldSpaceCell[0]) + " : " + std::to_string(f->m_TransformCmp->m_GameWorldSpaceCell[1]) + ")";
			DrawString(olc::vi2d(f->m_TransformCmp->m_PosX, f->m_TransformCmp->m_PosY + 60), cell, olc::CYAN, 1);
			DrawString(olc::vi2d(f->m_TransformCmp->m_PosX, f->m_TransformCmp->m_PosY + 70), pos, olc::CYAN, 1);

			DrawString(olc::vi2d(f->m_TransformCmp->m_PosX, f->m_TransformCmp->m_PosY + 80), forestclass, olc::CYAN, 1);


			hasAI = (f->m_AICmp == nullptr) ? "No AI" : "Has AI";
			DrawString(olc::vi2d(f->m_TransformCmp->m_PosX, f->m_TransformCmp->m_PosY + 90), hasAI, olc::CYAN, 1);
		}
	}

}


void Renderer::_drawGrid() {

	using namespace olc;

	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* > vec = *storage->GetMapTilesStorage();
	
	MapTile* maptile = nullptr;
	int startpos[2], endpos[2];

	for (auto it = vec.begin(); it != vec.end(); ++it) {

		maptile = reinterpret_cast<MapTile*>(*it);

		startpos[0] = maptile->m_TransformCmp->m_PosX;
		startpos[1] = maptile->m_TransformCmp->m_PosY;

		endpos[0] = maptile->m_TransformCmp->m_PosX;
		endpos[1] = MAP_SIZE * SPRITES_WIDTH_AND_HEIGHT;

		m_Game->DrawLine(vi2d(startpos[0], startpos[1]), vi2d(endpos[0], endpos[1]), olc::BLACK);



		startpos[0] = maptile->m_TransformCmp->m_PosX;
		startpos[1] = maptile->m_TransformCmp->m_PosY;

		endpos[0] = MAP_SIZE * SPRITES_WIDTH_AND_HEIGHT;
		endpos[1] = maptile->m_TransformCmp->m_PosY;

		m_Game->DrawLine(vi2d(startpos[0], startpos[1]), vi2d(endpos[0], endpos[1]), olc::BLACK);


	}
}



int main()
{
	Game demo;

	if (demo.Construct(1280, 720, 1, 1, false, true, false))
		demo.Start();


	return 0;
}


void Renderer::Render2Layer1() {

	using namespace olc;

	m_Game->SetDrawTarget(m_Layer1);
	m_Game->Clear(olc::BLANK);


	m_Game->EnableLayer(m_Layer1, true);
	m_Game->SetDrawTarget(nullptr);
}

void Renderer::Render2Layer2() {

	using namespace olc;

	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* > vec = *storage->GetMapViewRessources();

	m_Game->SetDrawTarget(m_Layer2);
	m_Game->Clear(olc::BLANK);

	GameEntity* entity = nullptr;

	// First, draw the mapviewressources.
	for (auto it = vec.begin(); it != vec.end(); ++it) {

		entity = reinterpret_cast<MapRessource*>(*it);

		// Do not draw tiles we do not see.
		if (entity->m_TransformCmp->m_Cell[0] > VISIBLE_MAP_WIDTH ||
			entity->m_TransformCmp->m_Cell[1] > VISIBLE_MAP_HEIGHT) continue;

		// Draw appropriate loaded sprite on position specified.
		m_Game->DrawDecal(vi2d(entity->m_TransformCmp->m_PosX, entity->m_TransformCmp->m_PosY),
			m_Game->m_SpriteResourceMap.at(entity->m_GraphicsCmp->m_SpriteName));

	}


	// Then, we can draw improvements, roads, cities ...
	// For this, we iterate through a specially define vector and draw everything like above in
	// the correct local order...
	// ...

	//Secondly, draw cities.
	vec = *storage->GetCitiesVec();

	City* city = nullptr;
	MapTileRegion* region = nullptr;

	for (auto it = vec.begin(); it != vec.end(); ++it) {

		city = reinterpret_cast<City*>(*it);

		// Do not draw tiles we do not see.
		if (city->m_TransformCmp->m_Cell[0] > VISIBLE_MAP_WIDTH ||
			city->m_TransformCmp->m_Cell[1] > VISIBLE_MAP_HEIGHT) continue;



		// First, we draw political region tiles.
		// Draw political map related borders.
		if (m_Game->m_PoliticalMap) {

			// Test, draw region around city.
			for (auto it = city->m_ClaimedRegions.begin(); it != city->m_ClaimedRegions.end(); ++it) {

				region = *it;

				_drawMapTileRegionRect(region);
			}

		}


		// After that we draw city. Thus the city will be drawn oer the regiontiles...
		// Draw appropriate loaded sprite on position specified.
		m_Game->DrawDecal(vi2d(city->m_TransformCmp->m_PosX, city->m_TransformCmp->m_PosY),
			m_Game->m_SpriteResourceMap.at(city->GetCurrentCitySprite()));

		std::string s = city->m_CityName + ". Size " + std::to_string(city->m_CitySize);
		m_Game->DrawString(vi2d(city->m_TransformCmp->m_PosX, city->m_TransformCmp->m_PosY),
			s, olc::BLACK);


	}



	// Continue rendering political map related borders. Here, city borders.
	if (m_Game->m_PoliticalMap) {
			
		std::vector<GameEntity*> vec_2 = *EntitiesStorage::Get()->GetCitiesVec();
		City* c = nullptr;
		MapTile* tile = nullptr;

		for (auto it = vec_2.begin(); it != vec_2.end(); ++it) {

			c = reinterpret_cast<City*>(*it);

			for (auto iter = c->m_MapTileBorderDirectionMap.begin(); iter != c->m_MapTileBorderDirectionMap.end(); ++iter) {

				tile = iter->first;

				// Do not draw tiles we do not see.
				if (tile->m_TransformCmp->m_Cell[0] > VISIBLE_MAP_WIDTH ||
					tile->m_TransformCmp->m_Cell[1] > VISIBLE_MAP_HEIGHT) continue;

				// Draw appropriate loaded sprite on position specified.
				m_Game->DrawDecal(vi2d(tile->m_TransformCmp->m_PosX, tile->m_TransformCmp->m_PosY),
					m_Game->m_SpriteResourceMap.at(c->m_MapTileBorderDirectionMap.at(tile)), vf2d(1.0f, 1.0f),
					m_Game->MakeOlcColorFromCityBorderColor(c->m_CityBorderColor));

			}

		}

	}


	m_Game->EnableLayer(m_Layer2, true);
	m_Game->SetDrawTarget(nullptr);
}



olc::Pixel Game::MakeOlcColorFromCityBorderColor(City::CityBorderColor color) {

	switch (color) {
	case City::CityBorderColor::CITY_BORDERCOLOR_BLACK:
		return olc::Pixel(0, 0, 0, 255);
		break;
	case City::CityBorderColor::CITY_BORDERCOLOR_RED:
		return olc::Pixel(178, 0, 0, 255);
		break;
	case City::CityBorderColor::CITY_BORDERCOLOR_BLUE:
		return olc::Pixel(0, 17, 255, 255);
		break;
	case City::CityBorderColor::CITY_BORDERCOLOR_GREEN:
		return olc::Pixel(0, 102, 40, 255);

		break;
	case City::CityBorderColor::CITY_BORDERCOLOR_YELLOW:
		return olc::Pixel(252, 200, 12, 255);

		break;
	case City::CityBorderColor::CITY_BORDERCOLOR_MAGENTA:
		return olc::Pixel(65, 0, 178, 255);

		break;
	case City::CityBorderColor::CITY_BORDERCOLOR_ORANGE:
		return olc::Pixel(252, 84, 12, 255);

		break;
	case City::CityBorderColor::CITY_BORDERCOLOR_BROWN:
		return olc::Pixel(101, 67, 33, 255);
		break;
	default:
		return olc::Pixel(255, 255, 255, 255);
		break;
	}
}


void Renderer::_drawMapTileRegionRect(MapTileRegion* region) {

	using namespace olc;
	MapTile* maptile = nullptr;

	for (auto it = region->m_MapTileRegionTiles.begin(); it != region->m_MapTileRegionTiles.end(); ++it) {

		maptile = *it;

		// Do not draw tiles we do not see.
		if (maptile->m_TransformCmp->m_Cell[0] > VISIBLE_MAP_WIDTH ||
			maptile->m_TransformCmp->m_Cell[1] > VISIBLE_MAP_HEIGHT) continue;

		// Check whether the region has a spriteressource set.
		if (COMPARE_STRINGS(region->m_GraphicsCmp->m_SpriteName, "NULL") == 0) continue;

		else {
			// We want to draw the rectangles with specific to the city color.
			m_Game->DrawDecal(vi2d(maptile->m_TransformCmp->m_PosX, maptile->m_TransformCmp->m_PosY),
				m_Game->m_SpriteResourceMap.at(region->m_GraphicsCmp->m_SpriteName));
		}
	}
}


void Renderer::Render2Layer3() {

	using namespace olc;

	EntitiesStorage* storage = EntitiesStorage::Get();
	/*
	std::vector< GameEntity* > vec = *storage->GetMapTilesStorage();

	MapTile* maptile = nullptr;
	GameEntity* entity = nullptr;
	Forest* f = nullptr;


	m_Game->SetDrawTarget(m_Layer3);
	m_Game->Clear(olc::BLANK);

	// Render Forests, Hills, etc.
	for (auto it = vec.begin(); it != vec.end(); ++it) {

		maptile = reinterpret_cast<MapTile*>(*it);

		// Do not draw tiles we do not see.
		if (maptile->m_TransformCmp->m_Cell[0] > VISIBLE_MAP_WIDTH ||
			maptile->m_TransformCmp->m_Cell[1] > VISIBLE_MAP_HEIGHT) continue;


		if (maptile->m_MapTileEntities->size() > 0) {


			for (auto iter = maptile->m_MapTileEntities->begin(); iter != maptile->m_MapTileEntities->end(); ++iter) {
						
				//entity = *iter;
				f = reinterpret_cast<Forest*>(*it);

				// Draw appropriate loaded sprite on position specified.
				m_Game->DrawDecal(vi2d(f->m_TransformCmp->m_PosX, f->m_TransformCmp->m_PosY),
										m_Game->m_SpriteResourceMap.at(f->m_GraphicsCmp->m_SpriteName));

			}

		}
	}
	*/

	m_Game->SetDrawTarget(m_Layer3);
	m_Game->Clear(olc::BLANK);

	MapTile* maptile = nullptr;
	Forest* forest = nullptr;
	GameEntity* entity = nullptr;



	// Render Forests
	std::vector< GameEntity* > vec = *storage->GetMapTilesStorage();

	for (auto it = vec.begin(); it != vec.end(); ++it) {

		maptile = reinterpret_cast<MapTile*>(*it);

		// Do not draw tiles we do not see.
		if (maptile->m_TransformCmp->m_Cell[0] > VISIBLE_MAP_WIDTH ||
			maptile->m_TransformCmp->m_Cell[1] > VISIBLE_MAP_HEIGHT) continue;


		if (maptile->m_MapTileEntities->size() > 0) {

			for (auto iter = maptile->m_MapTileEntities->begin(); iter != maptile->m_MapTileEntities->end(); ++iter) {

				entity = *iter;

				if (COMPARE_STRINGS(entity->m_IDCmp->m_DynamicTypeName, "Forest") == 0) {

					forest = reinterpret_cast<Forest*>(*iter);



					// Draw appropriate loaded sprite on position specified.
					m_Game->DrawDecal(vi2d(forest->m_TransformCmp->m_PosX, forest->m_TransformCmp->m_PosY),
						m_Game->m_SpriteResourceMap.at(forest->m_GraphicsCmp->m_SpriteName));
				}

			}

		}


	}

	// Render Mountains and Hills
	vec = *storage->GetHillsMountains();

	Hills* hills = nullptr;
	Mountains* mountains = nullptr;

	for (auto it = vec.begin(); it != vec.end(); ++it) {

		entity = *it;

		// Do not draw tiles we do not see.
		if (entity->m_TransformCmp->m_Cell[0] > VISIBLE_MAP_WIDTH ||
			entity->m_TransformCmp->m_Cell[1] > VISIBLE_MAP_HEIGHT) continue;




		if (COMPARE_STRINGS(entity->m_IDCmp->m_DynamicTypeName, "Hills")) {
			hills = reinterpret_cast<Hills*>(*it);
			mountains = nullptr;
		}
		else if (COMPARE_STRINGS(entity->m_IDCmp->m_DynamicTypeName, "Mountains")) {
			mountains = reinterpret_cast<Mountains*>(*it);
			hills = nullptr;
		}


		if (hills) {
			// Draw appropriate loaded sprite on position specified.
			m_Game->DrawDecal(vi2d(hills->m_TransformCmp->m_PosX, hills->m_TransformCmp->m_PosY),
				m_Game->m_SpriteResourceMap.at(hills->m_GraphicsCmp->m_SpriteName));
		}
		else if (mountains) {
			// Draw appropriate loaded sprite on position specified.
			m_Game->DrawDecal(vi2d(mountains->m_TransformCmp->m_PosX, mountains->m_TransformCmp->m_PosY),
				m_Game->m_SpriteResourceMap.at(mountains->m_GraphicsCmp->m_SpriteName));
		}

	}



	
	// Render rivers over other to see them
	River* river = nullptr;
	vec = *storage->GetRiversVec();
	for (auto it = vec.begin(); it != vec.end(); ++it) {

		river = reinterpret_cast<River*>(*it);

		// Do not draw tiles we do not see.
		if (river->m_TransformCmp->m_Cell[0] > VISIBLE_MAP_WIDTH ||
			river->m_TransformCmp->m_Cell[1] > VISIBLE_MAP_HEIGHT) continue;


		// Draw appropriate loaded sprite on position specified.
		m_Game->DrawDecal(vi2d(river->m_TransformCmp->m_PosX, river->m_TransformCmp->m_PosY),
			m_Game->m_SpriteResourceMap.at(river->m_GraphicsCmp->m_SpriteName));

	}



	m_Game->EnableLayer(m_Layer3, true);
	m_Game->SetDrawTarget(nullptr);
}

void Renderer::Render2Layer4() {

	using namespace olc;

	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* > vec = *storage->GetMapTilesStorage();
	MapTile* maptile = nullptr;

	m_Game->SetDrawTarget(m_Layer4);
	m_Game->Clear(olc::BLANK);


	for (auto it = vec.begin(); it != vec.end(); ++it) {

		maptile = reinterpret_cast<MapTile*>(*it);

		// Do not draw tiles we do not see.
		if (maptile->m_TransformCmp->m_Cell[0] > VISIBLE_MAP_WIDTH ||
			maptile->m_TransformCmp->m_Cell[1] > VISIBLE_MAP_HEIGHT) continue;


		// Draw appropriate loaded sprite on position specified.
		m_Game->DrawDecal(vi2d(maptile->m_TransformCmp->m_PosX, maptile->m_TransformCmp->m_PosY),
						  m_Game->m_SpriteResourceMap.at(maptile->m_GraphicsCmp->m_SpriteName));
	}

	m_Game->EnableLayer(m_Layer4, true);
	m_Game->SetDrawTarget(nullptr);
}



void Renderer::RenderLayer0() {

	using namespace olc;

	m_Game->Clear(olc::BLANK);
	
}



void Game::_updateAI2() {

	EntitiesStorage* storage = EntitiesStorage::Get();

	// Get all entities with AI Component.
	std::vector< GameEntity* > vec = *storage->GetAIEntitiesStorage();
	GameEntity* entity = nullptr;
	
	for (auto it = vec.begin(); it != vec.end(); ++it) {


		try {
			using namespace std;

			entity = *it;

			cout << APP_COLOR;
			cout << "Executing state logic for " << entity->m_IDCmp->m_ID << " at position "
				<< entity->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << entity->m_TransformCmp->m_GameWorldSpaceCell[1] << white << endl;

			if (!entity->m_AICmp->TryExecuteStateLogic()) {

					cout << APP_ERROR_COLOR
					 << " was unsuccessfull." << white << endl << endl;

			}
			else {

				cout << APP_SUCCESS_COLOR
					 << " was successfull." << white << endl << endl;
			}
		}
		catch (char* err) {
			continue;
		}

	}
}




void Game::_initializeMapTileCellCoords() {

	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* >* vec = storage->GetMapTilesStorage();

	for (auto& it : *vec) { // Iterate through all entities.

		it->m_TransformCmp->m_GameWorldSpaceCell[0] = (int)it->m_TransformCmp->m_PosX / SPRITES_WIDTH_AND_HEIGHT;
		it->m_TransformCmp->m_GameWorldSpaceCell[1] = (int)it->m_TransformCmp->m_PosY / SPRITES_WIDTH_AND_HEIGHT;

	}
}



void Game::_updateEntitiesMapTileCoords() {

	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* >* vec = storage->GetMapTilesStorage();

	for (auto it : *vec) {

		if (reinterpret_cast<MapTile*>(it)->m_MapTileEntities->size() > 0) {


			for (auto iter : *reinterpret_cast<MapTile*>(it)->m_MapTileEntities) {


				iter->m_TransformCmp->m_GameWorldSpaceCell[0] = it->m_TransformCmp->m_GameWorldSpaceCell[0];
				iter->m_TransformCmp->m_GameWorldSpaceCell[1] = it->m_TransformCmp->m_GameWorldSpaceCell[1];
			}
		}
	}

}



void Game::_updateLocalMapTileCellCoords() {

	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* > vec = *storage->GetMapTilesStorage();

	MapTile* maptile = nullptr;
	GameEntity* entity = nullptr;

	for (auto it = vec.begin(); it != vec.end(); ++it) {

		maptile = reinterpret_cast<MapTile*>(*it);

		
		maptile->m_TransformCmp->m_Cell[0] = ((int)maptile->m_TransformCmp->m_PosX  + 50) / SPRITES_WIDTH_AND_HEIGHT;
		maptile->m_TransformCmp->m_Cell[1] = ((int)maptile->m_TransformCmp->m_PosY + 50) / SPRITES_WIDTH_AND_HEIGHT;

		
		// Update local map coords for entities...
		if (maptile->m_MapTileEntities->size() > 0) {

			for (auto iter = maptile->m_MapTileEntities->begin(); iter != maptile->m_MapTileEntities->end(); ++iter ) {

				entity = *iter;

				entity->m_TransformCmp->m_Cell[0] = maptile->m_TransformCmp->m_Cell[0];
				entity->m_TransformCmp->m_Cell[1] = maptile->m_TransformCmp->m_Cell[1];
			}
		}
		
	}
}




void ForestSearch::executeStateLogic() {

	using namespace std;

	// increase lifetime on update. Counted in gameturns.
	m_ManagedForest->m_ForestLifeTimeNow++;

	// Forest too old, means dies of old age.
	if (m_ManagedForest->m_ForestLifeTimeNow > m_ManagedForest->m_ForestLifetime) {

		m_ManagedForest->m_ForestType = Forest::ForestType::FOREST_INVALID;

		m_ManagedForest->Update();
		return;
	}




	// check for transitions of young and older forests
	if (m_ManagedForest->m_ForestType == Forest::ForestType::FOREST_SCARCE) {


		if (m_ManagedForest->m_ForestLifeTimeNow > 32 * TURN_TIME_MODIFIER) { // scarce --> normal
			
			m_ManagedForest->m_ForestType = Forest::ForestType::FOREST_NORMAL;

			// Update on change.
			m_ManagedForest->Update();
		}
	}
	else {
		if (m_ManagedForest->m_ForestType == Forest::ForestType::FOREST_NORMAL && m_ManagedForest->m_ForestLifeTimeNow > 66 * TURN_TIME_MODIFIER || // normal --> dying
			m_ManagedForest->m_ForestType == Forest::ForestType::FOREST_DEEP && m_ManagedForest->m_ForestLifeTimeNow > 66*2 * TURN_TIME_MODIFIER) { // deep --> dying. This transition takes 2 times longer to fullfill, so the deep forest lives longer.


			if (m_ManagedForest->m_ForestType == Forest::ForestType::FOREST_DEEP) m_ManagedForest->m_ForestLifeTimeNow = 67; // Needed reset to normal value for deep forest to ensure common dying time.
			m_ManagedForest->m_ForestLifetime = 100 * TURN_TIME_MODIFIER;

			m_ManagedForest->m_ForestType = Forest::ForestType::FOREST_DYING;

			// Update on change.
			m_ManagedForest->Update();
		}
	}


	// Make changes dependent on forests position.
	// This logic acts only on normaltype forests.
	if (m_ManagedForest->m_ForestType == Forest::ForestType::FOREST_NORMAL) {

		cout << color(colors::BLUE);
		cout << "_checkForNewForestCreation() for " << m_ManagedForest->m_IDCmp->m_ID << " executing." << white << endl;
		_checkForNewForestCreation(m_ManagedForest);


		bool surrounded = false;
		surrounded = _surroundedByForestNormalOrDeep(m_ManagedForest);

		if (surrounded) {
			m_ManagedForest->m_ForestType = Forest::ForestType::FOREST_DEEP;
			m_ManagedForest->m_ForestLifetime = 200 * TURN_TIME_MODIFIER;

			cout << color(colors::WHITE);
			cout << "_surroundedByForestNormalOrDeep() successfully executed for " << m_ManagedForest->m_IDCmp->m_ID << " at position " << m_ManagedForest->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << m_ManagedForest->m_TransformCmp->m_GameWorldSpaceCell[1] << white << endl;
		}
		else {
			cout << color(colors::WHITE);
			cout << "_surroundedByForestNormalOrDeep() unsuccessfully executed for " << m_ManagedForest->m_IDCmp->m_ID << " at position " << m_ManagedForest->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << m_ManagedForest->m_TransformCmp->m_GameWorldSpaceCell[1] << white << endl;
		

			// Check whether to raise Randomly a deepforest.
			if( RaiseDeepForestRandomly()) {
				m_ManagedForest->m_ForestType = Forest::ForestType::FOREST_DEEP;
				m_ManagedForest->m_ForestLifetime = 200 * TURN_TIME_MODIFIER;

				cout << color(colors::WHITE);
				cout << "Randomly raised DeepForest " << m_ManagedForest->m_IDCmp->m_ID << " at position " << m_ManagedForest->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << m_ManagedForest->m_TransformCmp->m_GameWorldSpaceCell[1] << white << endl;

			}

		}
	}


	// Spawning Random forest around deep forest logic.
	if (m_ManagedForest->m_ForestType == Forest::ForestType::FOREST_DEEP) {

		cout << color(colors::BLUE);
		cout << "_spawnRandomForestAroundDeepOne() for " << m_ManagedForest->m_IDCmp->m_ID << " executed." << white << endl;
		_spawnRandomForestAroundDeepOne(m_ManagedForest);
	}


	// Update on change.
	m_ManagedForest->Update();
}


void Game::AdvanceOneTurn() {

	_updateAI2();

	// Random city spawning.
	//SpawnRandomCity();

	m_TurnCount++;
}



// This function can and must be improved.
bool ForestSearch::_surroundedByForestNormalOrDeep(Forest* forest) {

	int forest_cell[2];
	forest_cell[0] = forest->m_TransformCmp->m_GameWorldSpaceCell[0];
	forest_cell[1] = forest->m_TransformCmp->m_GameWorldSpaceCell[1];

	bool got_forest_up = false, got_forest_down = false, got_forest_left = false, got_forest_right = false;


	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* > vec = *storage->GetAIEntitiesStorage();

	// TODO:
	// Add forests to own vector storage, and iterate through it.


	Forest* other_forest = nullptr;

 	for (auto it = vec.begin(); it != vec.end(); ++it) {

		if (forest == *it) continue;

		other_forest = reinterpret_cast<Forest*>(*it);

		// TODO continue:
		// For now, we make sure to iterate only thorugh forests like this.
		if (!IsSubstringInString("Forest", other_forest->m_IDCmp->m_DynamicTypeName)) continue;


		if (other_forest->m_TransformCmp->m_GameWorldSpaceCell[0] == forest_cell[0] &&
			other_forest->m_TransformCmp->m_GameWorldSpaceCell[1] == forest_cell[1] - 1) { // one tile above our forest.

			if (IsSubstringInString("normal", other_forest->m_GraphicsCmp->m_SpriteName) ||
				IsSubstringInString("deep", other_forest->m_GraphicsCmp->m_SpriteName)) {

				got_forest_up = true;
			}
		}


		if (other_forest->m_TransformCmp->m_GameWorldSpaceCell[0] == forest_cell[0] - 1 &&
			other_forest->m_TransformCmp->m_GameWorldSpaceCell[1] == forest_cell[1]) { // one tile left to our forest.

			if (IsSubstringInString("normal", other_forest->m_GraphicsCmp->m_SpriteName) ||
				IsSubstringInString("deep", other_forest->m_GraphicsCmp->m_SpriteName)) {

				got_forest_left = true;
			}
		}


		if (other_forest->m_TransformCmp->m_GameWorldSpaceCell[0] == forest_cell[0] + 1 &&
			other_forest->m_TransformCmp->m_GameWorldSpaceCell[1] == forest_cell[1]) { // one tile right to our forest.

			if (IsSubstringInString("normal", other_forest->m_GraphicsCmp->m_SpriteName) ||
				IsSubstringInString("deep", other_forest->m_GraphicsCmp->m_SpriteName)) {

				got_forest_right = true;
			}
		}



		if (other_forest->m_TransformCmp->m_GameWorldSpaceCell[0] == forest_cell[0] &&
			other_forest->m_TransformCmp->m_GameWorldSpaceCell[1] == forest_cell[1] + 1) { // one tile down to our forest.

			if (IsSubstringInString("normal", other_forest->m_GraphicsCmp->m_SpriteName) ||
				IsSubstringInString("deep", other_forest->m_GraphicsCmp->m_SpriteName)) {

				got_forest_down = true;
			}
		}

	}

	// Forest is surrounded only if all four are true.
	return(got_forest_down && got_forest_left && got_forest_right && got_forest_up);
}




void ForestSearch::_checkForNewForestCreation(Forest* forest) {

	using namespace std;

	EntitiesStorage* storage = EntitiesStorage::Get();

	int forest_worldcell[2];
	forest_worldcell[0] = forest->m_TransformCmp->m_GameWorldSpaceCell[0];
	forest_worldcell[1] = forest->m_TransformCmp->m_GameWorldSpaceCell[1];

	Forest* other_forest = nullptr;

	// Derive the name and type of new forest.
	std::string forestname;
	if (forest->m_ForestClass == Forest::ForestClass::FOREST_CLASS_TEMPERATE) forestname = "forest_temperate_scarce";
	else if (forest->m_ForestClass == Forest::ForestClass::FOREST_CLASS_TUNDRA) forestname = "forest_tundra_scarce";
	else if (forest->m_ForestClass == Forest::ForestClass::FOREST_CLASS_JUNGLE) forestname = "forest_jungle_scarce";
	else if (forest->m_ForestClass == Forest::ForestClass::FOREST_CLASS_SAVANNAH) forestname = "forest_savannah_scarce";


	/*
	We nee to check exactly 4 maptiles. the upper left, upper right...
	
	1. upper left corner --> -1, -1
	2. upper right corner --> +1, -1
	3. lower left corner --> -1. +1
	4. lower right corner --> +1, +1
	*/

	other_forest = reinterpret_cast<Forest*>(IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(forest_worldcell[0] - 1, forest_worldcell[1] - 1), "Forest"));
	if (other_forest) { // is there forest on upper left..

		// Check first, if the forest has same class as this one, else skip everything.
		// And check whether the maptile is right for this forest to grow.
		if (!forest->HasSameForestClass(other_forest)) return;


		// check for needed type of forest --> forest_normal.
		// We may change this logic later.
		if (IsSubstringInString("normal", other_forest->m_GraphicsCmp->m_SpriteName) ||
			IsSubstringInString("deep", other_forest->m_GraphicsCmp->m_SpriteName)){ // Match! Found forest_normal  or forest_deep on needed position --> create new forest accordingly.

			// Further, we need to be sure the new forest will not be a duplicate...
			if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(forest_worldcell[0], forest_worldcell[1] - 1), "Forest")) { // As forest is upper left, we check the maptile above for creation.


				// Check whether new forest would be out of bound.
				if (IsIndexOutOfBound(forest_worldcell[0], forest_worldcell[1] - 1)) return;
				if (!MapTileAppropriteForForest(GetMapTileAtWorldPosition(forest_worldcell[0], forest_worldcell[1] - 1), forest)) return;


				// Empty tile --> create forest.
				
				// To create a new forest, we place its x and y position accordingly to that of the maptile at it position
				// We have to do this, as the x and y positions are dynamically updated accordingly to camera position.
				// Consider to wrap this functionality for ease of use...
				int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(forest_worldcell[0], forest_worldcell[1] - 1));
				int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(forest_worldcell[0], forest_worldcell[1] - 1));
				

				Forest* f = MakeNewForestAtPos(forestname, xpos, ypos, forest_worldcell[0], forest_worldcell[1] - 1);

				storage->AddGameEntitie(f);

				cout << color(colors::CYAN);
				cout << "New Forest created: CELL ( " << f->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << f->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << f->m_IDCmp->m_ID << white << endl;
			
			}
		}
	}



	other_forest = reinterpret_cast<Forest*>(IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(forest_worldcell[0] + 1, forest_worldcell[1] - 1), "Forest"));
	if (other_forest) { // is there forest on upper right..

		// Check first, if the forest has same class as this one, else skip everything.
		if (!forest->HasSameForestClass(other_forest)) return;

		if (IsSubstringInString("normal", other_forest->m_GraphicsCmp->m_SpriteName) ||
			IsSubstringInString("deep", other_forest->m_GraphicsCmp->m_SpriteName)) {

			
			if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(forest_worldcell[0] + 1, forest_worldcell[1]), "Forest")) {

				// Check whether new forest would be out of bound.
				if (IsIndexOutOfBound(forest_worldcell[0] + 1, forest_worldcell[1])) return;
				if (!MapTileAppropriteForForest(GetMapTileAtWorldPosition(forest_worldcell[0] + 1, forest_worldcell[1]), forest)) return;


				// Empty tile --> create forest.
				int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(forest_worldcell[0] + 1, forest_worldcell[1]));
				int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(forest_worldcell[0], forest_worldcell[1]));

				Forest* f = MakeNewForestAtPos(forestname, xpos, ypos, forest_worldcell[0] + 1, forest_worldcell[1]);

				storage->AddGameEntitie(f);

				cout << color(colors::CYAN);
				cout << "New Forest created: CELL ( " << f->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << f->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << f->m_IDCmp->m_ID << white << endl;
			}

		}
	}


	other_forest = reinterpret_cast<Forest*>(IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(forest_worldcell[0] - 1, forest_worldcell[1] + 1), "Forest"));
	if (other_forest) { // is there forest on down left..

		// Check first, if the forest has same class as this one, else skip everything.
		if (!forest->HasSameForestClass(other_forest)) return;


		if (IsSubstringInString("normal", other_forest->m_GraphicsCmp->m_SpriteName) ||
			IsSubstringInString("deep", other_forest->m_GraphicsCmp->m_SpriteName)) {

			if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(forest_worldcell[0] - 1, forest_worldcell[1]), "Forest")) {


				// Check whether new forest would be out of bound.
				if (IsIndexOutOfBound(forest_worldcell[0] - 1, forest_worldcell[1])) return;
				if (!MapTileAppropriteForForest(GetMapTileAtWorldPosition(forest_worldcell[0] - 1, forest_worldcell[1]), forest)) return;


				// Empty tile --> create forest.
				int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(forest_worldcell[0] - 1, forest_worldcell[1]));
				int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(forest_worldcell[0], forest_worldcell[1]));

				Forest* f = MakeNewForestAtPos(forestname, xpos, ypos, forest_worldcell[0] - 1, forest_worldcell[1]);

				storage->AddGameEntitie(f);

				cout << color(colors::CYAN);
				cout << "New Forest created: CELL ( " << f->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << f->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << f->m_IDCmp->m_ID << white << endl;
			}

		}
	}


	other_forest = reinterpret_cast<Forest*>(IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(forest_worldcell[0] + 1, forest_worldcell[1] + 1), "Forest"));
	if (other_forest) { // is there forest on down right..

		// Check first, if the forest has same class as this one, else skip everything.
		if (!forest->HasSameForestClass(other_forest)) return;


		if (IsSubstringInString("normal", other_forest->m_GraphicsCmp->m_SpriteName) ||
			IsSubstringInString("deep", other_forest->m_GraphicsCmp->m_SpriteName)) {

			if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(forest_worldcell[0], forest_worldcell[1] + 1), "Forest")) {

				// Check whether new forest would be out of bound.
				if (IsIndexOutOfBound(forest_worldcell[0], forest_worldcell[1] + 1)) return;
				if (!MapTileAppropriteForForest(GetMapTileAtWorldPosition(forest_worldcell[0], forest_worldcell[1] + 1), forest)) return;


				// Empty tile --> create forest.
				int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(forest_worldcell[0], forest_worldcell[1]));
				int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(forest_worldcell[0], forest_worldcell[1] + 1));

				Forest* f = MakeNewForestAtPos(forestname, xpos, ypos, forest_worldcell[0], forest_worldcell[1]+ 1);

				storage->AddGameEntitie(f);

				cout << color(colors::CYAN);
				cout << "New Forest created: CELL ( " << f->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << f->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << f->m_IDCmp->m_ID << white << endl;
			}

		}
	}
}


void ForestSearch::_spawnRandomForestAroundDeepOne(Forest* deepForest) {

	using namespace std;
	EntitiesStorage* storage = EntitiesStorage::Get();

	int deepForestCell[2];
	deepForestCell[0] = deepForest->m_TransformCmp->m_GameWorldSpaceCell[0];
	deepForestCell[1] = deepForest->m_TransformCmp->m_GameWorldSpaceCell[1];

	Forest* new_forest = nullptr;

	// Derive the name and type of new forest.
	std::string forestname;
	if (deepForest->m_ForestClass == Forest::ForestClass::FOREST_CLASS_TEMPERATE) forestname = "forest_temperate_scarce";
	else if (deepForest->m_ForestClass == Forest::ForestClass::FOREST_CLASS_TUNDRA) forestname = "forest_tundra_scarce";
	else if (deepForest->m_ForestClass == Forest::ForestClass::FOREST_CLASS_JUNGLE) forestname = "forest_jungle_scarce";
	else if (deepForest->m_ForestClass == Forest::ForestClass::FOREST_CLASS_SAVANNAH) forestname = "forest_savannah_scarce";



	int r = Random() % 10;

	switch (r) {
	case 0:

		// Some cell around Deep forest
		if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1] - 1), "Forest")) {

			// Check whether this new tile is out of map...
			if (IsIndexOutOfBound(deepForestCell[0] - 1, deepForestCell[1] - 1)) break;
			if (!MapTileAppropriteForForest(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1] - 1), deepForest)) return;

			// Empty tile --> create forest.
			int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1] - 1));
			int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1] - 1));

			new_forest = MakeNewForestAtPos(forestname, xpos, ypos, deepForestCell[0] - 1, deepForestCell[1] - 1);

			storage->AddGameEntitie(new_forest);

			cout << color(colors::CYAN);
			cout << "New Forest created around DeepForest: CELL ( " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << new_forest->m_IDCmp->m_ID << white << endl;
		}

		break;
	case 1:
		if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(deepForestCell[0], deepForestCell[1] - 1), "Forest")) {

			// Check whether this new tile is out of map...
			if (IsIndexOutOfBound(deepForestCell[0], deepForestCell[1] - 1)) break;
			if (!MapTileAppropriteForForest(GetMapTileAtWorldPosition(deepForestCell[0], deepForestCell[1] - 1), deepForest)) return;


			// Empty tile --> create forest.
			int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0], deepForestCell[1] - 1));
			int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0], deepForestCell[1] - 1));

			new_forest = MakeNewForestAtPos(forestname, xpos, ypos, deepForestCell[0], deepForestCell[1] - 1);

			storage->AddGameEntitie(new_forest);

			cout << color(colors::CYAN);
			cout << "New Forest created around DeepForest: CELL ( " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << new_forest->m_IDCmp->m_ID << white << endl;
		}


		break;
	case 2:
		if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1] - 1), "Forest")) {

			// Check whether this new tile is out of map...
			if (IsIndexOutOfBound(deepForestCell[0] + 1, deepForestCell[1] - 1)) break;
			if (!MapTileAppropriteForForest(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1] - 1), deepForest)) return;

			// Empty tile --> create forest.
			int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1] - 1));
			int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1] - 1));

			new_forest = MakeNewForestAtPos(forestname, xpos, ypos, deepForestCell[0] + 1, deepForestCell[1] - 1);

			storage->AddGameEntitie(new_forest);

			cout << color(colors::CYAN);
			cout << "New Forest created around DeepForest: CELL ( " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << new_forest->m_IDCmp->m_ID << white << endl;
		}

		break;
	case 3:
		if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1]), "Forest")) {

			// Check whether this new tile is out of map...
			if (IsIndexOutOfBound(deepForestCell[0] - 1, deepForestCell[1])) break;
			if (!MapTileAppropriteForForest(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1]), deepForest)) return;


			// Empty tile --> create forest.
			int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1]));
			int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1]));

			new_forest = MakeNewForestAtPos(forestname, xpos, ypos, deepForestCell[0] - 1, deepForestCell[1]);

			storage->AddGameEntitie(new_forest);

			cout << color(colors::CYAN);
			cout << "New Forest created around DeepForest: CELL ( " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << new_forest->m_IDCmp->m_ID << white << endl;
		}


		break;
	case 4:
		if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1]), "Forest")) {

			// Check whether this new tile is out of map...
			if (IsIndexOutOfBound(deepForestCell[0] + 1, deepForestCell[1])) break;
			if (!MapTileAppropriteForForest(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1]), deepForest)) return;


			// Empty tile --> create forest.
			int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1]));
			int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1]));

			new_forest = MakeNewForestAtPos(forestname, xpos, ypos, deepForestCell[0] + 1, deepForestCell[1]);

			storage->AddGameEntitie(new_forest);

			cout << color(colors::CYAN);
			cout << "New Forest created around DeepForest: CELL ( " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << new_forest->m_IDCmp->m_ID << white << endl;
		}
		break;
	case 5:
		if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1] + 1), "Forest")) {

			// Check whether this new tile is out of map...
			if (IsIndexOutOfBound(deepForestCell[0] - 1, deepForestCell[1] + 1)) break;
			if (!MapTileAppropriteForForest(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1] + 1), deepForest)) return;


			// Empty tile --> create forest.
			int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1] + 1));
			int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1] + 1));

			new_forest = MakeNewForestAtPos(forestname, xpos, ypos, deepForestCell[0] - 1, deepForestCell[1] + 1);

			storage->AddGameEntitie(new_forest);

			cout << color(colors::CYAN);
			cout << "New Forest created around DeepForest: CELL ( " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << new_forest->m_IDCmp->m_ID << white << endl;
		}
		break;
	case 6:
		if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(deepForestCell[0], deepForestCell[1] + 1), "Forest")) {

			// Check whether this new tile is out of map...
			if (IsIndexOutOfBound(deepForestCell[0], deepForestCell[1] + 1)) break;
			if (!MapTileAppropriteForForest(GetMapTileAtWorldPosition(deepForestCell[0], deepForestCell[1] + 1), deepForest)) return;



			// Empty tile --> create forest.
			int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0], deepForestCell[1] + 1));
			int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0], deepForestCell[1] + 1));

			new_forest = MakeNewForestAtPos(forestname, xpos, ypos, deepForestCell[0], deepForestCell[1] + 1);

			storage->AddGameEntitie(new_forest);

			cout << color(colors::CYAN);
			cout << "New Forest created around DeepForest: CELL ( " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << new_forest->m_IDCmp->m_ID << white << endl;
		}

		break;
	case 7:
		if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1] + 1), "Forest")) {

			// Check whether this new tile is out of map...
			if (IsIndexOutOfBound(deepForestCell[0] + 1, deepForestCell[1] + 1)) break;
			if (!MapTileAppropriteForForest(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1] + 1), deepForest)) return;


			int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1] + 1));
			int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1] + 1));

			new_forest = MakeNewForestAtPos(forestname, xpos, ypos, deepForestCell[0] + 1, deepForestCell[1] + 1);

			storage->AddGameEntitie(new_forest);

			cout << color(colors::CYAN);
			cout << "New Forest created around DeepForest: CELL ( " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << new_forest->m_IDCmp->m_ID << white << endl;
		}
		break;
	default:
		return;
	}

}