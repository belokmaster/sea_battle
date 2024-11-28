#include "input.h"

int Input::input_single_number(){
    int one;
    string input_s;
    while(true){
        try{
            getline(cin, input_s);
            stringstream ss(input_s);
            if(!(ss >> one) || !ss.eof()){
                throw IncorrectFieldSize("Некорректные данныe, введите ещё раз!");
            }
            break;
        } catch(IncorrectFieldSize& e){
            output.print_error_string(e.what());
            //cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return one;
}

vector<int> Input::input_ship_place(){
    int x, y, orientation;
    string input_s;
    while(true){
        try{
            getline(cin, input_s);
            stringstream ss(input_s);
            if(!(ss >> x >> y >> orientation) || !ss.eof()){
                throw IncorrectCoordinatesException("Некорректные данныe, введите ещё раз!");
            }
            break;
        } catch(IncorrectCoordinatesException& e){
            output.print_error_string(e.what());
            //cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    vector<int> coordinates = {x, y, orientation};
    return coordinates;
}


string Input::input_flag(){
    string flag;
    string input_s;
    while(true){
        try{
            getline(cin, input_s);
            stringstream ss(input_s);
            if(!(ss >> flag) || ss.fail() || !ss.eof()){
                throw IncorrectFieldSize("Некорректные данныe, введите ещё раз!");
            }
            break;
        } catch(IncorrectFieldSize& e){
            output.print_error_string(e.what());
        }
    }
    return flag;
}


pair<int, int> Input::input_coordinates(){
    int x, y;
    string input_s;
    while(true){
        try{
            getline(cin, input_s);
            stringstream ss(input_s);
            if(!(ss >> x >> y) || ss.fail() || !ss.eof()){
                throw IncorrectFieldSize("Некорректные данныe, введите ещё раз!");
            }
            break;
        } catch(IncorrectFieldSize& e){
            output.print_error_string(e.what());
        }
    }
    return make_pair(x, y);
}