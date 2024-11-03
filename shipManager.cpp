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

Ship& ShipManager::getShip(int index) const {
    return *ships[index];
}