#ifndef SHIP_MANAGER_H
#define SHIP_MANAGER_H

#include <iostream>
#include <vector>
#include "ship.h"
#include "gameField.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Ship;

class ShipManager {
private:
    std::vector<std::unique_ptr<Ship>> ships;
    int count;
public:
    ShipManager(int count, const std::vector<int>& sizes);

    bool all_ships_destroy();

    int get_ships_count();

    Ship& get_ship(int index) const;

    std::vector<std::unique_ptr<Ship>>& get_ships();

    void new_ships();

    json to_json() const;

    void from_json(const json& j, GameField& field);
};

#endif