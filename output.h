#ifndef OUTPUT_H
#define OUTPUT_H


#include <iostream>
#include <sstream>
#include <string>
#include <utility>

class Field;

class Output{
public:
    Output() = default;

    void printString(std::string message);
    void printCountShips(int i);
    void printErrorString(std::string message);

    void printScanner(int x, int y, bool flag);
    void printErrorWithXy(std::string message, int x, int y);

    void printFieldUser(Field* field, int size);
    void printFieldEnemy(Field* field, int size);
};

#endif