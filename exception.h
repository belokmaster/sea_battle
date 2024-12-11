#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <stdexcept>


class GameException : public std::invalid_argument {
public: 
    GameException(const char* _Message);
};

class InvalidFieldSizeException : public GameException {
public:
    explicit InvalidFieldSizeException(const char* _Message);
};

class OutOfBoundsException : public GameException {
private:
    int height_field_state;
    int width_field_state;
public:
    explicit OutOfBoundsException(const char* _Message, int width_field, int height_field);
    int get_height_state();
    int get_width_state();
};

class OrientationShipException : public GameException {
public:
    explicit OrientationShipException(const char* _Message);
};

class InvalidShipPlacementException : public GameException {
private:
    int occupied_cell_x;
    int occupied_cell_y;
public:
    explicit InvalidShipPlacementException(const char* _Message, int occupied_cell_x, int occupied_cell_y);
    int get_y_state();
    int get_x_state();
};

class NoAbilitiesException : public GameException {
public:
    explicit NoAbilitiesException(const char* _Message);
};

#endif
