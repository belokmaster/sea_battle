#include "game_state.h"


GameState::GameState(string filename, Field** userField, Field** enemyField, shipManager** userManager, shipManager** enemyManager, AbilityManager** abilityManager) {
    this -> filename = filename;
    this -> userField = userField;
    this->enemyField = enemyField;
    this->userManager = userManager;
    this->enemyManager = enemyManager;
    this->abilityManager = abilityManager;
}

json GameState::save() {
    json j;
    j["userField"] = (*userField)->write_json();
    j["enemyField"] = (*enemyField)->write_json();
    j["userManager"] = (*userManager)->write_json();
    j["enemyManager"] = (*enemyManager) -> write_json();
    j["abilities"] = (*abilityManager) ->write_json();
    return j;
}

void GameState::load(json& j) {
    int size = (*userField)->load_json_size(j["userField"]);
    *userManager = (*userManager) ->load_json(j["userManager"]);
    (*userManager) -> load_from_json_ship(j["userManager"]["ships"]);
    *enemyManager = (*enemyManager) ->load_json(j["enemyManager"]);
    (*enemyManager) -> load_from_json_ship(j["enemyManager"]["ships"]);
    *userField = new Field(size, *userManager);
    *enemyField = new Field(size, *enemyManager);
    (*userField) ->load_json_field(j["userField"]);
    (*enemyField) ->load_json_field(j["enemyField"]);
    *abilityManager = new AbilityManager(*enemyField, *enemyManager);
    (*abilityManager) ->load_json_ability(j["abilities"]);
}

void GameState::save_to_file() {
    WorkFile workfile("state.json");
    ofstream& output = workfile.open_for_write();
    output << *this;
}

void GameState::load_from_file() {
    WorkFile workfile("state.json");
    ifstream& input = workfile.open_for_read();
    input >> *this;
}

ofstream& operator<<(ofstream& os, GameState& state) {
    json j = state.save();
    os << j.dump(4);
    return os;
}

ifstream& operator>>(ifstream& is, GameState& state) {
    string json_string((istreambuf_iterator<char>(is)), istreambuf_iterator<char>());
    json j = json::parse(json_string);
    state.load(j);
    return is;
}