#include "scanner.h"
#include "../battleField.h"
#include "../shipManager.h"

void Scanner::apply(BattleField& field, int x, int y, ShipManager& manager) {
    bool found = false;

    for (int i = x; i < x + 2; ++i) {
        for (int j = y; j < y + 2; ++j) {
            if (i < field.getSize() && j < field.getSize()) {
                if (field.getCell(j, i) == 2) {
                    found = true;
                    break;
                }
            }
        }
        if (found) {
            break;
        }
    } 

    if (found) {
        std::cout << "Ship detected in the area" << std::endl;
    
    } else {
        std::cout << "No ships in the area" << std::endl;
    }
}