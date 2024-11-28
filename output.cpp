#include "field.h"


void Output::print_string(string msg){
    cout << msg;
}

void Output::print_for_scanner(int x, int y, bool flag){
    if(flag){
        cout << "В квадрате (" << x << ", " << y << ") (" << x + 1 << ", " << y + 1 << ")" << " находится корабль."<<'\n';
    }
    else{
        cout << "В квадрате (" << x << ", " << y << ") (" << x + 1 << ", " << y + 1 << ")" << " корабля нет." << '\n';
    }
}

void Output::print_quantity_ships(int i){
    cout << "Введите количество кораблей. Длины " << i << ": ";
}

void Output::print_error_string(string msg){
    cerr << msg << '\n';
}

void Output::print_error_with_xy(string msg, int x, int y){
    cerr << msg << x << ' ' << y << '\n';
}

void Output::print_field_user(Field* field, int size){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(field->get_cell(j, i) == Field::unknown){
                cout << "*" << " ";
            }
            else{
                if(field->get_cell(j, i) == Field::fogwar){
                    cout << 1 << " ";
                }
                else{
                    cout << field->get_cell(j, i) << " ";
                }
            }
        }
        cout << '\n';
    }
}

void Output::print_field_opponent(Field* field, int size){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(field -> get_cell(j, i) == Field::unknown || field -> get_cell(j, i) == Field::alive || field -> get_cell(j, i) == Field::fogwar){
                cout << "*" << " ";
            }
            else{
                cout << field -> get_cell(j, i) << " ";
            }
        }
        cout << '\n';
    }
}