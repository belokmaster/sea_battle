#include "input.h"


std::pair<int, int> Input::inputCoords() {
    int x, y;
    std::string input_s;
    while (true) {
        std::getline(std::cin, input_s);
        std::stringstream ss(input_s);

        if (ss >> x >> y && ss.eof()) {
            break;
        } 
        else {
            output.messageError();
        }
    }

    return std::make_pair(x, y);
}

std::string Input::inputOrientation(){
    std::string orientation;
    std::string input_s;

    while (true) {
        std::getline(std::cin, input_s);
        std::stringstream ss(input_s);
        if (!(ss >> orientation) || !ss.eof()) {
            output.messageError();
        }

        break;
        }
        
    return orientation;
}

bool Input::inputBool() {
    bool flag = false;
    std::string input_s;

    while (true) {
        std::getline(std::cin, input_s);
        std::stringstream ss(input_s);
        
        char temp;
        if (ss >> temp) {
            if (temp == 'y' || temp == 'Y') {
                flag = true;
                break;
            } else if (temp == 'n' || temp == 'N') {
                flag = false;
                break;  
            } else {
                output.messageError();
            }   
        } else {
            output.messageError();
        }
    }

    return flag;
}
