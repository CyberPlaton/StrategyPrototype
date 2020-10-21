#include"OLCGameEngineInterface.h"
#include"Platform.h"
#include"ColorConsole.h"
#include"GameEntity.h"
#include"Resources.h"


class Renderer {

};



class Game : public olc::PixelGameEngine {
public:
	Game() {
		sAppName = "StrategyPrototype";
	}

	bool OnUserCreate() override {


		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {


		return true;
	}

};


int main()
{
	Game demo;

	if (demo.Construct(968, 720, 1, 1, false, true, false))
		demo.Start();


	return 0;
}