#include "battleField.h"
#include "ship.h"
#include "shipManager.h"


BattleField::BattleField(int size) : size(size) {
    if (size < 5 || size > 20) {
        throw std::invalid_argument("Field size must be between 5 and 20.");
    }

    field = new cell * [size];
    for (int i = 0; i < size; i++) {
        field[i] = new cell[size];
        std::fill(field[i], field[i] + size, NEAR_CELL);
    }
}

BattleField::BattleField(const BattleField& other) : size(other.size), shipsCount(other.shipsCount) {
    field = new cell * [size];

    for (int i = 0; i < size; i++) {
        field[i] = new cell[size];
        std::copy(other.field[i], other.field[i] + size, field[i]);
    }
}

BattleField::BattleField(BattleField&& other) noexcept : size(other.size), field(other.field), shipsCount(other.shipsCount) {
    other.field = nullptr;
}

BattleField::~BattleField() {
    for (int i = 0; i < size; i++) {
        delete[] field[i];
    }
    delete[] field;
}

BattleField& BattleField::operator=(const BattleField& other) {
    if (this == &other) return *this;

    for (int i = 0; i < size; i++) {
        delete[] field[i];
    }
    delete[] field;

    size = other.size;
    shipsCount = other.shipsCount;

    field = new cell * [size];
    for (int i = 0; i < size; i++) {
        field[i] = new cell[size];
        std::copy(other.field[i], other.field[i] + size, field[i]);
    }

    return *this;
}

BattleField& BattleField::operator=(BattleField&& other) noexcept {
    if (this == &other) return *this;

    for (int i = 0; i < size; i++) {
        delete[] field[i];
    }
    delete[] field;

    size = other.size;
    field = other.field;
    shipsCount = other.shipsCount;

    other.field = nullptr;

    return *this;
}

int BattleField::getSize() const {
    return size;
}


int BattleField::getDoubleDamage() const {
    return doubleDamage;
}


void BattleField::setDoubleDamage(bool value) {
    doubleDamage = value;
}


ShipManager BattleField::normalShipsCount() {
    int countCell = (size * size) / 5;
    std::vector<int> shipSizes;

    if (countCell >= 20) {
        shipSizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
        shipsCount = 10;
    }
    else if (countCell >= 15) {
        shipSizes = {3, 3, 2, 2, 1, 1, 1};
        shipsCount = 7;
    }
    else {
        shipSizes = {2, 2, 1, 1};
        shipsCount = 4;
    }

    return ShipManager(shipsCount, shipSizes);
}

void BattleField::drawField(ShipManager& manager) {
    std::cout << "\nField looks like this: \n\n";

    std::cout << "   ";
    for (int col = 0; col < size; col++) {
        if (col < 10) {
            std::cout << " " << col << " ";
        }
        else {
            std::cout << col << " ";
        }
    }
    std::cout << std::endl;

    for (int row = 0; row < size; row++) {
        if (row < 10) {
            std::cout << " " << row << " ";
        }
        else {
            std::cout << row << " ";
        }

        for (int col = 0; col < size; col++) {
            bool segmentHit = false;

            if (field[row][col] == SHIP_CELL) {
                for (int i = 0; i < manager.getShipsCount(); i++) {
                    Ship& ship = manager.getShip(i);
                    int shipLength = ship.getLength();
                    bool isVertical = ship.isVertical();

                    for (int j = 0; j < shipLength; j++) {
                        int ship_x, ship_y;
                        if (isVertical) {
                            ship_x = ship.get_x();
                            ship_y = ship.get_y() + j;
                        }
                        else {
                            ship_x = ship.get_x() + j;
                            ship_y = ship.get_y();
                        }

                        if (ship_x == col && ship_y == row) {
                            int segmentState = ship.getSegmentState(j);
                            if (segmentState == 2) {
                                std::cout << " D ";
                                segmentHit = true;
                            }
                            else if (segmentState == 1) {
                                std::cout << " X ";
                                segmentHit = true;
                            }
                            else {
                                std::cout << " S ";
                                segmentHit = true;
                            }
                            break;
                        }
                    }
                    if (segmentHit) break;
                }
            }

            if (!segmentHit) {
                if (field[row][col] == WATER_CELL) {
                    std::cout << " ~ ";
                }
                else {
                    std::cout << " . ";
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void BattleField::placeShip(Ship& ship, int col, int row, std::string orientation) {
    if (orientation == "h" || orientation == "H") {
        ship.setVertical(0);
    }
    else if (orientation == "v" || orientation == "V") {
        ship.setVertical(1);
    }
    else {
        throw std::invalid_argument("The ship must be horizontal(h / H) or vertical(v / V).");
    }

    int length = ship.getLength();

    if (col < 0 || row < 0 || (ship.isVertical() && (row + length - 1 >= size)) || (!ship.isVertical() && (col + length - 1 >= size))) {
        throw std::invalid_argument("The coordinates are out of the field.");
    }

    for (int y = -1; y <= length; y++) {
        for (int x = -1; x <= 1; x++) {
            int check_col, check_row;
            if (ship.isVertical()) {
                check_col = col + x;
                check_row = row + y;
            }
            else {
                check_col = col + y;
                check_row = row + x;
            }

            if (check_row >= 0 && check_row < size && check_col >= 0 && check_col < size) {
                if (field[check_row][check_col] != NEAR_CELL) {
                    throw std::invalid_argument("The place is occupied or too close to another ship.");
                }
            }
        }
    }

    for (int i = 0; i < length; ++i) {
        if (ship.isVertical()) {
            field[row + i][col] = SHIP_CELL;
        }
        else {
            field[row][col + i] = SHIP_CELL;
        }
    }

    ship.set_x(col);
    ship.set_y(row);
}

void BattleField::markAroundDestroyedShip(Ship& ship) {
    int ship_x = ship.get_x();
    int ship_y = ship.get_y();
    int length = ship.getLength();
    bool isVertical = ship.isVertical();

    for (int i = -1; i <= length; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int mark_x, mark_y;
            if (isVertical) {
                mark_x = ship_x + j;
                mark_y = ship_y + i;
            }
            else {
                mark_x = ship_x + i;
                mark_y = ship_y + j;
            }

            if (mark_y >= 0 && mark_y < size && mark_x >= 0 && mark_x < size) {
                if (field[mark_y][mark_x] == NEAR_CELL) {
                    field[mark_y][mark_x] = WATER_CELL;
                }
            }
        }
    }
}

void BattleField::attackShip(int col, int row, ShipManager& manager) {
    if (col < 0 || col >= size || row < 0 || row >= size) {
        throw std::out_of_range("Attack coordinates are out of bounds.");
    }

    for (int y = 0; y < shipsCount; y++) {
        Ship& ship = manager.getShip(y);
        int ship_length = ship.getLength();
        bool is_vertical = ship.isVertical();

        for (int x = 0; x < ship_length; x++) {
            int ship_x;
            int ship_y;

            if (is_vertical) {
                ship_x = ship.get_x();
                ship_y = ship.get_y() + x;
            }
            else {
                ship_x = ship.get_x() + x;
                ship_y = ship.get_y();
            }

            if (ship_x == col && ship_y == row) {
                if (ship.getSegmentState(x) == 2) {
                    std::cout << "This segment is already destroyed.\n";
                    return;
                }
                ship.attackSegment(x);
                std::cout << "Segment damaged!\n";

                if (ship.isDestroyed()) {
                    std::cout << "Ship is sunk!\n";
                    markAroundDestroyedShip(ship);
                }
                return;
            }
        }
    }

    field[row][col] = WATER_CELL;
    std::cout << "Miss!" << std::endl;
}
