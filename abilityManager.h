#ifndef ABILITY_MANAGER_H
#define ABILITY_MANAGER_H

#include <iostream>
#include <queue>
#include <memory>
#include <string>
#include <random>
#include <vector>
#include <algorithm>
#include "abilities/doubleDamage.h"
#include "abilities/bombard.h"
#include "abilities/scanner.h"

class BattleField;
class ShipManager;

class AbilityManager {
private:
    std::queue<std::unique_ptr<Ability>> abilities;

public:
    AbilityManager();

    void apply_ability(BattleField& field, int x, int y, ShipManager& manager);
    std::string next_abilities(bool flag = false);
    void gain_random_ability();
};

#endif
