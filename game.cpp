#include "game.h"


Game::Game() {}

void Game::downloading_previous_game() {
    output.printString("Если хотите загрузить предыдущую игру, введите L\n");
    string flag_load = input.inputFlag();
    if (flag_load == "L") {
        game_state = new GameState("state.json", &userField, &enemyField, &userManager, &enemyManager, &abilitymanager);
        load();
        size = userField ->getSize();
        ships.resize(4);
        countShip = 0;
        for (int i = 0; i < 4; i++) {
            ships[i] = userManager ->getLenShips()[i];
            countShip += ships[i];
        }
        make_move();
    }
    else {
        start_game();
        coordinates_ship();
        alignment_of_enemy_ships();
        make_move();
    }
}

void Game::start_game() {
    while(1) {
        try {
            output.printString("Введите размер поля: ");
            size = input.inputSingleNumber();
            if (size < 2 || size > 20) {
                throw IncorrectFieldSize("Ошибка ввода! Размер поля - это число от 2 до 20.");
            }
            break;
        } catch(IncorrectFieldSize& e) {
            output.printErrorString(e.what());
        }
    }
    output.printString("Игра морской бой начинается.\n");
    ships.resize(4);
    for (int i = 0; i < 4; i++) {
        while(1) {
            try {
                output.printCountShips(i+1);
                ships[i] = input.inputSingleNumber();
                if (ships[i] < 0 || ships[i] > 10) {
                    throw IncorrectQuantity("Ошибка ввода! Количество кораблей число от 0 до 10.");
                }
                break;
            } catch(IncorrectQuantity& e) {
                output.printErrorString(e.what());
            }
        }
    }
    countShip = ships[0] + ships[1] + ships[2] + ships[3];
}

void Game::coordinates_ship() {
    userManager = new shipManager(countShip, ships);
    userField = new Field(size, userManager);
    enemyManager = new shipManager(countShip, ships);
    enemyField = new Field(size, enemyManager);
    abilitymanager = new AbilityManager(enemyField, enemyManager);
    game_state = new GameState("state.json", &userField, &enemyField, &userManager, &enemyManager, &abilitymanager);
    userField->createField();
    int x;
    int y;
    int orientation;
    int flag_error;
    for (int j = 0; j < 4; j++) {
        if (ships[j] > 0) {
            output.printString("Введите координаты и ориентацию кораблей в формате x y 0, где 0 обозначет горизатльное расположение, а 1 вертикальное.\n");
        }
        for (int i = 0; i < ships[j]; i++) {
            flag_error = 0;
            output.printString("x y orientation: ");
            vector<int> coordinates = input.inputShipPlace();
            x = coordinates[0];
            y = coordinates[1];
            orientation = coordinates[2];
            while(1) {
                try {
                    if (flag_error == 0) {
                        userManager->createShip(j+1, orientation, x, y);
                        userField->putShip();
                    }
                    else {
                        Ship& current_ship = userManager->getShip();
                        current_ship.setOrientation(orientation);
                        current_ship.inputCoordinates(x, y);
                        userField->putShip();
                    }
                    break;
                } catch(IncorrectCoordinatesException& e) {
                    output.printErrorString(e.what());
                    flag_error = 1;
                    output.printString("x y orientation: ");
                    vector<int> coordinates = input.inputShipPlace();
                    x = coordinates[0];
                    y = coordinates[1];
                    orientation = coordinates[2];
                }
                catch(PlaceShipException& e) {
                    output.printErrorWithXy(e.what(), e.getxerror(), e.getyerror());
                    flag_error = 1;
                    output.printString("x y orientation: ");
                    vector<int> coordinates = input.inputShipPlace();
                    x = coordinates[0];
                    y = coordinates[1];
                    orientation = coordinates[2];
                }
            }
        }
    }
}

void Game::alignment_of_enemy_ships() {
    enemyField -> createField();
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, size - 1);
    int x;
    int y;
    int orientation;
    int flag_error = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < ships[i]; j++) {
            flag_error = 0;
            while(1) {
                try {
                    x = dist(gen);
                    y = dist(gen);
                    orientation = dist(gen) % 2;
                    if (flag_error == 0) {
                        enemyManager->createShip(i+1, orientation, x, y);
                        enemyField->putShip();
                    }
                    else {
                        Ship& current_ship = enemyManager->getShip();
                        current_ship.setOrientation(orientation);
                        current_ship.inputCoordinates(x, y);
                        enemyField->putShip();
                    }
                    break;
                } catch(IncorrectCoordinatesException& e) {
                    flag_error = 1;
                }
                catch(PlaceShipException& e) {
                    flag_error = 1;
                }
            }
        }
    }
}

void Game::attack_enemy() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, size - 1);
    int x = dist(gen);
    int y = dist(gen);
    while(1) {
        try {
            if (userField -> getCell(x, y) == Field::DEAD) {
                throw IncorrectCoordinatesException("туд уже стрелял бот");
            }
            userField -> attackSegment(x, y);
            break;
        } catch(IncorrectCoordinatesException& e) {
            x = dist(gen);
            y = dist(gen);
        }
    }
}

void Game::make_move() {
    string flag_save;
    string flag_ability;
    int number_ships = enemyManager->getNumberShip();
    int x, y, orientation;
    while(enemyManager -> getNumberShip() != 0 && userManager -> getNumberShip() != 0) {
        output.printFieldUser(userField, size);
        output.printString("\n");
        output.printFieldUser(enemyField, size); // поменять на enemy field для тумана 
        if (abilitymanager->isEmpty() == false) {
            output.printString( "Чтобы активировать спобность введите A\n");
            flag_ability = input.inputFlag();
            if (flag_ability == "A") {
                output.printString("Способность активирована!\n");
                abilitymanager->applyAbility();
                if (enemyManager->getNumberShip() == 0) {
                    reload_game();
                }
            }
        }
        output.printString("Введите координаты для атаки.\n");
        output.printString("x y: ");
        pair<int, int> coordinates = input.inputCoordinates();
        x = get<0>(coordinates);
        y = get<1>(coordinates);
        while(1) {
            try {
                enemyField->attackSegment(x, y);
                break;
            } catch(IncorrectCoordinatesException& e) {
                output.printErrorString(e.what());
                output.printString("x y: ");
                pair<int, int> coordinates = input.inputCoordinates();
                x = get<0>(coordinates);
                y = get<1>(coordinates);
            }
        }
        if (enemyManager->getNumberShip() == 0) {
            reload_game();
        }
        attack_enemy();
        if (number_ships - enemyManager->getNumberShip() >= 1) {
            abilitymanager->addAbility();
            number_ships = enemyManager->getNumberShip();
        }
        output.printString("Если хотите сохранить игру на данном моменте введите S, если хотите загрузить игру, введите Z\n");
        string flag = input.inputFlag();
        if (flag == "S") {
            save(); 
        } else if (flag == "Z") {
            load();
        }
    }
    reload_game();
}


void Game::reload_game() {
    string flag_reload;
    if (enemyManager -> getNumberShip() == 0) {
        output.printString("Вы выиграли, если хотите продолжить игру с новым соперником Y - Да, Other - Нет\n");
        flag_reload = input.inputFlag();
        if (flag_reload == "Y") {
            enemyManager->getShips().resize(countShip+1);
            alignment_of_enemy_ships();
            make_move();
        }
        else {
            output.printString("Игра окончена!");
            exit(0);
        }

    }
    else if (userManager -> getNumberShip() == 0) {
        output.printString("Вы проиграли, если хотите начать сначала Y - Да, Other - Нет\n");
        flag_reload = input.inputFlag();
        if (flag_reload == "Y") {
            start_game();
            coordinates_ship();
            alignment_of_enemy_ships();
            make_move();
        }
        else {
            output.printString("Игра окончена!");
            exit(0);
        }
    }
}

void Game::save() {
    game_state -> save_to_file();
}

void Game::load() {
    game_state -> load_from_file();
}