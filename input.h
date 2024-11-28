#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <tuple>
#include <vector>
#include "exception.h"
#include "output.h"


class Input{
private:
    Output output;
public:
    Input() = default;

    int input_single_number();

    vector<int> input_ship_place();

    string input_flag();

    pair<int, int> input_coordinates();

};

#endif