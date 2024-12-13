#include "output.h"


void Output::printPlayerField(BattleField user_field) {
    std::cout << "Your field: " << std::endl;

    std::cout << "   ";
    for (int x = 0; x < user_field.getWidth(); ++x) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    for (int y = 0; y < user_field.getHeight(); y++) {
        std::cout << y << "  ";

        for (int x = 0; x < user_field.getWidth(); x++) {
            if (user_field.getCell(y, x) == 2) {
                std::cout << "S ";
            
            } else if (user_field.getCell(y, x) == 0 || user_field.getCell(y, x) == 1) {
                std::cout << "~ ";
            }
        }
        std::cout << std::endl;
    }
}

void Output::printEnemyField(BattleField enemy_field, ShipManager& enemy_manager) {
    std::cout << "Enemy field: " << std::endl;

    std::cout << "   ";
    for (int x = 0; x < enemy_field.getWidth(); ++x) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    for (int y = 0; y < enemy_field.getHeight(); ++y) {
        std::cout << y << "  ";

        for (int x = 0; x < enemy_field.getWidth(); ++x) {
            bool is_damaged = false;
            bool is_hit = false;

            for (int i = 0; i < enemy_field.ships_count; ++i) {
                Ship& ship = enemy_manager.getShip(i);
                int ship_length = ship.getLength();
                bool is_vertical = ship.isVertical();

                if (is_vertical) {
                    if (x == ship.get_x()) {
                        for (int j = 0; j < ship_length; ++j) {
                            if (y == ship.get_y() + j) {
                                if (ship.getSegmentState(j) == 2) {
                                    is_damaged = true;
                                } else if (ship.getSegmentState(j) == 1) {
                                    is_hit = true;
                                }
                                break;
                            }
                        }
                    }
                } else {
                    if (y == ship.get_y()) {
                        for (int j = 0; j < ship_length; ++j) {
                            if (x == ship.get_x() + j) {
                                if (ship.getSegmentState(j) == 2) {
                                    is_damaged = true;
                                } else if (ship.getSegmentState(j) == 1) {
                                    is_hit = true;
                                }
                                break;
                            }
                        }
                    }
                }
                if (is_damaged || is_hit) break;
            }

            if (enemy_field.getCell(y, x) == 0) {
                std::cout << ". ";
            } else if (enemy_field.getCell(y, x) == 1) {
                std::cout << "~ ";
            } else if (is_damaged) {
                std::cout << "D ";
            } else if (is_hit) {
                std::cout << "H ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}

void Output::printCells(ShipManager& manager) {
    std::vector<std::unique_ptr<Ship>>& ships = manager.getShips();
    for (int i = 0; i < ships.size(); i++) {
        Ship& ship = *ships[i];

        int len_ship = ship.getLength();
        int count_destroy = 0;

        std::cout << "Ship " << i + 1 <<": ";
        for (int i = 0; i < len_ship; i++) {
            int state = ship.getSegmentState(i);
            
            if (state == 0) {
                std::cout << "I";
            
            } else if (state == 1) {
                std::cout << "H";
            
            } else if (state == 2) {
                std::cout << "D";
                count_destroy++;
            }
            
            std::cout << " ";
        }
        
        if (count_destroy == len_ship) {
            std::cout << " " << "Ship destroyed";
        }

        std::cout << std::endl;
    }
}

void Output::messageLoad() {
    std::cout << "Load a save? (y/n)" << std::endl;
}

void Output::enterSize() {
    std::cout << "Enter field width and height: ";
}

void Output::messageShipCoords() {
    std::cout << "Enter ship coordinates: ";
}

void Output::messageShipOrientation() {
    std::cout << "Enter ship orientation: ";
}

void Output::messageAbility(std::string ability) {
    if (ability == "") {
        std::cout << "There is no abilities to apply." << std::endl;
    } else {
        std::cout << "Next ability is " << ability << ". Do you want to use it? (y / n)" << std::endl;
    }
}

void Output::messageScanner() {
    std::cout << "Enter the coordinates of the top left corner of the square to be scanned: ";
}

void Output::messageAttackCoords() {
    std::cout << "Enter the coordinates to be attacked: ";
}

void Output::messagePlayerAttack() {
    std::cout << "Player attack: ";
}

void Output::messageEnemyAttack() {
    std::cout << "Enemy attack: ";
}

void Output::mesageSaveGame() {
    std::cout << "Do you want to save the game? (y / n)" << std::endl;
}

void Output::mesageLoadGame() {
    std::cout << "Do you want to load the game? (y / n)" << std::endl;
}

void Output::messageWin() {
    std::cout << "You won! Do you want to create the new game? (y / n)" << std::endl;
}

void Output::messageNewRound() {
    std::cout << "New round with another enemy >>>>" << std::endl;
}

void Output::messageLose() {
    std::cout << "You lost. Do you want to create the new game? (y / n)" << std::endl;
}

void Output::messageNewGame() {
    std::cout << "New game >>>>" << std::endl;
}

void Output::messageExit() {
    std::cout << "The game is over. See you soon!" << std::endl;
}

void Output::messageError() {
    std::cout << "Incorrect input! Enter again: ";
}