// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include"StrategyPrototype.h"

Game* Game::m_Game = nullptr;
static olc::vf2d g_vi2dCameraPosition = olc::vf2d(0.0f, 0.0f);
static int ColorValue = 0;

PlayerTurnCounter* PlayerTurnCounter::g_pPlayerTurnCounter = nullptr;

bool Game::OnUserDestroy(){

	DeinitializeUnitTechnologyRequirements();
	DeinitializeBuildingTechnologyRequirements();
	DeinitializeBuildingRequirementsMap();


	m_SpriteStorage.clear();
	m_SpriteResourceMap.clear();

	return true;
}

bool IsPlayersUnit(Player* p, Unit* u) {

	std::vector<Unit*>::iterator it = std::find(p->m_PlayerUnits.begin(), p->m_PlayerUnits.end(), u);

	return ((it == p->m_PlayerUnits.end()) ? false : true);
}


void GetPrimaryMapTilesAroundSelf(int xpos, int ypos, std::vector<MapTile*>* storage) {

	int right[2], left[2], up[2], down[2];
	int left_up[2], left_down[2], right_up[2], right_down[2];

	right[0] = xpos + 1;
	right[1] = ypos;

	left[0] = xpos - 1;
	left[1] = ypos;

	up[0] = xpos;
	up[1] = ypos - 1;

	down[0] = xpos;
	down[1] = ypos + 1;

	left_up[0] = xpos - 1;
	left_up[1] = ypos - 1;

	left_down[0] = xpos - 1;
	left_down[1] = ypos + 1;

	right_up[0] = xpos + 1;
	right_up[1] = ypos - 1;

	right_down[0] = xpos + 1;
	right_down[1] = ypos + 1;



	MapTile* t1, * t2, * t3, * t4, * t5, * t6, * t7, * t8;

#pragma omp parallel
	t1 = GetMapTileAtWorldPosition(right[0], right[1]);
	t2 = GetMapTileAtWorldPosition(left[0], left[1]);
	t3 = GetMapTileAtWorldPosition(up[0], up[1]);
	t4 = GetMapTileAtWorldPosition(down[0], down[1]);
	t5 = GetMapTileAtWorldPosition(left_up[0], left_up[1]);
	t6 = GetMapTileAtWorldPosition(left_down[0], left_down[1]);
	t7 = GetMapTileAtWorldPosition(right_up[0], right_up[1]);
	t8 = GetMapTileAtWorldPosition(right_down[0], right_down[1]);

	
	if (t1) {
		storage->push_back(t1);
	}
	if (t2) {
		storage->push_back(t2);

	}
	if (t3) {
		storage->push_back(t3);

	}
	if (t4) {
		storage->push_back(t4);

	}
	if (t5) {
		storage->push_back(t5);

	}
	if (t6) {
		storage->push_back(t6);

	}
	if (t7) {
		storage->push_back(t7);

	}
	if (t8) {
		storage->push_back(t8);
	}
}


void GetSecondaryMapTilesAroundSelf(int xpos, int ypos, std::vector<MapTile*>* storage) {

}


void UpdateMapVisionForEntity(GameEntity* entt, Player* associated_player) {

	std::vector<MapTile*> vec;
	GetPrimaryMapTilesAroundSelf(entt->m_TransformCmp->m_GameWorldSpaceCell[0], entt->m_TransformCmp->m_GameWorldSpaceCell[1], &vec);

	for (auto it : vec) {

		associated_player->m_MapVisibility[it->m_TransformCmp->m_GameWorldSpaceCell[0]][it->m_TransformCmp->m_GameWorldSpaceCell[1]] +=  (associated_player->m_MapVisibility[it->m_TransformCmp->m_GameWorldSpaceCell[0]][it->m_TransformCmp->m_GameWorldSpaceCell[1]] == 0) ? 2 : 1;
	
	}


	// Increase for ownpos.
	associated_player->m_MapVisibility[entt->m_TransformCmp->m_GameWorldSpaceCell[0]][entt->m_TransformCmp->m_GameWorldSpaceCell[1]] += (associated_player->m_MapVisibility[entt->m_TransformCmp->m_GameWorldSpaceCell[0]][entt->m_TransformCmp->m_GameWorldSpaceCell[1]] == 0) ? 2 : 1;


}


void ReverseMapVisionForEntity(GameEntity* entt, Player* associated_player) {

	std::vector<MapTile*> vec;
	GetPrimaryMapTilesAroundSelf(entt->m_TransformCmp->m_GameWorldSpaceCell[0], entt->m_TransformCmp->m_GameWorldSpaceCell[1], &vec);

	for (auto it : vec) {

		//associated_player->m_MapVisibility[it->m_TransformCmp->m_GameWorldSpaceCell[0]][it->m_TransformCmp->m_GameWorldSpaceCell[1]]--;
		associated_player->m_MapVisibility[it->m_TransformCmp->m_GameWorldSpaceCell[0]][it->m_TransformCmp->m_GameWorldSpaceCell[1]] -= (associated_player->m_MapVisibility[it->m_TransformCmp->m_GameWorldSpaceCell[0]][it->m_TransformCmp->m_GameWorldSpaceCell[1]] == 1) ? 0 : 1;

	}


	// Increase for ownpos.
	//associated_player->m_MapVisibility[entt->m_TransformCmp->m_GameWorldSpaceCell[0]][entt->m_TransformCmp->m_GameWorldSpaceCell[1]]--;
	associated_player->m_MapVisibility[entt->m_TransformCmp->m_GameWorldSpaceCell[0]][entt->m_TransformCmp->m_GameWorldSpaceCell[1]] -= (associated_player->m_MapVisibility[entt->m_TransformCmp->m_GameWorldSpaceCell[0]][entt->m_TransformCmp->m_GameWorldSpaceCell[1]] == 1) ? 0 : 1;

}



bool IsUnitInCityOrFort(City* city, Unit* unit) {

	std::vector<GameEntity*>::iterator it = std::find(city->m_PresentUnitsVector.begin(), city->m_PresentUnitsVector.end(), unit);

	if (it == city->m_PresentUnitsVector.end()) return false;
	else return true;
}

bool IsUnitInCityOrFort(Unit* unit) {

	City* city = nullptr;
	Unit* city_unit = nullptr;

	std::vector<GameEntity*> vec = *EntitiesStorage::Get()->GetCitiesVec();

	for (auto it = vec.begin(); it != vec.end(); ++it) {

		city = reinterpret_cast<City*>(*it);



		for (auto itr = city->m_PresentUnitsVector.begin(); itr != city->m_PresentUnitsVector.end(); ++itr) {

			city_unit = reinterpret_cast<Unit*>(*itr);



			if (COMPARE_STRINGS_2(unit->m_IDCmp->m_ID, city_unit->m_IDCmp->m_ID) == 0) {

				return true;
			}
		}
	}


	return false;
}

City* HasMapTileCityOrFort(MapTile* maptile) {

	City* city = nullptr;

	for (auto it : *maptile->m_MapTileEntities) {

		city = reinterpret_cast<City*>(it);

		if (COMPARE_STRINGS(city->m_IDCmp->m_DynamicTypeName, "City") == 0) {

			return city;
		}
	}

	return nullptr;
}

int MovementCostHelper::GetFinalMovementCost(std::string race, MapTile* maptile, Unit* unit) {

	// We have to check whether this unit type HAS THE ABILITY to move on particular maptile type.
	if (unit->CanMoveOnMapTile(maptile) == false) {
		return 999;
	}

	// Firstly, for flying units, we define standard cost for everything := 2.
	if (unit->m_UnitMovementType == UnitMovementType::UNIT_MOVEMENT_TYPE_FLYING) {
		return 2;
	}




	int cost = 0;

	// Secondly, we deal with walking and swimming units separately:
	if (unit->m_UnitMovementType == UnitMovementType::UNIT_MOVEMENT_TYPE_SWIMMING) {

		// Swimming ...
		for (auto it : *maptile->m_MapTileEntities) {

			if (COMPARE_STRINGS(it->m_IDCmp->m_DynamicTypeName, "River") == 0) { // Get cost for moving on river.

				cost = it->m_MovementCostCmp->GetRaceModifiedMovementCost(race);
			}
		}

		// If no river then get cost for moving on maptile:
		if (cost == 0) {
			cost = maptile->m_MovementCostCmp->GetRaceModifiedMovementCost(race);
		}

	}
	else {

		// Walking...
		
		for (auto it : *maptile->m_MapTileEntities) {

			if (COMPARE_STRINGS(it->m_IDCmp->m_DynamicTypeName, "Forest") == 0) {

				cost = it->m_MovementCostCmp->GetRaceModifiedMovementCost(race);
			}
			else if (COMPARE_STRINGS(it->m_IDCmp->m_DynamicTypeName, "Hills") == 0) {

				cost = it->m_MovementCostCmp->GetRaceModifiedMovementCost(race);
			}
			else if (COMPARE_STRINGS(it->m_IDCmp->m_DynamicTypeName, "Mountains") == 0) {

				cost = it->m_MovementCostCmp->GetRaceModifiedMovementCost(race);
			}

		}

		// Means, no entities on tile and tile is empty.
		if (cost == 0) {
			cost = maptile->m_MovementCostCmp->GetRaceModifiedMovementCost(race);
		}

	}

	return cost;
}


IMGUI* IMGUI::m_IMGUI = nullptr;
int IMGUI::m_WidgetID = 0; // A valid ID is greater 0.


std::string GetColorFromString(std::string color) {

	if (COMPARE_STRINGS(color, "red") == 0) {
		return "unit_player_color_red";
	}
	else if (COMPARE_STRINGS(color, "blue") == 0) {
		return "unit_player_color_blue";
	}
	else if (COMPARE_STRINGS(color, "magenta") == 0) {
		return "unit_player_color_magenta";
	}
	else if (COMPARE_STRINGS(color, "green") == 0) {
		return "unit_player_color_green";
	}
	else if (COMPARE_STRINGS(color, "brown") == 0) {
		return "unit_player_color_brown";
	}
	else if (COMPARE_STRINGS(color, "black") == 0) {
		return "unit_player_color_black";
	}
	else if (COMPARE_STRINGS(color, "orange") == 0) {
		return "unit_player_color_orange";
	}
	else if (COMPARE_STRINGS(color, "yellow") == 0) {
		return "unit_player_color_yellow";
	}
	else{
		return "NULL";
	}
}


Unit* MakeNewUnitAtPos(CMPEntityRace::Race race, UnitMovementType movement_type, Player* p, std::string unit_class, int xpos, int ypos, int x_cell, int y_cell) {

	Unit* u = new Unit(race, movement_type, xpos, ypos, x_cell, y_cell);

	u->SetBirthsign();

	u->SetClass(unit_class);
	
	/*
	u->SetDerivedStats();

	u->UpdateMovementPoints();
	*/

	u->SetPlayer(p);

	UpdateMapVisionForEntity(u, p);

	return u;
}



Unit* SpawnCitizenInCity(City* city, int xpos, int ypos){

	using namespace std;

	Unit* unit = new Unit(city->m_CityRaceCmp->m_EntityRace, UnitMovementType::UNIT_MOVEMENT_TYPE_WALKING,
		xpos, ypos,
		city->m_TransformCmp->m_GameWorldSpaceCell[0], city->m_TransformCmp->m_GameWorldSpaceCell[1]);


	unit->SetBirthsign();
	unit->SetClass("Citizen");
	unit->SetPlayer(city->m_AssociatedPlayer);
	UpdateMapVisionForEntity(unit, city->m_AssociatedPlayer);

	city->AddUnit(unit);

	cout << color(colors::DARKMAGENTA);
	cout << "Unit Spawned: " << unit->m_Name << endl;
	cout << "City: " << city->m_CityName << white << endl;
	

	return unit;
}




Unit* GetUnitAtMapTileFromMousePosition(int xpos, int ypos) {

	std::vector<GameEntity*> vec = *EntitiesStorage::Get()->GetUnitsVec();
	
	Unit* unit = nullptr;

	// We compare the cells of maptile at that position and unit.
	MapTile* tile = nullptr;
	int unit_cell[2], tile_cell[2];

	tile = GetMaptileAtMousePosition(xpos, ypos);
	if (tile) {
		tile_cell[0] = tile->m_TransformCmp->m_GameWorldSpaceCell[0];
		tile_cell[1] = tile->m_TransformCmp->m_GameWorldSpaceCell[1];
	}
	else {
		return nullptr;
	}


	for (auto it = vec.begin(); it != vec.end(); ++it) {

		unit = reinterpret_cast<Unit*>(*it);

		unit_cell[0] = unit->m_TransformCmp->m_GameWorldSpaceCell[0];
		unit_cell[1] = unit->m_TransformCmp->m_GameWorldSpaceCell[1];


		if (unit_cell[0] == tile_cell[0] && unit_cell[1] == tile_cell[1]) {
			return unit;
		}
	}

	return nullptr;
}


std::string IMGUI::_getLastHitButton() {

	if (Game::Get()->GetKey(olc::Key::SPACE).bPressed) {
		return " ";
	}
	if (Game::Get()->GetKey(olc::Key::ENTER).bPressed) {
		return "enter";
	}
	if (Game::Get()->GetKey(olc::Key::BACK).bPressed) {
		return "back";
	}
	if (Game::Get()->GetKey(olc::Key::Q).bPressed) {
		return "a";
	}
	if (Game::Get()->GetKey(olc::Key::W).bPressed) {
		return "w";
	}
	if (Game::Get()->GetKey(olc::Key::E).bPressed) {
		return "e";
	}
	if (Game::Get()->GetKey(olc::Key::R).bPressed) {
		return "r";
	}
	if (Game::Get()->GetKey(olc::Key::T).bPressed) {
		return "t";
	}
	if (Game::Get()->GetKey(olc::Key::Z).bPressed) {
		return "z";
	}
	if (Game::Get()->GetKey(olc::Key::U).bPressed) {
		return "u";
	}
	if (Game::Get()->GetKey(olc::Key::I).bPressed) {
		return "i";
	}
	if (Game::Get()->GetKey(olc::Key::O).bPressed) {
		return "o";
	}
	if (Game::Get()->GetKey(olc::Key::P).bPressed) {
		return "p";
	}
	if (Game::Get()->GetKey(olc::Key::A).bPressed) {
		return "a";
	}
	if (Game::Get()->GetKey(olc::Key::S).bPressed) {
		return "s";
	}
	if (Game::Get()->GetKey(olc::Key::D).bPressed) {
		return "d";
	}
	if (Game::Get()->GetKey(olc::Key::F).bPressed) {
		return "f";
	}
	if (Game::Get()->GetKey(olc::Key::G).bPressed) {
		return "g";
	}
	if (Game::Get()->GetKey(olc::Key::H).bPressed) {
		return "h";
	}
	if (Game::Get()->GetKey(olc::Key::J).bPressed) {
		return "j";
	}
	if (Game::Get()->GetKey(olc::Key::K).bPressed) {
		return "k";
	}
	if (Game::Get()->GetKey(olc::Key::L).bPressed) {
		return "l";
	}
	if (Game::Get()->GetKey(olc::Key::Y).bPressed) {
		return "y";
	}
	if (Game::Get()->GetKey(olc::Key::X).bPressed) {
		return "x";
	}
	if (Game::Get()->GetKey(olc::Key::C).bPressed) {
		return "c";
	}
	if (Game::Get()->GetKey(olc::Key::V).bPressed) {
		return "v";
	}
	if (Game::Get()->GetKey(olc::Key::B).bPressed) {
		return "b";
	}
	if (Game::Get()->GetKey(olc::Key::N).bPressed) {
		return "n";
	}
	if (Game::Get()->GetKey(olc::Key::M).bPressed) {
		return "m";
	}



	return "";
}



UIState* IMGUI::GetUIState() {
	return IMGUI::Get()->m_UIState;
}


void IMGUI::UpdateUISTate() {

	IMGUI::Get()->m_UIState->m_MouseX = Game::Get()->GetMouseX();
	IMGUI::Get()->m_UIState->m_MouseY = Game::Get()->GetMouseY();


}

bool IMGUI::IsHovered(int xpos, int ypos, int width, int height) {

	// Is mouse position in borders of widget.

	bool collision = false;

	float own_x_pos = xpos;
	float own_y_pos = ypos;
	int own_size[2];
	own_size[0] = width;
	own_size[1] = height;


	float mouseX = Game::Get()->GetMouseX();
	float mouseY = Game::Get()->GetMouseY();



	if (own_x_pos < (mouseX) &&
		(own_x_pos + own_size[0]) > mouseX &&
		own_y_pos < (mouseY) &&
		(own_y_pos + own_size[1]) > mouseY) {

		collision = true;
	}

	return (collision);
}



void IMGUI::PrepareIMGUI() {

	// Reset on each frame beginning.
	m_UIState->m_HoveredItem = 0;
}

void IMGUI::FinishIMGUI() {

	
	if (m_UIState->m_MouseDown == -1) { // No mousebutton down...
		m_UIState->m_ActiveItem = 0; // .. thus reset the active item.
	}
	else {
		if (m_UIState->m_MouseDown == 0 && m_UIState->m_ActiveItem == 0) {
			m_UIState->m_LastFocusedWidget = 0;
			m_UIState->m_KeyboardItem = 0;
		}
		if (m_UIState->m_HoveredItem == 0 && m_UIState->m_MouseDown == 0) {
			m_UIState->m_KeyboardItem = 0;
			m_UIState->m_LastFocusedWidget = 0;
		}
		
	}

}



int IMGUI::Slider(int id, int xpos, int ypos, int max_value, int& value) {

	// Calculate mouse Y offset relatiev to widget.
	int widget_width = 16;
	int widget_height = 256;

	int rel_mouse_y_pos = ((256 - 16) * value) / max_value;

	// Check for hovering and activation.
	if (IsHovered(xpos, ypos, widget_width, widget_height)) {

		m_UIState->m_HoveredItem = id;
		if(m_UIState->m_ActiveItem == 0 && m_UIState->m_MouseDown == 0) {

			m_UIState->m_ActiveItem = id;
			m_UIState->m_LastFocusedWidget = id;
		}
	}


	// Rendering button. Basic. The slider underground.
	using namespace olc;
	Game::Get()->FillRect(vi2d(xpos, ypos), vi2d(widget_width, widget_height), *m_DefaultWidgetColor);


	// Slider is being interacted with... So render the sliding object.
	if (m_UIState->m_ActiveItem == id || m_UIState->m_HoveredItem == id) {

		Game::Get()->FillRect(vi2d(xpos, ypos + rel_mouse_y_pos), vi2d(16, 16), *m_DefaultActiveWidgetColor);
	}
	else {

		Game::Get()->FillRect(vi2d(xpos, ypos + rel_mouse_y_pos), vi2d(16, 16), *m_DefaultWidgetElementColor);
	}



	// Update widget value.
	if (m_UIState->m_ActiveItem == id){

		int mousepos = m_UIState->m_MouseY - (ypos);
		if (mousepos < 0) mousepos = 0;
		if (mousepos > 255) mousepos = 255;

		int v = (mousepos * max_value) / 255;

		if (v != value)
		{
			value = v;
			return 1;
		}
	}
	else if (m_UIState->m_LastFocusedWidget == id) {
		return 1;
	}


	return 0;
}



int IMGUI::Textfield(int id, int xpos, int ypos, std::string* buffer) {

	using namespace olc;

	int buffer_length = buffer->length();
	int changed = 0;


	// Whether hovered over textfield.
	// Width and Height are for testing purpose.
	if (IsHovered(xpos, ypos, 256, 25)) {

		m_UIState->m_HoveredItem = id;

		// Mouse button pressed over textfield.
		if (m_UIState->m_ActiveItem == 0 && m_UIState->m_MouseDown == 0) {
			m_UIState->m_ActiveItem = id;
			m_UIState->m_LastFocusedWidget = id;
		}
	}

	/*
	// No widget has keyboard focus, so take it.
	if (m_UIState->m_KeyboardItem == 0) {
		m_UIState->m_KeyboardItem = id;
	}
	*/

	// Present that we have keyboard focus.
	if (m_UIState->m_KeyboardItem == id && m_UIState->m_LastFocusedWidget == id) {

		m_UIState->m_ActiveItem = id;
		Game::Get()->DrawRect(vi2d(xpos - 4, ypos - 4), vi2d(256 + 8, 25 + 8), olc::RED);
	}


	// Draw Textfield.
	if (m_UIState->m_ActiveItem == id || m_UIState->m_HoveredItem == id || m_UIState->m_LastFocusedWidget == id) {

		// .. has some interaction.
		Game::Get()->FillRect(vi2d(xpos, ypos), vi2d(256, 25), *m_DefaultHoveredWidgetColor);
	}
	else {
		// .. has no interaction.
		Game::Get()->FillRect(vi2d(xpos, ypos), vi2d(256, 25), *m_DefaultWidgetColor);
	}

	// Draw input string over textfield.
	Game::Get()->DrawString(vi2d(xpos, ypos), *buffer, *m_DefaultWidgetTextColor);


	// Render a cursos if we have keyboard focus.
	if (m_UIState->m_ActiveItem == id) {
		Game::Get()->DrawString(vi2d(xpos + buffer->length()*8, ypos), "_", *m_DefaultWidgetTextColor);
	}


	// Process keyboard input if we have focus.
	if(m_UIState->m_KeyboardItem == id) {
		std::string s = _getLastHitButton();

		if (COMPARE_STRINGS(s, "") != 0) {

			if (COMPARE_STRINGS(s, "enter") == 0) { // Finish entering textfield.
				m_UIState->m_KeyboardItem = 0;
				m_UIState->m_ActiveItem = 0;
			}
			else if (COMPARE_STRINGS(s, "back") == 0) { // Delete last character.

				if (buffer->length() > 0) {
					buffer->pop_back();
					changed = 1;
				}
			}
			else {
				buffer->append(s);
				changed = 1;
			}
		}
	}

	
	// Check states...
	if (m_UIState->m_MouseDown == 0 &&
		m_UIState->m_HoveredItem == id &&
		m_UIState->m_ActiveItem == id) {

		m_UIState->m_KeyboardItem = id;
	}
	else if (m_UIState->m_LastFocusedWidget != id) {
		m_UIState->m_KeyboardItem = 0;
	}
	

	return changed;
}


int IMGUI::ToolTipButton(int id, int xpos, int ypos, std::string text, std::string tooltiptext){


	int w = text.size() * 8;
	int h = text.size() * 2;

	int tooltip_xpos = 0;
	int tooltip_ypos = 0;

	if (IsHovered(xpos, ypos, w, h)) {

		// Set this button as the hovered item.
		m_UIState->m_HoveredItem = id;


		// Check whether no active item and mouse was pressed over this one.
		if (m_UIState->m_ActiveItem == 0 &&
			m_UIState->m_MouseDown == 0) { // Means left mouse button pressed.

			// No active item and mouse pressed means,
			// this part. item is an active one.
			m_UIState->m_ActiveItem = id;
			m_UIState->m_LastFocusedWidget = id;
		}


		// As we hover, draw the tooltip around widget.
		if (Game::Get()->ScreenWidth() + text.length() * 8 > Game::Get()->ScreenWidth()) {
			tooltip_xpos -= 100;
		}
		if (Game::Get()->ScreenHeight() + text.length() * 8 > Game::Get()->ScreenHeight()) {
			tooltip_ypos -= 100;
		}
		if (xpos - 100 < 0) {
			tooltip_xpos += 100;
		}
		if (ypos - 100 < 0) {
			tooltip_ypos += 100;
		}


		TextButton(GEN_ID, tooltip_xpos, tooltip_ypos, tooltiptext);
	}


	// Rendering button. Basic.
	using namespace olc;
	Game::Get()->FillRect(vi2d(xpos, ypos), vi2d(w, h), *m_DefaultWidgetColor);
	Game::Get()->DrawString(vi2d(xpos + 2, ypos + 2), text, *m_DefaultWidgetTextColor);

	// Rendering button based on its "state".
	if (m_UIState->m_HoveredItem == id) {
		if (m_UIState->m_ActiveItem == id) {

			// If we hover over this button...
			// .. and we click on it...
			// ...give it a new color.
			Game::Get()->FillRect(vi2d(xpos, ypos), vi2d(w, h), *m_DefaultActiveWidgetColor); // Make it "Burn".
			Game::Get()->DrawString(vi2d(xpos + 2, ypos + 2), text, olc::BLACK);
		}
		else {

			// ... Button is just hovered upon.
			Game::Get()->FillRect(vi2d(xpos - 2, ypos - 2), vi2d(w, h), *m_DefaultHoveredWidgetColor);
			Game::Get()->DrawString(vi2d(xpos + 2, ypos + 2), text, *m_DefaultWidgetTextColor);

		}
	}
	else { // We do not hover over this button, so the normal button exprience...

		//Game::Get()->FillRect(vi2d(xpos, ypos), vi2d(64, 48), *m_DefaultWidgetColor);
	}


	// Means button is activated, e.g. clicked.
	if (m_UIState->m_MouseDown == 0 &&
		m_UIState->m_HoveredItem == id &&
		m_UIState->m_ActiveItem == id ||
		m_UIState->m_LastFocusedWidget == id) { // 

		return 1;
	}

	// .. else nothing happend.
	return 0;
}



int IMGUI::ToolTipSpriteButton(int id, int xpos, int ypos, std::string spritename, std::string tooltiptext) {

	
	using namespace olc;

	Decal* decal = nullptr;

	if (m_IMGUIDecalMap.at(spritename) == nullptr) {

		for (auto it : this->m_IMGUISpriteResourceMap) {

			if (COMPARE_STRINGS_2(it.first, spritename) == 0) {

				decal = new Decal(it.second); // Create dynamically new decal for rendering...
				m_IMGUIDecalMap.insert(std::make_pair(spritename, decal));
			}
		}
	}
	else {
		decal = m_IMGUIDecalMap.at(spritename);
	}

	int w = decal->sprite->width;
	int h = decal->sprite->height;


	int tooltip_xpos = 0;
	int tooltip_ypos = 0;

	if (IsHovered(xpos, ypos, w, h)) {

		// Set this button as the hovered item.
		m_UIState->m_HoveredItem = id;


		// Check whether no active item and mouse was pressed over this one.
		if (m_UIState->m_ActiveItem == 0 &&
			m_UIState->m_MouseDown == 0) { // Means left mouse button pressed.

			// No active item and mouse pressed means,
			// this part. item is an active one.
			m_UIState->m_ActiveItem = id;
			m_UIState->m_LastFocusedWidget = id;
		}


		// As we hover, draw the tooltip around widget.
		if (Game::Get()->ScreenWidth() + tooltiptext.length() * 8 > Game::Get()->ScreenWidth()) {
			tooltip_xpos = xpos - 100;
		}
		if (Game::Get()->ScreenHeight() + tooltiptext.length() * 8 > Game::Get()->ScreenHeight()) {
			tooltip_ypos = ypos - 100;
		}
		if (xpos - 100 < 0) {
			tooltip_xpos += w + 100;
		}
		if (ypos - 100 < 0) {
			tooltip_ypos += h + 100;
		}
		TextButton(GEN_ID, tooltip_xpos, tooltip_ypos, tooltiptext);
	}


	// Rendering button. Basic.
	using namespace olc;
	//Game::Get()->FillRect(vi2d(xpos, ypos), vi2d(74, 28), *m_DefaultWidgetColor);
	Game::Get()->DrawDecal(vf2d(xpos, ypos), decal);


	// Rendering button based on its "state".
	if (m_UIState->m_HoveredItem == id) {
		if (m_UIState->m_ActiveItem == id) {

			// If we hover over this button...
			// .. and we click on it...
			// ...give it a new color.
			//Game::Get()->FillRect(vi2d(xpos, ypos), vi2d(74, 28), *m_DefaultActiveWidgetColor); // Make it "Burn".
			Game::Get()->DrawDecal(vf2d(xpos, ypos), decal, vf2d(1.0f, 1.0f), olc::YELLOW);
		}
		else {

			// ... Button is just hovered upon.
			//Game::Get()->FillRect(vi2d(xpos - 2, ypos - 2), vi2d(74, 28), *m_DefaultHoveredWidgetColor);
			Game::Get()->DrawDecal(vf2d(xpos, ypos), decal, vf2d(1.0f, 1.0f), olc::DARK_YELLOW);
		}
	}
	else { // We do not hover over this button, so the normal button exprience...

		//Game::Get()->FillRect(vi2d(xpos, ypos), vi2d(64, 48), *m_DefaultWidgetColor);
	}


	// Means button is activated, e.g. clicked.
	if (m_UIState->m_MouseDown == 0 &&
		m_UIState->m_HoveredItem == id &&
		m_UIState->m_ActiveItem == id ||
		m_UIState->m_LastFocusedWidget == id) { // 

		return 1;
	}

	// .. else nothing happend.
	return 0;
}



int  IMGUI::ToolTipSpriteButton(int id, int xpos, int ypos, std::string spritename, std::string tooltiptext, olc::Pixel teint_color) {


	using namespace olc;

	Decal* decal = nullptr;

	if (m_IMGUIDecalMap.at(spritename) == nullptr) {

		for (auto it : this->m_IMGUISpriteResourceMap) {

			if (COMPARE_STRINGS_2(it.first, spritename) == 0) {

				decal = new Decal(it.second); // Create dynamically new decal for rendering...
				m_IMGUIDecalMap.insert(std::make_pair(spritename, decal));
			}
		}
	}
	else {
		decal = m_IMGUIDecalMap.at(spritename);
	}

	int w = decal->sprite->width;
	int h = decal->sprite->height;


	int tooltip_xpos = 0;
	int tooltip_ypos = 0;

	if (IsHovered(xpos, ypos, w, h)) {

		// Set this button as the hovered item.
		m_UIState->m_HoveredItem = id;


		// Check whether no active item and mouse was pressed over this one.
		if (m_UIState->m_ActiveItem == 0 &&
			m_UIState->m_MouseDown == 0) { // Means left mouse button pressed.

			// No active item and mouse pressed means,
			// this part. item is an active one.
			m_UIState->m_ActiveItem = id;
			m_UIState->m_LastFocusedWidget = id;
		}


		// As we hover, draw the tooltip around widget.
		if (Game::Get()->ScreenWidth() + tooltiptext.length() * 8 > Game::Get()->ScreenWidth()) {
			tooltip_xpos = xpos - 100;
		}
		if (Game::Get()->ScreenHeight() + tooltiptext.length() * 8 > Game::Get()->ScreenHeight()) {
			tooltip_ypos = ypos - 100;
		}
		if (xpos - 100 < 0) {
			tooltip_xpos += w + 100;
		}
		if (ypos - 100 < 0) {
			tooltip_ypos += h + 100;
		}
		TextButton(GEN_ID, tooltip_xpos, tooltip_ypos, tooltiptext);
	}


	// Rendering button. Basic.
	using namespace olc;
	Game::Get()->DrawDecal(vf2d(xpos, ypos), decal, vf2d(1.0f, 1.0f), teint_color);


	// Rendering button based on its "state".
	if (m_UIState->m_HoveredItem == id) {
		if (m_UIState->m_ActiveItem == id) {

			// If we hover over this button...
			// .. and we click on it...
			// ...give it a new color.
			//Game::Get()->FillRect(vi2d(xpos, ypos), vi2d(74, 28), *m_DefaultActiveWidgetColor); // Make it "Burn".
			Game::Get()->DrawDecal(vf2d(xpos, ypos), decal, vf2d(1.0f, 1.0f), olc::YELLOW);
		}
		else {

			// ... Button is just hovered upon.
			//Game::Get()->FillRect(vi2d(xpos - 2, ypos - 2), vi2d(74, 28), *m_DefaultHoveredWidgetColor);
			Game::Get()->DrawDecal(vf2d(xpos, ypos), decal, vf2d(1.0f, 1.0f), olc::DARK_YELLOW);
		}
	}
	else { // We do not hover over this button, so the normal button exprience...

		//Game::Get()->FillRect(vi2d(xpos, ypos), vi2d(64, 48), *m_DefaultWidgetColor);
	}


	// Means button is activated, e.g. clicked.
	if (m_UIState->m_MouseDown == 0 &&
		m_UIState->m_HoveredItem == id &&
		m_UIState->m_ActiveItem == id ||
		m_UIState->m_LastFocusedWidget == id) { // 

		return 1;
	}

	// .. else nothing happend.
	return 0;
}



int IMGUI::TextButton(int id, int xpos, int ypos, std::string text) {

	int width = text.length() * 8 + 2;
	int height = (width / 8 < 10) ? 12 : width / 8;

	if (IsHovered(xpos, ypos, width, height)) {

		// Set this button as the hovered item.
		m_UIState->m_HoveredItem = id;


		// Check whether no active item and mouse was pressed over this one.
		if (m_UIState->m_ActiveItem == 0 &&
			m_UIState->m_MouseDown == 0) { // Means left mouse button pressed.

			// No active item and mouse pressed means,
			// this part. item is an active one.
			m_UIState->m_ActiveItem = id;
			m_UIState->m_LastFocusedWidget = id;
		}
	}


	// Rendering button. Basic.
	using namespace olc;
	Game::Get()->FillRect(vi2d(xpos, ypos), vi2d(width, height), *m_DefaultWidgetColor);
	Game::Get()->DrawString(vi2d(xpos + 2, ypos + 2), text, *m_DefaultWidgetTextColor);

	// Rendering button based on its "state".
	if (m_UIState->m_HoveredItem == id) {
		if (m_UIState->m_ActiveItem == id) {

			// If we hover over this button...
			// .. and we click on it...
			// ...give it a new color.
			Game::Get()->FillRect(vi2d(xpos, ypos), vi2d(width, height), *m_DefaultActiveWidgetColor); // Make it "Burn".
			Game::Get()->DrawString(vi2d(xpos + 2, ypos + 2), text, olc::BLACK);
		}
		else {

			// ... Button is just hovered upon.
			Game::Get()->FillRect(vi2d(xpos - 2, ypos - 2), vi2d(width, height), *m_DefaultHoveredWidgetColor);
			Game::Get()->DrawString(vi2d(xpos + 2, ypos + 2), text, *m_DefaultWidgetTextColor);

		}
	}
	else { // We do not hover over this button, so the normal button exprience...

		//Game::Get()->FillRect(vi2d(xpos, ypos), vi2d(64, 48), *m_DefaultWidgetColor);
	}


	// Means button is activated, e.g. clicked.
	if (m_UIState->m_MouseDown == 0 &&
		m_UIState->m_HoveredItem == id &&
		m_UIState->m_ActiveItem == id ||
		m_UIState->m_LastFocusedWidget == id) { // 

		return 1;
	}

	// .. else nothing happend.
	return 0;
}

int IMGUI::SpriteButton(int id, int xpos, int ypos, std::string spritename) {

	
	using namespace olc;
	Decal* decal = nullptr;

	if (m_IMGUIDecalMap.at(spritename) == nullptr) {

		for (auto it : this->m_IMGUISpriteResourceMap) {

			if (COMPARE_STRINGS_2(it.first, spritename) == 0) {

				decal = new Decal(it.second); // Create dynamically new decal for rendering...
				m_IMGUIDecalMap.insert(std::make_pair(spritename, decal));
			}
		}
	}
	else {
		decal = m_IMGUIDecalMap.at(spritename);
	}


	int w = decal->sprite->width;
	int h = decal->sprite->height;

	if (IsHovered(xpos, ypos, w, h)) {

		// Set this button as the hovered item.
		m_UIState->m_HoveredItem = id;


		// Check whether no active item and mouse was pressed over this one.
		if (m_UIState->m_ActiveItem == 0 &&
			m_UIState->m_MouseDown == 0) { // Means left mouse button pressed.

			// No active item and mouse pressed means,
			// this part. item is an active one.
			m_UIState->m_ActiveItem = id;
			m_UIState->m_LastFocusedWidget = id;
		}
	}


	// Rendering button. Basic.
	using namespace olc;
	//Game::Get()->FillRect(vi2d(xpos, ypos), vi2d(74, 28), *m_DefaultWidgetColor);
	Game::Get()->DrawDecal(vf2d(xpos, ypos), decal);


	// Rendering button based on its "state".
	if (m_UIState->m_HoveredItem == id) {
		if (m_UIState->m_ActiveItem == id) {

			// If we hover over this button...
			// .. and we click on it...
			// ...give it a new color.
			//Game::Get()->FillRect(vi2d(xpos, ypos), vi2d(74, 28), *m_DefaultActiveWidgetColor); // Make it "Burn".
			Game::Get()->DrawDecal(vf2d(xpos, ypos), decal, vf2d(1.0f, 1.0f), olc::YELLOW);
		}
		else {

			// ... Button is just hovered upon.
			//Game::Get()->FillRect(vi2d(xpos - 2, ypos - 2), vi2d(74, 28), *m_DefaultHoveredWidgetColor);
			Game::Get()->DrawDecal(vf2d(xpos, ypos), decal, vf2d(1.0f, 1.0f), olc::DARK_YELLOW);
		}
	}
	else { // We do not hover over this button, so the normal button exprience...

		//Game::Get()->FillRect(vi2d(xpos, ypos), vi2d(64, 48), *m_DefaultWidgetColor);
	}


	// Means button is activated, e.g. clicked.
	if (m_UIState->m_MouseDown == 0 &&
		m_UIState->m_HoveredItem == id &&
		m_UIState->m_ActiveItem == id ||
		m_UIState->m_LastFocusedWidget == id) { // 

		return 1;
	}

	// .. else nothing happend.
	return 0;
}


int IMGUI::Button(int id, int xpos, int ypos) {

	
	if (IsHovered(xpos, ypos, 74, 28)) {

		// Set this button as the hovered item.
		m_UIState->m_HoveredItem = id;


		// Check whether no active item and mouse was pressed over this one.
		if (m_UIState->m_ActiveItem == 0 &&
			m_UIState->m_MouseDown == 0) { // Means left mouse button pressed.

			// No active item and mouse pressed means,
			// this part. item is an active one.
			m_UIState->m_ActiveItem = id;
			m_UIState->m_LastFocusedWidget = id;
		}
	}


	// Rendering button. Basic.
	using namespace olc;
	Game::Get()->FillRect(vi2d(xpos, ypos), vi2d(74, 28), *m_DefaultWidgetColor);


	// Rendering button based on its "state".
	if (m_UIState->m_HoveredItem == id) {
		if (m_UIState->m_ActiveItem == id) {

			// If we hover over this button...
			// .. and we click on it...
			// ...give it a new color.
			Game::Get()->FillRect(vi2d(xpos, ypos), vi2d(74, 28), *m_DefaultActiveWidgetColor); // Make it "Burn".
		}
		else {

			// ... Button is just hovered upon.
			Game::Get()->FillRect(vi2d(xpos - 2, ypos - 2), vi2d(74, 28), *m_DefaultHoveredWidgetColor);

		}
	}
	else { // We do not hover over this button, so the normal button exprience...

		//Game::Get()->FillRect(vi2d(xpos, ypos), vi2d(64, 48), *m_DefaultWidgetColor);
	}


	// Means button is activated, e.g. clicked.
	if (m_UIState->m_MouseDown == 0 &&
		m_UIState->m_HoveredItem == id &&
		m_UIState->m_ActiveItem == id ||
		m_UIState->m_LastFocusedWidget == id) { // 

		return 1;
	}

	// .. else nothing happend.
	return 0;
}






River* MakeNewRiver(std::string spritename, int x_cell_pos, int y_cell_pos) {

	River* r = new River(spritename, "layer3", int(x_cell_pos * SPRITES_WIDTH_AND_HEIGHT), int(y_cell_pos * SPRITES_WIDTH_AND_HEIGHT));
	r->m_TransformCmp->m_GameWorldSpaceCell[0] = x_cell_pos;
	r->m_TransformCmp->m_GameWorldSpaceCell[1] = y_cell_pos;

	return r;
}

bool HasMapTileRiver(MapTile* maptile) {

	GameEntity* entity = nullptr;

	for (auto it = maptile->m_MapTileEntities->begin(); it != maptile->m_MapTileEntities->end(); ++it) {

		entity = *it;
		if (COMPARE_STRINGS(entity->m_IDCmp->m_DynamicTypeName, "River") == 0) return true;
	}

	return false;
}

int GetXPositionOfMapTile(MapTile* tile) {
	return(tile->m_TransformCmp->m_PosX);
}

int GetYPositionOfMapTile(MapTile* tile) {
	return(tile->m_TransformCmp->m_PosY);
}

void SpawnRandomCity() {

	int cell[2];

	cell[0] = Random() % 19;
	cell[1] = Random() % 19;


	int probability = Random() % 2;

	if (probability == 0) {

		if (GetMapTileAtWorldPosition(cell[0], cell[1])->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_TEMPERATE ||
			GetMapTileAtWorldPosition(cell[0], cell[1])->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_TUNDRA ||
			GetMapTileAtWorldPosition(cell[0], cell[1])->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_SAVANNAH ||
			GetMapTileAtWorldPosition(cell[0], cell[1])->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_JUNGLE)
		{

			int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(cell[0], cell[1]));
			int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(cell[0], cell[1]));

			/*
 			City* city = MakeNewCityAtPos("Village", "city_human_small", *EntitiesStorage::Get()->GetPlayersVec()->begin(), xpos, ypos, cell[0], cell[1]);
			city->ClaimRegions();
			
			EntitiesStorage::Get()->AddGameEntitie(city);
			
			using namespace std;
			cout << APP_SUCCESS_COLOR;
			cout << "City created at  XY-(" << city->m_TransformCmp->m_PosX << ":" << city->m_TransformCmp->m_PosY << ") "
				<< " --  Cell-(" << city->m_TransformCmp->m_GameWorldSpaceCell[0] << ":" << city->m_TransformCmp->m_GameWorldSpaceCell[1] << ") ." << white << endl;
			*/
		}

	}
}


Player* GetPlayer(std::string name) {
	
	for (auto it : *EntitiesStorage::Get()->GetPlayersVec()) {

		if (COMPARE_STRINGS_2(name, it->m_PlayerName) == 0) {
			return it;
		}
	}
}

/*
Primary function for each time you want to get a Maptile from an X-Y-Coordinate.
This function considers camera movement and adjust the x-y-value accordingly
to give you dynamically correct the maptile you wish.

It too check for whether at clicked position a maptile exists.
*/
MapTile* GetMaptileAtMousePosition(int x, int y) {

	int x_cell = int((x + g_vi2dCameraPosition.x) / SPRITES_WIDTH_AND_HEIGHT);
	int y_cell = int((y + g_vi2dCameraPosition.y) / SPRITES_WIDTH_AND_HEIGHT);

	if (IsIndexOutOfBound(x_cell, y_cell) == false) {
		return (GetMapTileAtWorldPosition(x_cell, y_cell));
	}

	return nullptr;
}



MapTileRegion* GetRegionAtWorldPosition(int x, int y) {

	int x_cell = int((x + g_vi2dCameraPosition.x)/ SPRITES_WIDTH_AND_HEIGHT);
	int y_cell = int((y + g_vi2dCameraPosition.y) / SPRITES_WIDTH_AND_HEIGHT);

	if (IsIndexOutOfBound(x_cell, y_cell) == false) {
		return (GetMapTileAtWorldPosition(x_cell, y_cell)->m_AssociatedRegion);
	}

	return nullptr;
}

bool RaiseDeepForestRandomly() {

	using namespace std;

	int probability_factor = 0;
	int forests_count = GetTotalForestsCount();
	int coefficient = 0;
	
	coefficient = 0.5f + int((MAP_SIZE * MAP_SIZE) / forests_count);
	if (coefficient >= 8) { // .. enter preservation mode.
		// Interpretation of coefficient:
		// Every "coefficient" maptiles we can see a forest.

		probability_factor = -997; // 50% probablity...

		cout << APP_ERROR_COLOR;
		cout << "ENTERED FOREST-SELF-PRESERVATION MODE: coefficient < 8" << endl;
		cout << "Formula: 0.5f + (20*20)/" << forests_count << " = " << coefficient << white << endl << endl;

	}
	else {
		// .. do nothin for now.
	}

	// Every uneven turn, execute the testing.
	if (Game::Get()->m_TurnCount % 3 == 0) {

		int r = Random() % (999 + probability_factor);
		return ((r == 0) ? true : false);
	}
	else return false;
}


Mountains* MakeNewMountain(std::string spritename, int x_cell_pos, int y_cell_pos) {

	// We draw standardized forests on layer3, so skip this part from the user...
	Mountains* mountain = new Mountains(spritename, "layer2", x_cell_pos * SPRITES_WIDTH_AND_HEIGHT, y_cell_pos * SPRITES_WIDTH_AND_HEIGHT);

	mountain->m_TransformCmp->m_GameWorldSpaceCell[0] = x_cell_pos;
	mountain->m_TransformCmp->m_GameWorldSpaceCell[1] = y_cell_pos;

	return mountain;
}



City* MakeNewCity(bool city, std::string cityname, CMPEntityRace::Race race, Player* player, int x_cell_pos, int y_cell_pos, int citySize) {

	City* c = new City(cityname, city, race, player, x_cell_pos * SPRITES_WIDTH_AND_HEIGHT, y_cell_pos * SPRITES_WIDTH_AND_HEIGHT, citySize);

	c->m_TransformCmp->m_GameWorldSpaceCell[0] = x_cell_pos;
	c->m_TransformCmp->m_GameWorldSpaceCell[1] = y_cell_pos;

	c->Initialize();


	c->UpdateVisibility();


	return c;
}

// This function is very useful for dynamically creating a city, especially
// if the user is moving the camera. With it we can reliably determine the right x-y-position
// for the new city and the right x-y-cell.
City* MakeNewCityAtPos(bool city, std::string cityname, CMPEntityRace::Race race, Player* player, int xpos, int ypos, int set_x_cell_pos, int set_y_cell_pos, int citySize) {

	City* c = new City(cityname, city, race, player, xpos, ypos, citySize);

	c->m_TransformCmp->m_GameWorldSpaceCell[0] = set_x_cell_pos;
	c->m_TransformCmp->m_GameWorldSpaceCell[1] = set_y_cell_pos;

	c->Initialize();


	c->UpdateVisibility();

	return c;

}


Hills* MakeNewHill(std::string spritename, int x_cell_pos, int y_cell_pos) {

	// We draw standardized forests on layer3, so skip this part from the user...
	Hills* hills = new Hills(spritename, "layer2", x_cell_pos * SPRITES_WIDTH_AND_HEIGHT, y_cell_pos * SPRITES_WIDTH_AND_HEIGHT);

	hills->m_TransformCmp->m_GameWorldSpaceCell[0] = x_cell_pos;
	hills->m_TransformCmp->m_GameWorldSpaceCell[1] = y_cell_pos;

	return hills;
}


MapTile* GetMapTileAtXYPosition(int x, int y) {

	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* > vec = *storage->GetMapTilesStorage();

	MapTile* maptile = nullptr;

 	for (auto it = vec.begin(); it != vec.end(); ++it) {
		
		maptile = reinterpret_cast<MapTile*>(*it);

		if (maptile->m_TransformCmp->m_PosX == x && maptile->m_TransformCmp->m_PosY == y) return maptile;
	}

	return nullptr;
}

bool IsMapTilePartOfRegion(MapTile* tile) {

	if (!nullptr) return false;
	if (IsIndexOutOfBound(tile->m_TransformCmp->m_GameWorldSpaceCell[0], tile->m_TransformCmp->m_GameWorldSpaceCell[1])) return false;

	// This MapTile is already part of a region.
	if (tile->m_AssociatedRegion == nullptr) return true;

	return false;
}


olc::Pixel* Game::RandomColor(){

	int r = Random() % 6;

	switch (r){
	case 0:
		return &olc::Pixel(olc::BLUE);
		break;
	case 1:
		return &olc::Pixel(olc::GREEN);
		break;
	case 2:
		return &olc::Pixel(olc::RED);
		break;
	case 3:
		return &olc::Pixel(olc::MAGENTA);
		break;
	case 4:
		return &olc::Pixel(olc::YELLOW);
		break;
	case 5:
		return &olc::Pixel(olc::CYAN);
		break;
	default:
		break;
	}
}


std::string MapTileTypeToString(MapTile* tile) {

	if (tile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_ICE) return "ICE";
	else if (tile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_SAND) return "SAND";
	else if (tile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_SAVANNAH) return "SAVANNAH";
	else if (tile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_SNOW) return "SNOW";
	else if (tile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_TEMPERATE) return "TEMPERATE";
	else if (tile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_TUNDRA) return "TUNDRA";
	else if (tile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_WATER_DEEP) return "WATER_DEEP";
	else if (tile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_WATER_SHALLOW) return "WATER_SHALLOW";
	else if (tile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_JUNGLE) return "JUNGLE";


	else return "TYPE_INVALID";
}

bool MapTileAppropriteForForest(MapTile* tile, Forest* forest) {

	bool tile_type_ok = false;
	bool tile_free = true;

	// Check whether maptile is appropriate for forest type.
	switch (tile->m_MapTileType) {
	case MapTile::MapTileType::MAPTILE_TYPE_SAVANNAH:
		if (forest->m_ForestClass == Forest::ForestClass::FOREST_CLASS_SAVANNAH) tile_type_ok =  true;
		break;
	case MapTile::MapTileType::MAPTILE_TYPE_TEMPERATE:
		if (forest->m_ForestClass == Forest::ForestClass::FOREST_CLASS_TEMPERATE) tile_type_ok =  true;
		break;
	case MapTile::MapTileType::MAPTILE_TYPE_JUNGLE:
		if (forest->m_ForestClass == Forest::ForestClass::FOREST_CLASS_JUNGLE) tile_type_ok =  true;
		break;
	case  MapTile::MapTileType::MAPTILE_TYPE_TUNDRA:
		if (forest->m_ForestClass == Forest::ForestClass::FOREST_CLASS_TUNDRA) tile_type_ok = true;
		break;
	default:
		break;
	}


	// Now check whether there is a mountain or city etc.
	for (auto it : *tile->m_MapTileEntities) {

		if (COMPARE_STRINGS(it->m_IDCmp->m_DynamicTypeName, "Mountains") == 0) {
			tile_free = false;
		}
		else if (COMPARE_STRINGS(it->m_IDCmp->m_DynamicTypeName, "Hills") == 0) {
			tile_free = false;
		}
		else if (COMPARE_STRINGS(it->m_IDCmp->m_DynamicTypeName, "City") == 0) {
			tile_free = false;
		}

	}


	return (tile_type_ok && tile_free);
}


Forest* MakeNewForest(std::string name, int x_cell_pos, int y_cell_pos) {

	// We draw standardized forests on layer3, so skip this part from the user...
	Forest* forest = new Forest(name, "layer3", x_cell_pos * SPRITES_WIDTH_AND_HEIGHT, y_cell_pos * SPRITES_WIDTH_AND_HEIGHT);

	forest->m_TransformCmp->m_GameWorldSpaceCell[0] = x_cell_pos;
	forest->m_TransformCmp->m_GameWorldSpaceCell[1] = y_cell_pos;

	// Forests AI is standardized, only one state is legal and every forests has an AI, thus skip this part from the user...
	forest->m_AICmp->ChangeState(States::STATE_SEARCH);
	forest->m_AICmp->MapState("state_search", new ForestSearch(*forest->m_AICmp));

	return ((forest == nullptr) ? nullptr : forest);
}


Forest* MakeNewForestAtPos(std::string name, int xpos, int ypos, int set_x_cell, int set_y_cell){

	// We draw standardized forests on layer3, so skip this part from the user...
	Forest* forest = new Forest(name, "layer3", xpos, ypos);

	forest->m_TransformCmp->m_GameWorldSpaceCell[0] = set_x_cell;
	forest->m_TransformCmp->m_GameWorldSpaceCell[1] = set_y_cell;

	// Forests AI is standardized, only one state is legal and every forests has an AI, thus skip this part from the user...
	forest->m_AICmp->ChangeState(States::STATE_SEARCH);
	forest->m_AICmp->MapState("state_search", new ForestSearch(*forest->m_AICmp));

	return ((forest == nullptr) ? nullptr : forest);

}


bool IsSubstringInString(std::string substring, std::string string) {

	if (string.find(substring) != std::string::npos) {
		return true;
	}
	return false;
}


bool IsIndexOutOfBound(int x, int y) {

	if (x < 0 || y < 0) return true;

	// Mapsize counts from 1,..20 for example,
	// thus we need to check for x > MAP_SIZE - 1...

	if (x > MAP_SIZE - 1 ||
		y > MAP_SIZE - 1) return true;


	return false;
}


int GetTotalForestsCount() {

	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* > vec = *storage->GetStorage();
	GameEntity* entt = nullptr;


	int forest_count = 0;
	for (auto it = vec.begin(); it != vec.end(); ++it) {

		entt = *it;

		if (COMPARE_STRINGS(entt->m_IDCmp->m_DynamicTypeName, "Forest") == 0) forest_count++;
	}

	return forest_count;
}


MapTile* GetMapTileAtWorldPosition(int x, int y) {

	if (x < 0 || y < 0) return nullptr;


	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* > vec = *storage->GetMapTilesStorage();
	GameEntity* entity = nullptr;

	for (auto it = vec.begin(); it != vec.end(); ++it) {

		entity = *it;

		if (entity->m_TransformCmp->m_GameWorldSpaceCell[0] == x && entity->m_TransformCmp->m_GameWorldSpaceCell[1] == y) {
			return static_cast<MapTile*>(entity);
		}
	}

	// Nothing found. Means not valid index for maptile or some other weird error.
	return nullptr;
}


// The DynamicType of an Entity is basically its Class Name.
GameEntity* IsGameEntityTypeOnMapTile(MapTile* maptile, std::string dynamicTypeName) {

	if (maptile == nullptr) return nullptr;


	std::vector< GameEntity* > vec = *maptile->m_MapTileEntities;
	GameEntity* entt = nullptr;


	for (auto it = vec.begin(); it != vec.end(); ++it) {

		entt = *it;

		if (COMPARE_STRINGS_2(entt->m_IDCmp->m_DynamicTypeName, dynamicTypeName) == 0) return entt;
	}

	// Entity not present.
	return nullptr;
}


std::vector<GameEntity*> GetForestEntities() {

	std::vector<GameEntity*> return_vector;

	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* > vec = *storage->GetMapTilesStorage();
	
	MapTile* maptile = nullptr;
	GameEntity* entity = nullptr;

	for (auto it = vec.begin(); it != vec.end(); ++it) {

		maptile = reinterpret_cast<MapTile*>(*it);

		entity = IsGameEntityTypeOnMapTile(maptile, "Forest");

		if (entity) {

			return_vector.push_back(entity);
		}
	}

	return return_vector;

}







void CMPCameraInput::HandleKeyboard(Camera* cam) {

	Game* context = cam->m_Game;

	// Do not handle game keyboard input, if UI has focused keyboard input.
	if (IMGUI::Get()->GetUIState()->m_KeyboardItem != 0) return;


	switch (context->m_Renderer->m_RenderMode) {
	case Renderer::RenderMode::RENDERMODE_CITYVIEW:
		_handleCityViewKeyboard(cam);
		break;
	case Renderer::RenderMode::RENDERMODE_MAPVIEW:
		_handleMapViewKeyBoard(cam);
		break;
	default:
		break;
	}
}



void CMPCameraInput::_handleMapViewKeyBoard(Camera* cam) {

	Game* context = cam->m_Game;

	int speed = 4;

	if (context->GetKey(olc::Key::ESCAPE).bReleased) {
		exit(0);
	}

	if (context->GetKey(olc::Key::ENTER).bReleased) {
		
		context->m_AdvanceOneTurn = true;
		context->AdvanceOneTurn();
	}

	if (context->GetKey(olc::Key::CTRL).bHeld) {


		if (context->GetKey(olc::Key::G).bPressed) {

			context->m_DebugDrawGrid = (context->m_DebugDrawGrid == true) ? false : true;
		}

		if (context->GetKey(olc::Key::TAB).bPressed) {
			context->m_DebugDrawGeneralOptions = (context->m_DebugDrawGeneralOptions == true) ? false : true;
		}

		if (context->GetKey(olc::Key::M).bPressed) {
			context->m_DebugDrawMapTileInfo = (context->m_DebugDrawMapTileInfo == true) ? false : true;
		}

		if (context->GetKey(olc::Key::F).bPressed) {
			context->m_DebugDrawForestInfo = (context->m_DebugDrawForestInfo == true) ? false : true;
		}

		if (context->GetKey(olc::Key::R).bPressed) {
			context->m_DebugDrawRegions = (context->m_DebugDrawRegions == true) ? false : true;
		}

		if (context->GetKey(olc::Key::T).bPressed) {
			context->m_TimeModeTurnBased = (context->m_TimeModeTurnBased == true) ? false : true;
		}

		if (context->GetKey(olc::Key::U).bPressed) {
			context->m_DebugDrawUnitPositions = (context->m_DebugDrawUnitPositions == true) ? false : true;
		}

		if (context->GetKey(olc::Key::S).bPressed) {
			context->m_DebugDrawPlayersTech = (context->m_DebugDrawPlayersTech == true) ? false : true;
		}

		if (context->GetKey(olc::Key::B).bPressed) {
			context->m_DebugDrawPlayersBuildings = (context->m_DebugDrawPlayersBuildings == true) ? false : true;
		}



		if (context->GetKey(olc::Key::SPACE).bPressed) {
			Player* p = nullptr;
			p = GetPlayer("Bogdan");

			if (!p) return;

			for (auto it : p->m_PlayerCities) {
				ColorValue = (ColorValue + 1) % 8;
				it->m_CityBorderColor = City::CityBorderColor(ColorValue);
			}
		}

	}

	if (context->GetKey(olc::Key::P).bPressed) {

		City* city = nullptr;
		for (auto it : *EntitiesStorage::Get()->GetCitiesVec()) {
			
			city = reinterpret_cast<City*>(it);

			city->m_CitySize++;
			city->Update();
		}

	}

	if (context->GetKey(olc::Key::O).bPressed) {

		City* city = nullptr;
		for (auto it : *EntitiesStorage::Get()->GetCitiesVec()) {

			city = reinterpret_cast<City*>(it);

			city->m_CitySize--;
			city->Update();
		}

	}

	if (context->GetKey(olc::Key::SHIFT).bHeld) {

	}


	if (context->GetKey(olc::Key::W).bHeld) {

		if (g_vi2dCameraPosition.y <= 0) {
			g_vi2dCameraPosition.y = 0; return;
		}


		g_vi2dCameraPosition.y -= 1 * speed;

		for (auto it : *EntitiesStorage::Get()->GetMapTilesStorage()) {

			it->m_TransformCmp->m_PosY += 1 * speed;

			if (static_cast<MapTile*>(it)->m_MapTileEntities != nullptr) {
				if (static_cast<MapTile*>(it)->m_MapTileEntities->size() > 0) {


					for (auto iter : *static_cast<MapTile*>(it)->m_MapTileEntities) {

						iter->m_TransformCmp->m_PosY += 1 * speed;
					}
				}
			}
		}
	}

	if (context->GetKey(olc::Key::A).bHeld) {

		if (g_vi2dCameraPosition.x <= 0) {
			g_vi2dCameraPosition.x = 0; return;
		}


		g_vi2dCameraPosition.x -= 1 * speed;

		for (auto it : *EntitiesStorage::Get()->GetMapTilesStorage()) {

			it->m_TransformCmp->m_PosX += 1 * speed;


			if (static_cast<MapTile*>(it)->m_MapTileEntities != nullptr) {
				if (static_cast<MapTile*>(it)->m_MapTileEntities->size() > 0) {


					for (auto iter : *static_cast<MapTile*>(it)->m_MapTileEntities) {

						iter->m_TransformCmp->m_PosX += 1 * speed;
					}
				}
			}
		}
	}

	if (context->GetKey(olc::Key::S).bHeld) {

		if (g_vi2dCameraPosition.y >= MAP_SIZE * SPRITES_WIDTH_AND_HEIGHT) {
			g_vi2dCameraPosition.y = MAP_SIZE * SPRITES_WIDTH_AND_HEIGHT; return;
		}


		g_vi2dCameraPosition.y += 1 * speed;

		for (auto it : *EntitiesStorage::Get()->GetMapTilesStorage()) {

			it->m_TransformCmp->m_PosY -= 1 * speed;


			if (static_cast<MapTile*>(it)->m_MapTileEntities != nullptr) {
				if (static_cast<MapTile*>(it)->m_MapTileEntities->size() > 0) {


					for (auto iter : *static_cast<MapTile*>(it)->m_MapTileEntities) {

						iter->m_TransformCmp->m_PosY -= 1 * speed;
					}
				}
			}
		}
	}

	if (context->GetKey(olc::Key::D).bHeld) {

		if (g_vi2dCameraPosition.x >= MAP_SIZE * SPRITES_WIDTH_AND_HEIGHT) {
			g_vi2dCameraPosition.x = MAP_SIZE * SPRITES_WIDTH_AND_HEIGHT; return;
		}

		g_vi2dCameraPosition.x += 1 * speed;

		for (auto it : *EntitiesStorage::Get()->GetMapTilesStorage()) {

			it->m_TransformCmp->m_PosX -= 1 * speed;


			if (static_cast<MapTile*>(it)->m_MapTileEntities != nullptr) {
				if (static_cast<MapTile*>(it)->m_MapTileEntities->size() > 0) {


					for (auto iter : *static_cast<MapTile*>(it)->m_MapTileEntities) {

						iter->m_TransformCmp->m_PosX -= 1 * speed;
					}
				}
			}
		}
	}



}


static bool g_bAddingPatrolPoints = false;
void CMPCameraInput::_handleMapViewMouse(Camera* cam) {

	using namespace std;

	Game* context = cam->m_Game;

	// Draw Region around mouse position.
	MapTileRegion* region = nullptr;

	region = GetRegionAtWorldPosition(context->GetMouseX(), context->GetMouseY());

	if (region != nullptr) {

		for (auto it : region->m_MapTileRegionTiles) {


			context->DrawDecal(olc::vi2d(it->m_TransformCmp->m_PosX, it->m_TransformCmp->m_PosY),
				context->m_SpriteResourceMap.at("map_cell_white"));

		}
	}


	
	MapTile* tile = nullptr;
	City* city = nullptr;
	Unit* unit = nullptr;


	if (context->GetKey(olc::Key::C).bPressed && PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlySelectedUnit != nullptr) {

		tile = GetMaptileAtMousePosition(context->GetMouseX(), context->GetMouseY());


		for (auto it : *tile->m_MapTileEntities) {

			if (COMPARE_STRINGS_2(it->m_IDCmp->m_ID, PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlySelectedUnit->m_IDCmp->m_ID) == 0) {


				context->m_DrawUnitStats = (context->m_DrawUnitStats == true) ? false: true;
			}
		}
	}


	if (PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlySelectedUnit == nullptr) {

		context->m_DrawUnitStats = false;
	}

	if (context->GetKey(olc::Key::C).bReleased) {

		context->m_DrawUnitStats = false;
	}


	
	// Do not enter city by clicking on it, if we only want sent unit on it.
	if (context->GetMouse(1).bPressed && PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlySelectedUnit == nullptr){
		

		tile = GetMaptileAtMousePosition(context->GetMouseX(), context->GetMouseY());

		for (auto it : *tile->m_MapTileEntities) {

			if (COMPARE_STRINGS(it->m_IDCmp->m_DynamicTypeName, "City") == 0) {

				city = reinterpret_cast<City*>(it);

				context->m_Renderer->ChangeRenderMode();
				context->m_Renderer->SetCurrentViewedCity(city); // Set city which we now view.

			}
		}
	}
	

	if (context->GetMouse(0).bPressed) {
		IMGUI::Get()->GetUIState()->m_MouseDown = 0;

		using namespace std;
		cout << color(colors::BLUE) << endl;

		// Select unit. But, do not select units we do not own.
		Unit* unit = nullptr;
		unit = GetUnitAtMapTileFromMousePosition(context->GetMouseX(), context->GetMouseY());

		cout << "Unit selected: ";
		if (unit) {
			if (IsUnitInCityOrFort(unit) == false) {

				if (IsPlayersUnit(PlayerTurnCounter::Get()->m_CurrentTurnPlayer, unit)) {

					PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlySelectedUnit = unit;
					cout << PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlySelectedUnit->m_Name << white << endl;
				}
			}
			else {

				cout << " ...but it is in city... " << white << endl;
				PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlySelectedUnit = nullptr;

				unit = nullptr;
			}
		}
		else {
			cout << " ...but it is nullptr... " << white << endl;
			PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlySelectedUnit = nullptr;

			unit = nullptr;
		}




		cout << color(colors::DARKCYAN) << endl;
		cout << " at position  ::= " << context->GetMouseX() << ":" << context->GetMouseY() << endl;
		cout << " at cell ::= " << int(context->GetMouseX() / SPRITES_WIDTH_AND_HEIGHT) << ":" << int(context->GetMouseY() / SPRITES_WIDTH_AND_HEIGHT) << white << endl;


		// Deselect unit. Clear storage.
		if (PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlySelectedUnit == nullptr) {
			if (context->m_SelectedUnitsMovementTiles) {
				

				if (context->m_SelectedUnitsMovementTiles->size() > 0) {

					context->m_SelectedUnitsMovementTiles->clear();

					delete context->m_SelectedUnitsMovementTiles;
					context->m_SelectedUnitsMovementTiles = nullptr;
				}
			}
		}
	}


	if (PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlySelectedUnit != nullptr) {


		// Display to where unit can move to.
		if (context->m_SelectedUnitsMovementTiles == nullptr) {

			context->m_SelectedUnitsMovementTiles = new std::map<MapTile*, int>();
			PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlySelectedUnit->DetermineTilesInMovementRange2(context->m_SelectedUnitsMovementTiles);
		}



		if (context->GetMouse(1).bReleased && !g_bAddingPatrolPoints) {

			using namespace olc;

			vi2d pos = { 0,0 };
			pos.x = GetMaptileAtMousePosition(context->GetMouseX(), context->GetMouseY())->m_TransformCmp->m_GameWorldSpaceCell[0];
			pos.y = GetMaptileAtMousePosition(context->GetMouseX(), context->GetMouseY())->m_TransformCmp->m_GameWorldSpaceCell[1];

			PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlySelectedUnit->MoveTo(pos.x, pos.y);

			// Deselect after movement and clear storage for movement tiles.
			PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlySelectedUnit = nullptr;
			if (context->m_SelectedUnitsMovementTiles->size() > 0) {

				context->m_SelectedUnitsMovementTiles->clear();

				delete context->m_SelectedUnitsMovementTiles;
				context->m_SelectedUnitsMovementTiles = nullptr;
			}
		}

		if (context->GetKey(olc::Key::SHIFT).bReleased) {
			
			g_bAddingPatrolPoints = false;
		}

		if (context->GetKey(olc::Key::SHIFT).bHeld) {

			g_bAddingPatrolPoints = true;

			if (context->GetMouse(1).bPressed && g_bAddingPatrolPoints) {

				
				using namespace olc;
				using namespace std;

				cout << color(colors::MAGENTA) << endl;
				cout << "GetMouse(1).bPressed" << white << endl;

				vi2d pos = { 0,0 };
				pos.x = GetMaptileAtMousePosition(context->GetMouseX(), context->GetMouseY())->m_TransformCmp->m_GameWorldSpaceCell[0];
				pos.y = GetMaptileAtMousePosition(context->GetMouseX(), context->GetMouseY())->m_TransformCmp->m_GameWorldSpaceCell[1];

				// Add patrol points.
				reinterpret_cast<UnitPatrolLogic*>(PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlySelectedUnit->m_AICmp->m_StateLogicMap.at("state_patrol"))->AddPatrolPoint(pos);
				
			}

			if (context->GetKey(olc::Key::ENTER).bPressed && g_bAddingPatrolPoints) {

				// Set loose to patrol.
				PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlySelectedUnit->m_AICmp->ChangeState(States::STATE_PATROL);

				// IGOUGO Mode --> execute units logic...
				//NOTE:
				// This works for instant "go to".
				// For patroling the AI-Unit should himself set AT THE END of a PLAYER TURN "tryExecuteLogic"...
				// Thus we get an effect like in CIV6.
				PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlySelectedUnit->m_AICmp->TryExecuteStateLogic();
			}
		}
	}


	// Reset the mousedown state to non-down...
	if (context->GetMouse(0).bReleased) {
		IMGUI::Get()->GetUIState()->m_MouseDown = -1;
	}

	
	if (context->GetKey(olc::Key::CTRL).bHeld) {

		if (context->GetMouse(0).bPressed) {

			// TESTING PURPOSES:
			tile = GetMaptileAtMousePosition(context->GetMouseX(), context->GetMouseY());


			// Creating walking unit.
			Unit* unit = MakeNewUnitAtPos(PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_PlayerEmpireRace, UnitMovementType::UNIT_MOVEMENT_TYPE_WALKING, PlayerTurnCounter::Get()->m_CurrentTurnPlayer,
				"Citizen",
				tile->m_TransformCmp->m_PosX, tile->m_TransformCmp->m_PosY,
				tile->m_TransformCmp->m_GameWorldSpaceCell[0], tile->m_TransformCmp->m_GameWorldSpaceCell[1]);



			EntitiesStorage::Get()->AddGameEntitie(unit);
			PlayerTurnCounter::Get()->m_CurrentTurnPlayer->AddUnit(unit); // Add unit to players vector.
		}
	}
	

}


void Game::DrawSelectedUnitsMovementTiles() {

	if (m_SelectedUnitsMovementTiles == nullptr) return;
	if (m_SelectedUnitsMovementTiles->size() == 0) return;

	using namespace olc;
	MapTile* tile = nullptr;
	CMPEntityRace::Race race = PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_PlayerEmpireRace;

	for (auto it = m_SelectedUnitsMovementTiles->begin();
		it != m_SelectedUnitsMovementTiles->end(); ++it) {

		tile = it->first;

		// Draw cells.
		DrawDecal(vi2d(tile->m_TransformCmp->m_PosX, tile->m_TransformCmp->m_PosY),
			m_SpriteResourceMap.at("unit_rangecell"));

		
		// Draw race modified cost for each tile.
		std::string out = "Cost: " + std::to_string(it->second);
		DrawStringDecal(vi2d(tile->m_TransformCmp->m_PosX, tile->m_TransformCmp->m_PosY + 32), out, olc::BLACK);
		
	}
}




void CMPCameraInput::_handleCityViewMouse(Camera* cam) {

	using namespace std;
	using namespace olc;

	Game* context = cam->m_Game;
	PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyViewedCity = context->m_Renderer->m_CurrentViewedCity;

	// Show mouse position.
	int mouse_x = context->GetMouseX();
	int mouse_y = context->GetMouseY();

	//cout << color(colors::DARKMAGENTA);
	//cout << "Mouse ("<< mouse_x << ":" << mouse_y << ")" << white << endl;


	// Compute offset of maptile position in cityview for getting right maptile down below..
	City* city = PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyViewedCity;
	int cx = 992 - 32;
	int cy = 360 - 32;

	// We can get position of maptile in cityview by adding maptile position with this offset.
	int offsetx = cx - city->m_TransformCmp->m_PosX;
	int offsety = cy - city->m_TransformCmp->m_PosY;
	m_OffsetX = offsetx;
	m_OffsetY = offsety;


	// Reset the hovered over entity for re-iteration.
	PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyHoveredEntityInCity = nullptr;

	std::string type;
	PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyHoveredEntityInCity = _hoveringOverEntity(mouse_x, mouse_y, type);


	if (context->GetMouse(0).bPressed) {

		cout << "LMB Pressed" << white << endl;

		GameEntity* entt = nullptr;
		std::string entt_type;

		entt = _hoveringOverEntity(mouse_x, mouse_y, entt_type);

		// Check for hovering over unit...
		if (entt != nullptr &&
			COMPARE_STRINGS(entt_type, "Unit") == 0) { // We are hovering over a unit...

			// and we have pressed the left mouse button.
			// Save prevpos of unit for later.
			_storePrevPos(entt);


			// Save hovered over unit specific for player.
			PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyHoveredEntityInCity = entt;
		}

		/*
		// LMB Pressed over building or...
		if (entt != nullptr &&
			COMPARE_STRINGS(entt_type, "Building") == 0) { // We are hovering over a building...



			
			// and we have pressed the left mouse button.
			// Save prevpos of unit for later.
			_storePrevPos(entt);


			// Save hovered over building specific for player.
			PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyHoveredEntityInCity = entt;
		}
		*/

		// LMB Pressed over building slot.
		int slot = _hoveringOverBuildingSlot(mouse_x, mouse_y);
		if (slot != -1) { // Then we pressed LMB over a building slot.

			// Show building possibilities for player on specific building slot.
			std::vector<std::string>* buildings_vec = nullptr;

			buildings_vec = GetAvailableBuildingsForPlayerOnSlot(PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyViewedCity, slot);


			if (buildings_vec->size() == 0) {

				cout << color(colors::DARKRED);
				cout << "You cant build anything on this building slot." << white << endl;
			}
			else {

				int index = 0;
				for (auto it : *buildings_vec) {
					cout << color(colors::BLUE);
					cout << "You can build: " << index + 1 << ".) \"" << it << "\"." << white << endl;
					index++;
				}
			}

		}
	}


	if (context->GetMouse(0).bHeld && // Holding mouse ...

		PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyHoveredEntityInCity != nullptr && // .. over an entity...

		(COMPARE_STRINGS(PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyHoveredEntityInCity->m_IDCmp->m_DynamicTypeName, "Unit") == 0) // .. that is of type "unit", and not "building"...
		
		||
		
		m_DraggedUnit != nullptr) { // Or we are already dragging a "unit".



		// From here, deal with dragged unit directly in handler,
		// as such save this unit to ours.
		if (!m_DraggedUnit) {

			m_DraggedUnit = static_cast<Unit*>(PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyHoveredEntityInCity);
		}


		if (m_DraggedUnit) {
			// drag unit...
			m_DraggedUnit->m_TransformCmp->m_PosX = mouse_x - int(SPRITES_WIDTH_AND_HEIGHT / 2);
			m_DraggedUnit->m_TransformCmp->m_PosY = mouse_y - int(SPRITES_WIDTH_AND_HEIGHT / 2);
		}
	}


	// Releasing LMB after dragging is done.
	if (context->GetMouse(0).bReleased && m_DraggedUnit) {

		cout << "LMB Released" << white << endl;

		// Try give unit a class based on position we set him and...
		if (!_tryGivingUnitAProfession(m_DraggedUnit)) {

			// ...reset things.
			m_DraggedUnit->m_TransformCmp->m_PosX = m_EntityPrevXpos;
			m_DraggedUnit->m_TransformCmp->m_PosY = m_EntityPrevYpos;
			m_DraggedUnit = nullptr;

			_resetPrevPos();
		}
		else {

			// Giving profession was successful, so let go the dragging and reset for next drag-and-drop.
			m_DraggedUnit = nullptr;
			_resetPrevPos();
		}
	}

}


GameEntity* CMPCameraInput::_hoveringOverEntity(int xpos, int ypos, std::string& entityType) {

	// If we hover over an Entity, we give back a referece and save in "entityType"
	// the dynamictypename of this Entity.

	// Go through all entities...
	for (auto it : PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyViewedCity->m_PresentUnitsVector) {

		// Check for collision of mouse position and tile dimensions...
		if (it->m_TransformCmp->m_PosX <= xpos &&
			(it->m_TransformCmp->m_PosX + it->m_TransformCmp->m_Width) >= xpos
			&&
			it->m_TransformCmp->m_PosY <= ypos &&
			(it->m_TransformCmp->m_PosY + it->m_TransformCmp->m_Height) >= ypos) {

			// True.
			entityType = it->m_IDCmp->m_DynamicTypeName;
			return it;
		}

	}



	return nullptr;
}


// Returns -1 if no slot is hovered upon.
int CMPCameraInput::_hoveringOverBuildingSlot(int xpos, int ypos){ 

	for (auto it : PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyViewedCity->m_CityBuildingsSlots) {

		// Check for collision of mouse position and slot dimensions...
		if (it->m_XPos <= xpos &&
			(it->m_XPos + it->m_Width) >= xpos
			&&
			it->m_YPos <= ypos &&
			(it->m_YPos + it->m_Height) >= ypos) {


			return it->m_SlotNumber;
		}
	}

	return -1;
}


/*
void CMPCameraInput::_handleCityViewMouse(Camera* cam) {

	using namespace std;
	using namespace olc;


	Game* context = cam->m_Game;
	PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyViewedCity = context->m_Renderer->m_CurrentViewedCity;


	// Show mouse position.
	int mouse_x = context->GetMouseX();
	int mouse_y = context->GetMouseY();
	//cout << color(colors::RED);
	//cout << "Mouse Position (" << mouse_x << ":" << mouse_y << ")" << white << endl;

	// Get Maptile we are hovering over.
	// Utility, draw maptiles positions over mouse pos.
	MapTile* hovered_maptile = nullptr;
	City* city = context->m_Renderer->m_CurrentViewedCity;
	int cx = 992 - 32;
	int cy = 360 - 32;

	// We can get position of maptile in cityview by adding maptile position with this offset.
	int offsetx = cx - city->m_TransformCmp->m_PosX;
	int offsety = cy - city->m_TransformCmp->m_PosY;

	for (auto it = city->m_ClaimedRegions.begin(); it != city->m_ClaimedRegions.end(); ++it) {

MapTileRegion* region = *it;

for (auto itr : region->m_MapTileRegionTiles) {

	MapTile* tile = itr;

	// Check for collision of mouse position and tile dimensions...
	if (tile->m_TransformCmp->m_PosX + offsetx <= mouse_x &&
		(tile->m_TransformCmp->m_PosX + tile->m_TransformCmp->m_Width + offsetx) >= mouse_x
		&&
		tile->m_TransformCmp->m_PosY + offsety <= mouse_y &&
		(tile->m_TransformCmp->m_PosY + tile->m_TransformCmp->m_Height + offsety) >= mouse_y) {


		// Print result.
		//cout << color(colors::RED);
		//cout << "Hovered Maptile: ("<< tile->m_TransformCmp->m_PosX + offsetx << ":"<< tile->m_TransformCmp->m_PosY + offsety << ")" << white << endl;

		hovered_maptile = tile;
	}

}
	}




	// Reset hovered unit for re-iteration.
	PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyHoveredEntityInCity = nullptr;

	// Show over what unit or house the user is hovering.
	// First, save it as GameEntity..
	for (auto it : context->m_Renderer->m_CurrentViewedCity->m_PresentUnitsVector) {

		// Check for box collision.
		if (it->m_TransformCmp->m_PosX <= mouse_x &&
			(it->m_TransformCmp->m_PosX + it->m_TransformCmp->m_Width) >= mouse_x
			&&
			it->m_TransformCmp->m_PosY <= mouse_y &&
			(it->m_TransformCmp->m_PosY + it->m_TransformCmp->m_Height) >= mouse_y) {


			// Collision with mouse and sprite box...
			PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyHoveredEntityInCity = it;

		}
	}



	// TESTING:
	// Drag and Drop units.
	// We depend on hovering from above -> if we hover over a unit, then we can select it and drag somewhere...

	// For resetting unit position.
	static int prev_xpos, prev_ypos;

	if (context->GetMouse(0).bHeld) { // Holding left mousebutton.

		if (PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyHoveredEntityInCity) {

			if (COMPARE_STRINGS(PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyHoveredEntityInCity->m_IDCmp->m_DynamicTypeName, "Unit") == 0) {

				prev_xpos = PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyHoveredEntityInCity->m_TransformCmp->m_PosX;
				prev_ypos = PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyHoveredEntityInCity->m_TransformCmp->m_PosY;


				PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyHoveredEntityInCity->m_TransformCmp->m_PosX = mouse_x - int(SPRITES_WIDTH_AND_HEIGHT / 2);
				PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyHoveredEntityInCity->m_TransformCmp->m_PosY = mouse_y - int(SPRITES_WIDTH_AND_HEIGHT / 2);
			}
		}
	}


	// Change unit specialization on release over valid spot.
	if (hovered_maptile) {


		Unit* unit = nullptr;
		if (PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyHoveredEntityInCity != nullptr) {

			if (context->GetMouse(0).bReleased) {

				if (COMPARE_STRINGS(PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyHoveredEntityInCity->m_IDCmp->m_DynamicTypeName, "Unit") == 0) {

					unit = static_cast<Unit*>(PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyHoveredEntityInCity);
				}




				// Check for maptile type and possible working classes...

				// Check for woodcutter.
				for (auto it : *hovered_maptile->m_MapTileEntities) {


					if (COMPARE_STRINGS(it->m_IDCmp->m_DynamicTypeName, "Forest") == 0) {

						std::string answer;
						if (COMPARE_STRINGS(unit->m_UnitClass->m_UnitClassName, "Citizen") == 0) { // Everything, but not a citizen.


							bool hunter = false;
							std::string unit_type;
							cout << color(colors::RED);
							cout << "Hunter or Woodcutter ??";
							cin >> unit_type;
							if (COMPARE_STRINGS(unit_type, "Hunter") == 0) hunter = true;

							if (hunter) {

								unit->ChangeClass("Hunter");
								unit->m_TransformCmp->m_PosX = hovered_maptile->m_TransformCmp->m_PosX + offsetx;
								unit->m_TransformCmp->m_PosY = hovered_maptile->m_TransformCmp->m_PosY + offsety;

								city->RemoveCitizenFromJoblessVector(unit);
								return;
							}
							else {

								unit->ChangeClass("Woodcutter");
								unit->m_TransformCmp->m_PosX = hovered_maptile->m_TransformCmp->m_PosX + offsetx;
								unit->m_TransformCmp->m_PosY = hovered_maptile->m_TransformCmp->m_PosY + offsety;

								city->RemoveCitizenFromJoblessVector(unit);
								return;
							}



						}
						else {

							cout << color(colors::RED);
							cout << "Are you sure to give unit a new class? With it units level will be reset. [Y]es or [N]o." << white << endl;
							cin >> answer;

							if (COMPARE_STRINGS(answer, "Yes") == 0 ||
								COMPARE_STRINGS(answer, "Y") == 0 ||
								COMPARE_STRINGS(answer, "y") == 0) {



								bool hunter = false;
								std::string unit_type;
								cout << color(colors::RED);
								cout << "Hunter or Woodcutter ??";
								cin >> unit_type;
								if (COMPARE_STRINGS(unit_type, "Hunter") == 0) hunter = true;

								if (hunter) {

									unit->ChangeClass("Hunter");
									unit->m_TransformCmp->m_PosX = hovered_maptile->m_TransformCmp->m_PosX + offsetx;
									unit->m_TransformCmp->m_PosY = hovered_maptile->m_TransformCmp->m_PosY + offsety;

									city->RemoveCitizenFromJoblessVector(unit);
									return;
								}
								else {

									unit->ChangeClass("Woodcutter");
									unit->m_TransformCmp->m_PosX = hovered_maptile->m_TransformCmp->m_PosX + offsetx;
									unit->m_TransformCmp->m_PosY = hovered_maptile->m_TransformCmp->m_PosY + offsety;

									city->RemoveCitizenFromJoblessVector(unit);
									return;
								}
							}
							else {
								unit->m_TransformCmp->m_PosX = prev_xpos;
								unit->m_TransformCmp->m_PosY = prev_ypos;
								return;
							}


						}




					}
				}

				// Check for farmer...
				if (hovered_maptile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_TEMPERATE) {


					std::string answer;
					if (COMPARE_STRINGS(unit->m_UnitClass->m_UnitClassName, "Citizen") == 0) {


						unit->ChangeClass("Farmer");

						unit->m_TransformCmp->m_PosX = hovered_maptile->m_TransformCmp->m_PosX + offsetx;
						unit->m_TransformCmp->m_PosY = hovered_maptile->m_TransformCmp->m_PosY + offsety;

						city->RemoveCitizenFromJoblessVector(unit);
						return;
					}
					else {	// Everything, but not a citizen.

						cout << color(colors::RED);
						cout << "Are you sure to give unit a new class? With it units level will be reset. [Y]es or [N]o." << white << endl;
						cin >> answer;


						if (COMPARE_STRINGS(answer, "Yes") == 0 ||
							COMPARE_STRINGS(answer, "Y") == 0 ||
							COMPARE_STRINGS(answer, "y") == 0) {

							unit->ChangeClass("Farmer");

							unit->m_TransformCmp->m_PosX = hovered_maptile->m_TransformCmp->m_PosX + offsetx;
							unit->m_TransformCmp->m_PosY = hovered_maptile->m_TransformCmp->m_PosY + offsety;

							city->RemoveCitizenFromJoblessVector(unit);
							return;

						}
						else {
							unit->m_TransformCmp->m_PosX = prev_xpos;
							unit->m_TransformCmp->m_PosY = prev_ypos;
							return;
						}

					}


				}


				// Check for fisher...
				if (hovered_maptile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_WATER_SHALLOW) {


					std::string answer;
					if (COMPARE_STRINGS(unit->m_UnitClass->m_UnitClassName, "Citizen") == 0) {


						unit->ChangeClass("Fisher");

						unit->m_TransformCmp->m_PosX = hovered_maptile->m_TransformCmp->m_PosX + offsetx;
						unit->m_TransformCmp->m_PosY = hovered_maptile->m_TransformCmp->m_PosY + offsety;

						city->RemoveCitizenFromJoblessVector(unit);
						return;
						return;
					}
					else {	// Everything, but not a citizen.

						cout << color(colors::RED);
						cout << "Are you sure to give unit a new class? With it units level will be reset. [Y]es or [N]o." << white << endl;
						cin >> answer;


						if (COMPARE_STRINGS(answer, "Yes") == 0 ||
							COMPARE_STRINGS(answer, "Y") == 0 ||
							COMPARE_STRINGS(answer, "y") == 0) {

							unit->ChangeClass("Fisher");

							unit->m_TransformCmp->m_PosX = hovered_maptile->m_TransformCmp->m_PosX + offsetx;
							unit->m_TransformCmp->m_PosY = hovered_maptile->m_TransformCmp->m_PosY + offsety;

							city->RemoveCitizenFromJoblessVector(unit);
							return;

						}
						else {
							unit->m_TransformCmp->m_PosX = prev_xpos;
							unit->m_TransformCmp->m_PosY = prev_ypos;
							return;
						}

					}


				}



				// In case all is not aplicable, reset position of unit to "garrison".
				if (unit) {

					unit->m_TransformCmp->m_PosX = 700;
					unit->m_TransformCmp->m_PosY = 650;
				}
				return;
			}
		}
	}
	else {


		Unit* unit = nullptr;
		if (PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyHoveredEntityInCity != nullptr) {

			if (context->GetMouse(0).bReleased) {

				if (COMPARE_STRINGS(PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyHoveredEntityInCity->m_IDCmp->m_DynamicTypeName, "Unit") == 0) {

					unit = static_cast<Unit*>(PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyHoveredEntityInCity);
				}

				// In case all is not aplicable, reset position of unit to "garrison".
				if (unit) {
					unit->m_TransformCmp->m_PosX = 700;
					unit->m_TransformCmp->m_PosY = 650;
				}
			}
		}
	}

}
*/



bool CMPCameraInput::_tryGivingUnitAProfession(Unit* unit) {

	int mouse_x = Game::Get()->GetMouseX();
	int mouse_y = Game::Get()->GetMouseY();

	// Get maptile in question for information..
	MapTile* maptile = nullptr;
	for (auto it : PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyViewedCity->m_ClaimedRegions) {

		for (auto itr : it->m_MapTileRegionTiles) {

			// We check for collision of maptile and mouseposition and not the unit to get the right maptile..
			/*
			if (itr->m_TransformCmp->m_PosX + m_OffsetX == unit->m_TransformCmp->m_PosX &&
				itr->m_TransformCmp->m_PosY + m_OffsetY == unit->m_TransformCmp->m_PosY) {

				maptile = itr;
			}
			*/

			if (maptile) break;

			if (itr->m_TransformCmp->m_PosX + m_OffsetX <= mouse_x &&
				itr->m_TransformCmp->m_PosX + m_OffsetX + SPRITES_WIDTH_AND_HEIGHT >= mouse_x &&

				itr->m_TransformCmp->m_PosY + m_OffsetY <= mouse_y &&
				itr->m_TransformCmp->m_PosY + m_OffsetY + SPRITES_WIDTH_AND_HEIGHT >= mouse_y) {

				maptile = itr;
			}
		}
	}

	if (!maptile) return false;


	// Check whether there is another unit on maptile present.
	if (_isMaptileAlreadyWorked(maptile) == false) { // Maptile is free and no other unit.
		
		std::vector<std::string> vec = _getPossibleProfessionsOnMaptile(maptile);

		// Iterate through possible professions and let user choose one or give directly a profession.
		if (vec.size() == 0) { // No possible professions found.
			m_DraggedUnit->m_TransformCmp->m_PosX = m_EntityPrevXpos;

			m_DraggedUnit->m_TransformCmp->m_PosY = m_EntityPrevYpos;

			// Reset dragged unit for reiteration in mousehandler.
			m_DraggedUnit = nullptr;
			return false;
		}
		else if (vec.size() == 1) { // Give profession directly.

			if (_hasUnitAProfessionAlready(unit)) {
				if (_doesPlayerWantToResetProfession()) {


					if (_hasPlayerUnitTechRequirements(vec.at(0), PlayerTurnCounter::Get()->m_CurrentTurnPlayer)) {

						// User wants to reset profession, so give unit a new profession and let him work..
						unit->ChangeClass(vec.at(0)); // Only available profession.
						unit->m_AssociatedPlayer->m_CurrentlyViewedCity->RemoveCitizenFromJoblessVector(unit); // Remove from jobless if he was there.
						_giveUnitPositionAlignedToMaptile(unit, maptile);

						return true;
					}
					else {

						// Player has not researched needed technoology yet..
						m_DraggedUnit->m_TransformCmp->m_PosX = m_EntityPrevXpos;
						m_DraggedUnit->m_TransformCmp->m_PosY = m_EntityPrevYpos;

						// dragged unit is reseted in returned to function...
						return false;
					}
				}
				else { // User does not want to reset profession, so abort dragging.

					m_DraggedUnit->m_TransformCmp->m_PosX = m_EntityPrevXpos;
					m_DraggedUnit->m_TransformCmp->m_PosY = m_EntityPrevYpos;

					// dragged unit is reseted in returned to function...
					return false;
				}
			}
			else { // Citizen has no profession so give him directly the only one available.


				if (_hasPlayerUnitTechRequirements(vec.at(0), PlayerTurnCounter::Get()->m_CurrentTurnPlayer)) {

					// User wants to reset profession, so give unit a new profession and let him work..
					unit->ChangeClass(vec.at(0)); // Only available profession.
					unit->m_AssociatedPlayer->m_CurrentlyViewedCity->RemoveCitizenFromJoblessVector(unit); // Remove from jobless if he was there.
					_giveUnitPositionAlignedToMaptile(unit, maptile);

					return true;
				}
				else {

					// Player has not researched needed technoology yet..
					m_DraggedUnit->m_TransformCmp->m_PosX = m_EntityPrevXpos;
					m_DraggedUnit->m_TransformCmp->m_PosY = m_EntityPrevYpos;

					// dragged unit is reseted in returned to function...
					return false;
				}
			}

		}
		else { // Let user choose one profession..

			bool change_profession = false;
			bool has_profession = false;
			if (_hasUnitAProfessionAlready(unit)) {
				change_profession = _doesPlayerWantToResetProfession();
			}

			if (has_profession == false || change_profession == true) { // ..If he wants to.
			
				using namespace std;
				int index = 0;

				std::vector<std::string> available_professions_vec;

				// Determine professions which are tech. available for player.
				for (auto it : vec) {
					if (_hasPlayerUnitTechRequirements(it, PlayerTurnCounter::Get()->m_CurrentTurnPlayer)) {

						available_professions_vec.push_back(it);
					}
				}

				// Display only those which are available...
				for (auto it : available_professions_vec) {

					cout << color(colors::DARKYELLOW);
					cout << index + 1 << ".) Profession: \"" << it << "\"." << white << endl;

					index++;
				}

				// Check whether there are any available jobs for players current tech stage, else break.
				if (available_professions_vec.size() == 0) {

					// Reset...
					m_DraggedUnit->m_TransformCmp->m_PosX = m_EntityPrevXpos;
					m_DraggedUnit->m_TransformCmp->m_PosY = m_EntityPrevYpos;

					// dragged unit is reset in returned function...
					return false;
				}



				cout << color(colors::DARKRED);
				cout << "Please type number of profession to choose it for your unit." << white << endl;

				try { // Safety check for invalid input.

					int choosen_number = -1;
					cin >> choosen_number;
					choosen_number--;

					// Check fir valid number..
					if ((choosen_number < 0) &&
						(choosen_number > available_professions_vec.size() - 1)) {

						// Number is in minus range or greater than valid vec size, thus error.
						return false;
					}

					unit->ChangeClass(available_professions_vec.at(choosen_number));
					unit->m_AssociatedPlayer->m_CurrentlyViewedCity->RemoveCitizenFromJoblessVector(unit); // Remove from jobless if he was there.

					// Position unit to be directly over choosen maptile.
					_giveUnitPositionAlignedToMaptile(unit, maptile);

					return true;

				}
				catch (const char* err) {

					cout << color(colors::RED);
					cout << err << white << endl;

					// Reset...
					m_DraggedUnit->m_TransformCmp->m_PosX = m_EntityPrevXpos;
					m_DraggedUnit->m_TransformCmp->m_PosY = m_EntityPrevYpos;

					// Reset dragged unit for reiteration in mousehandler.
					//m_DraggedUnit = nullptr;
					// dragged unit is reset in returned function...
					return false;
				}
			}
			else {

				// Player reconsidered giving unit new profession and does not want to proceed.

				// Thus, reset position of dragged unit back.
				m_DraggedUnit->m_TransformCmp->m_PosX = m_EntityPrevXpos;
				m_DraggedUnit->m_TransformCmp->m_PosY = m_EntityPrevYpos;
				return false;
			}

		}

		return true;
	}
	else { // Maptile is not free, so send unit back to first position.

		m_DraggedUnit->m_TransformCmp->m_PosX = m_EntityPrevXpos;
		m_DraggedUnit->m_TransformCmp->m_PosY = m_EntityPrevYpos;


		// reseting dragged unit is done in returned function...
		return false;
	}
}

bool CMPCameraInput::_isMaptileAlreadyWorked(MapTile* maptile) {


	for (auto it : PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyViewedCity->m_PresentUnitsVector) {

		if ((maptile->m_TransformCmp->m_PosX + m_OffsetX) == it->m_TransformCmp->m_PosX &&
			(maptile->m_TransformCmp->m_PosY + m_OffsetY) == it->m_TransformCmp->m_PosY) {

			return true;
		}
	}

	return false;
}

void CMPCameraInput::_giveUnitPositionAlignedToMaptile(Unit* unit, MapTile* maptile) {

	unit->m_TransformCmp->m_PosX = maptile->m_TransformCmp->m_PosX + m_OffsetX;
	unit->m_TransformCmp->m_PosY = maptile->m_TransformCmp->m_PosY + m_OffsetY;
}

bool CMPCameraInput::_hasUnitAProfessionAlready(Unit* unit) {

	if (COMPARE_STRINGS(unit->m_UnitClass->m_UnitClassName, "Citizen") == 0) {
		return false;
	}
	return true;
}

bool CMPCameraInput::_doesPlayerWantToResetProfession() {

	using namespace std;

	cout << color(colors::DARKRED);
	cout << "You are about to replace a units profession." << endl;
	cout << "Do you want to proceed?" << endl;
	cout << "[Y]es or [N]o" << white << endl;

	std::string answer;
	cin >> answer;

	if (COMPARE_STRINGS(answer, "Yes") == 0 ||
		COMPARE_STRINGS(answer, "Y") == 0 ||
		COMPARE_STRINGS(answer, "yes") == 0 ||
		COMPARE_STRINGS(answer, "y") == 0) {
		return true;

	}
	else {
		return false;
	}

}

std::vector<std::string> CMPCameraInput::_getPossibleProfessionsOnMaptile(MapTile* maptile) {

	std::vector<std::string> vec;

	// Some flags.
	bool has_forest = false;
	bool has_hills = false;
	bool has_mountains = false;


	for (auto entt = maptile->m_MapTileEntities->begin(); entt != maptile->m_MapTileEntities->end(); ++entt) {

		GameEntity* e = *entt;

		// Check for basetype entities on maptile, like forests...
		if (COMPARE_STRINGS(e->m_IDCmp->m_DynamicTypeName, "Forest") == 0) {
			vec.push_back("Hunter");
			vec.push_back("Woodcutter");
			vec.push_back("Gatherer");


			has_forest = true;
		}
		
		if (COMPARE_STRINGS(e->m_IDCmp->m_DynamicTypeName, "Hills") == 0) {
			vec.push_back("Bronze Miner");
			vec.push_back("Iron Miner");
			vec.push_back("Malachite Miner");
			vec.push_back("Adamantium Miner");
			vec.push_back("Salt Miner");
			vec.push_back("Stone Miner");

			has_hills = true;
		}
		
		if (COMPARE_STRINGS(e->m_IDCmp->m_DynamicTypeName, "Mountains") == 0) {
			vec.push_back("Bronze Miner");
			vec.push_back("Iron Miner");
			vec.push_back("Malachite Miner");
			vec.push_back("Adamantium Miner");
			vec.push_back("Salt Miner");
			vec.push_back("Stone Miner");

			has_mountains = true;
		}

		// Check for possible ressources on maptile like deer and bears...
		// TODO:

	}

	// Check for maptile type self as possible ressource...
	if (maptile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_WATER_SHALLOW) {
		vec.push_back("Fisher");
	}
	if (maptile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_TEMPERATE && 
		(!has_forest && !has_hills && !has_mountains)) { // only if it is a clear grass maptile.

		vec.push_back("Farmer");
		vec.push_back("Clayminer");
		vec.push_back("Gatherer");

	}
	if (maptile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_JUNGLE &&
		(!has_forest && !has_hills && !has_mountains)) { // only if its a clear jungle grass tile..

		vec.push_back("Farmer");
		vec.push_back("Clayminer");

	}
	if (maptile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_SAVANNAH && 
		(!has_forest && !has_hills && !has_mountains)) { // Only if its a clear savannah grass tile..

		vec.push_back("Farmer");
		vec.push_back("Clayminer");
		vec.push_back("Gatherer");


	}
	if (maptile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_TUNDRA && 
		(!has_forest && !has_hills && !has_mountains)) { // only if its a clear tudnra tile...

		vec.push_back("Farmer");
		vec.push_back("Gatherer");

	}


	// Return vector without duplicates..
	std::vector<std::string> return_vec;
	for (auto it : vec) {

		// Check whether a profession is already contained in return_vec.
		std::vector<std::string>::iterator itr = std::find(return_vec.begin(), return_vec.end(), it);

		if (itr == return_vec.end()) { // Not found...

			return_vec.push_back(it);
		}
	}

	return return_vec;
}

Unit* CMPCameraInput::_isUnitPresentOnMaptile(MapTile* maptile) {

	for (auto it : PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyViewedCity->m_PresentUnitsVector) {

		if (it->m_TransformCmp->m_PosX == maptile->m_TransformCmp->m_PosX &&
			it->m_TransformCmp->m_PosY == maptile->m_TransformCmp->m_PosY) {

			return static_cast<Unit*>(it);
		}
	}

	return nullptr;
}


bool CMPCameraInput::_hasPlayerUnitTechRequirements(std::string tech, Player* p) {

	if (COMPARE_STRINGS(GetTechnologyRequirementsForUnit(tech), "All") == 0) return true; // Means, tech has no requirements and as such is available.


	for (auto itr : p->m_PlayersTechnologies) {

		if (itr.second == 1) { // Lookup only for already researched techs.

			if (COMPARE_STRINGS_2(GetTechnologyRequirementsForUnit(tech), itr.first) == 0) return true;
		}
	}

	return false;
}


void CMPCameraInput::_handleCityViewKeyboard(Camera* cam) {

	Game* context = cam->m_Game;

	if (PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyViewedCity == nullptr) return;
	City* city = PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyViewedCity;




	// CLOSE CityView.
	if (context->GetKey(olc::Key::ESCAPE).bReleased) {

		context->m_Renderer->ChangeRenderMode();
		context->m_Renderer->SetCurrentViewedCity(nullptr); // Reset city which we now view.
		PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyViewedCity = nullptr;
	}



	// Spawning new citizen on click.
	if (context->GetKey(olc::Key::ENTER).bReleased) {

		if (city->m_JoblessCitizens.size() < 10) { // Need to check...

			Unit* u = SpawnCitizenInCity(city, 0, 0);
			city->AddCitizenToJobless(u);
		}
	}
}


void CMPCameraInput::HandleMouse(Camera* cam) {

	Game* context = cam->m_Game;

	switch (context->m_Renderer->m_RenderMode) {
	case Renderer::RenderMode::RENDERMODE_CITYVIEW:
		_handleCityViewMouse(cam);
		break;
	case Renderer::RenderMode::RENDERMODE_MAPVIEW:
		_handleMapViewMouse(cam);
		break;
	default:
		break;
	}
}



void Game::_loadSpriteResources() {

	using namespace olc;
	
	// Loading sprites and decals.
	Sprite* s1 = new Sprite("assets/map/forest_temperate_normal.png");
	Sprite* s2 = new Sprite("assets/map/forest_temperate_deep.png");
	Sprite* s3 = new Sprite("assets/map/forest_temperate_scarce.png");
	Sprite* s5 = new Sprite("assets/map/forest_tundra_normal.png");
	Sprite* s6 = new Sprite("assets/map/forest_tundra_deep.png");
	Sprite* s7 = new Sprite("assets/map/forest_tundra_scarce.png");
	Sprite* s8 = new Sprite("assets/map/highmountain.png");
	Sprite* s9 = new Sprite("assets/map/hills.png");
	Sprite* s10 = new Sprite("assets/map/ice.png");
	Sprite* s12 = new Sprite("assets/map/sand.png");
	Sprite* s13 = new Sprite("assets/map/savannah.png");
	Sprite* s14 = new Sprite("assets/map/snow.png");
	Sprite* s15 = new Sprite("assets/map/temperate.png");
	Sprite* s16 = new Sprite("assets/map/tundra.png");
	Sprite* s17 = new Sprite("assets/map/water_deep.png");
	Sprite* s18 = new Sprite("assets/map/water_shallow.png");
	Sprite* s0 = new Sprite("assets/map/jungle.png");

	
	Sprite* s19 = new Sprite("assets/map/forest_temperate_dying.png");
	Sprite* s20 = new Sprite("assets/map/forest_tundra_dying.png");


	Sprite* s21 = new Sprite("assets/map/forest_savannah_scarce.png");
	Sprite* s4 = new Sprite("assets/map/forest_savannah_normal.png");
	Sprite* s22 = new Sprite("assets/map/forest_savannah_deep.png");
	Sprite* s23 = new Sprite("assets/map/forest_savannah_dying.png");


	Sprite* s24 = new Sprite("assets/map/forest_jungle_scarce.png");
	Sprite* s11 = new Sprite("assets/map/forest_jungle_normal.png");
	Sprite* s25 = new Sprite("assets/map/forest_jungle_deep.png");
	Sprite* s26 = new Sprite("assets/map/forest_jungle_dying.png");




	// Load colored cells
	Sprite* c1 = new Sprite("assets/map/overlay_cell/map_cell_black.png");
	Sprite* c2 = new Sprite("assets/map/overlay_cell/map_cell_blue.png");
	Sprite* c3 = new Sprite("assets/map/overlay_cell/map_cell_brown.png");
	Sprite* c4 = new Sprite("assets/map/overlay_cell/map_cell_green.png");
	Sprite* c5 = new Sprite("assets/map/overlay_cell/map_cell_magenta.png");
	Sprite* c6 = new Sprite("assets/map/overlay_cell/map_cell_orange.png");
	Sprite* c7 = new Sprite("assets/map/overlay_cell/map_cell_red.png");
	Sprite* c8 = new Sprite("assets/map/overlay_cell/map_cell_yellow.png");
	Sprite* c9 = new Sprite("assets/map/overlay_cell/map_cell_white.png");


	// Borders cells
	Sprite* c10 = new Sprite("assets/map/overlay_cell/map_cell_border_down.png");
	Sprite* c11 = new Sprite("assets/map/overlay_cell/map_cell_border_down_left.png");
	Sprite* c12 = new Sprite("assets/map/overlay_cell/map_cell_border_down_right.png");
	Sprite* c13 = new Sprite("assets/map/overlay_cell/map_cell_border_down_up_right.png");
	Sprite* c14 = new Sprite("assets/map/overlay_cell/map_cell_border_left.png");
	Sprite* c15 = new Sprite("assets/map/overlay_cell/map_cell_border_left_right.png");
	Sprite* c16 = new Sprite("assets/map/overlay_cell/map_cell_border_left_right_down.png");
	Sprite* c17 = new Sprite("assets/map/overlay_cell/map_cell_border_left_up_down.png");
	Sprite* c18 = new Sprite("assets/map/overlay_cell/map_cell_border_left_up_right.png");
	Sprite* c19 = new Sprite("assets/map/overlay_cell/map_cell_border_right.png");
	Sprite* c20 = new Sprite("assets/map/overlay_cell/map_cell_border_up.png");
	Sprite* c21 = new Sprite("assets/map/overlay_cell/map_cell_border_up_down.png");
	Sprite* c22 = new Sprite("assets/map/overlay_cell/map_cell_border_up_left.png");
	Sprite* c23 = new Sprite("assets/map/overlay_cell/map_cell_border_up_right.png");
	Sprite* c24 = new Sprite("assets/unit/unit_rangecell.png");
	Sprite* c25 = new Sprite("assets/map/overlay_cell/map_cell_fog_of_war.png");



	m_SpriteStorage.push_back(c1);
	m_SpriteStorage.push_back(c2);
	m_SpriteStorage.push_back(c3);
	m_SpriteStorage.push_back(c4);
	m_SpriteStorage.push_back(c5);
	m_SpriteStorage.push_back(c6);
	m_SpriteStorage.push_back(c7);
	m_SpriteStorage.push_back(c8);
	m_SpriteStorage.push_back(c9);

	m_SpriteStorage.push_back(c10);
	m_SpriteStorage.push_back(c11);
	m_SpriteStorage.push_back(c12);
	m_SpriteStorage.push_back(c13);
	m_SpriteStorage.push_back(c14);
	m_SpriteStorage.push_back(c15);
	m_SpriteStorage.push_back(c16);
	m_SpriteStorage.push_back(c17);
	m_SpriteStorage.push_back(c18);
	m_SpriteStorage.push_back(c19);
	m_SpriteStorage.push_back(c20);
	m_SpriteStorage.push_back(c21);
	m_SpriteStorage.push_back(c22);
	m_SpriteStorage.push_back(c23);
	m_SpriteStorage.push_back(c24);
	m_SpriteStorage.push_back(c25);


	Decal* dec10 = new Decal(c10);
	Decal* dec11 = new Decal(c11);
	Decal* dec12 = new Decal(c12);
	Decal* dec13 = new Decal(c13);
	Decal* dec14 = new Decal(c14);
	Decal* dec15 = new Decal(c15);
	Decal* dec16 = new Decal(c16);
	Decal* dec17 = new Decal(c17);
	Decal* dec18 = new Decal(c18);
	Decal* dec19 = new Decal(c19);
	Decal* dec20 = new Decal(c20);
	Decal* dec21 = new Decal(c21);
	Decal* dec22 = new Decal(c22);
	Decal* dec23 = new Decal(c23);
	Decal* dec24 = new Decal(c24);
	Decal* dec25 = new Decal(c25);


	m_SpriteResourceMap.insert(std::make_pair("map_cell_border_down", dec10));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_border_down_left", dec11));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_border_down_right", dec12));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_border_down_up_right", dec13));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_border_left", dec14));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_border_left_right", dec15));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_border_left_right_down", dec16));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_border_left_up_down", dec17));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_border_left_up_right", dec18));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_border_right", dec19));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_border_up", dec20));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_border_up_down", dec21));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_border_up_left", dec22));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_border_up_right", dec23));
	m_SpriteResourceMap.insert(std::make_pair("unit_rangecell", dec24));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_fog_of_war", dec25));



	// River tiles.
	Sprite* rv1 = new Sprite("assets/map/river_down_left.png");
	Sprite* rv2 = new Sprite("assets/map/river_down_right.png");
	Sprite* rv3 = new Sprite("assets/map/river_left_right.png");
	Sprite* rv4 = new Sprite("assets/map/river_left_right_down.png");
	Sprite* rv5 = new Sprite("assets/map/river_left_up_down.png");
	Sprite* rv6 = new Sprite("assets/map/river_up_down.png");
	Sprite* rv7 = new Sprite("assets/map/river_up_left.png");
	Sprite* rv8 = new Sprite("assets/map/river_up_right.png");
	Sprite* rv9 = new Sprite("assets/map/river_up_right_down.png");
	Sprite* rv10 = new Sprite("assets/map/river_up_right_left.png");
	Sprite* rv11 = new Sprite("assets/map/river_up_right_left_down.png");

	m_SpriteStorage.push_back(rv1);
	m_SpriteStorage.push_back(rv2);
	m_SpriteStorage.push_back(rv3);
	m_SpriteStorage.push_back(rv4);
	m_SpriteStorage.push_back(rv5);
	m_SpriteStorage.push_back(rv6);
	m_SpriteStorage.push_back(rv7);
	m_SpriteStorage.push_back(rv8);
	m_SpriteStorage.push_back(rv9);
	m_SpriteStorage.push_back(rv10);
	m_SpriteStorage.push_back(rv11);

	Decal* drv1 = new Decal(rv1);
	Decal* drv2 = new Decal(rv2);
	Decal* drv3 = new Decal(rv3);
	Decal* drv4 = new Decal(rv4);
	Decal* drv5 = new Decal(rv5);
	Decal* drv6 = new Decal(rv6);
	Decal* drv7 = new Decal(rv7);
	Decal* drv8 = new Decal(rv8);
	Decal* drv9 = new Decal(rv9);
	Decal* drv10 = new Decal(rv10);
	Decal* drv11 = new Decal(rv11);

	m_SpriteResourceMap.insert(std::make_pair("river_down_left", drv1));
	m_SpriteResourceMap.insert(std::make_pair("river_down_right", drv2));
	m_SpriteResourceMap.insert(std::make_pair("river_left_right", drv3));
	m_SpriteResourceMap.insert(std::make_pair("river_left_right_down", drv4));
	m_SpriteResourceMap.insert(std::make_pair("river_left_up_down", drv5));
	m_SpriteResourceMap.insert(std::make_pair("river_up_down", drv6));
	m_SpriteResourceMap.insert(std::make_pair("river_up_left", drv7));
	m_SpriteResourceMap.insert(std::make_pair("river_up_right", drv8));
	m_SpriteResourceMap.insert(std::make_pair("river_up_right_down", drv9));
	m_SpriteResourceMap.insert(std::make_pair("river_up_right_left", drv10));
	m_SpriteResourceMap.insert(std::make_pair("river_up_right_left_down", drv11));



	// Mapview Ressources
	Sprite* r1 = new Sprite("assets/ressources/mapview/ressource_map_bear.png");
	Sprite* r2 = new Sprite("assets/ressources/mapview/ressource_map_boar.png");
	Sprite* r3 = new Sprite("assets/ressources/mapview/ressource_map_deer.png");
	Sprite* r4 = new Sprite("assets/ressources/mapview/ressource_map_horse.png");
	Sprite* r5 = new Sprite("assets/ressources/mapview/ressource_map_raptor.png");
	Sprite* r6 = new Sprite("assets/ressources/mapview/ressource_map_guar.png");


	m_SpriteStorage.push_back(r1);
	m_SpriteStorage.push_back(r2);
	m_SpriteStorage.push_back(r3);
	m_SpriteStorage.push_back(r4);
	m_SpriteStorage.push_back(r5);
	m_SpriteStorage.push_back(r6);



	// Decals for mapressources
	Decal* dr1 = new Decal(r1);
	Decal* dr2 = new Decal(r2);
	Decal* dr3 = new Decal(r3);
	Decal* dr4 = new Decal(r4);
	Decal* dr5 = new Decal(r5);
	Decal* dr6 = new Decal(r6);


	m_SpriteResourceMap.insert(std::make_pair("ressource_map_bear", dr1));
	m_SpriteResourceMap.insert(std::make_pair("ressource_map_boar", dr2));
	m_SpriteResourceMap.insert(std::make_pair("ressource_map_deer", dr3));
	m_SpriteResourceMap.insert(std::make_pair("ressource_map_horse", dr4));
	m_SpriteResourceMap.insert(std::make_pair("ressource_map_raptor", dr5));
	m_SpriteResourceMap.insert(std::make_pair("ressource_map_guar", dr6));




	// Decals for colored cells
	Decal* dc1 = new Decal(c1);
	Decal* dc2 = new Decal(c2);
	Decal* dc3 = new Decal(c3);
	Decal* dc4 = new Decal(c4);
	Decal* dc5 = new Decal(c5);
	Decal* dc6 = new Decal(c6);
	Decal* dc7 = new Decal(c7);
	Decal* dc8 = new Decal(c8);
	Decal* dc9 = new Decal(c9);



	m_SpriteStorage.push_back(s0);
	m_SpriteStorage.push_back(s1);
	m_SpriteStorage.push_back(s2);
	m_SpriteStorage.push_back(s3);
	m_SpriteStorage.push_back(s4);
	m_SpriteStorage.push_back(s5);
	m_SpriteStorage.push_back(s6);
	m_SpriteStorage.push_back(s7);
	m_SpriteStorage.push_back(s8);
	m_SpriteStorage.push_back(s9);
	m_SpriteStorage.push_back(s10);
	m_SpriteStorage.push_back(s11);
	m_SpriteStorage.push_back(s12);
	m_SpriteStorage.push_back(s13);
	m_SpriteStorage.push_back(s14);
	m_SpriteStorage.push_back(s15);
	m_SpriteStorage.push_back(s16);
	m_SpriteStorage.push_back(s17);
	m_SpriteStorage.push_back(s18);
	m_SpriteStorage.push_back(s19);
	m_SpriteStorage.push_back(s20);
	m_SpriteStorage.push_back(s21);
	m_SpriteStorage.push_back(s22);
	m_SpriteStorage.push_back(s23);
	m_SpriteStorage.push_back(s24);
	m_SpriteStorage.push_back(s25);
	m_SpriteStorage.push_back(s26);




	Decal* d0 = new Decal(s0);
	Decal* d1 = new Decal(s1);
	Decal* d2 = new Decal(s2);
	Decal* d3 = new Decal(s3);
	Decal* d4 = new Decal(s4);
	Decal* d5 = new Decal(s5);
	Decal* d6 = new Decal(s6);
	Decal* d7 = new Decal(s7);
	Decal* d8 = new Decal(s8);
	Decal* d9 = new Decal(s9);
	Decal* d10 = new Decal(s10);
	Decal* d11 = new Decal(s11);
	Decal* d12 = new Decal(s12);
	Decal* d13 = new Decal(s13);
	Decal* d14 = new Decal(s14);
	Decal* d15 = new Decal(s15);
	Decal* d16 = new Decal(s16);
	Decal* d17 = new Decal(s17);
	Decal* d18 = new Decal(s18);
	Decal* d19 = new Decal(s19);
	Decal* d20 = new Decal(s20);
	Decal* d21 = new Decal(s21);
	Decal* d22 = new Decal(s22);
	Decal* d23 = new Decal(s23);
	Decal* d24 = new Decal(s24);
	Decal* d25 = new Decal(s25);
	Decal* d26 = new Decal(s26);





	// Create Decals from sprites.
	m_SpriteResourceMap.insert(std::make_pair("jungle", d0));
	m_SpriteResourceMap.insert(std::make_pair("forest_temperate_normal", d1));
	m_SpriteResourceMap.insert(std::make_pair("forest_temperate_deep", d2));
	m_SpriteResourceMap.insert(std::make_pair("forest_temperate_scarce", d3));
	m_SpriteResourceMap.insert(std::make_pair("forest_savannah_normal", d4));
	m_SpriteResourceMap.insert(std::make_pair("forest_tundra_normal", d5));
	m_SpriteResourceMap.insert(std::make_pair("forest_tundra_deep", d6));
	m_SpriteResourceMap.insert(std::make_pair("forest_tundra_scarce", d7));
	m_SpriteResourceMap.insert(std::make_pair("highmountain", d8));
	m_SpriteResourceMap.insert(std::make_pair("hills", d9));
	m_SpriteResourceMap.insert(std::make_pair("ice", d10));
	m_SpriteResourceMap.insert(std::make_pair("forest_jungle_normal", d11));
	m_SpriteResourceMap.insert(std::make_pair("sand", d12));
	m_SpriteResourceMap.insert(std::make_pair("savannah", d13));
	m_SpriteResourceMap.insert(std::make_pair("snow", d14));
	m_SpriteResourceMap.insert(std::make_pair("temperate", d15));
	m_SpriteResourceMap.insert(std::make_pair("tundra", d16));
	m_SpriteResourceMap.insert(std::make_pair("water_deep", d17));
	m_SpriteResourceMap.insert(std::make_pair("water_shallow", d18));
	m_SpriteResourceMap.insert(std::make_pair("forest_temperate_dying", d19));
	m_SpriteResourceMap.insert(std::make_pair("forest_tundra_dying", d20));


	m_SpriteResourceMap.insert(std::make_pair("forest_savannah_scarce", d21));
	m_SpriteResourceMap.insert(std::make_pair("forest_savannah_deep", d22));
	m_SpriteResourceMap.insert(std::make_pair("forest_savannah_dying", d23));

	m_SpriteResourceMap.insert(std::make_pair("forest_jungle_scarce", d24));
	m_SpriteResourceMap.insert(std::make_pair("forest_jungle_deep", d25));
	m_SpriteResourceMap.insert(std::make_pair("forest_jungle_dying", d26));




	// Map colored cells.
	m_SpriteResourceMap.insert(std::make_pair("map_cell_black", dc1));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_blue", dc2));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_brown", dc3));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_green", dc4));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_magenta", dc5));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_orange", dc6));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_red", dc7));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_yellow", dc8));
	m_SpriteResourceMap.insert(std::make_pair("map_cell_white", dc9));






	////////////////////////////////////////////////////////////////
	// Load cities
	Sprite* city1 = new Sprite("assets/city/orc/city_orc_huge.png");
	Sprite* city2 = new Sprite("assets/city/human/city_human_huge.png");
	Sprite* city3 = new Sprite("assets/city/human/city_human_small.png");
	Sprite* city4 = new Sprite("assets/city/highelf/city_highelf_small.png");
	Sprite* city5 = new Sprite("assets/city/orc/city_orc_small.png");
	Sprite* city6 = new Sprite("assets/city/orc/city_orc_normal.png");
	Sprite* city7 = new Sprite("assets/city/orc/city_orc_big.png");
	Sprite* city8 = new Sprite("assets/city/human/city_human_normal.png");
	Sprite* city9 = new Sprite("assets/city/human/city_human_big.png");

	
	m_SpriteStorage.push_back(city1);
	m_SpriteStorage.push_back(city2);
	m_SpriteStorage.push_back(city3);
	m_SpriteStorage.push_back(city4);
	m_SpriteStorage.push_back(city5);
	m_SpriteStorage.push_back(city6);
	m_SpriteStorage.push_back(city7);
	m_SpriteStorage.push_back(city8);
	m_SpriteStorage.push_back(city9);


	Decal* dcity1 = new Decal(city1);
	Decal* dcity2 = new Decal(city2);
	Decal* dcity3 = new Decal(city3);
	Decal* dcity4 = new Decal(city4);
	Decal* dcity5 = new Decal(city5);
	Decal* dcity6 = new Decal(city6);
	Decal* dcity7 = new Decal(city7);
	Decal* dcity8 = new Decal(city8);
	Decal* dcity9 = new Decal(city9);


	m_SpriteResourceMap.insert(std::make_pair("city_orc_huge", dcity1));
	m_SpriteResourceMap.insert(std::make_pair("city_human_huge", dcity2));
	m_SpriteResourceMap.insert(std::make_pair("city_human_small", dcity3));
	m_SpriteResourceMap.insert(std::make_pair("city_highelf_small", dcity4));
	m_SpriteResourceMap.insert(std::make_pair("city_orc_small", dcity5));
	m_SpriteResourceMap.insert(std::make_pair("city_orc_normal", dcity6));
	m_SpriteResourceMap.insert(std::make_pair("city_orc_big", dcity7));
	m_SpriteResourceMap.insert(std::make_pair("city_human_normal", dcity8));
	m_SpriteResourceMap.insert(std::make_pair("city_human_big", dcity9));


	// Forts
	Sprite* fort1 = new Sprite("assets/fort/human/fort_human_small.png");
	Sprite* fort2 = new Sprite("assets/fort/human/fort_human_normal.png");
	Sprite* fort3 = new Sprite("assets/fort/human/fort_human_big.png");
	Sprite* fort4 = new Sprite("assets/fort/human/fort_human_huge.png");
	Sprite* fort5 = new Sprite("assets/fort/orc/fort_orc_small.png");
	Sprite* fort6 = new Sprite("assets/fort/orc/fort_orc_normal.png");
	Sprite* fort7 = new Sprite("assets/fort/orc/fort_orc_big.png");
	Sprite* fort8 = new Sprite("assets/fort/orc/fort_orc_huge.png");

	m_SpriteStorage.push_back(fort1);
	m_SpriteStorage.push_back(fort2);
	m_SpriteStorage.push_back(fort3);
	m_SpriteStorage.push_back(fort4);
	m_SpriteStorage.push_back(fort5);
	m_SpriteStorage.push_back(fort6);
	m_SpriteStorage.push_back(fort7);
	m_SpriteStorage.push_back(fort8);

	Decal* dfort1 = new Decal(fort1);
	Decal* dfort2 = new Decal(fort2);
	Decal* dfort3 = new Decal(fort3);
	Decal* dfort4 = new Decal(fort4);
	Decal* dfort5 = new Decal(fort5);
	Decal* dfort6 = new Decal(fort6);
	Decal* dfort7 = new Decal(fort7);
	Decal* dfort8 = new Decal(fort8);


	m_SpriteResourceMap.insert(std::make_pair("fort_human_small", dfort1));
	m_SpriteResourceMap.insert(std::make_pair("fort_human_normal", dfort2));
	m_SpriteResourceMap.insert(std::make_pair("fort_human_big", dfort3));
	m_SpriteResourceMap.insert(std::make_pair("fort_human_huge", dfort4));
	m_SpriteResourceMap.insert(std::make_pair("fort_orc_small", dfort5));
	m_SpriteResourceMap.insert(std::make_pair("fort_orc_normal", dfort6));
	m_SpriteResourceMap.insert(std::make_pair("fort_orc_big", dfort7));
	m_SpriteResourceMap.insert(std::make_pair("fort_orc_huge", dfort8));




	////////////////////////////////////////////////////////////////////
	// Sprites for cities buildings.
	Sprite* b1 = new Sprite("assets/buildings/wooden_house.png");
	Sprite* b2 = new Sprite("assets/buildings/shack.png");
	Sprite* b3 = new Sprite("assets/buildings/stone_house.png");
	Sprite* b4 = new Sprite("assets/buildings/brick_house.png");
	Sprite* b5 = new Sprite("assets/buildings/storage.png");
	Sprite* b6 = new Sprite("assets/buildings/wooden_storage.png");
	Sprite* b7 = new Sprite("assets/buildings/stone_storage.png");
	Sprite* b8 = new Sprite("assets/buildings/brick_storage.png");
	Sprite* b9 = new Sprite("assets/buildings/wisemen_hut.png");
	Sprite* b10 = new Sprite("assets/buildings/wooden_school.png");
	Sprite* b11 = new Sprite("assets/buildings/stone_school.png");
	Sprite* b12 = new Sprite("assets/buildings/brick_school.png");
	Sprite* b13 = new Sprite("assets/buildings/shrine.png");
	Sprite* b14 = new Sprite("assets/buildings/magick_school.png");
	Sprite* b15 = new Sprite("assets/buildings/magick_college.png");
	Sprite* b16 = new Sprite("assets/buildings/inventors_hut.png");
	Sprite* b17 = new Sprite("assets/buildings/small_workshop.png");
	Sprite* b18 = new Sprite("assets/buildings/big_workshop.png");
	Sprite* b19 = new Sprite("assets/buildings/champions_hut.png");
	Sprite* b20 = new Sprite("assets/buildings/warrior_school.png");




	m_SpriteStorage.push_back(b1);
	m_SpriteStorage.push_back(b2);
	m_SpriteStorage.push_back(b3);
	m_SpriteStorage.push_back(b4);
	m_SpriteStorage.push_back(b5);
	m_SpriteStorage.push_back(b6);
	m_SpriteStorage.push_back(b7);
	m_SpriteStorage.push_back(b8);
	m_SpriteStorage.push_back(b9);
	m_SpriteStorage.push_back(b10);
	m_SpriteStorage.push_back(b11);
	m_SpriteStorage.push_back(b12);
	m_SpriteStorage.push_back(b13);
	m_SpriteStorage.push_back(b14);
	m_SpriteStorage.push_back(b15);
	m_SpriteStorage.push_back(b16);
	m_SpriteStorage.push_back(b17);
	m_SpriteStorage.push_back(b18);
	m_SpriteStorage.push_back(b19);
	m_SpriteStorage.push_back(b20);




	Decal* db1 = new Decal(b1);
	Decal* db2 = new Decal(b2);
	Decal* db3 = new Decal(b3);
	Decal* db4 = new Decal(b4);
	Decal* db5 = new Decal(b5);
	Decal* db6 = new Decal(b6);
	Decal* db7 = new Decal(b7);
	Decal* db8 = new Decal(b8);
	Decal* db9 = new Decal(b9);
	Decal* db10 = new Decal(b10);
	Decal* db11 = new Decal(b11);
	Decal* db12 = new Decal(b12);
	Decal* db13 = new Decal(b13);
	Decal* db14 = new Decal(b14);
	Decal* db15 = new Decal(b15);
	Decal* db16 = new Decal(b16);
	Decal* db17 = new Decal(b17);
	Decal* db18 = new Decal(b18);
	Decal* db19 = new Decal(b19);
	Decal* db20 = new Decal(b20);



	m_SpriteResourceMap.insert(std::make_pair("wooden_house", db1));
	m_SpriteResourceMap.insert(std::make_pair("shack", db2));
	m_SpriteResourceMap.insert(std::make_pair("stone_house", db3));
	m_SpriteResourceMap.insert(std::make_pair("brick_house", db4));
	m_SpriteResourceMap.insert(std::make_pair("storage", db5));
	m_SpriteResourceMap.insert(std::make_pair("wooden_storage", db6));
	m_SpriteResourceMap.insert(std::make_pair("stone_storage", db7));
	m_SpriteResourceMap.insert(std::make_pair("brick_storage", db8));
	m_SpriteResourceMap.insert(std::make_pair("wisemen_hut", db9));
	m_SpriteResourceMap.insert(std::make_pair("wooden_school", db10));
	m_SpriteResourceMap.insert(std::make_pair("stone_school", db11));
	m_SpriteResourceMap.insert(std::make_pair("brick_school", db12));
	m_SpriteResourceMap.insert(std::make_pair("shrine", db13));
	m_SpriteResourceMap.insert(std::make_pair("magick_school", db14));
	m_SpriteResourceMap.insert(std::make_pair("magick_college", db15));
	m_SpriteResourceMap.insert(std::make_pair("inventors_hut", db16));
	m_SpriteResourceMap.insert(std::make_pair("small_workshop", db17));
	m_SpriteResourceMap.insert(std::make_pair("big_workshop", db18));
	m_SpriteResourceMap.insert(std::make_pair("champions_hut", db19));
	m_SpriteResourceMap.insert(std::make_pair("warrior_school", db20));






	/////////////////////////////////////////////////////////////////////////////////////
	// Cityview sprites
	/*
	* NOTE:
	* 
	* Load city view sprites like this...
	* 
	Sprite* cityview1 = new Sprite("assets/city/human/city_human_normal_cityview.jpg");

	Decal* dcityview1 = new Decal(cityview1);

	m_SpriteResourceMap.insert(std::make_pair("city_human_normal_cityview", dcityview1));
	*/

	// Cityview Backgrounds.
	AddSpriteToStorage("assets/background/city/city_background_forest_temperate.png", "city_background_forest_temperate");
	AddSpriteToStorage("assets/background/city/city_background_forest_jungle.png", "city_background_forest_jungle");
	AddSpriteToStorage("assets/background/city/city_background_forest_tundra.png", "city_background_forest_tundra");
	AddSpriteToStorage("assets/background/city/city_background_forest_savannah.png", "city_background_forest_savannah");

	AddSpriteToStorage("assets/background/city/city_background_hills.png", "city_background_hills");
	AddSpriteToStorage("assets/background/city/city_background_river_no_water.png", "city_background_river_no_water");
	AddSpriteToStorage("assets/background/city/city_background_river_with_water.png", "city_background_river_with_water");
	AddSpriteToStorage("assets/background/city/city_background_wooden_wall_no_water.png", "city_background_wooden_wall_no_water");
	AddSpriteToStorage("assets/background/city/city_background_wooden_wall_with_water.png", "city_background_wooden_wall_with_water");

	AddSpriteToStorage("assets/background/city/human/city_background_human_no_water.png", "city_background_human_no_water");
	AddSpriteToStorage("assets/background/city/human/city_background_human_with_water.png", "city_background_human_with_water");

	AddSpriteToStorage("assets/background/city/darkelf/city_background_darkelf_no_water.png", "city_background_darkelf_no_water");
	AddSpriteToStorage("assets/background/city/darkelf/city_background_darkelf_with_water.png", "city_background_darkelf_with_water");

	AddSpriteToStorage("assets/background/city/highelf/city_background_highelf_no_water.png", "city_background_highelf_no_water");
	AddSpriteToStorage("assets/background/city/highelf/city_background_highelf_with_water.png", "city_background_highelf_with_water");

	AddSpriteToStorage("assets/background/city/dwarf/city_background_dwarf_no_water.png", "city_background_dwarf_no_water");
	AddSpriteToStorage("assets/background/city/dwarf/city_background_dwarf_with_water.png", "city_background_dwarf_with_water");

	AddSpriteToStorage("assets/background/city/orc/city_background_orc_no_water.png", "city_background_orc_no_water");
	AddSpriteToStorage("assets/background/city/orc/city_background_orc_with_water.png", "city_background_orc_with_water");

	AddSpriteToStorage("assets/background/city/gnome/city_background_gnome_no_water.png", "city_background_gnome_no_water");
	AddSpriteToStorage("assets/background/city/gnome/city_background_gnome_with_water.png", "city_background_gnome_with_water");

	AddSpriteToStorage("assets/background/city/goblin/city_background_goblin_no_water.png", "city_background_goblin_no_water");
	AddSpriteToStorage("assets/background/city/goblin/city_background_goblin_with_water.png", "city_background_goblin_with_water");

	AddSpriteToStorage("assets/background/city/troll/city_background_troll_no_water.png", "city_background_troll_no_water");
	AddSpriteToStorage("assets/background/city/troll/city_background_troll_with_water.png", "city_background_troll_with_water");




	// static gui sprite.
	Sprite* sidepanel = new Sprite("assets/sidepanel.png");
	Sprite* panel = new Sprite("assets/cityview_sidepanel.png");
	Sprite* panel2 = new Sprite("assets/cityview_upper_panel.png");

	m_SpriteStorage.push_back(sidepanel);
	m_SpriteStorage.push_back(panel);
	m_SpriteStorage.push_back(panel2);

	Decal* dside = new Decal(sidepanel);
	Decal* dside2 = new Decal(panel);
	Decal* dside3 = new Decal(panel2);


	m_SpriteResourceMap.insert(std::make_pair("sidepanel", dside));
	m_SpriteResourceMap.insert(std::make_pair("cityview_sidepanel", dside2));
	m_SpriteResourceMap.insert(std::make_pair("cityview_upper_panel", dside3));








	////////////////////////////////////////////////////////////////////////////
	// Units.
	Sprite* unit = new Sprite("assets/unit/human/human_citizen.png");
	Sprite* unit2 = new Sprite("assets/unit/human/human_farmer.png");
	Sprite* unit3 = new Sprite("assets/unit/human/human_woodcutter.png");
	Sprite* unit4 = new Sprite("assets/unit/orc/orc_citizen.png");
	Sprite* unit5 = new Sprite("assets/unit/orc/orc_farmer.png");
	Sprite* unit6 = new Sprite("assets/unit/orc/orc_woodcutter.png");
	Sprite* unit7 = new Sprite("assets/unit/highelf/highelf_citizen.png");
	Sprite* unit8 = new Sprite("assets/unit/highelf/highelf_farmer.png");
	Sprite* unit9 = new Sprite("assets/unit/highelf/highelf_woodcutter.png");
	Sprite* unit10 = new Sprite("assets/unit/darkelf/darkelf_citizen.png");
	Sprite* unit11 = new Sprite("assets/unit/darkelf/darkelf_farmer.png");
	Sprite* unit12 = new Sprite("assets/unit/darkelf/darkelf_woodcutter.png");
	Sprite* unit13 = new Sprite("assets/unit/dwarf/dwarf_citizen.png");
	Sprite* unit14 = new Sprite("assets/unit/dwarf/dwarf_farmer.png");
	Sprite* unit15 = new Sprite("assets/unit/dwarf/dwarf_woodcutter.png");
	Sprite* unit16 = new Sprite("assets/unit/gnome/gnome_citizen.png");
	Sprite* unit17 = new Sprite("assets/unit/gnome/gnome_farmer.png");
	Sprite* unit18 = new Sprite("assets/unit/gnome/gnome_woodcutter.png");
	Sprite* unit19 = new Sprite("assets/unit/goblin/goblin_citizen.png");
	Sprite* unit20 = new Sprite("assets/unit/goblin/goblin_farmer.png");
	Sprite* unit21 = new Sprite("assets/unit/goblin/goblin_woodcutter.png");
	Sprite* unit22 = new Sprite("assets/unit/troll/troll_citizen.png");
	Sprite* unit23 = new Sprite("assets/unit/troll/troll_farmer.png");
	Sprite* unit24 = new Sprite("assets/unit/troll/troll_woodcutter.png");




	m_SpriteStorage.push_back(unit);
	m_SpriteStorage.push_back(unit2);
	m_SpriteStorage.push_back(unit3);
	m_SpriteStorage.push_back(unit4);
	m_SpriteStorage.push_back(unit5);
	m_SpriteStorage.push_back(unit6);
	m_SpriteStorage.push_back(unit7);
	m_SpriteStorage.push_back(unit8);
	m_SpriteStorage.push_back(unit9);
	m_SpriteStorage.push_back(unit10);
	m_SpriteStorage.push_back(unit11);
	m_SpriteStorage.push_back(unit12);
	m_SpriteStorage.push_back(unit13);
	m_SpriteStorage.push_back(unit14);
	m_SpriteStorage.push_back(unit15);
	m_SpriteStorage.push_back(unit16);
	m_SpriteStorage.push_back(unit17);
	m_SpriteStorage.push_back(unit18);
	m_SpriteStorage.push_back(unit19);
	m_SpriteStorage.push_back(unit20);
	m_SpriteStorage.push_back(unit21);
	m_SpriteStorage.push_back(unit22);
	m_SpriteStorage.push_back(unit23);
	m_SpriteStorage.push_back(unit24);


	Decal* dunit = new Decal(unit);
	Decal* dunit2 = new Decal(unit2);
	Decal* dunit3 = new Decal(unit3);
	Decal* dunit4 = new Decal(unit4);
	Decal* dunit5 = new Decal(unit5);
	Decal* dunit6 = new Decal(unit6);
	Decal* dunit7 = new Decal(unit7);
	Decal* dunit8 = new Decal(unit8);
	Decal* dunit9 = new Decal(unit9);
	Decal* dunit10 = new Decal(unit10);
	Decal* dunit11 = new Decal(unit11);
	Decal* dunit12 = new Decal(unit12);
	Decal* dunit13 = new Decal(unit13);
	Decal* dunit14 = new Decal(unit14);
	Decal* dunit15 = new Decal(unit15);
	Decal* dunit16 = new Decal(unit16);
	Decal* dunit17 = new Decal(unit17);
	Decal* dunit18 = new Decal(unit18);
	Decal* dunit19 = new Decal(unit19);
	Decal* dunit20 = new Decal(unit20);
	Decal* dunit21 = new Decal(unit21);
	Decal* dunit22 = new Decal(unit22);
	Decal* dunit23 = new Decal(unit23);
	Decal* dunit24 = new Decal(unit24);


	m_SpriteResourceMap.insert(std::make_pair("human_citizen", dunit));
	m_SpriteResourceMap.insert(std::make_pair("human_farmer", dunit2));
	m_SpriteResourceMap.insert(std::make_pair("human_woodcutter", dunit3));

	m_SpriteResourceMap.insert(std::make_pair("orc_citizen", dunit4));
	m_SpriteResourceMap.insert(std::make_pair("orc_farmer", dunit5));
	m_SpriteResourceMap.insert(std::make_pair("orc_woodcutter", dunit6));

	m_SpriteResourceMap.insert(std::make_pair("highelf_citizen", dunit7));
	m_SpriteResourceMap.insert(std::make_pair("highelf_farmer", dunit8));
	m_SpriteResourceMap.insert(std::make_pair("highelf_woodcutter", dunit9));

	m_SpriteResourceMap.insert(std::make_pair("darkelf_citizen", dunit10));
	m_SpriteResourceMap.insert(std::make_pair("darkelf_farmer", dunit11));
	m_SpriteResourceMap.insert(std::make_pair("darkelf_woodcutter", dunit12));

	m_SpriteResourceMap.insert(std::make_pair("dwarf_citizen", dunit13));
	m_SpriteResourceMap.insert(std::make_pair("dwarf_farmer", dunit14));
	m_SpriteResourceMap.insert(std::make_pair("dwarf_citizen", dunit15));

	m_SpriteResourceMap.insert(std::make_pair("gnome_citizen", dunit16));
	m_SpriteResourceMap.insert(std::make_pair("gnome_farmer", dunit17));
	m_SpriteResourceMap.insert(std::make_pair("gnome_citizen", dunit18));

	m_SpriteResourceMap.insert(std::make_pair("goblin_citizen", dunit19));
	m_SpriteResourceMap.insert(std::make_pair("goblin_farmer", dunit20));
	m_SpriteResourceMap.insert(std::make_pair("goblin_woodcutter", dunit21));

	m_SpriteResourceMap.insert(std::make_pair("troll_citizen", dunit22));
	m_SpriteResourceMap.insert(std::make_pair("troll_farmer", dunit23));
	m_SpriteResourceMap.insert(std::make_pair("troll_woodcutter", dunit24));


	AddSpriteToStorage("assets/unit/darkelf/darkelf_hunter.png", "darkelf_hunter");
	AddSpriteToStorage("assets/unit/dwarf/dwarf_hunter.png", "dwarf_hunter");
	AddSpriteToStorage("assets/unit/gnome/gnome_hunter.png", "gnome_hunter");
	AddSpriteToStorage("assets/unit/goblin/goblin_hunter.png", "goblin_hunter");
	AddSpriteToStorage("assets/unit/highelf/highelf_hunter.png", "highelf_hunter");
	AddSpriteToStorage("assets/unit/human/human_hunter.png", "human_hunter");
	AddSpriteToStorage("assets/unit/orc/orc_hunter.png", "orc_hunter");
	AddSpriteToStorage("assets/unit/troll/troll_hunter.png", "troll_hunter");

	AddSpriteToStorage("assets/unit/darkelf/darkelf_fisher.png", "darkelf_fisher");
	AddSpriteToStorage("assets/unit/dwarf/dwarf_fisher.png", "dwarf_hunter");
	AddSpriteToStorage("assets/unit/gnome/gnome_fisher.png", "gnome_fisher");
	AddSpriteToStorage("assets/unit/goblin/goblin_fisher.png", "goblin_fisher");
	AddSpriteToStorage("assets/unit/highelf/highelf_fisher.png", "highelf_fisher");
	AddSpriteToStorage("assets/unit/human/human_fisher.png", "human_fisher");
	AddSpriteToStorage("assets/unit/orc/orc_fisher.png", "orc_fisher");
	AddSpriteToStorage("assets/unit/troll/troll_fisher.png", "troll_fisher");


	AddSpriteToStorage("assets/unit/darkelf/darkelf_clayminer.png", "darkelf_clayminer");
	AddSpriteToStorage("assets/unit/dwarf/dwarf_clayminer.png", "dwarf_clayminer");
	AddSpriteToStorage("assets/unit/gnome/gnome_clayminer.png", "gnome_clayminer");
	AddSpriteToStorage("assets/unit/goblin/goblin_clayminer.png", "goblin_clayminer");
	AddSpriteToStorage("assets/unit/highelf/highelf_clayminer.png", "highelf_clayminer");
	AddSpriteToStorage("assets/unit/human/human_clayminer.png", "human_clayminer");
	AddSpriteToStorage("assets/unit/orc/orc_clayminer.png", "orc_clayminer");
	AddSpriteToStorage("assets/unit/troll/troll_clayminer.png", "troll_clayminer");


	AddSpriteToStorage("assets/unit/darkelf/darkelf_miner.png", "darkelf_miner");
	AddSpriteToStorage("assets/unit/dwarf/dwarf_miner.png", "dwarf_miner");
	AddSpriteToStorage("assets/unit/gnome/gnome_miner.png", "gnome_miner");
	AddSpriteToStorage("assets/unit/goblin/goblin_miner.png", "goblin_miner");
	AddSpriteToStorage("assets/unit/highelf/highelf_miner.png", "highelf_miner");
	AddSpriteToStorage("assets/unit/human/human_miner.png", "human_miner");
	AddSpriteToStorage("assets/unit/orc/orc_miner.png", "orc_miner");
	AddSpriteToStorage("assets/unit/troll/troll_miner.png", "troll_miner");


	AddSpriteToStorage("assets/unit/darkelf/darkelf_gatherer.png", "darkelf_gatherer");
	AddSpriteToStorage("assets/unit/dwarf/dwarf_gatherer.png", "dwarf_gatherer");
	AddSpriteToStorage("assets/unit/gnome/gnome_gatherer.png", "gnome_gatherer");
	AddSpriteToStorage("assets/unit/goblin/goblin_gatherer.png", "goblin_gatherer");
	AddSpriteToStorage("assets/unit/highelf/highelf_gatherer.png", "highelf_gatherer");
	AddSpriteToStorage("assets/unit/human/human_gatherer.png", "human_gatherer");
	AddSpriteToStorage("assets/unit/orc/orc_gatherer.png", "orc_gatherer");
	AddSpriteToStorage("assets/unit/troll/troll_gatherer.png", "troll_gatherer");


	AddSpriteToStorage("assets/unit/darkelf/darkelf_brickburner.png", "darkelf_brickburner");
	AddSpriteToStorage("assets/unit/dwarf/dwarf_brickburner.png", "dwarf_brickburner");
	AddSpriteToStorage("assets/unit/gnome/gnome_brickburner.png", "gnome_brickburner");
	AddSpriteToStorage("assets/unit/goblin/goblin_brickburner.png", "goblin_brickburner");
	AddSpriteToStorage("assets/unit/highelf/highelf_brickburner.png", "highelf_brickburner");
	AddSpriteToStorage("assets/unit/human/human_brickburner.png", "human_brickburner");
	AddSpriteToStorage("assets/unit/orc/orc_brickburner.png", "orc_brickburner");
	AddSpriteToStorage("assets/unit/troll/troll_brickburner.png", "troll_brickburner");


	AddSpriteToStorage("assets/unit/darkelf/darkelf_carpenter.png", "darkelf_carpenter");
	AddSpriteToStorage("assets/unit/dwarf/dwarf_carpenter.png", "dwarf_carpenter");
	AddSpriteToStorage("assets/unit/gnome/gnome_carpenter.png", "gnome_carpenter");
	AddSpriteToStorage("assets/unit/goblin/goblin_carpenter.png", "goblin_carpenter");
	AddSpriteToStorage("assets/unit/highelf/highelf_carpenter.png", "highelf_carpenter");
	AddSpriteToStorage("assets/unit/human/human_carpenter.png", "human_carpenter");
	AddSpriteToStorage("assets/unit/orc/orc_carpenter.png", "orc_carpenter");
	AddSpriteToStorage("assets/unit/troll/troll_carpenter.png", "troll_carpenter");


	AddSpriteToStorage("assets/unit/darkelf/darkelf_mason.png", "darkelf_mason");
	AddSpriteToStorage("assets/unit/dwarf/dwarf_mason.png", "dwarf_mason");
	AddSpriteToStorage("assets/unit/gnome/gnome_mason.png", "gnome_mason");
	AddSpriteToStorage("assets/unit/goblin/goblin_mason.png", "goblin_mason");
	AddSpriteToStorage("assets/unit/highelf/highelf_mason.png", "highelf_mason");
	AddSpriteToStorage("assets/unit/human/human_mason.png", "human_mason");
	AddSpriteToStorage("assets/unit/orc/orc_mason.png", "orc_mason");
	AddSpriteToStorage("assets/unit/troll/troll_mason.png", "troll_mason");


	// Warriors and Fighters and Mages.
	AddSpriteToStorage("assets/unit/darkelf/darkelf_archer.png", "darkelf_archer");
	AddSpriteToStorage("assets/unit/dwarf/dwarf_archer.png", "dwarf_archer");
	AddSpriteToStorage("assets/unit/gnome/gnome_archer.png", "gnome_archer");
	AddSpriteToStorage("assets/unit/goblin/goblin_archer.png", "goblin_archer");
	AddSpriteToStorage("assets/unit/highelf/highelf_archer.png", "highelf_archer");
	AddSpriteToStorage("assets/unit/human/human_archer.png", "human_archer");
	AddSpriteToStorage("assets/unit/orc/orc_archer.png", "orc_archer");
	AddSpriteToStorage("assets/unit/troll/troll_archer.png", "troll_archer");

	AddSpriteToStorage("assets/unit/darkelf/darkelf_crossbowman_iron.png", "darkelf_crossbowman_iron");
	AddSpriteToStorage("assets/unit/dwarf/dwarf_crossbowman_iron.png", "dwarf_crossbowman_iron");
	AddSpriteToStorage("assets/unit/gnome/gnome_crossbowman_iron.png", "gnome_crossbowman_iron");
	AddSpriteToStorage("assets/unit/goblin/goblin_crossbowman_iron.png", "goblin_crossbowman_iron");
	AddSpriteToStorage("assets/unit/highelf/highelf_crossbowman_iron.png", "highelf_crossbowman_iron");
	AddSpriteToStorage("assets/unit/human/human_crossbowman_iron.png", "human_crossbowman_iron");
	AddSpriteToStorage("assets/unit/orc/orc_crossbowman_iron.png", "orc_crossbowman_iron");
	AddSpriteToStorage("assets/unit/troll/troll_crossbowman_iron.png", "troll_crossbowman_iron");

	AddSpriteToStorage("assets/unit/darkelf/darkelf_heavy_spearman_iron.png", "darkelf_heavy_spearman_iron");
	AddSpriteToStorage("assets/unit/dwarf/dwarf_heavy_spearman_iron.png", "dwarf_heavy_spearman_iron");
	AddSpriteToStorage("assets/unit/gnome/gnome_heavy_spearman_iron.png", "gnome_heavy_spearman_iron");
	AddSpriteToStorage("assets/unit/goblin/goblin_heavy_spearman_iron.png", "goblin_heavy_spearman_iron");
	AddSpriteToStorage("assets/unit/highelf/highelf_heavy_spearman_iron.png", "highelf_heavy_spearman_iron");
	AddSpriteToStorage("assets/unit/human/human_heavy_spearman_iron.png", "human_heavy_spearman_iron");
	AddSpriteToStorage("assets/unit/orc/orc_heavy_spearman_iron.png", "orc_heavy_spearman_iron");
	AddSpriteToStorage("assets/unit/troll/troll_heavy_spearman_iron.png", "troll_heavy_spearman_iron");

	AddSpriteToStorage("assets/unit/darkelf/darkelf_heavy_spearman_bronze.png", "darkelf_heavy_spearman_bronze");
	AddSpriteToStorage("assets/unit/dwarf/dwarf_heavy_spearman_bronze.png", "dwarf_heavy_spearman_bronze");
	AddSpriteToStorage("assets/unit/gnome/gnome_heavy_spearman_bronze.png", "gnome_heavy_spearman_bronze");
	AddSpriteToStorage("assets/unit/goblin/goblin_heavy_spearman_bronze.png", "goblin_heavy_spearman_bronze");
	AddSpriteToStorage("assets/unit/highelf/highelf_heavy_spearman_bronze.png", "highelf_heavy_spearman_bronze");
	AddSpriteToStorage("assets/unit/human/human_heavy_spearman_bronze.png", "human_heavy_spearman_bronze");
	AddSpriteToStorage("assets/unit/orc/orc_heavy_spearman_bronze.png", "orc_heavy_spearman_bronze");
	AddSpriteToStorage("assets/unit/troll/troll_heavy_spearman_bronze.png", "troll_heavy_spearman_bronze");

	AddSpriteToStorage("assets/unit/darkelf/darkelf_spearman_leather.png", "darkelf_spearman_leather");
	AddSpriteToStorage("assets/unit/dwarf/dwarf_spearman_leather.png", "dwarf_spearman_leather");
	AddSpriteToStorage("assets/unit/gnome/gnome_spearman_leather.png", "gnome_spearman_leather");
	AddSpriteToStorage("assets/unit/goblin/goblin_spearman_leather.png", "goblin_spearman_leather");
	AddSpriteToStorage("assets/unit/highelf/highelf_spearman_leather.png", "highelf_spearman_leather");
	AddSpriteToStorage("assets/unit/human/human_spearman_leather.png", "human_spearman_leather");
	AddSpriteToStorage("assets/unit/orc/orc_spearman_leather.png", "orc_spearman_leather");
	AddSpriteToStorage("assets/unit/troll/troll_spearman_leather.png", "troll_spearman_leather");

	AddSpriteToStorage("assets/unit/darkelf/darkelf_swordman_iron.png", "darkelf_swordman_iron");
	AddSpriteToStorage("assets/unit/dwarf/dwarf_swordman_iron.png", "dwarf_swordman_iron");
	AddSpriteToStorage("assets/unit/gnome/gnome_swordman_iron.png", "gnome_swordman_iron");
	AddSpriteToStorage("assets/unit/goblin/goblin_swordman_iron.png", "goblin_swordman_iron");
	AddSpriteToStorage("assets/unit/highelf/highelf_swordman_iron.png", "highelf_swordman_iron");
	AddSpriteToStorage("assets/unit/human/human_swordman_iron.png", "human_swordman_iron");
	AddSpriteToStorage("assets/unit/orc/orc_swordman_iron.png", "orc_swordman_iron");
	AddSpriteToStorage("assets/unit/troll/troll_swordman_iron.png", "troll_swordman_iron");

	AddSpriteToStorage("assets/unit/darkelf/darkelf_swordman_bronze.png", "darkelf_swordman_bronze");
	AddSpriteToStorage("assets/unit/dwarf/dwarf_swordman_bronze.png", "dwarf_swordman_bronze");
	AddSpriteToStorage("assets/unit/gnome/gnome_swordman_bronze.png", "gnome_swordman_bronze");
	AddSpriteToStorage("assets/unit/goblin/goblin_swordman_bronze.png", "goblin_swordman_bronze");
	AddSpriteToStorage("assets/unit/highelf/highelf_swordman_bronze.png", "highelf_swordman_bronze");
	AddSpriteToStorage("assets/unit/human/human_swordman_bronze.png", "human_swordman_bronze");
	AddSpriteToStorage("assets/unit/orc/orc_swordman_bronze.png", "orc_swordman_bronze");
	AddSpriteToStorage("assets/unit/troll/troll_swordman_bronze.png", "troll_swordman_bronze");


	AddSpriteToStorage("assets/unit/darkelf/human_paladin_adamantium.png", "human_paladin_adamantium");
	AddSpriteToStorage("assets/unit/dwarf/dwarf_paladin_adamantium.png", "dwarf_paladin_adamantium");
	AddSpriteToStorage("assets/unit/gnome/gnome_paladin_adamantium.png", "gnome_paladin_adamantium");
	AddSpriteToStorage("assets/unit/goblin/goblin_paladin_adamantium.png", "goblin_paladin_adamantium");
	AddSpriteToStorage("assets/unit/highelf/highelf_paladin_adamantium.png", "highelf_paladin_adamantium");
	AddSpriteToStorage("assets/unit/human/human_paladin_adamantium.png", "human_paladin_adamantium");
	AddSpriteToStorage("assets/unit/orc/orc_paladin_adamantium.png", "orc_paladin_adamantium");
	AddSpriteToStorage("assets/unit/troll/troll_paladin_adamantium.png", "troll_paladin_adamantium");


	AddSpriteToStorage("assets/unit/darkelf/human_paladin_malachite.png", "human_paladin_malachite");
	AddSpriteToStorage("assets/unit/dwarf/dwarf_paladin_malachite.png", "dwarf_paladin_malachite");
	AddSpriteToStorage("assets/unit/gnome/gnome_paladin_malachite.png", "gnome_paladin_malachite");
	AddSpriteToStorage("assets/unit/goblin/goblin_paladin_malachite.png", "goblin_paladin_malachite");
	AddSpriteToStorage("assets/unit/highelf/highelf_paladin_malachite.png", "highelf_paladin_malachite");
	AddSpriteToStorage("assets/unit/human/human_paladin_malachite.png", "human_paladin_malachite");
	AddSpriteToStorage("assets/unit/orc/orc_paladin_malachite.png", "orc_paladin_malachite");
	AddSpriteToStorage("assets/unit/troll/troll_paladin_malachite.png", "troll_paladin_malachite");

	AddSpriteToStorage("assets/unit/darkelf/darkelf_aristocrat.png", "darkelf_aristocrat");
	AddSpriteToStorage("assets/unit/dwarf/dwarf_aristocrat.png", "dwarf_aristocrat");
	AddSpriteToStorage("assets/unit/gnome/gnome_aristocrat.png", "gnome_aristocrat");
	AddSpriteToStorage("assets/unit/goblin/goblin_aristocrat.png", "goblin_aristocrat");
	AddSpriteToStorage("assets/unit/highelf/highelf_aristocrat.png", "highelf_aristocrat");
	AddSpriteToStorage("assets/unit/human/human_aristocrat.png", "human_aristocrat");
	AddSpriteToStorage("assets/unit/orc/orc_aristocrat.png", "orc_aristocrat");
	AddSpriteToStorage("assets/unit/troll/troll_aristocrat.png", "troll_aristocrat");


	AddSpriteToStorage("assets/unit/darkelf/darkelf_merchant.png", "darkelf_merchant");
	AddSpriteToStorage("assets/unit/dwarf/dwarf_merchant.png", "dwarf_merchant");
	AddSpriteToStorage("assets/unit/gnome/gnome_merchant.png", "gnome_merchant");
	AddSpriteToStorage("assets/unit/goblin/goblin_merchant.png", "goblin_merchant");
	AddSpriteToStorage("assets/unit/highelf/highelf_merchant.png", "highelf_merchant");
	AddSpriteToStorage("assets/unit/human/human_merchant.png", "human_merchant");
	AddSpriteToStorage("assets/unit/orc/orc_merchant.png", "orc_merchant");
	AddSpriteToStorage("assets/unit/troll/troll_merchant.png", "troll_merchant");


	AddSpriteToStorage("assets/unit/darkelf/darkelf_mage_researcher.png", "darkelf_mage_researcher");
	AddSpriteToStorage("assets/unit/dwarf/dwarf_mage_researcher.png", "dwarf_mage_researcher");
	AddSpriteToStorage("assets/unit/gnome/gnome_mage_researcher.png", "gnome_mage_researcher");
	AddSpriteToStorage("assets/unit/goblin/goblin_mage_researcher.png", "goblin_mage_researcher");
	AddSpriteToStorage("assets/unit/highelf/highelf_mage_researcher.png", "highelf_mage_researcher");
	AddSpriteToStorage("assets/unit/human/human_mage_researcher.png", "human_mage_researcher");
	AddSpriteToStorage("assets/unit/orc/orc_mage_researcher.png", "orc_mage_researcher");
	AddSpriteToStorage("assets/unit/troll/troll_mage_researcher.png", "troll_mage_researcher");


	AddSpriteToStorage("assets/unit/darkelf/darkelf_researcher.png", "darkelf_researcher");
	AddSpriteToStorage("assets/unit/dwarf/dwarf_researcher.png", "dwarf_researcher");
	AddSpriteToStorage("assets/unit/gnome/gnome_researcher.png", "gnome_researcher");
	AddSpriteToStorage("assets/unit/goblin/goblin_researcher.png", "goblin_researcher");
	AddSpriteToStorage("assets/unit/highelf/highelf_researcher.png", "highelf_researcher");
	AddSpriteToStorage("assets/unit/human/human_researcher.png", "human_researcher");
	AddSpriteToStorage("assets/unit/orc/orc_researcher.png", "orc_researcher");
	AddSpriteToStorage("assets/unit/troll/troll_researcher.png", "troll_researcher");



	AddSpriteToStorage("assets/unit/darkelf/darkelf_slinger.png", "darkelf_slinger");
	AddSpriteToStorage("assets/unit/dwarf/dwarf_slinger.png", "dwarf_slinger");
	AddSpriteToStorage("assets/unit/gnome/gnome_slinger.png", "gnome_slinger");
	AddSpriteToStorage("assets/unit/goblin/goblin_slinger.png", "goblin_slinger");
	AddSpriteToStorage("assets/unit/highelf/highelf_slinger.png", "highelf_slinger");
	AddSpriteToStorage("assets/unit/human/human_slinger.png", "human_slinger");
	AddSpriteToStorage("assets/unit/orc/orc_slinger.png", "orc_slinger");
	AddSpriteToStorage("assets/unit/troll/troll_slinger.png", "troll_slinger");


	AddSpriteToStorage("assets/unit/darkelf/darkelf_warrior_1.png", "darkelf_warrior_1");
	AddSpriteToStorage("assets/unit/dwarf/dwarf_warrior_1.png", "dwarf_warrior_1");
	AddSpriteToStorage("assets/unit/gnome/gnome_warrior_1.png", "gnome_warrior_1");
	AddSpriteToStorage("assets/unit/goblin/goblin_warrior_1.png", "goblin_warrior_1");
	AddSpriteToStorage("assets/unit/highelf/highelf_warrior_1.png", "highelf_warrior_1");
	AddSpriteToStorage("assets/unit/human/human_warrior_1.png", "human_warrior_1");
	AddSpriteToStorage("assets/unit/orc/orc_warrior_1.png", "orc_warrior_1");
	AddSpriteToStorage("assets/unit/troll/troll_warrior_1.png", "troll_warrior_1");


	AddSpriteToStorage("assets/unit/darkelf/darkelf_warrior_2.png", "darkelf_warrior_2");
	AddSpriteToStorage("assets/unit/dwarf/dwarf_warrior_2.png", "dwarf_warrior_2");
	AddSpriteToStorage("assets/unit/gnome/gnome_warrior_2.png", "gnome_warrior_2");
	AddSpriteToStorage("assets/unit/goblin/goblin_warrior_2.png", "goblin_warrior_2");
	AddSpriteToStorage("assets/unit/highelf/highelf_warrior_2.png", "highelf_warrior_2");
	AddSpriteToStorage("assets/unit/human/human_warrior_2.png", "human_warrior_2");
	AddSpriteToStorage("assets/unit/orc/orc_warrior_2.png", "orc_warrior_2");
	AddSpriteToStorage("assets/unit/troll/troll_warrior_2.png", "troll_warrior_2");
}


bool IMGUI::AddSprite(std::string path, std::string spritename) {

	using namespace olc;

	Sprite* s = new Sprite(path);
	if (s == nullptr) return false;

	IMGUI::Get()->m_IMGUISpriteResourceMap.insert(std::make_pair(spritename, s));
	
	Decal* d = new Decal(s);
	IMGUI::Get()->m_IMGUIDecalMap.insert(std::make_pair(spritename, d));
	
	return (d);
}


bool Game::AddSpriteToStorage(std::string path, std::string spritename) {

	using namespace olc;

	Sprite* s = new Sprite(path);
	if (!s) return false;

	m_SpriteStorage.push_back(s);


	Decal* d = new Decal(s);
	m_SpriteResourceMap.insert(std::make_pair(spritename, d));

	return (d);
}


void Game::_initializeMap() {

	m_WorldMap = WorldMap::Get();
	WorldMapDrawingOptions* mapOpt = new WorldMapDrawingOptions(19, 19);
	
	m_WorldMap->SetMapOptions(mapOpt);
}


void Game::_initialize() {

	_loadSpriteResources();
	_initializeMap();

	InitializeUnitTechnologyRequirements();
	InitializeBuildingTechnologyRequirements();
	InitializeBuildingRequirementsMap();
}


bool Game::OnUserCreate() {

	_initialize();
	_initializeMapTileCellCoords();

	m_TimeCounter = new TimeCounter();

	Camera* cam = new Camera(this, 0, 0);
	m_Renderer = new Renderer(this, cam);

	m_Renderer->m_Layer1 = CreateLayer();
	m_Renderer->m_Layer2 = CreateLayer();
	m_Renderer->m_Layer3 = CreateLayer();
	m_Renderer->m_Layer4 = CreateLayer();


	EntitiesStorage* storage = EntitiesStorage::Get();


	/*
	Mountains* m = new Mountains("highmountain", "layer2", 128, 128);
	
	Hills* h = new Hills("hills", "layer2", 256, 128);


	EntitiesStorage* storage = EntitiesStorage::Get();
	
	storage->AddGameEntitie(m);
	storage->AddGameEntitie(h);
	*/


	/*
	// Create some forests for testing.
	Forest* f, * f2, * f3;

	f = MakeNewForest("forest_temperate_deep", 3, 3);
	f2 = MakeNewForest("forest_temperate_deep", 4, 4);
	f3 = MakeNewForest("forest_temperate_deep", 5, 5);
	

	EntitiesStorage* storage = EntitiesStorage::Get();
	storage->AddGameEntitie(f);
	storage->AddGameEntitie(f2);
	storage->AddGameEntitie(f3);


	// Ressources are just a sprite on the map.
	MapRessource* r1 = new MapRessource("Bear", "ressource_map_bear", 384, 128);
	MapRessource* r2 = new MapRessource("Raptor", "ressource_map_raptor", 128, 384);
	MapRessource* r3 = new MapRessource("Horse", "ressource_map_horse", 128, 0);
	MapRessource* r4 = new MapRessource("Boar", "ressource_map_boar", 384, 128);
	MapRessource* r5 = new MapRessource("Guar", "ressource_map_guar", 512, 384);
	MapRessource* r6 = new MapRessource("Deer", "ressource_map_deer", 512, 128);



	r1->MapRessourceYield("Meat", 3);
	r1->MapRessourceYield("Hide", 5);
	r2->MapRessourceYield("Meat", 3);
	r2->MapRessourceYield("Hide", 5);
	r3->MapRessourceYield("Meat", 3);
	r3->MapRessourceYield("Hide", 5);


	storage->AddGameEntitie(r1);
	storage->AddGameEntitie(r2);
	storage->AddGameEntitie(r3);
	storage->AddGameEntitie(r4);
	storage->AddGameEntitie(r5);
	storage->AddGameEntitie(r6);
	*/	

	
	// NOTE:
	// We MUST have +1 players...
	Player* player = new Player("Bogdan", "blue", CMPEntityRace::Race::RACE_HUMAN);
	storage->AddPlayer(player);

	
	Player* player2 = new Player("Katharina", "magenta", CMPEntityRace::Race::RACE_ORC);
	storage->AddPlayer(player2);



	PlayerTurnCounter::Get()->AddPlayer(player);
	PlayerTurnCounter::Get()->AddPlayer(player2);


	
	// Cityname should be max 11. chars...
	City* city2 = MakeNewCity(true, "Stormgrad", CMPEntityRace::Race::RACE_HUMAN, player, 7, 6, 5);
	storage->AddGameEntitie(city2);

	city2->AddBuilding(new BuildingShack(city2), 1);
	city2->AddBuilding(new BuildingShack(city2), 2);
	city2->AddBuilding(new BuildingShack(city2), 3);
	city2->AddBuilding(new BuildingShrine(city2), 4);
	city2->AddBuilding(new BuildingShack(city2), 5);
	city2->AddBuilding(new BuildingShack(city2), 6);
	city2->AddBuilding(new BuildingInventorsHut(city2), 7);
	city2->AddBuilding(new BuildingShack(city2), 8);
	city2->AddBuilding(new BuildingShack(city2), 9);

	city2->AddBuilding(new BuildingChampionsHut(city2), 10);
	city2->AddBuilding(new BuildingChampionsHut(city2), 11);



	City* city3 = MakeNewCity(true, "Gral", CMPEntityRace::Race::RACE_ORC, player2, 16, 7, 5);
	storage->AddGameEntitie(city3);

	// TimeCounter
	m_TimeCounter->SetTimerForSeconds(1);
	m_TimeCounter->Start();



	// IMGUI Testing.
	IMGUI* gui = IMGUI::Get();
	
	// Testing sprite buttons.
	// First add ressources.
	gui->AddSprite("assets/button_menu.png", "button_menu");
	gui->AddSprite("assets/button_city_panel.png", "button_city_panel");
	gui->AddSprite("assets/button_political_map.png", "button_political_map");

	gui->AddSprite("assets/city_panel.png", "city_panel");

	gui->AddSprite("assets/unit/unit_player_color_red.png", "unit_player_color_red");
	gui->AddSprite("assets/unit/unit_player_color_blue.png", "unit_player_color_blue");
	gui->AddSprite("assets/unit/unit_player_color_magenta.png", "unit_player_color_magenta");
	gui->AddSprite("assets/unit/unit_player_color_green.png", "unit_player_color_green");
	gui->AddSprite("assets/unit/unit_player_color_black.png", "unit_player_color_black");
	gui->AddSprite("assets/unit/unit_player_color_brown.png", "unit_player_color_brown");
	gui->AddSprite("assets/unit/unit_player_color_orange.png", "unit_player_color_orange");
	gui->AddSprite("assets/unit/unit_player_color_yellow.png", "unit_player_color_yellow");

	

	// Add unit_class_ribons.
	gui->AddSprite("assets/unit/unit_class_archer.png", "unit_class_archer");
	gui->AddSprite("assets/unit/unit_class_assassin.png", "unit_class_assassin");
	gui->AddSprite("assets/unit/unit_class_barbarian.png", "unit_class_barbarian");
	gui->AddSprite("assets/unit/unit_class_battlemage.png", "unit_class_battlemage");
	gui->AddSprite("assets/unit/unit_class_healer.png", "unit_class_healer");
	gui->AddSprite("assets/unit/unit_class_inquisitor.png", "unit_class_inquisitor");
	gui->AddSprite("assets/unit/unit_class_knight.png", "unit_class_knight");
	gui->AddSprite("assets/unit/unit_class_mage.png", "unit_class_mage");
	gui->AddSprite("assets/unit/unit_class_nightblade.png", "unit_class_nightblade");
	gui->AddSprite("assets/unit/unit_class_paladin.png", "unit_class_paladin");
	gui->AddSprite("assets/unit/unit_class_rogue.png", "unit_class_rogue");
	gui->AddSprite("assets/unit/unit_class_scout.png", "unit_class_scout");
	gui->AddSprite("assets/unit/unit_class_sorcerer.png", "unit_class_sorcerer");
	gui->AddSprite("assets/unit/unit_class_spellsword.png", "unit_class_spellsword");
	gui->AddSprite("assets/unit/unit_class_spy.png", "unit_class_spy");
	gui->AddSprite("assets/unit/unit_class_warrior.png", "unit_class_warrior");




	// Astrology and birthsigns. YearCounter.
	YearCounter::Get(); // .. = construction.

	// Set first player as current turn player.
	PlayerTurnCounter::Get()->BeginGame();

	return true;
}

static int some_const_value = 0;

bool Game::OnUserUpdate(float fElapsedTime) {

	// IMGUI Testing.
	using namespace std;
	IMGUI::Get()->PrepareIMGUI();
	IMGUI::Get()->UpdateUISTate();
	IMGUI* gui = IMGUI::Get();


	if (m_TimeModeTurnBased == false) {
		
		if (m_TimeCounter->TimeOut()) {
			AdvanceOneTurn();
		}
	}


	// Update Entities MapCell
	_updateLocalMapTileCellCoords();

	// Input handling.
	m_Renderer->m_MainCam->m_CamInput->HandleKeyboard(m_Renderer->m_MainCam);
	m_Renderer->m_MainCam->m_CamInput->HandleMouse(m_Renderer->m_MainCam);


	m_Renderer->Render();

	// Consider move to Renderer.
	DrawSelectedUnitsMovementTiles();
	//if (m_SelectedUnitsMovementTiles->size() > 0) m_SelectedUnitsMovementTiles->clear(); // Resetting should be done after we deselect unit or movement was done...


	IMGUI::Get()->FinishIMGUI();

	return true;
}


static int m_IDHelper = 0;
void Renderer::DrawCityPanels() {
	
	City* city = nullptr;
	int id;


	// Testing: Fog of war.
	Player* curr_player = PlayerTurnCounter::Get()->m_CurrentTurnPlayer;


	for (auto it : *EntitiesStorage::Get()->GetCitiesVec()) {

		city = reinterpret_cast<City*>(it);


		// Do not draw tiles we do not see.
		if (city->m_TransformCmp->m_Cell[0] > VISIBLE_MAP_WIDTH ||
			city->m_TransformCmp->m_Cell[1] > VISIBLE_MAP_HEIGHT) continue;


		// Check whether maptile was explored...
		// We need to check this, as we draw ALL UNITS and not just players ones...
		// Here we check whether this maptile is IN fog of war, thus we dont draw units.
		if (curr_player->m_MapVisibility[city->m_TransformCmp->m_GameWorldSpaceCell[0]][city->m_TransformCmp->m_GameWorldSpaceCell[1]] == 0 ||
			curr_player->m_MapVisibility[city->m_TransformCmp->m_GameWorldSpaceCell[0]][city->m_TransformCmp->m_GameWorldSpaceCell[1]] == 1) continue;





		std::string cityname = city->m_CityName;
		std::string citysize = std::to_string(city->m_CitySize);


		// By creating gui widget in a loop make sure to define an ID that changes with every loop, or else
		// we will register input on all loop-widgets at the same time.
		IMGUI::Get()->ToolTipSpriteButton(++m_IDHelper + GEN_ID, city->m_TransformCmp->m_PosX - SPRITES_WIDTH_AND_HEIGHT / 2,
			city->m_TransformCmp->m_PosY + SPRITES_WIDTH_AND_HEIGHT - 16, "city_panel", city->GetCityLandscapeTypeString());
		

Game::Get()->DrawStringDecal(olc::vi2d(city->m_TransformCmp->m_PosX - 16, city->m_TransformCmp->m_PosY + SPRITES_WIDTH_AND_HEIGHT),
	cityname, olc::BLACK);


Game::Get()->DrawStringDecal(olc::vi2d(city->m_TransformCmp->m_PosX + SPRITES_WIDTH_AND_HEIGHT, city->m_TransformCmp->m_PosY + SPRITES_WIDTH_AND_HEIGHT),
	citysize, olc::BLACK);
	}

}


void Renderer::DrawCurrentTurnPlayerPanel() {

	using namespace olc;

	// The tooltip will show current birtsign.
	IMGUI::Get()->ToolTipSpriteButton(GEN_ID, 2, 64, "city_panel", "This Players Turn");

	// Draw current year...
	Game::Get()->DrawStringDecal(olc::vi2d(2 + 16, 64 + 16), PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_PlayerName, olc::BLACK);

	IMGUI::Get()->ToolTipSpriteButton(GEN_ID, 2 + 90, 64 + 8, GetColorFromString(PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_PlayerColor), "Player Color");
}


void Renderer::DrawYearQuartalPanel() {

	YearCounter* counter = YearCounter::Get();

	std::string year_quartal = "Y. " + std::to_string(counter->m_CurrentYear) + "	Q. " + std::to_string(counter->m_CurrentQuartal + 1);
	std::string tooltip = counter->GetCurrentBirthsign();

	// The tooltip will show current birtsign.
	IMGUI::Get()->ToolTipSpriteButton(GEN_ID, 764, 2, "city_panel", tooltip);

	// Draw current year...
	Game::Get()->DrawStringDecal(olc::vi2d(764 + 16, 16), year_quartal, olc::BLACK);
}



void Renderer::Render() {
	switch (m_RenderMode) {
	case RenderMode::RENDERMODE_CITYVIEW:

		// Layered rendering.
		RenderCityLayer1();  // 
		RenderCityLayer2();  // 
		RenderCityLayer3();  // 
		RenderCityLayer4();  // 
		RenderCityLayer0();  // 

		break;
	case RenderMode::RENDERMODE_MAPVIEW:

		// Layered rendering.
		Render2Layer1();  // units layer.
		Render2Layer2();  // buildings, cities...
		Render2Layer3();  // terrain, hills ...
		Render2Layer4();  // ground maptiles
		RenderLayer0();  // effects, general things...

		if (m_Game->m_DebugDraw) m_Game->DebugDrawStats();

		break;
	default:
		break;
	}
}


void Renderer::RenderCityLayer0() {

	using namespace olc;

	m_Game->Clear(olc::BLANK);


}


void Renderer::RenderCityLayer1() {

	using namespace olc;
	using namespace std;

	m_Game->SetDrawTarget(m_Layer1);
	m_Game->Clear(olc::BLANK);


	m_Game->FillRect(2, 690, 702, 50, olc::GREEN);

	// Draw name of hovered entity...
	GameEntity* entt = nullptr;
	Unit* unit = nullptr;
	Building* building = nullptr;
	entt = PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlyHoveredEntityInCity;

	if (entt) {

		if (COMPARE_STRINGS(entt->m_IDCmp->m_DynamicTypeName, "Unit") == 0) {

			unit = static_cast<Unit*>(entt);


			std::string out = "Unit: " + unit->m_Name + " Class: " + unit->m_UnitClass->m_UnitClassName + " Level: " + unit->m_UnitClass->LevelToString();
			m_Game->DrawString(4, 695, out, olc::RED);
		}
		else if (COMPARE_STRINGS(entt->m_IDCmp->m_DynamicTypeName, "Building") == 0){
		
			// NOTE:
			// a reinterpret_cast does not work here,
			// but a static_cast does perfectly as intended.
			building = static_cast<Building*>(entt);

			std::string out = "Building: " + building->m_BuildingName;
			m_Game->DrawString(4, 695, out, olc::RED);
		}
	}



	// Draw Units ovr buildings etc.
	for (auto it : m_CurrentViewedCity->m_PresentUnitsVector) {

		if (COMPARE_STRINGS(it->m_IDCmp->m_DynamicTypeName, "Unit") == 0) {


			// Draw unit at his position in city.
			m_Game->DrawDecal(vi2d(it->m_TransformCmp->m_PosX, it->m_TransformCmp->m_PosY),
				m_Game->m_SpriteResourceMap.at(it->m_GraphicsCmp->m_SpriteName));
		}
	}

	


	m_Game->EnableLayer(m_Layer1, true);
	m_Game->SetDrawTarget(nullptr);
}


void Renderer::RenderCityLayer2() {

	m_Game->SetDrawTarget(m_Layer2);
	m_Game->Clear(olc::BLANK);

	using namespace olc;

	City* city = nullptr;
	city = m_CurrentViewedCity;

	for (auto it : city->m_CityBuildingsSlots) {

		if (it->m_UsedByBuilding) {

			// Draw appropriate loaded sprite on position specified.
			m_Game->DrawDecal(vi2d(it->m_AssociatedBuilding->m_TransformCmp->m_PosX, it->m_AssociatedBuilding->m_TransformCmp->m_PosY),
				m_Game->m_SpriteResourceMap.at(it->m_AssociatedBuilding->m_GraphicsCmp->m_SpriteName));

		}
	}
	


	m_Game->EnableLayer(m_Layer2, true);
	m_Game->SetDrawTarget(nullptr);
}


void Renderer::RenderCityLayer3() {

	m_Game->SetDrawTarget(m_Layer3);
	m_Game->Clear(olc::BLANK);

	using namespace olc;

	GameEntity* entity = nullptr;
	MapTile* maptile = nullptr;
	GameEntity* maptile_entt = nullptr;
	MapTileRegion* region = nullptr;
	City* city = nullptr;

	// TODO:
	if (m_CurrentViewedCity == nullptr) return; // Verify for some weird bug where viewed city is nullptr.

	// 1)
	// Give the right panel center as city center:
	// Draw the city at this position.
	int cx = 992 - 32;
	int cy = 360 - 32;

	// 2)
	// Add the difference ( := offset  ) of center position and city mapview position 
	// to all to be drawn tiles etc.
	int offsetx = cx - m_CurrentViewedCity->m_TransformCmp->m_PosX;
	int offsety = cy - m_CurrentViewedCity->m_TransformCmp->m_PosY;


	// Render the city and surroundings.
	for (auto it = m_CurrentViewedCity->m_ClaimedRegions.begin(); it != m_CurrentViewedCity->m_ClaimedRegions.end(); ++it) {

		region = reinterpret_cast<MapTileRegion*>(*it);

		for (auto iter = region->m_MapTileRegionTiles.begin(); iter != region->m_MapTileRegionTiles.end(); ++iter) {

			entity = *iter;

			// Layer4. Maptiles.
			if (COMPARE_STRINGS(entity->m_IDCmp->m_DynamicTypeName, "MapTile") == 0) {

				// Render map tile.

				// Draw appropriate loaded sprite on position specified.
				m_Game->DrawDecal(vi2d(entity->m_TransformCmp->m_PosX + offsetx, entity->m_TransformCmp->m_PosY + offsety),
					m_Game->m_SpriteResourceMap.at(entity->m_GraphicsCmp->m_SpriteName));

			}

		}
	}



	for (auto it = m_CurrentViewedCity->m_ClaimedRegions.begin(); it != m_CurrentViewedCity->m_ClaimedRegions.end(); ++it) {

		region = reinterpret_cast<MapTileRegion*>(*it);

		for (auto iter = region->m_MapTileRegionTiles.begin(); iter != region->m_MapTileRegionTiles.end(); ++iter) {

			entity = *iter;
			// Layer 3. Hills, Forests, Mountains, Rivers.
			maptile = reinterpret_cast<MapTile*>(entity);
			for (auto itr = maptile->m_MapTileEntities->begin(); itr != maptile->m_MapTileEntities->end(); ++itr) {

				maptile_entt = *itr;

				if (COMPARE_STRINGS(maptile_entt->m_IDCmp->m_DynamicTypeName, "Mountains") == 0) {

					// Render...
					// Draw appropriate loaded sprite on position specified.
					m_Game->DrawDecal(vi2d(maptile_entt->m_TransformCmp->m_PosX + offsetx, maptile_entt->m_TransformCmp->m_PosY + offsety),
						m_Game->m_SpriteResourceMap.at(maptile_entt->m_GraphicsCmp->m_SpriteName));
				}
				if (COMPARE_STRINGS(maptile_entt->m_IDCmp->m_DynamicTypeName, "Hills") == 0) {

					// Render...
					// Draw appropriate loaded sprite on position specified.
					m_Game->DrawDecal(vi2d(maptile_entt->m_TransformCmp->m_PosX + offsetx, maptile_entt->m_TransformCmp->m_PosY + offsety),
						m_Game->m_SpriteResourceMap.at(maptile_entt->m_GraphicsCmp->m_SpriteName));
				}
				if (COMPARE_STRINGS(maptile_entt->m_IDCmp->m_DynamicTypeName, "Forest") == 0) {

					// Render...
					// Draw appropriate loaded sprite on position specified.
					m_Game->DrawDecal(vi2d(maptile_entt->m_TransformCmp->m_PosX + offsetx, maptile_entt->m_TransformCmp->m_PosY + offsety),
						m_Game->m_SpriteResourceMap.at(maptile_entt->m_GraphicsCmp->m_SpriteName));
				}
				if (COMPARE_STRINGS(maptile_entt->m_IDCmp->m_DynamicTypeName, "River") == 0) {

					// Render...
					// Draw appropriate loaded sprite on position specified.
					m_Game->DrawDecal(vi2d(maptile_entt->m_TransformCmp->m_PosX + offsetx, maptile_entt->m_TransformCmp->m_PosY + offsety),
						m_Game->m_SpriteResourceMap.at(maptile_entt->m_GraphicsCmp->m_SpriteName));
				}

			}

		}

	}


	for (auto it = m_CurrentViewedCity->m_ClaimedRegions.begin(); it != m_CurrentViewedCity->m_ClaimedRegions.end(); ++it) {

		region = reinterpret_cast<MapTileRegion*>(*it);

		for (auto iter = region->m_MapTileRegionTiles.begin(); iter != region->m_MapTileRegionTiles.end(); ++iter) {

			entity = *iter;
			// Layer2. Cities and Improvements.
			maptile = reinterpret_cast<MapTile*>(entity);
			for (auto itr = maptile->m_MapTileEntities->begin(); itr != maptile->m_MapTileEntities->end(); ++itr) {

				maptile_entt = *itr;

				if (COMPARE_STRINGS(maptile_entt->m_IDCmp->m_DynamicTypeName, "City") == 0) {

					city = reinterpret_cast<City*>(maptile_entt);

					// Render...
					m_Game->DrawDecal(vi2d(cx, cy),
						m_Game->m_SpriteResourceMap.at(city->GetCurrentCitySprite()));
				}

			}

		}

	}

	// Later render cities citizens and other units ...


	m_Game->EnableLayer(m_Layer3, true);
	m_Game->SetDrawTarget(nullptr);
}


void Renderer::_drawCityviewGroundBasedOnCityMaptileType(MapTile* maptile) {

	// NOTE:
	// This function is to be replaced to draw a single decal rect in needed position, and thus will be more efficient.

	using namespace olc;

	if (maptile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_TUNDRA) {

		// Define
		Pixel* tundra = new Pixel(60, 81, 72, 255);

		// Draw
		m_Game->FillRect(vi2d(2, 202), vi2d(700, 520), *tundra);

		// Release
		delete tundra;
	}
	else if (maptile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_SAVANNAH) {

		// Define
		Pixel* savannah = new Pixel(187, 161, 80, 255);

		// Draw
		m_Game->FillRect(vi2d(2, 202), vi2d(700, 520), *savannah);

		// Release
		delete savannah;
	}
	else if (maptile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_TEMPERATE) {


		// Define
		Pixel* temperate = new Pixel(107, 142, 78);

		// Draw
		m_Game->FillRect(vi2d(2, 202), vi2d(700, 520), *temperate);

		// Release
		delete temperate;
	}
	else if (maptile->m_MapTileType == MapTile::MapTileType::MAPTILE_TYPE_JUNGLE) {

		// Define
		Pixel* jungle = new Pixel(88, 66, 124, 255);

		// Draw
		m_Game->FillRect(vi2d(2, 202), vi2d(700, 520), *jungle);

		// Release
		delete jungle;
	}
	else {
		m_Game->FillRect(vi2d(2, 202), vi2d(700, 520), olc::RED);
	}
}


void Renderer::RenderCityLayer4() {

	using namespace olc;

	m_Game->SetDrawTarget(m_Layer4);
	m_Game->Clear(olc::BLANK);

	// VERSION 3.0.

	// 1. render panel of left upper side.
	m_Game->DrawDecal(vi2d(2, 2), m_Game->m_SpriteResourceMap.at("cityview_upper_panel"));

	// 2. Draw a color of underground based on the cities Maptile MapTileType...
	// TODO:
	// Make a special decal for this function, as I think, this draws down the FPS in cityview.
	_drawCityviewGroundBasedOnCityMaptileType(GetMapTileAtWorldPosition(m_CurrentViewedCity->m_TransformCmp->m_GameWorldSpaceCell[0], m_CurrentViewedCity->m_TransformCmp->m_GameWorldSpaceCell[1]));


	// 3. Draw cities background based on whether city has access to ocean
	// and based on race...
	std::string base = "city_background_";
	std::string race;
	std::string sprite;
	std::string water_access;
	std::string environment;
	std::string city_wall;

	switch (m_CurrentViewedCity->m_CoastalCity) {
	case true: // Water access..

		water_access = "with_water";
		break;
	case false: // No Water access..

		water_access = "no_water";
		break;
	}

	switch (m_CurrentViewedCity->m_CityRaceCmp->m_EntityRace) { // Based on race..
	case CMPEntityRace::Race::RACE_DARKELF:
		race = "darkelf_";

		break;
	case CMPEntityRace::Race::RACE_HIGHELF:
		race = "highelf_";

		break;
	case CMPEntityRace::Race::RACE_GNOME:
		race = "gnome_";

		break;
	case CMPEntityRace::Race::RACE_GOBLIN:
		race = "goblin_";

		break;
	case CMPEntityRace::Race::RACE_TROLL:
		race = "troll_";

		break;
	case CMPEntityRace::Race::RACE_DWARF:
		race = "dwarf_";

		break;
	case CMPEntityRace::Race::RACE_HUMAN:
		race = "human_";

		break;
	case CMPEntityRace::Race::RACE_ORC:
		race = "orc_";

		break;
	}

	// Get whaths in the background of the city...
	switch (*m_CurrentViewedCity->m_CityLandscapeType) {
	case City::CityLandscapeType::CITY_LANDSCAPE_FOREST:
		environment = "forest"; // For now we have only temperate forest.
		break;
	case City::CityLandscapeType::CITY_LANDSCAPE_HILLS:
		environment = "hills";
		break;
	case City::CityLandscapeType::CITY_LANDSCAPE_PLAIN:
		environment = "plains";
		break;
	}



	// 4. Draw things based on input from above...
	// 4.1. Draw environment background.
	std::string environment_background;
	bool env_flag = true;
	if (COMPARE_STRINGS(environment, "forest") == 0) {

		// Check for appropriate forest type...
		MapTile* tile = GetMapTileAtWorldPosition(m_CurrentViewedCity->m_TransformCmp->m_GameWorldSpaceCell[0], m_CurrentViewedCity->m_TransformCmp->m_GameWorldSpaceCell[1]);

		switch (tile->m_MapTileType) {
		case MapTile::MapTileType::MAPTILE_TYPE_JUNGLE:
			environment_background = base + "forest_jungle";
			break;
		case MapTile::MapTileType::MAPTILE_TYPE_SAVANNAH:
			environment_background = base + "forest_savannah";
			break;
		case MapTile::MapTileType::MAPTILE_TYPE_TUNDRA:
			environment_background = base + "forest_tundra";
			break;
		case MapTile::MapTileType::MAPTILE_TYPE_TEMPERATE:
			environment_background = base + "forest_temperate";
			break;
		default:
			// Give out some error message.
			return;
		}
	}
	else if (COMPARE_STRINGS(environment, "hills") == 0) {
		environment_background = base + "hills";
	}
	else {
		env_flag = false; // If city on plains, draw nothing...
	}

	if (env_flag) {
		m_Game->DrawDecal(vf2d(2, 2), m_Game->m_SpriteResourceMap.at(environment_background));
	}



	// 4.2. Draw river if present.
	std::string river_background;
	if (m_CurrentViewedCity->m_RiverPresentInCity) {

		river_background = base + "river_" + water_access;

		// Draw the river..
		m_Game->DrawDecal(vf2d(2, 2), m_Game->m_SpriteResourceMap.at(river_background));
	}




	// 4.3.  Draw cities background.
	std::string city_background = base + race + water_access; // e.g. "city_background_human_with_water"
	m_Game->DrawDecal(vf2d(2, 2), m_Game->m_SpriteResourceMap.at(city_background));



	// 4.4. Draw cities wall overlay..
	// For now we draw standard wooden wall for all cities...
	if (m_CurrentViewedCity->m_CoastalCity) {
		city_wall = base + "wooden_wall_with_water";
	}
	else {
		city_wall = base + "wooden_wall_no_water";

	}

	m_Game->DrawDecal(vf2d(2, 2), m_Game->m_SpriteResourceMap.at(city_wall));


	// 4.5. Lastly, draw right sidepanel of the city.
	m_Game->DrawDecal(vi2d(704, 2), m_Game->m_SpriteResourceMap.at("cityview_sidepanel"));




	/*
	//m_Game->FillRect(vi2d(2, 2), vi2d(700, 200), olc::DARK_CYAN);
	m_Game->DrawDecal(vi2d(2, 2), m_Game->m_SpriteResourceMap.at("cityview_upper_panel"));


	//m_Game->FillRect(vi2d(2, 202), vi2d(700, m_Game->ScreenHeight() - 6), olc::VERY_DARK_MAGENTA);
	// Here, draw a color of underground based on the cities Maptile MapTileType...
	_drawCityviewGroundBasedOnCityMaptileType(GetMapTileAtWorldPosition(m_CurrentViewedCity->m_TransformCmp->m_GameWorldSpaceCell[0], m_CurrentViewedCity->m_TransformCmp->m_GameWorldSpaceCell[1]));


	if (m_CurrentViewedCity->GetCityLandscapeType() == City::CityLandscapeType::CITY_LANDSCAPE_FOREST) {
		m_Game->DrawDecal(vf2d(2, 2), m_Game->m_SpriteResourceMap.at("background_city_forest_temperate"));
	}

	if (m_CurrentViewedCity->GetCityLandscapeType() == City::CityLandscapeType::CITY_LANDSCAPE_HILLS) {
		m_Game->DrawDecal(vf2d(2, 2), m_Game->m_SpriteResourceMap.at("background_city_hills"));
	}

	m_Game->DrawDecal(vf2d(2, 2), m_Game->m_SpriteResourceMap.at("background_city_orc_normal"));

	//m_Game->FillRect(vi2d(704, 2), vi2d(m_Game->ScreenWidth() - 700 - 6, m_Game->ScreenHeight() - 6), olc::VERY_DARK_GREEN);
	//m_Game->FillRect(vi2d(704, 2), vi2d(574, m_Game->ScreenHeight() - 6), olc::VERY_DARK_GREEN);
	m_Game->DrawDecal(vi2d(704, 2), m_Game->m_SpriteResourceMap.at("cityview_sidepanel"));
	*/


	/*
	// Version 2.0.
	m_Game->DrawDecal(vi2d(2, 2), m_Game->m_SpriteResourceMap.at("cityview_upper_panel"));


	// Here, draw a color of underground based on the cities Maptile MapTileType...
	// TODO:
	// Make a special decal for this function, as I think, this draws down the FPS in cityview.
	_drawCityviewGroundBasedOnCityMaptileType(GetMapTileAtWorldPosition(m_CurrentViewedCity->m_TransformCmp->m_GameWorldSpaceCell[0], m_CurrentViewedCity->m_TransformCmp->m_GameWorldSpaceCell[1]));


	// Draw a background based on the citylandscape, e.g. forest, hills, mountains ...
	// .. and based on its race, whether theres a river or watertile nearby etc.
	
	switch (m_CurrentViewedCity->m_CityRaceCmp->m_EntityRace) { // .. cities race..
		case CMPEntityRace::Race::RACE_HUMAN:

			// ... landscape ...
			if (m_CurrentViewedCity->GetCityLandscapeType() == City::CityLandscapeType::CITY_LANDSCAPE_FOREST) {
				m_Game->DrawDecal(vf2d(2, 2), m_Game->m_SpriteResourceMap.at("background_city_forest_temperate"));
			}
			else if (m_CurrentViewedCity->GetCityLandscapeType() == City::CityLandscapeType::CITY_LANDSCAPE_HILLS) {
				m_Game->DrawDecal(vf2d(2, 2), m_Game->m_SpriteResourceMap.at("background_city_hills"));
			}

			// ... river or not, mountain or not, hills or not ...
			if (m_CurrentViewedCity->m_RiverPresentInCity) {
				m_Game->DrawDecal(vf2d(2, 2), m_Game->m_SpriteResourceMap.at("background_city_human_river"));

			}

			else { // ... standard city without everything ...
				m_Game->DrawDecal(vf2d(2, 2), m_Game->m_SpriteResourceMap.at("background_city_human_normal"));

			}

			break;
		case CMPEntityRace::Race::RACE_ORC:

			// ... landscape ...
			if (m_CurrentViewedCity->GetCityLandscapeType() == City::CityLandscapeType::CITY_LANDSCAPE_FOREST) {
				m_Game->DrawDecal(vf2d(2, 2), m_Game->m_SpriteResourceMap.at("background_city_forest_temperate"));
			}
			else if (m_CurrentViewedCity->GetCityLandscapeType() == City::CityLandscapeType::CITY_LANDSCAPE_HILLS) {
				m_Game->DrawDecal(vf2d(2, 2), m_Game->m_SpriteResourceMap.at("background_city_hills"));
			}

			// ... river or not, mountain or not, hills or not ...
			if (m_CurrentViewedCity->m_RiverPresentInCity) {
				m_Game->DrawDecal(vf2d(2, 2), m_Game->m_SpriteResourceMap.at("background_city_orc_river"));

			}

			else { // ... standard city without everything ...
				m_Game->DrawDecal(vf2d(2, 2), m_Game->m_SpriteResourceMap.at("background_city_orc_normal"));

			}
			break;

		default:
			break;
	}




	m_Game->DrawDecal(vi2d(704, 2), m_Game->m_SpriteResourceMap.at("cityview_sidepanel"));
	*/

	m_Game->EnableLayer(m_Layer4, true);
	m_Game->SetDrawTarget(nullptr);
}



void Game::DebugDrawStats() {

	using namespace std;
	using namespace olc;


	if (!m_DebugDraw) return;

	if (!m_DebugDrawGeneralOptions) {

		/*
		std::string turncount = "Turn " + std::to_string(m_TurnCount);
		DrawString(olc::vi2d(2, 10), turncount, olc::BLACK, 1.0f);
		*/
		/*
		std::string political_map, political_map_on_off;
		political_map_on_off = (m_PoliticalMap == true) ? "On" : "Off";
		political_map = "Political Map ( M ): " + political_map_on_off;
		DrawString(olc::vi2d(2, 20), political_map, olc::BLACK, 1.0f);
		*/

	}


	if (m_DebugDrawUnitPositions) {

		std::string pos, cell;
		Unit* unit = nullptr;

		for (auto it = EntitiesStorage::Get()->GetUnitsVec()->begin(); it != EntitiesStorage::Get()->GetUnitsVec()->end(); ++it) {

			unit = reinterpret_cast<Unit*>(*it);

			pos = "(" + std::to_string(unit->m_TransformCmp->m_PosX) + ":" + std::to_string(unit->m_TransformCmp->m_PosY) + ")";
			cell = "(" + std::to_string(unit->m_TransformCmp->m_GameWorldSpaceCell[0]) + ":" + std::to_string(unit->m_TransformCmp->m_GameWorldSpaceCell[1]) + ")";


			DrawStringDecal(vi2d(unit->m_TransformCmp->m_PosX + 16, unit->m_TransformCmp->m_PosY + 16), pos, olc::BLACK);
			DrawStringDecal(vi2d(unit->m_TransformCmp->m_PosX + 16, unit->m_TransformCmp->m_PosY + 32), cell, olc::BLACK);
		}

	}



	if (m_DebugDrawGeneralOptions) {

		std::string s2 = "Camera Position " + std::to_string(g_vi2dCameraPosition.x) + " : " + std::to_string(g_vi2dCameraPosition.y);
		DrawString(olc::vi2d(2, 10), s2, olc::RED, 2.0f);

		std::string turncount = "Turn " + std::to_string(m_TurnCount);
		DrawString(olc::vi2d(2, 30), turncount, olc::RED, 2.0f);

		std::string on_off = (m_DebugDrawGrid == true) ? "On" : "Off";
		std::string debuggrid = "Grid (Ctrl + G): " + on_off;
		DrawString(olc::vi2d(2, 50), debuggrid, olc::RED, 2.0f);

		std::string maptile_info = (m_DebugDrawMapTileInfo == true) ? "On" : "Off";
		std::string maptile_info_2 = "Maptile Info (Ctrl + M): " + maptile_info;
		DrawString(olc::vi2d(2, 70), maptile_info_2, olc::RED, 2.0f);

		std::string forest_info = (m_DebugDrawForestInfo == true) ? "On" : "Off";
		std::string forest_info_2 = "Forest Info (Ctrl + F): " + forest_info;
		DrawString(olc::vi2d(2, 90), forest_info_2, olc::RED, 2.0f);

		/*
		std::string regions = (m_DebugDrawRegions == true) ? "On" : "Off";
		std::string regions_info = "Regions Info (Ctrl + R): " + regions;
		DrawString(olc::vi2d(2, 110), regions_info, olc::RED, 2.0f);
		*/

		std::string timemode = (m_TimeModeTurnBased == true) ? "Turn-Based" : "Real-Time";
		std::string timemode_info = "Timemode (Ctrl + T): " + timemode;
		DrawString(olc::vi2d(2, 110), timemode_info, olc::RED, 2.0f);
	}

	if (m_DebugDrawRegions) {

		MapTileRegion* region = nullptr;

		std::vector< GameEntity* > vec = *EntitiesStorage::Get()->GetMapTileRegions();
		m_DebugDrawRegionsCount =  std::to_string(vec.size());

		std::string regions_count = "Regions Count: " + m_DebugDrawRegionsCount;
		DrawString(olc::vi2d(2, 130), regions_count, olc::RED, 2.0f);

	}


	if (m_DebugDrawMapTileInfo) {

		// Draw each maptiles mapcell with position
		std::string s3, s4, tilepos, tilepos_2;
		for (auto it : *EntitiesStorage::Get()->GetMapTilesStorage()) {


			if (it->m_TransformCmp->m_Cell[0] > VISIBLE_MAP_WIDTH ||
				it->m_TransformCmp->m_Cell[1] > VISIBLE_MAP_HEIGHT) continue;


			// Camera dependent Cell 
			s3 = std::to_string(it->m_TransformCmp->m_Cell[0]) + " : " + std::to_string(it->m_TransformCmp->m_Cell[1]);
			DrawString(olc::vi2d(it->m_TransformCmp->m_PosX, it->m_TransformCmp->m_PosY), s3, olc::RED, 1.0f);

			// Gameworld Cell
			s4 = std::to_string(it->m_TransformCmp->m_GameWorldSpaceCell[0]) + " : " + std::to_string(it->m_TransformCmp->m_GameWorldSpaceCell[1]);
			DrawString(olc::vi2d(it->m_TransformCmp->m_PosX, it->m_TransformCmp->m_PosY + 10), s4, olc::DARK_RED, 1.0f);


			tilepos = "X: " + std::to_string(it->m_TransformCmp->m_PosX);
			DrawString(olc::vi2d(it->m_TransformCmp->m_PosX, it->m_TransformCmp->m_PosY + 20), tilepos, olc::BLACK, 1.0f);


			/*
			tiletype = MapTileTypeToString(reinterpret_cast<MapTile*>(it));
			DrawString(olc::vi2d(it->m_TransformCmp->m_PosX, it->m_TransformCmp->m_PosY + 30), tiletype, olc::RED, 1.0f);
			*/
			tilepos_2 = "Y: " + std::to_string(it->m_TransformCmp->m_PosY);
			DrawString(olc::vi2d(it->m_TransformCmp->m_PosX, it->m_TransformCmp->m_PosY + 30), tilepos_2, olc::BLACK, 1.0f);

		}

	}


	if (m_DebugDrawForestInfo) {

		std::string forestcount = "Forests " + std::to_string(GetTotalForestsCount());
		DrawString(olc::vi2d(2, 50), forestcount, olc::RED, 2.0f);

		// DrawForests and its Lifetime
		std::string s5, s6, s7, foresttype, cell, pos, forestclass, hasAI;
		std::vector< GameEntity* > vec = GetForestEntities();
		Forest* f = nullptr;
		for (auto it = vec.begin(); it != vec.end(); ++it) {

			f = reinterpret_cast<Forest*>(*it);

			switch (f->m_ForestType) {
			case Forest::ForestType::FOREST_NORMAL:
				foresttype = "NORMAL";
				break;
			case Forest::ForestType::FOREST_DYING:
				foresttype = "DYING";
				break;
			case Forest::ForestType::FOREST_SCARCE:
				foresttype = "SCARCE";
				break;
			case Forest::ForestType::FOREST_DEEP:
				foresttype = "DEEP";
				break;
			default:
				break;
			}


			switch (f->m_ForestClass) {
			case Forest::ForestClass::FOREST_CLASS_TUNDRA:
				forestclass = "CLASS_TUNDRA";
				break;
			case Forest::ForestClass::FOREST_CLASS_JUNGLE:
				forestclass = "CLASS_JUNGLE";
				break;
			case Forest::ForestClass::FOREST_CLASS_TEMPERATE:
				forestclass = "CLASS_TEMPERATE";
				break;
			case Forest::ForestClass::FOREST_CLASS_SAVANNAH:
				forestclass = "CLASS_SAVANNAH";
				break;
			default:
				forestclass = "CLASS_INVALID";
				break;
			}


			s5 = "LifeT.: " + std::to_string(f->m_ForestLifeTimeNow);
			s6 = " MaxLifeT.: " + std::to_string(f->m_ForestLifetime);
			s7 = " Type: " + foresttype;
			DrawString(olc::vi2d(f->m_TransformCmp->m_PosX, f->m_TransformCmp->m_PosY + 30), s5, olc::CYAN, 1);
			DrawString(olc::vi2d(f->m_TransformCmp->m_PosX, f->m_TransformCmp->m_PosY + 40), s6, olc::CYAN, 1);
			DrawString(olc::vi2d(f->m_TransformCmp->m_PosX, f->m_TransformCmp->m_PosY + 50), s7, olc::CYAN, 1);

			pos = "X: " + std::to_string(f->m_TransformCmp->m_PosX) + " Y: " + std::to_string(f->m_TransformCmp->m_PosY);
			cell = "(" + std::to_string(f->m_TransformCmp->m_GameWorldSpaceCell[0]) + " : " + std::to_string(f->m_TransformCmp->m_GameWorldSpaceCell[1]) + ")";
			DrawString(olc::vi2d(f->m_TransformCmp->m_PosX, f->m_TransformCmp->m_PosY + 60), cell, olc::CYAN, 1);
			DrawString(olc::vi2d(f->m_TransformCmp->m_PosX, f->m_TransformCmp->m_PosY + 70), pos, olc::CYAN, 1);

			DrawString(olc::vi2d(f->m_TransformCmp->m_PosX, f->m_TransformCmp->m_PosY + 80), forestclass, olc::CYAN, 1);


			hasAI = (f->m_AICmp == nullptr) ? "No AI" : "Has AI";
			DrawString(olc::vi2d(f->m_TransformCmp->m_PosX, f->m_TransformCmp->m_PosY + 90), hasAI, olc::CYAN, 1);
		}
	}

}


void Renderer::_drawGrid() {

	using namespace olc;

	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* > vec = *storage->GetMapTilesStorage();
	
	MapTile* maptile = nullptr;
	int startpos[2], endpos[2];

	for (auto it = vec.begin(); it != vec.end(); ++it) {

		maptile = reinterpret_cast<MapTile*>(*it);

		startpos[0] = maptile->m_TransformCmp->m_PosX;
		startpos[1] = maptile->m_TransformCmp->m_PosY;

		endpos[0] = maptile->m_TransformCmp->m_PosX;
		endpos[1] = MAP_SIZE * SPRITES_WIDTH_AND_HEIGHT;

		m_Game->DrawLine(vi2d(startpos[0], startpos[1]), vi2d(endpos[0], endpos[1]), olc::BLACK);



		startpos[0] = maptile->m_TransformCmp->m_PosX;
		startpos[1] = maptile->m_TransformCmp->m_PosY;

		endpos[0] = MAP_SIZE * SPRITES_WIDTH_AND_HEIGHT;
		endpos[1] = maptile->m_TransformCmp->m_PosY;

		m_Game->DrawLine(vi2d(startpos[0], startpos[1]), vi2d(endpos[0], endpos[1]), olc::BLACK);


	}
}



int main()
{
	Game demo;

	if (demo.Construct(1280, 720, 1, 1, false, true, false)) {
		demo.Start();
	}

	return 0;
}


void Renderer::Render2Layer1() {

	using namespace olc;

	m_Game->SetDrawTarget(m_Layer1);
	m_Game->Clear(olc::BLANK);

	std::vector<GameEntity*> vec = *EntitiesStorage::Get()->GetUnitsVec();

	Unit* unit = nullptr;


	// Testing: Fog of war.
	Player* curr_player = PlayerTurnCounter::Get()->m_CurrentTurnPlayer;


	for (auto it = vec.begin(); it != vec.end(); ++it) {

		unit = reinterpret_cast<Unit*>(*it);

		// Do not draw units that are in city.
		if(IsUnitInCityOrFort(unit)) continue;

		// Do not draw tiles we do not see.
		if (unit->m_TransformCmp->m_Cell[0] > VISIBLE_MAP_WIDTH ||
			unit->m_TransformCmp->m_Cell[1] > VISIBLE_MAP_HEIGHT) continue;


		// Check whether maptile was explored...
		// We need to check this, as we draw ALL UNITS and not just players ones...
		// Here we check whether this maptile is IN fog of war, thus we dont draw units.
		if (curr_player->m_MapVisibility[unit->m_TransformCmp->m_GameWorldSpaceCell[0]][unit->m_TransformCmp->m_GameWorldSpaceCell[1]] == 0 ||
			curr_player->m_MapVisibility[unit->m_TransformCmp->m_GameWorldSpaceCell[0]][unit->m_TransformCmp->m_GameWorldSpaceCell[1]] == 1) continue;



		// Draw unit.
		m_Game->DrawDecal(vf2d(unit->m_TransformCmp->m_PosX, unit->m_TransformCmp->m_PosY), 
						m_Game->m_SpriteResourceMap.at(unit->m_GraphicsCmp->m_SpriteName));
	}



	m_Game->EnableLayer(m_Layer1, true);
	m_Game->SetDrawTarget(nullptr);
}

void Renderer::Render2Layer2() {

	using namespace olc;

	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* > vec = *storage->GetMapViewRessources();

	m_Game->SetDrawTarget(m_Layer2);
	m_Game->Clear(olc::BLANK);

	GameEntity* entity = nullptr;



	// Testing: Fog of war.
	Player* curr_player = PlayerTurnCounter::Get()->m_CurrentTurnPlayer;



	// First, draw the mapviewressources.
	for (auto it = vec.begin(); it != vec.end(); ++it) {

		entity = reinterpret_cast<MapRessource*>(*it);

		// Do not draw tiles we do not see.
		if (entity->m_TransformCmp->m_Cell[0] > VISIBLE_MAP_WIDTH ||
			entity->m_TransformCmp->m_Cell[1] > VISIBLE_MAP_HEIGHT) continue;


		// Check whether maptile was explored...
		if (curr_player->m_MapVisibility[entity->m_TransformCmp->m_GameWorldSpaceCell[0]][entity->m_TransformCmp->m_GameWorldSpaceCell[1]] == 0) continue;



		// Draw appropriate loaded sprite on position specified.
		m_Game->DrawDecal(vi2d(entity->m_TransformCmp->m_PosX, entity->m_TransformCmp->m_PosY),
			m_Game->m_SpriteResourceMap.at(entity->m_GraphicsCmp->m_SpriteName));

	}


	// Then, we can draw improvements, roads, cities ...
	// For this, we iterate through a specially define vector and draw everything like above in
	// the correct local order...
	// ...

	//Secondly, draw cities.
	vec = *storage->GetCitiesVec();

	City* city = nullptr;
	MapTileRegion* region = nullptr;

	
	for (auto it = vec.begin(); it != vec.end(); ++it) {

		city = reinterpret_cast<City*>(*it);

		// Do not draw tiles we do not see.
		if (city->m_TransformCmp->m_Cell[0] > VISIBLE_MAP_WIDTH ||
			city->m_TransformCmp->m_Cell[1] > VISIBLE_MAP_HEIGHT) continue;


		// See whether maptile was explored. This is necessary, as we loop through ALL CITIES,
		// and not just the players ones.
		// Furthermore, check whether there are cities IN fog of war, if so, draw them. As we draw them as part of game definition...
		if (curr_player->m_MapVisibility[city->m_TransformCmp->m_GameWorldSpaceCell[0]][city->m_TransformCmp->m_GameWorldSpaceCell[1]] == 0) continue;



		// First, we draw political region tiles.
		// Draw political map related borders.
		if (m_Game->m_PoliticalMap) {

			// Test, draw region around city.
			for (auto it = city->m_ClaimedRegions.begin(); it != city->m_ClaimedRegions.end(); ++it) {

				region = *it;

				_drawMapTileRegionRect(region);
			}

		}
		

		// After that we draw city. Thus the city will be drawn over the regiontiles...
		// Draw appropriate loaded sprite on position specified.
		m_Game->DrawDecal(vi2d(city->m_TransformCmp->m_PosX, city->m_TransformCmp->m_PosY),
			m_Game->m_SpriteResourceMap.at(city->GetCurrentCitySprite()));
	}
	


	// Continue rendering political map related borders. Here, city borders.
	if (m_Game->m_PoliticalMap) {
			
		std::vector<GameEntity*> vec_2 = *EntitiesStorage::Get()->GetCitiesVec();
		City* c = nullptr;
		MapTile* tile = nullptr;

		for (auto it = vec_2.begin(); it != vec_2.end(); ++it) {

			c = reinterpret_cast<City*>(*it);

			for (auto iter = c->m_MapTileBorderDirectionMap.begin(); iter != c->m_MapTileBorderDirectionMap.end(); ++iter) {

				tile = iter->first;

				// Do not draw tiles we do not see.
				if (tile->m_TransformCmp->m_Cell[0] > VISIBLE_MAP_WIDTH ||
					tile->m_TransformCmp->m_Cell[1] > VISIBLE_MAP_HEIGHT) continue;


				// Visibility check....
				if (curr_player->m_MapVisibility[tile->m_TransformCmp->m_GameWorldSpaceCell[0]][tile->m_TransformCmp->m_GameWorldSpaceCell[1]] == 0) continue;


				// ... but, we dont want to draw city regions, if city is IN fog of war.
				if (curr_player->m_MapVisibility[tile->m_TransformCmp->m_GameWorldSpaceCell[0]][tile->m_TransformCmp->m_GameWorldSpaceCell[1]] > 1) {



					// Draw appropriate loaded sprite on position specified.
					m_Game->DrawDecal(vi2d(tile->m_TransformCmp->m_PosX, tile->m_TransformCmp->m_PosY),
						m_Game->m_SpriteResourceMap.at(c->m_MapTileBorderDirectionMap.at(tile)), vf2d(1.0f, 1.0f),
						m_Game->MakeOlcColorFromCityBorderColor(c->m_CityBorderColor));
				}
			}

		}

	}


	m_Game->EnableLayer(m_Layer2, true);
	m_Game->SetDrawTarget(nullptr);
}



olc::Pixel Game::MakeOlcColorFromCityBorderColor(City::CityBorderColor color) {

	switch (color) {
	case City::CityBorderColor::CITY_BORDERCOLOR_BLACK:
		return olc::Pixel(0, 0, 0, 255);
		break;
	case City::CityBorderColor::CITY_BORDERCOLOR_RED:
		return olc::Pixel(178, 0, 0, 255);
		break;
	case City::CityBorderColor::CITY_BORDERCOLOR_BLUE:
		return olc::Pixel(0, 17, 255, 255);
		break;
	case City::CityBorderColor::CITY_BORDERCOLOR_GREEN:
		return olc::Pixel(0, 102, 40, 255);

		break;
	case City::CityBorderColor::CITY_BORDERCOLOR_YELLOW:
		return olc::Pixel(252, 200, 12, 255);

		break;
	case City::CityBorderColor::CITY_BORDERCOLOR_MAGENTA:
		return olc::Pixel(65, 0, 178, 255);

		break;
	case City::CityBorderColor::CITY_BORDERCOLOR_ORANGE:
		return olc::Pixel(252, 84, 12, 255);

		break;
	case City::CityBorderColor::CITY_BORDERCOLOR_BROWN:
		return olc::Pixel(101, 67, 33, 255);
		break;
	default:
		return olc::Pixel(255, 255, 255, 255);
		break;
	}
}


void Renderer::_drawMapTileRegionRect(MapTileRegion* region) {

	using namespace olc;
	MapTile* maptile = nullptr;

	for (auto it = region->m_MapTileRegionTiles.begin(); it != region->m_MapTileRegionTiles.end(); ++it) {

		maptile = *it;

		// Do not draw tiles we do not see.
		if (maptile->m_TransformCmp->m_Cell[0] > VISIBLE_MAP_WIDTH ||
			maptile->m_TransformCmp->m_Cell[1] > VISIBLE_MAP_HEIGHT) continue;

		// Check whether the region has a spriteressource set.
		if (COMPARE_STRINGS(region->m_GraphicsCmp->m_SpriteName, "NULL") == 0) continue;

		else {
			// We want to draw the rectangles with specific to the city color.
			m_Game->DrawDecal(vi2d(maptile->m_TransformCmp->m_PosX, maptile->m_TransformCmp->m_PosY),
				m_Game->m_SpriteResourceMap.at(region->m_GraphicsCmp->m_SpriteName));
		}
	}
}


void Renderer::Render2Layer3() {

	using namespace olc;

	EntitiesStorage* storage = EntitiesStorage::Get();

	m_Game->SetDrawTarget(m_Layer3);
	m_Game->Clear(olc::BLANK);

	MapTile* maptile = nullptr;
	Forest* forest = nullptr;
	GameEntity* entity = nullptr;


	// Testing: Fog of war.
	Player* curr_player = PlayerTurnCounter::Get()->m_CurrentTurnPlayer;


	// Render Forests
	std::vector< GameEntity* > vec = *storage->GetMapTilesStorage();

	for (auto it = vec.begin(); it != vec.end(); ++it) {

		maptile = reinterpret_cast<MapTile*>(*it);

		// Do not draw tiles we do not see.
		if (maptile->m_TransformCmp->m_Cell[0] > VISIBLE_MAP_WIDTH ||
			maptile->m_TransformCmp->m_Cell[1] > VISIBLE_MAP_HEIGHT) continue;


		// We check whether this maptile was explored for current player. If not, dont draw.
		if (curr_player->m_MapVisibility[maptile->m_TransformCmp->m_GameWorldSpaceCell[0]][maptile->m_TransformCmp->m_GameWorldSpaceCell[1]] == 0) continue;



		if (maptile->m_MapTileEntities->size() > 0) {

			for (auto iter = maptile->m_MapTileEntities->begin(); iter != maptile->m_MapTileEntities->end(); ++iter) {

				entity = *iter;

				if (COMPARE_STRINGS(entity->m_IDCmp->m_DynamicTypeName, "Forest") == 0) {

					forest = reinterpret_cast<Forest*>(*iter);


					// Draw appropriate loaded sprite on position specified.
					m_Game->DrawDecal(vi2d(forest->m_TransformCmp->m_PosX, forest->m_TransformCmp->m_PosY),
						m_Game->m_SpriteResourceMap.at(forest->m_GraphicsCmp->m_SpriteName));
				}

			}

		}


	}

	// Render Mountains and Hills
	vec = *storage->GetHillsMountains();

	Hills* hills = nullptr;
	Mountains* mountains = nullptr;

	for (auto it = vec.begin(); it != vec.end(); ++it) {

		entity = *it;

		// Do not draw tiles we do not see.
		if (entity->m_TransformCmp->m_Cell[0] > VISIBLE_MAP_WIDTH ||
			entity->m_TransformCmp->m_Cell[1] > VISIBLE_MAP_HEIGHT) continue;


		// We check whether this maptile was explored for current player. If not, dont draw.
		if (curr_player->m_MapVisibility[entity->m_TransformCmp->m_GameWorldSpaceCell[0]][entity->m_TransformCmp->m_GameWorldSpaceCell[1]] == 0) continue;



		if (COMPARE_STRINGS(entity->m_IDCmp->m_DynamicTypeName, "Hills")) {
			hills = reinterpret_cast<Hills*>(*it);
			mountains = nullptr;
		}
		else if (COMPARE_STRINGS(entity->m_IDCmp->m_DynamicTypeName, "Mountains")) {
			mountains = reinterpret_cast<Mountains*>(*it);
			hills = nullptr;
		}


		if (hills) {
			// Draw appropriate loaded sprite on position specified.
			m_Game->DrawDecal(vi2d(hills->m_TransformCmp->m_PosX, hills->m_TransformCmp->m_PosY),
				m_Game->m_SpriteResourceMap.at(hills->m_GraphicsCmp->m_SpriteName));
		}
		else if (mountains) {
			// Draw appropriate loaded sprite on position specified.
			m_Game->DrawDecal(vi2d(mountains->m_TransformCmp->m_PosX, mountains->m_TransformCmp->m_PosY),
				m_Game->m_SpriteResourceMap.at(mountains->m_GraphicsCmp->m_SpriteName));
		}

	}



	
	// Render rivers over other to see them
	River* river = nullptr;
	vec = *storage->GetRiversVec();
	for (auto it = vec.begin(); it != vec.end(); ++it) {

		river = reinterpret_cast<River*>(*it);

		// Do not draw tiles we do not see.
		if (river->m_TransformCmp->m_Cell[0] > VISIBLE_MAP_WIDTH ||
			river->m_TransformCmp->m_Cell[1] > VISIBLE_MAP_HEIGHT) continue;



		// We check whether this maptile was explored for current player. If not, dont draw.
		if (curr_player->m_MapVisibility[river->m_TransformCmp->m_GameWorldSpaceCell[0]][river->m_TransformCmp->m_GameWorldSpaceCell[1]] == 0) continue;



		// Draw appropriate loaded sprite on position specified.
		m_Game->DrawDecal(vi2d(river->m_TransformCmp->m_PosX, river->m_TransformCmp->m_PosY),
			m_Game->m_SpriteResourceMap.at(river->m_GraphicsCmp->m_SpriteName));

	}



	m_Game->EnableLayer(m_Layer3, true);
	m_Game->SetDrawTarget(nullptr);
}

void Renderer::Render2Layer4() {

	using namespace olc;

	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* > vec = *storage->GetMapTilesStorage();
	MapTile* maptile = nullptr;

	m_Game->SetDrawTarget(m_Layer4);
	m_Game->Clear(olc::BLANK);

	// Testing: Fog of war.
	Player* curr_player = PlayerTurnCounter::Get()->m_CurrentTurnPlayer;



	for (auto it = vec.begin(); it != vec.end(); ++it) {

		maptile = reinterpret_cast<MapTile*>(*it);

		// Do not draw tiles we do not see.
		if (maptile->m_TransformCmp->m_Cell[0] > VISIBLE_MAP_WIDTH ||
			maptile->m_TransformCmp->m_Cell[1] > VISIBLE_MAP_HEIGHT) continue;

		// We check whether this maptile was explored for current player. If not, dont draw.
		if (curr_player->m_MapVisibility[maptile->m_TransformCmp->m_GameWorldSpaceCell[0]][maptile->m_TransformCmp->m_GameWorldSpaceCell[1]] == 0) continue;
		

		// Draw appropriate loaded sprite on position specified.
		m_Game->DrawDecal(vi2d(maptile->m_TransformCmp->m_PosX, maptile->m_TransformCmp->m_PosY),
			m_Game->m_SpriteResourceMap.at(maptile->m_GraphicsCmp->m_SpriteName));

	}



	m_Game->EnableLayer(m_Layer4, true);
	m_Game->SetDrawTarget(nullptr);
}



void Renderer::RenderLayer0() {

	using namespace olc;

	m_Game->Clear(olc::BLANK);


	// Draw FOG OF WAR.
	DrawFogOfWar();


	// Draw gui sidepanel. It is non-interactive.
	m_Game->DrawDecal(vf2d(m_Game->ScreenWidth() - 384, 0), m_Game->m_SpriteResourceMap.at("sidepanel"));

	IMGUI* gui = IMGUI::Get();

	if (gui->SpriteButton(GEN_ID, 2, 2, "city_panel")) {

		if (gui->TextButton(GEN_ID, 20, 40, "End Turn")) {
			m_Game->m_AdvanceOneTurn = true;
			m_Game->AdvanceOneTurn();
		}
	}

	if (gui->SpriteButton(GEN_ID, m_Game->ScreenWidth() - 64 - 32, 20, "button_menu")) {

		if (gui->SpriteButton(GEN_ID, m_Game->ScreenWidth() - 64 - 32, 60, "button_city_panel")) {
			Game::Get()->m_ShowCityPanel = (Game::Get()->m_ShowCityPanel == true) ? false : true;

		}


		if (gui->SpriteButton(GEN_ID, m_Game->ScreenWidth() - 64 - 32, 100, "button_political_map")) {
			Game::Get()->m_PoliticalMap = (Game::Get()->m_PoliticalMap == true) ? false : true;

		}

	}


	std::string turn;
	turn = "Turn " + std::to_string(m_Game->m_TurnCount);
	m_Game->DrawStringDecal(olc::vf2d(16, 16), turn, olc::BLACK);


	DrawYearQuartalPanel();

	// Interactive citypanels.
	// They show stats of city and give short info
	if (Game::Get()->m_ShowCityPanel) {
		DrawCityPanels();
	}




	// Show unit panels and general unit information.
	//DrawUnitPanels();



	// Show whos turn it is.
	DrawCurrentTurnPlayerPanel();


	if (m_Game->m_DrawUnitStats) {

		DrawUnitStats(PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlySelectedUnit);
	}


	if (m_Game->m_DebugDrawPlayersTech) {
		DrawPlayersTechnologies();
	}


	if (m_Game->m_DebugDrawPlayersBuildings) {
		DrawPlayersBuildingsForCities();
	}
}




void Renderer::DrawPlayersBuildingsForCities() {

	Player* p = PlayerTurnCounter::Get()->m_CurrentTurnPlayer;

	using namespace std;


	for (auto it : p->m_PlayerCities) {

		cout << color(colors::CYAN);
		cout << "City: " << it->m_CityName << endl;


		cout << " Buildings: " << white << endl;
		for (auto itr : it->m_CityBuildingsSlots) {

			if (itr->m_UsedByBuilding) {

				cout << color(colors::BLUE);
				cout << itr->m_SlotNumber << ".) Slot with \"" << itr->m_AssociatedBuilding->m_BuildingName<< "\"."<< white << endl;
				cout << color(colors::DARKGREEN);
				cout << "Position (" << itr->m_AssociatedBuilding->m_TransformCmp->m_PosX <<":" << itr->m_AssociatedBuilding->m_TransformCmp->m_PosY <<")" << white << endl;
			}
			else {

				cout << color(colors::BLUE);
				cout << itr->m_SlotNumber << ".) Slot without building." << white << endl;
				cout << color(colors::DARKGREEN);
				cout << "Position (" << itr->m_XPos << ":" << itr->m_YPos << ")" << white << endl;
			}
		}

		cout << endl;
		cout << endl;
	}

}





void Renderer::DrawPlayersTechnologies() {

	// Plus draw buildings that can be build with according tech.
	// TODO: draw units that can be build with according tech.

	using namespace std;

	std::vector<std::string> *vec;

	Player* p = PlayerTurnCounter::Get()->m_CurrentTurnPlayer;
	int counter = 1;

	for (auto it : p->m_PlayersTechnologies) {

		if (it.second == 1) {
			cout << color(colors::DARKGREEN);
			cout << counter << ".) Technology \"" << it.first << "\" was researched." << white << endl;

			// print buildings defined for tech
			cout << color(colors::YELLOW);
			cout << "Available Buildings for \"" << it.first << "\":" << endl;
			vec = GetAvailableBuildingsForTechnology(it.first);
			for (auto itr : *vec) {

				cout << color(colors::DARKCYAN);
				cout << "\"" <<  itr << "\"" << white << endl;
			}
		}
		else {
			cout << color(colors::DARKRED);
			cout << counter << ".) Technology \"" << it.first << "\" was not researched." << white << endl;
		
			// print buildings defined for tech
			cout << color(colors::YELLOW);
			cout << "Available Buildings for \"" << it.first << "\":" << endl;
			vec = GetAvailableBuildingsForTechnology(it.first);
			for (auto itr : *vec) {

				cout << color(colors::DARKCYAN);
				cout << "\"" << itr << "\"" << white << endl;
			}
		}

		counter++;
		cout << endl;

	}
	cout << endl;
	cout << endl;
}


void Renderer::DrawUnitStats(Unit* unit) {
	/*
	IMGUI* gui = IMGUI::Get();

	std::map<UnitAttributesEnum, int> attr_vec = *unit->GetUnitAttributes();
	std::map<UnitSkillsEnum, int> skills_vec = *unit->GetUnitSkills();

	// Attributes.
	int xpos, ypos;
	xpos = 300;
	ypos = 0;
	for (auto it : attr_vec) {

		// Draw attribute.
		gui->TextButton(++m_IDHelper + GEN_ID + Random(), xpos, ypos, AttributeToString(it.first));

		// Draw its value.
		gui->TextButton(++m_IDHelper + GEN_ID + Random(), xpos + AttributeToString(it.first).size()*9, ypos, std::to_string(it.second));

		ypos += 12;
	}


	// Skills.
	xpos = 450;
	ypos = 0;
	for (auto it : skills_vec) {

		// Draw skills.
		gui->TextButton(++m_IDHelper + GEN_ID + Random(), xpos, ypos, SkillToString(it.first));

		// Draw its value.
		gui->TextButton(++m_IDHelper + GEN_ID + Random(), xpos + SkillToString(it.first).size() * 9, ypos, std::to_string(it.second));

		ypos += 12;
	}


	// Draw general unit information.
	xpos = 200;
	ypos = 0;

	// Race.
	gui->TextButton(++m_IDHelper + GEN_ID + Random(), xpos, ypos, unit->m_EntityRaceCmp->m_EntityRaceString);
	ypos += 12;

	// Name.
	gui->TextButton(++m_IDHelper + GEN_ID + Random(), xpos, ypos, unit->m_Name);
	ypos += 12;

	// Class.
	gui->TextButton(++m_IDHelper + GEN_ID + Random(), xpos, ypos, unit->m_UnitClass->m_UnitClassName);
	ypos += 12;

	// Age.
	gui->TextButton(++m_IDHelper + GEN_ID + Random(), xpos, ypos, std::to_string(unit->m_Age));
	ypos += 12;

	*/
}



void Renderer::DrawFogOfWar() {
	
	using namespace olc;



	Player* curr_player = PlayerTurnCounter::Get()->m_CurrentTurnPlayer;


	// For testing, we get maptiles for which to draw fog of war.
	MapTile* maptile = nullptr;

	for (int i = 0; i < MAP_SIZE; ++i) {


		for (int j = 0; j < MAP_SIZE; ++j) {


			// Is this cell in fog if war?
			if (curr_player->m_MapVisibility[i][j] == 1) {

				// If yes, draw fog of war over it.

				maptile = GetMapTileAtWorldPosition(i, j);

				if (maptile) {


					// Draw appropriate loaded sprite on position specified.
					m_Game->DrawDecal(vi2d(maptile->m_TransformCmp->m_PosX, maptile->m_TransformCmp->m_PosY),
						m_Game->m_SpriteResourceMap.at("map_cell_fog_of_war"));
				}
			}
		}
	}


}


/*
void Renderer::DrawUnitPanels() {

	using namespace olc;

	std::vector<GameEntity*> vec = *EntitiesStorage::Get()->GetUnitsVec();

	Unit* unit = nullptr;
	IMGUI* gui = IMGUI::Get();

	// Flag for drawing additional panels.
	static bool age_panel = false;
	static bool movement_points_panel = false;


	Player* curr_player = PlayerTurnCounter::Get()->m_CurrentTurnPlayer;


	for (auto it = vec.begin(); it != vec.end(); ++it) {

		unit = reinterpret_cast<Unit*>(*it);



		// Do not draw tiles we do not see.
		if (unit->m_TransformCmp->m_Cell[0] > VISIBLE_MAP_WIDTH ||
			unit->m_TransformCmp->m_Cell[1] > VISIBLE_MAP_HEIGHT ||
			IsUnitInCityOrFort(unit)) continue;


		// Check whether maptile was explored...
		// We need to check this, as we draw ALL UNITS and not just players ones...
		// Here we check whether this maptile is IN fog of war, thus we dont draw units.
		if (curr_player->m_MapVisibility[unit->m_TransformCmp->m_GameWorldSpaceCell[0]][unit->m_TransformCmp->m_GameWorldSpaceCell[1]] == 0 ||
			curr_player->m_MapVisibility[unit->m_TransformCmp->m_GameWorldSpaceCell[0]][unit->m_TransformCmp->m_GameWorldSpaceCell[1]] == 1) continue;



		// Player unit color.
		std::string player_string = "Belongs to " + unit->m_AssociatedPlayer->m_PlayerName;
		if (gui->ToolTipSpriteButton(Random() + GEN_ID, unit->m_TransformCmp->m_PosX, unit->m_TransformCmp->m_PosY, unit->m_UnitPlayerColor, player_string, olc::WHITE)) {

			age_panel = (age_panel == true) ? false : true;
			movement_points_panel = (movement_points_panel == true) ? false : true;
		}

		// Unit ribbon.
		std::string unit_ribbon = unit->m_UnitClass->m_UnitClassName;
		if (gui->ToolTipSpriteButton(Random() + GEN_ID, unit->m_TransformCmp->m_PosX + 64 - 16, unit->m_TransformCmp->m_PosY, unit->m_UnitClass->m_UnitClassSpritename, unit_ribbon, olc::WHITE));
	

		

		// Drawing additional panels.
		if (age_panel) {

			std::string age = "Age: " + std::to_string(unit->m_Age) + " MaxAge: " + std::to_string(unit->m_MaxAge);
			gui->TextButton(++m_IDHelper + GEN_ID, unit->m_TransformCmp->m_PosX + 16, unit->m_TransformCmp->m_PosY + 64, age);
		}
		if (movement_points_panel) {

			std::string points = "Movement Points: " + std::to_string(unit->GetMovementPoints());
			gui->TextButton(++m_IDHelper + GEN_ID, unit->m_TransformCmp->m_PosX + 16, unit->m_TransformCmp->m_PosY + 64 + 16, points);
		}
		
	}
}
*/


void Game::_updateForestAI2() {

	using namespace std;

	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector<GameEntity*> vec = *storage->GetForestsVec();
	GameEntity* entity = nullptr;
	

	//cout << color(colors::BLUE) << endl << endl;
	//cout << "Executing _updateForestAI2()." << white << endl;

	for (auto it = vec.begin(); it != vec.end(); ++it) {
		try {

			entity = *it;
			
			//cout << APP_COLOR;
			//cout << "Executing state logic for " << entity->m_IDCmp->m_DynamicTypeName << " at position "
			//	<< entity->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << entity->m_TransformCmp->m_GameWorldSpaceCell[1] << white << endl;

			if (!entity->m_AICmp->TryExecuteStateLogic()) {

				//		cout << APP_ERROR_COLOR
				//	 << " was unsuccessfull." << white << endl << endl;

			}
			else {

				//cout << APP_SUCCESS_COLOR
				//	 << " was successfull." << white << endl << endl;
			}
		}
		catch (char* err) {
			continue;
		}

	}
}




void Game::_initializeMapTileCellCoords() {

	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* >* vec = storage->GetMapTilesStorage();

	for (auto& it : *vec) { // Iterate through all entities.

		it->m_TransformCmp->m_GameWorldSpaceCell[0] = (int)it->m_TransformCmp->m_PosX / SPRITES_WIDTH_AND_HEIGHT;
		it->m_TransformCmp->m_GameWorldSpaceCell[1] = (int)it->m_TransformCmp->m_PosY / SPRITES_WIDTH_AND_HEIGHT;

	}
}



void Game::_updateEntitiesMapTileCoords() {

	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* >* vec = storage->GetMapTilesStorage();

	for (auto it : *vec) {

		if (reinterpret_cast<MapTile*>(it)->m_MapTileEntities->size() > 0) {


			for (auto iter : *reinterpret_cast<MapTile*>(it)->m_MapTileEntities) {


				iter->m_TransformCmp->m_GameWorldSpaceCell[0] = it->m_TransformCmp->m_GameWorldSpaceCell[0];
				iter->m_TransformCmp->m_GameWorldSpaceCell[1] = it->m_TransformCmp->m_GameWorldSpaceCell[1];
			}
		}
	}

}



void Game::_updateLocalMapTileCellCoords() {

	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* > vec = *storage->GetMapTilesStorage();

	MapTile* maptile = nullptr;
	GameEntity* entity = nullptr;

	for (auto it = vec.begin(); it != vec.end(); ++it) {

		maptile = reinterpret_cast<MapTile*>(*it);

		
		maptile->m_TransformCmp->m_Cell[0] = ((int)maptile->m_TransformCmp->m_PosX  + 50) / SPRITES_WIDTH_AND_HEIGHT;
		maptile->m_TransformCmp->m_Cell[1] = ((int)maptile->m_TransformCmp->m_PosY + 50) / SPRITES_WIDTH_AND_HEIGHT;

		
		// Update local map coords for entities...
		if (maptile->m_MapTileEntities->size() > 0) {

			for (auto iter = maptile->m_MapTileEntities->begin(); iter != maptile->m_MapTileEntities->end(); ++iter ) {

				entity = *iter;

				entity->m_TransformCmp->m_Cell[0] = maptile->m_TransformCmp->m_Cell[0];
				entity->m_TransformCmp->m_Cell[1] = maptile->m_TransformCmp->m_Cell[1];
			}
		}
		
	}
}




void ForestSearch::executeStateLogic() {

	using namespace std;

	// increase lifetime on update. Counted in gameturns.
	// .. but only if no city occupies this forest.
	if (m_ManagedForest->IsCityOnForest() == false) {
		m_ManagedForest->m_ForestLifeTimeNow++;
	}

	// Forest too old, means dies of old age.
	if (m_ManagedForest->m_ForestLifeTimeNow > m_ManagedForest->m_ForestLifetime) {

		m_ManagedForest->m_ForestType = Forest::ForestType::FOREST_INVALID;

		m_ManagedForest->Update();
		return;
	}




	// check for transitions of young and older forests
	if (m_ManagedForest->m_ForestType == Forest::ForestType::FOREST_SCARCE) {


		if (m_ManagedForest->m_ForestLifeTimeNow > 32 * TURN_TIME_MODIFIER) { // scarce --> normal
			
			m_ManagedForest->m_ForestType = Forest::ForestType::FOREST_NORMAL;

			// Update on change.
			m_ManagedForest->Update();
		}
	}
	else {
		if (m_ManagedForest->m_ForestType == Forest::ForestType::FOREST_NORMAL && m_ManagedForest->m_ForestLifeTimeNow > 66 * TURN_TIME_MODIFIER || // normal --> dying
			m_ManagedForest->m_ForestType == Forest::ForestType::FOREST_DEEP && m_ManagedForest->m_ForestLifeTimeNow > 66*2 * TURN_TIME_MODIFIER) { // deep --> dying. This transition takes 2 times longer to fullfill, so the deep forest lives longer.


			if (m_ManagedForest->m_ForestType == Forest::ForestType::FOREST_DEEP) m_ManagedForest->m_ForestLifeTimeNow = 67; // Needed reset to normal value for deep forest to ensure common dying time.
			m_ManagedForest->m_ForestLifetime = 100 * TURN_TIME_MODIFIER;

			m_ManagedForest->m_ForestType = Forest::ForestType::FOREST_DYING;

			// Update on change.
			m_ManagedForest->Update();
		}
	}


	// Make changes dependent on forests position.
	// This logic acts only on normaltype forests.
	if (m_ManagedForest->m_ForestType == Forest::ForestType::FOREST_NORMAL) {

		//cout << color(colors::BLUE);
		//cout << "_checkForNewForestCreation() for " << m_ManagedForest->m_IDCmp->m_ID << " executing." << white << endl;
		_checkForNewForestCreation(m_ManagedForest);


		bool surrounded = false;
		surrounded = _surroundedByForestNormalOrDeep(m_ManagedForest);

		if (surrounded) {
			m_ManagedForest->m_ForestType = Forest::ForestType::FOREST_DEEP;
			m_ManagedForest->m_ForestLifetime = 200 * TURN_TIME_MODIFIER;

			//cout << color(colors::WHITE);
			//cout << "_surroundedByForestNormalOrDeep() successfully executed for " << m_ManagedForest->m_IDCmp->m_ID << " at position " << m_ManagedForest->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << m_ManagedForest->m_TransformCmp->m_GameWorldSpaceCell[1] << white << endl;
		}
		else {
			//cout << color(colors::WHITE);
			//cout << "_surroundedByForestNormalOrDeep() unsuccessfully executed for " << m_ManagedForest->m_IDCmp->m_ID << " at position " << m_ManagedForest->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << m_ManagedForest->m_TransformCmp->m_GameWorldSpaceCell[1] << white << endl;
		

			// Check whether to raise Randomly a deepforest.
			if( RaiseDeepForestRandomly()) {
				m_ManagedForest->m_ForestType = Forest::ForestType::FOREST_DEEP;
				m_ManagedForest->m_ForestLifetime = 200 * TURN_TIME_MODIFIER;

				//cout << color(colors::MAGENTA);
				//	cout << "Randomly raised DeepForest " << m_ManagedForest->m_IDCmp->m_ID << " at position " << m_ManagedForest->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << m_ManagedForest->m_TransformCmp->m_GameWorldSpaceCell[1] << white << endl;

			}

		}
	}


	// Spawning Random forest around deep forest logic.
	if (m_ManagedForest->m_ForestType == Forest::ForestType::FOREST_DEEP) {

		//cout << color(colors::BLUE);
		//cout << "_spawnRandomForestAroundDeepOne() for " << m_ManagedForest->m_IDCmp->m_ID << " executed." << white << endl;
		_spawnRandomForestAroundDeepOne(m_ManagedForest);
	}


	// Update on change.
	m_ManagedForest->Update();
}


void Game::AdvanceOneTurn() {

	using namespace std;

	// Let every player make theyre turn,
	// after it advance one turn for all.

	// Save current player before advancing one turn for execution of AI.
	Player* curr_player = PlayerTurnCounter::Get()->m_CurrentTurnPlayer;


	if (!PlayerTurnCounter::Get()->NextPlayerTurn()) {

		// Execute AI logic for units, cities tec. at the end of this players turn.
		std::vector<Unit*> units_vec = curr_player->m_PlayerUnits;



		for (auto it : units_vec) {

			it->m_AICmp->TryExecuteStateLogic();
		}


		return;
	}


	if (m_AdvanceOneTurn) {

		// For each player, try unlock one of the base techs after everyone has done theyre turns.
		for (auto it : PlayerTurnCounter::Get()->m_InGamePlayers) {

			it->RandomlyResearchBaseTechnology();
		}


		_updateForestAI2();

		m_TurnCount++;

		m_AdvanceOneTurn = false;

		YearCounter::Get()->AdvanceOneTurn();


		Unit* unit = nullptr;
		for (auto it : *EntitiesStorage::Get()->GetUnitsVec()) {

			unit = reinterpret_cast<Unit*>(it);

			// Prepare for next turn.
			unit->Update();
		}
	}
}



// This function can and must be improved.
bool ForestSearch::_surroundedByForestNormalOrDeep(Forest* forest) {

	int forest_cell[2];
	forest_cell[0] = forest->m_TransformCmp->m_GameWorldSpaceCell[0];
	forest_cell[1] = forest->m_TransformCmp->m_GameWorldSpaceCell[1];

	bool got_forest_up = false, got_forest_down = false, got_forest_left = false, got_forest_right = false;


	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* > vec = *storage->GetForestsVec();


	Forest* other_forest = nullptr;

 	for (auto it = vec.begin(); it != vec.end(); ++it) {

		if (forest == *it) continue;

		other_forest = reinterpret_cast<Forest*>(*it);


		if (other_forest->m_TransformCmp->m_GameWorldSpaceCell[0] == forest_cell[0] &&
			other_forest->m_TransformCmp->m_GameWorldSpaceCell[1] == forest_cell[1] - 1) { // one tile above our forest.

			if (IsSubstringInString("normal", other_forest->m_GraphicsCmp->m_SpriteName) ||
				IsSubstringInString("deep", other_forest->m_GraphicsCmp->m_SpriteName)) {

				got_forest_up = true;
			}
		}


		if (other_forest->m_TransformCmp->m_GameWorldSpaceCell[0] == forest_cell[0] - 1 &&
			other_forest->m_TransformCmp->m_GameWorldSpaceCell[1] == forest_cell[1]) { // one tile left to our forest.

			if (IsSubstringInString("normal", other_forest->m_GraphicsCmp->m_SpriteName) ||
				IsSubstringInString("deep", other_forest->m_GraphicsCmp->m_SpriteName)) {

				got_forest_left = true;
			}
		}


		if (other_forest->m_TransformCmp->m_GameWorldSpaceCell[0] == forest_cell[0] + 1 &&
			other_forest->m_TransformCmp->m_GameWorldSpaceCell[1] == forest_cell[1]) { // one tile right to our forest.

			if (IsSubstringInString("normal", other_forest->m_GraphicsCmp->m_SpriteName) ||
				IsSubstringInString("deep", other_forest->m_GraphicsCmp->m_SpriteName)) {

				got_forest_right = true;
			}
		}



		if (other_forest->m_TransformCmp->m_GameWorldSpaceCell[0] == forest_cell[0] &&
			other_forest->m_TransformCmp->m_GameWorldSpaceCell[1] == forest_cell[1] + 1) { // one tile down to our forest.

			if (IsSubstringInString("normal", other_forest->m_GraphicsCmp->m_SpriteName) ||
				IsSubstringInString("deep", other_forest->m_GraphicsCmp->m_SpriteName)) {

				got_forest_down = true;
			}
		}

	}

	// Forest is surrounded only if all four are true.
	return(got_forest_down && got_forest_left && got_forest_right && got_forest_up);
}




void ForestSearch::_checkForNewForestCreation(Forest* forest) {

	using namespace std;

	EntitiesStorage* storage = EntitiesStorage::Get();

	int forest_worldcell[2];
	forest_worldcell[0] = forest->m_TransformCmp->m_GameWorldSpaceCell[0];
	forest_worldcell[1] = forest->m_TransformCmp->m_GameWorldSpaceCell[1];

	Forest* other_forest = nullptr;

	// Derive the name and type of new forest.
	std::string forestname;
	if (forest->m_ForestClass == Forest::ForestClass::FOREST_CLASS_TEMPERATE) forestname = "forest_temperate_scarce";
	else if (forest->m_ForestClass == Forest::ForestClass::FOREST_CLASS_TUNDRA) forestname = "forest_tundra_scarce";
	else if (forest->m_ForestClass == Forest::ForestClass::FOREST_CLASS_JUNGLE) forestname = "forest_jungle_scarce";
	else if (forest->m_ForestClass == Forest::ForestClass::FOREST_CLASS_SAVANNAH) forestname = "forest_savannah_scarce";


	/*
	We nee to check exactly 4 maptiles. the upper left, upper right...
	
	1. upper left corner --> -1, -1
	2. upper right corner --> +1, -1
	3. lower left corner --> -1. +1
	4. lower right corner --> +1, +1
	*/

	other_forest = reinterpret_cast<Forest*>(IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(forest_worldcell[0] - 1, forest_worldcell[1] - 1), "Forest"));
	if (other_forest) { // is there forest on upper left..

		// Check first, if the forest has same class as this one, else skip everything.
		// And check whether the maptile is right for this forest to grow.
		if (!forest->HasSameForestClass(other_forest)) return;


		// check for needed type of forest --> forest_normal.
		// We may change this logic later.
		if (IsSubstringInString("normal", other_forest->m_GraphicsCmp->m_SpriteName) ||
			IsSubstringInString("deep", other_forest->m_GraphicsCmp->m_SpriteName)){ // Match! Found forest_normal  or forest_deep on needed position --> create new forest accordingly.

			// Further, we need to be sure the new forest will not be a duplicate...
			if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(forest_worldcell[0], forest_worldcell[1] - 1), "Forest")) { // As forest is upper left, we check the maptile above for creation.


				// Check whether new forest would be out of bound.
				if (IsIndexOutOfBound(forest_worldcell[0], forest_worldcell[1] - 1)) return;
				if (!MapTileAppropriteForForest(GetMapTileAtWorldPosition(forest_worldcell[0], forest_worldcell[1] - 1), forest)) return;


				// Empty tile --> create forest.
				
				// To create a new forest, we place its x and y position accordingly to that of the maptile at it position
				// We have to do this, as the x and y positions are dynamically updated accordingly to camera position.
				// Consider to wrap this functionality for ease of use...
				int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(forest_worldcell[0], forest_worldcell[1] - 1));
				int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(forest_worldcell[0], forest_worldcell[1] - 1));
				

				Forest* f = MakeNewForestAtPos(forestname, xpos, ypos, forest_worldcell[0], forest_worldcell[1] - 1);

				storage->AddGameEntitie(f);

				//cout << color(colors::CYAN);
				//cout << "New Forest created: CELL ( " << f->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << f->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << f->m_IDCmp->m_ID << white << endl;
			
			}
		}
	}



	other_forest = reinterpret_cast<Forest*>(IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(forest_worldcell[0] + 1, forest_worldcell[1] - 1), "Forest"));
	if (other_forest) { // is there forest on upper right..

		// Check first, if the forest has same class as this one, else skip everything.
		if (!forest->HasSameForestClass(other_forest)) return;

		if (IsSubstringInString("normal", other_forest->m_GraphicsCmp->m_SpriteName) ||
			IsSubstringInString("deep", other_forest->m_GraphicsCmp->m_SpriteName)) {

			
			if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(forest_worldcell[0] + 1, forest_worldcell[1]), "Forest")) {

				// Check whether new forest would be out of bound.
				if (IsIndexOutOfBound(forest_worldcell[0] + 1, forest_worldcell[1])) return;
				if (!MapTileAppropriteForForest(GetMapTileAtWorldPosition(forest_worldcell[0] + 1, forest_worldcell[1]), forest)) return;


				// Empty tile --> create forest.
				int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(forest_worldcell[0] + 1, forest_worldcell[1]));
				int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(forest_worldcell[0], forest_worldcell[1]));

				Forest* f = MakeNewForestAtPos(forestname, xpos, ypos, forest_worldcell[0] + 1, forest_worldcell[1]);

				storage->AddGameEntitie(f);

				//cout << color(colors::CYAN);
				//cout << "New Forest created: CELL ( " << f->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << f->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << f->m_IDCmp->m_ID << white << endl;
			}

		}
	}


	other_forest = reinterpret_cast<Forest*>(IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(forest_worldcell[0] - 1, forest_worldcell[1] + 1), "Forest"));
	if (other_forest) { // is there forest on down left..

		// Check first, if the forest has same class as this one, else skip everything.
		if (!forest->HasSameForestClass(other_forest)) return;


		if (IsSubstringInString("normal", other_forest->m_GraphicsCmp->m_SpriteName) ||
			IsSubstringInString("deep", other_forest->m_GraphicsCmp->m_SpriteName)) {

			if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(forest_worldcell[0] - 1, forest_worldcell[1]), "Forest")) {


				// Check whether new forest would be out of bound.
				if (IsIndexOutOfBound(forest_worldcell[0] - 1, forest_worldcell[1])) return;
				if (!MapTileAppropriteForForest(GetMapTileAtWorldPosition(forest_worldcell[0] - 1, forest_worldcell[1]), forest)) return;


				// Empty tile --> create forest.
				int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(forest_worldcell[0] - 1, forest_worldcell[1]));
				int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(forest_worldcell[0], forest_worldcell[1]));

				Forest* f = MakeNewForestAtPos(forestname, xpos, ypos, forest_worldcell[0] - 1, forest_worldcell[1]);

				storage->AddGameEntitie(f);

				//cout << color(colors::CYAN);
				//cout << "New Forest created: CELL ( " << f->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << f->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << f->m_IDCmp->m_ID << white << endl;
			}

		}
	}


	other_forest = reinterpret_cast<Forest*>(IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(forest_worldcell[0] + 1, forest_worldcell[1] + 1), "Forest"));
	if (other_forest) { // is there forest on down right..

		// Check first, if the forest has same class as this one, else skip everything.
		if (!forest->HasSameForestClass(other_forest)) return;


		if (IsSubstringInString("normal", other_forest->m_GraphicsCmp->m_SpriteName) ||
			IsSubstringInString("deep", other_forest->m_GraphicsCmp->m_SpriteName)) {

			if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(forest_worldcell[0], forest_worldcell[1] + 1), "Forest")) {

				// Check whether new forest would be out of bound.
				if (IsIndexOutOfBound(forest_worldcell[0], forest_worldcell[1] + 1)) return;
				if (!MapTileAppropriteForForest(GetMapTileAtWorldPosition(forest_worldcell[0], forest_worldcell[1] + 1), forest)) return;


				// Empty tile --> create forest.
				int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(forest_worldcell[0], forest_worldcell[1]));
				int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(forest_worldcell[0], forest_worldcell[1] + 1));

				Forest* f = MakeNewForestAtPos(forestname, xpos, ypos, forest_worldcell[0], forest_worldcell[1]+ 1);

				storage->AddGameEntitie(f);

				//cout << color(colors::CYAN);
				//cout << "New Forest created: CELL ( " << f->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << f->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << f->m_IDCmp->m_ID << white << endl;
			}

		}
	}
}


void ForestSearch::_spawnRandomForestAroundDeepOne(Forest* deepForest) {

	using namespace std;
	EntitiesStorage* storage = EntitiesStorage::Get();

	int deepForestCell[2];
	deepForestCell[0] = deepForest->m_TransformCmp->m_GameWorldSpaceCell[0];
	deepForestCell[1] = deepForest->m_TransformCmp->m_GameWorldSpaceCell[1];

	Forest* new_forest = nullptr;

	// Derive the name and type of new forest.
	std::string forestname;
	if (deepForest->m_ForestClass == Forest::ForestClass::FOREST_CLASS_TEMPERATE) forestname = "forest_temperate_scarce";
	else if (deepForest->m_ForestClass == Forest::ForestClass::FOREST_CLASS_TUNDRA) forestname = "forest_tundra_scarce";
	else if (deepForest->m_ForestClass == Forest::ForestClass::FOREST_CLASS_JUNGLE) forestname = "forest_jungle_scarce";
	else if (deepForest->m_ForestClass == Forest::ForestClass::FOREST_CLASS_SAVANNAH) forestname = "forest_savannah_scarce";



	int r = Random() % 10;

	switch (r) {
	case 0:

		// Some cell around Deep forest
		if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1] - 1), "Forest")) {

			// Check whether this new tile is out of map...
			if (IsIndexOutOfBound(deepForestCell[0] - 1, deepForestCell[1] - 1)) break;
			if (!MapTileAppropriteForForest(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1] - 1), deepForest)) return;

			// Empty tile --> create forest.
			int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1] - 1));
			int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1] - 1));

			new_forest = MakeNewForestAtPos(forestname, xpos, ypos, deepForestCell[0] - 1, deepForestCell[1] - 1);

			storage->AddGameEntitie(new_forest);

			//cout << color(colors::CYAN);
			//cout << "New Forest created around DeepForest: CELL ( " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << new_forest->m_IDCmp->m_ID << white << endl;
		}

		break;
	case 1:
		if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(deepForestCell[0], deepForestCell[1] - 1), "Forest")) {

			// Check whether this new tile is out of map...
			if (IsIndexOutOfBound(deepForestCell[0], deepForestCell[1] - 1)) break;
			if (!MapTileAppropriteForForest(GetMapTileAtWorldPosition(deepForestCell[0], deepForestCell[1] - 1), deepForest)) return;


			// Empty tile --> create forest.
			int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0], deepForestCell[1] - 1));
			int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0], deepForestCell[1] - 1));

			new_forest = MakeNewForestAtPos(forestname, xpos, ypos, deepForestCell[0], deepForestCell[1] - 1);

			storage->AddGameEntitie(new_forest);

			//cout << color(colors::CYAN);
			//cout << "New Forest created around DeepForest: CELL ( " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << new_forest->m_IDCmp->m_ID << white << endl;
		}


		break;
	case 2:
		if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1] - 1), "Forest")) {

			// Check whether this new tile is out of map...
			if (IsIndexOutOfBound(deepForestCell[0] + 1, deepForestCell[1] - 1)) break;
			if (!MapTileAppropriteForForest(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1] - 1), deepForest)) return;

			// Empty tile --> create forest.
			int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1] - 1));
			int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1] - 1));

			new_forest = MakeNewForestAtPos(forestname, xpos, ypos, deepForestCell[0] + 1, deepForestCell[1] - 1);

			storage->AddGameEntitie(new_forest);

			//cout << color(colors::CYAN);
			//cout << "New Forest created around DeepForest: CELL ( " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << new_forest->m_IDCmp->m_ID << white << endl;
		}

		break;
	case 3:
		if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1]), "Forest")) {

			// Check whether this new tile is out of map...
			if (IsIndexOutOfBound(deepForestCell[0] - 1, deepForestCell[1])) break;
			if (!MapTileAppropriteForForest(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1]), deepForest)) return;


			// Empty tile --> create forest.
			int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1]));
			int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1]));

			new_forest = MakeNewForestAtPos(forestname, xpos, ypos, deepForestCell[0] - 1, deepForestCell[1]);

			storage->AddGameEntitie(new_forest);

			//cout << color(colors::CYAN);
			//cout << "New Forest created around DeepForest: CELL ( " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << new_forest->m_IDCmp->m_ID << white << endl;
		}


		break;
	case 4:
		if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1]), "Forest")) {

			// Check whether this new tile is out of map...
			if (IsIndexOutOfBound(deepForestCell[0] + 1, deepForestCell[1])) break;
			if (!MapTileAppropriteForForest(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1]), deepForest)) return;


			// Empty tile --> create forest.
			int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1]));
			int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1]));

			new_forest = MakeNewForestAtPos(forestname, xpos, ypos, deepForestCell[0] + 1, deepForestCell[1]);

			storage->AddGameEntitie(new_forest);

			//cout << color(colors::CYAN);
			//cout << "New Forest created around DeepForest: CELL ( " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << new_forest->m_IDCmp->m_ID << white << endl;
		}
		break;
	case 5:
		if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1] + 1), "Forest")) {

			// Check whether this new tile is out of map...
			if (IsIndexOutOfBound(deepForestCell[0] - 1, deepForestCell[1] + 1)) break;
			if (!MapTileAppropriteForForest(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1] + 1), deepForest)) return;


			// Empty tile --> create forest.
			int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1] + 1));
			int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] - 1, deepForestCell[1] + 1));

			new_forest = MakeNewForestAtPos(forestname, xpos, ypos, deepForestCell[0] - 1, deepForestCell[1] + 1);

			storage->AddGameEntitie(new_forest);

			//cout << color(colors::CYAN);
			//cout << "New Forest created around DeepForest: CELL ( " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << new_forest->m_IDCmp->m_ID << white << endl;
		}
		break;
	case 6:
		if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(deepForestCell[0], deepForestCell[1] + 1), "Forest")) {

			// Check whether this new tile is out of map...
			if (IsIndexOutOfBound(deepForestCell[0], deepForestCell[1] + 1)) break;
			if (!MapTileAppropriteForForest(GetMapTileAtWorldPosition(deepForestCell[0], deepForestCell[1] + 1), deepForest)) return;



			// Empty tile --> create forest.
			int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0], deepForestCell[1] + 1));
			int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0], deepForestCell[1] + 1));

			new_forest = MakeNewForestAtPos(forestname, xpos, ypos, deepForestCell[0], deepForestCell[1] + 1);

			storage->AddGameEntitie(new_forest);

			//cout << color(colors::CYAN);
			//cout << "New Forest created around DeepForest: CELL ( " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << new_forest->m_IDCmp->m_ID << white << endl;
		}

		break;
	case 7:
		if (!IsGameEntityTypeOnMapTile(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1] + 1), "Forest")) {

			// Check whether this new tile is out of map...
			if (IsIndexOutOfBound(deepForestCell[0] + 1, deepForestCell[1] + 1)) break;
			if (!MapTileAppropriteForForest(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1] + 1), deepForest)) return;


			int xpos = GetXPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1] + 1));
			int ypos = GetYPositionOfMapTile(GetMapTileAtWorldPosition(deepForestCell[0] + 1, deepForestCell[1] + 1));

			new_forest = MakeNewForestAtPos(forestname, xpos, ypos, deepForestCell[0] + 1, deepForestCell[1] + 1);

			storage->AddGameEntitie(new_forest);

			//cout << color(colors::CYAN);
			//cout << "New Forest created around DeepForest: CELL ( " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << new_forest->m_TransformCmp->m_GameWorldSpaceCell[1] << " )" << " ---- ID: " << new_forest->m_IDCmp->m_ID << white << endl;
		}
		break;
	default:
		return;
	}

}