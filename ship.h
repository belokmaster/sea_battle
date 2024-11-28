#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <vector>
using namespace std;


class Ship {
enum Condition {dead, shot, alive};
private:
    int lenght;
    int orientation;
    vector<int> boat;
    vector<int> coordinates;

public:
    Ship();
    Ship(int lenght, int orientation);
    int getlenght();
    int getorientation();
    vector<int> current_condition();
    void setsegment(vector<int> segment);
    void attack(int i);
    void setorientation(int oreintation);
    void input_coordinates(int x, int y);
    vector<int> getcoordinates();
    int dead_ship();
};

#endif
