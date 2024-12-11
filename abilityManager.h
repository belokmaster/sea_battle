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
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class GameField;
class ShipManager;

class AbilityManager {
private:
    std::queue<std::unique_ptr<Ability>> abilities;
    int len_queue = 3;

public:
    AbilityManager();

    void apply_ability(GameField& field, int x, int y, ShipManager& manager);

    std::string next_abilities();

    void gain_random_ability();

    int get_len_queue();
    void set_len_queue(int value);

    void from_json(const json& j);
    json to_json();
};

#endif
