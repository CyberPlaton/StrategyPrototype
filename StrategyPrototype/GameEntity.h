#pragma once
#include"Platform.h"
#include"Components.h"
#include"FiniteStateMachine.h"


class GameEntity{
public:



	// Basic components for an Entity.
	CMPTransform* m_TransformCmp = nullptr;
	CMPPhysics* m_PhysicsCmp = nullptr;
	CMPGraphics* m_GraphicsCmp = nullptr;
	CMPArtificialIntelligence* m_AICmp = nullptr;
	FiniteStateMachine* m_FSM = nullptr;
};

