#include "scanner.h"


Scanner::Scanner(Field* field) {
    this->field = field;
}

void Scanner::useAbility() {
    output.print_string("Используется способность Scanner.\n");
    output.print_string("x y: ");
    pair<int, int> coordinates = input.input_coordinates();
    x = get<0>(coordinates);
    y = get<1>(coordinates);
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            if(field->check_cell(x + i, y + j)){
                output.print_for_scanner(x, y, true);
                return;
            }
        }
    }
    output.print_for_scanner(x, y, false);
}

void Scanner::setcoordinates(int x, int y){
    this -> x = x;
    this -> y = y;
}