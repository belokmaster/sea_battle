#include "exception.h"


GameException::GameException(const char* _Message) : invalid_argument(_Message) {}

InvalidFieldSizeException::InvalidFieldSizeException(const char* _Message) : GameException(_Message) {}

OutOfBoundsException::OutOfBoundsException(const char* _Message, int width_field, int height_field) : 
    GameException(_Message), width_field_state(width_field), height_field_state(height_field) {}


int OutOfBoundsException::get_height_state() {
    return height_field_state;
}

int OutOfBoundsException::get_width_state() {
    return width_field_state;
}

OrientationShipException::OrientationShipException(const char* _Message) : GameException(_Message) {}

InvalidShipPlacementException::InvalidShipPlacementException(const char* _Message, int coordinate_occupied_cell_x, int coordinate_occupied_cell_y) : 
    GameException(_Message), occupied_cell_x(coordinate_occupied_cell_x), occupied_cell_y(coordinate_occupied_cell_y) {}

int InvalidShipPlacementException::get_y_state() {
    return occupied_cell_y;
}

int InvalidShipPlacementException::get_x_state() {
    return occupied_cell_x;
}

NoAbilitiesException::NoAbilitiesException(const char* _Message) : GameException(_Message) {}
