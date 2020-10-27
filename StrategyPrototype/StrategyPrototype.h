#pragma once
#include"OLCGameEngineInterface.h"
#include"Platform.h"
#include"ColorConsole.h"
#include"GameEntity.h"
#include"Resources.h"




class Game;
class Camera;
struct CMPCameraInput{

	void HandleKeyboard(Camera* cam);
	void HandleMouse(Camera* cam);
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


	void ChangeRenderMode() { m_RenderMode = (m_RenderMode == RenderMode::RENDERMODE_CITYVIEW) ? RenderMode::RENDERMODE_MAPVIEW : RenderMode::RENDERMODE_CITYVIEW; }

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
	void RenderLayer2();
	void Render2Layer2();

	// Layer for drawing units.
	void RenderLayer1();
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

private:

private:
	void _drawGrid();
};



class Game : public olc::PixelGameEngine {
public:
	Game() {
		sAppName = "StrategyPrototype";
	}

	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;


	void DebugDrawStats();

	void AdvanceOneTurn();

	Renderer* m_Renderer;
	WorldMap* m_WorldMap;

	// Holds sprite instances of specified names for them.
	//std::map<std::string, olc::Sprite*> m_SpriteResourceMap; 
	std::map<std::string, olc::Decal*> m_SpriteResourceMap;
	std::vector<olc::Sprite*> m_SpriteStorage;

	bool m_DebugDraw = false;
	bool m_DebugDrawGrid = false;

	int m_TurnCount = 1;

private:

	void _initialize();
	void _initializeMap();
	void _loadSpriteResources();

	void _initializeMapTileCellCoords();
	void _updateLocalMapTileCellCoords();
	void _updateEntitiesMapTileCoords();


	void _updateAI2();
};





// FOREST AI LOGIC DEF
// If we let it be like this, then 
// we have for every forest instance an own forestsearch logic object and thus
// higher memory consumption... but thus we can run them parallel to each other and
// purely independent. Too, we can make adjustments for different types of forest or even make 
// individual forests with unique AI...
//
// For now, we do not change it.
class ForestSearch : public IStateLogic {
public:
	ForestSearch(CMPArtificialIntelligence& ai) {
		m_AICmp = &ai;
		m_ManagedForest = static_cast<Forest*>(m_AICmp->m_ManagedObject);


		// As forest have only one state, predefine it accotrdingly.
		m_AICmp->ChangeState(States::STATE_SEARCH);
	}


	void executeStateLogic() override;


	CMPArtificialIntelligence* m_AICmp = nullptr;
	Forest* m_ManagedForest = nullptr;


private:


private:

	bool _surroundedByForestNormal(Forest* forest);
	void _checkForNewForestCreation(Forest* forest);
	void _spawnRandomForestAroundDeepOne(Forest* deepForest);
};