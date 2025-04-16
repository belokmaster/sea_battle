#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <tuple>

#include "field.h"
#include "ship.h"
#include "shipManager.h"
#include "gameState.h"

using namespace std;

class Game {
private:
    shipManager* userManager;
    shipManager* enemyManager;
    Field* userField;
    Field* enemyField;
    AbilityManager* abilitymanager;
    Output output;
    Input input;
    GameState* game_state;
    int size;
    vector<int> ships;
    int countShip;


public:
    Game();
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