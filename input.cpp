#include "input.h"


std::string Input::input_orientation(){
    std::string orientation;
    std::string input_s;

    while (true) {
        std::getline(std::cin, input_s);
        std::stringstream ss(input_s);
        if (!(ss >> orientation) || !ss.eof()) {
            output.error_message();
        }

        break;
        }

    return orientation;
}

bool Input::input_flag() {
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
                output.error_message();
            }
        
        } else {
            output.error_message();
        }
    }

    return flag;
}


std::pair<int, int> Input::input_two_ints() {
    int x, y;
    std::string input_s;

    while (true) {
        std::getline(std::cin, input_s);

        std::stringstream ss(input_s);

        if (ss >> x >> y && ss.eof()) {
            break;
        } else {
            output.error_message();
        }
    }

    return std::make_pair(x, y);
}
