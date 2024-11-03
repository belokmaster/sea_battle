#include "doubleDamage.h"
#include "battleField.h"
#include "shipManager.h"

void DoubleDamage::apply(BattleField& field, int x, int y, ShipManager& manager) {
    field.set_double_damage(true);
    std::cout << "Next hit deals double damage" << std::endl;

}