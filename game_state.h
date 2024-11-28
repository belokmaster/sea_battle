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
    Field** user_field;
    Field** opponent_field;
    shipManager** user_manager;
    shipManager** opponent_manager;
    AbilityManager** ability_manager;

public:
    GameState() = default;

    GameState(string filename, Field** user_field, Field** opponent_field, shipManager** user_manager, shipManager** opponent_manager, AbilityManager** ability_manager);

    json save();

    void save_to_file();

    void load_from_file();

    friend ofstream& operator<<(ofstream& os, GameState& state);

    void load(json& j);

    friend ifstream& operator>>(ifstream& is, GameState& state);
};

ofstream& operator<<(ofstream& os, GameState& state);

ifstream& operator>>(ifstream& os, GameState& state);

#endif