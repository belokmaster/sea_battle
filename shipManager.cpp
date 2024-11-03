#include "shipManager.h"


ShipManager::ShipManager(int count, const std::vector<int>& sizes) : count(count) {
    if (count != sizes.size()) {
        throw std::invalid_argument("Count of ships must match sizes vector.");
    }

    for (int size : sizes) {
        ships.emplace_back(std::make_unique<Ship>(size, size % 2 == 0));
    }
}

void ShipManager::print_states() {
    for(int i = 0; i < ships.size(); i++) {
        Ship& ship = *ships[i];

        int len_ship = ship.get_length();
        int count_destroy = 0;

        std::cout << "Ship " << i + 1 <<": ";
        for(int i = 0; i < len_ship; i++) {
            int state = ship.get_segment_state(i);
            
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

int ShipManager::get_ships_count() {
    return count;
}

Ship& ShipManager::get_ship(int index) const {
    return *ships[index];
}