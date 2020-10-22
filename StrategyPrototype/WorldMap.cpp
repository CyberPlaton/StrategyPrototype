#include"WorldMap.h"

WorldMap::WorldMap(WorldMapDrawingOptions* worldDef) {

	m_MapDrawOptions = worldDef;
	m_WorldMap = worldDef->m_MapDefinitions;
}


void WorldMapDrawingOptions::_createMap() {


	m_MapDefinitions = new MapArray();


	for (int i = 0; i <= 20; i++) {


		for (int j = 0; j <= 20; j++) {


			m_MapDefinitions->at(i).at(j).assign("null");
		}
	}
}