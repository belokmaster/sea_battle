#include "exception.h"

GameException::GameException(const char* _Message) : invalid_argument(_Message) {}

InvalidFieldSizeException::InvalidFieldSizeException(const char* _Message) : GameException(_Message) {}

OutOfBoundsException::OutOfBoundsException(const char* _Message, int field_size) :
    GameException(_Message), field_size_state(field_size) {}

int OutOfBoundsException::get_field_size() const {
    return field_size_state;
}

OrientationShipException::OrientationShipException(const char* _Message) : GameException(_Message) {}

InvalidShipPlacementException::InvalidShipPlacementException(const char* _Message, int coordinate_occupied_cell_x, int coordinate_occupied_cell_y) :
    GameException(_Message), occupied_cell_x(coordinate_occupied_cell_x), occupied_cell_y(coordinate_occupied_cell_y) {}

int InvalidShipPlacementException::get_x_state() const {
    return occupied_cell_x;
}

int InvalidShipPlacementException::get_y_state() const {
    return occupied_cell_y;
}

NoAbilitiesException::NoAbilitiesException(const char* _Message) : GameException(_Message) {}

InvalidShipLengthException::InvalidShipLengthException(const char* _Message) : GameException(_Message) {}
