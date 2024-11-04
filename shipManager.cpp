#include "shipManager.h"


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
    for(int i = 0; i < ships.size(); i++) {
        Ship& ship = *ships[i];

        int len_ship = ship.getLength();
        int count_destroy = 0;

        std::cout << "Ship " << i + 1 <<": ";
        for(int i = 0; i < len_ship; i++) {
            int state = ship.getSegmentState(i);
            
            if(state == 0) {
                std::cout << "i";
            
            } else if (state == 1) {
                std::cout << "h";
            
            } else if (state == 2) {
                std::cout << "d";
                count_destroy++;
            }
            
            std::cout << " ";
        }
        
        if(count_destroy == len_ship) {
            std::cout << " " << "Ship destroyed";
        }

        std::cout << std::endl;
    }
}


Ship& ShipManager::getShip(int index) const {
    return *ships[index];
}