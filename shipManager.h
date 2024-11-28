#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include "ship.h" 
#include <vector>
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;


class shipManager {
private:
    int qantity_ship;
    vector<int> len_ships;
    vector<Ship> ships;
    int number_ships;

public:
    shipManager(int qantity_ship, vector<int> len_ships);

    shipManager() = default;

    void create_ship(int length, int orientation, int x, int y);

    vector<Ship>& getships();

    Ship& getship();

    vector<int> getlenships();

    int getnumbership();

    void remove_ship(int i);

    int getqantityship();

    json write_json();

    shipManager* load_json(json j);
    
    void load_from_json_ship(json j);

    ~shipManager();
};
#endif