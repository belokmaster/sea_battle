#ifndef GAME_SESSION_H
#define GAME_SESSION_H

#include <iostream>
#include <vector>
#include <tuple>
using namespace std;
#include "field.h"
#include "ship.h"
#include "shipManager.h"
#include "game_state.h"


class GameSession{
private:
    shipManager* user_manager;
    shipManager* opponent_manager;
    Field* user_field;
    Field* opponent_field;
    AbilityManager* abilitymanager;
    Output output;
    Input input;
    GameState* game_state;
    int size;
    vector<int> ships;
    int qantity_ship;


public:
    GameSession();
    void downloading_previous_game();
    void start_game();
    void coordinates_ship();
    void alignment_of_enemy_ships();
    void attack_enemy();
    void make_move();
    void reload_game();
    void save();
    void load();
};

#endif