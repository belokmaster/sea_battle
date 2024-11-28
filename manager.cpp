#include "manager.h"


Manager::Manager(int qantity_ship, vector<int> len_ships){
    this -> qantity_ship = qantity_ship;
    this -> len_ships = len_ships;
    ships.resize(qantity_ship);
    this -> number_ships = 0;
}
void Manager::create_ship(int lenght, int orientation, int x , int y){
    ships[this->number_ships] = Ship(lenght, orientation);
    ships[this->number_ships].input_coordinates(x, y);
    this->number_ships += 1;
}
vector<Ship>& Manager::getships(){
    return this->ships;
}

Ship& Manager::getship(){
    return this->ships[this->number_ships - 1];
}

vector<int> Manager::getlenships(){
    return this->len_ships;
}

int Manager::getnumbership(){
    return this->number_ships;
}
void Manager::remove_ship(int i){
    if(i < this->number_ships && i >= 0){
        ships.erase(ships.begin() + i);
        this -> number_ships -= 1;
    }
}
int Manager::getqantityship(){
    return this -> qantity_ship;
}

json Manager::write_json(){
    json j;
    json array_ship = json::array();
    int x_ship, y_ship, length_ship, oreintation_ship;
    vector<int> segment_ship;
    Ship current_ship;
    j["number_ship"] = this -> number_ships;
    j["len_ships"] = this -> len_ships;

    for(int i = 0; i < this -> number_ships; i++){
        current_ship = ships[i];
        length_ship = current_ship.getlenght();
        segment_ship = current_ship.current_condition();
        x_ship = current_ship.getcoordinates()[0];
        y_ship = current_ship.getcoordinates()[1];
        oreintation_ship = current_ship.getorientation();
        json length = {"lenght", length_ship};
        json x = {"x", x_ship};
        json y = {"y", y_ship};
        json oreintation = {"oreintation", oreintation_ship};
        json segment = {"segments", segment_ship};
        array_ship.push_back({length, x, y, oreintation, segment});
    }
    j["ships"] = array_ship;
    return j;
}

Manager* Manager::load_json(json j) {
    int number_ship = j["number_ship"];
    vector<int> len_ships;
    len_ships.resize(4);
    auto len_ships_json = j["len_ships"];
    for(int i = 0; i < 4; i++){
        len_ships[i] = len_ships_json[i];
    }
    Manager* manager = new Manager(number_ship, len_ships);
    return manager;
}

void Manager::load_from_json_ship(json j){
    for(int i = 0; i < qantity_ship; i++){
        int length = j[i]["lenght"];
        int x = j[i]["x"];
        int y = j[i]["y"];
        int oreintation = j[i]["oreintation"];
        auto segment_json = j[i]["segments"];
        vector<int> segment;
        segment.resize(length);
        for(int j = 0; j < length; j++){
            segment[j] = segment_json[j];
        }
        create_ship(length, oreintation, x, y);
        Ship& current_ship = getship();
        current_ship.setsegment(segment);
    }
}

Manager::~Manager(){}

