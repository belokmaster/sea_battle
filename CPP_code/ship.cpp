#include "ship.h"



Ship::Ship() : lenght(0), orientation(0) {}

Ship::Ship(int lenght, int orientation) {
    this -> lenght = lenght;
    this -> orientation = orientation;
    boat.resize(lenght, ALIVE);
    coordinates.resize(2, 0);
}

int Ship::getLenght() {
    return this -> lenght;
}

int Ship::getOrientation() {
    return this -> orientation;
}

void Ship::setOrientation(int oreintation) {
    this->orientation = oreintation;
}

std::vector<int> Ship::currentCondition() {
    return this->boat;
}

void Ship::getSegment(std::vector<int> segment) {
    this->boat = segment;
}

void Ship::attack(int i) {
    if (boat[i] > 0) {
        this -> boat[i] -= 1;
    }
}

int Ship::destroyedShip() {
    int segments  = 0;
    for (int i = 0; i < this -> lenght; i++) {
        segments  += this -> boat[i];
    }
    if (segments  == 0) {
        return 1; 
    }
    else {
        return 0;
    }
}

void Ship::inputCoordinates(int x, int y) {
    this -> coordinates[0] = x;
    this -> coordinates[1] = y;
}

std::vector<int> Ship::getCoordinates() {
    return this->coordinates;
}


