#ifndef ABILITY_H
#define ABILITY_H

#include <string>
#include <iostream>

class BattleField;
class ShipManager;

class Ability {
public:
    virtual void apply(BattleField& field, int x, int y, ShipManager& manager) = 0;

    virtual ~Ability() = default;
};

#endif
