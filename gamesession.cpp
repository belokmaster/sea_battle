#include "gamesession.h"


GameSession::GameSession(){}

void GameSession::downloading_previous_game(){
    output.print_string("Если хотите загрузить предыдущую игру, введите Y\n");
    string flag_load = input.input_flag();
    if(flag_load == "Y"){
        game_state = new GameState("state.json", &user_field, &opponent_field, &user_manager, &opponent_manager, &abilitymanager);
        load();
        size = user_field ->getsize();
        ships.resize(4);
        qantity_ship = 0;
        for(int i = 0; i < 4; i++){
            ships[i] = user_manager ->getLenShips()[i];
            qantity_ship += ships[i];
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

void GameSession::start_game(){
    while(1){
        try{
            output.print_string("Введите размер поля: ");
            size = input.input_single_number();
            if (size < 2 || size > 20) {
                throw IncorrectFieldSize("Ошибка ввода! Размер поля - это число от 2 до 20.");
            }
            break;
        } catch(IncorrectFieldSize& e){
            output.print_error_string(e.what());
        }
    }
    output.print_string("Игра морской бой начинается.\n");
    ships.resize(4);
    for(int i = 0; i < 4; i++){
        while(1){
            try{
                output.print_quantity_ships(i+1);
                ships[i] = input.input_single_number();
                if (ships[i] < 0 || ships[i] > 10) {
                    throw IncorrectQuantity("Ошибка ввода! Количество кораблей число от 0 до 10.");
                }
                break;
            } catch(IncorrectQuantity& e){
                output.print_error_string(e.what());
            }
        }
    }
    qantity_ship = ships[0] + ships[1] + ships[2] + ships[3];
}

void GameSession::coordinates_ship(){
    user_manager = new shipManager(qantity_ship, ships);
    user_field = new Field(size, user_manager);
    opponent_manager = new shipManager(qantity_ship, ships);
    opponent_field = new Field(size, opponent_manager);
    abilitymanager = new AbilityManager(opponent_field, opponent_manager);
    game_state = new GameState("state.json", &user_field, &opponent_field, &user_manager, &opponent_manager, &abilitymanager);
    user_field->create_field();
    int x;
    int y;
    int orientation;
    int flag_error;
    for(int j = 0; j < 4; j++){
        if(ships[j] > 0){
            output.print_string("Введите координаты и ориентацию кораблей в формате x y 0, где 0 обозначет горизатльное расположение, а 1 вертикальное.\n");
        }
        for(int i = 0; i < ships[j]; i++){
            flag_error = 0;
            output.print_string("x y orientation: ");
            vector<int> coordinates = input.input_ship_place();
            x = coordinates[0];
            y = coordinates[1];
            orientation = coordinates[2];
            while(1){
                try{
                    if(flag_error == 0){
                        user_manager->createShip(j+1, orientation, x, y);
                        user_field->put_ship();
                    }
                    else{
                        Ship& current_ship = user_manager->getShip();
                        current_ship.setOrientation(orientation);
                        current_ship.inputCoordinates(x, y);
                        user_field->put_ship();
                    }
                    break;
                } catch(IncorrectCoordinatesException& e){
                    output.print_error_string(e.what());
                    flag_error = 1;
                    output.print_string("x y orientation: ");
                    vector<int> coordinates = input.input_ship_place();
                    x = coordinates[0];
                    y = coordinates[1];
                    orientation = coordinates[2];
                }
                catch(PlaceShipException& e){
                    output.print_error_with_xy(e.what(), e.getxerror(), e.getyerror());
                    flag_error = 1;
                    output.print_string("x y orientation: ");
                    vector<int> coordinates = input.input_ship_place();
                    x = coordinates[0];
                    y = coordinates[1];
                    orientation = coordinates[2];
                }
            }
        }
    }
}

void GameSession::alignment_of_enemy_ships(){
    opponent_field -> create_field();
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, size - 1);
    int x;
    int y;
    int orientation;
    int flag_error = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < ships[i]; j++){
            flag_error = 0;
            while(1){
                try{
                    x = dist(gen);
                    y = dist(gen);
                    orientation = dist(gen) % 2;
                    if(flag_error == 0){
                        opponent_manager->createShip(i+1, orientation, x, y);
                        opponent_field->put_ship();
                    }
                    else{
                        Ship& current_ship = opponent_manager->getShip();
                        current_ship.setOrientation(orientation);
                        current_ship.inputCoordinates(x, y);
                        opponent_field->put_ship();
                    }
                    break;
                } catch(IncorrectCoordinatesException& e){
                    flag_error = 1;
                }
                catch(PlaceShipException& e){
                    flag_error = 1;
                }
            }
        }
    }
}

void GameSession::attack_enemy(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, size - 1);
    int x = dist(gen);
    int y = dist(gen);
    while(1){
        try{
            if(user_field -> get_cell(x, y) == Field::dead){
                throw IncorrectCoordinatesException("Бот уже стрялял сюда.");
            }
            user_field -> attack_segment(x, y);
            break;
        } catch(IncorrectCoordinatesException& e){
            x = dist(gen);
            y = dist(gen);
        }
    }
}


void GameSession::make_move(){
    string flag_save;
    string flag_ability;
    int number_ships = opponent_manager->getNumberShip();
    int x, y, orientation;
    while(opponent_manager -> getNumberShip() != 0 && user_manager -> getNumberShip() != 0){
        output.print_field_user(user_field, size);
        output.print_string("\n");
        output.print_field_user(opponent_field, size);
        if (abilitymanager->isEmpty() == false){
            output.print_string( "Чтобы активировать спобность введите Y\n");
            flag_ability = input.input_flag();
            if(flag_ability == "Y"){
                output.print_string("Активирована способность.\n");
                abilitymanager->applyAbility();
                if(opponent_manager->getNumberShip() == 0){
                    reload_game();
                }
            }
        }
        output.print_string("Введите координаты для атаки.\n");
        output.print_string("x y: ");
        pair<int, int> coordinates = input.input_coordinates();
        x = get<0>(coordinates);
        y = get<1>(coordinates);
        while(1){
            try{
                opponent_field->attack_segment(x, y);
                break;
            } catch(IncorrectCoordinatesException& e){
                output.print_error_string(e.what());
                output.print_string("x y: ");
                pair<int, int> coordinates = input.input_coordinates();
                x = get<0>(coordinates);
                y = get<1>(coordinates);
            }
        }
        if(opponent_manager->getNumberShip() == 0){
            reload_game();
        }
        attack_enemy();
        if(number_ships - opponent_manager->getNumberShip() >= 1){
            abilitymanager->addAbility();
            number_ships = opponent_manager->getNumberShip();
        }
        output.print_string("Если хотите сохранить игру на данном моменте введите Y\n");
        flag_save = input.input_flag();
        if (flag_save == "Y") {
            save();
        }
        // ЗДЕСЬ ДОЛЖНА БЫТЬ ЕЩЕ ЗАГРУЗКА 
    }
    reload_game();
}


void GameSession::reload_game(){
    string flag_reload;
    if(opponent_manager -> getNumberShip() == 0){
        output.print_string("Вы выиграли, хотите продолжить игру с новым соперником? Y - Да, Other - Нет\n");
        flag_reload = input.input_flag();
        if(flag_reload == "Y"){
            opponent_manager->getShips().resize(qantity_ship+1);
            alignment_of_enemy_ships();
            make_move();
        }
        else{
            output.print_string("Игра окончена!");
            exit(0);
        }

    }
    else if (user_manager -> getNumberShip() == 0){
        output.print_string("Вы проиграли, хотите начать сначала? Y - Да, Other - Нет\n");
        flag_reload = input.input_flag();
        if(flag_reload == "Y"){
            start_game();
            coordinates_ship();
            alignment_of_enemy_ships();
            make_move();
        }
        else{
            output.print_string("Игра окончена!");
            exit(0);
        }
    }
}

void GameSession::save() {
    game_state -> save_to_file();
}


void GameSession::load(){
    game_state -> load_from_file();
}