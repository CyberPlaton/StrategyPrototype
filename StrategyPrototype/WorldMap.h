#pragma once

#include"Platform.h"

typedef std::array<std::array<std::string, 21>, 21> MapArray;


struct WorldMapDrawingOptions {
	WorldMapDrawingOptions() {
		_createMap();
	}


	MapArray* m_MapDefinitions;

private:

	void _createMap();
};

class WorldMap {
public:
	WorldMap(WorldMapDrawingOptions* worldDef);
	~WorldMap() = default;


private:
	WorldMapDrawingOptions* m_MapDrawOptions = nullptr;

	MapArray* m_WorldMap = nullptr;
private:

};
