#include "bombard.h"
#include "../battleField.h"
#include "../shipManager.h"

void Bombard::apply(BattleField& filed, int x, int y, ShipManager& manager) {
    srand(time(NULL));

    if(manager.get_ships_count() > 0) {
        int random_index = rand() % manager.get_ships_count();
        Ship& target_ship = manager.get_ship(random_index);
        int segment_index = rand() % target_ship.get_length();
        target_ship.damage_segment(segment_index);

        std::cout << "Bombard dealt damage to ship at number " << random_index + 1 
        << " segment " << segment_index + 1 << std::endl;
    } 
}