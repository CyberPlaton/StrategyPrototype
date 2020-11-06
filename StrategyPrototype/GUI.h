#pragma once
#include"Platform.h"
#include"olcPixelGameEngine.h"

namespace helper {

	extern int CurrentMousePosX();
	extern int CurrentMousePosY();

}


enum class MouseButton {
	MOUSE_BUTTON_INVALID = -1,
	MOUSE_BUTTON_LEFT = 0,
	MOUSE_BUTTON_MIDDLE = 1,
	MOUSE_BUTTON_RIGHT = 2
};


struct Widget {

	// Is mouse position in borders of widget.
	virtual bool IsHovered() = 0;

	// Function callback if widget is hovered upon.
	virtual void OnHovered() = 0;

	// Function callback if mouse was clicked on the button.
	virtual void OnClicked(MouseButton) = 0;


	int m_Xpos;
	int m_Ypos;
	int m_Width;
	int m_Height;

	int m_ID;
};


// In order to draw a widget, call olc´s DrawDecal();
struct Button : public Widget {

	bool IsHovered() override;
	void OnHovered() override;
	void OnClicked(MouseButton mb) override;

	// Name of the visual representation of this button.
	std::string m_SpriteName;
};



struct WidgetStorage {
	
	
	


	static WidgetStorage* Get() {
	
		if (g_pWidgetStorage) {
			return g_pWidgetStorage;
		}
		else {
			g_pWidgetStorage = new WidgetStorage();
			return g_pWidgetStorage;
		}
	}
	
	static void Del() {
		if (g_pWidgetStorage) {
			delete g_pWidgetStorage;
		}
	}

private:
	static int m_Widgets;
	static WidgetStorage* g_pWidgetStorage;


	std::vector<Widget*> m_WidgetsVec;
private:
	WidgetStorage() {

	}

};
