#include"StrategyPrototype.h"

static olc::vf2d g_vi2dCameraPosition = olc::vf2d(0.0f, 0.0f);



void CMPCameraInput::HandleKeyboard(Camera* cam) {

	Game* context = cam->m_Game;

	int speed = 4;

	if (context->GetKey(olc::Key::SHIFT).bHeld) {
		speed = 9;
	}

	if (context->GetKey(olc::Key::TAB).bPressed) {
		context->m_DebugDraw = (context->m_DebugDraw == true) ? false : true;
	}

	if (context->GetKey(olc::Key::W).bHeld) {

		g_vi2dCameraPosition.y -= 1;

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

		g_vi2dCameraPosition.x -= 1;

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

		g_vi2dCameraPosition.y += 1;

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

		g_vi2dCameraPosition.x += 1;

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
	_mapAIStateLogicFunctions();



	Camera* cam = new Camera(this, 0, 0);
	m_Renderer = new Renderer(this, cam);

	m_Renderer->m_Layer1 = CreateLayer();
	m_Renderer->m_Layer2 = CreateLayer();
	m_Renderer->m_Layer3 = CreateLayer();
	m_Renderer->m_Layer4 = CreateLayer();


	return true;
}


bool Game::OnUserUpdate(float fElapsedTime) {


	// Update Entities MapCell
	//_updateEntitiesMapCellCoords();

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

	//_updateAI2();

	return true;
}



void Game::DebugDrawStats() {

	std::string s2 = "Camera Position " + std::to_string(g_vi2dCameraPosition.x) + " : " + std::to_string(g_vi2dCameraPosition.y);
	DrawString(olc::vi2d(2, 40), s2, olc::RED, 2.0f);


	// Draw each maptiles mapcell
	
	std::string s3, s4;
	for (auto it : *EntitiesStorage::Get()->GetMapTilesStorage()) {


		// Camera dependent Cell 
		s3 = std::to_string(it->m_TransformCmp->m_Cell[0]) + " : " + std::to_string(it->m_TransformCmp->m_Cell[1]);
		DrawString(olc::vi2d(it->m_TransformCmp->m_PosX, it->m_TransformCmp->m_PosY), s3, olc::RED, 1.0f);

		// Gameworld Cell
		s4 = std::to_string(it->m_TransformCmp->m_GameWorldSpaceCell[0]) + " : " + std::to_string(it->m_TransformCmp->m_GameWorldSpaceCell[1]);
		DrawString(olc::vi2d(it->m_TransformCmp->m_PosX, it->m_TransformCmp->m_PosY+20), s4, olc::DARK_RED, 1.0f);

	
	}



}


void Game::_drawDebugGrid() {

	using namespace olc;

	int w = ScreenWidth();
	int h = ScreenHeight();


	for (int i = 0; i < w; i += 250) {

		DrawLine(vi2d(i, 0), vi2d(i, h), olc::WHITE);
	}

	for (int j = 0; j < h; j += 250) {

		DrawLine(vi2d(0, j), vi2d(w, j), olc::WHITE);
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

	/*
#ifdef _DEBUG
	m_Game->DrawGrid();
#endif // _DEBUG
	*/

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
	std::vector< GameEntity* >* vec = storage->GetMapTilesStorage();

	MapTile* maptile = nullptr;



	m_Game->SetDrawTarget(m_Layer3);
	m_Game->Clear(olc::BLANK);



	for (auto it: *vec) {

		// Do not draw tiles we do not see.
		if (it->m_TransformCmp->m_Cell[0] > 4 ||
			it->m_TransformCmp->m_Cell[1] > 4) continue;


		maptile = reinterpret_cast<MapTile*>(it);

		if (maptile->m_MapTileEntities->size() > 0) {

			for (auto iter : *maptile->m_MapTileEntities) {


				// Draw appropriate loaded sprite on position specified.
				m_Game->DrawDecal(vi2d(iter->m_TransformCmp->m_PosX, iter->m_TransformCmp->m_PosY),
					m_Game->m_SpriteResourceMap.at(iter->m_GraphicsCmp->m_SpriteName));
			}
		}
	}



	m_Game->EnableLayer(m_Layer3, true);
	m_Game->SetDrawTarget(nullptr);
}

void Renderer::Render2Layer4() {

	using namespace olc;

	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* >* vec = storage->GetMapTilesStorage();

	m_Game->SetDrawTarget(m_Layer4);
	m_Game->Clear(olc::BLANK);


	for (auto it : *vec) {

		// Do not draw tiles we do not see.
		if (it->m_TransformCmp->m_Cell[0] > 4 ||
			it->m_TransformCmp->m_Cell[1] > 4) continue;


			// Draw appropriate loaded sprite on position specified.
			m_Game->DrawDecal(vi2d(it->m_TransformCmp->m_PosX, it->m_TransformCmp->m_PosY),
				m_Game->m_SpriteResourceMap.at(it->m_GraphicsCmp->m_SpriteName));
	}


	m_Game->EnableLayer(m_Layer4, true);
	m_Game->SetDrawTarget(nullptr);

}



void Renderer::RenderLayer0() {

	using namespace olc;

	m_Game->Clear(olc::BLANK);

}




// Find better solution for this functionality.
// It uses way too much CPU.
void Game::_updateAI() {


	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* >* vec = storage->GetStorage();

	for (auto& it : *vec) { // Iterate through all entities.

		// The Maptile iteslf has no AI logic, thus skip it and see
		// whether there are entities on it present.
		MapTile* itMapTile = static_cast<MapTile*>(it);

		if (itMapTile->m_MapTileEntities != nullptr) { // This object IS a maptile.


			if (itMapTile->m_MapTileEntities->size() > 0) { // ... and its vector is not empty.

				for (auto iter : *itMapTile->m_MapTileEntities) { // Do the same for each entity on this maptile.

					using namespace std;
										

					if (!iter->m_AICmp->TryExecuteStateLogic()) {

						cout << APP_ERROR_COLOR;
						cout << "Executing state logic for " << iter->m_IDCmp->m_ID
							<< iter->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << iter->m_TransformCmp->m_GameWorldSpaceCell[1]
							<< " was unsuccessfull." << white << endl;
					
					}
					else {

						cout << APP_SUCCESS_COLOR;
						cout << "Executing state logic for " << iter->m_IDCmp->m_ID << " at position "
							<< iter->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << iter->m_TransformCmp->m_GameWorldSpaceCell[1]
							<< " was successfull." << white << endl;
					}
					
				}
			}
		}
	}

}



void Game::_updateAI2() {

	EntitiesStorage* storage = EntitiesStorage::Get();

	// Get all entities with AI Component.
	std::vector< GameEntity* >* vec = storage->GetAIEntitiesStorage();

	for (auto it : *vec) {


		try {
			using namespace std;


			if (!it->m_AICmp->TryExecuteStateLogic()) {

				cout << APP_ERROR_COLOR;
				cout << "Executing state logic for " << it->m_IDCmp->m_ID << " at position "
					<< it->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << it->m_TransformCmp->m_GameWorldSpaceCell[1]
					<< " was unsuccessfull." << white << endl;

			}
			else {

				cout << APP_SUCCESS_COLOR;
				cout << "Executing state logic for " << it->m_IDCmp->m_ID << " at position "
					<< it->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << it->m_TransformCmp->m_GameWorldSpaceCell[1]
					<< " was successfull." << white << endl;
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

		it->m_TransformCmp->m_GameWorldSpaceCell[0] = (int)it->m_TransformCmp->m_PosX / 256;
		it->m_TransformCmp->m_GameWorldSpaceCell[1] = (int)it->m_TransformCmp->m_PosY / 256;
	}
}


void Game::_mapAIStateLogicFunctions() {
	
	// Test
	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* >* vec = storage->GetAIEntitiesStorage();

	std::string substring = "forest";

	for (auto it : *vec) {

		if (it->m_GraphicsCmp->m_SpriteName.find(substring) != std::string::npos) {

			// Give the forest entity the ForestSearch AI Logic.
			it->m_AICmp->MapState("state_search", new  ForestSearch(*it->m_AICmp));
		}
	}
}




void ForestSearch::executeStateLogic() {

	// increase lifetime on update.
	m_ManagedForest->m_ForestLifetime++;


	// check for transitions of young and old forests
	if (m_ManagedForest->m_ForestType == Forest::ForestType::FOREST_SCARCE) {


		if (m_ManagedForest->m_ForestLifetime > 32) { // scarce --> normal
			
			m_ManagedForest->m_ForestType = Forest::ForestType::FOREST_NORMAL;

			// Update on change.
			m_ManagedForest->Update();
		}
	}
	else {
		if (m_ManagedForest->m_ForestType == Forest::ForestType::FOREST_NORMAL && m_ManagedForest->m_ForestLifetime > 66 || // normal --> dying
			m_ManagedForest->m_ForestType == Forest::ForestType::FOREST_DEEP && m_ManagedForest->m_ForestLifetime > 66*2) { // deep --> dying. This transition takes 2 times longer to fullfill, so the deep forest lives longer.


			if (m_ManagedForest->m_ForestType == Forest::ForestType::FOREST_DEEP) m_ManagedForest->m_ForestLifetime = 67; // Needed reset to normal value for deep forest to ensure common dying time.


			m_ManagedForest->m_ForestType = Forest::ForestType::FOREST_DYING;

			// Update on change.
			m_ManagedForest->Update();
		}
	}
}