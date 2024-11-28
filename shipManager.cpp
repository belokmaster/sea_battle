#include "shipManager.h"


shipManager::shipManager(int countShips, std::vector<int> lenShips) {
    this -> countShips = countShips;
    this -> lenShips = lenShips;
    ships.resize(countShips);
    this -> number_ships = 0;
}

void shipManager::createShip(int lenght, int orientation, int x , int y) {
    ships[this->number_ships] = Ship(lenght, orientation);
    ships[this->number_ships].inputCoordinates(x, y);
    this->number_ships += 1;
}

std::vector<Ship>& shipManager::getShips() {
    return this->ships;
}

Ship& shipManager::getShip() {
    return this->ships[this->number_ships - 1];
}

std::vector<int> shipManager::getLenShips() {
    return this->lenShips;
}

int shipManager::getNumberShip() {
    return this->number_ships;
}

void shipManager::removeShip(int i) {
    if (i < this->number_ships && i >= 0) {
        ships.erase(ships.begin() + i);
        this -> number_ships -= 1;
    }
}

int shipManager::getCountShips() {
    return this -> countShips;
}

json shipManager::write_json() {
    json j;
    json array_ship = json::array();

    int x_ship; 
    int y_ship; 
    int lengthShip; 
    int oreintationShip;

    std::vector<int> segmentShip;
    Ship currentShip;
    j["number_ship"] = this -> number_ships;
    j["lenShips"] = this -> lenShips;

    for (int i = 0; i < this -> number_ships; i++) {
        currentShip = ships[i];
        lengthShip = currentShip.getLenght();
        segmentShip = currentShip.currentCondition();
        x_ship = currentShip.getCoordinates()[0];
        y_ship = currentShip.getCoordinates()[1];
        oreintationShip = currentShip.getOrientation();

        json length = {"lenght", lengthShip};
        json x = {"x", x_ship};
        json y = {"y", y_ship};
        json oreintation = {"oreintation", oreintationShip};
        json segment = {"segments", segmentShip};

        array_ship.push_back({length, x, y, oreintation, segment});
    }
    j["ships"] = array_ship;
    return j;
}

shipManager* shipManager::load_json(json j) {
    int number_ship = j["number_ship"];
    std::vector<int> lenShips;
    lenShips.resize(4);
    auto lenShips_json = j["lenShips"];
    for (int i = 0; i < 4; i++) {
        lenShips[i] = lenShips_json[i];
    }
    shipManager* manager = new shipManager(number_ship, lenShips);
    return manager;
}

void shipManager::load_from_json_ship(json j) {
    for(int i = 0; i < countShips; i++) {
        int length = j[i]["lenght"];
        int x = j[i]["x"];
        int y = j[i]["y"];
        int oreintation = j[i]["oreintation"];
        auto segment_json = j[i]["segments"];
        std::vector<int> segment;
        segment.resize(length);
        for (int j = 0; j < length; j++) {
            segment[j] = segment_json[j];
        }
        createShip(length, oreintation, x, y);
        Ship& current_ship = getShip();
        current_ship.getSegment(segment);
    }
}

shipManager::~shipManager(){}

