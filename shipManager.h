#ifndef SHIP_MANAGER_H
#define SHIP_MANAGER_H

#include <iostream>
#include <vector>
#include "ship.h"
#include "battleField.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Ship;

class ShipManager {
private:
    std::vector<std::unique_ptr<Ship>> ships;
    int count;

public:
    ShipManager(int count, const std::vector<int>& sizes);

    void newShips();
    int getShipsCount();

    Ship& getShip(int index) const;
    std::vector<std::unique_ptr<Ship>>& getShips();
    bool allDestroyed();

    json to_json() const;
    void from_json(const json& j, BattleField& field);
};

#endif