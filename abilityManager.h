#ifndef ABILITY_MANAGER_H
#define ABILITY_MANAGER_H

#include <iostream>
#include <queue>
#include <memory>
#include <string>
#include <random>
#include <vector>
#include <algorithm>
#include "doubleDamage.h"
#include "bombard.h"
#include "scanner.h"

class GameField;
class ShipManager;

class AbilityManager {
private:
    std::queue<std::unique_ptr<Ability>> abilities;

public:
    AbilityManager();

    void apply_ability(GameField& field, int x, int y, ShipManager& manager);
    std::string next_abilities(bool flag = false);
    void gain_random_ability();
};

#endif
