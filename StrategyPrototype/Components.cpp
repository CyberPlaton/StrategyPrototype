#include"Components.h"

void CMPInput::HandleKeyboard() {

}


void CMPInput::HandleMouse() {

}


int CMPMovementCostModifier::GetFinalMovementCost(std::string race, MapTile* maptile) {
	return MovementCostHelper::GetFinalMovementCost(race, maptile);
}