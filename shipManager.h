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

    void print_states();

    int get_ships_count();

    Ship& get_ship(int index) const;
};

#endif