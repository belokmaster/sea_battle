#include "output.h"


void Output::main_menu_message() {
    std::cout << "Load a save? (y/n)" << std::endl;
}

void Output::width_and_height_message() {
    std::cout << "Enter field width and height: ";
}

void Output::ship_coordinates_message() {
    std::cout << "Enter ship coordinates: ";
}

void Output::ship_orientation_message() {
    std::cout << "Enter ship orientation: ";
}

void Output::ability_message(std::string ability) {
    if (ability == "") {
        std::cout << "There is no abilities to apply." << std::endl;
    } else {
        std::cout << "Next ability is " << ability << ". Do you wanna use it? (y/n)" << std::endl;
    }
}

void Output::scanner_coordinates_message() {
    std::cout << "Enter the coordinates of the top left corner of the square to be scanned: ";
}

void Output::your_attack_message() {
    std::cout << "Your attack: ";
}

void Output::enemy_attack_message() {
    std::cout << "Enemy attack: ";
}

void Output::attack_message() {
    std::cout << "Enter the coordinates to be attacked: ";
}

void Output::save_message() {
    std::cout << "Do you wanna save the game? (y/n)" << std::endl;
}

void Output::load_message() {
    std::cout << "Do you wanna load the game? (y/n)" << std::endl;
}

void Output::win_message() {
    std::cout << "You won. Congrats! Do you wanna continue the game with another enemy? (y/n)" << std::endl;
}

void Output::new_round_message() {
    std::cout << "New round with another enemy >>>>" << std::endl;
}

void Output::defeat_message() {
    std::cout << "You lost. Do you wanna start from the beginning? (y/n)" << std::endl;
}

void Output::new_game_message() {
    std::cout << "New game >>>>" << std::endl;
}

void Output::exit_message() {
    std::cout << "The game is over. See you soon!" << std::endl;
}

void Output::error_message() {
    std::cout << "Incorrect input! Enter again: ";
}

void Output::print_user_field(BattleField user_field) {
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

void Output::print_enemy_field(BattleField enemy_field, ShipManager& enemy_manager) {
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

void Output::print_states(ShipManager& manager) {
    std::vector<std::unique_ptr<Ship>>& ships = manager.getShips();
    for(int i = 0; i < ships.size(); i++) {
        Ship& ship = *ships[i];

        int len_ship = ship.getLength();
        int count_destroy = 0;

        std::cout << "Ship " << i + 1 <<": ";
        for(int i = 0; i < len_ship; i++) {
            int state = ship.getSegmentState(i);
            
            if(state == 0) {
                std::cout << "I";
            
            } else if (state == 1) {
                std::cout << "H";
            
            } else if (state == 2) {
                std::cout << "D";
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