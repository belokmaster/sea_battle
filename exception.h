#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>

class GameException : public std::invalid_argument {
public:
    explicit GameException(const char* _Message);
};

class InvalidFieldSizeException : public GameException {
public:
    explicit InvalidFieldSizeException(const char* _Message);
};

class OutOfBoundsException : public GameException {
public:
    OutOfBoundsException(const char* _Message, int field_size);
    int get_field_size() const;

private:
    int field_size_state;
};

class OrientationShipException : public GameException {
public:
    explicit OrientationShipException(const char* _Message);
};

class InvalidShipPlacementException : public GameException {
public:
    InvalidShipPlacementException(const char* _Message, int coordinate_occupied_cell_x, int coordinate_occupied_cell_y);
    int get_x_state() const;
    int get_y_state() const;

private:
    int occupied_cell_x;
    int occupied_cell_y;
};

class NoAbilitiesException : public GameException {
public:
    explicit NoAbilitiesException(const char* _Message);
};

class InvalidShipLengthException : public GameException {
public:
    explicit InvalidShipLengthException(const char* _Message);
};

class InvalidSegmentIndexException : public std::out_of_range {
public:
    explicit InvalidSegmentIndexException(const char* message) : std::out_of_range(message) {}
};

#endif // EXCEPTION_H
