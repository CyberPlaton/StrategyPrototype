#pragma once
#include"Platform.h"

struct CMPIdentifier {
	CMPIdentifier() {

		// Stringify the own physical address or the GUID.
		std::stringstream stream;
		stream << static_cast<const void*>(this);
		m_ID = stream.str();

	}

	std::string m_ID = NULL;
};


struct CMPGraphics{

};


struct CMPTransform {

};


struct CMPPhysics {

};


struct CMPArtificialIntelligence {

};