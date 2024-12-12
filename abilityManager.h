#ifndef ABILITY_MANAGER_H
#define ABILITY_MANAGER_H

#include "abilities/doubleDamage.h"
#include "abilities/bombard.h"
#include "abilities/scanner.h"
#include "nlohmann/json.hpp"

#include <iostream>
#include <queue>
#include <memory>
#include <string>
#include <random>
#include <vector>
#include <algorithm>

using json = nlohmann::json;

class BattleField;
class ShipManager;

class AbilityManager {
private:
    std::queue<std::unique_ptr<Ability>> abilities;
    int countAbilities = 3;

public:
    AbilityManager();

    void applyAbility(BattleField& field, int x, int y, ShipManager& manager);
    std::string nextAbility();
    void getRandomAbility();
    
    int getCountAbilities();
    void setCountAbilities(int value);

    void from_json(const nlohmann::json& j);
    json to_json();
};

#endif
