#include "shipManager.h"
#include "ship.h"


ShipManager::ShipManager(int count, const std::vector<int>& sizes) : count(count) {
    if (count != sizes.size()) {
        throw std::invalid_argument("Count of ships must match sizes vector.");
    }

    for (int size : sizes) {
        ships.emplace_back(std::make_unique<Ship>(size, size % 2 == 0));
    }
}


int ShipManager::getShipsCount() {
    return count;
}


void ShipManager::printStates() {
    std::cout << std::endl;
    for (int i = 0; i < ships.size(); i++) {
        Ship& ship = *ships[i];

        int len_ship = ship.getLength();
        int count_destroy = 0;

        int x = ship.get_x();
        int y = ship.get_y();
        char orientation = ship.isVertical() ? 'v' : 'h'; 

        std::cout << "Ship " << (i + 1) << (i < 9 ? "  " : " ") << "[" << x << " " << y << " " << orientation << "]: ";

        for (int j = 0; j < len_ship; j++) {
            int state = ship.getSegmentState(j);
            
            if (state == 0) {
                std::cout << "I";
            } 
            else if (state == 1) {
                std::cout << "X";
            } 
            else if (state == 2) {
                std::cout << "D";
                count_destroy++;
            }
            
            std::cout << " ";
        }
        
        if (count_destroy == len_ship) {
            std::cout << " " << "This ship is destroyed!";
        }

        std::cout << std::endl;
    }
}


Ship& ShipManager::getShip(int index) const {
    return *ships[index];
}