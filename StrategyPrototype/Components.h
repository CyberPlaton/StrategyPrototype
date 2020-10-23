#pragma once
#include"Platform.h"

struct CMPIdentifier {
	CMPIdentifier() {

		// Stringify the own physical address or the GUID.
		std::stringstream stream;
		stream << static_cast<const void*>(this);
		m_ID = stream.str();

	}

	std::string m_ID;
};


struct CMPGraphics{



	std::string m_DrawingLayer;

	std::string m_SpriteName;
};


struct CMPTransform {



	int m_PosX;
	int m_PosY;


	int m_Width;
	int m_Height;

	int m_Cell[2];
};


struct CMPPhysics {

};


struct CMPArtificialIntelligence {

};


struct CMPInput {


	virtual void HandleKeyboard();
	virtual void HandleMouse();
};