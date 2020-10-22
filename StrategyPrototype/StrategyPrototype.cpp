#include"StrategyPrototype.h"

void Renderer::Render(std::string layer) {

	using namespace olc;

	EntitiesStorage* storage = EntitiesStorage::Get();
	std::vector< GameEntity* >* vec = storage->GetStorage();

	if (COMPARE_STRINGS(layer, "layer1") == 0) {

		for (auto const& it : *vec) {
			if (COMPARE_STRINGS(it->m_GraphicsCmp->m_DrawingLayer, "layer1") == 0) {

				m_Game->DrawSprite(vi2d(it->m_TransformCmp->m_PosX, it->m_TransformCmp->m_PosY),
										m_Game->m_SpriteResourceMap.at(it->m_GraphicsCmp->m_SpriteName));
			}
		}
	}
	else if (COMPARE_STRINGS(layer, "layer2") == 0) {

	}
	else if (COMPARE_STRINGS(layer, "layer3") == 0) {

	}
	else if (COMPARE_STRINGS(layer, "layer4") == 0) {

	}
}



void Game::_loadSpriteResources() {

	for (auto const& it : *EntitiesStorage::Get()->GetStorage()) {

		// Load sprites defined.
		m_SpriteResourceMap.insert(std::make_pair(it->m_GraphicsCmp->m_SpriteName, new olc::Sprite(it->m_GraphicsCmp->m_SpritePath)));
	}
}

int main()
{
	Game demo;

	if (demo.Construct(968, 720, 1, 1, false, true, false))
		demo.Start();


	return 0;
}