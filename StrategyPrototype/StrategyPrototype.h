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

	void DrawCityPanels();
	void DrawYearQuartalPanel();
	void DrawUnitPanels();
	void DrawCurrentTurnPlayerPanel();


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

	void _drawCityviewGroundBasedOnCityMaptileType(MapTile* maptile);
};

/*
NOTE:
Turn-Based strategy with I-GO-U-GO mode.
*/
struct PlayerTurnCounter {

	static PlayerTurnCounter* Get() {

		if (g_pPlayerTurnCounter) {
			return g_pPlayerTurnCounter;
		}
		else {
			g_pPlayerTurnCounter = new PlayerTurnCounter();
			return g_pPlayerTurnCounter;
		}
	}

	static void Del() {

		if (g_pPlayerTurnCounter) {
			delete g_pPlayerTurnCounter;
		}
	}


	void BeginGame() {
		// Let player begin.
		m_CurrentTurnPlayer = m_InGamePlayers[0];
	}


	void AddPlayer(Player* p) {
		m_InGamePlayers.push_back(p);
	}

	void EliminatePlayer(Player* p) {

		std::vector<Player*>::iterator it = std::find(m_InGamePlayers.begin(), m_InGamePlayers.end(), p);
		m_InGamePlayers.erase(it);
	}


	bool NextPlayerTurn() {

		bool all_had_turn = false;
		int current_index = m_CurrentPlayerIndex;
		m_CurrentPlayerIndex = (++m_CurrentPlayerIndex) % m_InGamePlayers.size();

		if (current_index > 0 & m_CurrentPlayerIndex == 0) {
			all_had_turn = true;
		}

		m_CurrentTurnPlayer = m_InGamePlayers[m_CurrentPlayerIndex];
	
		
		return all_had_turn;
	}


	Player* m_CurrentTurnPlayer = nullptr;
	std::vector<Player*> m_InGamePlayers;

private:
	int m_CurrentPlayerIndex = -1;
	bool m_AllPlayersHadTurn = false;


	static PlayerTurnCounter* g_pPlayerTurnCounter;

private:

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

	bool m_DebugDrawRegions = false;
	std::string m_DebugDrawRegionsCount = "-1";

	int m_TurnCount = 1;

	TimeCounter* m_TimeCounter = nullptr;



	// Game GUI specific flags.
	bool m_ShowCityPanel = true;
	bool m_PoliticalMap = true;
	bool m_AdvanceOneTurn = false;

private:
	static Game* m_Game;

private:

	void _initialize();
	void _initializeMap();
	void _loadSpriteResources();

	void _initializeMapTileCellCoords();
	void _updateLocalMapTileCellCoords();
	void _updateEntitiesMapTileCoords();

	// Function updates the forests AI components.
	void _updateForestAI2();
};




// Macro for ID creation of a widget.
#define GEN_ID (__LINE__)

struct UIState {

	// Mouse handling.
	float m_MouseX;
	float m_MouseY;

	// -1 means no valid mouse button was pressed.
	// It is the only plausible choise.
	int m_MouseDown = -1;

	// Hovered and active items are ID´s from  1..n
	int m_HoveredItem = 0;
	int m_ActiveItem = 0;


	// Keyboard handling.
	int m_KeyboardItem;
	int m_KeyEntered;
	int m_KeyMode;

	// 
	int m_LastFocusedWidget;

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
	int TextButton(int id, int xpos, int ypos, std::string text);

	// Usage: Display some text if we hover over a widget, e.g. Button.
	// NOTE:
	// Currently not working. Use ToolTipSpriteButton() instead!
	int ToolTipButton(int id, int xpos, int ypos, std::string text, std::string tooltiptext);

	// Spritebutton that displays a tooltip on hovering.
	int ToolTipSpriteButton(int id, int xpos, int ypos, std::string spritename, std::string tooltiptext);
	int ToolTipSpriteButton(int id, int xpos, int ypos, std::string spritename, std::string tooltiptext, olc::Pixel teint_color);


	// The sprite is stored in struct
	int SpriteButton(int id, int xpos, int ypos, std::string spritename);

	// Slider with value input.
	int Slider(int id, int xpos, int ypos, int max_value, int &value);

	// Textinput 
	int Textfield(int id, int xpos, int ypos, std::string* buffer);

	// Check whether mouse is hovered over a widget.
	// Can also be used to see whether a specific region was "hit".
	static bool IsHovered(int xpos, int ypos, int width, int height);
	static UIState* GetUIState();
	static void UpdateUISTate();

	static bool AddSprite(std::string path, std::string spritename);

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

	olc::Pixel* m_DefaultWidgetColor;
	olc::Pixel* m_DefaultHoveredWidgetColor;
	olc::Pixel* m_DefaultActiveWidgetColor;
	olc::Pixel* m_DefaultWidgetElementColor;
	olc::Pixel* m_DefaultWidgetTextColor;


	// Same as in Game, but here we re sotring explicitlly GUI sprites for loading everytime...
	std::map<std::string, olc::Sprite*> m_IMGUISpriteResourceMap;

	// Holds currently used decals.
	std::map<std::string, olc::Decal*> m_IMGUIDecalMap;

private:
	IMGUI() {
		m_UIState = new UIState();
		m_UIState->m_HoveredItem = 0; // Reset.

		m_DefaultWidgetElementColor = new olc::Pixel(53, 48, 38, 255); // Very dark brown.
		m_DefaultWidgetColor = new olc::Pixel(83, 61, 53, 225); // Default brown.
		m_DefaultHoveredWidgetColor = new olc::Pixel(106, 78, 56, 225); // Bit lighter brown.
		m_DefaultActiveWidgetColor = new olc::Pixel(151, 121, 97, 225); // Very light brown.
		m_DefaultWidgetTextColor = new olc::Pixel(255, 255, 255, 255); // Very light brown.

	}



	std::string _getLastHitButton();
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