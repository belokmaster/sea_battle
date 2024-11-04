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
            for (int i = 0; i < size; ++i) {
                field[i] = new cell[size];
                std::fill(field[i], field[i] + size, unknown_state);
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


BattleField::BattleField(const BattleField& other) : size(other.size), ships_count(other.ships_count) {
    field = new cell * [size];

    for (int i = 0; i < size; ++i) {
        field[i] = new cell[size];
        std::copy(other.field[i], other.field[i] + size, field[i]);
    }
}


BattleField::BattleField(BattleField&& other) noexcept : size(other.size), field(other.field), ships_count(other.ships_count) {
    other.field = nullptr;
}


BattleField::~BattleField() {
    for (int i = 0; i < size; ++i) {
        delete[] field[i];
    }
    delete[] field;
}


BattleField& BattleField::operator=(const BattleField& other) {
    if (this == &other) return *this;

    for (int i = 0; i < size; ++i) {
        delete[] field[i];
    }
    delete[] field;

    size = other.size;
    ships_count = other.ships_count;

    field = new cell * [size];
    for (int i = 0; i < size; ++i) {
        field[i] = new cell[size];
        std::copy(other.field[i], other.field[i] + size, field[i]);
    }

    return *this;
}


BattleField& BattleField::operator=(BattleField&& other) noexcept {
    if (this == &other) return *this;

    for (int i = 0; i < size; ++i) {
        delete[] field[i];
    }
    delete[] field;

    size = other.size;
    field = other.field;
    ships_count = other.ships_count;

    other.field = nullptr;

    return *this;
}


int BattleField::get_size() const {
    return size;
}


int BattleField::get_cell_status(int x, int y) {
    return field[y][x];
}


ShipManager BattleField::ship_quantity_preset() {
    int count_ships_cell = (size * size) / 5;
    std::vector<int> ship_sizes;

    if (count_ships_cell >= 20) {
        ship_sizes = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
        ships_count = 10;

    }
    else if (count_ships_cell >= 15) {
        ship_sizes = { 3, 3, 2, 2, 1, 1, 1 };
        ships_count = 7;

    }
    else {
        ship_sizes = { 2, 2, 1, 1 };
        ships_count = 4;
    }

    return ShipManager(ships_count, ship_sizes);
}


void BattleField::draw_all_field() {
    std::cout << "Ships on the field: " << std::endl;

    std::cout << "   ";
    for (int x = 0; x < size; ++x) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    for (int y = 0; y < size; y++) {
        std::cout << y << "  ";

        for (int x = 0; x < size; x++) {
            if (field[y][x] == ship_state) {
                std::cout << "S ";

            }
            else if (field[y][x] == unknown_state || field[y][x] == empty_state) {
                std::cout << "~ ";
            }
        }
        std::cout << std::endl;
    }
}


void BattleField::draw_enemy_field(ShipManager& manager) {
    std::cout << "Field: " << std::endl;

    std::cout << "   ";
    for (int x = 0; x < size; ++x) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    for (int y = 0; y < size; ++y) {
        std::cout << y << "  ";

        for (int x = 0; x < size; ++x) {
            bool is_hit = false;

            for (int i = 0; i < ships_count; ++i) {
                Ship& ship = manager.get_ship(i);
                int ship_length = ship.get_length();
                bool is_vertical = ship.is_orientation_vertical();

                if (is_vertical) {
                    if (x == ship.get_x()) {
                        for (int j = 0; j < ship_length; ++j) {
                            if (y == ship.get_y() + j && ship.get_segment_state(j) != 0) {
                                is_hit = true;
                                break;
                            }
                        }
                    }
                }
                else {
                    if (y == ship.get_y()) {
                        for (int j = 0; j < ship_length; ++j) {
                            if (x == ship.get_x() + j && ship.get_segment_state(j) != 0) {
                                is_hit = true;
                                break;
                            }
                        }
                    }
                }
                if (is_hit) break;
            }

            if (field[y][x] == unknown_state) {
                std::cout << ". ";
            }
            else if (field[y][x] == empty_state) {
                std::cout << "~ ";
            }
            else if (is_hit) {
                std::cout << "S ";
            }
            else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}


void BattleField::place_ship(Ship& ship, int x, int y, std::string orientation) {
    while (true) {
        try {
            if (orientation == "h" || orientation == "default") {
                ship.set_orientation(0);

            }
            else if (orientation == "v") {
                ship.set_orientation(1);
            }

            ship.set_x(x);
            ship.set_y(y);

            for (int i = 0; i < ship.get_length(); ++i) {
                int pos_x = ship.is_orientation_vertical() ? x : x + i;
                int pos_y = ship.is_orientation_vertical() ? y + i : y;

                if (pos_x >= size || pos_y >= size || pos_x < 0 || pos_y < 0 || field[pos_y][pos_x] == ship_state) {
                    throw InvalidShipPlacementException("Invalid ship placement.", x, y);
                }
            }

            for (int i = 0; i < ship.get_length(); ++i) {
                int pos_x = ship.is_orientation_vertical() ? x : x + i;
                int pos_y = ship.is_orientation_vertical() ? y + i : y;
                field[pos_y][pos_x] = ship_state;
            }

            break;

        }
        catch (OutOfBoundsException& e) {
            std::cout << "The field has a size of " << e.get_field_size() << std::endl;
            std::cerr << e.what() << std::endl;
            std::cout << "Enter ship coordinates and orientation again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> x >> y >> orientation;
            place_ship(ship, x, y, orientation);
        }
        catch (InvalidShipPlacementException& e) {
            std::cout << "The ship is already located at coordinates: "
                << e.get_x_state() << " " << e.get_y_state() << std::endl;
            std::cerr << e.what() << std::endl;
            std::cout << "Enter ship coordinates and orientation again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> x >> y >> orientation;
            place_ship(ship, x, y, orientation);
        }
        catch (OrientationShipException& e) {
            std::cerr << e.what() << std::endl;
            std::cout << "Enter ship coordinates and orientation again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> x >> y >> orientation;
            place_ship(ship, x, y, orientation);
        }
    }
}


void BattleField::attack(int x, int y, ShipManager& manager, AbilityManager& ability_manager) {
    while (true) {
        try {
            if (x < 0 || x >= size || y < 0 || y >= size) {
                throw OutOfBoundsException("Attack coordinates are out of bounds.", size);
            }

            for (int i = 0; i < ships_count; ++i) {
                Ship& ship = manager.get_ship(i);
                int ship_length = ship.get_length();
                bool is_vertical = ship.is_orientation_vertical();

                for (int j = 0; j < ship_length; ++j) {
                    int ship_x = is_vertical ? ship.get_x() : ship.get_x() + j;
                    int ship_y = is_vertical ? ship.get_y() + j : ship.get_y();

                    if (ship_x == x && ship_y == y) {
                        if (ship.get_segment_state(j) == 2) {
                            std::cout << "This segment is already destroyed." << std::endl;
                            return;
                        }
                        ship.damage_segment(j);
                        if (double_damage) {
                            ship.damage_segment(j);
                        }
                        if (get_double_damage()) {
                            set_double_damage(false);
                        }
                        if (ship.is_destroy()) {
                            ability_manager.gain_random_ability();
                        }
                        std::cout << "Hit!" << std::endl;
                        return;
                    }
                }
            }

            field[y][x] = empty_state;
            if (get_double_damage()) {
                set_double_damage(false);
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


bool BattleField::get_double_damage() {
    return double_damage;
}


void BattleField::set_double_damage(bool value) {
    double_damage = value;
}