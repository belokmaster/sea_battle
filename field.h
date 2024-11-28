#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include "shipManager.h"
#include "exception.h"
#include <vector>
#include "output.h"
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;



class Field {
public:
    enum Condition {
            DEAD, 
            SHOT, 
            ALIVE, 
            UNKNOWN, 
            FOGWAR
        };

private:
    int size;
    shipManager* managerfield; 
    Condition** fields;
    bool double_attack;
    Output output;

public:
    Field(int size, shipManager* managerfield);
    Field(const Field& other);
    Field(Field&& other);
    Field() = default;

    int isField(int x, int y);
    int isShip(int x, int y, int length, int orientation);
    int isClosely(int x, int y, int length, int orientation, bool first);

    void createField();
    void putShip();
    int getSize();

    void attackSegment(int x, int y, bool flag_bot=false);
    void setDoubleAttackFlag();
    void bombing(int x, int y);

    bool checkCell(int x, int y);
    Condition getCell(int x, int y);

    Field& operator=(const Field& other);
    Field& operator=(Field&& other);

    json write_json();
    int load_json_size(json j);
    void load_json_field(json j);

    void endGame();
    ~Field();
};
#endif 