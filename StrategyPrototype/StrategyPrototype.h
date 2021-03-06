#pragma once
// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

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



	// Functions related to drag-and-drop units and giving them professions.
	int m_EntityPrevXpos;
	int m_EntityPrevYpos;
	Unit* m_DraggedUnit = nullptr;

	// Maptile offset for currentview city.
	int m_OffsetX;
	int m_OffsetY;


	void _storePrevPos(GameEntity* entt) {
		m_EntityPrevXpos = entt->m_TransformCmp->m_PosX;
		m_EntityPrevYpos = entt->m_TransformCmp->m_PosY;
	}

	void _resetPrevPos() {
		m_EntityPrevXpos = 0;
		m_EntityPrevYpos = 0;
	}


	bool _tryMakeBuilding(int xpos, int ypos); // Algorithm for building buidlings on slots choosen by user...
	bool _removeBuilding(int xpos, int ypos);
	bool _tryGivingUnitAProfession(Unit* unit);
	//bool _trySetUnitsRessourceToGather(Unit* unit); // Function lets user choose from possible ressources what to gather, we set then how much..
	//bool _setUnitRessourceGathering(Unit* unit, std::string ressource, int yield);
	GameEntity* _hoveringOverEntity(int xpos, int ypos, std::string& entityType);
	GameEntity* _hoveringOverEntityWithoutDraggedUnit(int xpos, int ypos, std::string& entityType, Unit* dragged_unit);
	int _hoveringOverBuildingSlot(int xpos, int ypos); // Returns -1 if no slot is hovered upon.
	bool _isBuildingOnSlot(int slot);
	Unit* _isUnitPresentOnMaptile(MapTile* maptile);
	bool _hasPlayerUnitTechRequirements(std::string tech, Player* p);
	bool _doesPlayerWantToResetProfession();
	bool _doesPlayerWantToGiveOtherProfession();
	bool _hasUnitAProfessionAlready(Unit* unit);
	void _giveUnitPositionAlignedToMaptile(Unit* unit, MapTile* maptile);
	void _giveUnitPositionAlignedToBuilding(Unit* unit, Building* building);


	// Functions for checking appropriate "ressources" on maptile for selecting profession.
	std::vector<std::string> _getPossibleProfessionsOnMaptile(MapTile* maptile);
	std::vector<std::string> _getPossibleProfessionsOnBuilding(Building* building);

	bool _isMaptileAlreadyWorked(MapTile* maptile);
	bool _isBuildingAlreadyWorked(Building* building);


	void _setUnitsWorkedEntity(Building* building, Unit* unit);
	void _setUnitsWorkedEntity(MapTile* maptile, Unit* unit);
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
	//void DrawUnitPanels();
	void DrawCurrentTurnPlayerPanel();
	void DrawFogOfWar(); // Consider redo the concept of fog of war. As this function is fairly slow.... and there are better ways.
	void DrawUnitStats(Unit* unit);
	void DrawPlayersTechnologies();
	void DrawPlayersBuildingsForCities(); // Debug function, "draws" to console...


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
	// Here we draw fog of war over maptiles.
	void RenderLayer0();



	/*
	CITY DRAWING LOGIC
	*/
	void RenderCityLayer0();
	void RenderCityLayer1();
	void RenderCityLayer2(); // Buildings.
	void RenderCityLayer3(); // Mapstuff and city background.
	void RenderCityLayer4(); // City panels and background.


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
		int mod = m_InGamePlayers.size();
		
		// Go to next players index.
		// If end was reached go to first player at index 0.
		int x = (++m_CurrentPlayerIndex) % mod;
		m_CurrentPlayerIndex = x;

		if ((current_index > 0) &&
			(m_CurrentPlayerIndex == 0)) {

			// Register that all player are done.
			all_had_turn = true;
		}

		// Set new player.
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
	bool OnUserDestroy() override;

	olc::Pixel RandomColor();
	olc::Pixel MakeOlcColorFromCityBorderColor(City::CityBorderColor color);

	void DebugDrawStats();

	void AdvanceOneTurn();

	bool AddSpriteToStorage(std::string path, std::string spritename);

	Renderer* m_Renderer = nullptr;
	WorldMap* m_WorldMap = nullptr;

	// Holds sprite instances of specified names for them.
	//std::map<std::string, olc::Sprite*> m_SpriteResourceMap; 
	std::map<std::string, olc::Decal*> m_SpriteResourceMap;
	std::vector<olc::Sprite*> m_SpriteStorage;

	bool m_DebugDraw = true;
	bool m_DebugDrawGrid = false;
	bool m_DebugDrawForestInfo = false;
	bool m_DebugDrawMapTileInfo = false;
	bool m_DebugDrawGeneralOptions = false;
	bool m_DebugDrawUnitPositions = false;
	bool m_DebugDrawPlayersTech = false;
	bool m_DebugDrawPlayersBuildings = false;
	bool m_DebugResearchAllTech = false; // Is a cheat, once used it works. To reset you must restart program.

	bool m_TimeModeTurnBased = true;

	bool m_DebugDrawRegions = false;
	std::string m_DebugDrawRegionsCount = "-1";

	int m_TurnCount = 1;

	TimeCounter* m_TimeCounter = nullptr;



	// Game GUI specific flags.
	bool m_ShowCityPanel = true;
	bool m_PoliticalMap = true;
	bool m_AdvanceOneTurn = false;
	bool m_DrawUnitStats = false;


	// UI Component. For drawing movement tiles for selected unit.
	//std::vector<MapTile*>* m_SelectedUnitsMovementTiles = nullptr;
	std::map<MapTile*, int>* m_SelectedUnitsMovementTiles = nullptr;
	void DrawSelectedUnitsMovementTiles();
	bool UnlockAllTech(Player* player);
	bool MaxLevelForAllCurrentUnits(Player* player);

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
	float m_MouseX = 0;
	float m_MouseY = 0;

	// -1 means no valid mouse button was pressed.
	// It is the only plausible choise.
	int m_MouseDown = -1;

	// Hovered and active items are ID�s from  1..n
	int m_HoveredItem = 0;
	int m_ActiveItem = 0;


	// Keyboard handling.
	int m_KeyboardItem = 0;
	int m_KeyEntered = 0;
	int m_KeyMode = 0;

	// 
	int m_LastFocusedWidget = 0;

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