#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include "ship.h" 
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;


class shipManager {
private:
    int countShips;
    std::vector<int> lenShips;
    std::vector<Ship> ships;
    int number_ships;

public:
    shipManager(int countShips, std::vector<int> lenShips);
    shipManager() = default;

    void createShip(int length, int orientation, int x, int y);
    std::vector<Ship>& getShips();
    Ship& getShip();
    std::vector<int> getLenShips();

    int getNumberShip();
    void removeShip(int i);
    int getCountShips();

    json write_json();
    shipManager* load_json(json j);
    void load_from_json_ship(json j);

    ~shipManager();
};
#endif