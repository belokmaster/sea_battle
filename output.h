#ifndef OUTPUT_H
#define OUTPUT_H


#include <iostream>
#include <sstream>
#include <string>
#include <utility>
using namespace std;

class Field;

class Output{
public:
    Output() = default;

    void print_string(string msg);

    void print_for_scanner(int x, int y, bool flag);

    void print_quantity_ships(int i);

    void print_error_string(string msg);

    void print_error_with_xy(string msg, int x, int y);

    void print_field_user(Field* field, int size);

    void print_field_opponent(Field* field, int size);
};

#endif