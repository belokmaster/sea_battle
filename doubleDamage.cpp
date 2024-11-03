#include "doubleDamage.h"
#include "gameField.h"
#include "shipManager.h"

void DoubleDamage::apply(GameField& field, int x, int y, ShipManager& manager) {
    field.set_double_damage(true);
    std::cout << "Next hit deals double damage" << std::endl;

}