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


	// View rectangle is from middle of the screen plus width/2 and plus height/2 accordingly.
	void SetViewRect(int width, int height) {

		m_ViewRect[0].x = m_Transform->m_PosX;
		m_ViewRect[0].y = m_Transform->m_PosY;

		m_ViewRect[1].x = m_ViewRect[0].x + width;
		m_ViewRect[1].y = m_ViewRect[0].y + height;

	}


	CMPCameraInput* m_CamInput = nullptr;
	CMPTransform* m_Transform = nullptr;

	Game* m_Game = nullptr;



private:
	olc::vi2d m_ViewRect[2];
	

private:

};



class Renderer {
public:
	Renderer(Game* g, Camera* cam) { m_Game = g; m_MainCam = cam; }


	/*
	NOTE FOR DRAWING LAYERS.

	Specify tiles for drawing only on appropriate layers,
	testing for the right layer may be withdrawn in the future.

	Otherwise errors may occur.
	*/

	// Layer for drawing ground maptiles.
	void RenderLayer4();

	// Layer for drawing terrain adds like hills, forests, mountains.
	void RenderLayer3();

	// Layer for drawing buildings, cities, caves and improvements.
	void RenderLayer2();

	// Layer for drawing units.
	void RenderLayer1();

	// Layer for drawin effects or general things.
	void RenderLayer0();



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
};



class Game : public olc::PixelGameEngine {
public:
	Game() {
		sAppName = "StrategyPrototype";
	}

	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;


	void DrawGrid() { _drawDebugGrid(); }

	void DebugDrawStats();


	Renderer* m_Renderer;
	WorldMap* m_WorldMap;

	// Holds sprite instances of specified names for them.
	//std::map<std::string, olc::Sprite*> m_SpriteResourceMap; 
	std::map<std::string, olc::Decal*> m_SpriteResourceMap;
	std::vector<olc::Sprite*> m_SpriteStorage;

	bool m_DebugDraw = false;


private:

	void _initialize();
	void _initializeMap();
	void _loadSpriteResources();

	void _drawDebugGrid();


	void _updateEntitiesMapCellCoords();
};