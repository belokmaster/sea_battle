#ifndef SHIP_MANAGER_H
#define SHIP_MANAGER_H

#include <iostream>
#include <vector>
#include "ship.h"


class Ship;

class ShipManager {
private:
    std::vector<std::unique_ptr<Ship>> ships;
    int count;

public:
    ShipManager(int count, const std::vector<int>& sizes);
    int getShipsCount();
    void printStates();
    Ship& getShip(int index) const;
};

#endif