#include "battleField.h"
#include "ship.h"
#include "shipManager.h"
#include "exception.h"
#include "abilityManager.h"


BattleField::BattleField(int width, int height) {
    while (true) {
        try {
            if (width > 20 || height > 20) {
                throw InvalidFieldSizeException("Too big field.");
            }
            if (width < 5 || height < 5) {
                throw InvalidFieldSizeException("Too small field.");
            }

            this->width = width;
            this->height = height;
            field = new cell*[height];
            for (int i = 0; i < height; ++i) {
                field[i] = new cell[width];
                std::fill(field[i], field[i] + width, unknown_state);
            }
            break;

        } catch (InvalidFieldSizeException& e) {
            std::cerr << e.what() << std::endl;
            std::cout << "Enter field width and height again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> width >> height;
        }
    }
}


BattleField::BattleField(const BattleField& other) : width(other.width), height(other.height), ships_count(other.ships_count) {
    field = new cell*[height];
    
    for (int i = 0; i < height; ++i) {
        field[i] = new cell[width];
        std::copy(other.field[i], other.field[i] + width, field[i]);
    }
}


BattleField::BattleField(BattleField&& other) noexcept : width(other.width), height(other.height), field(other.field), ships_count(other.ships_count) {
    other.field = nullptr;
}


BattleField& BattleField::operator=(const BattleField& other) {
    if (this == &other) return *this;

    for (int i = 0; i < height; ++i) {
        delete[] field[i];
    }
    delete[] field;

    width = other.width;
    height = other.height;
    ships_count = other.ships_count;

    field = new cell * [height];
    for (int i = 0; i < height; ++i) {
        field[i] = new cell[width];
        std::copy(other.field[i], other.field[i] + width, field[i]);
    }

    return *this;
}


BattleField& BattleField::operator=(BattleField&& other) noexcept {
    if (this == &other) return *this;

    for (int i = 0; i < height; ++i) {
        delete[] field[i];
    }
    delete[] field;

    width = other.width;
    height = other.height;
    field = other.field;
    ships_count = other.ships_count;

    other.field = nullptr;

    return *this;
}


BattleField::~BattleField() {
    for (int i = 0; i < height; ++i) {
        delete[] field[i];
    }
    delete[] field;
}


int BattleField::get_height() const {
    return height;
}


int BattleField::get_width() const {
    return width;
}


int BattleField::get_cell_status(int x, int y) {
    return field[x][y];
}


bool BattleField::get_double_damage() {
    return double_damage;
}


void BattleField::set_double_damage(bool value) {
    double_damage = value;
}


ShipManager BattleField::ship_quantity_preset() {
    int countCell = (width * height) / 5;
    std::vector<int> shipSizes;

    if (countCell >= 20) {
        shipSizes = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
        ships_count = 10;
    }
    else if (countCell >= 15) {
        shipSizes = { 3, 3, 2, 2, 1, 1, 1 };
        ships_count = 7;
    }
    else {
        shipSizes = { 2, 2, 1, 1 };
        ships_count = 4;
    }

    return ShipManager(ships_count, shipSizes);
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
            else {
                throw OrientationShipException("The ship must have horizontal (h) or vertical (v).");
            }

            int length = ship.get_length();

            if (x < 0 || y < 0 ||
                (ship.is_orientation_vertical() && (y + length - 1 >= height)) || (!ship.is_orientation_vertical() && (x + length - 1 >= width))) {
                throw OutOfBoundsException("The coordinates are out of the field.", width, height);
            }

            for (int i = -1; i <= length; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    int check_x = ship.is_orientation_vertical() ? x + j : x + i;
                    int check_y = ship.is_orientation_vertical() ? y + i : y + j;

                    if (check_y >= 0 && check_y < height && check_x >= 0 && check_x < width) {
                        if (field[check_y][check_x] != unknown_state) {
                            throw InvalidShipPlacementException("The place is occupied or too close to another ship.", check_x, check_y);
                        }
                    }
                }
            }

            if (ship.is_orientation_vertical()) {
                for (int i = 0; i < length; ++i) {
                    field[y + i][x] = ship_state;
                }
            }
            else {
                for (int i = 0; i < length; ++i) {
                    field[y][x + i] = ship_state;
                }
            }

            ship.set_x(x);
            ship.set_y(y);
            break;

        }
        catch (OutOfBoundsException& e) {
            std::cout << "The field has a width of " << e.get_width_state()
                << " and a height of " << e.get_height_state() << std::endl;
            std::cerr << e.what() << std::endl;
            std::cout << "Enter ship coordinates and orientation again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> x >> y >> orientation;
        }

        catch (InvalidShipPlacementException& e) {
            std::cout << "The ship is already located at coordinates: "
                << e.get_x_state() << " " << e.get_y_state() << std::endl;
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


void BattleField::draw_enemy_field(ShipManager& manager) {
    std::cout << "Field: " << std::endl;

    std::cout << "   ";
    for (int x = 0; x < width; ++x) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    for (int y = 0; y < height; ++y) {
        std::cout << y << "  ";

        for (int x = 0; x < width; ++x) {
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
                } else {
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
            } else if (field[y][x] == empty_state) {
                std::cout << "~ ";
            } else if (is_hit) {
                std::cout << "S ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}


void BattleField::draw_all_field() {
    std::cout << "Ships on the field: " << std::endl;

    std::cout << "   ";
    for (int x = 0; x < width; ++x) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    for (int y = 0; y < height; y++) {
        std::cout << y << "  ";

        for (int x = 0; x < width; x++) {
            if (field[y][x] == ship_state) {
                std::cout << "S ";
            
            } else if (field[y][x] == unknown_state || field[y][x] == empty_state) {
                std::cout << "~ ";
            }
        }
        std::cout << std::endl;
    }
}


void BattleField::attack(int x, int y, ShipManager& manager, AbilityManager& ability_manager) {
    while (true) {
        try {
            if (x < 0 || x >= width || y < 0 || y >= height) {
                throw OutOfBoundsException("Attack coordinates are out of bounds.", width, height);
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
            std::cout << "The field has a width of " << e.get_width_state()
                << " and a height of " << e.get_height_state() << std::endl;
            std::cerr << e.what() << std::endl;
            std::cout << "Enter attack coordinates again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> x >> y;
        }
    }
}