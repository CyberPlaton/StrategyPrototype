#include"Components.h"

void CMPInput::HandleKeyboard() {

}


void CMPInput::HandleMouse() {

}


int CMPMovementCostModifier::GetFinalMovementCost(std::string race, MapTile* maptile, Unit* unit) {
	return MovementCostHelper::GetFinalMovementCost(race, maptile, unit);
}