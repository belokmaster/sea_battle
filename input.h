#ifndef INPUT_H
#define INPUT_H

#include "exception.h"
#include "output.h"

#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <tuple>
#include <vector>


class Input{
private:
    Output output;
    
public:
    Input() = default;
    int input_single_number();

    std::pair<int, int> inputCoords();
    std::string inputOrientation();
    bool inputBool();
};

#endif