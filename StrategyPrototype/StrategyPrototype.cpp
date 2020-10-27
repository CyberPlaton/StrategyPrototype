#include"StrategyPrototype.h"

static olc::vf2d g_vi2dCameraPosition = olc::vf2d(0.0f, 0.0f);


int GetXPositionOfMapTile(MapTile* tile) {
	return(tile->m_TransformCmp->m_PosX);
}

int GetYPositionOfMapTile(MapTile* tile) {
	return(tile->m_TransformCmp->m_PosY);
}


bool IsIndexOutOfBound(int x, int y) {

	if (x < 0 || y < 0) return true;

	if (x > MAP_SIZE ||
		y > MAP_SIZE) return true;


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

	int speed = 4;

	if (context->GetKey(olc::Key::SPACE).bReleased) {

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

	if (context->GetKey(olc::Key::TAB).bPressed) {
		context->m_DebugDraw = (context->m_DebugDraw == true) ? false : true;
	}

	if (context->GetKey(olc::Key::W).bHeld) {

		if (g_vi2dCameraPosition.y <= 0) {
			g_vi2dCameraPosition.y = 0; return;
		}


		g_vi2dCameraPosition.y -= 1 * speed;

		for (auto it : *EntitiesStorage::Get()->GetMapTilesStorage()) {

			it->m_TransformCmp->m_PosY += 1* speed;

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

		if (g_vi2dCameraPosition.x  >= MAP_SIZE * SPRITES_WIDTH_AND_HEIGHT) {
			g_vi2dCameraPosition.x = MAP_SIZE * SPRITES_WIDTH_AND_HEIGHT; return;
		}

		g_vi2dCameraPosition.x += 1 * speed;

		for (auto it : *EntitiesStorage::Get()->GetMapTilesStorage() ) {

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


void CMPCameraInput::HandleMouse(Camera* cam) {

}



void Game::_loadSpriteResources() {

	using namespace olc;
	
	// Loading sprites and decals.
	Sprite* s1 = new Sprite("assets/map/forest_normal.png");
	Sprite* s2 = new Sprite("assets/map/forest_deep.png");
	Sprite* s3 = new Sprite("assets/map/forest_scarce.png");
	Sprite* s4 = new Sprite("assets/map/forest_savannah.png");
	Sprite* s5 = new Sprite("assets/map/forest_tundra_norm.png");
	Sprite* s6 = new Sprite("assets/map/forest_tundra_deep.png");
	Sprite* s7 = new Sprite("assets/map/forest_tundra_scarce.png");
	Sprite* s8 = new Sprite("assets/map/highmountain.png");
	Sprite* s9 = new Sprite("assets/map/hills.png");
	Sprite* s10 = new Sprite("assets/map/ice.png");
	Sprite* s11 = new Sprite("assets/map/jungle.png");
	Sprite* s12 = new Sprite("assets/map/sand.png");
	Sprite* s13 = new Sprite("assets/map/savannah.png");
	Sprite* s14 = new Sprite("assets/map/snow.png");
	Sprite* s15 = new Sprite("assets/map/temperate.png");
	Sprite* s16 = new Sprite("assets/map/tundra.png");
	Sprite* s17 = new Sprite("assets/map/water_deep.png");
	Sprite* s18 = new Sprite("assets/map/water_shallow.png");
	Sprite* s19 = new Sprite("assets/map/forest_dying.png");


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



	// Create Decals from sprites.
	m_SpriteResourceMap.insert(std::make_pair("forest_normal", d1));
	m_SpriteResourceMap.insert(std::make_pair("forest_deep", d2));
	m_SpriteResourceMap.insert(std::make_pair("forest_scarce", d3));
	m_SpriteResourceMap.insert(std::make_pair("forest_savannah", d4));
	m_SpriteResourceMap.insert(std::make_pair("forest_tundra_norm", d5));
	m_SpriteResourceMap.insert(std::make_pair("forest_tundra_deep", d6));
	m_SpriteResourceMap.insert(std::make_pair("forest_tundra_scarce", d7));
	m_SpriteResourceMap.insert(std::make_pair("highmountain", d8));
	m_SpriteResourceMap.insert(std::make_pair("hills", d9));
	m_SpriteResourceMap.insert(std::make_pair("ice", d10));
	m_SpriteResourceMap.insert(std::make_pair("jungle", d11));
	m_SpriteResourceMap.insert(std::make_pair("sand", d12));
	m_SpriteResourceMap.insert(std::make_pair("savannah", d13));
	m_SpriteResourceMap.insert(std::make_pair("snow", d14));
	m_SpriteResourceMap.insert(std::make_pair("temperate", d15));
	m_SpriteResourceMap.insert(std::make_pair("tundra", d16));
	m_SpriteResourceMap.insert(std::make_pair("water_deep", d17));
	m_SpriteResourceMap.insert(std::make_pair("water_shallow", d18));
	m_SpriteResourceMap.insert(std::make_pair("forest_dying", d19));


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


	Camera* cam = new Camera(this, 0, 0);
	m_Renderer = new Renderer(this, cam);

	m_Renderer->m_Layer1 = CreateLayer();
	m_Renderer->m_Layer2 = CreateLayer();
	m_Renderer->m_Layer3 = CreateLayer();
	m_Renderer->m_Layer4 = CreateLayer();




	// Create some forests for testing.
	/*
	NOTE:
	If we create a forest, it is meant he is scarce from beginning.
	*/
	int f_cell[2], f2_cell[2], f3_cell[2] , f4_cell[2], f5_cell[2];
	f_cell[0] = 1; f_cell[1] = 1;
	f2_cell[0] = 0; f2_cell[1] = 1;
	f3_cell[0] = 1; f3_cell[1] = 2;
	f4_cell[0] = 1; f4_cell[1] = 0;
	f5_cell[0] = 2; f5_cell[1] = 1;



	Forest* f = new Forest("forest_scarce", "layer3", (f_cell[0]) * SPRITES_WIDTH_AND_HEIGHT,
													  (f_cell[1]) * SPRITES_WIDTH_AND_HEIGHT);
	f->m_TransformCmp->m_GameWorldSpaceCell[0] = f_cell[0];
	f->m_TransformCmp->m_GameWorldSpaceCell[1] = f_cell[1];
	f->m_AICmp->ChangeState(States::STATE_SEARCH);
	f->m_AICmp->MapState("state_search", new ForestSearch(*f->m_AICmp));
	

	Forest* f2 = new Forest("forest_scarce", "layer3", (f2_cell[0]) * SPRITES_WIDTH_AND_HEIGHT,
													   (f2_cell[1]) * SPRITES_WIDTH_AND_HEIGHT);
	f2->m_TransformCmp->m_GameWorldSpaceCell[0] = f2_cell[0];
	f2->m_TransformCmp->m_GameWorldSpaceCell[1] = f2_cell[1];
	f2->m_AICmp->ChangeState(States::STATE_SEARCH);
	f2->m_AICmp->MapState("state_search", new ForestSearch(*f2->m_AICmp));

	

	Forest* f3 = new Forest("forest_scarce", "layer3", (f3_cell[0]) * SPRITES_WIDTH_AND_HEIGHT,
													   (f3_cell[1]) * SPRITES_WIDTH_AND_HEIGHT);
	f3->m_TransformCmp->m_GameWorldSpaceCell[0] = f3_cell[0];
	f3->m_TransformCmp->m_GameWorldSpaceCell[1] = f3_cell[1];
	f3->m_AICmp->ChangeState(States::STATE_SEARCH);
	f3->m_AICmp->MapState("state_search", new ForestSearch(*f3->m_AICmp));



	Forest* f4 = new Forest("forest_deep", "layer3", (f4_cell[0]) * SPRITES_WIDTH_AND_HEIGHT,
		(f4_cell[1]) * SPRITES_WIDTH_AND_HEIGHT);
	f4->m_TransformCmp->m_GameWorldSpaceCell[0] = f4_cell[0];
	f4->m_TransformCmp->m_GameWorldSpaceCell[1] = f4_cell[1];
	f4->m_AICmp->ChangeState(States::STATE_SEARCH);
	f4->m_AICmp->MapState("state_search", new ForestSearch(*f4->m_AICmp));


	Forest* f5 = new Forest("forest_deep", "layer3", (f5_cell[0]) * SPRITES_WIDTH_AND_HEIGHT,
		(f5_cell[1]) * SPRITES_WIDTH_AND_HEIGHT);
	f5->m_TransformCmp->m_GameWorldSpaceCell[0] = f5_cell[0];
	f5->m_TransformCmp->m_GameWorldSpaceCell[1] = f5_cell[1];
	f5->m_AICmp->ChangeState(States::STATE_SEARCH);
	f5->m_AICmp->MapState("state_search", new ForestSearch(*f5->m_AICmp));


	EntitiesStorage* storage = EntitiesStorage::Get();
	storage->AddGameEntitie(f);
	storage->AddGameEntitie(f2);
	storage->AddGameEntitie(f3);
	storage->AddGameEntitie(f4);
	storage->AddGameEntitie(f5);








	return true;
}


bool Game::OnUserUpdate(float fElapsedTime) {


	// Update Entities MapCell
	_updateLocalMapTileCellCoords();
	_updateEntitiesMapTileCoords(); // This will be very inefficient for looping every turn.

	// Input handling.
	m_Renderer->m_MainCam->m_CamInput->HandleKeyboard(m_Renderer->m_MainCam);
	m_Renderer->m_MainCam->m_CamInput->HandleMouse(m_Renderer->m_MainCam);

	// Layered rendering.
	m_Renderer->RenderLayer1();  // units layer.
	m_Renderer->RenderLayer2();  // buildings, cities...
	m_Renderer->Render2Layer3();  // terrain, hills ...
	m_Renderer->Render2Layer4();  // ground maptiles
	m_Renderer->RenderLayer0();  // effects, general things...

	if (m_DebugDraw) DebugDrawStats();

	return true;
}



void Game::DebugDrawStats() {

	std::string s2 = "Camera Position " + std::to_string(g_vi2dCameraPosition.x) + " : " + std::to_string(g_vi2dCameraPosition.y);
	DrawString(olc::vi2d(2, 10), s2, olc::RED, 2.0f);

	std::string turncount = "Turn " + std::to_string(m_TurnCount);
	DrawString(olc::vi2d(2, 30), turncount, olc::RED, 2.0f);

	std::string forestcount = "Forests " + std::to_string(GetTotalForestsCount());
	DrawString(olc::vi2d(2, 60), forestcount, olc::RED, 2.0f);



	// Draw each maptiles mapcell with position
	std::string s3, s4, tilepos;
	for (auto it : *EntitiesStorage::Get()->GetMapTilesStorage()) {


		// Camera dependent Cell 
		s3 = std::to_string(it->m_TransformCmp->m_Cell[0]) + " : " + std::to_string(it->m_TransformCmp->m_Cell[1]);
		DrawString(olc::vi2d(it->m_TransformCmp->m_PosX, it->m_TransformCmp->m_PosY), s3, olc::RED, 1.0f);

		// Gameworld Cell
		s4 = std::to_string(it->m_TransformCmp->m_GameWorldSpaceCell[0]) + " : " + std::to_string(it->m_TransformCmp->m_GameWorldSpaceCell[1]);
		DrawString(olc::vi2d(it->m_TransformCmp->m_PosX, it->m_TransformCmp->m_PosY+20), s4, olc::DARK_RED, 1.0f);


		tilepos = "X: " + std::to_string(it->m_TransformCmp->m_PosX) + " : " + " Y: " + std::to_string(it->m_TransformCmp->m_PosY);
		DrawString(olc::vi2d(it->m_TransformCmp->m_PosX, it->m_TransformCmp->m_PosY + 40), tilepos, olc::DARK_RED, 1.0f);

	}



	// DrawForests and its Lifetime
	std::string s5, s6, s7, foresttype, cell, pos;
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



	}

}


void Game::_drawDebugGrid() {

	using namespace olc;

	int w = ScreenWidth();
	int h = ScreenHeight();


	for (int i = 0; i < w; i += 128) {

		DrawLine(vi2d(i, 0), vi2d(i, h), olc::BLACK);
	}

	for (int j = 0; j < h; j += 128) {

		DrawLine(vi2d(0, j), vi2d(w, j), olc::BLACK);
	}
}



int main()
{
	Game demo;

	if (demo.Construct(968, 720, 1, 1, false, true, false))
		demo.Start();


	return 0;
}



void Renderer::RenderLayer2() {

	using namespace olc;

	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* >* vec = storage->GetStorage();


	m_Game->SetDrawTarget(m_Layer2);
	m_Game->Clear(olc::BLANK);


	for (auto const& it : *vec) {
		if (COMPARE_STRINGS(it->m_GraphicsCmp->m_DrawingLayer, "layer2") == 0) {

			// Draw appropriate loaded sprite on position specified.
			m_Game->DrawDecal(vi2d(it->m_TransformCmp->m_PosX, it->m_TransformCmp->m_PosY),
				m_Game->m_SpriteResourceMap.at(it->m_GraphicsCmp->m_SpriteName));
		}
	}


	m_Game->EnableLayer(m_Layer2, true);
	m_Game->SetDrawTarget(nullptr);

}


void Renderer::RenderLayer1() {

	using namespace olc;

	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* >* vec = storage->GetStorage();


	m_Game->SetDrawTarget(m_Layer1);
	m_Game->Clear(olc::BLANK);


	for (auto const& it : *vec) {
		if (COMPARE_STRINGS(it->m_GraphicsCmp->m_DrawingLayer, "layer1") == 0) {

			// Draw appropriate loaded sprite on position specified.
			m_Game->DrawDecal(vi2d(it->m_TransformCmp->m_PosX, it->m_TransformCmp->m_PosY),
				m_Game->m_SpriteResourceMap.at(it->m_GraphicsCmp->m_SpriteName));
		}
	}

	
#ifdef _DEBUG
	m_Game->DrawGrid();
#endif // _DEBUG
	

	m_Game->EnableLayer(m_Layer1, true);
	m_Game->SetDrawTarget(nullptr);


}


void Renderer::Render2Layer1() {

}

void Renderer::Render2Layer2() {

}

void Renderer::Render2Layer3() {

	using namespace olc;

	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* > vec = *storage->GetMapTilesStorage();

	MapTile* maptile = nullptr;
	GameEntity* entity = nullptr;


	m_Game->SetDrawTarget(m_Layer3);
	m_Game->Clear(olc::BLANK);

	// Render Forests, Hills, etc.
	for (auto it = vec.begin(); it != vec.end(); ++it) {

		maptile = reinterpret_cast<MapTile*>(*it);

		// Do not draw tiles we do not see.
		if (maptile->m_TransformCmp->m_Cell[0] > 4 ||
			maptile->m_TransformCmp->m_Cell[1] > 4) continue;


		if (maptile->m_MapTileEntities->size() > 0) {


			for (auto iter = maptile->m_MapTileEntities->begin(); iter != maptile->m_MapTileEntities->end(); ++iter) {
						
				entity = *iter;

				// Draw appropriate loaded sprite on position specified.
				m_Game->DrawDecal(vi2d(entity->m_TransformCmp->m_PosX, entity->m_TransformCmp->m_PosY),
										m_Game->m_SpriteResourceMap.at(entity->m_GraphicsCmp->m_SpriteName));

			}

		}
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
		if (maptile->m_TransformCmp->m_Cell[0] > 4 ||
			maptile->m_TransformCmp->m_Cell[1] > 4) continue;


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


	for (auto it = vec.begin(); it != vec.end(); ++it) {

		maptile = reinterpret_cast<MapTile*>(*it);

		
		maptile->m_TransformCmp->m_Cell[0] = ((int)maptile->m_TransformCmp->m_PosX + 110) / SPRITES_WIDTH_AND_HEIGHT;
		maptile->m_TransformCmp->m_Cell[1] = ((int)maptile->m_TransformCmp->m_PosY + 110) / SPRITES_WIDTH_AND_HEIGHT;
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


		if (m_ManagedForest->m_ForestLifeTimeNow > 32) { // scarce --> normal
			
			m_ManagedForest->m_ForestType = Forest::ForestType::FOREST_NORMAL;

			// Update on change.
			m_ManagedForest->Update();
		}
	}
	else {
		if (m_ManagedForest->m_ForestType == Forest::ForestType::FOREST_NORMAL && m_ManagedForest->m_ForestLifeTimeNow > 66 || // normal --> dying
			m_ManagedForest->m_ForestType == Forest::ForestType::FOREST_DEEP && m_ManagedForest->m_ForestLifeTimeNow > 66*2) { // deep --> dying. This transition takes 2 times longer to fullfill, so the deep forest lives longer.


			if (m_ManagedForest->m_ForestType == Forest::ForestType::FOREST_DEEP) m_ManagedForest->m_ForestLifeTimeNow = 67; // Needed reset to normal value for deep forest to ensure common dying time.
			m_ManagedForest->m_ForestLifetime = 100;

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


		if (_surroundedByForestNormal(m_ManagedForest)) {
			m_ManagedForest->m_ForestType = Forest::ForestType::FOREST_DEEP;
			m_ManagedForest->m_ForestLifetime = 200;

		
			// Update on change.
			m_ManagedForest->Update();


			cout << color(colors::BLUE);
			cout << "_surroundedByForestNormal() successfully executed for " << m_ManagedForest->m_IDCmp->m_ID << "." << white << endl;
		}
	}


	// Spawning random forest around deep forest logic.
	if (m_ManagedForest->m_ForestType == Forest::ForestType::FOREST_DEEP) {

		cout << color(colors::BLUE);
		cout << "_spawnRandomForestAroundDeepOne() for " << m_ManagedForest->m_IDCmp->m_ID << " executed." << white << endl;
		_spawnRandomForestAroundDeepOne(m_ManagedForest);
	}
}


void Game::AdvanceOneTurn() {

	_updateAI2();



	m_TurnCount++;
}



// This function can and must be improved.
bool ForestSearch::_surroundedByForestNormal(Forest* forest) {

	int forest_cell[2];
	forest_cell[0] = forest->m_TransformCmp->m_GameWorldSpaceCell[0];
	forest_cell[1] = forest->m_TransformCmp->m_GameWorldSpaceCell[1];

	bool got_forest_up = false, got_forest_down = false, got_forest_left = false, got_forest_right = false;


	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* > vec = *storage->GetAIEntitiesStorage();

	// Get Entities that are explicitly forest type and surround given forest.
	std::string substring = "normal"; // "forest_normal" etc.
	Forest* other_forest = nullptr;

	for (auto it = vec.begin(); it != vec.end(); ++it) {

		if (forest == *it) continue;

		other_forest = reinterpret_cast<Forest*>(*it);

		if (other_forest->m_TransformCmp->m_GameWorldSpaceCell[0] == forest_cell[0] &&
			other_forest->m_TransformCmp->m_GameWorldSpaceCell[1] == forest_cell[1] - 1) { // one tile above our forest.

			if (other_forest->m_GraphicsCmp->m_SpriteName.find(substring) != std::string::npos) {

				got_forest_up = true;
			}
		}


		if (other_forest->m_TransformCmp->m_GameWorldSpaceCell[0] == forest_cell[0] - 1 &&
			other_forest->m_TransformCmp->m_GameWorldSpaceCell[1] == forest_cell[1]) { // one tile left to our forest.

			if (other_forest->m_GraphicsCmp->m_SpriteName.find(substring) != std::string::npos) {

				got_forest_left = true;
			}
		}


		if (other_forest->m_TransformCmp->m_GameWorldSpaceCell[0] == forest_cell[0] + 1 &&
			other_forest->m_TransformCmp->m_GameWorldSpaceCell[1] == forest_cell[1]) { // one tile right to our forest.

			if (other_forest->m_GraphicsCmp->m_SpriteName.find(substring) != std::string::npos) {

				got_forest_right = true;
			}
		}



		if (other_forest->m_TransformCmp->m_GameWorldSpaceCell[0] == forest_cell[0] &&
			other_forest->m_TransformCmp->m_GameWorldSpaceCell[1] == forest_cell[1] + 1) { // one tile down to our forest.

			if (other_forest->m_GraphicsCmp->m_SpriteName.find(substring) != std::string::npos) {

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

	/*
	We nee to check exactly 4 maptiles. the upper left, upper right...
	
	1. upper left corner --> -1, -1
	2. upper right corner --> +1, -1
	3. lower left corner --> -1. +1
	4. lower right corner --> +1, +1
	*/

	other_forest = reinterpret_cast<Forest*>(IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(forest_worldcell[0] - 1, forest_worldcell[1] - 1), "Forest"));
	if (other_forest) { // is there forest on upper left..

		// check for needed type of forest --> forest_normal.
		// We may change this logic later.
		if (other_forest->m_GraphicsCmp->m_SpriteName.find("normal") != std::string::npos) { // Match! Found forest_normal on needed position --> create new forest accordingly.

			// Further, we need to be sure the new forest will not be a duplicate...
			if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(forest_worldcell[0], forest_worldcell[1] - 1), "Forest")) { // As forest is upper left, we check the maptile above for creation.


				// Check whether new forest would be out of bound.
				if (IsIndexOutOfBound(forest_worldcell[0], forest_worldcell[1] - 1)) return;

				// Empty tile --> create forest.
				//Forest* f = new Forest("forest_scarce", "layer3", (forest_worldcell[0]) * SPRITES_WIDTH_AND_HEIGHT,
				//												  (forest_worldcell[1] - 1) * SPRITES_WIDTH_AND_HEIGHT);
				
				int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(forest_worldcell[0], forest_worldcell[1] - 1));
				int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(forest_worldcell[0], forest_worldcell[1] - 1));


				Forest* f = new Forest("forest_scarce", "layer3", xpos, ypos);


				f->m_TransformCmp->m_GameWorldSpaceCell[0] = forest_worldcell[0];
				f->m_TransformCmp->m_GameWorldSpaceCell[1] = forest_worldcell[1] - 1;
				f->m_AICmp->ChangeState(States::STATE_SEARCH);
				f->m_AICmp->MapState("state_search", new ForestSearch(*f->m_AICmp));

				storage->AddGameEntitie(f);

				cout << color(colors::CYAN);
				cout << "New Forest created: CELL ( " << f->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << f->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << f->m_IDCmp->m_ID << white << endl;
			
			}
		}
	}



	other_forest = reinterpret_cast<Forest*>(IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(forest_worldcell[0] + 1, forest_worldcell[1] - 1), "Forest"));
	if (other_forest) { // is there forest on upper right..

		if (other_forest->m_GraphicsCmp->m_SpriteName.find("normal") != std::string::npos) {

			
			if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(forest_worldcell[0] + 1, forest_worldcell[1]), "Forest")) {

				// Check whether new forest would be out of bound.
				if (IsIndexOutOfBound(forest_worldcell[0] + 1, forest_worldcell[1])) return;

				// Empty tile --> create forest.
				//Forest* f = new Forest("forest_scarce", "layer3", (forest_worldcell[0] + 1) * SPRITES_WIDTH_AND_HEIGHT,
				//												  (forest_worldcell[1]) * SPRITES_WIDTH_AND_HEIGHT);

				int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(forest_worldcell[0] + 1, forest_worldcell[1]));
				int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(forest_worldcell[0], forest_worldcell[1]));

				Forest* f = new Forest("forest_scarce", "layer3", xpos, ypos);

				f->m_TransformCmp->m_GameWorldSpaceCell[0] = forest_worldcell[0] + 1;
				f->m_TransformCmp->m_GameWorldSpaceCell[1] = forest_worldcell[1];
				f->m_AICmp->ChangeState(States::STATE_SEARCH);
				f->m_AICmp->MapState("state_search", new ForestSearch(*f->m_AICmp));

				storage->AddGameEntitie(f);

				cout << color(colors::CYAN);
				cout << "New Forest created: CELL ( " << f->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << f->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << f->m_IDCmp->m_ID << white << endl;
			}

		}
	}


	other_forest = reinterpret_cast<Forest*>(IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(forest_worldcell[0] - 1, forest_worldcell[1] + 1), "Forest"));
	if (other_forest) { // is there forest on down left..

		if (other_forest->m_GraphicsCmp->m_SpriteName.find("normal") != std::string::npos) {

			if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(forest_worldcell[0] - 1, forest_worldcell[1]), "Forest")) {


				// Check whether new forest would be out of bound.
				if (IsIndexOutOfBound(forest_worldcell[0] - 1, forest_worldcell[1])) return;


				// Empty tile --> create forest.
				//Forest* f = new Forest("forest_scarce", "layer3", (forest_worldcell[0] - 1) * SPRITES_WIDTH_AND_HEIGHT,
				//												  (forest_worldcell[1]) * SPRITES_WIDTH_AND_HEIGHT);

				int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(forest_worldcell[0] - 1, forest_worldcell[1]));
				int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(forest_worldcell[0], forest_worldcell[1]));

				Forest* f = new Forest("forest_scarce", "layer3", xpos, ypos);

				f->m_TransformCmp->m_GameWorldSpaceCell[0] = forest_worldcell[0] - 1;
				f->m_TransformCmp->m_GameWorldSpaceCell[1] = forest_worldcell[1];
				f->m_AICmp->ChangeState(States::STATE_SEARCH);
				f->m_AICmp->MapState("state_search", new ForestSearch(*f->m_AICmp));

				storage->AddGameEntitie(f);

				cout << color(colors::CYAN);
				cout << "New Forest created: CELL ( " << f->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << f->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << f->m_IDCmp->m_ID << white << endl;
			}

		}
	}


	other_forest = reinterpret_cast<Forest*>(IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(forest_worldcell[0] + 1, forest_worldcell[1] + 1), "Forest"));
	if (other_forest) { // is there forest on down right..

		if (other_forest->m_GraphicsCmp->m_SpriteName.find("normal") != std::string::npos) {

			if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(forest_worldcell[0], forest_worldcell[1] + 1), "Forest")) {

				// Check whether new forest would be out of bound.
				if (IsIndexOutOfBound(forest_worldcell[0], forest_worldcell[1] + 1)) return;

				// Empty tile --> create forest.
				//Forest* f = new Forest("forest_scarce", "layer3", (forest_worldcell[0]) * SPRITES_WIDTH_AND_HEIGHT,
				//												  (forest_worldcell[1] + 1) * SPRITES_WIDTH_AND_HEIGHT);

				int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(forest_worldcell[0], forest_worldcell[1]));
				int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(forest_worldcell[0], forest_worldcell[1] + 1));

				Forest* f = new Forest("forest_scarce", "layer3", xpos, ypos);

				f->m_TransformCmp->m_GameWorldSpaceCell[0] = forest_worldcell[0];
				f->m_TransformCmp->m_GameWorldSpaceCell[1] = forest_worldcell[1] + 1;
				f->m_AICmp->ChangeState(States::STATE_SEARCH);
				f->m_AICmp->MapState("state_search", new ForestSearch(*f->m_AICmp));

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

	int r = rand() % 10;

	switch (r) {
	case 0:

		// Some cell around Deep forest
		if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1] - 1), "Forest")) {


			// Check whether this new tile is out of map...
			if (IsIndexOutOfBound(deepForestCell[0] - 1, deepForestCell[1] - 1)) break;

			// Empty tile --> create forest.
			//new_forest = new Forest("forest_scarce", "layer3", (deepForestCell[0] - 1) * SPRITES_WIDTH_AND_HEIGHT,
			//												  (deepForestCell[1] - 1) * SPRITES_WIDTH_AND_HEIGHT);

			int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1] - 1));
			int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1] - 1));

			new_forest = new Forest("forest_scarce", "layer3", xpos, ypos);

			new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] = deepForestCell[0] - 1;
			new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] = deepForestCell[1] - 1;
			new_forest->m_AICmp->ChangeState(States::STATE_SEARCH);
			new_forest->m_AICmp->MapState("state_search", new ForestSearch(*new_forest->m_AICmp));

			storage->AddGameEntitie(new_forest);

			cout << color(colors::CYAN);
			cout << "New Forest created around DeepForest: CELL ( " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << new_forest->m_IDCmp->m_ID << white << endl;
		}

		break;
	case 1:
		if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(deepForestCell[0], deepForestCell[1] - 1), "Forest")) {

			// Check whether this new tile is out of map...
			if (IsIndexOutOfBound(deepForestCell[0], deepForestCell[1] - 1)) break;


			// Empty tile --> create forest.
			//new_forest = new Forest("forest_scarce", "layer3", (deepForestCell[0]) * SPRITES_WIDTH_AND_HEIGHT,
			//												   (deepForestCell[1] - 1) * SPRITES_WIDTH_AND_HEIGHT);

			int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0], deepForestCell[1] - 1));
			int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0], deepForestCell[1] - 1));

			new_forest = new Forest("forest_scarce", "layer3", xpos, ypos);

			new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] = deepForestCell[0];
			new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] = deepForestCell[1] - 1;
			new_forest->m_AICmp->ChangeState(States::STATE_SEARCH);
			new_forest->m_AICmp->MapState("state_search", new ForestSearch(*new_forest->m_AICmp));

			storage->AddGameEntitie(new_forest);

			cout << color(colors::CYAN);
			cout << "New Forest created around DeepForest: CELL ( " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << new_forest->m_IDCmp->m_ID << white << endl;
		}


		break;
	case 2:
		if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1] - 1), "Forest")) {


			// Check whether this new tile is out of map...
			if (IsIndexOutOfBound(deepForestCell[0] + 1, deepForestCell[1] - 1)) break;

			// Empty tile --> create forest.
			//new_forest = new Forest("forest_scarce", "layer3", (deepForestCell[0] + 1) * SPRITES_WIDTH_AND_HEIGHT,
			//													(deepForestCell[1] - 1) * SPRITES_WIDTH_AND_HEIGHT);

			int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1] - 1));
			int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1] - 1));

			new_forest = new Forest("forest_scarce", "layer3", xpos, ypos);

			new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] = deepForestCell[0] + 1;
			new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] = deepForestCell[1] - 1;
			new_forest->m_AICmp->ChangeState(States::STATE_SEARCH);
			new_forest->m_AICmp->MapState("state_search", new ForestSearch(*new_forest->m_AICmp));

			storage->AddGameEntitie(new_forest);

			cout << color(colors::CYAN);
			cout << "New Forest created around DeepForest: CELL ( " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << new_forest->m_IDCmp->m_ID << white << endl;
		}

		break;
	case 3:
		if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1]), "Forest")) {


			// Check whether this new tile is out of map...
			if (IsIndexOutOfBound(deepForestCell[0] - 1, deepForestCell[1])) break;


			// Empty tile --> create forest.
			//new_forest = new Forest("forest_scarce", "layer3", (deepForestCell[0] - 1) * SPRITES_WIDTH_AND_HEIGHT,
			//												   (deepForestCell[1]) * SPRITES_WIDTH_AND_HEIGHT);

			int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1]));
			int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1]));

			new_forest = new Forest("forest_scarce", "layer3", xpos, ypos);

			new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] = deepForestCell[0] - 1;
			new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] = deepForestCell[1];
			new_forest->m_AICmp->ChangeState(States::STATE_SEARCH);
			new_forest->m_AICmp->MapState("state_search", new ForestSearch(*new_forest->m_AICmp));

			storage->AddGameEntitie(new_forest);

			cout << color(colors::CYAN);
			cout << "New Forest created around DeepForest: CELL ( " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << new_forest->m_IDCmp->m_ID << white << endl;
		}


		break;
	case 4:
		if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1]), "Forest")) {

			// Check whether this new tile is out of map...
			if (IsIndexOutOfBound(deepForestCell[0] + 1, deepForestCell[1])) break;


			// Empty tile --> create forest.
			//new_forest = new Forest("forest_scarce", "layer3", (deepForestCell[0] + 1) * SPRITES_WIDTH_AND_HEIGHT,
			//													(deepForestCell[1]) * SPRITES_WIDTH_AND_HEIGHT);

			int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1]));
			int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1]));

			new_forest = new Forest("forest_scarce", "layer3", xpos, ypos);

			new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] = deepForestCell[0] + 1;
			new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] = deepForestCell[1];
			new_forest->m_AICmp->ChangeState(States::STATE_SEARCH);
			new_forest->m_AICmp->MapState("state_search", new ForestSearch(*new_forest->m_AICmp));

			storage->AddGameEntitie(new_forest);

			cout << color(colors::CYAN);
			cout << "New Forest created around DeepForest: CELL ( " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << new_forest->m_IDCmp->m_ID << white << endl;
		}
		break;
	case 5:
		if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1] + 1), "Forest")) {


			// Check whether this new tile is out of map...
			if (IsIndexOutOfBound(deepForestCell[0] - 1, deepForestCell[1] + 1)) break;


			// Empty tile --> create forest.
			//new_forest = new Forest("forest_scarce", "layer3", (deepForestCell[0] - 1) * SPRITES_WIDTH_AND_HEIGHT,
			//													(deepForestCell[1] + 1) * SPRITES_WIDTH_AND_HEIGHT);

			int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1] + 1));
			int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1] + 1));

			new_forest = new Forest("forest_scarce", "layer3", xpos, ypos);

			new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] = deepForestCell[0] - 1;
			new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] = deepForestCell[1] + 1;
			new_forest->m_AICmp->ChangeState(States::STATE_SEARCH);
			new_forest->m_AICmp->MapState("state_search", new ForestSearch(*new_forest->m_AICmp));

			storage->AddGameEntitie(new_forest);

			cout << color(colors::CYAN);
			cout << "New Forest created around DeepForest: CELL ( " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << new_forest->m_IDCmp->m_ID << white << endl;
		}
		break;
	case 6:
		if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(deepForestCell[0], deepForestCell[1] + 1), "Forest")) {


			// Check whether this new tile is out of map...
			if (IsIndexOutOfBound(deepForestCell[0], deepForestCell[1] + 1)) break;

			// Empty tile --> create forest.
			//new_forest = new Forest("forest_scarce", "layer3", (deepForestCell[0]) * SPRITES_WIDTH_AND_HEIGHT,
			//													(deepForestCell[1] + 1) * SPRITES_WIDTH_AND_HEIGHT);


			int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0], deepForestCell[1] + 1));
			int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0], deepForestCell[1] + 1));

			new_forest = new Forest("forest_scarce", "layer3", xpos, ypos);

			new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] = deepForestCell[0];
			new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] = deepForestCell[1] + 1;
			new_forest->m_AICmp->ChangeState(States::STATE_SEARCH);
			new_forest->m_AICmp->MapState("state_search", new ForestSearch(*new_forest->m_AICmp));

			storage->AddGameEntitie(new_forest);

			cout << color(colors::CYAN);
			cout << "New Forest created around DeepForest: CELL ( " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << new_forest->m_IDCmp->m_ID << white << endl;
		}

		break;
	case 7:
		if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1] + 1), "Forest")) {


			// Check whether this new tile is out of map...
			if (IsIndexOutOfBound(deepForestCell[0] + 1, deepForestCell[1] + 1)) break;

			// Empty tile --> create forest.
			//new_forest = new Forest("forest_scarce", "layer3", (deepForestCell[0] + 1) * SPRITES_WIDTH_AND_HEIGHT,
			//													(deepForestCell[1] + 1) * SPRITES_WIDTH_AND_HEIGHT);


			int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1] + 1));
			int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1] + 1));

			new_forest = new Forest("forest_scarce", "layer3", xpos, ypos);

			new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] = deepForestCell[0] + 1;
			new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] = deepForestCell[1] + 1;
			new_forest->m_AICmp->ChangeState(States::STATE_SEARCH);
			new_forest->m_AICmp->MapState("state_search", new ForestSearch(*new_forest->m_AICmp));

			storage->AddGameEntitie(new_forest);

			cout << color(colors::CYAN);
			cout << "New Forest created around DeepForest: CELL ( " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << new_forest->m_IDCmp->m_ID << white << endl;
		}
		break;
	default:
		return;
	}

}