#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <vector>


class Ship {
enum Condition {
        DESTROYED, 
        SHOT, 
        ALIVE
    };

private:
    int lenght;
    int orientation;
    std::vector<int> boat;
    std::vector<int> coordinates;

public:
    Ship();
    Ship(int lenght, int orientation);

    int getLenght();
    int getOrientation();
    void setOrientation(int oreintation);
    std::vector<int> currentCondition();
    void getSegment(std::vector<int> segment);

    void attack(int i);
    int destroyedShip();
    void inputCoordinates(int x, int y);
    std::vector<int> getCoordinates();
};

#endif
