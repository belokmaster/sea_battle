#include "game_state.h"


GameState::GameState(string filename, Field** user_field, Field** opponent_field, shipManager** user_manager, shipManager** opponent_manager, AbilityManager** ability_manager){
    this -> filename = filename;
    this -> user_field = user_field;
    this->opponent_field = opponent_field;
    this->user_manager = user_manager;
    this->opponent_manager = opponent_manager;
    this->ability_manager = ability_manager;
}


void GameState::save_to_file(){
    WorkFile workfile("state.json");
    ofstream& output = workfile.open_for_write();
    output << *this;
    //workfile.closeWrite();
}

void GameState::load_from_file(){
    WorkFile workfile("state.json");
    ifstream& input = workfile.open_for_read();
    input >> *this;
    //workfile.closeRead();
}

json GameState::save(){
    json j;
    j["user_field"] = (*user_field)->write_json();
    j["opponent_field"] = (*opponent_field)->write_json();
    j["user_manager"] = (*user_manager)->write_json();
    j["opponent_manager"] = (*opponent_manager) -> write_json();
    j["abilities"] = (*ability_manager) ->write_json();
    return j;
}

ofstream& operator<<(ofstream& os, GameState& state){
    json j = state.save();
    os << j.dump(4);
    return os;
}


void GameState::load(json& j){
    int size = (*user_field)->load_json_size(j["user_field"]);
    *user_manager = (*user_manager) ->load_json(j["user_manager"]);
    (*user_manager) -> load_from_json_ship(j["user_manager"]["ships"]);
    *opponent_manager = (*opponent_manager) ->load_json(j["opponent_manager"]);
    (*opponent_manager) -> load_from_json_ship(j["opponent_manager"]["ships"]);
    *user_field = new Field(size, *user_manager);
    *opponent_field = new Field(size, *opponent_manager);
    (*user_field) ->load_json_field(j["user_field"]);
    (*opponent_field) ->load_json_field(j["opponent_field"]);
    *ability_manager = new AbilityManager(*opponent_field, *opponent_manager);
    (*ability_manager) ->load_json_ability(j["abilities"]);
}



ifstream& operator>>(ifstream& is, GameState& state){
    string json_string((istreambuf_iterator<char>(is)), istreambuf_iterator<char>());
    json j = json::parse(json_string);
    state.load(j);
    return is;
}