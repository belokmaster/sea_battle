#ifndef BOMBARD_H
#define BOMBARD_H

#include "ability.h"

class Bombard : public Ability {
public:
    void apply(BattleField& filed, int x, int y, ShipManager& manager) override;
};

#endif
