#pragma once

#include"Platform.h"

class Resources{
public:
	Resources();


	static Resources* Get() {

		if (m_Resources) {
			return m_Resources;
		}
		else {
			m_Resources = new Resources();
			return m_Resources;
		}
	}

	static void Del() {
		if (m_Resources) delete m_Resources;
	}

private:

	static Resources* m_Resources;
	std::map<std::string, std::string> m_ResourcePathMap; // e.g. "woods_scarce" = "assets/trees/woods_scarce_temp.png". 

private:

};

