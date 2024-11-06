#include "doubleDamage.h"
#include "../battleField.h"
#include "../shipManager.h"

void DoubleDamage::apply(BattleField& field, int x, int y, ShipManager& manager) {
    field.setDoubleDamage(true);
    std::cout << "Next hit deals double damage" << std::endl;
}