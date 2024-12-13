#ifndef GAME_H
#define GAME_H

#include "exception.h"
#include "battleField.h"
#include "ship.h"
#include "abilityManager.h"
#include "shipManager.h"
#include "gameState.h"
#include "output.h"
#include "input.h"

#include <iostream>
#include <vector>
#include <tuple>
#include <random>


class Game{
private:
    BattleField user_field;
    BattleField enemy_field;

    ShipManager user_manager;
    ShipManager enemy_manager;

    AbilityManager ability_manager;

    Output output;
    Input input;

    GameState game_state;
public:
    Game() 
        : user_field(5, 5), 
          enemy_field(5, 5),
          enemy_manager(enemy_field.normalCountShips()),
          user_manager(user_field.normalCountShips()), 
          game_state("data_game.json") {}

    void main_menu();
    void start_game();

    void generate_enemy_ships();
    void enemy_attack();

    void round();
    void new_game();

    void save_game();
    void load_game();
};

#endif