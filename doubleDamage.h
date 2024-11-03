#ifndef DOUBLE_DAMAGE_H
#define DOUBLE_DAMAGE_H

#include "ability.h"

class DoubleDamage : public Ability {
public:
    void apply(GameField& field, int x, int y, ShipManager& manager) override;
};

#endif