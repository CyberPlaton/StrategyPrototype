// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "GameEntity.h"

EntitiesStorage* EntitiesStorage::m_EntitiesStorage = nullptr;
WorldMap* WorldMap::m_WorldMapInstance = nullptr;

// Map stores tech. requirements for a given building.
static std::map<std::string, BuildingTechRequirementsVec*> g_pBuildingTechRequirementsMap; 

static std::map<std::string, BuildingRequirements*> g_pBuildingsRequirementsMap;


void InitializeBuildingRequirementsMap() {

	BuildingRequirements* req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_1;
	req->m_PopulationCountRequirement = 1;

	g_pBuildingsRequirementsMap.emplace("Shack", req);


	// Reuse pointer-object for other buildings.
	req = nullptr;



	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_1;
	req->m_PopulationCountRequirement = 5;

	g_pBuildingsRequirementsMap.emplace("Wooden House", req);

	req = nullptr;




	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_2;
	req->m_PopulationCountRequirement = 10;

	g_pBuildingsRequirementsMap.emplace("Stone House", req);

	req = nullptr;






	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_3;
	req->m_PopulationCountRequirement = 20;

	g_pBuildingsRequirementsMap.emplace("Brick House", req);

	req = nullptr;




	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_1;
	req->m_PopulationCountRequirement = 5;

	g_pBuildingsRequirementsMap.emplace("Underground Storage", req);

	req = nullptr;





	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_1;
	req->m_PopulationCountRequirement = 1;

	g_pBuildingsRequirementsMap.emplace("Underground Storage", req);

	req = nullptr;





	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_1;
	req->m_PopulationCountRequirement = 5;

	g_pBuildingsRequirementsMap.emplace("Wooden Warehouse", req);

	req = nullptr;






	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_2;
	req->m_PopulationCountRequirement = 10;

	g_pBuildingsRequirementsMap.emplace("Big Warehouse", req);

	req = nullptr;





	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_3;
	req->m_PopulationCountRequirement = 20;

	g_pBuildingsRequirementsMap.emplace("City Storage", req);

	req = nullptr;




	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_1;
	req->m_PopulationCountRequirement = 1;

	g_pBuildingsRequirementsMap.emplace("Wisemen Hut", req);

	req = nullptr;





	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_2;
	req->m_PopulationCountRequirement = 10;

	g_pBuildingsRequirementsMap.emplace("Big School", req);

	req = nullptr;






	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_2;
	req->m_PopulationCountRequirement = 20;

	g_pBuildingsRequirementsMap.emplace("College", req);

	req = nullptr;





	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_1;
	req->m_PopulationCountRequirement = 5;

	g_pBuildingsRequirementsMap.emplace("Shrine", req);

	req = nullptr;





	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_2;
	req->m_PopulationCountRequirement = 10;

	g_pBuildingsRequirementsMap.emplace("Magick School", req);

	req = nullptr;




	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_3;
	req->m_PopulationCountRequirement = 20;

	g_pBuildingsRequirementsMap.emplace("Magick College", req);

	req = nullptr;





	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_1;
	req->m_PopulationCountRequirement = 5;

	g_pBuildingsRequirementsMap.emplace("Inventors Hut", req);

	req = nullptr;




	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_2;
	req->m_PopulationCountRequirement = 10;

	g_pBuildingsRequirementsMap.emplace("Small Workshop", req);

	req = nullptr;





	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_3;
	req->m_PopulationCountRequirement = 20;

	g_pBuildingsRequirementsMap.emplace("Big Workshop", req);

	req = nullptr;



	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_1;
	req->m_PopulationCountRequirement = 5;

	g_pBuildingsRequirementsMap.emplace("Champions Hut", req);

	req = nullptr;




	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_2;
	req->m_PopulationCountRequirement = 10;

	g_pBuildingsRequirementsMap.emplace("Warrior School", req);

	req = nullptr;




	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_1;
	req->m_PopulationCountRequirement = 5;

	g_pBuildingsRequirementsMap.emplace("Picklers Workshop", req);

	req = nullptr;



	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_2;
	req->m_PopulationCountRequirement = 10;

	g_pBuildingsRequirementsMap.emplace("Ranch", req);

	req = nullptr;



	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_2;
	req->m_PopulationCountRequirement = 10;

	g_pBuildingsRequirementsMap.emplace("Toolsmiths Workshop", req);

	req = nullptr;



	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_2;
	req->m_PopulationCountRequirement = 10;

	g_pBuildingsRequirementsMap.emplace("Smelters Workshop", req);

	req = nullptr;



	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_2;
	req->m_PopulationCountRequirement = 10;

	g_pBuildingsRequirementsMap.emplace("Weaponsmiths Workshop", req);

	req = nullptr;



	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_2;
	req->m_PopulationCountRequirement = 10;

	g_pBuildingsRequirementsMap.emplace("Armorsmiths Workshop", req);

	req = nullptr;



	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_3;
	req->m_PopulationCountRequirement = 20;

	g_pBuildingsRequirementsMap.emplace("Goldsmiths Workshop", req);

	req = nullptr;



	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_2;
	req->m_PopulationCountRequirement = 10;

	g_pBuildingsRequirementsMap.emplace("Brewery", req);

	req = nullptr;


	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_2;
	req->m_PopulationCountRequirement = 10;

	g_pBuildingsRequirementsMap.emplace("Tailors Workshop", req);

	req = nullptr;



	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_2;
	req->m_PopulationCountRequirement = 10;

	g_pBuildingsRequirementsMap.emplace("Masons Workshop", req);

	req = nullptr;



	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_3;
	req->m_PopulationCountRequirement = 20;

	g_pBuildingsRequirementsMap.emplace("Brickmakers Workshop", req);

	req = nullptr;




	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_1;
	req->m_PopulationCountRequirement = 5;

	g_pBuildingsRequirementsMap.emplace("Carpenters Workshop", req);

	req = nullptr;




	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_3;
	req->m_PopulationCountRequirement = 20;

	g_pBuildingsRequirementsMap.emplace("Taverns Quarter", req);

	req = nullptr;



	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_2;
	req->m_PopulationCountRequirement = 10;

	g_pBuildingsRequirementsMap.emplace("Tavern", req);

	req = nullptr;




	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_1;
	req->m_PopulationCountRequirement = 5;

	g_pBuildingsRequirementsMap.emplace("Brothel", req);

	req = nullptr;



	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_3;
	req->m_PopulationCountRequirement = 20;

	g_pBuildingsRequirementsMap.emplace("Merchants Quarter", req);

	req = nullptr;




	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_2;
	req->m_PopulationCountRequirement = 10;

	g_pBuildingsRequirementsMap.emplace("Big Market", req);

	req = nullptr;



	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_1;
	req->m_PopulationCountRequirement = 5;

	g_pBuildingsRequirementsMap.emplace("Local Market", req);

	req = nullptr;




	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_3;
	req->m_PopulationCountRequirement = 20;

	g_pBuildingsRequirementsMap.emplace("Mayors Palace", req);

	req = nullptr;



	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_2;
	req->m_PopulationCountRequirement = 10;

	g_pBuildingsRequirementsMap.emplace("Town Hall", req);

	req = nullptr;



	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_1;
	req->m_PopulationCountRequirement = 5;

	g_pBuildingsRequirementsMap.emplace("Council", req);

	req = nullptr;



	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_3;
	req->m_PopulationCountRequirement = 20;

	g_pBuildingsRequirementsMap.emplace("Military College", req);

	req = nullptr;





	// GUILDS
	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_2;
	req->m_PopulationCountRequirement = 30;

	g_pBuildingsRequirementsMap.emplace("Assassins Guild", req);

	req = nullptr;




	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_2;
	req->m_PopulationCountRequirement = 30;

	g_pBuildingsRequirementsMap.emplace("Thieves Guild", req);

	req = nullptr;




	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_2;
	req->m_PopulationCountRequirement = 30;

	g_pBuildingsRequirementsMap.emplace("Mages Guild", req);

	req = nullptr;



	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_2;
	req->m_PopulationCountRequirement = 30;

	g_pBuildingsRequirementsMap.emplace("Fighters Guild", req);

	req = nullptr;



	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_2;
	req->m_PopulationCountRequirement = 30;

	g_pBuildingsRequirementsMap.emplace("Merchants Guild", req);

	req = nullptr;





	// MILITARY BUILDINGS.
	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_2;
	req->m_PopulationCountRequirement = 10;

	g_pBuildingsRequirementsMap.emplace("Siege Workshop", req);

	req = nullptr;


	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_2;
	req->m_PopulationCountRequirement = 10;

	g_pBuildingsRequirementsMap.emplace("Mages Tower", req);

	req = nullptr;



	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_2;
	req->m_PopulationCountRequirement = 10;

	g_pBuildingsRequirementsMap.emplace("Stables", req);

	req = nullptr;




	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_2;
	req->m_PopulationCountRequirement = 10;

	g_pBuildingsRequirementsMap.emplace("Archery Range", req);

	req = nullptr;




	req = new BuildingRequirements();
	req->m_BuildingSlotType = City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD;
	req->m_RaceRequirement = "All";
	req->m_BuildingTier = BuildingTier::BUILDING_TIER_2;
	req->m_PopulationCountRequirement = 10;

	g_pBuildingsRequirementsMap.emplace("Baracks", req);

	req = nullptr;
}



void DeinitializeBuildingRequirementsMap() {

	g_pBuildingsRequirementsMap.clear();
}



void DeinitializeBuildingTechnologyRequirements(){

	g_pBuildingTechRequirementsMap.clear();
}

void InitializeBuildingTechnologyRequirements() {

	BuildingTechRequirementsVec *vec = new BuildingTechRequirementsVec();
	g_pBuildingTechRequirementsMap.emplace("Shack", vec); // vec has size == 0, thus no req.


	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Wood Working");
	g_pBuildingTechRequirementsMap.emplace("Wooden House", vec);



	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Stone Working");
	g_pBuildingTechRequirementsMap.emplace("Stone House", vec);



	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Brick Making");
	g_pBuildingTechRequirementsMap.emplace("Brick House", vec);



	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	g_pBuildingTechRequirementsMap.emplace("Underground Storage", vec);



	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Wood Working");
	g_pBuildingTechRequirementsMap.emplace("Wooden House", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Wood Working");
	g_pBuildingTechRequirementsMap.emplace("Wooden Warehouse", vec);



	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Stone Working");
	vec->push_back("Pottery");
	g_pBuildingTechRequirementsMap.emplace("Stone Warehouse", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Brick Working");
	g_pBuildingTechRequirementsMap.emplace("City Storage", vec);



	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Wisemen Circle");
	g_pBuildingTechRequirementsMap.emplace("Wisemen Hut", vec);



	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Alphabet");
	g_pBuildingTechRequirementsMap.emplace("Small School", vec);



	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Writing");
	g_pBuildingTechRequirementsMap.emplace("Big School", vec);



	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Literture");
	g_pBuildingTechRequirementsMap.emplace("College", vec);



	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Ceremony");
	g_pBuildingTechRequirementsMap.emplace("Shrine", vec);



	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Elementalism");
	g_pBuildingTechRequirementsMap.emplace("Magick School", vec);



	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Polytheism");
	g_pBuildingTechRequirementsMap.emplace("Magick College", vec);



	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Wood Working");
	g_pBuildingTechRequirementsMap.emplace("Inventors Hut", vec);



	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Architecture");
	vec->push_back("Tool Making");
	g_pBuildingTechRequirementsMap.emplace("Small Workshop", vec);



	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Iron Working");
	vec->push_back("Brick Making");
	g_pBuildingTechRequirementsMap.emplace("Big Workshop", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Honor");
	g_pBuildingTechRequirementsMap.emplace("Champions Hut", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Warfare Theory");
	g_pBuildingTechRequirementsMap.emplace("Warrior School", vec);






	// MILITARY BUILDINGS
	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Siege Craft");
	g_pBuildingTechRequirementsMap.emplace("Siege Workshop", vec);


	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Magical Warfare");
	g_pBuildingTechRequirementsMap.emplace("Mages Tower", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Mounted Warfare");
	g_pBuildingTechRequirementsMap.emplace("Stables", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Archery");
	g_pBuildingTechRequirementsMap.emplace("Archery Range", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Warfare Theory");
	g_pBuildingTechRequirementsMap.emplace("Baracks", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Salting");
	g_pBuildingTechRequirementsMap.emplace("Picklers Workshop", vec);



	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Animal Husbandry");
	g_pBuildingTechRequirementsMap.emplace("Ranch", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Tool Making");
	g_pBuildingTechRequirementsMap.emplace("Toolsmiths Workshop", vec);



	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Bronze Working");
	g_pBuildingTechRequirementsMap.emplace("Smelters Workshop", vec);



	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Bronze Working");
	g_pBuildingTechRequirementsMap.emplace("Weaponsmiths Workshop", vec);





	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Bronze Working");
	g_pBuildingTechRequirementsMap.emplace("Armorsmiths Workshop", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Jewelry");
	g_pBuildingTechRequirementsMap.emplace("Goldsmiths Workshop", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Alcohol Making");
	g_pBuildingTechRequirementsMap.emplace("Brewery", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Clothing");
	g_pBuildingTechRequirementsMap.emplace("Tailors Workshop", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Stone Working");
	g_pBuildingTechRequirementsMap.emplace("Masons Workshop", vec);





	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Brick Making");
	g_pBuildingTechRequirementsMap.emplace("Brickmakers Workshop", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Wood Working");
	g_pBuildingTechRequirementsMap.emplace("Carpenters Workshop", vec);



	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Aggressive Stance");
	g_pBuildingTechRequirementsMap.emplace("Assassins Guild", vec);



	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Aggressive Stance");
	g_pBuildingTechRequirementsMap.emplace("Thieves Guild", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Knowledge Of Magicka");
	g_pBuildingTechRequirementsMap.emplace("Mages Guild", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Aggressive Stance");
	g_pBuildingTechRequirementsMap.emplace("Fighters Guild", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Trade");
	g_pBuildingTechRequirementsMap.emplace("Merchants Guild", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Alcohol Brewing");
	g_pBuildingTechRequirementsMap.emplace("Taverns Quarter", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Beverage Making");
	g_pBuildingTechRequirementsMap.emplace("Tavern", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("All"); // Meaning free for all... 
	g_pBuildingTechRequirementsMap.emplace("Brothel", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Trade");
	g_pBuildingTechRequirementsMap.emplace("Merchants Quarter", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Currency");
	g_pBuildingTechRequirementsMap.emplace("Big Market", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Bartering");
	g_pBuildingTechRequirementsMap.emplace("Local Market", vec);





	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Philosophy");
	g_pBuildingTechRequirementsMap.emplace("Mayors Palace", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Council");
	g_pBuildingTechRequirementsMap.emplace("Town Hall", vec);





	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Council");
	g_pBuildingTechRequirementsMap.emplace("Council", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Aggressive Stance");
	g_pBuildingTechRequirementsMap.emplace("Military College", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Warfare Theory");
	g_pBuildingTechRequirementsMap.emplace("Warrior School", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Honor");
	g_pBuildingTechRequirementsMap.emplace("Champions Hut", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Iron Making");
	g_pBuildingTechRequirementsMap.emplace("Big Workshop", vec);



	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Architecture");
	g_pBuildingTechRequirementsMap.emplace("Small Workshop", vec);



	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Wood Working");
	g_pBuildingTechRequirementsMap.emplace("Inventors Hut", vec);



	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Polytheism");
	g_pBuildingTechRequirementsMap.emplace("Magick College", vec);



	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Mysticism");
	g_pBuildingTechRequirementsMap.emplace("Magick School", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Ceremony");
	g_pBuildingTechRequirementsMap.emplace("Shrine", vec);



	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Literature");
	g_pBuildingTechRequirementsMap.emplace("College", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Writing");
	g_pBuildingTechRequirementsMap.emplace("Big School", vec);




	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Wisemen Circle");
	g_pBuildingTechRequirementsMap.emplace("Wisemen Hut", vec);





	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Brick Making");
	g_pBuildingTechRequirementsMap.emplace("City Storage", vec);



	vec = nullptr;
	vec = new BuildingTechRequirementsVec();

	vec->push_back("Stone Working");
	vec->push_back("Pottery");
	g_pBuildingTechRequirementsMap.emplace("Big Warehouse", vec);

}

BuildingTechRequirementsVec *GetTechnologyRequirementsForBuilding(std::string building_name) {

	try {
		return g_pBuildingTechRequirementsMap.at(building_name);
	}
	catch (const char* err) {
		// print error.
	}

	return nullptr;
}

BuildingTechRequirementsVec *GetTechnologyRequirementsForBuilding(Building* b) {

	try {
		return g_pBuildingTechRequirementsMap.at(b->m_BuildingName);

	}
	catch (const char* err) {
		// print error.
	}

	return nullptr;
}


std::vector<std::string>* GetAvailableBuildingsForTechnology(Technology* t) {

	std::vector<std::string>* vec = new std::vector<std::string>();

	for (auto it : g_pBuildingTechRequirementsMap) {

		for (auto itr : *it.second) {

			if (COMPARE_STRINGS_2(t->m_TechName, itr) == 0) {

				vec->push_back(it.first);
			}
		}
	}

	return vec;
}

std::vector<std::string>* GetAvailableBuildingsForTechnology(std::string t) {

	std::vector<std::string>* vec = new std::vector<std::string>();

	for (auto it : g_pBuildingTechRequirementsMap) {

		for (auto itr : *it.second) {

			if (COMPARE_STRINGS_2(t, itr) == 0) {

				vec->push_back(it.first);
			}
		}
	}

	return vec;
}


void Player::RandomlyResearchBaseTechnology() {

	using namespace std;

	// Check whether all tech trees are unlocked.
	if (m_PlayersTechnologies.at("Ceremony") == 1 &&
		m_PlayersTechnologies.at("Honor") == 1 &&
		m_PlayersTechnologies.at("Wood Working") == 1 &&
		m_PlayersTechnologies.at("Wisemen Circle") == 1) {

		return; // Everything set up, do  nothing.
	}


	// First, determine randomly which tech tree to unlock.
	int r = Random() % TECH_TREE_COUNT; // 0-3.

	switch (r) {
	case 0: // Check for magicka
		if (m_PlayersTechnologies.at("Ceremony") == 1) { // Already researched, do nothing.
			return;
		}
		else {
			int r2 = Random() % 100;

			if (r2 >= 90) {
				m_PlayersTechnologies.at("Ceremony") = 1;

				cout << color(colors::GREEN);
				cout << "\"" << m_PlayerName << "s\" Empire managed to unlock a base technologie: \"Ceremony\".\n" << endl;
				cout << "This makes research in \"Magicka\" possible.\n" << white << endl;
			}
		}
		break;

	case 1: // Technical
		if (m_PlayersTechnologies.at("Wood Working") == 1) { // Already researched, do nothing.
			return;
		}
		else {
			int r2 = Random() % 100;

			if (r2 >= 90) {
				m_PlayersTechnologies.at("Wood Working") = 1;

				cout << color(colors::GREEN);
				cout << "\"" << m_PlayerName << "s\" Empire managed to unlock a base technologie: \"Wood Working\".\n" << endl;
				cout << "This makes research in \"Technical\" possible.\n" << white << endl;
			}
		}
		break;

	case 2: // Military
		if (m_PlayersTechnologies.at("Honor") == 1) { // Already researched, do nothing.
			return;
		}
		else {
			int r2 = Random() % 100;

			if (r2 >= 90) {
				m_PlayersTechnologies.at("Honor") = 1;

				cout << color(colors::GREEN);
				cout << "\"" << m_PlayerName << "s\" Empire managed to unlock a base technologie: \"Honor\".\n" << endl;
				cout << "This makes research in \"Military\" possible.\n" << white << endl;
			}
		}
		break;

	case 3: // Civilian
		if (m_PlayersTechnologies.at("Wisemen Circle") == 1) { // Already researched, do nothing.
			return;
		}
		else {
			int r2 = Random() % 100;

			if (r2 >= 90) {
				m_PlayersTechnologies.at("Wisemen Circle") = 1;

				cout << color(colors::GREEN);
				cout << "\"" << m_PlayerName << "s\" Empire managed to unlock a base technologie: \"Wisemen Circle\".\n" << endl;
				cout << "This makes research in \"Civilian\" possible.\n" << white << endl;
			}
		}
		break;

	default:
		break;
	}
}

void Player::_initStandardResearchedTech() {

	using namespace std;

	TechnologyTree* tech_tree = TechnologyTree::Get();

	CMPEntityRace race = m_PlayerEmpireRace;

	// Insert all defined technologies for player sepcific race.
	for (auto it : tech_tree->GetTechnologyMap()) {

		if (COMPARE_STRINGS(it.second->m_TechRace, "All") == 0 ||
			COMPARE_STRINGS_2(it.second->m_TechRace, race.m_EntityRaceString) == 0) {

			m_PlayersTechnologies.emplace(it.first, 0);
		}
	}


	// Define researched techs for players based on race...

	switch (m_PlayerEmpireRace) {
	case CMPEntityRace::Race::RACE_DARKELF:

		// Darkelfs are magically oriented race..
		// In that they are going more into warfare.
		m_PlayersTechnologies.at("Ceremony") = 1;
		m_PlayersTechnologies.at("Mysticism") = 1;
		m_PlayersTechnologies.at("Elementalism") = 1;

		// And as such they get no bonuses for other techs.

		break;


	case CMPEntityRace::Race::RACE_DWARF:

		// Dwarfs are more merchants type,
		// and basically non-violent aligned.
		m_PlayersTechnologies.at("Bartering") = 1;
		m_PlayersTechnologies.at("Currency") = 1;

		break;

	case CMPEntityRace::Race::RACE_GNOME:

		// Gnomes are technically inclined.
		m_PlayersTechnologies.at("Wood Working") = 1;
		m_PlayersTechnologies.at("Stone Working") = 1;


		break;
	
	case CMPEntityRace::Race::RACE_GOBLIN:

		// Goblins are technically inclined.
		m_PlayersTechnologies.at("Wood Working") = 1;
		m_PlayersTechnologies.at("Stone Working") = 1;


		break;
	
	case CMPEntityRace::Race::RACE_HIGHELF:

		// Highelfs are magically inclined and more "holy"-like...
		m_PlayersTechnologies.at("Ceremony") = 1;
		m_PlayersTechnologies.at("Mysticism") = 1;
		m_PlayersTechnologies.at("Restoration") = 1;


		break;
	
	case CMPEntityRace::Race::RACE_HUMAN:

		// Humans are militaristic inclined, but more "good"..
		m_PlayersTechnologies.at("Honor") = 1;

		// As humans are more "good" they are more civilized...
		m_PlayersTechnologies.at("Wisemen Circle") = 1;


		break;
	
	case CMPEntityRace::Race::RACE_ORC:

		// Orcs are militaristic but more "evil"...
		// Thus they do not receive a civilized bonus, but more bonuses for warfare...
		m_PlayersTechnologies.at("Honor") = 1;
		m_PlayersTechnologies.at("Warrior Code") = 1;

		m_PlayersTechnologies.at("Hunting") = 1;


		break;
	
	case CMPEntityRace::Race::RACE_TROLL:

		// Trolls are more merchants type and aggressive against others..
		// Thus they receive a bonus to "civilian" and "military".
		m_PlayersTechnologies.at("Bartering") = 1;
		m_PlayersTechnologies.at("Currency") = 1;

		break;


	default:
		cout << color(colors::RED);
		cout << "Race for Player \"" << m_PlayerName << "\" was not set." << white << endl;
		return;
	}



	m_PlayerTechnologyTier = TechTier::TECH_TIER_1;
}


void Unit::_defineUnitName() {

	switch (m_EntityRaceCmp->m_EntityRace) {
	case CMPEntityRace::Race::RACE_INVALID:
		break;
	case CMPEntityRace::Race::RACE_HUMAN:
		m_Name = UnitNames::Get()->GetRandomHumanName();
		break;
	case CMPEntityRace::Race::RACE_TROLL:
		m_Name = UnitNames::Get()->GetRandomTrollName();

		break;
	case CMPEntityRace::Race::RACE_DWARF:
		m_Name = UnitNames::Get()->GetRandomDwarfName();

		break;
	case CMPEntityRace::Race::RACE_ORC:
		m_Name = UnitNames::Get()->GetRandomOrcName();

		break;
	case CMPEntityRace::Race::RACE_HIGHELF:
		m_Name = UnitNames::Get()->GetRandomHighelfName();

		break;
	case CMPEntityRace::Race::RACE_DARKELF:
		m_Name = UnitNames::Get()->GetRandomDarkelfName();

		break;
	case CMPEntityRace::Race::RACE_GOBLIN:
		m_Name = UnitNames::Get()->GetRandomGoblinName();

		break;
	case CMPEntityRace::Race::RACE_GNOME:
		m_Name = UnitNames::Get()->GetRandomGnomeName();

		break;
	default:
		break;
	}
	

}

/*
bool Unit::SetDerivedStats() {

	if (this->m_EntityRaceCmp == nullptr) return false;
	if (COMPARE_STRINGS(m_Birthsign, "NULL") == 0) return false;
	if (m_UnitClass == nullptr) return false;


	_defineStatsBasedOnUnitRace();
	_defineStatsBasedOnUnitBirthsign();
	_defineDerivedAttributes();

	return true;
}
*/

/*
void Unit::_defineRandomUnitTalents() {

	// NOTE:
	// We define 1 attribute and 1 skill to be increased or decreased with 0-5 Points.
	// Samewise, we do the same with 1 other attribute and 1 other skill, but revert the value...

	using namespace std;

	// Randomize attributes
	int random_index_attr = Random() % GetUnitAttributes()->size();
	int random_index_attr_2 = Random() % GetUnitAttributes()->size();


	// Randomize skills
	int random_index_skills = Random() % GetUnitSkills()->size();
	int random_index_skills_2 = Random() % GetUnitSkills()->size();



	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();


	int random_value = 1 + Random() % 6;
	int random_direction = random_value % 2;

	if (random_direction == 0) {
		random_value = (-random_value);


		// Attribute 1
		UnitAttributesEnum a = UnitAttributesEnum(random_index_attr);
		attr->SetAttribute(GetUnitAttributes(), AttributeToString(a), random_value);

		// Skill 1
		UnitSkillsEnum s = UnitSkillsEnum(random_index_skills);
		skills->SetSkill(GetUnitSkills(), SkillToString(s), random_value);


		// Attribute 2
		UnitAttributesEnum aa = UnitAttributesEnum(random_index_attr_2);
		attr->SetAttribute(GetUnitAttributes(), AttributeToString(aa), -random_value);

		// Skill 2
		UnitSkillsEnum ss = UnitSkillsEnum(random_index_skills_2);
		skills->SetSkill(GetUnitSkills(), SkillToString(ss), -random_value);


		cout << color(colors::DARKRED) << endl;
		cout << "Random Talent: Attribute \"" << AttributeToString(a) << "\" ::= " << std::to_string(random_value) << endl;
		cout << "Random Talent: Skill \"" << SkillToString(s) << "\" ::= " << std::to_string(random_value) << endl;
		cout << "Random Talent: Attribute \"" << AttributeToString(aa) << "\" ::= " << std::to_string(-random_value) << endl;
		cout << "Random Talent: Skill \"" << SkillToString(ss) << "\" ::= " << std::to_string(-random_value) << endl;
		cout << white << endl;


	}
	else {

		// Attribute 1
		UnitAttributesEnum a = UnitAttributesEnum(random_index_attr);
		attr->SetAttribute(GetUnitAttributes(), AttributeToString(a), random_value);

		// Skill 1
		UnitSkillsEnum s = UnitSkillsEnum(random_index_skills);
		skills->SetSkill(GetUnitSkills(), SkillToString(s), random_value);


		// Attribute 2
		UnitAttributesEnum aa = UnitAttributesEnum(random_index_attr_2);
		attr->SetAttribute(GetUnitAttributes(), AttributeToString(aa), -random_value);

		// Skill 2
		UnitSkillsEnum ss = UnitSkillsEnum(random_index_skills_2);
		skills->SetSkill(GetUnitSkills(), SkillToString(ss), -random_value);


		cout << color(colors::DARKRED) << endl;
		cout << "Random Talent: Attribute \"" << AttributeToString(a) << "\" ::= " << std::to_string(random_value) << endl;
		cout << "Random Talent: Skill \"" << SkillToString(s) << "\" ::= " << std::to_string(random_value) << endl;
		cout << "Random Talent: Attribute \"" << AttributeToString(aa) << "\" ::= " << std::to_string(-random_value) << endl;
		cout << "Random Talent: Skill \"" << SkillToString(ss) << "\" ::= " << std::to_string(-random_value) << endl;
		cout << white << endl;
	}

}
*/

GameEntity::~GameEntity() {

	delete m_IDCmp; m_IDCmp = nullptr;
	delete m_TransformCmp; m_TransformCmp = nullptr;
	delete m_PhysicsCmp; m_PhysicsCmp = nullptr;
	delete m_GraphicsCmp; m_GraphicsCmp = nullptr;
	delete m_FSM; m_FSM = nullptr;
	delete m_MovementCostCmp; m_MovementCostCmp = nullptr;
	delete m_EntityRaceCmp; m_EntityRaceCmp = nullptr;
}


void Forest::_setMovementCost() {

	// Set base cost
	switch (m_ForestType) {
	case ForestType::FOREST_DEEP:
		// Base cost for a deepforest...
		m_MovementCostCmp->SetBaseMovementCost(3);
		break;


	default:
		// Base cost for Normal, Dying and Scarce.
		m_MovementCostCmp->SetBaseMovementCost(2);
		break;
	}



	switch (m_ForestType) {
	case ForestType::FOREST_DEEP:

		// Race modifiers..
		// bonuses..
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HIGHELF, -2);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DARKELF, -2);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_TROLL, -2);


		// minuses...
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HUMAN, 1);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_ORC, 1);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GNOME, 3);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DWARF, 3);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GOBLIN, 3);

		break;
	case ForestType::FOREST_NORMAL:

		// bonuses...
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HIGHELF, -1);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DARKELF, -1);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_TROLL, -1);


		// minuses...
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HUMAN, 1);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_ORC, 1);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GNOME, 2);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DWARF, 2);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GOBLIN, 2);

		break;
	case ForestType::FOREST_SCARCE:

		// bonuses...
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HIGHELF, -1);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DARKELF, -1);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_TROLL, -1);


		// minuses...
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HUMAN, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_ORC, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GNOME, 1);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DWARF, 1);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GOBLIN, 1);
		break;
	case ForestType::FOREST_DYING:

		// Race modifiers..
		// bonuses..
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HIGHELF, -1);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DARKELF, -1);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_TROLL, -1);


		// minuses...
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HUMAN, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_ORC, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GNOME, 1);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DWARF, 1);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GOBLIN, 1);
		break;
	default:
		break;
	}
}


void MapTile::_setMovementCost() {

	switch (m_MapTileType) {
	case MapTileType::MAPTILE_TYPE_ICE:
		m_MovementCostCmp->SetBaseMovementCost(10);
		break;
	case  MapTileType::MAPTILE_TYPE_SAND:
		m_MovementCostCmp->SetBaseMovementCost(10);
		break;
	case MapTileType::MAPTILE_TYPE_SNOW:
		m_MovementCostCmp->SetBaseMovementCost(4);
		break;
	case MapTileType::MAPTILE_TYPE_WATER_DEEP:
		m_MovementCostCmp->SetBaseMovementCost(4);
		break;

	default:
		// Shallow water, Temperate, Savannah, Jungle, Tundra.
		m_MovementCostCmp->SetBaseMovementCost(2);
		break;
	}


	switch (m_MapTileType) {
	case MapTileType::MAPTILE_TYPE_ICE:
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HUMAN, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_ORC, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HIGHELF, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DARKELF, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_TROLL, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GNOME, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DWARF, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GOBLIN, 0);

		break;
	case  MapTileType::MAPTILE_TYPE_JUNGLE:
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HUMAN, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_ORC, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HIGHELF, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DARKELF, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_TROLL, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GNOME, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DWARF, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GOBLIN, 0);

		break;
	case  MapTileType::MAPTILE_TYPE_SAND:
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HUMAN, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_ORC, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HIGHELF, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DARKELF, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_TROLL, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GNOME, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DWARF, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GOBLIN, 0);
		break;
	case MapTileType::MAPTILE_TYPE_SAVANNAH:
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HUMAN, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_ORC, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HIGHELF, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DARKELF, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_TROLL, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GNOME, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DWARF, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GOBLIN, 0);
		break;

	case MapTileType::MAPTILE_TYPE_SNOW:
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HUMAN, 2);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_ORC, 2);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HIGHELF, 2);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DARKELF, 2);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_TROLL, 2);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GNOME, 2);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DWARF, 2);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GOBLIN, 2);

		break;
	case MapTileType::MAPTILE_TYPE_TEMPERATE:
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HUMAN, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_ORC, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HIGHELF, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DARKELF, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_TROLL, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GNOME, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DWARF, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GOBLIN, 0);

		break;
	case MapTileType::MAPTILE_TYPE_TUNDRA:
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HUMAN, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_ORC, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HIGHELF, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DARKELF, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_TROLL, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GNOME, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DWARF, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GOBLIN, 0);
		break;
	case MapTileType::MAPTILE_TYPE_WATER_DEEP:
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HUMAN, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_ORC, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HIGHELF, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DARKELF, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_TROLL, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GNOME, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DWARF, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GOBLIN, 0);

		break;
	case MapTileType::MAPTILE_TYPE_WATER_SHALLOW:
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HUMAN, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_ORC, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_HIGHELF, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DARKELF, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_TROLL, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GNOME, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_DWARF, 0);
		m_MovementCostCmp->SetRaceSpecificMovementCostModifier(CMPEntityRace::Race::RACE_GOBLIN, 0);
		break;

	default:
		break;
	}
}


/*
void Unit::_defineStandardBeginningStats() {

	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_HEAVY_ARMOR, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_MEDIUM_ARMOR, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_LIGHT_ARMOR, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_SPEAR, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_AXE, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_BLUNT_WEAPON, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_LONG_BLADE, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_SHORT_BLADE, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_BLOCK, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_MARKSMAN, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_ACROBATICS, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_ATHLETICS, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_SNEAK, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_UNARMORED, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_ILLUSION, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_MERCANTILE, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_SPEECHCRAFT, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_ALCHEMY, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_CONJURATION, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_ENCHANT, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_ALTERATION, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_DESTRUCTION, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_MYSTICISM, 8));
	GetUnitSkills()->insert(std::make_pair(UnitSkillsEnum::UNIT_SKILL_RESTORATION, 8));


	GetUnitAttributes()->insert(std::make_pair(UnitAttributesEnum::UNIT_ATTRIBUTE_STRENGTH, 8));
	GetUnitAttributes()->insert(std::make_pair(UnitAttributesEnum::UNIT_ATTRIBUTE_INTELLIGENCE, 8));
	GetUnitAttributes()->insert(std::make_pair(UnitAttributesEnum::UNIT_ATTRIBUTE_WILLPOWER, 8));
	GetUnitAttributes()->insert(std::make_pair(UnitAttributesEnum::UNIT_ATTRIBUTE_AGILITY, 8));
	GetUnitAttributes()->insert(std::make_pair(UnitAttributesEnum::UNIT_ATTRIBUTE_SPEED, 8));
	GetUnitAttributes()->insert(std::make_pair(UnitAttributesEnum::UNIT_ATTRIBUTE_ENDURANCE, 8));
	GetUnitAttributes()->insert(std::make_pair(UnitAttributesEnum::UNIT_ATTRIBUTE_PERSONALITY, 8));

	GetUnitAttributes()->insert(std::make_pair(UnitAttributesEnum::UNIT_ATTRIBUTE_HEALTH, 10));
	GetUnitAttributes()->insert(std::make_pair(UnitAttributesEnum::UNIT_ATTRIBUTE_MAGICKA, 10));
	GetUnitAttributes()->insert(std::make_pair(UnitAttributesEnum::UNIT_ATTRIBUTE_FATIGUE, 10));

	
	_defineRandomUnitTalents();
}
*/

/*
void Unit::_defineDerivedAttributes() {

	_getHealth();
	_getMagicka();
	_getFatigue();
}
*/

/*
int Unit::_getFatigue() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Define Fatigue.
	// .. define multiplier
	int fatigue_multiplier = 1;
	if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_HIGHELF) {
		fatigue_multiplier += 0.2f;
	}
	else if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_ORC) {
		fatigue_multiplier += 1;
	}
	else if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_DWARF) {
		fatigue_multiplier += 0.7f;
	}
	else if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_TROLL) {
		fatigue_multiplier += 1.5f;
	}
	else if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_GNOME) {
		fatigue_multiplier -= 0.5f;
	}
	else if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_DWARF) {
		fatigue_multiplier -= 0.5f;
	}
	else if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_GOBLIN) {
		fatigue_multiplier -= 0.5f;
	}


	int strength = GetUnitAttributes()->at(UnitAttributesEnum::UNIT_ATTRIBUTE_STRENGTH);
	int endurance = GetUnitAttributes()->at(UnitAttributesEnum::UNIT_ATTRIBUTE_ENDURANCE);
	int athletics = GetUnitSkills()->at(UnitSkillsEnum::UNIT_SKILL_ATHLETICS);
	int acrobatics = GetUnitSkills()->at(UnitSkillsEnum::UNIT_SKILL_ACROBATICS);

	int fatigue = int(fatigue_multiplier * (int(strength + endurance + (athletics / 2) + (acrobatics / 2)) / 2));


	attr->SetAttribute(GetUnitAttributes(), "Fatigue", fatigue);
	return fatigue;
}

int Unit::_getMagicka() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();

	// Define multiplier..
	// .. based on race.
	int multiplier = 1;
	if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_HIGHELF) {
		multiplier += 1;
	}
	else if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_DARKELF) {
		multiplier += 0.5f;
	}
	else if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_ORC) {
		multiplier -= 0.5f;
	}
	else if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_DWARF) {
		multiplier -= 0.5f;
	}
	else if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_GOBLIN) {
		multiplier -= 0.5f;
	}
	else if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_GNOME) {
		multiplier -= 0.5f;
	}

	// .. based on birthsign.
	if (COMPARE_STRINGS(this->m_Birthsign, "The Mage") == 0) {
		multiplier += 0.5f;
	}
	else if (COMPARE_STRINGS(this->m_Birthsign, "The Sorcerer") == 0) {
		multiplier += 1.0f;
	}
	else if (COMPARE_STRINGS(this->m_Birthsign, "The Ritual") == 0) {
		multiplier += 0.3f;
	}

	int intelligence = GetUnitAttributes()->at(UnitAttributesEnum::UNIT_ATTRIBUTE_INTELLIGENCE);
	int willpower = GetUnitAttributes()->at(UnitAttributesEnum::UNIT_ATTRIBUTE_WILLPOWER);

	int magicka = int(multiplier * (intelligence + willpower) / 2);
	attr->SetAttribute(GetUnitAttributes(), "Magicka", magicka);

	return magicka;
}

int Unit::_getHealth() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();


	// Define health.
	// .. define multiplier
	int health_multiplier = 1;
	if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_HIGHELF) {
		health_multiplier -= 0.5f;
	}
	else if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_ORC) {
		health_multiplier += 1;
	}
	else if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_DWARF) {
		health_multiplier += 1.0f;
	}
	else if (this->m_EntityRaceCmp->m_EntityRace == CMPEntityRace::Race::RACE_TROLL) {
		health_multiplier += 1;
	}


	int strength = GetUnitAttributes()->at(UnitAttributesEnum::UNIT_ATTRIBUTE_STRENGTH);
	int endurance = GetUnitAttributes()->at(UnitAttributesEnum::UNIT_ATTRIBUTE_ENDURANCE);

	int health = int((strength * health_multiplier + endurance) / 2);
	attr->SetAttribute(GetUnitAttributes(), "Health", health);

	return health;
}
*/


/*
void  Unit::_defineStatsBasedOnUnitBirthsign() {


	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();


	if (COMPARE_STRINGS(this->m_Birthsign, "The Warrior") == 0) {


		attr->SetAttribute(GetUnitAttributes(), "Strength", 10);
		attr->UnsetAttribute(GetUnitAttributes(), "Intelligence", 5);

	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Mage") == 0) {

		attr->SetAttribute(GetUnitAttributes(), "Magicka", 20);
		attr->SetAttribute(GetUnitAttributes(), "Intelligence", 5);

		attr->UnsetAttribute(GetUnitAttributes(), "Strength", 5);

	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Thief") == 0) {

		attr->SetAttribute(GetUnitAttributes(), "Speed", 5);
		skills->SetSkill(GetUnitSkills(), "Sneak", 10);

		skills->UnsetSkill(GetUnitSkills(), "Personality", 10);

	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Tower") == 0) {


		attr->SetAttribute(GetUnitAttributes(), "Health", 10);
		attr->SetAttribute(GetUnitAttributes(), "Speed", 2);
		skills->SetSkill(GetUnitSkills(), "Sneak", 5);

	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Lover") == 0) {

		attr->SetAttribute(GetUnitAttributes(), "Personality", 10);

	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Guard") == 0) {


		attr->SetAttribute(GetUnitAttributes(), "Health", 15);
		attr->SetAttribute(GetUnitAttributes(), "Strength", 5);
		attr->SetAttribute(GetUnitAttributes(), "Endurance", 5);

		skills->SetSkill(GetUnitSkills(), "Heavy Armor", 10);
		skills->UnsetSkill(GetUnitSkills(), "Sneak", 10);

	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Sorcerer") == 0) {

		attr->SetAttribute(GetUnitAttributes(), "Intelligence", 5);
		attr->SetAttribute(GetUnitAttributes(), "Magicka", 5);

		skills->SetSkill(GetUnitSkills(), "Destruction", 10);
		skills->UnsetSkill(GetUnitSkills(), "Heavy Armor", 10);
	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Shadow") == 0) {

		attr->SetAttribute(GetUnitAttributes(), "Speed", 10);
		attr->SetAttribute(GetUnitAttributes(), "Health", 5);

		skills->SetSkill(GetUnitSkills(), "Unarmored", 5);
		skills->UnsetSkill(GetUnitSkills(), "Sneak", 20);
	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Lightfeet") == 0) {

		attr->SetAttribute(GetUnitAttributes(), "Speed", 20);
		attr->SetAttribute(GetUnitAttributes(), "Endurance", 5);

		attr->UnsetAttribute(GetUnitAttributes(), "Strength", 5);
		attr->UnsetAttribute(GetUnitAttributes(), "Health", 5);


		skills->SetSkill(GetUnitSkills(), "Athletics", 15);
		skills->SetSkill(GetUnitSkills(), "Acrobatics", 10);

		skills->UnsetSkill(GetUnitSkills(), "Heavy Armor", 15);
		skills->UnsetSkill(GetUnitSkills(), "Medium Armor", 10);

	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Ritual") == 0) {

		skills->SetSkill(GetUnitSkills(), "Mysticism", 15);

	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Paladin") == 0) {

		skills->SetSkill(GetUnitSkills(), "Heavy Armor", 20);
		skills->SetSkill(GetUnitSkills(), "Personality", 15);

		attr->SetAttribute(GetUnitAttributes(), "Strength", 5);

		skills->UnsetSkill(GetUnitSkills(), "Light Armor", 10);
		skills->UnsetSkill(GetUnitSkills(), "Sneak", 20);
	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Mechanist") == 0) {

		attr->SetAttribute(GetUnitAttributes(), "Intelligence", 10);

	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Ignorant") == 0) {

		attr->UnsetAttribute(GetUnitAttributes(), "Intelligence", 10);

	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Lord") == 0) {

		attr->SetAttribute(GetUnitAttributes(), "Intelligence", 5);
		attr->SetAttribute(GetUnitAttributes(), "Personality", 20);

		attr->UnsetAttribute(GetUnitAttributes(), "Speed", 10);
		attr->UnsetAttribute(GetUnitAttributes(), "Willpower", 5);

		skills->UnsetSkill(GetUnitSkills(), "Short Sword", 5);
		skills->UnsetSkill(GetUnitSkills(), "Axe", 5);
		skills->UnsetSkill(GetUnitSkills(), "Blunt Weapon", 5);
		skills->UnsetSkill(GetUnitSkills(), "Spear", 5);

	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Protector") == 0) {
		
		skills->SetSkill(GetUnitSkills(), "Short Sword", 5);
		skills->SetSkill(GetUnitSkills(), "Axe", 5);
		skills->SetSkill(GetUnitSkills(), "Blunt Weapon", 5);
		skills->SetSkill(GetUnitSkills(), "Spear", 5);

	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Stubborn") == 0) {

		attr->UnsetAttribute(GetUnitAttributes(), "Intelligence", 20);
		attr->UnsetAttribute(GetUnitAttributes(), "Magicka", 10);

		attr->SetAttribute(GetUnitAttributes(), "Endurance", 20);
		attr->SetAttribute(GetUnitAttributes(), "Strength", 5);


	}


	else if (COMPARE_STRINGS(this->m_Birthsign, "The Serpent") == 0) {

		attr->SetAttribute(GetUnitAttributes(), "Intelligence", 50);
		attr->SetAttribute(GetUnitAttributes(), "Willpower", 25);

		skills->SetSkill(GetUnitSkills(), "Sneak", 25);
		skills->SetSkill(GetUnitSkills(), "Mysticism", 25);
		skills->SetSkill(GetUnitSkills(), "Destruction", 25);
	}
}
*/

/*
void Unit::_defineStatsBasedOnUnitRace() {

	UnitAttributes* attr = new UnitAttributes();
	UnitSkills* skills = new UnitSkills();


	if (m_EntityRaceCmp == nullptr) return;

	float intelligence_multiplier = 1.0f;
	int intelligence = 0;


	switch (m_EntityRaceCmp->m_EntityRace) {
		{
	case CMPEntityRace::Race::RACE_INVALID:
		break;
	case CMPEntityRace::Race::RACE_HUMAN:


		intelligence_multiplier = 0.65f;
		intelligence = GetUnitAttributes()->at(UnitAttributesEnum::UNIT_ATTRIBUTE_INTELLIGENCE);
		intelligence = 0.5f + intelligence * intelligence_multiplier;

		// Bonuses
		attr->SetAttribute(m_UnitAttributesMap, "Intelligence", intelligence);



		attr->SetAttribute(m_UnitAttributesMap, "Strength", 2);
		attr->SetAttribute(m_UnitAttributesMap, "Personality", 5);

		// Minuses
		attr->UnsetAttribute(m_UnitAttributesMap, "Endurance", 3);



		
		skills->SetSkill(m_UnitSkillsMap, "Light Armor", 10);
		skills->SetSkill(m_UnitSkillsMap, "Long Blade", 10);
		skills->SetSkill(m_UnitSkillsMap, "Restoration", 5);
		skills->SetSkill(m_UnitSkillsMap, "Destruction", 5);
		skills->SetSkill(m_UnitSkillsMap, "Medium Armor", 5);


		break;
	case CMPEntityRace::Race::RACE_TROLL:
		// Bonuses
		attr->SetAttribute(m_UnitAttributesMap, "Strength", 5);
		attr->SetAttribute(m_UnitAttributesMap, "Agility", 5);

		// Minuses
		// none.


		skills->SetSkill(m_UnitSkillsMap, "Unarmored", 10);
		skills->SetSkill(m_UnitSkillsMap, "Short Blade", 5);
		skills->SetSkill(m_UnitSkillsMap, "Mercantile", 10);
		skills->SetSkill(m_UnitSkillsMap, "Speechcraft", 5);
		skills->SetSkill(m_UnitSkillsMap, "Acrobatics", 5);

		break;
	case CMPEntityRace::Race::RACE_DWARF:
		// Bonuses
		attr->SetAttribute(m_UnitAttributesMap, "Endurance", 5);
		attr->SetAttribute(m_UnitAttributesMap, "Strength", 5);
		attr->SetAttribute(m_UnitAttributesMap, "Personality", 5);

		// Minuses
		attr->UnsetAttribute(m_UnitAttributesMap, "Agility", 5);


		skills->SetSkill(m_UnitSkillsMap, "Mercantile", 10);
		skills->SetSkill(m_UnitSkillsMap, "Blunt Weapon", 10);
		skills->SetSkill(m_UnitSkillsMap, "Heavy Armor", 10);
		skills->SetSkill(m_UnitSkillsMap, "Athletics", 5);
		skills->SetSkill(m_UnitSkillsMap, "Axe", 5);

		break;
	case CMPEntityRace::Race::RACE_ORC:
		// Bonuses
		attr->SetAttribute(m_UnitAttributesMap, "Strength", 10);
		attr->SetAttribute(m_UnitAttributesMap, "Endurance", 7);

		// Minuses
		attr->UnsetAttribute(m_UnitAttributesMap, "Intelligence", 4);


		skills->SetSkill(m_UnitSkillsMap, "Medium Armor", 10);
		skills->SetSkill(m_UnitSkillsMap, "Axe", 10);
		skills->SetSkill(m_UnitSkillsMap, "Heavy Armor", 10);
		skills->SetSkill(m_UnitSkillsMap, "Block", 5);
		skills->SetSkill(m_UnitSkillsMap, "Mysticism", 5);

		break;
	case CMPEntityRace::Race::RACE_HIGHELF:
		// Bonuses
		attr->SetAttribute(m_UnitAttributesMap, "Intelligence", 10);
		attr->SetAttribute(m_UnitAttributesMap, "Agility", 3);

		// Minuses
		attr->UnsetAttribute(m_UnitAttributesMap, "Strength", 3);


		skills->SetSkill(m_UnitSkillsMap, "Medium Armor", 5);
		skills->SetSkill(m_UnitSkillsMap, "Restoration", 10);
		skills->SetSkill(m_UnitSkillsMap, "Illusion", 5);
		skills->SetSkill(m_UnitSkillsMap, "Conjuration", 10);
		skills->SetSkill(m_UnitSkillsMap, "Enchant", 5);

		break;
	case CMPEntityRace::Race::RACE_DARKELF:
		// Bonuses
		attr->SetAttribute(m_UnitAttributesMap, "Speed", 7);
		attr->SetAttribute(m_UnitAttributesMap, "Agility", 10);

		// Minuses
		attr->UnsetAttribute(m_UnitAttributesMap, "Personality", 2);


		skills->SetSkill(m_UnitSkillsMap, "Light Armor", 5);
		skills->SetSkill(m_UnitSkillsMap, "Destruction", 10);
		skills->SetSkill(m_UnitSkillsMap, "Mysticism", 10);
		skills->SetSkill(m_UnitSkillsMap, "Conjuration", 5);
		skills->SetSkill(m_UnitSkillsMap, "Short Blade", 5);

		break;
	case CMPEntityRace::Race::RACE_GOBLIN:
		// Bonuses
		attr->SetAttribute(m_UnitAttributesMap, "Intelligence", 10);
		attr->SetAttribute(m_UnitAttributesMap, "Personality", 4);

		// Minuses
		attr->UnsetAttribute(m_UnitAttributesMap, "Strength", 5);


		skills->SetSkill(m_UnitSkillsMap, "Light Armor", 5);
		skills->SetSkill(m_UnitSkillsMap, "Illusion", 10);
		skills->SetSkill(m_UnitSkillsMap, "Speechcraft", 5);
		skills->SetSkill(m_UnitSkillsMap, "Alteration", 10);
		skills->SetSkill(m_UnitSkillsMap, "Conjuration", 5);

		break;
	case CMPEntityRace::Race::RACE_GNOME:
		// Bonuses
		attr->SetAttribute(m_UnitAttributesMap, "Intelligence", 10);
		attr->SetAttribute(m_UnitAttributesMap, "Agility", 5);
		attr->SetAttribute(m_UnitAttributesMap, "Speed", 3);

		// Minuses
		attr->UnsetAttribute(m_UnitAttributesMap, "Strength", 5);


		skills->SetSkill(m_UnitSkillsMap, "Unarmored", 10);
		skills->SetSkill(m_UnitSkillsMap, "Illusion", 5);
		skills->SetSkill(m_UnitSkillsMap, "Mysticism", 5);
		skills->SetSkill(m_UnitSkillsMap, "Alteration", 10);
		skills->SetSkill(m_UnitSkillsMap, "Short Blade", 5);

		break;
	default:
		break;
		}
	}
}
*/


void Unit::_defineMaxAge() {

	int r = Random() % 10;
	int r3 = Random() % 10;

	int r2 = Random() % 2;

	if (r2 == 0) {
		m_MaxAge = 70 + r + r3;
	}
	else {
		m_MaxAge = 70 - r - r3;

	}
}



void Unit::Update() {

	// Reset Movement Points.
	m_MovementPoints = 6;

	int x = m_AgeInternal; // Flag.
	m_AgeInternal = (m_AgeInternal + 1) % 4;

	// One year lived...
	if (x == 3 && m_AgeInternal == 0) {
		m_Age++;
	}

	if (m_Age > m_MaxAge) {

		Die();
	}
}


bool Unit::SetBirthsign() {
	m_Birthsign = YearCounter::Get()->GetCurrentBirthsign();

	return (COMPARE_STRINGS(m_Birthsign, "") == 0) ? false : true;
}


bool Unit::SetPlayer(Player* p) {
	m_AssociatedPlayer = p;
	if (m_AssociatedPlayer) _determineUnitRibbonColor();

	return (m_AssociatedPlayer == nullptr) ? false : true;
}


void Unit::MoveTo(int x_cell, int y_cell) {
	this->MoveTo(x_cell, y_cell, m_MovementCostStorage);
}


void City::RemoveCitizenFromJoblessVector(GameEntity* unit) {

	std::vector<GameEntity*>::iterator it = std::find(m_GarrisonedUnits.begin(), m_GarrisonedUnits.end(), unit);

	if (it != m_GarrisonedUnits.end()) {

		m_GarrisonedUnits.erase(it);
	}
}

bool City::AddCitizenToJobless(GameEntity* unit) {

	if (m_GarrisonedUnits.size() < JOBLESS_CITIZENS_COUNT) {

		if (m_GarrisonedUnits.size() == 0) {

			unit->m_TransformCmp->m_PosX = 702;
			unit->m_TransformCmp->m_PosY = 650;
			this->m_GarrisonedUnits.push_back(unit);
		}
		else {

			int xpos = 0, ypos = 0;
			for (auto it : this->m_GarrisonedUnits) {
				xpos = it->m_TransformCmp->m_PosX;
				ypos = it->m_TransformCmp->m_PosY;
			}

			unit->m_TransformCmp->m_PosX = 32 + xpos;
			unit->m_TransformCmp->m_PosY = ypos;
			this->m_GarrisonedUnits.push_back(unit);
		}


		return true;
	}
	else {
		return false;
	}
}


Unit::Unit(CMPEntityRace::Race race, UnitMovementType movement_type, int xpos, int ypos, int set_x_cell, int set_y_cell) {

	m_IDCmp->m_DynamicTypeName = "Unit";

	_setUnitMovementType(movement_type);

	m_TransformCmp->m_PosX = xpos;
	m_TransformCmp->m_PosY = ypos;
	m_TransformCmp->m_GameWorldSpaceCell[0] = set_x_cell;
	m_TransformCmp->m_GameWorldSpaceCell[1] = set_y_cell;

	m_TransformCmp->m_Height = SPRITES_WIDTH_AND_HEIGHT;
	m_TransformCmp->m_Width = SPRITES_WIDTH_AND_HEIGHT;


	m_GraphicsCmp = new CMPGraphics();
	m_GraphicsCmp->m_DrawingLayer = "layer1";

	m_EntityRaceCmp = new CMPEntityRace(race);

	_defineMaxAge();

	/*
	m_UnitSkillsMap = new std::map<UnitSkillsEnum, int>();
	m_UnitAttributesMap = new std::map<UnitAttributesEnum, int>();
	*/

	// Stats and Skills.
	//_defineStandardBeginningStats();

	// Define name.
	_defineUnitName();

	// Define AI for unit.
	m_AICmp = new CMPArtificialIntelligence(this);

	// We need to map according state functions first, else we get errors.
	// Like:
	// forest->m_AICmp->MapState("state_search", new ForestSearch(*forest->m_AICmp));

	_mapStates();
	m_AICmp->ChangeState(States::STATE_WAIT);
}


bool Unit::SetClass(std::string classname) {

	if (COMPARE_STRINGS(classname, "Citizen") == 0) {
		m_UnitClass = new UnitCitizen();
	}
	else if (COMPARE_STRINGS(classname, "Scout") == 0) {
		//m_UnitClass = new UnitScout();
	}
	else if (COMPARE_STRINGS(classname, "Woodcutter") == 0) {
		m_UnitClass = new UnitWoodCutter();
	}
	else if (COMPARE_STRINGS(classname, "Farmer") == 0) {
		m_UnitClass = new UnitFarmer();
	}
	else if (COMPARE_STRINGS(classname, "Hunter") == 0) {
		m_UnitClass = new UnitHunter();
	}
	else if (COMPARE_STRINGS(classname, "Fisher") == 0) {
		m_UnitClass = new UnitFisher();
	}
	else if (COMPARE_STRINGS(classname, "Brick Burner") == 0) {
		m_UnitClass = new UnitBrickBurner();
	}
	else if (COMPARE_STRINGS(classname, "Carpenter") == 0) {
		m_UnitClass = new UnitCarpenter();
	}
	else if (COMPARE_STRINGS(classname, "Gatherer") == 0) {
		m_UnitClass = new UnitGatherer();
	}

	else if (COMPARE_STRINGS(classname, "Bronze Miner") == 0) {
		m_UnitClass = new UnitBronzeMiner();
	}
	else if (COMPARE_STRINGS(classname, "Iron Miner") == 0) {
		m_UnitClass = new UnitIronMiner();
	}
	else if (COMPARE_STRINGS(classname, "Malachite Miner") == 0) {
		m_UnitClass = new UnitMalachiteMiner();
	}
	else if (COMPARE_STRINGS(classname, "Adamantium Miner") == 0) {
		m_UnitClass = new UnitAdamantiumMiner();
	}
	else if (COMPARE_STRINGS(classname, "Stone Miner") == 0) {
		m_UnitClass = new UnitStoneMiner();
	}
	else if (COMPARE_STRINGS(classname, "Salt Miner") == 0) {
		m_UnitClass = new UnitSaltMiner();
	}
	else if (COMPARE_STRINGS(classname, "Clayminer") == 0) {
		m_UnitClass = new UnitClayMiner();
	}

	else if (COMPARE_STRINGS(classname, "Mason") == 0) {
		m_UnitClass = new UnitMason();
	}



	else {
		return false;
	}

	// Lastly, set according sprite for unit.
	_setSpriteBasedOnClassAndRace();
	return true;
}


bool Unit::ChangeClass(std::string classname) {

	// First, delete previous class.
	delete m_UnitClass;

	// Set new class.
	return SetClass(classname);
}


void Unit::_determineUnitRibbonColor() {
	if (COMPARE_STRINGS(m_AssociatedPlayer->m_PlayerColor, "red") == 0) {
		m_UnitPlayerColor = "unit_player_color_red";
	}
	else if (COMPARE_STRINGS(m_AssociatedPlayer->m_PlayerColor, "blue") == 0) {
		m_UnitPlayerColor = "unit_player_color_blue";
	}
	else if (COMPARE_STRINGS(m_AssociatedPlayer->m_PlayerColor, "magenta") == 0) {
		m_UnitPlayerColor = "unit_player_color_magenta";
	}
	else if (COMPARE_STRINGS(m_AssociatedPlayer->m_PlayerColor, "green") == 0) {
		m_UnitPlayerColor = "unit_player_color_green";
	}
	else if (COMPARE_STRINGS(m_AssociatedPlayer->m_PlayerColor, "brown") == 0) {
		m_UnitPlayerColor = "unit_player_color_brown";
	}
	else if (COMPARE_STRINGS(m_AssociatedPlayer->m_PlayerColor, "black") == 0) {
		m_UnitPlayerColor = "unit_player_color_black";
	}
	else if (COMPARE_STRINGS(m_AssociatedPlayer->m_PlayerColor, "orange") == 0) {
		m_UnitPlayerColor = "unit_player_color_orange";
	}
	else if (COMPARE_STRINGS(m_AssociatedPlayer->m_PlayerColor, "yellow") == 0) {
		m_UnitPlayerColor = "unit_player_color_yellow";
	}
	else {
		m_UnitPlayerColor = "NULL"; // Indicates an error.
	}
}


void Unit::_setSpriteBasedOnClassAndRace() {

	std::string sprite;
	
	switch (m_EntityRaceCmp->m_EntityRace){
	case CMPEntityRace::Race::RACE_INVALID:
		return;
		break;
	case CMPEntityRace::Race::RACE_HUMAN:
		sprite = "human_";
		break;
	case CMPEntityRace::Race::RACE_TROLL:
		sprite = "troll_";
		break;
	case CMPEntityRace::Race::RACE_DWARF:
		sprite = "dwarf_";
		break;
	case CMPEntityRace::Race::RACE_ORC:
		sprite = "orc_";
		break;
	case CMPEntityRace::Race::RACE_HIGHELF:
		sprite = "highelf_";
		break;
	case CMPEntityRace::Race::RACE_DARKELF:
		sprite = "darkelf_";
		break;
	case CMPEntityRace::Race::RACE_GOBLIN:
		sprite = "goblin_";
		break;
	case CMPEntityRace::Race::RACE_GNOME:
		sprite = "gnome_";
		break;
	default:
		break;
	}


	if (COMPARE_STRINGS(m_UnitClass->m_UnitClassName, "Woodcutter") == 0) {
		sprite += "woodcutter";
	}
	else if (COMPARE_STRINGS(m_UnitClass->m_UnitClassName, "Farmer") == 0) {
		sprite += "farmer";

	}
	else if (COMPARE_STRINGS(m_UnitClass->m_UnitClassName, "Citizen") == 0) {
		sprite += "citizen";

	}
	else if (COMPARE_STRINGS(m_UnitClass->m_UnitClassName, "Fisher") == 0) {
		sprite += "fisher";

	}
	else if (COMPARE_STRINGS(m_UnitClass->m_UnitClassName, "Hunter") == 0) {
		sprite += "hunter";

	}
	else if (COMPARE_STRINGS(m_UnitClass->m_UnitClassName, "Brick Burner") == 0) {
		sprite += "brickburner";
	}
	else if (COMPARE_STRINGS(m_UnitClass->m_UnitClassName, "Carpenter") == 0) {
		sprite += "crapenter";
	}
	else if (COMPARE_STRINGS(m_UnitClass->m_UnitClassName, "Gatherer") == 0) {
		sprite += "gatherer";
	}

	else if (COMPARE_STRINGS(m_UnitClass->m_UnitClassName, "Bronze Miner") == 0) {
		sprite += "miner";
	}
	else if (COMPARE_STRINGS(m_UnitClass->m_UnitClassName, "Iron Miner") == 0) {
		sprite += "miner";
	}
	else if (COMPARE_STRINGS(m_UnitClass->m_UnitClassName, "Malachite Miner") == 0) {
		sprite += "miner";
	}
	else if (COMPARE_STRINGS(m_UnitClass->m_UnitClassName, "Adamantium Miner") == 0) {
		sprite += "miner";
	}
	else if (COMPARE_STRINGS(m_UnitClass->m_UnitClassName, "Stone Miner") == 0) {
		sprite += "miner";
	}
	else if (COMPARE_STRINGS(m_UnitClass->m_UnitClassName, "Salt Miner") == 0) {
		sprite += "miner";
	}
	else if (COMPARE_STRINGS(m_UnitClass->m_UnitClassName, "Clayminer") == 0) {
		sprite += "clayminer";
	}
	else if (COMPARE_STRINGS(m_UnitClass->m_UnitClassName, "Mason") == 0) {
		sprite += "mason";
	}

	m_GraphicsCmp->m_SpriteName = sprite;
}


/*
bool Unit::SetClass(std::string c) {

	// First, make sure we reset the class setting.
	if (m_UnitClass) {
		delete m_UnitClass;
	}


	// Second, make new class definitions.
	if (COMPARE_STRINGS(c, "Archer") == 0) {
		m_UnitClass = new UnitClassArcher(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else if (COMPARE_STRINGS(c, "Assassin") == 0) {
		m_UnitClass = new UnitClassAssassin(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else if (COMPARE_STRINGS(c, "Barbarian") == 0) {
		m_UnitClass = new UnitClassBarbarian(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else if (COMPARE_STRINGS(c, "Battlemage") == 0) {
		m_UnitClass = new UnitClassBattlemage(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else if (COMPARE_STRINGS(c, "Healer") == 0) {
		m_UnitClass = new UnitClassHealer(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else if (COMPARE_STRINGS(c, "Inquisitor") == 0) {
		m_UnitClass = new UnitClassInquisitor(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else if (COMPARE_STRINGS(c, "Knight") == 0) {
		m_UnitClass = new UnitClassKnight(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else if (COMPARE_STRINGS(c, "Mage") == 0) {
		m_UnitClass = new UnitClassMage(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else if (COMPARE_STRINGS(c, "Nightblade") == 0) {
		m_UnitClass = new UnitClassNightblade(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else if (COMPARE_STRINGS(c, "Paladin") == 0) {
		m_UnitClass = new UnitClassPaladin(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else if (COMPARE_STRINGS(c, "Rogue") == 0) {
		m_UnitClass = new UnitClassRogue(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else if (COMPARE_STRINGS(c, "Scout") == 0) {
		m_UnitClass = new UnitClassScout(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else if (COMPARE_STRINGS(c, "Sorcerer") == 0) {
		m_UnitClass = new UnitClassSorcerer(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else if (COMPARE_STRINGS(c, "Spellsword") == 0) {
		m_UnitClass = new UnitClassSpellsword(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else if (COMPARE_STRINGS(c, "Spy") == 0) {
		m_UnitClass = new UnitClassSpy(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else if (COMPARE_STRINGS(c, "Warrior") == 0) {
		m_UnitClass = new UnitClassWarrior(m_UnitSkillsMap, m_UnitAttributesMap);
	}
	else {
		return false;
	}


	if (m_UnitClass != nullptr) return true;
	else return false;
}
*/


bool Forest::IsCityOnForest() {

	MapTile* maptile = GetMapTileAtWorldPosition(m_TransformCmp->m_GameWorldSpaceCell[0], m_TransformCmp->m_GameWorldSpaceCell[1]);

	for (auto it : *maptile->m_MapTileEntities) {

		if (COMPARE_STRINGS(it->m_IDCmp->m_DynamicTypeName, "City") == 0) return true;
	}

	return false;
}


void WorldMap::SetMapOptions(WorldMapDrawingOptions* worldDef) {

	m_MapDrawOptions = worldDef;
	m_WorldMap = worldDef->m_MapDefinitions;
}


void WorldMapDrawingOptions::_createMap() {


	m_MapDefinitions = new MapTileArray();

	EntitiesStorage* storage = EntitiesStorage::Get();

	using namespace std;

	ifstream map("assets/map/worldmap_alpha.txt", fstream::in);

	string line;
	string token;
	string token_two;

	int xpos = 0;
	int ypos = 0;

	// Width and Height must always be 1 less then defined in the loaded mapfile. Else errors occur.
	int mapwidth = 19;
	int mapheight = 19;

	MapTile* maptile = nullptr;

	std::vector<MapTileRegion*> regions_vec;
	MapTileRegion* region = nullptr;


	while (getline(map, line)) {


		//cout << line << endl;



		// Read the textfile line by line.
		if (IsSubstringInString("maptiles", line)) { // Defining the ground maptiles.

			cout << APP_COLOR;
			cout << "CREATING MAPTILES." << white << endl;


			if (COMPARE_STRINGS(line, "maptiles;") == 0) getline(map, line); // Read next line for maptiles definition.


			cout << APP_ERROR_COLOR;
			cout << line << white << endl;

			/*
			For: every token do:
			...

			*/
			// First, identify tokens.
			string token = "";
			bool escape_code = false;
			bool line_end_escape_code = false; // Means, the end of the line was reached, the delimiter ";" was found, thus move to next line.

			for (auto it = line.begin(); it != line.end(); ++it) {

				if (*it == ',') { // escape code
					escape_code = true;
				}
				else if (*it == ';') {
					line_end_escape_code = true;
				}
				else {
					token.push_back((*it)); // At char to string.
				}


				// Now check for definitions an create new maptiles.
				// Escape code means, we found our delimiter and can check the word for maptile definition.
				if (escape_code) {


					if (IsSubstringInString("_shallow", token)) {
						maptile = new MapTile("water_shallow", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);
						maptile->m_TransformCmp->m_GameWorldSpaceCell[0] = xpos;
						maptile->m_TransformCmp->m_GameWorldSpaceCell[1] = ypos;

						m_MapDefinitions->at(xpos).at(ypos) = maptile;

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.


						cout << APP_SUCCESS_COLOR;
						cout << "Create WATER_SHALLOW at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("_deep", token)) {
						maptile = new MapTile("water_deep", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);
						maptile->m_TransformCmp->m_GameWorldSpaceCell[0] = xpos;
						maptile->m_TransformCmp->m_GameWorldSpaceCell[1] = ypos;

						m_MapDefinitions->at(xpos).at(ypos) = maptile;

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create WATER_DEEP at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("temperate", token)) {
						maptile = new MapTile("temperate", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);
						maptile->m_TransformCmp->m_GameWorldSpaceCell[0] = xpos;
						maptile->m_TransformCmp->m_GameWorldSpaceCell[1] = ypos;

						m_MapDefinitions->at(xpos).at(ypos) = maptile;

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create TEMPERATE at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("jungle", token)) {
						maptile = new MapTile("jungle", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);
						maptile->m_TransformCmp->m_GameWorldSpaceCell[0] = xpos;
						maptile->m_TransformCmp->m_GameWorldSpaceCell[1] = ypos;

						m_MapDefinitions->at(xpos).at(ypos) = maptile;

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create JUNGLE at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("tundra", token)) {
						maptile = new MapTile("tundra", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);

						maptile->m_TransformCmp->m_GameWorldSpaceCell[0] = xpos;
						maptile->m_TransformCmp->m_GameWorldSpaceCell[1] = ypos;

						m_MapDefinitions->at(xpos).at(ypos) = maptile;

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create TUNDRA at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("savannah", token)) {
						maptile = new MapTile("savannah", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);

						maptile->m_TransformCmp->m_GameWorldSpaceCell[0] = xpos;
						maptile->m_TransformCmp->m_GameWorldSpaceCell[1] = ypos;

						m_MapDefinitions->at(xpos).at(ypos) = maptile;

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create SAVANNAH at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("snow", token)) {
						maptile = new MapTile("snow", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);

						maptile->m_TransformCmp->m_GameWorldSpaceCell[0] = xpos;
						maptile->m_TransformCmp->m_GameWorldSpaceCell[1] = ypos;

						m_MapDefinitions->at(xpos).at(ypos) = maptile;

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create SNOW at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("ice", token)) {
						maptile = new MapTile("ice", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);

						maptile->m_TransformCmp->m_GameWorldSpaceCell[0] = xpos;
						maptile->m_TransformCmp->m_GameWorldSpaceCell[1] = ypos;

						m_MapDefinitions->at(xpos).at(ypos) = maptile;

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create ICE at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("sand", token)) {
						maptile = new MapTile("sand", "layer4", xpos * SPRITES_WIDTH_AND_HEIGHT, ypos * SPRITES_WIDTH_AND_HEIGHT);

						maptile->m_TransformCmp->m_GameWorldSpaceCell[0] = xpos;
						maptile->m_TransformCmp->m_GameWorldSpaceCell[1] = ypos;

						m_MapDefinitions->at(xpos).at(ypos) = maptile;

						storage->AddGameEntitie(m_MapDefinitions->at(xpos).at(ypos)); // Add Maptile to EntitiesStorage.

						cout << APP_SUCCESS_COLOR;
						cout << "Create SAND at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}


					// Custom double for-loop iterator...
					// To get the right cell position of the next tile.
					cout << color(colors::MAGENTA);
					cout << "X " << xpos << " Y " << ypos << white << endl;

					++xpos;
					if (xpos > mapwidth) {

						// Move on to the next line.
						++ypos;
						if (ypos > mapheight) {
							ypos = 0; // Set to 0 or reset it...
						}


						// Reset xpos.
						xpos = 0;
					}



					cout << color(colors::MAGENTA);
					cout << "X " << xpos << " Y " << ypos << white << endl;

				}
				else if (line_end_escape_code) {
					continue;
				}



			}

		}
		else if (IsSubstringInString("overlay", line)) { // Defining forests, hills, mountains etc.

		Forest* forest = nullptr;

		cout << APP_COLOR;
		cout << "CREATING OVERLAY." << white << endl;

		cout << xpos << ypos << endl;



		string token = ""; // The next word.
		bool escape_code = false;
		bool line_end_escape_code = false; // Means, the end of the line was reached, the delimiter ";" was found, thus move to next line.


		if (COMPARE_STRINGS(line, "overlay;") == 0) getline(map, line); // Read next line for maptiles definition.

		
		cout << line << endl;


		for (auto it = line.begin(); it != line.end(); ++it) {

				if (*it == ',') { // escape code
					escape_code = true;
				}
				else if (*it == ';') {
					line_end_escape_code = true;
				}
				else {
					token.push_back((*it)); // At char to string.
				}



				if (escape_code) {

					if (IsSubstringInString("forest_tundra", token)) {

						// Create forest.
						forest = MakeNewForest("forest_tundra_deep", xpos, ypos);
						storage->AddGameEntitie(forest);



						cout << token << endl;
						// Custom double for-loop iterator...
						// To get the right cell position of the next tile.
						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						++xpos;
						if (xpos > mapwidth) {

							// Move on to the next line.
							++ypos;
							if (ypos > mapheight) {
								ypos = 0; // Set to 0 or reset it...
							}


							// Reset xpos.
							xpos = 0;
						}



						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;
						cout << color(colors::CYAN);
						cout << "Create FOREST_TUNDRA at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("forest_jungle", token)) {

						// Create forest.
						forest = MakeNewForest("forest_jungle_deep", xpos, ypos);
						storage->AddGameEntitie(forest);

						cout << token << endl;


						// Custom double for-loop iterator...
						// To get the right cell position of the next tile.
						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						++xpos;
						if (xpos > mapwidth) {

							// Move on to the next line.
							++ypos;
							if (ypos > mapheight) {
								ypos = 0; // Set to 0 or reset it...
							}


							// Reset xpos.
							xpos = 0;
						}



						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						cout << color(colors::CYAN);
						cout << "Create FOREST_JUNGLE at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("forest_temperate", token)) {

						// Create forest.
						forest = MakeNewForest("forest_temperate_deep", xpos, ypos);
						storage->AddGameEntitie(forest);

						cout << token << endl;


						// Custom double for-loop iterator...
						// To get the right cell position of the next tile.
						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						++xpos;
						if (xpos > mapwidth) {

							// Move on to the next line.
							++ypos;
							if (ypos > mapheight) {
								ypos = 0; // Set to 0 or reset it...
							}


							// Reset xpos.
							xpos = 0;
						}



						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						cout << color(colors::CYAN);
						cout << "Create FOREST_TEMPERATE at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("forest_savannah", token)) {

						// Create forest.
						forest = MakeNewForest("forest_savannah_deep", xpos, ypos);
						storage->AddGameEntitie(forest);

						cout << token << endl;


						// Custom double for-loop iterator...
						// To get the right cell position of the next tile.
						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						++xpos;
						if (xpos > mapwidth) {

							// Move on to the next line.
							++ypos;
							if (ypos > mapheight) {
								ypos = 0; // Set to 0 or reset it...
							}


							// Reset xpos.
							xpos = 0;
						}



						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						cout << color(colors::CYAN);
						cout << "Create FOREST_SAVANNAH at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("hill", token)) {

						cout << token << endl;

						Hills* hills = MakeNewHill("hills", xpos, ypos);
						storage->AddGameEntitie(hills);

						// Custom double for-loop iterator...
						// To get the right cell position of the next tile.
						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						++xpos;
						if (xpos > mapwidth) {

							// Move on to the next line.
							++ypos;
							if (ypos > mapheight) {
								ypos = 0; // Set to 0 or reset it...
							}


							// Reset xpos.
							xpos = 0;
						}



						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						cout << color(colors::CYAN);
						cout << "Create HILLS at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("mountain", token)) {

						cout << token << endl;

						Mountains* mountains = MakeNewMountain("highmountain", xpos, ypos);
						storage->AddGameEntitie(mountains);


						// Custom double for-loop iterator...
						// To get the right cell position of the next tile.
						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						++xpos;
						if (xpos > mapwidth) {

							// Move on to the next line.
							++ypos;
							if (ypos > mapheight) {
								ypos = 0; // Set to 0 or reset it...
							}


							// Reset xpos.
							xpos = 0;
						}



						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						cout << color(colors::CYAN);
						cout << "Create MOUNTAINS at Position " << xpos << ":" << ypos << white << endl;

						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (IsSubstringInString("none", token)) {

						cout << token << endl;


						// Custom double for-loop iterator...
						// To get the right cell position of the next tile.
						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						++xpos;
						if (xpos > mapwidth) {

							// Move on to the next line.
							++ypos;
							if (ypos > mapheight) {
								ypos = 0; // Set to 0 or reset it...
							}


							// Reset xpos.
							xpos = 0;
						}



						cout << color(colors::MAGENTA);
						cout << "X " << xpos << " Y " << ypos << white << endl;

						cout << color(colors::CYAN);
						cout << "Create NONE at Position " << xpos << ":" << ypos << white << endl;
						// Nothing...


						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;
					}
					else if (line_end_escape_code) {
						continue;
					}



				}

			} // end for overlay


		}
		else if (IsSubstringInString("region;", line)) { // Defining maptileregions for the map.

				// Regions are defined like
				// region;
				// 1:0, 2:0, 1:1,; ...
				int map_tile[2];
				bool first_digit_defined = false;

				region = new MapTileRegion();
				regions_vec.push_back(region);


				cout << APP_COLOR;
				cout << "CREATING REGIONS" << white << endl;

				string token = ""; // The next word.
				bool escape_code = false;
				bool token_escape_code = false;
				bool token_end_of_maptile_definition = false;
				bool line_end_escape_code = false; // Means, the end of the line was reached, the delimiter ";" was found, thus move to next line.


				if (COMPARE_STRINGS(line, "region;") == 0) getline(map, line); // Read next line for maptiles definition.


				cout << APP_ERROR_COLOR;
				cout << line << white << endl;

				// Iterate through line
				for (auto it = line.begin(); it != line.end(); ++it) {

					if (*it == ',') { // escape code
						escape_code = true;
					}
					else if (*it == ';') {
						line_end_escape_code = true;
					}
					else {
						token.push_back((*it)); // At char to string.
					}


					// Check tokens.
					if (escape_code) {

						cout << APP_ERROR_COLOR;
						cout << token << white << endl;

						// Extract numbers out of token
						string first_number, second_number;
						bool delimiter_reached = false;

						for (auto it = token.begin(); it != token.end(); ++it) {

							if (*it == ':') delimiter_reached = true;

							if (*it != ':' && delimiter_reached == false) {

								first_number.push_back(*it);
							}
							else if(*it != ':'){
								second_number.push_back(*it);
							}

						}


						// Convert first_number and second_number to a maptile position.
						map_tile[0] = atoi(first_number.c_str());
						map_tile[1] = atoi(second_number.c_str());


						region->AddTileToRegion(GetMapTileAtWorldPosition(map_tile[0], map_tile[1]));


						cout << APP_ERROR_COLOR;
						cout << "First: "<<first_number << " Second: " << second_number << white << endl;
						first_number.clear();
						second_number.clear();



						// Reset the reading token and escape_code
						token.clear();
						escape_code = false;

					}
					else if (line_end_escape_code) {
						continue;
					}




				}

		}
		else if (IsSubstringInString("rivers;", line)) {

			cout << APP_COLOR;
			cout << "CREATING RIVERS." << white << endl;

			cout << xpos << ypos << endl;

			string token = ""; // The next word.
			bool escape_code = false;
			bool line_end_escape_code = false; // Means, the end of the line was reached, the delimiter ";" was found, thus move to next line.

			if (COMPARE_STRINGS(line, "rivers;") == 0) getline(map, line); // Read next line for rivers definition.

			cout << line << endl;


			for (auto it = line.begin(); it != line.end(); ++it) {

				if (*it == ',') { // escape code
					escape_code = true;
				}
				else if (*it == ';') {
					line_end_escape_code = true;
				}
				else {
					token.push_back((*it)); // At char to string.
				}

				// Check tokens.
				if (escape_code) {

					cout << APP_ERROR_COLOR;
					cout << token << white << endl;

					// Make river.
				if (IsSubstringInString("up_right_left_down", token)) {

					River* r = MakeNewRiver("river_up_right_left_down", xpos, ypos);
					storage->AddGameEntitie(r);

				}
				else if (IsSubstringInString("up_right_left", token)) {

					River* r = MakeNewRiver("river_up_right_left", xpos, ypos);
					storage->AddGameEntitie(r);

				}
				else if (IsSubstringInString("up_right_down", token)) {

					River* r = MakeNewRiver("river_up_right_down", xpos, ypos);
					storage->AddGameEntitie(r);

				}
				else if (IsSubstringInString("down_left", token)) {

						River* r = MakeNewRiver("river_down_left", xpos, ypos);
						storage->AddGameEntitie(r);

					}
					else if (IsSubstringInString("down_right", token)) {

						River* r = MakeNewRiver("river_down_right", xpos, ypos);
						storage->AddGameEntitie(r);


					}
					else if (IsSubstringInString("left_right", token)) {

						River* r = MakeNewRiver("river_left_right", xpos, ypos);
						storage->AddGameEntitie(r);

					}
					else if (IsSubstringInString("left_right_down", token)) {

						River* r = MakeNewRiver("river_left_right_down", xpos, ypos);
						storage->AddGameEntitie(r);

					}
					else if (IsSubstringInString("left_up_down", token)) {

						River* r = MakeNewRiver("river_left_up_down", xpos, ypos);
						storage->AddGameEntitie(r);

					}
					else if (IsSubstringInString("up_down", token)) {

						River* r = MakeNewRiver("river_up_down", xpos, ypos);
						storage->AddGameEntitie(r);

					}
					else if (IsSubstringInString("up_left", token)) {

						River* r = MakeNewRiver("river_up_left", xpos, ypos);
						storage->AddGameEntitie(r);

					}
					else if (IsSubstringInString("up_right", token)) {

						River* r = MakeNewRiver("river_up_right", xpos, ypos);
						storage->AddGameEntitie(r);


					}
					else if (IsSubstringInString("none", token)) {

					}




					++xpos;
					if (xpos > mapwidth) {

						// Move on to the next line.
						++ypos;
						if (ypos > mapheight) {
							ypos = 0; // Set to 0 or reset it...
						}


						// Reset xpos.
						xpos = 0;
					}


					// Reset the reading token and escape_code
					token.clear();
					escape_code = false;

				}
				else if (line_end_escape_code) {
					continue;
				}

		}


		}
		else {
			continue;
		}
	}


	// At last, add regions made to storage.
	for (auto it : regions_vec) {

		storage->AddGameEntitie(it);
	}
	

	regions_vec.clear();
	map.close();
}


WorldMap* WorldMap::Get() {
	if (!m_WorldMapInstance) {
		m_WorldMapInstance = new WorldMap();

		return m_WorldMapInstance;
	}
	else {
		return m_WorldMapInstance;
	}
}


void WorldMap::Del() {

	if (m_WorldMapInstance) delete m_WorldMapInstance;
}


void Forest::Update() {


	// Change graphics accordingly to own type.
	switch (m_ForestType) {
	case ForestType::FOREST_SCARCE:

		switch (m_ForestClass) {
		case ForestClass::FOREST_CLASS_TEMPERATE:
			m_GraphicsCmp->m_SpriteName = "forest_temperate_scarce";
			break;
		case ForestClass::FOREST_CLASS_JUNGLE:
			m_GraphicsCmp->m_SpriteName = "forest_jungle_scarce";
			break;
		case ForestClass::FOREST_CLASS_TUNDRA:
			m_GraphicsCmp->m_SpriteName = "forest_tundra_scarce";
			break;
		case ForestClass::FOREST_CLASS_SAVANNAH:
			m_GraphicsCmp->m_SpriteName = "forest_savannah_scarce";
			break;
		default:
			break;
		}

		break;
	case ForestType::FOREST_NORMAL:

		switch (m_ForestClass) {
		case ForestClass::FOREST_CLASS_TEMPERATE:
			m_GraphicsCmp->m_SpriteName = "forest_temperate_normal";
			break;
		case ForestClass::FOREST_CLASS_JUNGLE:
			m_GraphicsCmp->m_SpriteName = "forest_jungle_normal";
			break;
		case ForestClass::FOREST_CLASS_TUNDRA:
			m_GraphicsCmp->m_SpriteName = "forest_tundra_normal";
			break;
		case ForestClass::FOREST_CLASS_SAVANNAH:
			m_GraphicsCmp->m_SpriteName = "forest_savannah_normal";
			break;
		default:
			break;
		}

		break;
	case ForestType::FOREST_DEEP:
		switch (m_ForestClass) {
		case ForestClass::FOREST_CLASS_TEMPERATE:
			m_GraphicsCmp->m_SpriteName = "forest_temperate_deep";
			break;
		case ForestClass::FOREST_CLASS_JUNGLE:
			m_GraphicsCmp->m_SpriteName = "forest_jungle_deep";
			break;
		case ForestClass::FOREST_CLASS_TUNDRA:
			m_GraphicsCmp->m_SpriteName = "forest_tundra_deep";
			break;
		case ForestClass::FOREST_CLASS_SAVANNAH:
			m_GraphicsCmp->m_SpriteName = "forest_savannah_deep";
			break;
		default:
			break;
		}
		break;
	case ForestType::FOREST_DYING:
		switch (m_ForestClass) {
		case ForestClass::FOREST_CLASS_TEMPERATE:
			m_GraphicsCmp->m_SpriteName = "forest_temperate_dying";
			break;
		case ForestClass::FOREST_CLASS_JUNGLE:
			m_GraphicsCmp->m_SpriteName = "forest_jungle_dying";
			break;
		case ForestClass::FOREST_CLASS_TUNDRA:
			m_GraphicsCmp->m_SpriteName = "forest_tundra_dying";
			break;
		case ForestClass::FOREST_CLASS_SAVANNAH:
			m_GraphicsCmp->m_SpriteName = "forest_savannah_dying";
			break;
		default:
			break;
		}
		break;
	case ForestType::FOREST_INVALID: // Forests lifetime ended or other error occured. So delete this instance from game.

		EntitiesStorage::Get()->DeleteGameEntitie(this);
		break;
	default:
		break;
	}
}

void City::ReclaimRegions() {

	_unclaimRegions();
	ClaimRegions();
}


void City::Update() {

	// Later make that this city ceases if population is smaller than 1.
	// For now, we just skip this and do not let the city die.
	if (m_CitySize < 1) m_CitySize = 1;

	CitySizeClass size = this->m_CitySizeClass;

	_updateCitySizeClass();

	if (m_CitySizeClass != size) {

		// First, reset visibility.
		ResetVisibility();

		ReclaimRegions();
		MakeCityBorders();

		// Lastly, update visibility.
		UpdateVisibility();
	}
}




void City::_defineCityBuildingsSlots() {

	CityType city_type = m_CityType;
	CityLandscapeType landscape_type = *m_CityLandscapeType;
	bool flag = false;

	// Version 2.0.
	flag = (city_type == City::CityType::CITY_TYPE_CITY) ? true : false;

	if (flag) {

		// City.
		if (m_CoastalCity) {
			m_CityBuildingsSlots.push_back(new BuildingSlot(604, 530, 12, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_PORT));
			m_CityBuildingsSlots.push_back(new BuildingSlot(539, 594, 13, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_PORT));
		}


		// 9 standard slots.
		m_CityBuildingsSlots.push_back(new BuildingSlot(266, 340, 1, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD));
		m_CityBuildingsSlots.push_back(new BuildingSlot(376, 300, 2, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD));
		m_CityBuildingsSlots.push_back(new BuildingSlot(501, 342, 3, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD));
		m_CityBuildingsSlots.push_back(new BuildingSlot(210, 434, 4, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD));
		m_CityBuildingsSlots.push_back(new BuildingSlot(156, 509, 5, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD));
		m_CityBuildingsSlots.push_back(new BuildingSlot(292, 512, 6, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD));
		m_CityBuildingsSlots.push_back(new BuildingSlot(331, 414, 7, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD));
		m_CityBuildingsSlots.push_back(new BuildingSlot(448, 436, 8, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD));
		m_CityBuildingsSlots.push_back(new BuildingSlot(573, 405, 9, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD));



		// 2 special slots.
		m_CityBuildingsSlots.push_back(new BuildingSlot(132, 350, 10, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_SPECIAL));
		m_CityBuildingsSlots.push_back(new BuildingSlot(75, 415, 11, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_SPECIAL));

	}
	else {

		// Fort.

		// TODO:

	}

	/*
	switch (city_type) {

	case CityType::CITY_TYPE_CITY:
		flag = true;
		break;


	case CityType::CITY_TYPE_FORT:
		flag = false;
		break;

	default:
		return;
	}

	// Define...
	if (flag) { // City...
		switch (landscape_type) {
		case CityLandscapeType::CITY_LANDSCAPE_FOREST:
			if (m_CoastalCity) {

				m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, 12, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_PORT));
				m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, 13, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_PORT));

			}

			// 9 standard slots.
			m_CityBuildingsSlots.push_back(new BuildingSlot(190, 360, 1, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD));
			m_CityBuildingsSlots.push_back(new BuildingSlot(320, 345, 2, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD));
			m_CityBuildingsSlots.push_back(new BuildingSlot(445, 345, 3, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD));
			m_CityBuildingsSlots.push_back(new BuildingSlot(130, 415, 4, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD));
			m_CityBuildingsSlots.push_back(new BuildingSlot(250, 415, 5, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD));
			m_CityBuildingsSlots.push_back(new BuildingSlot(380, 400, 6, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD));
			m_CityBuildingsSlots.push_back(new BuildingSlot(195, 475, 7, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD));
			m_CityBuildingsSlots.push_back(new BuildingSlot(325, 475, 8, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD));
			m_CityBuildingsSlots.push_back(new BuildingSlot(512, 536, 9, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD));



			// 2 special slots.
			m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, 10, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_SPECIAL));
			m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, 11, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_SPECIAL));



			break;

		case CityLandscapeType::CITY_LANDSCAPE_HILLS:
			if (m_CoastalCity) {

				m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, 12, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_PORT));
				m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, 13, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_PORT));

			}


			// 9 standard slots.
			for (int i = 1; i <= 9; i++) {
				m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, i, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD));
			}

			// 2 special slots.
			m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, 10, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_SPECIAL));
			m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, 11, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_SPECIAL));



			break;

		case CityLandscapeType::CITY_LANDSCAPE_PLAIN:
			if (m_CoastalCity) {

				m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, 12, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_PORT));
				m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, 13, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_PORT));

			}


			// 9 standard slots.
			for (int i = 1; i <= 9; i++) {
				m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, i, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD));
			}

			// 2 special slots.
			m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, 10, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_SPECIAL));
			m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, 11, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_SPECIAL));



			break;



		default:
			return;
		}

	}
	else { // Fort...
		switch (landscape_type) {
		case CityLandscapeType::CITY_LANDSCAPE_FOREST:

			// 4 standard slots.
			for (int i = 1; i <= 4; i++) {
				m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, i, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD));
			}

			// 4 special slots.
			m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, 5, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_SPECIAL));
			m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, 6, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_SPECIAL));
			m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, 7, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_SPECIAL));
			m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, 8, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_SPECIAL));

			break;

		case CityLandscapeType::CITY_LANDSCAPE_HILLS:

			// 4 standard slots.
			for (int i = 1; i <= 4; i++) {
				m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, i, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD));
			}

			// 4 special slots.
			m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, 5, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_SPECIAL));
			m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, 6, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_SPECIAL));
			m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, 7, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_SPECIAL));
			m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, 8, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_SPECIAL));



			break;

		case CityLandscapeType::CITY_LANDSCAPE_PLAIN:

			// 4 standard slots.
			for (int i = 1; i <= 4; i++) {
				m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, i, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD));
			}

			// 4 special slots.
			m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, 5, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_SPECIAL));
			m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, 6, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_SPECIAL));
			m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, 7, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_SPECIAL));
			m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, 8, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_SPECIAL));




			break;

		case CityLandscapeType::CITY_LANDSCAPE_MOUNTAINS:

			// 4 standard slots.
			for (int i = 1; i <= 4; i++) {
				m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, i, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD));
			}

			// 4 special slots.
			m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, 5, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_SPECIAL));
			m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, 6, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_SPECIAL));
			m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, 7, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_SPECIAL));
			m_CityBuildingsSlots.push_back(new BuildingSlot(0, 0, 8, City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_SPECIAL));




			break;


		default:
			return;
		}
	}
	*/
}


void City::AddBuilding(Building* building, int slot) {

	for (auto it : m_CityBuildingsSlots) {
		if (it->m_SlotNumber == slot) {
			it->m_AssociatedBuilding = building;
			it->m_UsedByBuilding = true;

			building->m_TransformCmp->m_PosX = it->m_XPos;
			building->m_TransformCmp->m_PosY = it->m_YPos;


			// Finally, store the building in citystorage.
			m_PresentUnitsVector.push_back(building);
		}
	}
}


void City::AddUnit(Unit* unit) {

	// Finally, store the building in citystorage.
	m_PresentUnitsVector.push_back(unit);

	m_CitySize += 1;

	Update();
}


void City::RemoveUnit(Unit* unit) {

	std::vector<GameEntity*>::iterator it = std::find(m_PresentUnitsVector.begin(), m_PresentUnitsVector.end(), unit);

	if (it != m_PresentUnitsVector.end()) {

		m_PresentUnitsVector.erase(it);
	}
}


void City::RemoveBuilding(Building* building) {

	std::vector<GameEntity*>::iterator it = std::find(m_PresentUnitsVector.begin(), m_PresentUnitsVector.end(), building);

	if (it != m_PresentUnitsVector.end()) {

		m_PresentUnitsVector.erase(it);
	}
}


void Unit::_mapStates() {

	if (m_AICmp) {

		m_AICmp->MapState("state_flee", new UnitFleeLogic(*m_AICmp));
		m_AICmp->MapState("state_search", new UnitSearchLogic(*m_AICmp));
		m_AICmp->MapState("state_die", new UnitDieLogic(*m_AICmp));
		m_AICmp->MapState("state_defend", new UnitDefendLogic(*m_AICmp));
		m_AICmp->MapState("state_attack", new UnitAttackLogic(*m_AICmp));
		m_AICmp->MapState("state_move", new UnitMoveLogic(*m_AICmp));
		m_AICmp->MapState("state_patrol", new UnitPatrolLogic(*m_AICmp));
		m_AICmp->MapState("state_wait", new UnitWaitLogic(*m_AICmp));
	}
}


void City::_deriveCityLandscapeType() {

	/*
	NOTE: How do we handle rivers.

	Rivers are additional to cities landscape. As rivers can be on hills, forests and plain.
	Thus, we give for a river a boolean, that is true, if a river is present on the cities tile.
	*/

	MapTile* city_tile = GetMapTileAtWorldPosition(this->m_TransformCmp->m_GameWorldSpaceCell[0], this->m_TransformCmp->m_GameWorldSpaceCell[1]);

	bool mountain = false, hill = false, forest = false;

	// First, check for mountains.
	for (auto it : *city_tile->m_MapTileEntities) {

		if (COMPARE_STRINGS(it->m_IDCmp->m_DynamicTypeName, "Mountains") == 0) {
			mountain = true;
		}
		// .. check for hills.
		else if (COMPARE_STRINGS(it->m_IDCmp->m_DynamicTypeName, "Hills") == 0) {
			hill = true;

		}
		// .. check for river.
		else if (COMPARE_STRINGS(it->m_IDCmp->m_DynamicTypeName, "River") == 0) {
			m_RiverPresentInCity = true;

		}
		// .. check for forest
		else if (COMPARE_STRINGS(it->m_IDCmp->m_DynamicTypeName, "Forest") == 0) {
			forest = true;
		}


	}

	if (mountain) {
		m_CityLandscapeType = new CityLandscapeType(CityLandscapeType::CITY_LANDSCAPE_MOUNTAINS);
	}
	else if (hill) {
		m_CityLandscapeType = new CityLandscapeType(CityLandscapeType::CITY_LANDSCAPE_HILLS);
	}
	else if (forest) {
		m_CityLandscapeType = new CityLandscapeType(CityLandscapeType::CITY_LANDSCAPE_FOREST);
	}
	// .. lastly, if nothing present, define as plain city.
	else {
		m_CityLandscapeType = new CityLandscapeType(CityLandscapeType::CITY_LANDSCAPE_PLAIN);
	}



	// Check whether coastal city.
	MapTile* m1, *m2, *m3, *m4;

	m1 = GetMapTileAtWorldPosition(m_TransformCmp->m_GameWorldSpaceCell[0]+1, m_TransformCmp->m_GameWorldSpaceCell[1]);
	m2 = GetMapTileAtWorldPosition(m_TransformCmp->m_GameWorldSpaceCell[0]-1, m_TransformCmp->m_GameWorldSpaceCell[1]);
	m3 = GetMapTileAtWorldPosition(m_TransformCmp->m_GameWorldSpaceCell[0], m_TransformCmp->m_GameWorldSpaceCell[1]+1);
	m4 = GetMapTileAtWorldPosition(m_TransformCmp->m_GameWorldSpaceCell[0], m_TransformCmp->m_GameWorldSpaceCell[1]-1);


	if (m1) {
		if (m1->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_WATER_SHALLOW) {
			m_CoastalCity = true;
		}
	}
	if (m2) {
		if (m2->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_WATER_SHALLOW) {
			m_CoastalCity = true;
		}
	}
	if (m3) {
		if (m3->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_WATER_SHALLOW) {
			m_CoastalCity = true;
		}
	}
	if (m4) {
		if (m4->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_WATER_SHALLOW) {
			m_CoastalCity = true;
		}
	}

}



void City::_unclaimRegions() {

	for (auto it : m_ClaimedRegions) {

		it->SetAssociatedPlayer(nullptr);
		
	}

	if (m_ClaimedRegions.size() > 0) {
		m_ClaimedRegions.clear();
		m_CityBorderMapTileVec.clear();
		m_MapTileBorderDirectionMap.clear();
	}
}


void City::_claimRegions() {

	using namespace std;
	cout << APP_SUCCESS_COLOR;
	cout << "_claimRegions() for " << m_CityName;

	switch (m_CityType){
	case CityType::CITY_TYPE_CITY:
		switch (m_CitySizeClass) {
		case CitySizeClass::CITY_SIZE_CLASS_SMALL:
			_claimPrimaryRegions();


			cout << ". Claim _claimPrimaryRegions()." << white << endl;
			break;
		case CitySizeClass::CITY_SIZE_CLASS_NORMAL:
			_claimPrimaryRegions();
			_claimSecondaryRegions();


			cout << ". Claim up to _claimSecondaryRegions()." << white << endl;
			break;
		case CitySizeClass::CITY_SIZE_CLASS_BIG:
			_claimPrimaryRegions();
			_claimSecondaryRegions();
			_claimTertiaryReions();


			cout << ". Claim up to _claimTertiaryReions()." << white << endl;
			break;
		case CitySizeClass::CITY_SIZE_CLASS_HUGE:
			_claimPrimaryRegions();
			_claimSecondaryRegions();
			_claimTertiaryReions();
			_claimQuartaryRegions();

			cout << ". Claim up to _claimQuartaryRegions()." << white << endl;
			break;
		default:
			break;
		}
		break;
	case CityType::CITY_TYPE_FORT:// Test for castles, they claim only half of cities max regions. Till secondary...
		switch (m_CitySizeClass) {
		case CitySizeClass::CITY_SIZE_CLASS_SMALL:
			_claimPrimaryRegions();
			break;
		case CitySizeClass::CITY_SIZE_CLASS_NORMAL:
			_claimPrimaryRegions();
			_claimSecondaryRegions();
			break;
		case CitySizeClass::CITY_SIZE_CLASS_BIG:
			_claimPrimaryRegions();
			_claimSecondaryRegions();
			//_claimTertiaryReions();
			break;
		case CitySizeClass::CITY_SIZE_CLASS_HUGE:
			_claimPrimaryRegions();
			_claimSecondaryRegions();
			//_claimTertiaryReions(); 
			// Fort does not claim quartary tiles.
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}



	_setSpriteForClaimedRegion();

	// Set region owner for claimed regions.
	for (auto it : m_ClaimedRegions) {

		it->SetAssociatedPlayer(m_AssociatedPlayer);
	}
}


void City::_claimPrimaryRegions() {

	// Primary regions are at tiles around city.
	// Those are 4.
	int city_pos[2];
	city_pos[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	city_pos[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];

	int right[2], left[2], up[2], down[2];

	right[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 1;
	right[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];

	left[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 1;
	left[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];

	up[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	up[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 1;

	down[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	down[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 1;

	MapTile* m0, * m1, * m2, * m3, * m4;
	m0 = GetMapTileAtWorldPosition(city_pos[0], city_pos[1]);
	m1 = GetMapTileAtWorldPosition(right[0], right[1]);
	m2 = GetMapTileAtWorldPosition(left[0], left[1]);
	m3 = GetMapTileAtWorldPosition(up[0], up[1]);
	m4 = GetMapTileAtWorldPosition(down[0], down[1]);


	// No need for nullptr test here.
	m_ClaimedRegions.push_back(m0->m_AssociatedRegion);

	// Here we must test whether the tile is valid.
	if (m1 != nullptr) {

		if (_isRegionClaimedAlreadyByThisCity(m1->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m1->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m1->m_AssociatedRegion);
		}
	}
	if (m2 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m2->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m2->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m2->m_AssociatedRegion);
		}
	}
	if (m3 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m3->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m3->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m3->m_AssociatedRegion);
		}
	}
	if (m4 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m4->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m4->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m4->m_AssociatedRegion);
		}
	}
}


void City::_claimSecondaryRegions() {

	// Secondary regions are at tiles 2 tiles away around city.
	// Those are 8.
	int city_pos[2];
	city_pos[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	city_pos[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];

	int up[2], right[2], down[2], left[2], left_up[2], right_up[2], down_left[2], down_right[2];

	right[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 2;
	right[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];

	left[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 2;
	left[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];

	up[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	up[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 2;

	down[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	down[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 2;

	down_right[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 1;
	down_right[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 1;

	down_left[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 1;
	down_left[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 1;

	right_up[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 1;
	right_up[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 1;

	left_up[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 1;
	left_up[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 1;


	MapTile* m1, * m2, * m3, * m4, * m5, * m6, * m7, * m8;
	m1 = GetMapTileAtWorldPosition(right[0], right[1]);
	m2 = GetMapTileAtWorldPosition(left[0], left[1]);
	m3 = GetMapTileAtWorldPosition(up[0], up[1]);
	m4 = GetMapTileAtWorldPosition(down[0], down[1]);
	m5 = GetMapTileAtWorldPosition(down_right[0], down_right[1]);
	m6 = GetMapTileAtWorldPosition(down_left[0], down_left[1]);
	m7 = GetMapTileAtWorldPosition(right_up[0], right_up[1]);
	m8 = GetMapTileAtWorldPosition(left_up[0], left_up[1]);

	// Here we must test whether the tile is valid.
	if (m1 != nullptr) {

		if (_isRegionClaimedAlreadyByThisCity(m1->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m1->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m1->m_AssociatedRegion);
		}
	}
	if (m2 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m2->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m2->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m2->m_AssociatedRegion);
		}
	}
	if (m3 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m3->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m3->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m3->m_AssociatedRegion);
		}
	}
	if (m4 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m4->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m4->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m4->m_AssociatedRegion);
		}
	}
	if (m5 != nullptr) {

		if (_isRegionClaimedAlreadyByThisCity(m5->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m5->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m5->m_AssociatedRegion);
		}
	}
	if (m6 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m6->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m6->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m6->m_AssociatedRegion);
		}
	}
	if (m7 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m7->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m7->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m7->m_AssociatedRegion);
		}
	}
	if (m8 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m8->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m8->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m8->m_AssociatedRegion);
		}
	}
}


void City::_claimTertiaryReions() {

	// Tertiry regions are that tiles, that are 3 tiles away around city.
	// Those are 12.
	int city_pos[2];
	city_pos[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	city_pos[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];

	int up[2], right[2], down[2], left[2],
		left_up[2], right_up[2], down_left[2], down_right[2],
		left_up_2[2], right_up_2[2], down_left_2[2], down_right_2[2];

	right[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 3;
	right[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];

	left[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 3;
	left[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];

	up[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	up[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 3;

	down[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	down[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 3;


	left_up[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 1;
	left_up[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 2;

	right_up[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 1;
	right_up[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 2;

	down_left[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 1;
	down_left[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 2;

	down_right[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 1;
	down_right[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 2;


	left_up_2[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] -2;
	left_up_2[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 1;

	right_up_2[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 2;
	right_up_2[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 1;

	down_left_2[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 2;
	down_left_2[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 1;

	down_right_2[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 2;
	down_right_2[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 1;



	MapTile* m1, * m2, * m3, * m4, * m5, * m6, * m7, * m8,* m9, * m10, * m11, * m12;
	m1 = GetMapTileAtWorldPosition(right[0], right[1]);
	m2 = GetMapTileAtWorldPosition(left[0], left[1]);
	m3 = GetMapTileAtWorldPosition(up[0], up[1]);
	m4 = GetMapTileAtWorldPosition(down[0], down[1]);
	m5 = GetMapTileAtWorldPosition(down_right[0], down_right[1]);
	m6 = GetMapTileAtWorldPosition(down_left[0], down_left[1]);
	m7 = GetMapTileAtWorldPosition(right_up[0], right_up[1]);
	m8 = GetMapTileAtWorldPosition(left_up[0], left_up[1]);
	m9 = GetMapTileAtWorldPosition(left_up_2[0], left_up_2[1]);
	m10 = GetMapTileAtWorldPosition(right_up_2[0], right_up_2[1]);
	m11 = GetMapTileAtWorldPosition(down_left_2[0], down_left_2[1]);
	m12 = GetMapTileAtWorldPosition(down_right_2[0], down_right_2[1]);

	// Here we must test whether the tile is valid.
	if (m1 != nullptr) {

		if (_isRegionClaimedAlreadyByThisCity(m1->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m1->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m1->m_AssociatedRegion);
		}
	}
	if (m2 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m2->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m2->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m2->m_AssociatedRegion);
		}
	}
	if (m3 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m3->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m3->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m3->m_AssociatedRegion);
		}
	}
	if (m4 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m4->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m4->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m4->m_AssociatedRegion);
		}
	}
	if (m5 != nullptr) {

		if (_isRegionClaimedAlreadyByThisCity(m5->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m5->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m5->m_AssociatedRegion);
		}
	}
	if (m6 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m6->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m6->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m6->m_AssociatedRegion);
		}
	}
	if (m7 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m7->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m7->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m7->m_AssociatedRegion);
		}
	}
	if (m8 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m8->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m8->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m8->m_AssociatedRegion);
		}
	}
	if (m9 != nullptr) {

		if (_isRegionClaimedAlreadyByThisCity(m9->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m9->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m9->m_AssociatedRegion);
		}
	}
	if (m10 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m10->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m10->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m10->m_AssociatedRegion);
		}
	}
	if (m11 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m11->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m11->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m11->m_AssociatedRegion);
		}
	}
	if (m12 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m12->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m12->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m12->m_AssociatedRegion);
		}
	}
}



void City::_claimQuartaryRegions() {

	// Tertiry regions are that tiles, that are 3 tiles away around city.
	// Those are 16.
	int city_pos[2];
	city_pos[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	city_pos[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];


	int up[2], right[2], down[2], left[2],
		left_up[2], right_up[2], down_left[2], down_right[2],
		left_up_2[2], right_up_2[2], down_left_2[2], down_right_2[2],
		left_up_3[2], right_up_3[2], down_left_3[2], down_right_3[2];



	right[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 4;
	right[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];

	left[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 4;
	left[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1];

	up[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	up[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 4;

	down[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0];
	down[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 4;


	left_up[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 1;
	left_up[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 3;

	right_up[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 1;
	right_up[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 3;

	down_left[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 1;
	down_left[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 3;

	down_right[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 1;
	down_right[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 3;


	left_up_2[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 2;
	left_up_2[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 2;

	right_up_2[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 2;
	right_up_2[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 2;

	down_left_2[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 2;
	down_left_2[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 2;

	down_right_2[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 2;
	down_right_2[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 2;

	left_up_3[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 3;
	left_up_3[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 1;

	right_up_3[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 3;
	right_up_3[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] - 1;

	down_left_3[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] - 3;
	down_left_3[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 1;

	down_right_3[0] = this->m_TransformCmp->m_GameWorldSpaceCell[0] + 3;
	down_right_3[1] = this->m_TransformCmp->m_GameWorldSpaceCell[1] + 1;



	MapTile* m1, * m2, * m3, * m4, * m5, * m6, * m7, * m8, * m9, * m10, * m11, * m12, * m13, * m14, * m15, * m16;
	m1 = GetMapTileAtWorldPosition(right[0], right[1]);
	m2 = GetMapTileAtWorldPosition(left[0], left[1]);
	m3 = GetMapTileAtWorldPosition(up[0], up[1]);
	m4 = GetMapTileAtWorldPosition(down[0], down[1]);

	m5 = GetMapTileAtWorldPosition(down_right[0], down_right[1]);
	m6 = GetMapTileAtWorldPosition(down_left[0], down_left[1]);
	m7 = GetMapTileAtWorldPosition(right_up[0], right_up[1]);
	m8 = GetMapTileAtWorldPosition(left_up[0], left_up[1]);

	m9 = GetMapTileAtWorldPosition(left_up_2[0], left_up_2[1]);
	m10 = GetMapTileAtWorldPosition(right_up_2[0], right_up_2[1]);
	m11 = GetMapTileAtWorldPosition(down_left_2[0], down_left_2[1]);
	m12 = GetMapTileAtWorldPosition(down_right_2[0], down_right_2[1]);

	m13 = GetMapTileAtWorldPosition(left_up_3[0], left_up_3[1]);
	m14 = GetMapTileAtWorldPosition(right_up_3[0], right_up_3[1]);
	m15 = GetMapTileAtWorldPosition(down_left_3[0], down_left_3[1]);
	m16 = GetMapTileAtWorldPosition(down_right_3[0], down_right_3[1]);


	// Here we must test whether the tile is valid.
	if (m1 != nullptr) {

		if (_isRegionClaimedAlreadyByThisCity(m1->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m1->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m1->m_AssociatedRegion);
		}
	}
	if (m2 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m2->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m2->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m2->m_AssociatedRegion);
		}
	}
	if (m3 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m3->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m3->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m3->m_AssociatedRegion);
		}
	}
	if (m4 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m4->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m4->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m4->m_AssociatedRegion);
		}
	}
	if (m5 != nullptr) {

		if (_isRegionClaimedAlreadyByThisCity(m5->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m5->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m5->m_AssociatedRegion);
		}
	}
	if (m6 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m6->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m6->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m6->m_AssociatedRegion);
		}
	}
	if (m7 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m7->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m7->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m7->m_AssociatedRegion);
		}
	}
	if (m8 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m8->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m8->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m8->m_AssociatedRegion);
		}
	}
	if (m9 != nullptr) {

		if (_isRegionClaimedAlreadyByThisCity(m9->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m9->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m9->m_AssociatedRegion);
		}
	}
	if (m10 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m10->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m10->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m10->m_AssociatedRegion);
		}
	}
	if (m11 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m11->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m11->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m11->m_AssociatedRegion);
		}
	}
	if (m12 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m12->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m12->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m12->m_AssociatedRegion);
		}
	}
	if (m13 != nullptr) {

		if (_isRegionClaimedAlreadyByThisCity(m13->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m13->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m13->m_AssociatedRegion);
		}
	}
	if (m14 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m14->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m14->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m14->m_AssociatedRegion);
		}
	}
	if (m15 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m15->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m15->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m15->m_AssociatedRegion);
		}
	}
	if (m16 != nullptr) {
		if (_isRegionClaimedAlreadyByThisCity(m16->m_AssociatedRegion) == false &&
			_isRegionClaimedByOtherCity(m16->m_AssociatedRegion) == false) {

			m_ClaimedRegions.push_back(m16->m_AssociatedRegion);
		}
	}
}







bool City::_isRegionClaimedAlreadyByThisCity(MapTileRegion* region) {

	std::vector<MapTileRegion*> vec = m_ClaimedRegions;
	MapTileRegion* r = nullptr;

	for (auto it = vec.begin(); it != vec.end(); ++it) {

		r = *it;

		if (COMPARE_STRINGS_2(r->m_IDCmp->m_ID, region->m_IDCmp->m_ID) == 0) return true;
	}

	return false;
}


bool City::_isRegionClaimedByOtherCity(MapTileRegion* region) {

	if (region == nullptr) throw;

	if (region->m_AssociatedPlayer == nullptr) return false;
	else return true;
}


void City::_setSpriteForClaimedRegion() {

	for (auto it : m_ClaimedRegions) {

		it->m_GraphicsCmp->m_SpriteName = m_ClaimedRegionsSpriteName;
	}
}



void EntitiesStorage::RemovePlayer(std::string playername) {

	for (auto it : *m_PlayersVec) {
		if (COMPARE_STRINGS_2(it->m_PlayerName, playername) == 0) {
			RemovePlayer(it);
		}
	}
}

void EntitiesStorage::RemovePlayer(Player* p) {

	std::vector<Player*>::iterator it = std::find(m_PlayersVec->begin(), m_PlayersVec->end(), p);
	if (it != m_PlayersVec->end()) m_PlayersVec->erase(it);
}


std::string City::GetCurrentCitySprite() {

	switch (m_CitySizeClass)
	{
	case CitySizeClass::CITY_SIZE_CLASS_SMALL:
		return m_CitySpritesStorage->m_SmallCitySprite;
		break;
	case CitySizeClass::CITY_SIZE_CLASS_NORMAL:
		return m_CitySpritesStorage->m_NormalCitySprite;
		break;
	case CitySizeClass::CITY_SIZE_CLASS_BIG:
		return m_CitySpritesStorage->m_BigCitySprite;
		break;
	case CitySizeClass::CITY_SIZE_CLASS_HUGE:
		return m_CitySpritesStorage->m_HugeCitySprite;
		break;

	default:
		break;
	}
	
}


City::City(std::string cityname, bool city, CMPEntityRace::Race race, Player* player, int xpos, int ypos, int citySize) {

	m_IDCmp->m_DynamicTypeName = "City";


	m_CityName = cityname;
	m_CitySize = citySize;
	_updateCitySizeClass();

	m_CityRaceCmp = new CMPEntityRace(CMPEntityRace::Race::RACE_INVALID);
	_deriveCityRace(race); // Initializes the race for the city.

	m_CityType = (city == true) ? City::CityType::CITY_TYPE_CITY : City::CityType::CITY_TYPE_FORT;


	m_GraphicsCmp = new CMPGraphics();
	m_GraphicsCmp->m_DrawingLayer = "layer2";
	m_CitySpritesStorage = new CitySpritesHolder();
	_deriveCitySprites(); // Derives the cities sprites for the specific race.

	m_TransformCmp->m_PosX = xpos;
	m_TransformCmp->m_PosY = ypos;


	m_AICmp = new CMPArtificialIntelligence(this);

	m_AssociatedPlayer = player;
	player->AddCity(this);
	_determineMapCell(m_AssociatedPlayer->m_PlayerColor);
}


std::string City::GetCityLandscapeTypeString() {
	switch (*m_CityLandscapeType) {
	case CityLandscapeType::CITY_LANDSCAPE_FOREST:
		return "Forest";
		break;
	case CityLandscapeType::CITY_LANDSCAPE_MOUNTAINS:
		return "Mountains";
		break;
	case CityLandscapeType::CITY_LANDSCAPE_HILLS:
		return "Hills";
		break;
	case CityLandscapeType::CITY_LANDSCAPE_PLAIN:
		return "Plain";
		break;
	default:
		throw;
		break;
	}
}


City::CityLandscapeType City::GetCityLandscapeType() {
	return *m_CityLandscapeType;
}



bool Player::_isMapTileSurroundedByOwnTiles(MapTile* tile) {

	MapTile* other_tile = nullptr;

	bool up = false, down = false, left = false, right = false;

	int up_tile[2], down_tile[2], left_tile[2], right_tile[2];

	up_tile[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0];
	up_tile[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1] - 1;

	down_tile[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0];
	down_tile[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1] + 1;

	left_tile[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0] - 1;
	left_tile[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1];

	right_tile[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0] + 1;
	right_tile[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1];



	if (IsIndexOutOfBound(up_tile[0], up_tile[1]) == false) {

		other_tile = GetMapTileAtWorldPosition(up_tile[0], up_tile[1]);
		if (other_tile) {

			if (_belongMapTileToThisPlayer(other_tile) == false) {

				// The up tile belongs to us, thus no border in up diretion.
				up = false;
			}
			else {

				// MAptile does not belong to us, thus border in up dir.
				up = true;

			}
		}

	}
	else {
		// Map end in up direction means its a border.
		up = true;
	}


	other_tile = nullptr;
	if (IsIndexOutOfBound(down_tile[0], down_tile[1]) == false) {

		other_tile = GetMapTileAtWorldPosition(down_tile[0], down_tile[1]);
		if (other_tile) {

			if (_belongMapTileToThisPlayer(other_tile) == false) {

				// The up tile belongs to us, thus no border in up diretion.
				down = false;
			}
			else {

				// MAptile does not belong to us, thus border in up dir.
				down = true;

			}
		}

	}
	else {
		// Map end in up direction means its a border.
		down = true;
	}


	other_tile = nullptr;
	if (IsIndexOutOfBound(left_tile[0], left_tile[1]) == false) {

		other_tile = GetMapTileAtWorldPosition(left_tile[0], left_tile[1]);
		if (other_tile) {

			if (_belongMapTileToThisPlayer(other_tile) == false) {

				// The up tile belongs to us, thus no border in up diretion.
				left = false;
			}
			else {

				// MAptile does not belong to us, thus border in up dir.
				left = true;

			}
		}

	}
	else {
		// Map end in up direction means its a border.
		left = true;
	}


	other_tile = nullptr;
	if (IsIndexOutOfBound(right_tile[0], right_tile[1]) == false) {

		other_tile = GetMapTileAtWorldPosition(right_tile[0], right_tile[1]);
		if (other_tile) {

			if (_belongMapTileToThisPlayer(other_tile) == false) {

				// The up tile belongs to us, thus no border in up diretion.
				right = false;
			}
			else {

				// MAptile does not belong to us, thus border in up dir.
				right = true;

			}
		}

	}
	else {
		// Map end in up direction means its a border.
		right = true;
	}


	return (up && right && left && down);
}

bool Player::_belongMapTileToThisPlayer(MapTile* tile) {

	MapTile* maptile = nullptr;

	for (auto it : m_PlayerCities) {

		for (auto iter : it->m_ClaimedRegions) {

			
			for (auto itr : iter->m_MapTileRegionTiles) {

				maptile = itr;

				if (maptile == tile) return true;
			}

		}

	}

	return false;

}


void City::_determineCityBorderTiles() {

	// Iterate through each regions maptiles.
	MapTileRegion* region = nullptr;
	MapTile* tile = nullptr;

	int tile_up[2], tile_down[2], tile_right[2], tile_left[2];

	bool up = false, down = false, right = false, left = false;


	for (auto it = m_ClaimedRegions.begin(); it != m_ClaimedRegions.end(); ++it) {

		region = *it;

		for (auto iter = region->m_MapTileRegionTiles.begin(); iter != region->m_MapTileRegionTiles.end(); ++iter) {

			tile = *iter;


			tile_up[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0];
			tile_up[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1] - 1;

			tile_down[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0];
			tile_down[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1] + 1;

			tile_right[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0] + 1;
			tile_right[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1];

			tile_left[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0] - 1;
			tile_left[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1];



			if (_isMapTileClaimedByCity(GetMapTileAtWorldPosition(tile_up[0], tile_up[1]))) { // true, if up is own maptile.
				up = true;
			}

			if (_isMapTileClaimedByCity(GetMapTileAtWorldPosition(tile_down[0], tile_down[1]))) {
				down = true;
			}

			if (_isMapTileClaimedByCity(GetMapTileAtWorldPosition(tile_right[0], tile_right[1]))) {
				right = true;
			}

			if (_isMapTileClaimedByCity(GetMapTileAtWorldPosition(tile_left[0], tile_left[1]))) {
				left = true;
			}





			if (up && down && right && left){
				// Means, this tile is surrounded by own, so no border tile.

				// reset for next tile.
				up = down = left = right = false;
				continue;
			}
			else {
				m_CityBorderMapTileVec.push_back(tile);
				up = down = left = right = false;
			}
		}
	}
}


void City::_determineMapTilesBorderDirection() {

	// Iterate through all border tiles.
	MapTile* tile = nullptr;
	int tile_up[2], tile_down[2], tile_right[2], tile_left[2];

	bool border_up = false, border_down = false, border_right = false, border_left = false;


	for (auto it = m_CityBorderMapTileVec.begin(); it != m_CityBorderMapTileVec.end(); ++it) {

		tile = *it;

		tile_up[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0];
		tile_up[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1] - 1;

		tile_down[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0];
		tile_down[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1] + 1;

		tile_right[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0] + 1;
		tile_right[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1];

		tile_left[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0] - 1;
		tile_left[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1];


		// Determine the border direction.
		if (_isMapTileClaimedByCity(GetMapTileAtWorldPosition(tile_up[0], tile_up[1])) == false) {

			// .. border in up direction.
			border_up = true;
		}
		
		if (_isMapTileClaimedByCity(GetMapTileAtWorldPosition(tile_down[0], tile_down[1])) == false) {
			
			// .. border in down direction.
			border_down = true;
		}
		
		if (_isMapTileClaimedByCity(GetMapTileAtWorldPosition(tile_right[0], tile_right[1])) == false) {
			
			// .. border in right direction.
			border_right = true;
		}
		
		if (_isMapTileClaimedByCity(GetMapTileAtWorldPosition(tile_left[0], tile_left[1])) == false) {
			
			// .. border in left direction.
			border_left = true;
		}

		
		// Define decal for appropriate bordertype.
		// In order to get valid results, we must iterate backwards all possibilities.
		if (border_up && border_down && border_right && !border_left) { // Three borders.
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_down_up_right"));

		}
		else if (!border_up && border_down && border_right && border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_left_right_down"));

		}
		else if (border_up && border_down && !border_right && border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_left_up_down"));

		}
		else if (border_up && !border_down && border_right && border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_left_up_right"));

		}
		else if (border_up && border_down && !border_right && !border_left) { // Two borders
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_up_down"));

		}
		else if (border_up && !border_down && border_right && !border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_up_right"));

		}
		else if (border_up && !border_down && !border_right && border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_up_left"));

		}
		else if (!border_up && border_down && border_right && !border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_down_right"));

		}
		else if (!border_up && border_down && !border_right && border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_down_left"));

		}
		else if (!border_up && !border_down && border_right && border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_left_right"));

		}
		else if (border_up && !border_down && !border_right && !border_left) { // One border.
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_up"));

		}
		else if (!border_up && border_down && !border_right && !border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_down"));

		}
		else if (!border_up && !border_down && border_right && !border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_right"));

		}
		else if (!border_up && !border_down && !border_right && border_left) {
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_left"));

		}
		else {
			//throw;
			m_MapTileBorderDirectionMap.insert(std::make_pair(tile, "map_cell_border_down_up_right"));
		}


		// Reset border flags...
		border_up = false, border_down = false, border_right = false, border_left = false;
	}
}


bool City::_isMapTileClaimedByCity(MapTile* maptile) {

	if (maptile == nullptr) return false;

	
	for (auto it : this->m_ClaimedRegions) {
		for (auto iter : it->m_MapTileRegionTiles) {
			if (maptile->m_AssociatedRegion == iter->m_AssociatedRegion) return true;
		}
	}
	
	return false;
}

/*
unsigned int  Unit::_determineMovementPoints() {

	using namespace std;

	int fatigue = this->m_UnitAttributesMap->at(UnitAttributesEnum::UNIT_ATTRIBUTE_FATIGUE);
	int speed = this->m_UnitAttributesMap->at(UnitAttributesEnum::UNIT_ATTRIBUTE_SPEED);

	cout << color(colors::CYAN);
	cout << "Fatigue of " << fatigue << " and Speed of " << speed << " gives ";

	m_MovementPoints = int((fatigue + speed)*2 / (m_Age));


	cout << m_MovementPoints << " Movement Points." << white << endl;

	return m_MovementPoints;
}

void  Unit::_resetMovementPoints() {

	m_MovementPoints = _determineMovementPoints();
}
*/


bool Unit::CanMoveOnMapTile(MapTile* tile) {

	switch (m_UnitMovementType) {
	case UnitMovementType::UNIT_MOVEMENT_TYPE_FLYING:
		return true; // Flying units can fly over mountains, hills... and water.
		break;
	case UnitMovementType::UNIT_MOVEMENT_TYPE_WALKING:

		// Walking units cannot walk over water...
		// Later we deal accordingly with sand and ice.
		if (tile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_WATER_SHALLOW ||
			tile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_WATER_DEEP) {

			return false;
		}
		else {
			return true;
		}
		break;
	case UnitMovementType::UNIT_MOVEMENT_TYPE_SWIMMING:
		
		// Swimming units can only swimm over water...
		if (tile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_WATER_SHALLOW ||
			tile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_WATER_DEEP) {

			return true;
		}
		else if (HasMapTileRiver(tile)) { // Check whether a river is present, then true.
			
			return true;
		}
		else {
			return false;
		}
		break;
	default:
		return false;
		break;
	}
}



bool Unit::DetermineTilesInMovementRange2(std::map<MapTile*, int>* storage) {

	using namespace std;
	cout << APP_COLOR << endl;

	// NOTE:
	// We associate every maptile with a cost, and store it in given map.
	// We define the maptile we are standing on, as cost of 0.

	std::vector<MapTile*> first_neighbors = *_getNeighbouringMapTiles(m_TransformCmp->m_GameWorldSpaceCell[0], m_TransformCmp->m_GameWorldSpaceCell[1]);

	// Other tiles neighbors.
	std::vector<MapTile*> neighbors_vec;


	// First step before recursion, checking immediate neighbors.
	for (auto it : first_neighbors) { // For each neighbor, do:

		// If we can reach it, insert in storage.
		if (m_MovementPoints - (it->m_MovementCostCmp->GetFinalMovementCost(m_EntityRaceCmp->m_EntityRaceString, it, this)) >= 0) {

			storage->try_emplace(it, it->m_MovementCostCmp->GetFinalMovementCost(m_EntityRaceCmp->m_EntityRaceString, it, this));
		}
	}

	first_neighbors.clear();


	// Second step, insert maptile we are standing on as zero cost.
	storage->try_emplace(GetMapTileAtWorldPosition(m_TransformCmp->m_GameWorldSpaceCell[0], m_TransformCmp->m_GameWorldSpaceCell[1]), 0);

	// Third. Copy evrything to vector. Thus we can push to end and  iterate over EVERY tile.
	std::vector<MapTile*> copied_vec;
	for (auto it : *storage) {

		copied_vec.push_back(it.first);
	}


	int cost = 0, parent_cost = 0;
	int loops = 0;

	// Do algorithm:
	for (int i = 0; i < copied_vec.size(); ++i) {


		neighbors_vec = *_getNeighbouringMapTiles(copied_vec[i]);


		for (auto n_itr : neighbors_vec) {


			cost = n_itr->m_MovementCostCmp->GetFinalMovementCost(m_EntityRaceCmp->m_EntityRaceString, n_itr, this);
			parent_cost = storage->at(copied_vec[i]);


			if (m_MovementPoints - (cost + parent_cost) >= 0 &&
				_isMapTileAlreadyInserted(n_itr, storage) == false) {


				storage->try_emplace(n_itr, cost + parent_cost);

				// And save particular maptile for recursive processing of neighbors.
				copied_vec.push_back(n_itr);
			}


		}


	}



	m_MovementCostStorage = storage;

	return true;
}



bool Unit::_isMapTileAlreadyInserted(MapTile* m, std::map<MapTile*, int>* storage) {

	for (auto it : *storage) {

		if (COMPARE_STRINGS_2(m->m_IDCmp->m_ID, it.first->m_IDCmp->m_ID) == 0) {

			return true;
		}
	}

	return false;
}


bool Unit::_isMapTileWeAreStandingOn(MapTile* m) {

	if (m->m_TransformCmp->m_GameWorldSpaceCell[0] == m_TransformCmp->m_GameWorldSpaceCell[0] &&
		m->m_TransformCmp->m_GameWorldSpaceCell[1] == m_TransformCmp->m_GameWorldSpaceCell[1]) {

		return true;
	}

	return false;
}



std::vector<MapTile*>* Unit::_getNeighbouringMapTiles(int xpos, int ypos) {

	std::vector<MapTile*>* vec = new std::vector<MapTile*>();

	int up[2], down[2], right[2], left[2];
	int leftup[2], leftdown[2], rightup[2], rightdown[2];

	up[0] = xpos;
	up[1] = ypos - 1;

	down[0] = xpos;
	down[1] = ypos + 1;

	right[0] = xpos + 1;
	right[1] = ypos;

	left[0] = xpos - 1;
	left[1] = ypos;

	leftup[0] = xpos - 1;
	leftup[1] = ypos - 1;

	leftdown[0] = xpos - 1;
	leftdown[1] = ypos + 1;

	rightup[0] = xpos + 1;
	rightup[1] = ypos - 1;

	rightdown[0] = xpos + 1;
	rightdown[1] = ypos + 1;



	MapTile* tile = nullptr;

	tile = GetMapTileAtWorldPosition(up[0], up[1]);
	if (tile) vec->push_back(tile);
	tile = nullptr;

	tile = GetMapTileAtWorldPosition(down[0], down[1]);
	if (tile) vec->push_back(tile);
	tile = nullptr;

	tile = GetMapTileAtWorldPosition(right[0], right[1]);
	if (tile) vec->push_back(tile);
	tile = nullptr;

	tile = GetMapTileAtWorldPosition(left[0], left[1]);
	if (tile) vec->push_back(tile);
	tile = nullptr;

	tile = GetMapTileAtWorldPosition(leftup[0], leftup[1]);
	if (tile) vec->push_back(tile);
	tile = nullptr;

	tile = GetMapTileAtWorldPosition(leftdown[0], leftdown[1]);
	if (tile) vec->push_back(tile);
	tile = nullptr;

	tile = GetMapTileAtWorldPosition(rightup[0], rightup[1]);
	if (tile) vec->push_back(tile);
	tile = nullptr;

	tile = GetMapTileAtWorldPosition(rightdown[0], rightdown[1]);
	if (tile) vec->push_back(tile);
	tile = nullptr;

	return vec;
}


std::vector<MapTile*>* Unit::_getNeighbouringMapTiles(MapTile* maptile) {

	return _getNeighbouringMapTiles(maptile->m_TransformCmp->m_GameWorldSpaceCell[0], maptile->m_TransformCmp->m_GameWorldSpaceCell[1]);
}


// Move unit to a location.
void Unit::MoveTo(int x_cell, int y_cell, std::map<MapTile*, int>* storage) {

	using namespace std;

	/*
	NOTE:
	We need to move from one tile to next.
	Not from x,y to x´,y´.

	Moreover we need to move so many tiles every TURN, not immediately.
	Furthermore we need to have a defined "way" of moving, that is PATH.
	

	But for now, we test moving directly to destination.
	*/


	// Firstly, check for whether we can reach the maptile.
	MapTile* maptile = nullptr;
	bool flag = false;
	maptile = GetMapTileAtWorldPosition(x_cell, y_cell);
	for (auto it : *storage) {

		if (COMPARE_STRINGS_2(maptile->m_IDCmp->m_ID, it.first->m_IDCmp->m_ID) == 0) {
			flag = true;
		}
	}

	if (flag == false) return;
	/*
	NOTE: I do not understand the part above. What is it for?
	

	Answer:

	We got in storage the maptiles with according movement costs saved.
	So we iterate through it to check, whether the maptile we want to move to is in there.
	Because if not, we cant reach it...
	*/



	int curr_pos_x, curr_pos_y;
	curr_pos_x = m_TransformCmp->m_PosX;
	curr_pos_y = m_TransformCmp->m_PosY;

	int curr_tile[2];
	curr_tile[0] = m_TransformCmp->m_GameWorldSpaceCell[0];
	curr_tile[1] = m_TransformCmp->m_GameWorldSpaceCell[1];


	// Get position of old maptile. Thats the maptile we were standing on before moving..
	MapTile* old_maptile = nullptr;
	old_maptile = GetMapTileAtWorldPosition(curr_tile[0], curr_tile[1]);


	// Maptile we want to move to...
	MapTile* tile = GetMapTileAtWorldPosition(x_cell, y_cell);
	if (tile == nullptr) return;


	// If we are here, then movement is immenent.
	// Thus we have to update units vision:
	// For fog of war.
	// Before we move, decrement mapvision reference count for old maptiles.
	ReverseMapVisionForEntity(this, m_AssociatedPlayer);



	// Here we update the Transform component of the unit to be same as that of maptile.
	// Instant teleportation to that position...
	m_TransformCmp->m_PosX = tile->m_TransformCmp->m_PosX;
	m_TransformCmp->m_PosY = tile->m_TransformCmp->m_PosY;

	// Update the gameworld position...
	m_TransformCmp->m_GameWorldSpaceCell[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0];
	m_TransformCmp->m_GameWorldSpaceCell[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1];

	// .. and the local cell position.
	m_TransformCmp->m_Cell[0] = tile->m_TransformCmp->m_Cell[0];
	m_TransformCmp->m_Cell[1] = tile->m_TransformCmp->m_Cell[1];



	// Lastly, update the content of the maptiles entities vectors.
	old_maptile->m_MapTileEntities->erase(std::find(old_maptile->m_MapTileEntities->begin(), old_maptile->m_MapTileEntities->end(), this)); // Delete "this" Unit from vector of old maptile.
	tile->m_MapTileEntities->push_back(this); // And add "this" Unit to the new maptiles vector.




	// Lastly, decrease movement points.
	m_MovementPoints -= storage->at(maptile);


	cout << APP_ERROR_COLOR << endl;
	cout << "Unit " << this->m_Name << " moved from (" << curr_pos_x << ":" << curr_pos_y << ") ::= (" << curr_tile[0] << ":" << curr_tile[1] << ") to" << endl;
	cout << "(" << m_TransformCmp->m_PosX << ":" << m_TransformCmp->m_PosY << ") ::= (" << m_TransformCmp->m_GameWorldSpaceCell[0] << ":" << m_TransformCmp->m_GameWorldSpaceCell[1] << ")." << white << endl;


	// For fog of war...
	// if unit has moved, we need to update the reference count for the maptiles it sees.
	UpdateMapVisionForEntity(this, m_AssociatedPlayer);


	// CHeck whether a city is at this tile and if so, enter it
	City* city = nullptr;
	city = HasMapTileCityOrFort(tile);
	if (city != nullptr) {


		// NOTE:
		// we need to see whether we should have a std::map or std::vector
		// for storage of units...
		// if map, then we need to have NON-SIMILAR keys...
		//city->m_PresentUnitsMap.emplace(this->m_Name, this);
		city->m_PresentUnitsVector.push_back(this);
		
		cout << APP_COLOR << endl;
		cout << "Unit " << this->m_Name << " entered " << city->m_CityName << " ." << white << endl;
	}


}

// Unit cease to exist.
void Unit::Die() {
	EntitiesStorage::Get()->DeleteGameEntitie(this);
}


















/*
UNIT AI LOGIC.
*/

UnitWaitLogic::UnitWaitLogic(CMPArtificialIntelligence& ai) {

	m_AICmp = &ai;
	m_ManagedUnit = static_cast<Unit*>(m_AICmp->m_ManagedObject);
}

UnitWaitLogic::~UnitWaitLogic() {

}

UnitPatrolLogic::UnitPatrolLogic(CMPArtificialIntelligence& ai, bool circle, States endpointstate) {

	// Specify endpoint state.
	m_TransitState = endpointstate;
	if (circle == false) { // Enforce a valid state to transit to.
		if (m_TransitState == States::STATE_INVALID) throw std::runtime_error(std::string("INVALID OR NO TRANSIT STATE SPECIFIED."));
	}


	m_AICmp = &ai;
	m_ManagedUnit = static_cast<Unit*>(m_AICmp->m_ManagedObject);
}

UnitPatrolLogic::~UnitPatrolLogic() {

}

UnitMoveLogic::UnitMoveLogic(CMPArtificialIntelligence& ai) {

	m_AICmp = &ai;
	m_ManagedUnit = static_cast<Unit*>(m_AICmp->m_ManagedObject);
}

UnitMoveLogic::~UnitMoveLogic() {

}

UnitAttackLogic::UnitAttackLogic(CMPArtificialIntelligence& ai) {

	m_AICmp = &ai;
	m_ManagedUnit = static_cast<Unit*>(m_AICmp->m_ManagedObject);
}

UnitAttackLogic::~UnitAttackLogic() {

}


UnitDefendLogic::UnitDefendLogic(CMPArtificialIntelligence& ai) {

	m_AICmp = &ai;
	m_ManagedUnit = static_cast<Unit*>(m_AICmp->m_ManagedObject);
}

UnitDefendLogic::~UnitDefendLogic() {

}

UnitDieLogic::UnitDieLogic(CMPArtificialIntelligence& ai) {

	m_AICmp = &ai;
	m_ManagedUnit = static_cast<Unit*>(m_AICmp->m_ManagedObject);
}

UnitDieLogic::~UnitDieLogic() {

}


UnitSearchLogic::UnitSearchLogic(CMPArtificialIntelligence& ai) {

	m_AICmp = &ai;
	m_ManagedUnit = static_cast<Unit*>(m_AICmp->m_ManagedObject);
}

UnitSearchLogic::~UnitSearchLogic() {

}


UnitFleeLogic::UnitFleeLogic(CMPArtificialIntelligence& ai) {

	m_AICmp = &ai;
	m_ManagedUnit = static_cast<Unit*>(m_AICmp->m_ManagedObject);
}

UnitFleeLogic::~UnitFleeLogic() {

}








void UnitFleeLogic::executeStateLogic() {

	using namespace std;



	cout << color(colors::DARKGREEN);
	cout << "UnitFleeLogic::executeStateLogic() executed for ";
	cout << this->m_ManagedUnit->m_Name << white << endl;
}

void UnitSearchLogic::executeStateLogic() {

	using namespace std;




	cout << color(colors::DARKGREEN);
	cout << "UnitSearchLogic::executeStateLogic() executed for ";
	cout << this->m_ManagedUnit->m_Name << white << endl;
}

void UnitDieLogic::executeStateLogic() {

	using namespace std;




	cout << color(colors::DARKGREEN);
	cout << "UnitDieLogic::executeStateLogic() executed for ";
	cout << this->m_ManagedUnit->m_Name << white << endl;
}

void UnitDefendLogic::executeStateLogic() {

	using namespace std;




	cout << color(colors::DARKGREEN);
	cout << "UnitDefendLogic::executeStateLogic() executed for ";
	cout << this->m_ManagedUnit->m_Name << white << endl;
}

void UnitAttackLogic::executeStateLogic() {

	using namespace std;




	cout << color(colors::DARKGREEN);
	cout << "UnitAttackLogic::executeStateLogic() executed for ";
	cout << this->m_ManagedUnit->m_Name << white << endl;
}



olc::vd2d UnitMoveLogic::_getMapTileMiddle(int xpos, int ypos) {

	MapTile* maptile = nullptr;
	maptile = GetMapTileAtWorldPosition(xpos, ypos);

	if (maptile) {

		double x = (double)maptile->m_TransformCmp->m_PosX + 32;
		double y = (double)maptile->m_TransformCmp->m_PosY + 32;

		return { x, y };
	}

	return { 999.0, 999.0 };
}



void UnitMoveLogic::executeStateLogic() {

	using namespace std;

	// We have in vec the movement cost tiles.
	// Iterate through all
	// and get the one, which is the nearest to the objective maptile position.
	// To that one we move to.

	// Such we do not take enemy units into account.
	// Nor do we take some tactical decisions into account.

	
	int current_smallest_cost = 999; // Saves smallest cost for neighbor iteration.


	// Get vector with movement cost maptiles.
	Unit* unit = this->m_ManagedUnit;
	unit->m_MovementCostStorage = new std::map<MapTile*, int>();
	unit->DetermineTilesInMovementRange2(unit->m_MovementCostStorage);


	// Get Endpoint.
	// Go through all maptiles and test which one has least distance to destination.
	olc::vi2d objective_position = unit->m_MovementObjectives.front(); // Position of the objective.
	olc::vi2d endpoint = objective_position;

	// For debugging print all movement objectives:
	cout << color(colors::DARKRED);
	cout << "Movement Objectives for " << unit->m_Name << " :" << endl;
	for (auto it : unit->m_MovementObjectives) {

		cout << "(" << it.x << ":" << it.y << ")" << endl;
	}
	cout << white << endl;




	double distance = 999.0; // saves the current distance.

	// Find the nearest endpoint to objective.
	for (auto it : *unit->m_MovementCostStorage) {

		// Try solve with pythogoras´ theorem: sqrt( (x2-x1)^2 + (y2-y1)^2  ) is the distance.

		// To solve the problem, we check which tile has the shortest distance from endpoint.
		//olc::vi2d tile_pos = { it.first->m_TransformCmp->m_GameWorldSpaceCell[0], it.first->m_TransformCmp->m_GameWorldSpaceCell[1] };
		//double new_distance = sqrt( pow((objective_position.y-objective_position.x), 2.0) + pow((tile_pos.y-tile_pos.x), 2.0) );

		olc::vd2d tile_pos = _getMapTileMiddle(it.first->m_TransformCmp->m_GameWorldSpaceCell[0], it.first->m_TransformCmp->m_GameWorldSpaceCell[1]);
		olc::vd2d obj_pos = _getMapTileMiddle(objective_position.x, objective_position.y);

		double new_distance = sqrt(pow((obj_pos.x - tile_pos.x), 2.0) + pow((obj_pos.y - tile_pos.y), 2.0));
		
		if (new_distance < distance) {

			distance = new_distance;
			//endpoint = tile_pos;
			endpoint = { it.first->m_TransformCmp->m_GameWorldSpaceCell[0] ,it.first->m_TransformCmp->m_GameWorldSpaceCell[1] };
			
			cout << APP_ERROR_COLOR;
			cout << "Current shortest distance has maptile (" << endpoint.x << ":" << endpoint.y << ")" << " of " << distance << white << endl;
		}
	}

	
	// If endpoint is directly reachable, just move there.
	for (auto it : *unit->m_MovementCostStorage) {

		if (it.first->m_TransformCmp->m_GameWorldSpaceCell[0] == endpoint.x && it.first->m_TransformCmp->m_GameWorldSpaceCell[1] == endpoint.y) {


			m_MovementVector.push_back(endpoint);
			unit->MoveTo(m_MovementVector.front().x, m_MovementVector.front().y);

			// Pop local movement vector and unitwise movement objective.
			pop_front(m_MovementVector);
			pop_front(unit->m_MovementObjectives);

			return;
		}
	}
	// Else execute pathfinding algorithm.

	// TODO:
	// Check whether we need the algorithm below.
	// It looks like we do not need it.


	/*
	// In endpoint we have our local objective we are moving to.
	// Start the algorithm.
	MapTile* currently_chosen_maptile = nullptr;
	currently_chosen_maptile = GetMapTileAtWorldPosition(endpoint.x, endpoint.y); // This maptile MUST be valid. As its in the movement cost map.


	// Maptile with minimal movement cost for current chosen maptile.
	MapTile* min_neighbor_maptile = nullptr;

	bool logarithm_end = false;
	while (!logarithm_end) {

		int x = currently_chosen_maptile->m_TransformCmp->m_GameWorldSpaceCell[0];
		int y = currently_chosen_maptile->m_TransformCmp->m_GameWorldSpaceCell[1];

		// Iterate through all maptiles in vector.
		for (auto it : *unit->m_MovementCostStorage) {

			// Get only direct neighbors of current chosen maptile, and do algorithm for them...
			if (_isMaptTileDirectNeighbor(x, y, it.first)) {


				// Get maptile if its cost is smaller than current smallest maptile cost.
				if (!min_neighbor_maptile) { // ..only needed in the beginning.

					min_neighbor_maptile = currently_chosen_maptile;
				}
				else if (unit->m_MovementCostStorage->at(min_neighbor_maptile) > unit->m_MovementCostStorage->at(currently_chosen_maptile)) {

					min_neighbor_maptile = currently_chosen_maptile;
				}
			}
		}


		// Change the curr. chosen maptile for reiteration...
		currently_chosen_maptile = min_neighbor_maptile;


		// Save minimal movement maptiles in movement vector for moveTo execution.
		m_MovementVector.push_back(olc::vi2d(currently_chosen_maptile->m_TransformCmp->m_GameWorldSpaceCell[0],
											 currently_chosen_maptile->m_TransformCmp->m_GameWorldSpaceCell[1]));

		// If true, we reached enpoint so algorithm ends...
		if ((currently_chosen_maptile->m_TransformCmp->m_GameWorldSpaceCell[0] == endpoint.x) &&
			(currently_chosen_maptile->m_TransformCmp->m_GameWorldSpaceCell[1] == endpoint.y)) {

			logarithm_end = true;
		}
	}

	 
	// After logarithms end, if m_MovementVector is not empty, execute movements for unit.
	while (m_MovementVector.size() > 0) {

		cout << color(colors::WHITE);
		cout << "Movement vector for " << unit->m_Name << " :" << endl;
		for (auto it : m_MovementVector) {

			cout << "("<< it.x << ":" << it.y << ")" << endl;

		}
		cout << white << endl;


		unit->MoveTo(m_MovementVector.front().x, m_MovementVector.front().y);
		pop_front(m_MovementVector);
	}
	*/
}



bool UnitMoveLogic::_isMaptTileDirectNeighbor(int xpos, int ypos, MapTile* maptile) {

	// x and y is position of the to be tested maptile.
	int x = maptile->m_TransformCmp->m_GameWorldSpaceCell[0];
	int y = maptile->m_TransformCmp->m_GameWorldSpaceCell[1];

	// We have to test 8 directions...
	if (x == (xpos + 1) && y == (ypos)) { // right

		return true; // Hes right from us...
	}
	else if (x == (xpos - 1) && y == (ypos)) { // left

		return true; // Hes left from us...
	}
	else if (x == (xpos) && y == (ypos - 1)) { // up

		return true; // Hes up from us...
	}
	else if (x == (xpos) && y == (ypos + 1)) { // down

		return true; // Hes up from us...
	}
	else if (x == (xpos - 1) && y == (ypos - 1)) { // left up

		return true; // Hes up from us...
	}
	else if (x == (xpos + 1) && y == (ypos - 1)) { // right up

		return true; // Hes up from us...
	}
	else if (x == (xpos - 1) && y == (ypos + 1)) { // left down

		return true; // Hes up from us...
	}
	else if (x == (xpos + 1) && y == (ypos + 1)) { // right down

		return true; // Hes up from us...
	}
	else {
		return false;
	}
}



/*
void UnitMoveLogic::executeStateLogic() {

	using namespace std;

	// Movemnt objective in m_MovementObjectives.
	Unit* unit = this->m_ManagedUnit;

	olc::vi2d own_pos = olc::vi2d(unit->m_TransformCmp->m_GameWorldSpaceCell[0], unit->m_TransformCmp->m_GameWorldSpaceCell[1]);
	olc::vi2d objective_pos = unit->m_MovementObjectives.front();
	unit->m_MovementCostStorage = new std::map<MapTile*, int>();

	int loop_counter = 0;
	while(unit->GetMovementPoints() > 0) {

		if (loop_counter > unit->GetMovementPoints()) return;

		// Print debug information.
		cout << color(colors::DARKMAGENTA);
		cout << unit->m_Name << " movement points: " << unit->GetMovementPoints() << endl;

		cout << "Movement objectives: " << unit->m_MovementObjectives.size() << white << endl;
		for (auto it : unit->m_MovementObjectives) {
			cout << "	Objective: ("<< it.x << ":" << it.y << ")";
		}
		cout << white << endl;


		// Updates up front.
		// We have to update own position as we move on... Else we risk having an endless loop.
		own_pos = olc::vi2d(unit->m_TransformCmp->m_GameWorldSpaceCell[0], unit->m_TransformCmp->m_GameWorldSpaceCell[1]);

		// We must check whether we reached this movement point and can get next.
		if (_movementPointReached(own_pos.x, own_pos.y)) {


			// Remove first movement objective.
			pop_front(unit->m_MovementObjectives);

			if (unit->m_MovementObjectives.size() > 0) {

				// Reset movement objectve.
				objective_pos = unit->m_MovementObjectives.front();
			}
			else { // No movement Points. Quit Move logic.
				return;
			}
		}







		// The ALGORITHM itself.
		int width = objective_pos.x - own_pos.x;
		int height = objective_pos.y - own_pos.y;

		cout << APP_ERROR_COLOR;
		cout << "Try moving to (" << objective_pos.x << ":" << objective_pos.y << ")" << endl;
		cout << "Width ::= " << width << " and Height ::=" << height << white << endl;


		// Go in direction of breadth..
		if (width < 0 && height < 0) { // Go diagonally left up

			// Move unit.
			// Movement is done iterative, means 1 tile by 1 tile.
			unit->DetermineTilesInMovementRange2(unit->m_MovementCostStorage);
			unit->MoveTo(own_pos.x - 1, own_pos.y - 1);

		}
		else if (width > 0 && height > 0) { // Go right up


			// Move unit.
			// Movement is done iterative, means 1 tile by 1 tile.
			unit->DetermineTilesInMovementRange2(unit->m_MovementCostStorage);
			unit->MoveTo(own_pos.x + 1, own_pos.y + 1);

		}
		else if (width < 0 && height > 0) { // Go diagonally left down. 

			// Move unit.
			// Movement is done iterative, means 1 tile by 1 tile.
			unit->DetermineTilesInMovementRange2(unit->m_MovementCostStorage);
			unit->MoveTo(own_pos.x - 1, own_pos.y + 1);

		}
		else if (width > 0 && height < 0) { // Go diagonally right down

			// Move unit.
			// Movement is done iterative, means 1 tile by 1 tile.
			unit->DetermineTilesInMovementRange2(unit->m_MovementCostStorage);
			unit->MoveTo(own_pos.x + 1, own_pos.y - 1);

		}
		if (width > 0) { // Go right.

			// Move unit.
			// Movement is done iterative, means 1 tile by 1 tile.
			unit->DetermineTilesInMovementRange2(unit->m_MovementCostStorage);
			unit->MoveTo(own_pos.x + 1, own_pos.y);

		}
		else if (width < 0) { // Go left.


			// Move unit.
			// Movement is done iterative, means 1 tile by 1 tile.
			unit->DetermineTilesInMovementRange2(unit->m_MovementCostStorage);
			unit->MoveTo(own_pos.x - 1, own_pos.y);

		}
		else if (height > 0) { // Go down. 

			// Move unit.
		    // Movement is done iterative, means 1 tile by 1 tile.
			unit->DetermineTilesInMovementRange2(unit->m_MovementCostStorage);
			unit->MoveTo(own_pos.x, own_pos.y + 1);

		}
		else if (height < 0) { // Go up.

			// Move unit.
			// Movement is done iterative, means 1 tile by 1 tile.
			unit->DetermineTilesInMovementRange2(unit->m_MovementCostStorage);		
			unit->MoveTo(own_pos.x, own_pos.y - 1);

		}
		else { // No possibilities to go. Change state.

			return;
		}


		loop_counter++;
}

	cout << color(colors::DARKGREEN);
	cout << "UnitMoveLogic::executeStateLogic() executed for ";
	cout << this->m_ManagedUnit->m_Name << white << endl;
}
*/



bool UnitMoveLogic::_movementPointReached(int our_xpos, int our_ypos) {

	Unit* unit = this->m_ManagedUnit;
	olc::vi2d obj_pos = unit->m_MovementObjectives.front();

	if (our_xpos == obj_pos.x &
		our_ypos == obj_pos.y) {
		return true;
	}

	return false;
}




void UnitPatrolLogic::executeStateLogic() {

	/*
	NOTE: TODO:
	As we have now a new movement system, we need to redo the patroling logic.

	Instead of moving the unit here, we issue movement orders, and at
	the end of turn, the unit executes them.
	*/

	using namespace olc;
	using namespace std;

	/*
	cout << color(colors::DARKGREEN);
	cout << "UnitPatrolLogic::executeStateLogic() executed for ";
	cout << this->m_ManagedUnit->m_Name << white << endl;
	*/


	Unit* object = m_ManagedUnit;

	if (object) {

		cout << color(colors::DARKGREEN);
		cout << "Begin Patroling routine for " << object->m_Name << "." << white << endl;


		if (m_PatrolPointReached == false) {
			
			vi2d p1 = vi2d(m_PatrolPoints[0].x, m_PatrolPoints[0].y); // Point to reach, coordinates are maptile positions.
			vi2d p2 = vi2d(object->m_TransformCmp->m_GameWorldSpaceCell[0], object->m_TransformCmp->m_GameWorldSpaceCell[1]); // Where we are.


			cout << color(colors::GREEN);
			cout << "Patrol from (" << p2.x << ":" << p2.y << ")" << " to Patrolpoint (" << p1.x << ":" << p1.y << ")" << white << endl;



			vi2d endpoint;

			if (p1.x > p2.x) endpoint.x = p2.x + 1;
			if (p1.x < p2.x) endpoint.x = p2.x - 1;
			if (p1.x == p2.x) endpoint.x = p2.x; // X position reached.

			if (p1.y > p2.y) endpoint.y = p2.y + 1;
			if (p1.y < p2.y) endpoint.y = p2.y - 1;
			if (p1.y == p2.y) endpoint.y = p2.y; // Y position reached.


			// We are giving the worldmap cell coordinates which we wish to reach.
			//object->MoveTo(endpoint.x, endpoint.y, m_ManagedUnit->m_MovementCostStorage);


			/*
			// Issue movement order by storing it.
			int movePoint[2];
			movePoint[0] = endpoint.x;
			movePoint[1] = endpoint.y;
			*/

			// Patroling logic orders movement issues to the patroling points, if there are any, else
			// change state of the unit.
			// If something happens during patrol, e.g. another players unit is sighted, we can here adjust what happens.

			// Try move directly to patrolpoint...
			object->m_MovementObjectives.push_back(olc::vi2d(p1.x, p1.y));
			//object->m_MovementObjectives.push_back(movePoint);
			

			// Change state and execute movement obj.
			object->m_AICmp->ChangeState(States::STATE_MOVE);
			object->m_AICmp->TryExecuteStateLogic();


			// Change back to prev. state.
			object->m_AICmp->ChangeState(States::STATE_PATROL);
			//object->m_AICmp->TryExecuteStateLogic();



			/*
			vi2d left = (p1 - p2);
			cout << color(colors::CYAN) << object->m_Name << " left to reach patrolpoint ::= " << left.str() << white << endl;
			*/

			// If our position equals position we aim for, then point reached.
			if ((p1 - vi2d(object->m_TransformCmp->m_GameWorldSpaceCell[0], object->m_TransformCmp->m_GameWorldSpaceCell[1])) == vi2d(0, 0)) m_PatrolPointReached = true;

		}
		else {

			if (m_TransitState != States::STATE_INVALID && m_PatrolPoints.size() > 0) { // Valid transit state given => no looping of patrol route.

				if (m_PatrolPoints.size() > 0) { // Not all points reached, patrol further.

					m_PatrolPoints.erase(m_PatrolPoints.begin());
					m_PatrolPointReached = false;


					if (m_PatrolPoints.size() == 0) { // All patrol points reached, change state.

						object->m_AICmp->ChangeState(m_TransitState);

						cout << color(colors::DARKGREEN);
						cout << "Patroling routine for " << object->m_Name << " complete." << white << endl;
					}
				}
			}
			else { // circle = true => looping of patrol route.

				// Append the current reached patrol point to the end.
				m_PatrolPoints.push_back(m_PatrolPoints[0]);
				m_PatrolPoints.erase(m_PatrolPoints.begin());

				m_PatrolPointReached = false;

				cout << color(colors::DARKGREEN);
				cout << "Patroling point reached for " << object->m_Name << ". Continue to next Patroling point." << white << endl;
			}
		}

	}
	else {
		return;
	}
}

void UnitWaitLogic::executeStateLogic() {

	using namespace std;




	cout << color(colors::DARKGREEN);
	cout << "UnitWaitLogic::executeStateLogic() executed for ";
	cout << this->m_ManagedUnit->m_Name << white << endl;
}


void Player::_initMapVisibilityMatrix() {


	for (int i = 0; i < MAP_SIZE; ++i) {
		for (int j = 0; j < MAP_SIZE; ++j) {

			// Set initially every tile, whole map, as unexplored.
			m_MapVisibility[i][j] = 0;
		}
	}
}


void City::ResetVisibility() {

	// Firstly, reset the visibility for all maptiles.
	// Needed beacuse we might decrease the borders of the city.

	// First:
	std::vector<MapTile*> vec1;

	// Iterate through all regions maptiles and set it as visible.
	for (auto it : m_ClaimedRegions) {

		for (auto itr : it->m_MapTileRegionTiles) {


			m_AssociatedPlayer->m_MapVisibility[itr->m_TransformCmp->m_GameWorldSpaceCell[0]][itr->m_TransformCmp->m_GameWorldSpaceCell[1]] -= (m_AssociatedPlayer->m_MapVisibility[itr->m_TransformCmp->m_GameWorldSpaceCell[0]][itr->m_TransformCmp->m_GameWorldSpaceCell[1]] == 0) ? 0 : 1;


			vec1.push_back(itr);
		}
	}

	m_AssociatedPlayer->m_MapVisibility[m_TransformCmp->m_GameWorldSpaceCell[0]][m_TransformCmp->m_GameWorldSpaceCell[1]] -= (m_AssociatedPlayer->m_MapVisibility[m_TransformCmp->m_GameWorldSpaceCell[0]][m_TransformCmp->m_GameWorldSpaceCell[1]] == 0) ? 0 : 1;


	// See how we can make direct neighbors of those maptiles as visible too.
	// In vec are all maptiles for which we can set them as visible.
	std::vector<MapTile*> temp1;
	for (auto it : vec1) {

		GetPrimaryMapTilesAroundSelf(it->m_TransformCmp->m_GameWorldSpaceCell[0], it->m_TransformCmp->m_GameWorldSpaceCell[1], &temp1);
	}

	// Iterate through those neighbors and set them as visible.
	for (auto it : temp1) {

		m_AssociatedPlayer->m_MapVisibility[it->m_TransformCmp->m_GameWorldSpaceCell[0]][it->m_TransformCmp->m_GameWorldSpaceCell[1]] -= (m_AssociatedPlayer->m_MapVisibility[it->m_TransformCmp->m_GameWorldSpaceCell[0]][it->m_TransformCmp->m_GameWorldSpaceCell[1]] == 0) ? 0 : 1;
	}

}


void City::UpdateVisibility() {


	// Second:
	// Make new visibility.
	std::vector<MapTile*> vec;

	// Iterate through all regions maptiles and set it as visible.
	for (auto it : m_ClaimedRegions) {

		for (auto itr : it->m_MapTileRegionTiles) {


			m_AssociatedPlayer->m_MapVisibility[itr->m_TransformCmp->m_GameWorldSpaceCell[0]][itr->m_TransformCmp->m_GameWorldSpaceCell[1]] += (m_AssociatedPlayer->m_MapVisibility[itr->m_TransformCmp->m_GameWorldSpaceCell[0]][itr->m_TransformCmp->m_GameWorldSpaceCell[1]] == 0) ? 2 : 1;
		

			vec.push_back(itr);
		}
	}

	m_AssociatedPlayer->m_MapVisibility[m_TransformCmp->m_GameWorldSpaceCell[0]][m_TransformCmp->m_GameWorldSpaceCell[1]] += (m_AssociatedPlayer->m_MapVisibility[m_TransformCmp->m_GameWorldSpaceCell[0]][m_TransformCmp->m_GameWorldSpaceCell[1]] == 0) ? 2 : 1;


	// See how we can make direct neighbors of those maptiles as visible too.
	// In vec are all maptiles for which we can set them as visible.
	std::vector<MapTile*> temp;
	for (auto it : vec) {

		GetPrimaryMapTilesAroundSelf(it->m_TransformCmp->m_GameWorldSpaceCell[0], it->m_TransformCmp->m_GameWorldSpaceCell[1], &temp);
	}

	// Iterate through those neighbors and set them as visible.
	for (auto it : temp) {

		m_AssociatedPlayer->m_MapVisibility[it->m_TransformCmp->m_GameWorldSpaceCell[0]][it->m_TransformCmp->m_GameWorldSpaceCell[1]] += (m_AssociatedPlayer->m_MapVisibility[it->m_TransformCmp->m_GameWorldSpaceCell[0]][it->m_TransformCmp->m_GameWorldSpaceCell[1]] == 0) ? 2 : 1;
	}
}



bool DoesPlayerCityFulfillRequirementsForBuilding(City* city, std::string building_name, int slot) {

	
	// First, check for city size.
	bool race_req = false;
	int needed_size = g_pBuildingsRequirementsMap.at(building_name)->m_PopulationCountRequirement;
	
	if (city->m_CitySize < needed_size) return false;



	// Check for race req.
	if (COMPARE_STRINGS(g_pBuildingsRequirementsMap.at(building_name)->m_RaceRequirement, "All") == 0 ||
		COMPARE_STRINGS_2(g_pBuildingsRequirementsMap.at(building_name)->m_RaceRequirement, city->m_AssociatedPlayer->GetPlayersRace()) == 0) {

		race_req = true;
	}

	if (!race_req) return false;





	// Check for slot.
	switch (g_pBuildingsRequirementsMap.at(building_name)->m_BuildingSlotType) {
	case City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_STANDARD:

		// Check for the right slot number.
		// Std. slots are 1-9.
		if (slot > 9) return false;

		break;
	case City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_PORT:

		// Port slots are 12-13.
		if (slot < 12) return false;

		break;
	case City::CityBuildingSlotType::CITY_BUILDING_SLOT_TYPE_SPECIAL:

		// Special slots are 10-11.
		if (slot < 10 ||
			slot > 11) return false;

		break;

	default:

		// Something else weird -> in all cases error...
		// Maybe good to give out debug message.
		return false;
		break;
	}



	// Check for tech req.
	std::vector<std::string> needed_tech_vec = *g_pBuildingTechRequirementsMap.at(building_name);
	for (auto it : needed_tech_vec) {

		// Check whether player has researched needed technologies for the building...
		if (HasPlayerTech(it, city->m_AssociatedPlayer) == false) {
			return false;
		}
	}



	// Check for Tier of player..
	if (HasPlayerNeededTier(g_pBuildingsRequirementsMap.at(building_name)->m_BuildingTier, city->m_AssociatedPlayer) == false) {

		return false;
	}
	

	// Everything checked and player can build building in his city.
	return true;
}


std::vector<std::string>* GetAvailableBuildingsForPlayerOnSlot(City* city, int slot) {

	using namespace std;

	std::vector<std::string> *vec = new std::vector<std::string>();


	// Cycle through all registered buildings...
	for (auto it : g_pBuildingsRequirementsMap) {

		if (DoesPlayerCityFulfillRequirementsForBuilding(city, it.first, slot)) {

			vec->push_back(it.first); // Store building we can build.
		}

	}


	return vec;
}



bool HasPlayerTech(std::string tech, Player* player) {

	for (auto it : player->m_PlayersTechnologies) {

		if (COMPARE_STRINGS_2(tech, it.first) == 0) {

			return(it.second == 1) ? true : false;
		}
	}
	
	return false;
}


bool HasPlayerNeededTier(BuildingTier tier, Player* player) {

	int needed_tier = -1, player_tier = -1;

	switch (tier) {
	case BuildingTier::BUILDING_TIER_1:
		needed_tier = 1;
		break;
	case BuildingTier::BUILDING_TIER_2:
		needed_tier = 2;
		break;
	case BuildingTier::BUILDING_TIER_3:
		needed_tier = 3;
		break;
	default:
		return false;
		break;
	}

	switch (player->m_PlayerTechnologyTier) {
	case TechTier::TECH_TIER_1:
		player_tier = 1;
		break;
	case TechTier::TECH_TIER_2:
		player_tier = 2;
		break;
	case TechTier::TECH_TIER_3:
		player_tier = 3;
		break;
	default:
		return false;
		break;
	}

	return (player_tier >= needed_tier) ? true : false;
}



bool HasPlayerNeededTier(int tier, Player* player) {

	int player_tier = -1;
	switch (player->m_PlayerTechnologyTier) {
	case TechTier::TECH_TIER_1:
		player_tier = 1;
		break;
	case TechTier::TECH_TIER_2:
		player_tier = 2;
		break;
	case TechTier::TECH_TIER_3:
		player_tier = 3;
		break;
	default:
		return false;
		break;
	}


	return(player_tier >= tier) ? true : false;
}


std::string Player::GetPlayersRace() {

	switch (m_PlayerEmpireRace) {
	case CMPEntityRace::Race::RACE_HUMAN:
		return  "Human";
		break;
	case CMPEntityRace::Race::RACE_TROLL:
		return "Troll";
		break;
	case CMPEntityRace::Race::RACE_DWARF:
		return "Dwarf";
		break;
	case CMPEntityRace::Race::RACE_ORC:
		return "Orc";
		break;
	case CMPEntityRace::Race::RACE_HIGHELF:
		return "High Elf";
		break;
	case CMPEntityRace::Race::RACE_DARKELF:
		return "Dark Elf";
		break;
	case CMPEntityRace::Race::RACE_GOBLIN:
		return "Goblin";
		break;
	case CMPEntityRace::Race::RACE_GNOME:
		return "Gnome";
		break;
	default:
		break;
	}

	return "NULL";
}