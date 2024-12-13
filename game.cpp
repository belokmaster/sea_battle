#include "game.h"


void Game::main_menu() {
    output.messageLoad();

    bool input_flag = input.inputBool();
    if (input_flag) {
        load_game();
        round();
    } else{
        start_game();
        generate_enemy_ships();
        round();
    }
}

void Game::start_game() {
    int width_field, height_field;
    output.enterSize();
    std::pair<int, int> size = input.inputCoords();

    std::tie(width_field, height_field) = size;
    
    user_field = BattleField(width_field, height_field);
    enemy_field = BattleField(width_field, height_field);

    user_field.gain_ability = false;
    enemy_field.gain_ability = true;

    enemy_manager = enemy_field.ship_quantity_preset();
    user_manager = user_field.ship_quantity_preset();
    int ships_count = user_field.ships_count;

    for (int i = 0; i < ships_count; ++i) {
        Ship& ship = user_manager.getShip(i);
        int x, y;
        std::string orientation;

        output.printPlayerField(user_field);

        output.messageShipCoords();
        std::pair<int, int> coordinates = input.inputCoords();

        std::tie(x, y) = coordinates;

        output.messageShipOrientation();
        orientation = input.inputOrientation();

        user_field.place_ship(ship, x, y, orientation);
    }

    output.printPlayerField(user_field);
}


void Game::generate_enemy_ships() {
    srand(static_cast<unsigned int>(time(NULL)));
    int width = enemy_field.getWidth();
    int height = enemy_field.getHeight();
    std::vector<std::vector<int>> cell_status(height, std::vector<int>(width, 0)); 
    
    for (int i = 0; i < enemy_manager.getShipsCount(); i++) {
        Ship& ship = enemy_manager.getShip(i);
        int length = ship.getLength();
        bool placed = false;
        
        while (!placed) {
            int x = rand() % width;
            int y = rand() % height;
            std::string orientation = (rand() % 2 == 0) ? "h" : "v"; 
            bool can_place = true;

            if (x > width || y > height || x < 0 || y < 0 || x + length > width || y + length > height) {
                continue; 
            }

            for (int j = 0; j < length; j++) {
                int check_x = (orientation == "h") ? x + j : x;
                int check_y = (orientation == "h") ? y : y + j;

                if (check_x >= 0 && check_x < width && check_y >= 0 && check_y < height) {
                    if (cell_status[check_y][check_x] != 0) {
                        can_place = false;
                        break; 
                    }
                } else {
                    can_place = false;
                    break;
                }
            }

            if (can_place) {
                for (int j = 0; j < length; j++) {
                    int place_x = (orientation == "h") ? x + j : x;
                    int place_y = (orientation == "h") ? y : y + j;
                    cell_status[place_y][place_x] = 1;
                }

                for (int j = -1; j <= length; j++) {
                    for (int k = -1; k <= 1; k++) {
                        int startX = (orientation == "v") ? x + k : x + j;
                        int startY = (orientation == "v") ? y + j : y + k;

                        if (startX >= 0 && startX < width && startY >= 0 && startY < height) {
                            cell_status[startY][startX] = 1;
                        }
                    }
                }  

                enemy_field.place_ship(ship, x, y, orientation); 
                placed = true; 
            }
        }
    }
    output.printPlayerField(enemy_field);
}

void Game::round() {
    bool save_flag;
    bool load_flag;
    bool ability_flag;

    int x = 0, y = 0;


    while(!enemy_manager.allDestroyed() && !user_manager.allDestroyed()) {
        std::string ability = ability_manager.nextAbility();
        output.printPlayerField(user_field);
        output.printEnemyField(enemy_field, enemy_manager);
        output.messageAbility(ability);
        ability_flag = false;

        if (ability != ""){
            ability_flag = input.inputBool();
        }
        if (ability_flag) {
            if (ability == "Scanner") {
                output.messageScanner();
                std::pair<int, int> coordinates = input.inputCoords();
                
                std::tie(x, y) = coordinates;
            }
            ability_manager.applyAbility(enemy_field, x, y, enemy_manager);
            if (enemy_manager.allDestroyed()) {
                new_game();
            }
        } else {
            output.messageAttackCoords();
            std::pair<int, int> coordinates = input.inputCoords();

            std::tie(x, y) = coordinates;
            
            output.messagePlayerAttack();
            enemy_field.attack(x, y, enemy_manager, ability_manager);

            if (enemy_manager.allDestroyed()) { 
                new_game();
            }
        }

        output.messageEnemyAttack();
        enemy_attack();

        save_flag = false;
        output.mesageSaveGame();
        save_flag = input.inputBool();
        if (save_flag) {
            save_game();
        }

        load_flag = false;
        output.mesageLoadGame();
        load_flag = input.inputBool();
        if (load_flag) {
            load_game();
        }

    }
    new_game();
}

void Game::enemy_attack() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist_x(0, user_field.getWidth() - 1);
    std::uniform_int_distribution<int> dist_y(0, user_field.getHeight() - 1);

    int x, y;

    do {
        x = dist_x(gen);
        y = dist_y(gen);
    } while (user_field.getCell(x, y) == 1);

    user_field.attack(x, y, user_manager, ability_manager);
}

void Game::new_game() {
    bool new_game_flag;
    if (enemy_manager.allDestroyed()) {
        output.messageWin();
        new_game_flag = input.inputBool();
        if (new_game_flag) {
            output.messageNewRound();
            enemy_manager.newShips();
            enemy_field.clean(); 
            generate_enemy_ships();
            round();
        } else {
            output.messageExit();
            exit(0);
        }

    } else if (user_manager.allDestroyed()) {
        output.messageLose();
        new_game_flag = input.inputBool();
        if (new_game_flag) {
            output.messageNewGame();
            start_game();
            generate_enemy_ships();
            round();
        } else{
            output.messageExit();
            exit(0);
        }
    }
}

void Game::save_game() {
    game_state.save(user_field, enemy_field, user_manager, enemy_manager, ability_manager);
}

void Game::load_game() {
    game_state.load(user_field, enemy_field, user_manager, enemy_manager, ability_manager);
}