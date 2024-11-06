#include <iostream>
#include "game.h"

int main() {
    try {
        int size;
        std::cout << "Enter field size: ";
        std::cin >> size;

        BattleField field(size);
        AbilityManager ability_manager;
        ShipManager manager = field.normalShipsCount();

        placeShips(field, manager);
        gameLoop(field, manager, ability_manager);

    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
