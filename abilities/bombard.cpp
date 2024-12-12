#include "bombard.h"
#include "../battleField.h"
#include "../shipManager.h"

void Bombard::apply(BattleField& filed, int x, int y, ShipManager& manager) {
    srand(time(NULL));

    if (manager.getShipsCount() > 0) {
        int random_index = rand() % manager.getShipsCount();
        Ship& target_ship = manager.getShip(random_index);
        
        int segment_index = rand() % target_ship.getLength();
        target_ship.attackSegment(segment_index);

        std::cout << "Bombard dealt damage to ship at number " << random_index + 1 
        << " segment " << segment_index + 1 << std::endl;
    } 
}