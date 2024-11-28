#include "field.h"


Field::Field(int size, shipManager* managerfield) {
    this->size = size;
    this -> managerfield = managerfield;
    this -> double_attack = 0;
    this -> fields = new Condition*[size];
    for (int i = 0; i < size; i++) {
        this -> fields[i] = new Condition[size];
    }
}

Field::Field(const Field& other) {
    this->size = other.size;
    this->fields = new Condition*[size];
    for (int i = 0; i < size; i++) {
        this->fields[i] = new Condition[size];
        for (int j = 0; j < size; j++) {
            this->fields[i][j] = other.fields[i][j];
        }
    }
}

Field::Field(Field&& other) {
    this->size = other.size;
    this->fields = other.fields;
    other.size = 0;
    other.fields = nullptr;
}

int Field::isField(int x, int y) {
    if (x < 0 || y < 0 || x >= this->size || y >= this->size) {
        return 0;
    }
    return 1;
}

int Field::isShip(int x, int y, int lenght, int orientation) {
    for (int i = 0; i < lenght; i++) {
        if (orientation == 0) {
            if (this->fields[y][x + i] == ALIVE) {
                return 0;
            }
        }
        else {
            if (this->fields[y + i][x] == ALIVE) {
                return 0;
            }
        }
    }
    return 1;
}

int Field::isClosely(int x, int y, int lenght, int orientation, bool first) {
    int checkx;
    int checky;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if ((i == 0 && j == 0)) {
                continue;
            }
            checkx = x + i;
            checky  = y + j;
            if ((isField(checkx, checky) == 0) || (i == 1 && j == 0 && orientation == 0 && first == 1 && lenght != 1) || (i == -1 && j == 0 && orientation == 0 && first == 0 && lenght != 1)) {
                continue;
            }
            if ((i == 0 && j == 1 && orientation == 1 && first == 1 && lenght != 1) || (i == 0 && j == -1 && orientation == 1 && first == 0 && lenght != 1)) {
                continue;
            }
            if (this->fields[checky][checkx] == ALIVE) {
                return 0;
            }
        }
    }
    return 1;
}

void Field::createField() {
    for (int i = 0; i < this -> size; i++) {
        for (int j = 0; j < this -> size; j++) {
            this->fields[i][j] = UNKNOWN;
        }
    }
}

void Field::putShip() {
    Ship& current_ship = managerfield->getShip();
    vector<int> coordinates = current_ship.getCoordinates();
    
    if (isField(coordinates[0], coordinates[1]) == 0) {
        throw IncorrectCoordinatesException("Координата находится за пределами поля!");
    }

    int orientation = current_ship.getOrientation();
    if (orientation != 0 && orientation != 1) {
        throw IncorrectCoordinatesException("Ошибка ввода! Неправильная ориентация.");
    }

    int lenght = current_ship.getLenght();
    if (isClosely(coordinates[0], coordinates[1], lenght, orientation, 1) == 0) {
        throw PlaceShipException("На этих координатх или близко к ним уже стоит корабль: ", coordinates[0], coordinates[1]);
    }

    if (orientation == 0) {
        if (isClosely(coordinates[0] + lenght - 1, coordinates[1], lenght, orientation, 0) == 0) {
            throw PlaceShipException("На этих координатх или близко к ним уже стоит корабль: ", coordinates[0] + lenght - 1, coordinates[1]);
        }
        if (isField(coordinates[0] + lenght - 1, coordinates[1]) == 0) {
            throw IncorrectCoordinatesException("Координата находится за пределами поля!");
        }   
    }
    else {
        if (isClosely(coordinates[0], coordinates[1] + lenght - 1, lenght, orientation, 0) == 0) {
            throw PlaceShipException("На этих координатх или близко к ним уже стоит корабль: ", coordinates[0], coordinates[1] + lenght - 1);
        }
        if (isField(coordinates[0], coordinates[1] + lenght - 1) == 0) {
            throw IncorrectCoordinatesException("Координата находится за пределами поля!");
        }
    }

    if (isShip(coordinates[0], coordinates[1], lenght, orientation) == 0) {
        throw PlaceShipException("На этих координатх или близко к ним уже стоит корабль: ", coordinates[0], coordinates[1]);
    }

    for (int l = 0; l < lenght; l++) {
        if (orientation == 0) {
            this ->fields[coordinates[1]] [coordinates[0] + l] = ALIVE;
        }
        else {
            this ->fields[coordinates[1] + l][coordinates[0]] = ALIVE;
        }
    }
}

int Field::getSize() {
    return this->size;
}

void Field::attackSegment(int x, int y, bool flag_bot) {
    if (isField(x, y) == 0) {
        throw IncorrectCoordinatesException("Координата за пределами поля.");
    }
    else {
        if (this->fields[y][x] == ALIVE || this->fields[y][x] == SHOT || this->fields[y][x] == FOGWAR) {
            if (this->fields[y][x] == ALIVE) {
                if (double_attack == true) {
                    this->fields[y][x] = DEAD;
                }
                else {
                    this->fields[y][x] = SHOT;
                    if (flag_bot) {
                        output.printString("Корабль ранен.\n");
                    }
                }
            }
            else if (this->fields[y][x] == SHOT || this->fields[y][x] == FOGWAR) {
                this->fields[y][x] = DEAD;
            }
            vector<Ship>& array_ship = managerfield->getShips();
            int quantity = managerfield->getNumberShip();
            for (int i = 0; i < quantity; i++) {
                vector<int> coordinates = array_ship[i].getCoordinates();;
                int orientation = array_ship[i].getOrientation();
                int lenght = array_ship[i].getLenght();
                for (int l = 0; l < lenght; l++) {
                    if (orientation == 0) {
                        if (coordinates[0] + l == x && coordinates[1] == y) {
                            array_ship[i].attack(l);
                            if (double_attack == true) {
                                array_ship[i].attack(l);
                            }
                            if (array_ship[i].destroyedShip() == 1) {
                                managerfield ->removeShip(i);
                                if (flag_bot) {
                                    output.printString("Корабль убит.\n");
                                }
                            }
                            double_attack = 0;
                            return;
                        }
                    }
                    else {
                        if (coordinates[0] == x && coordinates[1] + l == y) {
                            array_ship[i].attack(l);
                            if (double_attack == true) {
                                array_ship[i].attack(l);
                            }
                            if (array_ship[i].destroyedShip() == 1) {
                                managerfield ->removeShip(i);
                                if (flag_bot) {
                                    output.printString("Корабль убит.\n");
                                }
                            }
                            double_attack = 0;
                            return;
                        }
                    }
                }
            }
        }
        else if (this->fields[y][x] == UNKNOWN || this->fields[y][x] == DEAD) {
            this->fields[y][x] = DEAD;
            if (flag_bot) {
                output.printString("Промах.\n");
            }
        }
    }
    double_attack = 0;
}

void Field::setDoubleAttackFlag() {
    this->double_attack = 1;
}

void Field::bombing(int x, int y) {
    if (isField(x, y)) {
        if (this->fields[y][x] == ALIVE) {
            this->fields[y][x] = FOGWAR;
        }
        else if (this->fields[y][x] == SHOT || this->fields[y][x] == FOGWAR) {
            this->fields[y][x] = DEAD;
        }
    }
    else {
        output.printString("Координаты за предалами поля.\n");
    }
}

bool Field::checkCell(int x, int y) {
    if (isField(x, y)) {
        if (this -> fields[y][x] == ALIVE || this -> fields[y][x] == SHOT || this -> fields[y][x] == FOGWAR) {
            return true;
        }
    }
    return false;
}

Field::Condition Field::getCell(int x, int y) {
    return this->fields[y][x];
}

Field& Field::operator=(const Field& other) {
    if (this != &other) {
        for (int i = 0; i < size; ++i) {
            delete[] fields[i];
        }
        delete[] fields;
        this->size = other.size;
        this->fields = new Condition*[size];
        for (int i = 0; i < size; i++) {
            this->fields[i] = new Condition[size];
            for (int j = 0; j < size; j++) {
                this->fields[i][j] = other.fields[i][j];
            }
        }
    }
    return *this;
}

Field& Field::operator=(Field&& other) {
    if (this != &other) {
        for (int i = 0; i < size; ++i) {
            delete[] fields[i];
        }
        delete[] fields;
        this->size = other.size;
        this->fields = other.fields;
        other.size = 0;
        other.fields = nullptr;
    }
    return *this;
}

json Field::write_json() {
    json j;
    j["size"] = this -> size;
    for (int i = 0; i < this -> size; i++) {
        vector<int> column;
        for (int k = 0; k < this -> size; k++) {
            column.push_back(static_cast<int>(fields[k][i]));
        }
        j["field"].push_back(column);
    }
    return j;
}

int Field::load_json_size(json j) {
    int size = j["size"];
    return size;
}

void Field::load_json_field(json j) {
    for (int i = 0; i < size; i++) {
        for (int k = 0; k < size; k ++) {
            fields[k][i] = static_cast<Condition>(j["field"][i][k]);
        }
    }
}

void Field::endGame() {
    if (managerfield->getNumberShip() == 0) {
        output.printString("the end.\n");
        exit(0);
    }
}

Field::~Field() {
    for (int i = 0; i < size; i++) {
        delete[] fields[i];
    }
    delete[] fields;
}