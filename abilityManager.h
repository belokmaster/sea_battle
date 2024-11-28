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

    void applyAbility(BattleField& field, int x, int y, ShipManager& manager);
    std::string nextAbility(bool flag = false);
    void getRandomAbility();
};

#endif