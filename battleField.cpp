#include "battleField.h"
#include "ship.h"
#include "shipManager.h"
#include "exception.h"
#include "abilityManager.h"


BattleField::BattleField(int width_f, int height_f) : width(width_f), height(height_f) {
    while (true) {
        try {
            if (width_f > 20 || height_f > 20) {
                throw InvalidFieldSizeException("Too big field.");
            }
            if (width_f < 5 || height_f < 5) {
                throw InvalidFieldSizeException("Too small field.");
            }

            this->width = width_f;
            this->height = height_f;
            field = new cell*[height_f];
            for (int i = 0; i < height_f; ++i) {
                field[i] = new cell[width_f];
                std::fill(field[i], field[i] + width_f, unknown_state);
            }
            break;

        } catch (InvalidFieldSizeException& e) {
            std::cerr << e.what() << std::endl;
            std::cout << "Enter field width and height again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> width_f >> height_f;
        }
    }
}

BattleField::BattleField(const BattleField& other) 
    : width(other.width), height(other.height), ships_count(other.ships_count) {
    field = new cell*[height];
    
    for (int i = 0; i < height; ++i) {
        field[i] = new cell[width];
        std::copy(other.field[i], other.field[i] + width, field[i]);
    }
}

BattleField::BattleField(BattleField&& other) noexcept : width(other.width), height(other.height), field(other.field), ships_count(other.ships_count) {
    other.field = nullptr;
}

void BattleField::attack(int x, int y, ShipManager& manager, AbilityManager& ability_manager) {
    while (true) {
        try {
            if (x < 0 || x >= width || y < 0 || y >= height) {
                throw OutOfBoundsException("Attack coordinates are out of bounds.", width, height);
            }

            for (int i = 0; i < ships_count; ++i) {
                Ship& ship = manager.getShip(i);
                int ship_length = ship.getLength();
                bool is_vertical = ship.isVertical();

                for (int j = 0; j < ship_length; ++j) {
                    int ship_x = is_vertical ? ship.get_x() : ship.get_x() + j;
                    int ship_y = is_vertical ? ship.get_y() + j : ship.get_y();

                    if (ship_x == x && ship_y == y) {
                        if (ship.getSegmentState(j) == 2) {
                            std::cout << "The attack was carried out on a destroyed segment." << std::endl;
                            return;
                        }
                        ship.attackSegment(j);
                        if(double_damage) {
                            ship.attackSegment(j);
                        }
                        if (get_double_damage()) {
                            set_double_damage(false);
                        }
                        if(ship.isDestroyed() && gain_ability) {
                            ability_manager.getRandomAbility();
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

        } catch (OutOfBoundsException& e) {
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


int BattleField::get_height() const {
    return height;
}

int BattleField::get_width() const {
    return width;
}

bool BattleField::get_double_damage() {
    return double_damage;
}

void BattleField::set_double_damage(bool value) {
    double_damage = value;
}

ShipManager BattleField::ship_quantity_preset() {
    int count_cell = width * height;
    int count_ships_cell = count_cell / 5;
    std::vector<int> ship_sizes;

    if (count_ships_cell >= 20) { 
        ship_sizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1}; 
        ships_count = 10;
    
    } else if (count_ships_cell >= 15) {
        ship_sizes = {3, 3, 2, 2, 1, 1, 1};
        ships_count = 7;
    
    } else {
        ship_sizes = {2, 2, 1, 1}; 
        ships_count = 4;
    }
    
    return ShipManager(ship_sizes.size(), ship_sizes);
}

void BattleField::place_ship(Ship& ship, int x, int y, std::string orientation) {
    while (true) {
        try {
            if (orientation == "h" || orientation == "") {
                ship.setVertical(0);
            
            } else if (orientation == "v") {
                ship.setVertical(1);
            
            } else {
                throw OrientationShipException("The ship must have horizontal (h) or vertical (v).");
            }

            int length = ship.getLength();

            if (x < 0 || y < 0 || 
                (ship.isVertical() && (y + length - 1 >= height)) || (!ship.isVertical() && (x + length - 1 >= width))) {
                throw OutOfBoundsException("The coordinates are out of the field.", width, height);
            }

            for (int i = -1; i <= length; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    int check_x = ship.isVertical() ? x + j : x + i;
                    int check_y = ship.isVertical() ? y + i : y + j;

                    if (check_y >= 0 && check_y < height && check_x >= 0 && check_x < width) {
                        if (field[check_y][check_x] != unknown_state) {
                            throw InvalidShipPlacementException("The place is occupied or too close to another ship.", check_x, check_y);
                        }
                    }
                }
            }

            if (ship.isVertical()) {
                for (int i = 0; i < length; ++i) {
                    field[y + i][x] = ship_state;
                }
            } else {
                for (int i = 0; i < length; ++i) {
                    field[y][x + i] = ship_state;
                }
            }

            ship.set_x(x);
            ship.set_y(y);
            break;
            
        } catch (OutOfBoundsException& e) {
            std::cout << "The field has a width of " << e.get_width_state() 
                      << " and a height of " << e.get_height_state() << std::endl;  
            std::cerr << e.what() << std::endl;
            std::cout << "Enter ship coordinates again: ";
            std::cin.clear();
            //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> x >> y;
            std::cout << "Enter ship orientation again: ";
            std::cin >> orientation;
        } 

        catch (InvalidShipPlacementException& e) {
            std::cout << "The ship is already located at coordinates: "
                      << e.get_x_state() << " " <<  e.get_y_state() << std::endl;
            std::cerr << e.what() << std::endl;
            std::cout << "Enter ship coordinates and orientation again: ";
            std::cin.clear();
            //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> x >> y;
            std::cout << "Enter ship orientation again: ";
            std::cin >> orientation;
        }

        catch (OrientationShipException& e) {
            std::cerr << e.what() << std::endl;
            std::cout << "Enter ship coordinates and orientation again: ";
            std::cin.clear();
            //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> x >> y;
            std::cout << "Enter ship orientation again: ";
            std::cin >> orientation;
        }
    }
}

int BattleField::get_cell_status(int x, int y) {
    return field[x][y];
}

void BattleField::clean() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) { 
            field[y][x] = unknown_state;
        }
    }
}

BattleField& BattleField::operator=(BattleField&& other) noexcept {
    if (this != &other) {

        for (int i = 0; i < height; ++i) {
            delete[] field[i];
        }
        delete[] field;

        width = other.width;
        height = other.height;
        field = other.field;
        ships_count = other.ships_count;

        other.field = nullptr;
        other.width = 0;
        other.height = 0;
        other.ships_count = 0;
    }
    return *this;
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

    field = new cell*[height];
    for (int i = 0; i < height; ++i) {
        field[i] = new cell[width];
        std::copy(other.field[i], other.field[i] + width, field[i]);
    }
    
    return *this;
}

json BattleField::to_json() const {
    json j;
    j["width"] = width;
    j["height"] = height;
    j["gain_ability"] = gain_ability;

    for (int i = 0; i < height; ++i) {
        std::vector<int> row;
        for (int j = 0; j < width; ++j) {
            row.push_back(static_cast<int>(field[i][j]));
        }
        j["field"].push_back(row);
    }

    return j;
}

BattleField BattleField::from_json_size(const json& j) {
    BattleField field(j["width"], j["height"]);
    field.gain_ability = (j["gain_ability"]);
    return field;
}

void BattleField::from_json_coord(const json& j) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) { 
            field[y][x] = j["field"][y][x];
        }
    }
}

BattleField::~BattleField() {
    for (int i = 0; i < height; ++i) {
        delete[] field[i];
    }
    delete[] field;
}