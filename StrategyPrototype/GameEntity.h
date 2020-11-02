#pragma once
#include"Components.h"
#include"FiniteStateMachine.h"

class MapTile;
class MapRessource;
class Forest;
struct MapTileRegion;
class Game;
class Mountains;
class Hills;
class City;
class Player;
typedef std::array<std::array<MapTile*, 20>, 20> MapTileArray;


// Helpers.
MapTile* GetMapTileAtWorldPosition(int x, int y);
MapTile* GetMapTileAtXYPosition(int x, int y);
GameEntity* IsGameEntityTypeOnMapTile(MapTile* maptile, std::string dynamicTypeName);
std::vector<GameEntity*> GetForestEntities();
bool IsIndexOutOfBound(int x, int y);
int GetTotalForestsCount();
bool IsSubstringInString(std::string substring, std::string string);
Forest* MakeNewForest(std::string name, int x_cell_pos, int y_cell_pos);
Forest* MakeNewForestAtPos(std::string name, int xpos, int ypos, int set_x_cell, int set_y_cell);
Mountains* MakeNewMountain(std::string spritename, int x_cell_pos, int y_cell_pos);
Hills* MakeNewHill(std::string spritename, int x_cell_pos, int y_cell_pos);
City* MakeNewCity(std::string cityname, std::string spritename, Player* player, int x_cell_pos, int y_cell_pos, int citySize);
City* MakeNewCityAtPos(std::string cityname, std::string spritename, Player* player, int xpos, int ypos, int set_x_cell_pos, int set_y_cell_pos, int citySize);
std::string MapTileTypeToString(MapTile* tile);
bool MapTileAppropriteForForest(MapTile* tile, Forest* forest);
bool IsMapTilePartOfRegion(MapTile* tile);
bool RaiseDeepForestRandomly();
MapTileRegion* GetRegionAtWorldPosition(int x, int y);
Player* GetPlayer(std::string name);



enum class TileImprovementLevel {
	TILE_IMPROVEMENT_LVL_INVALID = -1,
	TILE_IMPROVEMENT_LVL_ONE = 0,
	TILE_IMPROVEMENT_LVL_TWO = 1,
	TILE_IMPROVEMENT_LVL_THREE = 2
};


class GameEntity{
public:

	GameEntity() {

		m_IDCmp = new CMPIdentifier();
		m_IDCmp->m_DynamicTypeName = "GameEntity";

		m_TransformCmp = new CMPTransform();
	}

	// Basic components for an Entity.
	CMPIdentifier* m_IDCmp = nullptr;
	CMPTransform* m_TransformCmp = nullptr;
	CMPPhysics* m_PhysicsCmp = nullptr;
	CMPGraphics* m_GraphicsCmp = nullptr;
	CMPArtificialIntelligence* m_AICmp = nullptr;
	FiniteStateMachine* m_FSM = nullptr;
	CMPMovementCostModifier* m_MovementCostCmp = nullptr;
	CMPEntityRace* m_EntityRaceCmp = nullptr;
};


struct CityRessource : public GameEntity {
	CityRessource(std::string name, std::string spritename, int xpos, int ypos) {

		m_IDCmp->m_DynamicTypeName = "CityRessource";
		m_RessourceName = name;

		// For testing purpose te graphics are none.
		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_SpriteName = spritename;

		m_TransformCmp->m_PosX = xpos;
		m_TransformCmp->m_PosY = ypos;


	}

	void IncreaseCount(int n) { m_RessourceCount += n; }
	void DecreaseCount(int n) { m_RessourceCount -= n; }



	std::string m_RessourceName;
	unsigned int m_RessourceCount = 0;
};



struct MapRessource : public GameEntity{
	MapRessource(std::string ressourcename, std::string spritename, int xpos, int ypos) {

		m_IDCmp->m_DynamicTypeName = "MapRessource";
		m_RessourceName = ressourcename;

		m_TransformCmp->m_PosX = xpos;
		m_TransformCmp->m_PosY = ypos;

		// Standardized drawing layer is layer2.
		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "layer2";
		m_GraphicsCmp->m_SpriteName = spritename;
	}

	~MapRessource() = default;


	void MapRessourceYield(std::string ressourcename, unsigned int yield) {

		m_RessourceYieldMap.insert(std::make_pair(ressourcename, yield));
	}


	void UnmapRessourceYield(std::string ressourcename) {
		
		m_RessourceYieldMap.erase(m_RessourceYieldMap.find(ressourcename));
	}


	unsigned int GetRessourceYield(std::string ressourcename){
		return(m_RessourceYieldMap.find(ressourcename)->second);
	}

	std::string m_RessourceName;
	std::map<std::string, int> m_RessourceYieldMap;
};


class City : public GameEntity {
public:

	enum class CitySizeClass {
		CITY_SIZE_CLASS_INVALID = -1,
		CITY_SIZE_CLASS_NORMAL = 0,
		CITY_SIZE_CLASS_BIG = 1,
		CITY_SIZE_CLASS_HUGE = 2
	};
	
	enum class CityBorderColor {
		CITY_BORDERCOLOR_INVALID = -1,
		CITY_BORDERCOLOR_RED = 0,
		CITY_BORDERCOLOR_BLUE = 1,
		CITY_BORDERCOLOR_GREEN = 2,
		CITY_BORDERCOLOR_YELLOW = 3,
		CITY_BORDERCOLOR_MAGENTA = 4,
		CITY_BORDERCOLOR_ORANGE = 5,
		CITY_BORDERCOLOR_BROWN = 6,
		CITY_BORDERCOLOR_BLACK = 7
	};

public:
	City(std::string cityname, std::string spritename, Player* player, int xpos, int ypos, int citySize);

	~City() = default;

	void ClaimRegions();
	void ReclaimRegions(); // Function for testing.

	void MakeCityBorders() {
		_determineCityBorderTiles();
		_determineMapTilesBorderDirection();
	}




	std::string m_CityName;
	unsigned int m_CitySize;
	CitySizeClass m_CitySizeClass = CitySizeClass::CITY_SIZE_CLASS_INVALID;

	std::map<std::string, CityRessource*> m_CityRessourcesMap;
	std::map<std::string, GameEntity*> m_PresentUnitsMap;

	std::vector<MapTileRegion*> m_ClaimedRegions;
	std::string m_ClaimedRegionsSpriteName;

	// To which player this city belongs.
	Player* m_AssociatedPlayer = nullptr;

	// Determine and Draw Borders.
	std::vector<MapTile*> m_CityBorderMapTileVec; // Stores maptiles that belong to city border.
	std::map<MapTile*, std::string> m_MapTileBorderDirectionMap; // Stores for each bordertile in which direction the border is looking to.
																 // Directions are stored like: "left_up_down" etc.

	CityBorderColor m_CityBorderColor = CityBorderColor::CITY_BORDERCOLOR_INVALID; // For appropriate coloring of borders.

private:

	// Cityborder functions.
	void _determineCityBorderTiles();
	void _determineMapTilesBorderDirection();

	// Border helpers.
	bool _isMapTileClaimedByCity(MapTile* maptile);


	// General functions.
	void _updateCitySizeClass() {
		if (m_CitySize < 16) m_CitySizeClass = CitySizeClass::CITY_SIZE_CLASS_NORMAL;
		else if(m_CitySize >= 17 && m_CitySize < 31) m_CitySizeClass = CitySizeClass::CITY_SIZE_CLASS_BIG;
		else if(m_CitySize >= 31) m_CitySizeClass = CitySizeClass::CITY_SIZE_CLASS_HUGE;
		else m_CitySizeClass = CitySizeClass::CITY_SIZE_CLASS_INVALID;
	}


	void _claimRegion(MapTileRegion* region) {
		m_ClaimedRegions.push_back(region);
	}

	bool _isRegionClaimedAlreadyByThisCity(MapTileRegion* region);
	bool _isRegionClaimedByOtherCity(MapTileRegion* region);

	// Call after claiming regions.
	void _setSpriteForClaimedRegion();

	void _unclaimRegions() {
		if (m_ClaimedRegions.size() > 0) {
			m_ClaimedRegions.clear();
		}
	}

	void _determineMapCell(std::string color) {

		if (COMPARE_STRINGS(color, "blue") == 0) {
			m_ClaimedRegionsSpriteName = "map_cell_blue";
			m_CityBorderColor = CityBorderColor::CITY_BORDERCOLOR_BLUE;
		}

		if (COMPARE_STRINGS(color, "red") == 0) {
			m_ClaimedRegionsSpriteName = "map_cell_red";
			m_CityBorderColor = CityBorderColor::CITY_BORDERCOLOR_RED;
		}
	}
};


class Hills : public GameEntity {
public:

	Hills(std::string name, std::string layer, int xpos, int ypos) {

		// Forests have transform, graphics, AI, FSM and id.
		m_IDCmp->m_DynamicTypeName = "Hills";

		m_TransformCmp->m_PosX = xpos;
		m_TransformCmp->m_PosY = ypos;

		m_TransformCmp->m_GameWorldSpaceCell[0] = xpos;
		m_TransformCmp->m_GameWorldSpaceCell[1] = ypos;


		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = layer;
		m_GraphicsCmp->m_SpriteName = name;


		m_MovementCostCmp = new CMPMovementCostModifier();
		_setMovementCost();
	}


private:


private:
	void _setMovementCost() {
		m_MovementCostCmp->SetBaseMovementCost(3);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HUMAN, 1);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_ORC, 1);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HIGHELF, 1);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DARKELF, 1);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_TROLL, 1);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GNOME, -2);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DWARF, -2);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GOBLIN, -2);
	}
};


class Mountains : public GameEntity {
public:

	Mountains(std::string name, std::string layer, int xpos, int ypos) {

		// Forests have transform, graphics, AI, FSM and id.
		m_IDCmp->m_DynamicTypeName = "Mountains";

		m_TransformCmp->m_PosX = xpos;
		m_TransformCmp->m_PosY = ypos;


		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = layer;
		m_GraphicsCmp->m_SpriteName = name;


		m_MovementCostCmp = new CMPMovementCostModifier();
		_setMovementCost();
	}


private:


private:
	void _setMovementCost() {
		m_MovementCostCmp->SetBaseMovementCost(4);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HUMAN, 2);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_ORC, 2);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HIGHELF, 3);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DARKELF, 3);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_TROLL, 3);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GNOME, -3);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DWARF, -3);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GOBLIN, -2);
	}
};



class Forest : public GameEntity {
public:

	enum class ForestClass {
		FOREST_CLASS_INVALID = -1,
		FOREST_CLASS_TEMPERATE = 0,
		FOREST_CLASS_TUNDRA = 1,
		FOREST_CLASS_JUNGLE = 2,
		FOREST_CLASS_SAVANNAH = 3
	};

	enum class ForestType {
		FOREST_INVALID = -1,
		FOREST_DYING = 0,
		FOREST_SCARCE = 1,
		FOREST_NORMAL = 2,
		FOREST_DEEP = 3
	};


	Forest(std::string name, std::string layer, int xpos, int ypos) {

		// Forests have transform, graphics, AI, FSM and id.
		m_IDCmp->m_DynamicTypeName = "Forest";

		m_TransformCmp->m_PosX = xpos;
		m_TransformCmp->m_PosY = ypos;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = layer;
		m_GraphicsCmp->m_SpriteName = name;


		m_MovementCostCmp = new CMPMovementCostModifier();
		_setMovementCost();

		m_AICmp = new CMPArtificialIntelligence(this);

		// Define props
		m_ForestLifetime = 100* TURN_TIME_MODIFIER;
		
		if (IsSubstringInString("_scarce", name)) { // means "_scarce" is in name.
			m_ForestType = ForestType::FOREST_SCARCE;
		}
		else if (IsSubstringInString("_normal", name)) {
			m_ForestType = ForestType::FOREST_NORMAL;

		}
		else if (IsSubstringInString("_deep", name)) {
			m_ForestType = ForestType::FOREST_DEEP;
			m_ForestLifetime = 200;
		}


		if (IsSubstringInString("tundra", name)) {
			m_ForestClass = ForestClass::FOREST_CLASS_TUNDRA;
		}
		else if (IsSubstringInString("temperate", name)) {
			m_ForestClass = ForestClass::FOREST_CLASS_TEMPERATE;
		}
		else if (IsSubstringInString("jungle", name)) {
			m_ForestClass = ForestClass::FOREST_CLASS_JUNGLE;
		}
		else if (IsSubstringInString("savannah", name)) {
			m_ForestClass = ForestClass::FOREST_CLASS_SAVANNAH;
		}
		
	}


	// Update is not meant to be done on each tick, only on occured changes.
	void Update();

	bool HasSameForestClass(Forest* other) {
		return((m_ForestClass == other->m_ForestClass) ? true : false);
	}


	int m_ForestLifeTimeNow = 0;
	int m_ForestLifetime = 0;
	ForestType m_ForestType = ForestType::FOREST_INVALID;
	ForestClass m_ForestClass = ForestClass::FOREST_CLASS_INVALID;

private:


private:

	void _setMovementCost() {
		switch (m_ForestType) {
		case ForestType::FOREST_DEEP:
			// Base cost for a deepforest...
			m_MovementCostCmp->SetBaseMovementCost(3);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HUMAN, 0);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_ORC, 0);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HIGHELF, -2);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DARKELF, -2);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_TROLL, -2);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GNOME, 1);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DWARF, 1);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GOBLIN, 1);

			break;
		case ForestType::FOREST_NORMAL:
			m_MovementCostCmp->SetBaseMovementCost(2);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HUMAN, 0);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_ORC, 0);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HIGHELF, -1);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DARKELF, -1);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_TROLL, -1);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GNOME, 1);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DWARF, 1);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GOBLIN, 1);

			break;
		case ForestType::FOREST_SCARCE:
			m_MovementCostCmp->SetBaseMovementCost(1);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HUMAN, 0);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_ORC, 0);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HIGHELF, 0);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DARKELF, 0);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_TROLL, 0);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GNOME, 0);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DWARF, 0);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GOBLIN, 0);
			break;
		case ForestType::FOREST_DYING:
			m_MovementCostCmp->SetBaseMovementCost(2);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HUMAN, 0);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_ORC, 0);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HIGHELF, -1);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DARKELF, -1);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_TROLL, -1);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GNOME, 1);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DWARF, 1);
			m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GOBLIN, 1);
			break;
		default:
			break;
		}
	}

};



class MapTile : public GameEntity {
public:
	enum class MapTileType {
		MAPTILE_TYPE_INVALID = -1,
		MAPTILE_TYPE_ICE = 0,
		MAPTILE_TYPE_SAND = 1,
		MAPTILE_TYPE_SAVANNAH = 2,
		MAPTILE_TYPE_SNOW = 3,
		MAPTILE_TYPE_TEMPERATE = 4,
		MAPTILE_TYPE_TUNDRA = 5,
		MAPTILE_TYPE_WATER_DEEP = 6,
		MAPTILE_TYPE_WATER_SHALLOW = 7,
		MAPTILE_TYPE_JUNGLE = 8

	};
public:
	MapTile(std::string name, std::string layer, int xpos, int ypos) {
		
		m_IDCmp->m_DynamicTypeName = "MapTile";

		m_MapTileEntities = new std::vector<GameEntity*>();

		// Maptiles have transform, graphics, id.
		m_MapTileName = name;
		m_TransformCmp->m_PosX = xpos;
		m_TransformCmp->m_PosY = ypos;
		
		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = layer;


		if (IsSubstringInString("ice", name)) {
			m_MapTileType = MapTileType::MAPTILE_TYPE_ICE;
			m_GraphicsCmp->m_SpriteName = "ice";
		}
		else if (IsSubstringInString("shallow", name)) {
			m_MapTileType = MapTileType::MAPTILE_TYPE_WATER_SHALLOW;
			m_GraphicsCmp->m_SpriteName = "water_shallow";
		}
		else if (IsSubstringInString("deep", name)) {
			m_MapTileType = MapTileType::MAPTILE_TYPE_WATER_DEEP;
			m_GraphicsCmp->m_SpriteName = "water_deep";
		}
		else if (IsSubstringInString("tundra", name)) {
			m_MapTileType = MapTileType::MAPTILE_TYPE_TUNDRA;
			m_GraphicsCmp->m_SpriteName = "tundra";
		}
		else if (IsSubstringInString("temperate", name)) {
			m_MapTileType = MapTileType::MAPTILE_TYPE_TEMPERATE;
			m_GraphicsCmp->m_SpriteName = "temperate";
		}
		else if (IsSubstringInString("snow", name)) {
			m_MapTileType = MapTileType::MAPTILE_TYPE_SNOW;
			m_GraphicsCmp->m_SpriteName = "snow";
		}
		else if (IsSubstringInString("savannah", name)) {
			m_MapTileType = MapTileType::MAPTILE_TYPE_SAVANNAH;
			m_GraphicsCmp->m_SpriteName = "savannah";
		}
		else if (IsSubstringInString("sand", name)) {
			m_MapTileType = MapTileType::MAPTILE_TYPE_SAND;
			m_GraphicsCmp->m_SpriteName = "sand";
		}
		else if (IsSubstringInString("jungle", name)) {
			m_MapTileType = MapTileType::MAPTILE_TYPE_JUNGLE;
			m_GraphicsCmp->m_SpriteName = "jungle";
		}


	}


	void AssociateToMapTileRegion(MapTileRegion* region) {
		if (region == nullptr) return;

		m_AssociatedRegion = region;
	}


	std::vector<GameEntity*>* m_MapTileEntities;
	std::string m_MapTileName = "NULL";
	MapTileType m_MapTileType = MapTileType::MAPTILE_TYPE_INVALID;

	MapTileRegion* m_AssociatedRegion = nullptr;
};


struct MapTileRegion : public GameEntity{
	MapTileRegion() {
		m_IDCmp->m_DynamicTypeName = "MapTileRegion";

		// Our MapTileRegion is an abstract entity that combines real maptiles.
		// Thus the region does not have a particular position, nor a graphical representation.
		// If there should be an overlay sprite for the region, use the saved MapTiles to get the coords.
		delete m_TransformCmp;
		m_TransformCmp = nullptr;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "layer2";
		m_GraphicsCmp->m_SpriteName = "NULL";
	}

	void SetAssociatedPlayer(Player* p) { m_AssociatedPlayer = p; }

	void SetRegionSprite(std::string spritename) {
		m_GraphicsCmp->m_SpriteName = spritename;
	}

	void AddTileToRegion(MapTile* maptile) {
		if (maptile != nullptr) m_MapTileRegionTiles.push_back(maptile);

		// Then tell the maptile that it belongs to this region.
		maptile->AssociateToMapTileRegion(this);
	}

	void RemoveTileFromRegion(MapTile* maptile) {
		std::vector<MapTile*>::iterator it = std::find(m_MapTileRegionTiles.begin(), m_MapTileRegionTiles.end(), maptile);
		if (it != m_MapTileRegionTiles.end()) m_MapTileRegionTiles.erase(it);
	}


	std::vector<MapTile*> m_MapTileRegionTiles;
	Player* m_AssociatedPlayer = nullptr; // To which player this region belongs.
};



struct EntitiesStorage {


	std::vector< GameEntity* >* GetAIEntitiesStorage() { return m_GameEntitiesWithAIVec; }
	std::vector< GameEntity* >* GetStorage() { return m_GameEntitiesVec; }
	std::vector< GameEntity* >* GetMapTilesStorage() { return m_MapTileGameEntitiesVec; }
	std::vector< GameEntity* >* GetMapViewRessources() { return m_MapViewRessourcesVec; }
	std::vector< GameEntity* >* GetCitiesVec() { return m_CityVec; }
	std::vector< GameEntity* >* GetHillsMountains() { return m_MountainsHillsVec; }
	std::vector<GameEntity*>* GetMapTileRegions() { return m_MapTileRegionsVec; }
	std::vector<Player*>* GetPlayersVec() { return m_PlayersVec; }


	void AddPlayer(Player* p) {
		m_PlayersVec->push_back(p);
	}

	void RemovePlayer(Player* p);

	void RemovePlayer(std::string playername);

	void AddGameEntitie(GameEntity* e) {

		// This entity is a maptile region. Thus we do not want it in general storage.
		// We only add it to specific vector and it can be accessed from there only.
		if (_isMapTileRegion(e)) {
			_addMapTileRegion(e);
			return;
		}



		// General saving.
		m_GameEntitiesVec->push_back(e);

		// Does it have an AI component?
		if (e->m_AICmp) _addEntitieWithAI(e);
		
		// Is it a maptile?
		if (_isMaptile(e)) {

			// Yes, so just add it here...
			_addMaptileEntity(e);
		}
		else {

			// No, it is some entity on a maptile.
			_addEntityToMapTileVector(e);



			// Is it a mapressource?
			if (_isMapViewRessource(e)) {
				_addMapViewRessource(e);
			}

			// Is it a city?
			if (_isCity(e)) {
				_addCity(e);
			}

			// Is it a MapTileRegion?
			if (_isMapTileRegion(e)) {
				_addMapTileRegion(e);
			}

			// Is it a hill or mountain?
			if (_isHillOrMountain(e)) {
				_addHillMountain(e);
			}
		}
			
	}


	void DeleteGameEntitie(GameEntity* e) {


		std::vector< GameEntity* >::iterator iterator = std::find(m_GameEntitiesVec->begin(), m_GameEntitiesVec->end(), e);

		if (iterator != m_GameEntitiesVec->end()) {
			m_GameEntitiesVec->erase(iterator);
		}



		if (e->m_AICmp) { // Delete entitie from AIEntities vector.

			std::vector< GameEntity* >::iterator it = std::find(m_GameEntitiesWithAIVec->begin(), m_GameEntitiesWithAIVec->end(), e);

			if (it != m_GameEntitiesWithAIVec->end()) {
				m_GameEntitiesWithAIVec->erase(it);


				// We need to find the maptiles on which this entities are and delete them from there too.

				MapTile* our_maptile = nullptr;

				// Find maptile on which this entity is.
				for (auto maptile : *m_MapTileGameEntitiesVec) {

					if (maptile->m_TransformCmp->m_GameWorldSpaceCell[0] == e->m_TransformCmp->m_GameWorldSpaceCell[0] &&
						maptile->m_TransformCmp->m_GameWorldSpaceCell[1] == e->m_TransformCmp->m_GameWorldSpaceCell[1]) {

						our_maptile = reinterpret_cast<MapTile*>(maptile);

						std::vector< GameEntity*>::iterator entity = std::find(our_maptile->m_MapTileEntities->begin(),
																				our_maptile->m_MapTileEntities->end(),
																			e);
						if (entity != our_maptile->m_MapTileEntities->end()) {

							our_maptile->m_MapTileEntities->erase(entity);
						}
					}
				}

			}
		}


		// Delete from maptileve if needed.
		if (_isMaptile(e)) {

			std::vector< GameEntity* >::iterator it = std::find(m_MapTileGameEntitiesVec->begin(), m_MapTileGameEntitiesVec->end(), e);

			if (it != m_MapTileGameEntitiesVec->end()) {
				m_MapTileGameEntitiesVec->erase(it);
			}
		}


		// If needed, delete from mapviewressource.
		if (_isMapViewRessource(e)) {

			std::vector< GameEntity* >::iterator it = std::find(m_MapViewRessourcesVec->begin(), m_MapViewRessourcesVec->end(), e);

			if (it != m_MapViewRessourcesVec->end()) {
				m_MapViewRessourcesVec->erase(it);
			}

		}
		

		// Delete city from CityVec.
		if (_isCity(e)) {
			std::vector< GameEntity* >::iterator it = std::find(m_CityVec->begin(), m_CityVec->end(), e);

			if (it != m_CityVec->end()) {
				m_CityVec->erase(it);
			}
		}

		// Delete regions from Maptileregionsvec.
		if (_isMapTileRegion(e)) {
			std::vector< GameEntity* >::iterator it = std::find(m_MapTileRegionsVec->begin(), m_MapTileRegionsVec->end(), e);

			if (it != m_MapTileRegionsVec->end()) {
				m_MapTileRegionsVec->erase(it);
			}
		}

		// Delete Hills or Mountains.
		if (_isHillOrMountain(e)) {
			std::vector< GameEntity* >::iterator it = std::find(m_MountainsHillsVec->begin(), m_MountainsHillsVec->end(), e);

			if (it != m_MountainsHillsVec->end()) {
				m_MountainsHillsVec->erase(it);
			}

		}
		
	}

	void DeleteGameEntitie(CMPIdentifier* id) {

		std::vector<GameEntity*> *vec = m_GameEntitiesVec;

		GameEntity* e = nullptr;
		for (auto const& it : *vec) {
			if (it->m_IDCmp->m_ID == id->m_ID) e = it;
		}

		DeleteGameEntitie(e);
	}

	// The only accessible constructor for this class.
	static  EntitiesStorage* Get() {

		if (!m_EntitiesStorage) {
			m_EntitiesStorage = new EntitiesStorage();
			m_EntitiesStorage->_initGameEntitiesVector();
			return m_EntitiesStorage;
		}
		else {
			return m_EntitiesStorage;
		}

	}

	static void Del() {
		if (m_EntitiesStorage) delete m_EntitiesStorage;
	}

private:
	static EntitiesStorage* m_EntitiesStorage;


	std::vector< GameEntity*>* m_MapTileGameEntitiesVec; // Vector that explicitly hold Maptiles. 
	std::vector< GameEntity* >* m_GameEntitiesVec; // Holds all entities ingame.
	std::vector<GameEntity*>* m_GameEntitiesWithAIVec; // Holds entities in game with AI.
	std::vector<GameEntity*>* m_MapViewRessourcesVec; // Holds all ressources in game, that are explicitly on the mapview.
	std::vector<GameEntity*>* m_CityVec; // Holds all cities in the game.
	std::vector<GameEntity*>* m_MapTileRegionsVec; // Holds all regions defined in game.
	std::vector<GameEntity*>* m_MountainsHillsVec; // Holds all hills and mountains in game.
	std::vector<Player*>* m_PlayersVec; // Holds all player of the game.

private:
	EntitiesStorage() = default;
	EntitiesStorage(const EntitiesStorage&) = default;
	~EntitiesStorage() = default;


	void _initGameEntitiesVector() {
		m_GameEntitiesVec = new std::vector< GameEntity*>();
		m_GameEntitiesWithAIVec = new std::vector<GameEntity*>();
		m_MapTileGameEntitiesVec = new std::vector<GameEntity*>();

		m_MapViewRessourcesVec = new std::vector<GameEntity*>();
		m_CityVec = new std::vector<GameEntity*>();
		m_MapTileRegionsVec = new std::vector<GameEntity*>();
		m_MountainsHillsVec = new std::vector<GameEntity*>();

		m_PlayersVec = new std::vector<Player*>();
	}

	void _addHillMountain(GameEntity* e) {
		m_MountainsHillsVec->push_back(e);
	}

	void _addMapTileRegion(GameEntity* e) {
		m_MapTileRegionsVec->push_back(e);
	}

	void _addCity(GameEntity* e) {
		m_CityVec->push_back(e);
	}

	void _addMapViewRessource(GameEntity* e) {
		m_MapViewRessourcesVec->push_back(e);
	}


	void _addEntitieWithAI(GameEntity* e) {
		m_GameEntitiesWithAIVec->push_back(e);
	}


	void _addMaptileEntity(GameEntity* e) {
		m_MapTileGameEntitiesVec->push_back(e);
	}


	void _addEntityToMapTileVector(GameEntity* e) {

		int entity_cell[2]; entity_cell[0] = e->m_TransformCmp->m_GameWorldSpaceCell[0]; entity_cell[1] = e->m_TransformCmp->m_GameWorldSpaceCell[1];

		GetMapTileAtWorldPosition(entity_cell[0], entity_cell[1])->m_MapTileEntities->push_back(e);
	}


	bool _isHillOrMountain(GameEntity* e) {
		if (COMPARE_STRINGS(e->m_IDCmp->m_DynamicTypeName, "Hills") == 0 ||
			COMPARE_STRINGS(e->m_IDCmp->m_DynamicTypeName, "Mountains") == 0) {
			return true;
		}
		else return false;
	}


	bool _isMapViewRessource(GameEntity* e) {

		MapRessource* r = reinterpret_cast<MapRessource*>(e);

		if (r != nullptr && COMPARE_STRINGS(r->m_IDCmp->m_DynamicTypeName, "MapRessource") == 0) return true;
		else return false;
	}

	bool _isMaptile(GameEntity* e) {

		std::string name;
		name = e->m_GraphicsCmp->m_SpriteName;

		if (COMPARE_STRINGS(name, "temperate") == 0 ||
			COMPARE_STRINGS(name, "ice") == 0 ||
			COMPARE_STRINGS(name, "sand") == 0 ||
			COMPARE_STRINGS(name, "savannah") == 0 ||
			COMPARE_STRINGS(name, "snow") == 0 ||
			COMPARE_STRINGS(name, "tundra") == 0 ||
			COMPARE_STRINGS(name, "water_deep") == 0 ||
			COMPARE_STRINGS(name, "water_shallow") == 0 ||
			COMPARE_STRINGS(name, "jungle") == 0) {
			return true;
		}
		else {
			return false;
		}

	}


	bool _isCity(GameEntity* e) {

		if (e != nullptr) {
			if (COMPARE_STRINGS(e->m_IDCmp->m_DynamicTypeName, "City") == 0) return true;
		}

		return false;
	}


	bool _isMapTileRegion(GameEntity* e) {
		if (COMPARE_STRINGS(e->m_IDCmp->m_DynamicTypeName, "MapTileRegion") == 0) return true;
		else return false;
	}
};



struct WorldMapDrawingOptions {
	WorldMapDrawingOptions(int width, int height) {
		m_MapWidth = width;
		m_MapHeight = height;
		_createMap();
	}

	std::string IndexAsString(int i, int j) {
		return "";
	}

	int m_MapWidth;
	int m_MapHeight;

	MapTileArray* m_MapDefinitions;

private:

	void _createMap();
};




class WorldMap {
public:
	WorldMap() = default;
	~WorldMap() = default;


	void SetMapOptions(WorldMapDrawingOptions* worldDef);
	static WorldMap* Get();
	static void Del();



private:
	static WorldMap* m_WorldMapInstance;
	WorldMapDrawingOptions* m_MapDrawOptions = nullptr;
	MapTileArray* m_WorldMap = nullptr;

private:

};



class Player {
public:
	Player(std::string playername, std::string playercolor) {
		
		m_PlayerName = playername;
		m_PlayerColor = playercolor;
	}

	void AddCity(City* c) {
		m_PlayerCities.push_back(c);
	}


	std::string m_PlayerName;
	std::string m_PlayerColor;
	std::vector<City*> m_PlayerCities;

private:


private:


	bool _isMapTileSurroundedByOwnTiles(MapTile* tile);
	bool _belongMapTileToThisPlayer(MapTile* tile);
};