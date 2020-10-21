#pragma once

#include"Platform.h"


struct WorldMapDrawingOptions {

	std::vector<std::vector<std::string>> m_MapDef;
};

class WorldMap {
public:
	WorldMap(WorldMapDrawingOptions** worldDef);
	~WorldMap() = default;


private:

private:

};
