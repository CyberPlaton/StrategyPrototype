#include"StrategyPrototype.h"

Game* Game::m_Game = nullptr;
static olc::vf2d g_vi2dCameraPosition = olc::vf2d(0.0f, 0.0f);
static int ColorValue = 0;

PlayerTurnCounter* PlayerTurnCounter::g_pPlayerTurnCounter = nullptr;


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


Unit* MakeNewUnitAtPos(CMPEntityRace::Race race, Player* p, std::string unit_class, std::string spritename, int xpos, int ypos, int x_cell, int y_cell) {

	Unit* u = new Unit(race, spritename, xpos, ypos, x_cell, y_cell);

	u->SetBirthsign();

	u->SetClass(unit_class);

	u->SetDerivedStats();

	u->SetPlayer(p);

	return u;
}


Unit* GetUnitAtMapTileFromMousePosition(int xpos, int ypos) {

	std::vector<GameEntity*> vec = *EntitiesStorage::Get()->GetUnitsVec();
	
	Unit* unit = nullptr;

	for (auto it = vec.begin(); it != vec.end(); ++it) {

		unit = reinterpret_cast<Unit*>(*it);

		if (int(xpos / SPRITES_WIDTH_AND_HEIGHT) == int(unit->m_TransformCmp->m_PosX / SPRITES_WIDTH_AND_HEIGHT) &&
			int(ypos / SPRITES_WIDTH_AND_HEIGHT) == int(unit->m_TransformCmp->m_PosY / SPRITES_WIDTH_AND_HEIGHT)) {

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

	// TODO:
	// Define later on which layer to render rivers...
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


void CMPCameraInput::_handleCityViewKeyboard(Camera* cam) {

	Game* context = cam->m_Game;


	if (context->GetKey(olc::Key::ESCAPE).bReleased) {

		context->m_Renderer->ChangeRenderMode();
		context->m_Renderer->SetCurrentViewedCity(nullptr); // Reset city which we now view.

	}

}


static int g_iUnitClassIndex = 0;
static int g_iUnitRaceIndex = 0;
static std::string g_sUnitClasses[5] = {
	"Assassin", "Spy", "Warrior", "Sorcerer", "Paladin"
};

static CMPEntityRace::Race g_rUnitRaces[8] = {
	CMPEntityRace::Race::RACE_DARKELF,
	CMPEntityRace::Race::RACE_HIGHELF,
	CMPEntityRace::Race::RACE_HUMAN,
	CMPEntityRace::Race::RACE_ORC,
	CMPEntityRace::Race::RACE_GNOME,
	CMPEntityRace::Race::RACE_TROLL,
	CMPEntityRace::Race::RACE_GOBLIN,
	CMPEntityRace::Race::RACE_DWARF
};


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
	if (context->GetMouse(1).bPressed) {

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

		// Select unit.
		PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlySelectedUnit = GetUnitAtMapTileFromMousePosition(context->GetMouseX(), context->GetMouseY());
		
		cout << "Unit selected: ";
		if (PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlySelectedUnit) {
			cout << PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlySelectedUnit->m_Name << white << endl;
		}
		else {
			cout << " nullptr" << white << endl;
		}
	}

	if (PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlySelectedUnit != nullptr) {

		if (context->GetKey(olc::Key::ENTER).bPressed) {

			// Set loose to patrol.
			PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlySelectedUnit->m_AICmp->ChangeState(States::STATE_PATROL);

			// IGOUGO Mode --> execute units logic...
			//NOTE:
			// This works for instant "go to".
			// For patroling the AI-Unit should himself set AT THE END of a PLAYER TURN "tryExecuteLogic"...
			// Thus we get an effect like in CIV6.
			PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_CurrentlySelectedUnit->m_AICmp->TryExecuteStateLogic();
		}


		if (context->GetMouse(1).bPressed) {

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
	}


	// Reset the mousedown state to non-down...
	if (context->GetMouse(0).bReleased) {
		IMGUI::Get()->GetUIState()->m_MouseDown = -1;
	}


	
	if (context->GetKey(olc::Key::CTRL).bHeld) {

		if (context->GetMouse(0).bPressed) {

			// TESTING PURPOSES:
			tile = GetMaptileAtMousePosition(context->GetMouseX(), context->GetMouseY());
			Unit* unit = MakeNewUnitAtPos(PlayerTurnCounter::Get()->m_CurrentTurnPlayer->m_PlayerEmpireRace, PlayerTurnCounter::Get()->m_CurrentTurnPlayer,
				g_sUnitClasses[++g_iUnitClassIndex % 5], "gnome_noble",
				tile->m_TransformCmp->m_PosX, tile->m_TransformCmp->m_PosY,
				tile->m_TransformCmp->m_GameWorldSpaceCell[0], tile->m_TransformCmp->m_GameWorldSpaceCell[1]);

			EntitiesStorage::Get()->AddGameEntitie(unit);

		}
	}
	

}


void CMPCameraInput::_handleCityViewMouse(Camera* cam) {

	Game* context = cam->m_Game;


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
	Sprite* back1 = new Sprite("assets/background/city/background_city_forest_temperate.png");
	Sprite* back2 = new Sprite("assets/background/city/background_city_orc_normal.png");
	Sprite* back3 = new Sprite("assets/background/city/background_city_human_normal.png");
	Sprite* back4 = new Sprite("assets/background/city/background_city_hills.png");
	Sprite* back5 = new Sprite("assets/background/city/background_city_human_river.png");




	m_SpriteStorage.push_back(back1);
	m_SpriteStorage.push_back(back2);
	m_SpriteStorage.push_back(back3);
	m_SpriteStorage.push_back(back4);
	m_SpriteStorage.push_back(back5);


	Decal* d_back1 = new Decal(back1);
	Decal* d_back2 = new Decal(back2);
	Decal* d_back3 = new Decal(back3);
	Decal* d_back4 = new Decal(back4);
	Decal* d_back5 = new Decal(back5);


	m_SpriteResourceMap.insert(std::make_pair("background_city_forest_temperate", d_back1));
	m_SpriteResourceMap.insert(std::make_pair("background_city_orc_normal", d_back2));
	m_SpriteResourceMap.insert(std::make_pair("background_city_human_normal", d_back3));
	m_SpriteResourceMap.insert(std::make_pair("background_city_hills", d_back4));
	m_SpriteResourceMap.insert(std::make_pair("background_city_human_river", d_back5));





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





	// Units.
	Sprite* gnome = new Sprite("assets/unit/gnome/gnome_mechafighter.png");
	Sprite* troll = new Sprite("assets/unit/troll/troll_raptor_rider.png");
	Sprite* gnome1 = new Sprite("assets/unit/gnome/gnome_citizen.png");
	Sprite* gnome2 = new Sprite("assets/unit/gnome/gnome_worker.png");
	Sprite* gnome3 = new Sprite("assets/unit/gnome/gnome_noble.png");
	Sprite* gnome4 = new Sprite("assets/unit/gnome/gnome_priest.png");
	Sprite* gnome5 = new Sprite("assets/unit/gnome/gnome_fisher.png");
	Sprite* gnome6 = new Sprite("assets/unit/gnome/gnome_hunter.png");
	Sprite* gnome7 = new Sprite("assets/unit/gnome/gnome_miner.png");
	Sprite* gnome8 = new Sprite("assets/unit/gnome/gnome_farmer.png");



	m_SpriteStorage.push_back(gnome1);
	m_SpriteStorage.push_back(gnome2);
	m_SpriteStorage.push_back(gnome3);
	m_SpriteStorage.push_back(gnome4);
	m_SpriteStorage.push_back(gnome5);
	m_SpriteStorage.push_back(gnome6);
	m_SpriteStorage.push_back(gnome7);
	m_SpriteStorage.push_back(gnome8);


	m_SpriteStorage.push_back(gnome);
	m_SpriteStorage.push_back(troll);

	Decal* d_gnome1 = new Decal(gnome1);
	Decal* d_gnome2 = new Decal(gnome2);
	Decal* d_gnome3 = new Decal(gnome3);
	Decal* d_gnome4 = new Decal(gnome4);
	Decal* d_gnome5 = new Decal(gnome5);
	Decal* d_gnome6 = new Decal(gnome6);
	Decal* d_gnome7 = new Decal(gnome7);
	Decal* d_gnome8 = new Decal(gnome8);

	Decal* d_gnome = new Decal(gnome);
	Decal* d_troll = new Decal(troll);

	m_SpriteResourceMap.insert(std::make_pair("gnome_citizen", d_gnome1));
	m_SpriteResourceMap.insert(std::make_pair("gnome_worker", d_gnome2));
	m_SpriteResourceMap.insert(std::make_pair("gnome_noble", d_gnome3));
	m_SpriteResourceMap.insert(std::make_pair("gnome_priest", d_gnome4));
	m_SpriteResourceMap.insert(std::make_pair("gnome_fisher", d_gnome5));
	m_SpriteResourceMap.insert(std::make_pair("gnome_hunter", d_gnome6));
	m_SpriteResourceMap.insert(std::make_pair("gnome_miner", d_gnome7));
	m_SpriteResourceMap.insert(std::make_pair("gnome_farmer", d_gnome8));
	m_SpriteResourceMap.insert(std::make_pair("gnome_mechafighter", d_gnome));
	
	m_SpriteResourceMap.insert(std::make_pair("troll_raptor_rider", d_troll));

	/*
	// Unit ribbons and player color thingies and classes...
	Sprite* player_color1 = new Sprite("assets/unit/unit_player_color_red.png");
	Sprite* player_color2 = new Sprite("assets/unit/unit_player_color_blue.png");
	Sprite* player_color3 = new Sprite("assets/unit/unit_player_color_magenta.png");

	Sprite* class1 = new Sprite("assets/unit/unit_class_archer.png");



	Decal* d_player_color1 = new Decal(player_color1);
	Decal* d_player_color2 = new Decal(player_color2);
	Decal* d_player_color3 = new Decal(player_color3);

	Decal* dclass1 = new Decal(class1);



	m_SpriteResourceMap.insert(std::make_pair("unit_player_color_red", d_player_color1));
	m_SpriteResourceMap.insert(std::make_pair("unit_player_color_blue", d_player_color2));
	m_SpriteResourceMap.insert(std::make_pair("unit_player_color_magenta", d_player_color3));

	m_SpriteResourceMap.insert(std::make_pair("unit_class_archer", dclass1));
	*/
}


bool IMGUI::AddSprite(std::string path, std::string spritename) {

	using namespace olc;

	Sprite* s = new Sprite(path);
	if (s == nullptr) return false;

	IMGUI::Get()->m_IMGUISpriteResourceMap.insert(std::make_pair(spritename, s));
	
	Decal* d = new Decal(s);
	IMGUI::Get()->m_IMGUIDecalMap.insert(std::make_pair(spritename, d));
	
}


void Game::_initializeMap() {

	m_WorldMap = WorldMap::Get();
	WorldMapDrawingOptions* mapOpt = new WorldMapDrawingOptions(19, 19);
	
	m_WorldMap->SetMapOptions(mapOpt);
}


void Game::_initialize() {

	_loadSpriteResources();
	_initializeMap();

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

	
	Player* player = new Player("Bogdan", "blue", CMPEntityRace::Race::RACE_HUMAN);
	storage->AddPlayer(player);

	Player* player2 = new Player("Hans", "red", CMPEntityRace::Race::RACE_ORC);
	storage->AddPlayer(player2);

	Player* player3 = new Player("Walter", "orange", CMPEntityRace::Race::RACE_HIGHELF);
	storage->AddPlayer(player3);



	PlayerTurnCounter::Get()->AddPlayer(player);
	PlayerTurnCounter::Get()->AddPlayer(player2);
	PlayerTurnCounter::Get()->AddPlayer(player3);


	
	// Cityname should be max 11. chars...
	City* city2 = MakeNewCity(true, "Stormgrad", CMPEntityRace::Race::RACE_HUMAN, player, 7, 6, 5);
	storage->AddGameEntitie(city2);

	/*
	City* fort = MakeNewCity(true, "Durotar", CMPEntityRace::Race::RACE_ORC, player2, 15, 8, 8);
	City* city4 = MakeNewCity(false, "Lorderon", CMPEntityRace::Race::RACE_HUMAN, player3, 4, 11, 2);

	City* city3 = MakeNewCity(true, "Orgrimmar", CMPEntityRace::Race::RACE_ORC, player4, 18, 5, 2);
	City* fort2 = MakeNewCity(false, "Razor Hill", CMPEntityRace::Race::RACE_ORC, player5, 13, 3, 4);

	City* city5 = MakeNewCity(true, "Iceveil", CMPEntityRace::Race::RACE_HUMAN, player6, 2, 2, 1);
	City* city6 = MakeNewCity(false, "Lower Orgrimmar", CMPEntityRace::Race::RACE_ORC, player7, 18, 12, 1);
	City* fort3 = MakeNewCity(false, "Upper Razor Hill", CMPEntityRace::Race::RACE_HUMAN, player8, 8, 2, 1);


	storage->AddGameEntitie(city4);
	storage->AddGameEntitie(fort);

	storage->AddGameEntitie(city3);
	storage->AddGameEntitie(fort2);
	storage->AddGameEntitie(city5);
	storage->AddGameEntitie(city6);
	storage->AddGameEntitie(fort3);
	*/


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
	IMGUI::Get()->FinishIMGUI();

	return true;
}


static int m_IDHelper = 0;
void Renderer::DrawCityPanels() {
	
	City* city = nullptr;
	int id;

	for (auto it : *EntitiesStorage::Get()->GetCitiesVec()) {

		city = reinterpret_cast<City*>(it);

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

	m_Game->SetDrawTarget(m_Layer1);
	m_Game->Clear(olc::BLANK);



	m_Game->EnableLayer(m_Layer1, true);
	m_Game->SetDrawTarget(nullptr);
}


void Renderer::RenderCityLayer2() {

	m_Game->SetDrawTarget(m_Layer2);
	m_Game->Clear(olc::BLANK);


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
	if (m_CurrentViewedCity == nullptr) return;
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

	using namespace olc;

	Pixel* tundra = new Pixel(60, 81, 72, 255);
	Pixel* savannah = new Pixel(187, 161, 80, 255);
	Pixel* jungle = new Pixel(88, 66, 124, 255);
	Pixel* temperate = new Pixel(107, 142, 78);



	switch (maptile->m_MapTileType) {
	case MapTile::MapTileType::MAPTILE_TYPE_TUNDRA:
		m_Game->FillRect(vi2d(2, 202), vi2d(700, 520), *tundra);
		break;
	case MapTile::MapTileType::MAPTILE_TYPE_SAVANNAH:
		m_Game->FillRect(vi2d(2, 202), vi2d(700, 520), *savannah);
		break;
	case MapTile::MapTileType::MAPTILE_TYPE_TEMPERATE:
		m_Game->FillRect(vi2d(2, 202), vi2d(700, 520), *temperate);
		break;
	case MapTile::MapTileType::MAPTILE_TYPE_JUNGLE:
		m_Game->FillRect(vi2d(2, 202), vi2d(700, 520), *jungle);
		break;
	default:
		m_Game->FillRect(vi2d(2, 202), vi2d(700, 520), olc::RED);
		break;
	}
}


void Renderer::RenderCityLayer4() {

	using namespace olc;

	m_Game->SetDrawTarget(m_Layer4);
	m_Game->Clear(olc::BLANK);

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


	// Version 2.0.
	m_Game->DrawDecal(vi2d(2, 2), m_Game->m_SpriteResourceMap.at("cityview_upper_panel"));


	// Here, draw a color of underground based on the cities Maptile MapTileType...
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


	m_Game->EnableLayer(m_Layer4, true);
	m_Game->SetDrawTarget(nullptr);
}



void Game::DebugDrawStats() {

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

	for (auto it = vec.begin(); it != vec.end(); ++it) {

		unit = reinterpret_cast<Unit*>(*it);

		// For now, do not check for out of screen..

		// Draw unit.
		m_Game->DrawDecal(vf2d(unit->m_TransformCmp->m_PosX, unit->m_TransformCmp->m_PosY), 
						m_Game->m_SpriteResourceMap.at(unit->m_GraphicsCmp->m_SpriteName));
	}



	/*
	m_Game->DrawDecal(vi2d(320, 256), m_Game->m_SpriteResourceMap.at("gnome_mechafighter"));
	m_Game->DrawDecal(vi2d(384, 256), m_Game->m_SpriteResourceMap.at("troll_raptor_rider"));

	m_Game->DrawDecal(vi2d(128, 128), m_Game->m_SpriteResourceMap.at("gnome_worker"));
	m_Game->DrawDecal(vi2d(256, 128), m_Game->m_SpriteResourceMap.at("gnome_citizen"));
	m_Game->DrawDecal(vi2d(320, 128), m_Game->m_SpriteResourceMap.at("gnome_noble"));
	m_Game->DrawDecal(vi2d(384, 128), m_Game->m_SpriteResourceMap.at("gnome_farmer"));
	m_Game->DrawDecal(vi2d(512, 128), m_Game->m_SpriteResourceMap.at("gnome_fisher"));
	m_Game->DrawDecal(vi2d(512, 256), m_Game->m_SpriteResourceMap.at("gnome_hunter"));
	m_Game->DrawDecal(vi2d(512, 320), m_Game->m_SpriteResourceMap.at("gnome_priest"));
	m_Game->DrawDecal(vi2d(512, 384), m_Game->m_SpriteResourceMap.at("gnome_miner"));
	*/

	



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

	// First, draw the mapviewressources.
	for (auto it = vec.begin(); it != vec.end(); ++it) {

		entity = reinterpret_cast<MapRessource*>(*it);

		// Do not draw tiles we do not see.
		if (entity->m_TransformCmp->m_Cell[0] > VISIBLE_MAP_WIDTH ||
			entity->m_TransformCmp->m_Cell[1] > VISIBLE_MAP_HEIGHT) continue;

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



		// First, we draw political region tiles.
		// Draw political map related borders.
		if (m_Game->m_PoliticalMap) {

			// Test, draw region around city.
			for (auto it = city->m_ClaimedRegions.begin(); it != city->m_ClaimedRegions.end(); ++it) {

				region = *it;

				_drawMapTileRegionRect(region);
			}

		}


		// After that we draw city. Thus the city will be drawn oer the regiontiles...
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

				// Draw appropriate loaded sprite on position specified.
				m_Game->DrawDecal(vi2d(tile->m_TransformCmp->m_PosX, tile->m_TransformCmp->m_PosY),
					m_Game->m_SpriteResourceMap.at(c->m_MapTileBorderDirectionMap.at(tile)), vf2d(1.0f, 1.0f),
					m_Game->MakeOlcColorFromCityBorderColor(c->m_CityBorderColor));

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
	/*
	std::vector< GameEntity* > vec = *storage->GetMapTilesStorage();

	MapTile* maptile = nullptr;
	GameEntity* entity = nullptr;
	Forest* f = nullptr;


	m_Game->SetDrawTarget(m_Layer3);
	m_Game->Clear(olc::BLANK);

	// Render Forests, Hills, etc.
	for (auto it = vec.begin(); it != vec.end(); ++it) {

		maptile = reinterpret_cast<MapTile*>(*it);

		// Do not draw tiles we do not see.
		if (maptile->m_TransformCmp->m_Cell[0] > VISIBLE_MAP_WIDTH ||
			maptile->m_TransformCmp->m_Cell[1] > VISIBLE_MAP_HEIGHT) continue;


		if (maptile->m_MapTileEntities->size() > 0) {


			for (auto iter = maptile->m_MapTileEntities->begin(); iter != maptile->m_MapTileEntities->end(); ++iter) {
						
				//entity = *iter;
				f = reinterpret_cast<Forest*>(*it);

				// Draw appropriate loaded sprite on position specified.
				m_Game->DrawDecal(vi2d(f->m_TransformCmp->m_PosX, f->m_TransformCmp->m_PosY),
										m_Game->m_SpriteResourceMap.at(f->m_GraphicsCmp->m_SpriteName));

			}

		}
	}
	*/

	m_Game->SetDrawTarget(m_Layer3);
	m_Game->Clear(olc::BLANK);

	MapTile* maptile = nullptr;
	Forest* forest = nullptr;
	GameEntity* entity = nullptr;



	// Render Forests
	std::vector< GameEntity* > vec = *storage->GetMapTilesStorage();

	for (auto it = vec.begin(); it != vec.end(); ++it) {

		maptile = reinterpret_cast<MapTile*>(*it);

		// Do not draw tiles we do not see.
		if (maptile->m_TransformCmp->m_Cell[0] > VISIBLE_MAP_WIDTH ||
			maptile->m_TransformCmp->m_Cell[1] > VISIBLE_MAP_HEIGHT) continue;


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


	for (auto it = vec.begin(); it != vec.end(); ++it) {

		maptile = reinterpret_cast<MapTile*>(*it);

		// Do not draw tiles we do not see.
		if (maptile->m_TransformCmp->m_Cell[0] > VISIBLE_MAP_WIDTH ||
			maptile->m_TransformCmp->m_Cell[1] > VISIBLE_MAP_HEIGHT) continue;


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
	DrawUnitPanels();



	// Show whos turn it is.
	DrawCurrentTurnPlayerPanel();
	
}



void Renderer::DrawUnitPanels() {

	using namespace olc;

	std::vector<GameEntity*> vec = *EntitiesStorage::Get()->GetUnitsVec();

	Unit* unit = nullptr;
	IMGUI* gui = IMGUI::Get();

	// Flag for drawing additional panels.
	static bool age_panel = false;


	for (auto it = vec.begin(); it != vec.end(); ++it) {

		unit = reinterpret_cast<Unit*>(*it);

		// Player unit color.
		std::string player_string = "Belongs to " + unit->m_AssociatedPlayer->m_PlayerName;
		if (gui->ToolTipSpriteButton(Random() + GEN_ID, unit->m_TransformCmp->m_PosX, unit->m_TransformCmp->m_PosY, unit->m_UnitPlayerColor, player_string, olc::WHITE)) {

			age_panel = (age_panel == true) ? false : true;
		}

		// Unit ribbon.
		std::string unit_ribbon = unit->m_UnitClass->m_UnitClassName;
		if (gui->ToolTipSpriteButton(Random() + GEN_ID, unit->m_TransformCmp->m_PosX + 64 - 16, unit->m_TransformCmp->m_PosY, unit->m_UnitClass->m_UnitClassSpritename, unit_ribbon, olc::WHITE));
	

		

		// Drawing additional panels.
		if (age_panel) {

			std::string age = "Age: " + std::to_string(unit->m_Age) + " MaxAge: " + std::to_string(unit->m_MaxAge);
			gui->TextButton(++m_IDHelper + GEN_ID, unit->m_TransformCmp->m_PosX + 16, unit->m_TransformCmp->m_PosY + 64, age);
		}
		
	}
}



void Game::_updateForestAI2() {

	using namespace std;

	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector<GameEntity*> vec = *storage->GetForestsVec();
	GameEntity* entity = nullptr;
	

	cout << color(colors::BLUE) << endl << endl;
	cout << "Executing _updateForestAI2()." << white << endl;

	for (auto it = vec.begin(); it != vec.end(); ++it) {
		try {

			entity = *it;

			cout << APP_COLOR;
			cout << "Executing state logic for " << entity->m_IDCmp->m_DynamicTypeName << " at position "
				<< entity->m_TransformCmp->m_GameWorldSpaceCell[0] << " : " << entity->m_TransformCmp->m_GameWorldSpaceCell[1] << white << endl;

			if (!entity->m_AICmp->TryExecuteStateLogic()) {

					cout << APP_ERROR_COLOR
					 << " was unsuccessfull." << white << endl << endl;

			}
			else {

				cout << APP_SUCCESS_COLOR
					 << " was successfull." << white << endl << endl;
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

	if (!PlayerTurnCounter::Get()->NextPlayerTurn()) {
		return;
	}


	if (m_AdvanceOneTurn) {

		_updateForestAI2();

		m_TurnCount++;

		m_AdvanceOneTurn = false;

		YearCounter::Get()->AdvanceOneTurn();


		Unit* unit = nullptr;
		for (auto it : *EntitiesStorage::Get()->GetUnitsVec()) {

			unit = reinterpret_cast<Unit*>(it);
			unit->Update();

			cout << APP_SUCCESS_COLOR;
			cout << endl;
			cout << "Unit name: " << unit->m_Name << endl;
			cout << "Unit race: " << unit->m_EntityRaceCmp->m_EntityRaceString << endl;
			cout << "Unit class: " << unit->m_UnitClass->m_UnitClassName << endl;
			cout << "Unit birthsign: " << unit->m_Birthsign << endl;
			cout << "Unit stats: " << endl;
			cout << endl;

			for (auto it : *unit->GetUnitSkills()) {
				cout << "Skill \"" << SkillToString(it.first) << "\" ::= " << it.second << endl;
			}

			cout << endl;

			for (auto it : *unit->GetUnitAttributes()) {
				cout << "Attribute \"" << AttributeToString(it.first) << "\" ::= " << it.second << endl;
			}

		}
	}
	else if (m_TimeModeTurnBased == false) {

		_updateForestAI2();


		m_TurnCount++;

		YearCounter::Get()->AdvanceOneTurn();

		Unit* unit = nullptr;
		for (auto it : *EntitiesStorage::Get()->GetUnitsVec()) {
			
			unit = reinterpret_cast<Unit*>(it);
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
	std::vector< GameEntity* > vec = *storage->GetAIEntitiesStorage();

	// TODO:
	// Add forests to own vector storage, and iterate through it.


	Forest* other_forest = nullptr;

 	for (auto it = vec.begin(); it != vec.end(); ++it) {

		if (forest == *it) continue;

		other_forest = reinterpret_cast<Forest*>(*it);

		// TODO continue:
		// For now, we make sure to iterate only thorugh forests like this.
		if (!IsSubstringInString("Forest", other_forest->m_IDCmp->m_DynamicTypeName)) continue;


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