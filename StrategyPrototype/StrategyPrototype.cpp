#include"StrategyPrototype.h"

#define MAX_THREAD_NUMBER 20

void Renderer::Render(std::string layer) {

	using namespace olc;

	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* >* vec = storage->GetStorage();


	if (COMPARE_STRINGS(layer, "layer4") == 0) { // the outmost background

		m_Game->SetDrawTarget(m_Layer4);
		m_Game->Clear(olc::VERY_DARK_BLUE);


		for (auto const& it : *vec) {
			if (COMPARE_STRINGS(it->m_GraphicsCmp->m_DrawingLayer, "layer4") == 0) {

				// Draw appropriate loaded sprite on position specified.
				m_Game->DrawDecal(vi2d(it->m_TransformCmp->m_PosX, it->m_TransformCmp->m_PosY),
										m_Game->m_SpriteResourceMap.at(it->m_GraphicsCmp->m_SpriteName));
			}
		}


		m_Game->EnableLayer(m_Layer4, true);
	}
	else if (COMPARE_STRINGS(layer, "layer3") == 0) {

		m_Game->SetDrawTarget(m_Layer3);
		m_Game->Clear(olc::BLANK);


		m_Game->EnableLayer(m_Layer3, true);

	}
	else if (COMPARE_STRINGS(layer, "layer2") == 0) {

		m_Game->SetDrawTarget(m_Layer2);
		m_Game->Clear(olc::BLANK);


		m_Game->EnableLayer(m_Layer2, true);

	}
	else if (COMPARE_STRINGS(layer, "layer1") == 0) {
		
		m_Game->SetDrawTarget(m_Layer1);
		m_Game->Clear(olc::BLANK);

#ifdef _DEBUG
		m_Game->DrawGrid();
#endif // _DEBUG

		m_Game->EnableLayer(m_Layer1, true);

	}


	m_Game->SetDrawTarget(nullptr);
}



void Game::_loadSpriteResources() {

	using namespace olc;
	
	// Loading sprites and decals.
	Sprite* s1 = new Sprite("assets/map/forest_norm.png");
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
	m_SpriteResourceMap.insert(std::make_pair("forest_norm", d1));
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

	m_Renderer = new Renderer(this);
	m_Renderer->m_Layer1 = CreateLayer();
	m_Renderer->m_Layer2 = CreateLayer();
	m_Renderer->m_Layer3 = CreateLayer();
	m_Renderer->m_Layer4 = CreateLayer();


	return true;
}


bool Game::OnUserUpdate(float fElapsedTime) {

	// Layered rendering.
	m_Renderer->Render("layer1");
	m_Renderer->Render("layer2");
	m_Renderer->Render("layer3");
	m_Renderer->Render("layer4");


	// At the end specfy the drawing the 0-th layer, the uppermost one.
	Clear(olc::BLANK);

	return true;
}



void Game::_drawDebugGrid() {

	using namespace olc;

	int w = ScreenWidth();
	int h = ScreenHeight();
	int offsetx = w / 47;
	int offsety = h / 35;


	for (int i = 0; i < w; i += offsetx) {

		DrawLine(vi2d(i, 0), vi2d(i, h), olc::WHITE);
	}

	for (int j = 0; j < h; j += offsety) {

		DrawLine(vi2d(0, j), vi2d(w, j), olc::WHITE);
	}
}



int main()
{
	Game demo;

	if (demo.Construct(968, 720, 2, 2, false, true, false))
		demo.Start();


	return 0;
}