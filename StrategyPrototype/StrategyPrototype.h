#pragma once
#include"OLCGameEngineInterface.h"
#include"Platform.h"
#include"ColorConsole.h"
#include"GameEntity.h"
#include"Resources.h"

class Game;

class Renderer {
public:


	void Render(std::string layer);

	Game* m_Game = nullptr;
};



class Game : public olc::PixelGameEngine {
public:
	Game() {
		sAppName = "StrategyPrototype";
	}

	bool OnUserCreate() override {

		m_Renderer = new Renderer();



		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {

		// Layered rendering.
		m_Renderer->Render("layer1");
		m_Renderer->Render("layer2");
		m_Renderer->Render("layer3");
		m_Renderer->Render("layer4");


		return true;
	}


	Renderer* m_Renderer;
	std::map<std::string, olc::Sprite*> m_SpriteResourceMap;

private:

	void _loadSpriteResources();
};