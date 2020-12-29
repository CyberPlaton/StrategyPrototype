#pragma once
// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include"Platform.h"

struct IStateLogic {
	virtual void executeStateLogic() = 0;
};


enum class States {
	STATE_INVALID = -1, // Implementation helper.


	STATE_PATROL = 0,
	STATE_SEARCH = 1,
	STATE_ATTACK = 2,
	STATE_DEFEND = 3,
	STATE_FLEE = 4,
	STATE_DIE = 5,
	STATE_MOVE = 6,
	STATE_WAIT = 7,



	STATE_INVALID_END // Do not define number for this, and do not remove it. Implementation helper.
};



class FiniteStateMachine{
public:
	FiniteStateMachine(States state) {
		m_CurrentState = state;
	}

	~FiniteStateMachine() = default;

	void ChangeState(States state) {
		m_CurrentState = state;
	}

	States GetCurrentState() {
		return m_CurrentState;
	}


private:
	States m_CurrentState = States::STATE_INVALID;

private:

};

