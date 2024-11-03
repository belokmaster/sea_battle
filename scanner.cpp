#include "scanner.h"
#include "gameField.h"
#include "shipManager.h"

void Scanner::apply(GameField& field, int x, int y, ShipManager& manager) {
    bool found = false;

    for (int i = x; i < x + 2; ++i) {
        for (int j = y; j < y + 2; ++j) {
            if (i < field.get_height() && j < field.get_width()) {
                if (field.get_cell_status(j, i) == 2) {
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