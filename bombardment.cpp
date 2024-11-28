#include "bombardment.h"


Bombardment::Bombardment(Manager* managerfield, Field* field){
    this -> managerfield = managerfield;
    this -> field = field;
}

void Bombardment::use_ability(){
    srand(time(0));
    output.print_string("Используется способность Bombardment.\n");
    int random_ship = rand();
    random_ship = random_ship % managerfield -> getnumbership();
    vector<Ship>& array_ship = managerfield->getships();
    int random_segment = rand() % array_ship[random_ship].getlenght();
    array_ship[random_ship].attack(random_segment);
    int x = array_ship[random_ship].getcoordinates()[0];
    int y = array_ship[random_ship].getcoordinates()[1];
    if(array_ship[random_ship].getorientation() == 0){
        x = x + random_segment;
    }
    else{
        y = y + random_segment;
    }
    field->bombing(x, y);
    if(array_ship[random_ship].dead_ship() == 1){
        managerfield ->remove_ship(random_ship);
        cout << "Корабль убит." << '\n';
    }
}