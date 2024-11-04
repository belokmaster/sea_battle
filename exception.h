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
private:
    int field_size_state;

public:
    OutOfBoundsException(const char* _Message, int field_size);
    int get_field_size() const;
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
    InvalidShipPlacementException(const char* _Message, int coordinate_occupied_cell_x, int coordinate_occupied_cell_y);
    int get_y_state() const;
    int get_x_state() const;
};

class NoAbilitiesException : public GameException {
public:
    explicit NoAbilitiesException(const char* _Message);
};
