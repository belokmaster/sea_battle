#include "ship.h"



Ship::Ship() : lenght(0), orientation(0){}
Ship::Ship(int lenght, int orientation){
    this -> lenght = lenght;
    this -> orientation = orientation;
    boat.resize(lenght, alive);
    coordinates.resize(2, 0);
}
int Ship::getlenght(){
    return this -> lenght;
}
int Ship::getorientation(){
    return this -> orientation;
}
vector<int> Ship::current_condition() {
    return this->boat;
}

void Ship::setsegment(vector<int> segment){
    this->boat = segment;
}
void Ship::attack(int i){
    if(boat[i] > 0){
        this -> boat[i] -= 1;
    }
}
void Ship::setorientation(int oreintation){
    this->orientation = oreintation;
}
void Ship::input_coordinates(int x, int y){
    this -> coordinates[0] = x;
    this -> coordinates[1] = y;
}
vector<int> Ship::getcoordinates() {
    return this->coordinates;
}
int Ship::dead_ship(){
    int summ = 0;
    for(int i = 0; i < this -> lenght; i++){
        summ += this -> boat[i];
    }
    if(summ == 0){
        return 1; 
    }
    else{
        return 0;
    }
}


