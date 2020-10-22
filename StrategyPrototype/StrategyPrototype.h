#pragma once
#include"OLCGameEngineInterface.h"
#include"Platform.h"
#include"ColorConsole.h"
#include"GameEntity.h"
#include"Resources.h"

class Game;

class Renderer {
public:
	Renderer(Game* g) { m_Game = g; }

	void Render(std::string layer);

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


	Renderer* m_Renderer;
	WorldMap* m_WorldMap;

	// Holds sprite instances of specified names for them.
	//std::map<std::string, olc::Sprite*> m_SpriteResourceMap; 
	std::map<std::string, olc::Decal*> m_SpriteResourceMap;
	std::vector<olc::Sprite*> m_SpriteStorage;

private:

	void _initialize();
	void _initializeMap();
	void _loadSpriteResources();

	void _drawDebugGrid();
};