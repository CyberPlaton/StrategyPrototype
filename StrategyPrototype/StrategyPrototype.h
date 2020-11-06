#pragma once
#include"olcPixelGameEngine.h"
#include"Platform.h"
#include"ColorConsole.h"
#include"GameEntity.h"
#include"Resources.h"




class Game;
class Camera;
struct CMPCameraInput{

	void HandleKeyboard(Camera* cam);
	void HandleMouse(Camera* cam);

private:
	void _handleMapViewKeyBoard(Camera* cam);
	void _handleCityViewKeyboard(Camera* cam);

	void _handleMapViewMouse(Camera* cam);
	void _handleCityViewMouse(Camera* cam);

};



class Camera {
public:
	Camera(Game* game, int xpos, int ypos) {
		m_Game = game;
		
		m_CamInput = new CMPCameraInput();
		m_Transform = new CMPTransform();

		m_Transform->m_PosX = xpos;
		m_Transform->m_PosY = ypos;

	}
	
	// Position of camera is in the middle of the screen.
	void SetPosition(int x, int y) {

		m_Transform->m_PosX = x;
		m_Transform->m_PosY = y;
	}



	CMPCameraInput* m_CamInput = nullptr;
	CMPTransform* m_Transform = nullptr;

	Game* m_Game = nullptr;



private:	

private:

};



class Renderer {

public:
	enum class RenderMode {
		RENDERMODE_INVALID = -1,
		RENDERMODE_MAPVIEW = 0,
		RENDERMODE_CITYVIEW = 1
	};

public:
	Renderer(Game* g, Camera* cam) { m_Game = g; m_MainCam = cam; m_RenderMode = RenderMode::RENDERMODE_MAPVIEW; }


	void ChangeRenderMode() {
		m_RenderMode = (m_RenderMode == RenderMode::RENDERMODE_CITYVIEW) ? RenderMode::RENDERMODE_MAPVIEW : RenderMode::RENDERMODE_CITYVIEW;
	}

	void SetCurrentViewedCity(City* opened_city){
		m_CurrentViewedCity = opened_city;
	}

	// Should be the only public method for rendering.
	void Render();

	/*
	NOTE FOR DRAWING LAYERS.

	Specify tiles for drawing only on appropriate layers,
	testing for the right layer may be withdrawn in the future.

	Otherwise errors may occur.
	*/

	// Layer for drawing ground maptiles.
	void Render2Layer4(); // With implemented view tesing. Draw only what player sees.

	// Layer for drawing terrain adds like hills, forests, mountains.
	void Render2Layer3();

	// Layer for drawing buildings, cities, caves and improvements.
	void Render2Layer2();

	// Layer for drawing units.
	//void RenderLayer1();
	void Render2Layer1();

	// Layer for drawin effects or general things.
	void RenderLayer0();



	/*
	CITY DRAWING LOGIC
	*/
	void RenderCityLayer0();
	void RenderCityLayer1();
	void RenderCityLayer2();
	void RenderCityLayer3();
	void RenderCityLayer4();


	Camera* m_MainCam = nullptr;
	Game* m_Game = nullptr;


	// Rendering Layers.
	// Layer 0 is always the last that is rendered and cant be changed,
	// it is the most top surface.
	// Last layer is drawn first. We start from 1 to 4.
	int m_Layer4;
	int m_Layer3;
	int m_Layer2;
	int m_Layer1;

	RenderMode m_RenderMode = RenderMode::RENDERMODE_INVALID;

	City* m_CurrentViewedCity = nullptr;

private:

private:
	void _drawGrid();

	void _drawMapTileRegionRect(MapTileRegion* region);
};



class Game : public olc::PixelGameEngine {
public:
	Game() {
		sAppName = "StrategyPrototype";
		m_Game = this;
	}

	static Game* Get() {
		if (m_Game) {
			return m_Game;
		}
		else {
			m_Game = new Game();
			return m_Game;
		}
	}

	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;

	olc::Pixel* RandomColor();
	olc::Pixel MakeOlcColorFromCityBorderColor(City::CityBorderColor color);

	void DebugDrawStats();

	void AdvanceOneTurn();

	Renderer* m_Renderer;
	WorldMap* m_WorldMap;

	// Holds sprite instances of specified names for them.
	//std::map<std::string, olc::Sprite*> m_SpriteResourceMap; 
	std::map<std::string, olc::Decal*> m_SpriteResourceMap;
	std::vector<olc::Sprite*> m_SpriteStorage;

	bool m_DebugDraw = true;
	bool m_DebugDrawGrid = false;
	bool m_DebugDrawForestInfo = false;
	bool m_DebugDrawMapTileInfo = false;
	bool m_DebugDrawGeneralOptions = false;

	bool m_TimeModeTurnBased = true;
	bool m_PoliticalMap = false;

	bool m_DebugDrawRegions = false;
	std::string m_DebugDrawRegionsCount = "-1";

	int m_TurnCount = 1;

	TimeCounter* m_TimeCounter = nullptr;
private:
	static Game* m_Game;

private:

	void _initialize();
	void _initializeMap();
	void _loadSpriteResources();

	void _initializeMapTileCellCoords();
	void _updateLocalMapTileCellCoords();
	void _updateEntitiesMapTileCoords();


	void _updateAI2();
};






struct UIState {

	float m_MouseX;
	float m_MouseY;

	// -1 means no valid mouse button was pressed.
	// It is the only plausible choise.
	int m_MouseDown = -1;

	// Hovered and active items are ID�s from  1..n
	int m_HoveredItem = 0;
	int m_ActiveItem = 0;
};


// Intermediate mode graphical user interface implementation.
struct IMGUI {

	enum class StyleColor {
		STYLE_COLOR_INVALID = -1,
		STYLE_COLOR_DARK_BLUE = 0
	};

	// Receive Mouse and Keyboard input.
	void PrepareIMGUI();
	void FinishIMGUI();

	// Returns 0 if not clicked, returns 1 if clicked...
	int Button(int id, int xpos, int ypos);



	// Check whether mouse is hovered over a widget.
	// Can also be used to see whether a specific region was "hit".
	static bool IsHovered(int xpos, int ypos, int width, int height);
	static UIState* GetUIState();
	static void UpdateUISTate();


	// Utility.
	static IMGUI* Get() {

		if (m_IMGUI) {
			return m_IMGUI;
		}
		else {
			m_IMGUI = new IMGUI();
			return m_IMGUI;
		}
	}

	static void Del() {
		if (m_IMGUI) {
			delete m_IMGUI;
		}
	}

private:
	static int m_WidgetID;

	static IMGUI* m_IMGUI;

	UIState* m_UIState = nullptr;
private:
	IMGUI() {
		m_UIState = new UIState();
		m_UIState->m_HoveredItem = 0; // Reset.
	}

};









// FOREST AI LOGIC DEF
class ForestSearch : public IStateLogic {
public:
	ForestSearch(CMPArtificialIntelligence& ai) {
		m_AICmp = &ai;
		m_ManagedForest = static_cast<Forest*>(m_AICmp->m_ManagedObject);

		// As forest have only one state, predefine it accordingly.
		m_AICmp->ChangeState(States::STATE_SEARCH);
	}


	void executeStateLogic() override;


	CMPArtificialIntelligence* m_AICmp = nullptr;
	Forest* m_ManagedForest = nullptr;


private:


private:

	bool _surroundedByForestNormalOrDeep(Forest* forest);
	void _checkForNewForestCreation(Forest* forest);
	void _spawnRandomForestAroundDeepOne(Forest* deepForest);
};