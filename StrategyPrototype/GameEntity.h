#pragma once
// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include"Components.h"
#include"FiniteStateMachine.h"
#include"YearCounter.h"
#include"UnitDefs.h"
#include"UnitHelpers.h"
#include"olcPixelGameEngine.h"
#include"TechnologyTree.h"


// CLASSES DECLARATIONS.
class MapTile;
class MapRessource;
class Forest;
struct MapTileRegion;
class Game;
class Mountains;
class Hills;
class City;
class Player;
class River;
class Unit;
class Building;
typedef std::array<std::array<MapTile*, 20>, 20> MapTileArray;


/*
UNIT AI LOGIC FUNCTIONS.

Some functions like attack, defend, move, patrol etc.
must be set from "outside", like an AI-Engine that is "bigger" than this
units AI component, or the player controling this unit.

After that the unit executes the logic until it reaches the defined "endpoint" or
its "unterbrochen".
*/

// WAIT
class UnitWaitLogic : public IStateLogic {
public:
	UnitWaitLogic(CMPArtificialIntelligence& ai);
	~UnitWaitLogic();


	void executeStateLogic() override;





	// Holding Unit and its AI component.
	CMPArtificialIntelligence* m_AICmp = nullptr;
	Unit* m_ManagedUnit = nullptr;

private:

private:

};

// PATROL
class UnitPatrolLogic : public IStateLogic {
public:
	UnitPatrolLogic(CMPArtificialIntelligence& ai, bool circle = true, States endpointstate = States::STATE_INVALID);
	~UnitPatrolLogic();


	void executeStateLogic() override;




	void AddPatrolPoint(olc::vi2d v) {
		m_PatrolPoints.push_back(v);
	}


	// Holding Unit and its AI component.
	CMPArtificialIntelligence* m_AICmp = nullptr;
	Unit* m_ManagedUnit = nullptr;

private:

	States m_TransitState; // To which state to change after patrolend reached.
	bool m_PatrolPointReached = false;

	std::vector<olc::vi2d> m_PatrolPoints; // The "points" on the worldmap to patrol.
										   // Points are cell positions like {1:2} etc.

private:

};

// MOVE
class UnitMoveLogic : public IStateLogic {
public:
	UnitMoveLogic(CMPArtificialIntelligence& ai);
	~UnitMoveLogic();


	void executeStateLogic() override;





	// Holding Unit and its AI component.
	CMPArtificialIntelligence* m_AICmp = nullptr;
	Unit* m_ManagedUnit = nullptr;

private:
	// Defines specified movement points of
	// how and where to the unit must move to.
	// The logic executes movment in direction of first point,
	// or defines a new vector if all movement points are done.
	// 
	// The endpoint is given by a point from the units "unit->m_MovementObjectives".
	// If an endpoint is reached we get the next point from "unit->m_MovementObjectives"
	// and redo the procedure.
	std::vector<olc::vi2d> m_MovementVector;

private:

	bool _movementPointReached(int our_xpos, int our_ypos);
	bool _isMaptTileDirectNeighbor(int xpos, int ypos, MapTile* maptile);

	olc::vd2d _getMapTileMiddle(int xpos, int ypos);
};

// ATTACK
class UnitAttackLogic : public IStateLogic {
public:
	UnitAttackLogic(CMPArtificialIntelligence& ai);
	~UnitAttackLogic();


	void executeStateLogic() override;





	// Holding Unit and its AI component.
	CMPArtificialIntelligence* m_AICmp = nullptr;
	Unit* m_ManagedUnit = nullptr;

private:

private:

};

// DEFEND
class UnitDefendLogic : public IStateLogic {
public:
	UnitDefendLogic(CMPArtificialIntelligence& ai);
	~UnitDefendLogic();


	void executeStateLogic() override;





	// Holding Unit and its AI component.
	CMPArtificialIntelligence* m_AICmp = nullptr;
	Unit* m_ManagedUnit = nullptr;

private:

private:

};

// DIE
class UnitDieLogic : public IStateLogic {
public:
	UnitDieLogic(CMPArtificialIntelligence& ai);
	~UnitDieLogic();


	void executeStateLogic() override;





	// Holding Unit and its AI component.
	CMPArtificialIntelligence* m_AICmp = nullptr;
	Unit* m_ManagedUnit = nullptr;

private:

private:

};

// SEARCH
class UnitSearchLogic : public IStateLogic {
public:
	UnitSearchLogic(CMPArtificialIntelligence& ai);
	~UnitSearchLogic();


	void executeStateLogic() override;





	// Holding Unit and its AI component.
	CMPArtificialIntelligence* m_AICmp = nullptr;
	Unit* m_ManagedUnit = nullptr;

private:

private:

};

// FLEE
class UnitFleeLogic : public IStateLogic {
public:
	UnitFleeLogic(CMPArtificialIntelligence& ai);
	~UnitFleeLogic();


	void executeStateLogic() override;





	// Holding Unit and its AI component.
	CMPArtificialIntelligence* m_AICmp = nullptr;
	Unit* m_ManagedUnit = nullptr;

private:

private:

};


struct CMPUnitRessourceProduction {
	CMPUnitRessourceProduction(Unit* unit, City* city) {

		m_ManagedUnit = unit;
		m_AssociatedCity = city;
	}

	// Let unit produce ressource it is set for and store in city.
	bool Produce();

	bool SetWorkedEntity(MapTile* entt);
	bool SetWorkedEntity(Building* entt);


	void SetCurrentProduction();


	Unit* m_ManagedUnit = nullptr;
	City* m_AssociatedCity = nullptr;

	// Entities the unit derive the yield for ressource and other information.
	MapTile* m_WorkedMaptile = nullptr;
	Building* m_WorkedBuilding = nullptr;

	// Current production and demand can be set dynamically by getting
	// m_UnitClass->m_UnitRessourceProduction->m_ProducedRessource...
	std::string m_CurrentProducedRessource;
	int m_CurrentYield = 0;
	std::string m_CurrentDemandedRessource;
	int m_CurrentDemand = 0;

	int m_BaseYieldForWorkedEntity = 0; // Needed for computing current yield with Level.

private:
	
	GameEntity* _hasWorkeableEntity(MapTile* maptile);
};


// Helpers.
MapTile* GetMaptileAtMousePosition(int x, int y);
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

// If city = false, then a fort will be defined.
City* MakeNewCity(bool city, std::string cityname, CMPEntityRace::Race race, Player* player, int x_cell_pos, int y_cell_pos, int citySize);
City* MakeNewCityAtPos(bool city, std::string cityname, CMPEntityRace::Race race, Player* player, int xpos, int ypos, int set_x_cell_pos, int set_y_cell_pos, int citySize);
std::string MapTileTypeToString(MapTile* tile);
bool MapTileAppropriteForForest(MapTile* tile, Forest* forest);
bool IsMapTilePartOfRegion(MapTile* tile);
bool RaiseDeepForestRandomly();
MapTileRegion* GetRegionAtWorldPosition(int x, int y);
Player* GetPlayer(std::string name);
bool HasMapTileRiver(MapTile* maptile);
City* HasMapTileCityOrFort(MapTile* maptile);
bool IsUnitInCityOrFort(Unit* unit);
bool IsUnitInCityOrFort(City* city, Unit* unit);
River* MakeNewRiver(std::string spritename, int x_cell_pos, int y_cell_pos);

Unit* SpawnCitizenInCity(City* city, int xpos, int ypos);
Unit* MakeNewUnitAtPos(CMPEntityRace::Race race, UnitMovementType movement_type, Player* p, std::string unit_class, int xpos, int ypos, int x_cell, int y_cell);
Unit* GetUnitAtMapTileFromMousePosition(int xpos, int ypos);
std::string GetColorFromString(std::string color);

// Function SETS maptiles directly around entity as visible for the associated player.
void UpdateMapVisionForEntity(GameEntity* entt, Player* associated_player);

// Function UNSETS maptiles directly around entity as visible for the associated player.
void ReverseMapVisionForEntity(GameEntity* entt, Player* associated_player);

void GetPrimaryMapTilesAroundSelf(int xpos, int ypos, std::vector<MapTile*>* storage); // Like tiles directly around self.
void GetSecondaryMapTilesAroundSelf(int xpos, int ypos, std::vector<MapTile*>* storage); // Like tiles 1 tile away around self.
bool IsPlayersUnit(Player* p, Unit* u);


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

	~GameEntity();

	// Basic components for an Entity.
	CMPIdentifier* m_IDCmp = nullptr;
	CMPTransform* m_TransformCmp = nullptr;
	CMPPhysics* m_PhysicsCmp = nullptr;
	CMPGraphics* m_GraphicsCmp = nullptr;
	CMPArtificialIntelligence* m_AICmp = nullptr;
	FiniteStateMachine* m_FSM = nullptr;
	CMPMovementCostModifier* m_MovementCostCmp = nullptr;
	CMPEntityRace* m_EntityRaceCmp = nullptr;
	CMPGatherableRessource* m_GatherableRessourceCmp = nullptr;
};



class Unit : public GameEntity {
public:
	Unit(CMPEntityRace::Race race, UnitMovementType movement_type, int xpos, int ypos, int set_x_cell, int set_y_cell);

	// Unit specific, all classes wide functionality.
	//
	//

	bool SetBirthsign();
	bool SetPlayer(Player* p);
	unsigned int GetMovementPoints() { return m_MovementPoints; }
	bool CanMoveOnMapTile(MapTile* tile);
	bool SetClass(std::string classname);
	bool ChangeClass(std::string classname);
	bool JoinCity(City* city);
	bool LeaveCity();

	// Move unit to a location.
	// Storage has the movement cost definitions for this particular unit.
	void MoveTo(int x_cell, int y_cell, std::map<MapTile*, int>* storage);
	void MoveTo(int x_cell, int y_cell);


	// Saves maptiles to which this unit can go in current turn.
	// It returns the reachable maptiles, so we can draw them in main function.
	bool DetermineTilesInMovementRange2(std::map<MapTile*, int>* storage);

	
	// Unit cease to exist.
	void Die();



	// Standard functions.
	~Unit() = default;

	// Function for calling after every turn.
	// It updates current age of unit and reset movement points.
	void Update();

	// Function to be called every turn if unit has civil class.
	// It gathers ressourcers specific for UnitClass of this unit.
	//bool DoClassSpecificWork();

	//std::map<std::string, int>* GetValidGatheringRessources() {
	//	return _getValidRessourceForGatheringOrCreating();
	//}

	/*
	void UpdateMovementPoints() {
		_resetMovementPoints();
	}
	*/

	//bool SetDerivedStats();
	//bool SetClass(std::string c);

	/*
	std::map<UnitSkillsEnum, int>* GetUnitSkills() {
		return m_UnitSkillsMap;
	}

	std::map<UnitAttributesEnum, int>* GetUnitAttributes() {
		return m_UnitAttributesMap;
	}
	*/



	// All units are at least 14 Years old.
	unsigned int m_Age = 14;
	// Defines the max age to which this unit will live.
	unsigned int m_MaxAge = -1;


	std::string m_Name;
	std::string m_Birthsign = "NULL"; // Defined by year-quartal in which unit was "born".

	//UnitClass* m_UnitClass = nullptr;
	Player* m_AssociatedPlayer = nullptr;
	std::string m_UnitPlayerColor = "NULL";

	bool m_IsInCity = false;
	City* m_AssociatedCity = nullptr;

	UnitMovementType m_UnitMovementType = UnitMovementType::UNIT_MOVEMENT_TYPE_INVALID;

	// Update this everytime we have unit in focus.
	std::map<MapTile*, int>* m_MovementCostStorage = nullptr;

	// Storage for objectives where the unit has to move to.
	// Purpose is, that units execute movement objectives to destinations
	// on turn end autonomously.
	std::vector<olc::vi2d> m_MovementObjectives;



	// UnitRelated structs for more functionality.
	UnitBase* m_UnitClass = nullptr;
	CMPUnitRessourceProduction* m_UnitRessourceProductionCmp = nullptr;

private:
	int m_AgeInternal = -1;

	int m_MovementPoints = 0;

	/*
	// Units skills and attributes.
	std::map<UnitSkillsEnum, int>* m_UnitSkillsMap;
	std::map<UnitAttributesEnum, int>* m_UnitAttributesMap;
	*/

private:

	// Function gets all valid ressources for gathering for this unit.
	// If nothing to gather is available we return nullptr.
	//std::map<std::string, int>* _getValidRessourceForGatheringOrCreating();

	void _determineUnitRibbonColor();
	void _defineMaxAge();

	void _setUnitMovementType(UnitMovementType type) {
		m_UnitMovementType = type;
	}

	//void _defineRandomUnitTalents(); // Defines randomized bonuses to attributes and skills.
	//void _defineStandardBeginningStats(); // All skills and attributes start at 5.
	//void _defineStatsBasedOnUnitRace(); // Based on race give bonuses or minuses to stats or skills.
	//void _defineStatsBasedOnUnitBirthsign(); // Gives bonuses and minuses based on the birthsign of unit.
	//void _defineDerivedAttributes();

	void _defineUnitName();

	unsigned int _determineMovementPoints();
	void _resetMovementPoints();


	// Based on given position returns a vector of neighboring maptiles.
	std::vector<MapTile*>* _getNeighbouringMapTiles(int xpos, int ypos);
	std::vector<MapTile*>* _getNeighbouringMapTiles(MapTile* maptile);
	bool _isMapTileWeAreStandingOn(MapTile* m);
	bool _isMapTileAlreadyInserted(MapTile* m, std::map<MapTile*, int>* storage);


	void _mapStates();

	// Functions updates Attributes based on current data and return result.
	//int _getFatigue();
	//int _getMagicka();
	//int _getHealth();



	void _setSpriteBasedOnClassAndRace();
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


class Building;
class City : public GameEntity {
public:

	// Defines the type of landscape 
	// the city is built upon.
	// Note: no cities can be built on mountains, only forts.
	enum class CityLandscapeType {
		CITY_LANDSCAPE_INVALID = -1,
		CITY_LANDSCAPE_HILLS = 0,
		CITY_LANDSCAPE_MOUNTAINS = 1,
		CITY_LANDSCAPE_FOREST = 2,
		CITY_LANDSCAPE_PLAIN = 3
	};

	// Define here whether this cityentity is a fort or city.
	// Based on it, it will have other functinalities and possibilities.
	enum class CityType {
		CITY_TYPE_INVALID = -1,
		CITY_TYPE_CITY = 0,
		CITY_TYPE_FORT = 1
	};

	enum class CitySizeClass {
		CITY_SIZE_CLASS_INVALID = -1,
		CITY_SIZE_CLASS_SMALL = 0,
		CITY_SIZE_CLASS_NORMAL = 1,
		CITY_SIZE_CLASS_BIG = 2,
		CITY_SIZE_CLASS_HUGE = 3
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


	enum class CityBuildingSlotType {
		CITY_BUILDING_SLOT_TYPE_INVALID = -1,
		CITY_BUILDING_SLOT_TYPE_STANDARD = 0,
		CITY_BUILDING_SLOT_TYPE_SPECIAL = 1,
		CITY_BUILDING_SLOT_TYPE_PORT = 2
	};

	struct CitySpritesHolder {
		std::string m_SmallCitySprite;
		std::string m_NormalCitySprite;
		std::string m_BigCitySprite;
		std::string m_HugeCitySprite;
	};

	struct BuildingSlot {
		BuildingSlot(int xpos, int ypos, int slot_number,
			City::CityBuildingSlotType slot_type) {

			m_XPos = xpos;
			m_YPos = ypos;
			m_Width = SPRITES_WIDTH_AND_HEIGHT;
			m_Height = SPRITES_WIDTH_AND_HEIGHT;

			m_SlotNumber = slot_number;
			m_SlotType = slot_type;
		}


		int m_XPos;
		int m_YPos;
		int m_Width;
		int m_Height;

		int m_SlotNumber = -1;

		City::CityBuildingSlotType m_SlotType;

		bool m_UsedByBuilding = false;

		Building* m_AssociatedBuilding = nullptr;
	};

public:
	// Constructor for cityentities, whether a city or fort.
	// Make sure to set always the correct sprite for fort or city, as we do not test semantics...
	City(std::string cityname, bool city, CMPEntityRace::Race race, Player* player, int xpos, int ypos, int citySize);

	~City() = default;

	// First function to be called after creation of a city.
	// Initializes properly all needed definitions for a city entity.
	void Initialize() {

		ClaimRegions();
		MakeCityBorders();
		_deriveCityLandscapeType();


		_defineCityBuildingsSlots(); // Must be after landscape definition.


		_initializeCityRessourceMap();
	}

	// Function updates visibility of maptiles around self.
	void UpdateVisibility();
	void ResetVisibility();

	// Use this to render current city representation.
	std::string GetCurrentCitySprite();

	// Stringifies the landscape type of the city.
	std::string GetCityLandscapeTypeString();
	CityLandscapeType GetCityLandscapeType();

	void ClaimRegions() {
		_claimRegions();
	}

	// Checks whether city size has changed and borders must be reclaimed.
	void Update();

	void ProduceRessources();

	// Should be called when city grows or declines in size.
	void ReclaimRegions();

	// Function lets all units in city try to gather ressourses defined for them.
	//void LetUnitsGatherRessources();

	void MakeCityBorders() {
		_determineCityBorderTiles();
		_determineMapTilesBorderDirection();
	}


	void AddBuilding(Building* building, int slot);
	void RemoveBuilding(Building* building);
	void AddUnit(Unit* unit);
	void RemoveUnit(Unit* unit);

	bool AddCitizenToJobless(GameEntity* unit);
	void RemoveCitizenFromJoblessVector(GameEntity* unit);

	CMPEntityRace* m_CityRaceCmp = nullptr;
	std::string m_CityName;
	unsigned int m_CitySize;
	CitySizeClass m_CitySizeClass = CitySizeClass::CITY_SIZE_CLASS_INVALID;
	CityType m_CityType = CityType::CITY_TYPE_INVALID;
	CitySpritesHolder* m_CitySpritesStorage = nullptr;
	CityLandscapeType* m_CityLandscapeType = nullptr;
	bool m_RiverPresentInCity = false; // Defines the cityview, is set on initialization.
	bool m_CoastalCity = false; // Defines the layout in cityview, and is set at initialization.

	//std::map<std::string, CityRessource*> m_CityRessourcesMap;
	std::map<std::string, int> m_CityRessourcesMap; // e.g. {"Horses", 13};
	std::vector<GameEntity*> m_PresentUnitsVector;

	// Special for PresentUnits that dont have a job, say citizens and
	// present military units that dont do aniything.
	std::vector<GameEntity*> m_GarrisonedUnits;

	std::vector<MapTileRegion*> m_ClaimedRegions;
	std::string m_ClaimedRegionsSpriteName;

	// To which player this city belongs.
	Player* m_AssociatedPlayer = nullptr;

	// Determine and Draw Borders.
	std::vector<MapTile*> m_CityBorderMapTileVec; // Stores maptiles that belong to city border.
	std::map<MapTile*, std::string> m_MapTileBorderDirectionMap; // Stores for each bordertile in which direction the border is looking to.
																 // Directions are stored like: "left_up_down" etc.

	CityBorderColor m_CityBorderColor = CityBorderColor::CITY_BORDERCOLOR_INVALID; // For appropriate coloring of borders.


	// City buildings slots.
	// NOTE:
	// Every city has 9 standard slots, as most buildins are standard.
	// Then they have 2 special slots. And if by water 2 port slots.
	//
	// Every fort has 4 standard slots. 2 special slots. And if by water 2 port slots.
	//
	// For now we do not disitinct between slots for hill- , forest- and plain cities...
	//
	// Slots are numbered:
	// City: 
	// 1-9 standard, 10-11 special, 12-13 port.
	//
	// Fort:
	// 1-4 standard, 5-8 special.
	std::vector<BuildingSlot*> m_CityBuildingsSlots;

private:

	void _initializeCityRessourceMap();
	void _deinitializeCityRessourceMap();


	// Functions for buildings.
	void _defineCityBuildingsSlots();

	// Function defines the m_CityLandscapeType based on the tile on which
	// this city is built upon. 
	// m_CityLandscapeType define the cities CityView layout and/or buildings possibilities.
	void _deriveCityLandscapeType();

	// Regions claiming version 2.0
	/*
	NOTE:
	Primary: for small city that are one tile around him by definition.
	Secondary: ...normal city, tiles are 2 tiles away by def.
	Tertiary: ...big city, tiles are 3 tiles away...
	Quartary: ...huge city, tiles are 4 tiles away...
	*/
	void _claimPrimaryRegions();
	void _claimSecondaryRegions();
	void _claimTertiaryReions();
	void _claimQuartaryRegions();

	// New function for claiming appropriate regions,
	// which are claimed are determined by citytype and -size.
	// ClaimRegions() will call this function.
	void _claimRegions();

	// Cityborder functions.
	void _determineCityBorderTiles();
	void _determineMapTilesBorderDirection();

	// Border helpers.
	bool _isMapTileClaimedByCity(MapTile* maptile);


	// General functions.
	void _deriveCitySprites() {
		switch (m_CityRaceCmp->m_EntityRace)
		{
		case CMPEntityRace::Race::RACE_INVALID:
			break;
		case CMPEntityRace::Race::RACE_HUMAN:
			switch (m_CityType)
			{
			case CityType::CITY_TYPE_FORT:
				m_CitySpritesStorage->m_SmallCitySprite = "fort_human_small";
				m_CitySpritesStorage->m_NormalCitySprite = "fort_human_normal";
				m_CitySpritesStorage->m_BigCitySprite = "fort_human_big";
				m_CitySpritesStorage->m_HugeCitySprite = "fort_human_huge";
				break;
			case CityType::CITY_TYPE_CITY:
				m_CitySpritesStorage->m_SmallCitySprite = "city_human_small";
				m_CitySpritesStorage->m_NormalCitySprite = "city_human_normal";
				m_CitySpritesStorage->m_BigCitySprite = "city_human_big";
				m_CitySpritesStorage->m_HugeCitySprite = "city_human_huge";
				break;

			default:
				break;
			}


			break;
		case CMPEntityRace::Race::RACE_TROLL:
			switch (m_CityType)
			{
			case CityType::CITY_TYPE_FORT:
				m_CitySpritesStorage->m_SmallCitySprite = "fort_troll_small";
				m_CitySpritesStorage->m_NormalCitySprite = "fort_troll_normal";
				m_CitySpritesStorage->m_BigCitySprite = "fort_troll_big";
				m_CitySpritesStorage->m_HugeCitySprite = "fort_troll_huge";
				break;
			case CityType::CITY_TYPE_CITY:
				m_CitySpritesStorage->m_SmallCitySprite = "city_troll_small";
				m_CitySpritesStorage->m_NormalCitySprite = "city_troll_normal";
				m_CitySpritesStorage->m_BigCitySprite = "city_troll_big";
				m_CitySpritesStorage->m_HugeCitySprite = "city_troll_huge";
				break;

			default:
				break;
			}

			break;
		case CMPEntityRace::Race::RACE_DWARF:
			switch (m_CityType)
			{
			case CityType::CITY_TYPE_FORT:
				m_CitySpritesStorage->m_SmallCitySprite = "fort_dwarf_small";
				m_CitySpritesStorage->m_NormalCitySprite = "fort_dwarf_normal";
				m_CitySpritesStorage->m_BigCitySprite = "fort_dwarf_big";
				m_CitySpritesStorage->m_HugeCitySprite = "fort_dwarf_huge";
				break;
			case CityType::CITY_TYPE_CITY:
				m_CitySpritesStorage->m_SmallCitySprite = "city_dwarf_small";
				m_CitySpritesStorage->m_NormalCitySprite = "city_dwarf_normal";
				m_CitySpritesStorage->m_BigCitySprite = "city_dwarf_big";
				m_CitySpritesStorage->m_HugeCitySprite = "city_dwarf_huge";
				break;

			default:
				break;
			}


			break;
		case CMPEntityRace::Race::RACE_ORC:
			switch (m_CityType)
			{
			case CityType::CITY_TYPE_FORT:
				m_CitySpritesStorage->m_SmallCitySprite = "fort_orc_small";
				m_CitySpritesStorage->m_NormalCitySprite = "fort_orc_normal";
				m_CitySpritesStorage->m_BigCitySprite = "fort_orc_big";
				m_CitySpritesStorage->m_HugeCitySprite = "fort_orc_huge";
				break;
			case CityType::CITY_TYPE_CITY:
				m_CitySpritesStorage->m_SmallCitySprite = "city_orc_small";
				m_CitySpritesStorage->m_NormalCitySprite = "city_orc_normal";
				m_CitySpritesStorage->m_BigCitySprite = "city_orc_big";
				m_CitySpritesStorage->m_HugeCitySprite = "city_orc_huge";
				break;

			default:
				break;
			}


			break;
		case CMPEntityRace::Race::RACE_HIGHELF:
			switch (m_CityType)
			{
			case CityType::CITY_TYPE_FORT:
				m_CitySpritesStorage->m_SmallCitySprite = "fort_highelf_small";
				m_CitySpritesStorage->m_NormalCitySprite = "fort_highelf_normal";
				m_CitySpritesStorage->m_BigCitySprite = "fort_highelf_big";
				m_CitySpritesStorage->m_HugeCitySprite = "fort_highelf_huge";
				break;
			case CityType::CITY_TYPE_CITY:
				m_CitySpritesStorage->m_SmallCitySprite = "city_highelf_small";
				m_CitySpritesStorage->m_NormalCitySprite = "city_highelf_normal";
				m_CitySpritesStorage->m_BigCitySprite = "city_highelf_big";
				m_CitySpritesStorage->m_HugeCitySprite = "city_highelf_huge";
				break;

			default:
				break;
			}


			break;
		case CMPEntityRace::Race::RACE_DARKELF:
			switch (m_CityType)
			{
			case CityType::CITY_TYPE_FORT:
				m_CitySpritesStorage->m_SmallCitySprite = "fort_darkelf_small";
				m_CitySpritesStorage->m_NormalCitySprite = "fort_darkelf_normal";
				m_CitySpritesStorage->m_BigCitySprite = "fort_darkelf_big";
				m_CitySpritesStorage->m_HugeCitySprite = "fort_darkelf_huge";
				break;
			case CityType::CITY_TYPE_CITY:
				m_CitySpritesStorage->m_SmallCitySprite = "city_darkelf_small";
				m_CitySpritesStorage->m_NormalCitySprite = "city_darkelf_normal";
				m_CitySpritesStorage->m_BigCitySprite = "city_darkelf_big";
				m_CitySpritesStorage->m_HugeCitySprite = "city_darkelf_huge";
				break;

			default:
				break;
			}


			break;
		case CMPEntityRace::Race::RACE_GOBLIN:
			switch (m_CityType)
			{
			case CityType::CITY_TYPE_FORT:
				m_CitySpritesStorage->m_SmallCitySprite = "fort_goblin_small";
				m_CitySpritesStorage->m_NormalCitySprite = "fort_goblin_normal";
				m_CitySpritesStorage->m_BigCitySprite = "fort_goblin_big";
				m_CitySpritesStorage->m_HugeCitySprite = "fort_goblin_huge";
				break;
			case CityType::CITY_TYPE_CITY:
				m_CitySpritesStorage->m_SmallCitySprite = "city_goblin_small";
				m_CitySpritesStorage->m_NormalCitySprite = "city_goblin_normal";
				m_CitySpritesStorage->m_BigCitySprite = "city_goblin_big";
				m_CitySpritesStorage->m_HugeCitySprite = "city_goblin_huge";
				break;

			default:
				break;
			}


			break;
		case CMPEntityRace::Race::RACE_GNOME:
			switch (m_CityType)
			{
			case CityType::CITY_TYPE_FORT:
				m_CitySpritesStorage->m_SmallCitySprite = "fort_gnome_small";
				m_CitySpritesStorage->m_NormalCitySprite = "fort_gnome_normal";
				m_CitySpritesStorage->m_BigCitySprite = "fort_gnome_big";
				m_CitySpritesStorage->m_HugeCitySprite = "fort_gnome_huge";
				break;
			case CityType::CITY_TYPE_CITY:
				m_CitySpritesStorage->m_SmallCitySprite = "city_gnome_small";
				m_CitySpritesStorage->m_NormalCitySprite = "city_gnome_normal";
				m_CitySpritesStorage->m_BigCitySprite = "city_gnome_big";
				m_CitySpritesStorage->m_HugeCitySprite = "city_gnome_huge";
				break;

			default:
				break;
			}


			break;

		default:
			break;
		}
	}

	void _deriveCityRace(CMPEntityRace::Race race) {
		switch (race)
		{
		case CMPEntityRace::Race::RACE_INVALID:
			break;
		case CMPEntityRace::Race::RACE_HUMAN:
			m_CityRaceCmp->m_EntityRace = CMPEntityRace::Race::RACE_HUMAN;
			m_CityRaceCmp->m_EntityRaceString = "Human";
			break;
		case CMPEntityRace::Race::RACE_TROLL:
			m_CityRaceCmp->m_EntityRace = CMPEntityRace::Race::RACE_TROLL;
			m_CityRaceCmp->m_EntityRaceString = "Troll";

			break;
		case CMPEntityRace::Race::RACE_DWARF:
			m_CityRaceCmp->m_EntityRace = CMPEntityRace::Race::RACE_DWARF;
			m_CityRaceCmp->m_EntityRaceString = "Dwarf";


			break;
		case CMPEntityRace::Race::RACE_ORC:
			m_CityRaceCmp->m_EntityRace = CMPEntityRace::Race::RACE_ORC;
			m_CityRaceCmp->m_EntityRaceString = "Orc";


			break;
		case CMPEntityRace::Race::RACE_HIGHELF:
			m_CityRaceCmp->m_EntityRace = CMPEntityRace::Race::RACE_HIGHELF;
			m_CityRaceCmp->m_EntityRaceString = "High Elf";


			break;
		case CMPEntityRace::Race::RACE_DARKELF:
			m_CityRaceCmp->m_EntityRace = CMPEntityRace::Race::RACE_DARKELF;
			m_CityRaceCmp->m_EntityRaceString = "Dark Elf";


			break;
		case CMPEntityRace::Race::RACE_GOBLIN:
			m_CityRaceCmp->m_EntityRace = CMPEntityRace::Race::RACE_GOBLIN;
			m_CityRaceCmp->m_EntityRaceString = "Goblin";


			break;
		case CMPEntityRace::Race::RACE_GNOME:
			m_CityRaceCmp->m_EntityRace = CMPEntityRace::Race::RACE_GNOME;
			m_CityRaceCmp->m_EntityRaceString = "Gnome";


			break;
		default:
			break;
		}
	}

	void _updateCitySizeClass() {
		if (m_CitySize <= 10) m_CitySizeClass = CitySizeClass::CITY_SIZE_CLASS_SMALL;

		else if (m_CitySize > 10 && m_CitySize <= 20) m_CitySizeClass = CitySizeClass::CITY_SIZE_CLASS_NORMAL;

		else if(m_CitySize > 20 && m_CitySize <= 30) m_CitySizeClass = CitySizeClass::CITY_SIZE_CLASS_BIG;

		else if(m_CitySize > 30) m_CitySizeClass = CitySizeClass::CITY_SIZE_CLASS_HUGE;

		else m_CitySizeClass = CitySizeClass::CITY_SIZE_CLASS_INVALID;
	}


	void _claimRegion(MapTileRegion* region) {
		m_ClaimedRegions.push_back(region);
	}

	bool _isRegionClaimedAlreadyByThisCity(MapTileRegion* region);
	bool _isRegionClaimedByOtherCity(MapTileRegion* region);

	// Call after claiming regions.
	void _setSpriteForClaimedRegion();

	void _unclaimRegions();

	void _determineMapCell(std::string color) {

		if (COMPARE_STRINGS(color, "blue") == 0) {
			m_ClaimedRegionsSpriteName = "map_cell_blue";
			m_CityBorderColor = CityBorderColor::CITY_BORDERCOLOR_BLUE;
		}

		if (COMPARE_STRINGS(color, "red") == 0) {
			m_ClaimedRegionsSpriteName = "map_cell_red";
			m_CityBorderColor = CityBorderColor::CITY_BORDERCOLOR_RED;
		}

		if (COMPARE_STRINGS(color, "magenta") == 0) {
			m_ClaimedRegionsSpriteName = "map_cell_magenta";
			m_CityBorderColor = CityBorderColor::CITY_BORDERCOLOR_MAGENTA;
		}

		if (COMPARE_STRINGS(color, "yellow") == 0) {
			m_ClaimedRegionsSpriteName = "map_cell_yellow";
			m_CityBorderColor = CityBorderColor::CITY_BORDERCOLOR_YELLOW;
		}

		if (COMPARE_STRINGS(color, "green") == 0) {
			m_ClaimedRegionsSpriteName = "map_cell_green";
			m_CityBorderColor = CityBorderColor::CITY_BORDERCOLOR_GREEN;
		}

		if (COMPARE_STRINGS(color, "brown") == 0) {
			m_ClaimedRegionsSpriteName = "map_cell_brown";
			m_CityBorderColor = CityBorderColor::CITY_BORDERCOLOR_BROWN;
		}

		if (COMPARE_STRINGS(color, "orange") == 0) {
			m_ClaimedRegionsSpriteName = "map_cell_orange";
			m_CityBorderColor = CityBorderColor::CITY_BORDERCOLOR_ORANGE;
		}

		if (COMPARE_STRINGS(color, "black") == 0) {
			m_ClaimedRegionsSpriteName = "map_cell_black";
			m_CityBorderColor = CityBorderColor::CITY_BORDERCOLOR_BLACK;
		}
	}
};





// BUILDING STUFF
enum class BuildingTier {
	BUILDING_TIER_INVALID = -1,

	BUILDING_TIER_1 = 0,
	BUILDING_TIER_2 = 1,
	BUILDING_TIER_3 = 2
};

struct BuildingRequirements {
	City::CityBuildingSlotType m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_INVALID;
	std::string m_RaceRequirement;
	int m_PopulationCountRequirement = 0;
	BuildingTier m_BuildingTier = BuildingTier::BUILDING_TIER_INVALID;
};


// Standard baseclass for all buildings.
class Building : public GameEntity {
public:
	virtual ~Building(){}

	City* m_AssociatedCity = nullptr;
	Player* m_AssociatedPlayer = nullptr;
	std::string m_BuildingName;

	std::vector<std::string> m_BuildingsProfession;
private:

};



// Buildings and Technlogyrelalted functions.
typedef std::vector<std::string> BuildingTechRequirementsVec; // For static tech. map.
void InitializeBuildingTechnologyRequirements();
void DeinitializeBuildingTechnologyRequirements();
BuildingTechRequirementsVec* GetTechnologyRequirementsForBuilding(std::string building_name);
BuildingTechRequirementsVec* GetTechnologyRequirementsForBuilding(Building* b);
std::vector<std::string>* GetAvailableBuildingsForTechnology(Technology* t);
std::vector<std::string>* GetAvailableBuildingsForTechnology(std::string t);

// Define appropriate requirements for each in game building...
void InitializeBuildingRequirementsMap();
void DeinitializeBuildingRequirementsMap();

// We check here whether player can build a builing.
bool DoesPlayerCityFulfillRequirementsForBuilding(City* city, std::string building_name, int slot);
std::vector<std::string> *GetAvailableBuildingsForPlayerOnSlot(City* city, int slot);

bool HasPlayerTech(std::string tech, Player* player);
bool HasPlayerNeededTier(BuildingTier tier, Player* player);
bool HasPlayerNeededTier(int tier, Player* player);
int GetBuildingSlotFromPosition(City* city, int xpos, int ypos); // Returns -1 if nothing was found...
Building *MakeNewBuilding(City* city, std::string building_name, int slot);
void DeleteBuilding(City* city, std::string building_name, int slot);

/*
List of Buildings and according Tiers:
Tier 1							Tier 2										Tier 3
council							town hall									mayors palace
local market					big market									merchants quarter
brothel							tavern										taverns quarter
wisemen hut						school										college
shrine							magic school								magic college
inventors hut					small workshop								big workshop
champions hut					military school								military college
shack							stone house									brick house
wooden house					big storage house							city storage
underground storage				masons works.								goldsmiths works.
storage house					brewery
sawmill							smelters works.
tailors works.					armor smiths works.
picklers works.					weapon smiths works.
								tool smiths works.
								ranch

								merchants guild
								fighters guild
								mages guild
								thieves guild
								assassins guild

								baracks
								archery range
								mages tower
								stables

*/

class BuildingShack : public Building {
public:

	BuildingShack(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "shack";

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Shack";

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;
	}


private:


private:
	
};


class BuildingWoodenHouse : public Building {
public:

	BuildingWoodenHouse(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "wooden_house";

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Wooden House";

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;
	}


private:


private:

};



class BuildingStoneHouse : public Building {
public:

	BuildingStoneHouse(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "stone_house";

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Stone House";

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;
	}


private:


private:

};



class BuildingBrickHouse : public Building {
public:

	BuildingBrickHouse(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "brick_house";

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Brick House";

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;
	}


private:


private:

};


class BuildingStorage : public Building {
public:

	BuildingStorage(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "storage";

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Underground Storage";

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;
	}


private:


private:

};


class BuildingWoodenWarehouse : public Building {
public:

	BuildingWoodenWarehouse(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "wooden_storage";

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Wooden Warehouse";

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;
	}


private:


private:

};



class BuildingStoneWarehouse : public Building {
public:

	BuildingStoneWarehouse(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "stone_storage";

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Big Warehouse";

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;
	}


private:


private:

};


class BuildingBrickWarehouse : public Building {
public:

	BuildingBrickWarehouse(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "brick_storage";

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "City Storage";

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;
	}


private:


private:

};


class BuildingWisemenHut : public Building {
public:

	BuildingWisemenHut(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "wisemen_hut";

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Wisemen Hut";
		m_BuildingsProfession.push_back("Civilian Researcher");

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;

		m_GatherableRessourceCmp = new CMPGatherableRessource();
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Civilian Knowledge");
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);
	}


private:


private:

};

/*
class BuildingWoodenSchool : public Building {
public:

	BuildingWoodenSchool(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "wooden_school";

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Small School";

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;


		// Define req.
		m_Requirements = new BuildingRequirements();
		m_Requirements->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
		m_Requirements->m_RaceRequirement = "All";
		m_Requirements->m_PopulationCountRequirement = 5;
		m_BuildingTier = BuildingTier::BUILDING_TIER_1;

	}


private:


private:

};
*/

class BuildingStoneSchool : public Building {
public:

	BuildingStoneSchool(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "stone_school";

		m_IDCmp->m_DynamicTypeName = "Building";
		m_BuildingsProfession.push_back("Researcher");


		m_BuildingName = "Big School";

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;

		m_GatherableRessourceCmp = new CMPGatherableRessource();
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Civilian Knowledge");
		m_GatherableRessourceCmp->m_ProductionYield.push_back(2);
	}


private:


private:

};



class BuildingBrickSchool : public Building {
public:

	BuildingBrickSchool(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "brick_school";

		m_IDCmp->m_DynamicTypeName = "Building";
		m_BuildingsProfession.push_back("Researcher");


		m_BuildingName = "College";

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;

		m_GatherableRessourceCmp = new CMPGatherableRessource();
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Civilian Knowledge");
		m_GatherableRessourceCmp->m_ProductionYield.push_back(4);
	}


private:


private:

};



class BuildingShrine : public Building {
public:

	BuildingShrine(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "shrine";

		m_IDCmp->m_DynamicTypeName = "Building";
		m_BuildingsProfession.push_back("Magick Researcher");


		m_BuildingName = "Shrine";

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;


		m_GatherableRessourceCmp = new CMPGatherableRessource();
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Magick Knowledge");
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);
	}


private:


private:

};


class BuildingMagickSchool : public Building {
public:

	BuildingMagickSchool(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "magick_school";

		m_IDCmp->m_DynamicTypeName = "Building";
		m_BuildingsProfession.push_back("Mage Researcher");


		m_BuildingName = "Magick School";

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;


		m_GatherableRessourceCmp = new CMPGatherableRessource();
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Magick Knowledge");
		m_GatherableRessourceCmp->m_ProductionYield.push_back(2);
	}


private:


private:

};


class BuildingMagickCollege : public Building {
public:

	BuildingMagickCollege(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "magick_college";

		m_IDCmp->m_DynamicTypeName = "Building";
		m_BuildingsProfession.push_back("Mage Researcher");


		m_BuildingName = "Magick College";

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;

		m_GatherableRessourceCmp = new CMPGatherableRessource();
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Magick Knowledge");
		m_GatherableRessourceCmp->m_ProductionYield.push_back(4);
	}


private:


private:

};


class BuildingInventorsHut : public Building {
public:

	BuildingInventorsHut(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "inventors_hut";

		m_IDCmp->m_DynamicTypeName = "Building";
		m_BuildingsProfession.push_back("Technical Researcher");


		m_BuildingName = "Inventors Hut";

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;


		m_GatherableRessourceCmp = new CMPGatherableRessource();
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Technical Knowledge");
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);
	}


private:


private:

};


class BuildingSmallWorkshop : public Building {
public:

	BuildingSmallWorkshop(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "small_workshop";

		m_IDCmp->m_DynamicTypeName = "Building";
		m_BuildingsProfession.push_back("Technical Researcher");


		m_BuildingName = "Small Workshop";

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;

		m_GatherableRessourceCmp = new CMPGatherableRessource();
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Technical Knowledge");
		m_GatherableRessourceCmp->m_ProductionYield.push_back(2);
	}


private:


private:

};


class BuildingBigWorkshop : public Building {
public:

	BuildingBigWorkshop(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "big_workshop";

		m_IDCmp->m_DynamicTypeName = "Building";
		m_BuildingsProfession.push_back("Technical Researcher");


		m_BuildingName = "Big Workshop";

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;


		m_GatherableRessourceCmp = new CMPGatherableRessource();
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Technical Knowledge");
		m_GatherableRessourceCmp->m_ProductionYield.push_back(4);
	}


private:


private:

};



class BuildingChampionsHut : public Building {
public:

	BuildingChampionsHut(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "champions_hut";

		m_IDCmp->m_DynamicTypeName = "Building";
		m_BuildingsProfession.push_back("Military Researcher");


		m_BuildingName = "Champions Hut";

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;


		m_GatherableRessourceCmp = new CMPGatherableRessource();
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Military Knowledge");
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);
	}


private:


private:

};


class BuildingWarriorSchool : public Building {
public:

	BuildingWarriorSchool(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "warrior_school";

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Warrior School";
		m_BuildingsProfession.push_back("Military Researcher");

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;


		m_GatherableRessourceCmp = new CMPGatherableRessource();
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Military Knowledge");
		m_GatherableRessourceCmp->m_ProductionYield.push_back(2);
	}


private:


private:

};



class BuildingMilitaryCollege : public Building {
public:

	BuildingMilitaryCollege(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = ""; // TODO:

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Military College";
		m_BuildingsProfession.push_back("Military Researcher");

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;



		m_GatherableRessourceCmp = new CMPGatherableRessource();
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Military Knowledge");
		m_GatherableRessourceCmp->m_ProductionYield.push_back(4);
	}


private:


private:

};



class BuildingCouncil : public Building {
public:

	BuildingCouncil(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = ""; // TODO:

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Council";
		m_BuildingsProfession.push_back("Aristocrat");

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;
	}


private:


private:

};



class BuildingTownHall : public Building {
public:

	BuildingTownHall(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = ""; // TODO:

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Town Hall";
		m_BuildingsProfession.push_back("Aristocrat");

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;
	}


private:


private:

};


class BuildingMayorsPalace : public Building {
public:

	BuildingMayorsPalace(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = ""; // TODO:

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Mayors Palace";
		m_BuildingsProfession.push_back("Aristocrat");

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;
	}


private:


private:

};


class BuildingLocalMarket : public Building {
public:

	BuildingLocalMarket(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = ""; // TODO:

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Local Market";
		m_BuildingsProfession.push_back("Merchant");

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;


		m_GatherableRessourceCmp = new CMPGatherableRessource();
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Denars");
		m_GatherableRessourceCmp->m_ProductionYield.push_back(10);
	}


private:


private:

};


class BuildingBigMarket : public Building {
public:

	BuildingBigMarket(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = ""; // TODO:

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Big Market";
		m_BuildingsProfession.push_back("Merchant");

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;

		m_GatherableRessourceCmp = new CMPGatherableRessource();
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Denars");
		m_GatherableRessourceCmp->m_ProductionYield.push_back(20);

	}


private:


private:

};



class BuildingMerchantsQuarter : public Building {
public:

	BuildingMerchantsQuarter(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = ""; // TODO:

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Merchants Quarter";
		m_BuildingsProfession.push_back("Merchant");

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;



		m_GatherableRessourceCmp = new CMPGatherableRessource();
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Denars");
		m_GatherableRessourceCmp->m_ProductionYield.push_back(40);
	}


private:


private:

};



class BuildingBrothel : public Building {
public:

	BuildingBrothel(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = ""; // TODO:

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Brothel";

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;
	}


private:


private:

};



class BuildingTavern : public Building {
public:

	BuildingTavern(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = ""; // TODO:

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Tavern";

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;
	}


private:


private:

};


class BuildingTavernsQuarter : public Building {
public:

	BuildingTavernsQuarter(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = ""; // TODO:

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Taverns Quarter";

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;
	}


private:


private:

};




class BuildingMerchantsGuild : public Building {
public:

	BuildingMerchantsGuild(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "merchants_guild";

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Merchants Guild";

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;
	}


private:


private:

};



class BuildingFightersGuild : public Building {
public:

	BuildingFightersGuild(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "fighters_guild";

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Fighters Guild";

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;
	}


private:


private:

};



class BuildingMagesGuild : public Building {
public:

	BuildingMagesGuild(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "mages_guild";

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Mages Guild";

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;
	}


private:


private:

};


class BuildingThievesGuild : public Building {
public:

	BuildingThievesGuild(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "thieves_guild";

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Thieves Guild";

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;
	}


private:


private:

};



class BuildingAssassinsGuild : public Building {
public:

	BuildingAssassinsGuild(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "assassins_guild";

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Assassins Guild";

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;
	}


private:


private:

};



class BuildingCarpentersWorkshop : public Building {
public:

	BuildingCarpentersWorkshop(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "carpenters_workshop";

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Carpenters Workshop";
		m_BuildingsProfession.push_back("Carpenter");


		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;


		// Below definitions mean:
		// From 2 wood we make 1 plank. Same for all buildings below...
		m_GatherableRessourceCmp = new CMPGatherableRessource();
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Planks");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Wood");
		m_GatherableRessourceCmp->m_DemandValue.push_back(2);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);
	}


private:


private:

};


class BuildingBrickmakersWorkshop : public Building {
public:

	BuildingBrickmakersWorkshop(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "brickmakers_workshop";

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Brickmakers Workshop";
		m_BuildingsProfession.push_back("Brickmaker");

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;


		m_GatherableRessourceCmp = new CMPGatherableRessource();
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Bricks");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Clay");
		m_GatherableRessourceCmp->m_DemandValue.push_back(2);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);
	}


private:


private:

};


class BuildingMasonsWorkshop : public Building {
public:

	BuildingMasonsWorkshop(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "masons_workshop";

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Masons Workshop";
		m_BuildingsProfession.push_back("Mason");

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;



		m_GatherableRessourceCmp = new CMPGatherableRessource();
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Stone Blocks");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Raw Stone");
		m_GatherableRessourceCmp->m_DemandValue.push_back(2);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);
	}


private:


private:

};



class BuildingTailorsWorkshop : public Building {
public:

	BuildingTailorsWorkshop(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "tailors_workshop";

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Tailors Workshop";
		m_BuildingsProfession.push_back("Tailor");

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;

		m_GatherableRessourceCmp = new CMPGatherableRessource();
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Clothing");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Leather");
		m_GatherableRessourceCmp->m_DemandValue.push_back(2);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);
	}


private:


private:

};



class BuildingBrewery : public Building {
public:

	BuildingBrewery(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "brewery";

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Brewery";
		m_BuildingsProfession.push_back("Brewer");

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;


		m_GatherableRessourceCmp = new CMPGatherableRessource();
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Alcohol");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Grapes");
		m_GatherableRessourceCmp->m_DemandValue.push_back(2);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);
	}


private:


private:

};


class BuildingGoldsmithsWorkshop : public Building {
public:

	BuildingGoldsmithsWorkshop(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "goldsmiths_workshop";

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Goldsmiths Workshop";
		m_BuildingsProfession.push_back("Goldsmith");

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;


		m_GatherableRessourceCmp = new CMPGatherableRessource();

		// Jewelry production
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Jewelry");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Silver Ore");
		m_GatherableRessourceCmp->m_DemandValue.push_back(1);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(2);


		// Denars production
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Denars");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Gold Bars");
		m_GatherableRessourceCmp->m_DemandValue.push_back(1);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(20);
	}


private:


private:

};



class BuildingArmorSmithsWorkshop : public Building {
public:

	BuildingArmorSmithsWorkshop(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "armorsmiths_workshop";

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Armorsmiths Workshop";
		m_BuildingsProfession.push_back("Armorsmith");

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;


		m_GatherableRessourceCmp = new CMPGatherableRessource();


		// Bronze
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Bronze Armor");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Bronze Bars");
		m_GatherableRessourceCmp->m_DemandValue.push_back(8);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);



		// Iron
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Iron Armor");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Iron Bars");
		m_GatherableRessourceCmp->m_DemandValue.push_back(8);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);



		// Steel
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Steel Armor");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Iron Bars");
		m_GatherableRessourceCmp->m_DemandValue.push_back(16);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);




		// Adamantium
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Adamantium Armor");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Adamantium Bars");
		m_GatherableRessourceCmp->m_DemandValue.push_back(8);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);



		// Malachite
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Malachite Armor");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Malachite Bars");
		m_GatherableRessourceCmp->m_DemandValue.push_back(8);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);


		// Silver
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Silver Armor");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Silver Bars");
		m_GatherableRessourceCmp->m_DemandValue.push_back(2);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);



		// Gold
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Gold Armor");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Gold Bars");
		m_GatherableRessourceCmp->m_DemandValue.push_back(2);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);
	}


private:


private:

};



class BuildingWeaponSmithsWorkshop : public Building {
public:

	BuildingWeaponSmithsWorkshop(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "weaponsmiths_workshop";

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Weaponsmiths Workshop";
		m_BuildingsProfession.push_back("Weaponsmith");

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;


		m_GatherableRessourceCmp = new CMPGatherableRessource();


		// Bronze
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Bronze Weapons");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Bronze Bars");
		m_GatherableRessourceCmp->m_DemandValue.push_back(2);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);



		// Iron
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Iron Weapons");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Iron Bars");
		m_GatherableRessourceCmp->m_DemandValue.push_back(2);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);



		// Steel
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Steel Weapons");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Iron Bars");
		m_GatherableRessourceCmp->m_DemandValue.push_back(4);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);




		// Adamantium
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Adamantium Weapons");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Adamantium Bars");
		m_GatherableRessourceCmp->m_DemandValue.push_back(2);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);



		// Malachite
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Malachite Weapons");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Malachite Bars");
		m_GatherableRessourceCmp->m_DemandValue.push_back(2);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);


		// Silver
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Silver Weapons");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Silver Bars");
		m_GatherableRessourceCmp->m_DemandValue.push_back(2);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);



		// Gold
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Gold Weapons");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Gold Bars");
		m_GatherableRessourceCmp->m_DemandValue.push_back(2);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);
	}


private:


private:

};


class BuildingSmeltersWorkshop : public Building {
public:

	BuildingSmeltersWorkshop(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "smelters_workshop";

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Smelters Workshop";
		m_BuildingsProfession.push_back("Smelter");

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;

		m_GatherableRessourceCmp = new CMPGatherableRessource();


		// Bronze
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Bronze Bars");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Bronze Ore");
		m_GatherableRessourceCmp->m_DemandValue.push_back(4);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);



		// Iron
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Iron Bars");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Iron Ore");
		m_GatherableRessourceCmp->m_DemandValue.push_back(4);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);



		// Steel
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Steel Bars");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Iron Ore");
		m_GatherableRessourceCmp->m_DemandValue.push_back(8);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);




		// Adamantium
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Adamantium Bars");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Adamantium Ore");
		m_GatherableRessourceCmp->m_DemandValue.push_back(4);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);



		// Malachite
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Malachite Bars");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Malachite Ore");
		m_GatherableRessourceCmp->m_DemandValue.push_back(4);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);


		// Silver
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Silver Bars");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Silver Ore");
		m_GatherableRessourceCmp->m_DemandValue.push_back(4);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);



		// Gold
		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Gold Bars");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Gold Ore");
		m_GatherableRessourceCmp->m_DemandValue.push_back(4);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);
	}


private:


private:

};


class BuildingToolSmithsWorkshop : public Building {
public:

	BuildingToolSmithsWorkshop(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "toolsmiths_workshop";

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Toolsmiths Workshop";
		m_BuildingsProfession.push_back("Toolsmith");

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;

		m_GatherableRessourceCmp = new CMPGatherableRessource();


		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Tools");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Bronze Bars");
		m_GatherableRessourceCmp->m_DemandValue.push_back(1);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(2);
	}


private:


private:

};


class BuildingRanch : public Building {
public:

	BuildingRanch(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "ranch";

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Ranch";
		m_BuildingsProfession.push_back("Rancher");

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;


		m_GatherableRessourceCmp = new CMPGatherableRessource();


		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Horses");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Food");
		m_GatherableRessourceCmp->m_DemandValue.push_back(10);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);
	}


private:


private:

};

class BuildingPicklersWorkshop : public Building {
public:

	BuildingPicklersWorkshop(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = "picklers_workshop";

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Picklers Workshop";
		m_BuildingsProfession.push_back("Pickler");

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;


		m_GatherableRessourceCmp = new CMPGatherableRessource();


		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Food");
		m_GatherableRessourceCmp->m_DemandedRawRessourceForProduction.push_back("Salt");
		m_GatherableRessourceCmp->m_DemandValue.push_back(1);
		m_GatherableRessourceCmp->m_ProductionYield.push_back(2);
	}


private:


private:

};


class BuildingBaracks : public Building {
public:

	BuildingBaracks(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = ""; // TODO:

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Baracks";

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;
	}


private:


private:

};


class BuildingArcheryRange : public Building {
public:

	BuildingArcheryRange(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = ""; // TODO:

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Archery Range";

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;
	}


private:


private:

};

class BuildingStables : public Building {
public:

	BuildingStables(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = ""; // TODO:

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Stables";

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;
	}


private:


private:

};



class BuildingMagesTower : public Building {
public:

	BuildingMagesTower(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = ""; // TODO:

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Mages Tower";

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;
	}


private:


private:

};


class BuildingSiegeWorkshop : public Building {
public:

	BuildingSiegeWorkshop(City* associated_city) {

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = "Layer2";
		m_GraphicsCmp->m_SpriteName = ""; // TODO:

		m_IDCmp->m_DynamicTypeName = "Building";


		m_BuildingName = "Siege Workshop";
		m_BuildingsProfession.push_back("Engineer");

		m_AssociatedCity = associated_city;
		m_AssociatedPlayer = m_AssociatedCity->m_AssociatedPlayer;
	}


private:


private:

};



class Hills : public GameEntity {
public:

	Hills(std::string name, std::string layer, int xpos, int ypos) {

		// Forests have transform, graphics, AI, FSM and id.
		m_IDCmp->m_DynamicTypeName = "Hills";

		m_TransformCmp->m_PosX = xpos;
		m_TransformCmp->m_PosY = ypos;

		// This looks like a bug. Check later. Now no errors occuring.
		m_TransformCmp->m_GameWorldSpaceCell[0] = xpos;
		m_TransformCmp->m_GameWorldSpaceCell[1] = ypos;


		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = layer;
		m_GraphicsCmp->m_SpriteName = name;


		m_MovementCostCmp = new CMPMovementCostModifier();
		_setMovementCost();


		m_GatherableRessourceCmp = new CMPGatherableRessource();
		_defineRessourceYield();
	}


private:


private:
	// Function defines which ressource in what amount can be gathered.
	void _defineRessourceYield() {

		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Raw Stone");
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);
	}

	void _setMovementCost() {
		
		// Base cost for moving on hills.
		m_MovementCostCmp->SetBaseMovementCost(2);

		// Race modifiers for moving on hills.
		// Get minuses for moving on hills.
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HUMAN, 1);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_ORC, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HIGHELF, 2);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DARKELF, 2);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_TROLL, 1);

		// Get bonuses for moving on hills.
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GNOME, -1);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DWARF, -1);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GOBLIN, -1);
	}
};




class River : public GameEntity {
public:
	River(std::string spritename, std::string layer, int xpos, int ypos) {
		// Forests have transform, graphics, AI, FSM and id.
		m_IDCmp->m_DynamicTypeName = "River";

		m_TransformCmp->m_PosX = xpos;
		m_TransformCmp->m_PosY = ypos;


		m_GraphicsCmp = new CMPGraphics();
		m_GraphicsCmp->m_DrawingLayer = layer;

		// As we do not dynamically create rivers, we dont have to update theyre sprite based
		// on other rivers around. But we need to set it correctly at the beginning.
		m_GraphicsCmp->m_SpriteName = spritename;


		m_MovementCostCmp = new CMPMovementCostModifier();
		_setMovementCost();
	}


private:

	void _setMovementCost() {
		m_MovementCostCmp->SetBaseMovementCost(1);
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

		m_GatherableRessourceCmp = new CMPGatherableRessource();
		_defineRessourceYield();
	}


private:


private:
	// Function defines which ressource in what amount can be gathered.
	void _defineRessourceYield() {

		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Raw Stone");
		m_GatherableRessourceCmp->m_ProductionYield.push_back(2);

		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Bronze Ore");
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);

		m_GatherableRessourceCmp->m_ProducedRessource.push_back("Iron Ore");
		m_GatherableRessourceCmp->m_ProductionYield.push_back(1);
	}

	void _setMovementCost() {
		// Base cost form oving on mountains.
		m_MovementCostCmp->SetBaseMovementCost(3);

		// Race modifiers..
		// minuses..
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HUMAN, 2);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_ORC, 2);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HIGHELF, 3);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DARKELF, 3);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_TROLL, 3);

		// bonuses...
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GNOME, -2);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DWARF, -2);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GOBLIN, -1);
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


		// Set movement cost after ForestType is define, as
		// we count on its definition.
		m_MovementCostCmp = new CMPMovementCostModifier();
		_setMovementCost();


		m_GatherableRessourceCmp = new CMPGatherableRessource();
		_defineRessourceYield();
	}


	// Update is not meant to be done on each tick, only on occured changes.
	void Update();

	bool HasSameForestClass(Forest* other) {
		return((m_ForestClass == other->m_ForestClass) ? true : false);
	}

	// See whether a city occupies this forest.
	// Thus the forest will not get older.
	bool IsCityOnForest();


	int m_ForestLifeTimeNow = 0;
	int m_ForestLifetime = 0;
	ForestType m_ForestType = ForestType::FOREST_INVALID;
	ForestClass m_ForestClass = ForestClass::FOREST_CLASS_INVALID;

private:


private:
	// Function defines which ressource in what amount can be gathered.
	void _defineRessourceYield() {
		switch (m_ForestType) {
		case ForestType::FOREST_DEEP:
			m_GatherableRessourceCmp->m_ProducedRessource.push_back("Food");
			m_GatherableRessourceCmp->m_ProductionYield.push_back(2);

			m_GatherableRessourceCmp->m_ProducedRessource.push_back("Leather");
			m_GatherableRessourceCmp->m_ProductionYield.push_back(2);

			m_GatherableRessourceCmp->m_ProducedRessource.push_back("Wood");
			m_GatherableRessourceCmp->m_ProductionYield.push_back(6);
			
			break;
		case ForestType::FOREST_NORMAL:
			m_GatherableRessourceCmp->m_ProducedRessource.push_back("Food");
			m_GatherableRessourceCmp->m_ProductionYield.push_back(1);

			m_GatherableRessourceCmp->m_ProducedRessource.push_back("Leather");
			m_GatherableRessourceCmp->m_ProductionYield.push_back(1);

			m_GatherableRessourceCmp->m_ProducedRessource.push_back("Wood");
			m_GatherableRessourceCmp->m_ProductionYield.push_back(4);
			break;
		case ForestType::FOREST_SCARCE:
			m_GatherableRessourceCmp->m_ProducedRessource.push_back("Wood");
			m_GatherableRessourceCmp->m_ProductionYield.push_back(2);
			break;


		default:
			break;
		}
	}

	void _setMovementCost();

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

		m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
		m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;

		
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


		// Basic movements cost for maptiles.
		m_MovementCostCmp = new CMPMovementCostModifier();
		_setMovementCost();


		m_GatherableRessourceCmp = new CMPGatherableRessource();
		_defineRessourceYield();
	}


	void AssociateToMapTileRegion(MapTileRegion* region) {
		if (region == nullptr) return;

		m_AssociatedRegion = region;
	}


	std::vector<GameEntity*>* m_MapTileEntities;
	std::string m_MapTileName = "NULL";
	MapTileType m_MapTileType = MapTileType::MAPTILE_TYPE_INVALID;

	MapTileRegion* m_AssociatedRegion = nullptr;

private:


private:

	// Function defines which ressource in what amount can be gathered.
	void _defineRessourceYield() {
		switch (m_MapTileType) {

		case MapTileType::MAPTILE_TYPE_JUNGLE:
			m_GatherableRessourceCmp->m_ProducedRessource.push_back("Food");
			m_GatherableRessourceCmp->m_ProductionYield.push_back(1);

			m_GatherableRessourceCmp->m_ProducedRessource.push_back("Clay");
			m_GatherableRessourceCmp->m_ProductionYield.push_back(1);

			break;
		case MapTileType::MAPTILE_TYPE_SAVANNAH:
			m_GatherableRessourceCmp->m_ProducedRessource.push_back("Food");
			m_GatherableRessourceCmp->m_ProductionYield.push_back(1);

			m_GatherableRessourceCmp->m_ProducedRessource.push_back("Clay");
			m_GatherableRessourceCmp->m_ProductionYield.push_back(2);
			break;
		case MapTileType::MAPTILE_TYPE_TEMPERATE:
			m_GatherableRessourceCmp->m_ProducedRessource.push_back("Food");
			m_GatherableRessourceCmp->m_ProductionYield.push_back(2);

			m_GatherableRessourceCmp->m_ProducedRessource.push_back("Clay");
			m_GatherableRessourceCmp->m_ProductionYield.push_back(1);
			break;
		case MapTileType::MAPTILE_TYPE_TUNDRA:
			m_GatherableRessourceCmp->m_ProducedRessource.push_back("Food");
			m_GatherableRessourceCmp->m_ProductionYield.push_back(1);

			m_GatherableRessourceCmp->m_ProducedRessource.push_back("Clay");
			m_GatherableRessourceCmp->m_ProductionYield.push_back(1);
			break;
		case MapTileType::MAPTILE_TYPE_WATER_SHALLOW:
			m_GatherableRessourceCmp->m_ProducedRessource.push_back("Food");
			m_GatherableRessourceCmp->m_ProductionYield.push_back(2);

			break;


		default:
			break;
		}
	}

	void _setMovementCost();
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

		if (maptile) {
			m_MapTileRegionTiles.push_back(maptile);

			maptile->AssociateToMapTileRegion(this); // Then tell the maptile that it belongs to this region.
		}
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
	std::vector<GameEntity*>* GetRiversVec() { return m_Riversvec; }
	std::vector<Player*>* GetPlayersVec() { return m_PlayersVec; }
	std::vector<GameEntity*>* GetUnitsVec() { return m_UnitsVec; }
	std::vector<GameEntity*>* GetForestsVec() { return m_ForestsVec; }




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

			// Is it a river?
			if (_isRiver(e)) {
				_addRiver(e);
			}

			// Is it a unit?
			if (_isUnit(e)) {
				_addUnit(e);

				// Workaround. Store units in players vec too.
				// They are deleted from here too.
				Unit* unit = reinterpret_cast<Unit*>(e);
				_addUnitToPlayer(e, unit->m_AssociatedPlayer);
			}

			// Is Forest?
			if (_isForest(e)) {
				_addForest(e);
			}

			// Is Buildin?
			if (_isBuilding(e)) {
				_addBuilding(e);
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


		// Delete rivers
		if (_isRiver(e)) {

			std::vector< GameEntity* >::iterator it = std::find( m_Riversvec->begin(), m_Riversvec->end(), e);

			if (it != m_Riversvec->end()) {
				m_Riversvec->erase(it);
			}
		}

		// Delete units
		if (_isUnit(e)) {

			std::vector< GameEntity* >::iterator it = std::find(m_UnitsVec->begin(), m_UnitsVec->end(), e);

			if (it != m_UnitsVec->end()) {
				m_UnitsVec->erase(it);
			}


			// Workaround. Delete units from players vec too.
			Unit* unit = reinterpret_cast<Unit*>(e);
			_deleteUnitFromPlayer(e, unit->m_AssociatedPlayer);
		}


		// Delete Forests
		if (_isForest(e)) {

			std::vector< GameEntity* >::iterator it = std::find(m_ForestsVec->begin(), m_ForestsVec->end(), e);

			if (it != m_ForestsVec->end()) {
				m_ForestsVec->erase(it);
			}
		}

		// Delete Buildings
		if (_isBuilding(e)) {

			std::vector< GameEntity* >::iterator it = std::find(m_BuildingsVec->begin(), m_BuildingsVec->end(), e);

			if (it != m_BuildingsVec->end()) {
				m_BuildingsVec->erase(it);
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


	std::vector<GameEntity*>* m_ForestsVec; // Holds all forests in game.
	std::vector<GameEntity*>* m_Riversvec; // Holds all rivers in game.
	std::vector< GameEntity*>* m_MapTileGameEntitiesVec; // Vector that explicitly hold Maptiles. 
	std::vector< GameEntity* >* m_GameEntitiesVec; // Holds all entities ingame.
	std::vector<GameEntity*>* m_GameEntitiesWithAIVec; // Holds entities in game with AI.
	std::vector<GameEntity*>* m_MapViewRessourcesVec; // Holds all ressources in game, that are explicitly on the mapview.
	std::vector<GameEntity*>* m_CityVec; // Holds all cities in the game.
	std::vector<GameEntity*>* m_MapTileRegionsVec; // Holds all regions defined in game.
	std::vector<GameEntity*>* m_MountainsHillsVec; // Holds all hills and mountains in game.
	std::vector<Player*>* m_PlayersVec; // Holds all player of the game.
	std::vector<GameEntity*>* m_UnitsVec; // Holds all units ingame.
	std::vector<GameEntity*>* m_BuildingsVec; // Holds all buildings ingame.


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
		m_Riversvec = new std::vector<GameEntity*>();
		m_UnitsVec = new std::vector<GameEntity*>();
		m_ForestsVec = new std::vector<GameEntity*>();
		m_BuildingsVec = new std::vector<GameEntity*>();

		m_PlayersVec = new std::vector<Player*>();
	}

	bool _isUnit(GameEntity* e) {
		if (COMPARE_STRINGS(e->m_IDCmp->m_DynamicTypeName, "Unit") == 0) {
			return true;
		}
		else {
			return false;
		}
	}

	bool _isRiver(GameEntity* e) {
		if (COMPARE_STRINGS(e->m_IDCmp->m_DynamicTypeName, "River") == 0) {
			return true;
		}
		else {
			return false;
		}
	}

	bool _isBuilding(GameEntity* e) {
		return(COMPARE_STRINGS(e->m_IDCmp->m_DynamicTypeName, "Building") == 0);
	}

	void _addUnitToPlayer(GameEntity* e, Player* p);

	void _deleteUnitFromPlayer(GameEntity* e, Player* p);

	void _addForest(GameEntity* e) {
		m_ForestsVec->push_back(e);
	}

	void _addUnit(GameEntity* e) {
		m_UnitsVec->push_back(e);
	}

	void _addBuilding(GameEntity* e) {
		m_BuildingsVec->push_back(e);
	}

	void _addRiver(GameEntity* e) {
		m_Riversvec->push_back(e);
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


	bool _isForest(GameEntity* e) {
		if (e != nullptr) {
			if (COMPARE_STRINGS(e->m_IDCmp->m_DynamicTypeName, "Forest") == 0) return true;
		}

		return false;
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
	Player(std::string playername, std::string playercolor, CMPEntityRace::Race race) {
		
		// NOTE:
		// We explicitly set a race for a player,
		// as player can only instantiate certain types of cities and units 
		// associated with this race.

		m_PlayerName = playername;
		m_PlayerColor = playercolor;
		m_PlayerEmpireRace = race;
		m_PlayerUnits = std::vector<Unit*>();
		m_PlayerCities = std::vector<City*>();



		_initStandardResearchedTech();
	}

	void AddCity(City* c) {
		m_PlayerCities.push_back(c);
	}

	void AddUnit(Unit* u) {
		m_PlayerUnits.push_back(u);
	}

	std::string GetPlayersRace();

	// Function researches randomly one of the base technologies of tech trees.
	void RandomlyResearchBaseTechnology();


	std::string m_PlayerName;
	std::string m_PlayerColor;
	std::vector<City*> m_PlayerCities;
	std::vector<Unit*> m_PlayerUnits;


	CMPEntityRace::Race m_PlayerEmpireRace;

	// Currently selected unit in mapview.
	Unit* m_CurrentlySelectedUnit = nullptr;

	// The city, in which the player is currently "in".
	City* m_CurrentlyViewedCity = nullptr;

	// Currently hovered over entity in cityview.
	GameEntity* m_CurrentlyHoveredEntityInCity = nullptr;

	// FogOfWar related.
	int m_MapVisibility[MAP_SIZE][MAP_SIZE];

	// Technology
	std::map<std::string, int> m_PlayersTechnologies; // 1 for researched, 0 for not researched.
	TechTier m_PlayerTechnologyTier = TechTier::TECH_TIER_INVALID;

private:


private:

	void _initMapVisibilityMatrix();

	bool _isMapTileSurroundedByOwnTiles(MapTile* tile);
	bool _belongMapTileToThisPlayer(MapTile* tile);

	// This function is based on the race of the player.
	void _initStandardResearchedTech();
};