#include"GUI.h"

WidgetStorage* WidgetStorage::g_pWidgetStorage = nullptr;
int WidgetStorage::m_Widgets = 0;



bool Button::IsHovered() {

	// Is mouse position in borders of widget.

	bool collision = false;

	float own_x_pos = m_Xpos;
	float own_y_pos = m_Ypos;
	int own_size[2];
	own_size[0] = m_Width;
	own_size[1] = m_Height;


	float mouseX = helper::CurrentMousePosX();
	float mouseY = helper::CurrentMousePosY();



	if (own_x_pos < (mouseX) &&
		(own_x_pos + own_size[0]) > mouseX &&
		own_y_pos < (mouseY) &&
		(own_y_pos + own_size[1]) > mouseY) {

		collision = true;
	}

	return (collision);
}


void Button::OnHovered() {

	// Function callback if widget is hovered upon.
}


void Button::OnClicked(MouseButton mb) {

	// Function callback if mouse was clicked on the button.

}