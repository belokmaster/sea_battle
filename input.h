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

    std::pair<int, int> input_two_ints();

    std::string input_orientation();

    bool input_flag();

};

#endif