#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "field.h"
#include "ability_manager.h"
#include "work_with_file.h"
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;


class GameState{
private:
    string filename;
    json saved_game;
    Field** userField;
    Field** enemyField;
    shipManager** userManager;
    shipManager** enemyManager;
    AbilityManager** abilityManager;

public:
    GameState() = default;
    GameState(string filename, Field** userField, Field** enemyField, shipManager** userManager, shipManager** enemyManager, AbilityManager** abilityManager);

    json save();
    void load(json& j);
    void save_to_file();
    void load_from_file();

    friend ofstream& operator<<(ofstream& os, GameState& state);
    friend ifstream& operator>>(ifstream& is, GameState& state);
};

ofstream& operator<<(ofstream& os, GameState& state);
ifstream& operator>>(ifstream& os, GameState& state);

#endif