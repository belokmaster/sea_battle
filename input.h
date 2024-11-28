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

    int inputSingleNumber();
    vector<int> inputShipPlace();
    string inputFlag();
    pair<int, int> inputCoordinates();

};

#endif