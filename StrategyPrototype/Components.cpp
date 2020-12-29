// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include"Components.h"

void CMPInput::HandleKeyboard() {

}


void CMPInput::HandleMouse() {

}


int CMPMovementCostModifier::GetFinalMovementCost(std::string race, MapTile* maptile, Unit* unit) {
	return MovementCostHelper::GetFinalMovementCost(race, maptile, unit);
}