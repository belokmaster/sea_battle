#include "battleField.h"
#include "ship.h"
#include "shipManager.h"
#include "exception.h"
#include "abilityManager.h"


BattleField::BattleField(int size) {
    while (true) {
        try {
            if (size < 5 || size > 20) {
                throw InvalidFieldSizeException("Field size must be between 5 and 20.");
            }

            this->size = size;
            field = new cell * [size];
            for (int i = 0; i < size; i++) {
                field[i] = new cell[size];
                std::fill(field[i], field[i] + size, UNKNOWN_CELL);
            }
            break;

        }
        catch (InvalidFieldSizeException& e) {
            std::cerr << e.what() << std::endl;
            std::cout << "Enter field size again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> size;
        }
    }
}


BattleField::BattleField(const BattleField& other) : size(other.size), shipsCount(other.shipsCount) {
    field = new cell * [size];

    for (int i = 0; i < size; ++i) {
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


int BattleField::getCell(int x, int y) {
    return field[y][x];
}


ShipManager BattleField::normalShipsCount() {
    int countShipsCell = (size * size) / 5;
    std::vector<int> shipSizes;

    if (countShipsCell >= 20) {
        shipSizes = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
        shipsCount = 10;
    }
    else if (countShipsCell >= 15) {
        shipSizes = { 3, 3, 2, 2, 1, 1, 1 };
        shipsCount = 7;
    }
    else {
        shipSizes = { 2, 2, 1, 1 };
        shipsCount = 4;
    }

    return ShipManager(shipsCount, shipSizes);
}


void BattleField::drawField(ShipManager& manager, bool isEnemyField) {
    std::cout << "\nField looks like this: \n\n";

    std::cout << "   ";
    for (int x = 0; x < size; x++) {
        if (x < 10) {
            std::cout << " " << x << " ";
        }
        else {
            std::cout << x << " ";
        }
    }
    std::cout << std::endl;

    for (int y = 0; y < size; y++) {
        if (y < 10) {
            std::cout << " " << y << " ";
        }
        else {
            std::cout << y << " ";
        }

        for (int x = 0; x < size; x++) {
            bool segmentHit = false;
            bool shipPresent = false;

            if (field[y][x] == SHIP_CELL) {
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

                        if (ship_x == x && ship_y == y) {
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
                                shipPresent = true;
                            }
                            break;
                        }
                    }
                    if (segmentHit || shipPresent) break;
                }
            }

            if (!segmentHit && !shipPresent) {
                if (field[y][x] == EMPTY_CELL) {
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


void BattleField::placeShip(Ship& ship, int x, int y, std::string orientation) {
    while (true) {
        try {
            if (orientation == "h" || orientation == "H") {
                ship.setVertical(0);
            } 
            else if (orientation == "v" || orientation == "V") {
                ship.setVertical(1);     
            } 
            else {
                throw OrientationShipException("The ship must have horizontal (h / H) or vertical (v / V).");
            }

            int length = ship.getLength();
            if (x < 0 || y < 0 || (ship.isVertical() && (y + length - 1 >= size)) || (ship.isVertical() && (x >= size)) || (!ship.isVertical() && (x + length - 1 >= size))) {
                throw OutOfBoundsException("The coordinates are out of the field.", size);
            }

            for (int i = -1; i <= length; i++) {
                for (int j = -1; j <= 1; j++) {
                    int check_x = ship.isVertical() ? x + j : x + i;
                    int check_y = ship.isVertical() ? y + i : y + j;

                    if (check_y >= 0 && check_y < size && check_x >= 0 && check_x < size) {
                        if (field[check_y][check_x] != UNKNOWN_CELL) {
                            throw InvalidShipPlacementException("The place is occupied or too close to another ship.", check_x, check_y);
                        }
                    }
                }
            }

            if (ship.isVertical()) {
                for (int i = 0; i < length; ++i) {
                    field[y + i][x] = SHIP_CELL;
                }
            } 
            else {
                for (int i = 0; i < length; ++i) {
                    field[y][x + i] = SHIP_CELL;
                }
            }

            ship.set_x(x);
            ship.set_y(y);
            break;
        } 
        catch (OutOfBoundsException& e) {
            std::cout << "The field has a size of " << e.get_field_size() << std::endl;
            std::cerr << e.what() << std::endl;
            std::cout << "Enter ship coordinates and orientation again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> x >> y >> orientation;
        }
        catch (InvalidShipPlacementException& e) {
            std::cout << "The ship is already located at coordinates: " << e.get_x_state() << " " << e.get_y_state() << std::endl;
            std::cerr << e.what() << std::endl;
            std::cout << "Enter ship coordinates and orientation again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> x >> y >> orientation;
        }
        catch (OrientationShipException& e) {
            std::cerr << e.what() << std::endl;
            std::cout << "Enter ship coordinates and orientation again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> x >> y >> orientation;
        }
    }
}


void BattleField::attackShip(int x, int y, ShipManager& manager, AbilityManager& ability_manager) {
    while (true) {
        try {
            if (x < 0 || x >= size || y < 0 || y >= size) {
                throw OutOfBoundsException("Attack coordinates are out of bounds.", size);
            }

            for (int i = 0; i < shipsCount; ++i) {
                Ship& ship = manager.getShip(i);
                int ship_length = ship.getLength();
                bool is_vertical = ship.isVertical();

                for (int j = 0; j < ship_length; ++j) {
                    int ship_x;
                    int ship_y;

                    if (is_vertical) {
                        ship_x = ship.get_x();     
                        ship_y = ship.get_y() + j; 
                    }
                    else {
                        ship_x = ship.get_x() + j; 
                        ship_y = ship.get_y();  
                    }

                    if (ship_x == x && ship_y == y) {
                        if (ship.getSegmentState(j) == 2) {
                            std::cout << "This segment is already destroyed." << std::endl;
                            return;
                        }
                        ship.attackSegment(j);
                        if (doubleDamage) {
                            ship.attackSegment(j);
                        }
                        if (getDoubleDamage()) {
                            setDoubleDamage(false);
                        }
                        if (ship.isDestroyed()) {
                            std::cout << "Ship is sunk!" << std::endl;
                            markAroundDestroyedShip(ship);
                            ability_manager.gain_random_ability();
                        }
                        std::cout << "Hit!" << std::endl;
                        return;
                    }
                }
            }
            
            field[y][x] = EMPTY_CELL;
            if (getDoubleDamage()) {
                setDoubleDamage(false);
            }
            std::cout << "Miss!" << std::endl;
            return;

        }
        catch (OutOfBoundsException& e) {
            std::cout << "The field has a size of " << e.get_field_size() << std::endl;
            std::cerr << e.what() << std::endl;
            std::cout << "Enter attack coordinates again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> x >> y;
        }
    }
}


void BattleField::markAroundDestroyedShip(Ship& ship) {
    int ship_x = ship.get_x();
    int ship_y = ship.get_y();
    int length = ship.getLength();
    bool isVertical = ship.isVertical();

    for (int i = -1; i <= length; i++) {
        for (int j = -1; j <= 1; j++) {
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
                if (field[mark_y][mark_x] == UNKNOWN_CELL) {
                    field[mark_y][mark_x] = EMPTY_CELL;
                }
            }
        }
    }
}


bool BattleField::getDoubleDamage() {
    return doubleDamage;
}


void BattleField::setDoubleDamage(bool value) {
    doubleDamage = value;
}