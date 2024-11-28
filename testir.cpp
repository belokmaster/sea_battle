#include <iostream>
#include <vector>
using namespace std;


class Ship {
enum Condition {dead, shot, alive};
private:
    int lenght;
    bool orientation;
    vector<int> boat;
    vector<int> coordinates;

public:
    Ship() : lenght(0), orientation(0){};
    Ship(int lenght, bool orientation){
        if(lenght > 4 || lenght < 1) {
            cout << "Длина корабля должна быть от 1 до 4\n";
            exit(0);
        }
        this -> lenght = lenght;
        this -> orientation = orientation;
        boat.resize(lenght, alive);
        coordinates.resize(2, 0);
    }
    int getlenght(){
        return this -> lenght;
    }
    bool getorientation(){
        return this -> orientation;
    }
    vector<int> current_condition() {
        return this->boat;
    }
    void attack(int i){
        this -> boat[i] -= 1;
    }
    void input_coordinates(int x, int y){
        this -> coordinates[0] = x;
        this -> coordinates[1] = y;
    }
    vector<int> getcoordinates() {
        return this->coordinates;
    }
    int dead_ship(){
        int summ = 0;
        for(int i = 0; i < this -> lenght; i++){
            summ += this -> boat[i];
        }
        if(summ == 0){
            return 1; 
        }
        else{
            return 0;
        }
    }
};

class Manager{
private:
    int qantity_ship;
    int* len_ships;
    Ship* ships;
    int number_ships;
public:
    Manager(int qantity_ship, int* len_ships){
        this -> qantity_ship = qantity_ship;
        this -> len_ships = len_ships;
        this -> ships = new Ship[qantity_ship];
        this -> number_ships = 0;

    }
    void create_ship(int lenght, bool orientation, int x , int y){
        ships[number_ships] = Ship(lenght, orientation);
        ships[number_ships].input_coordinates(x, y);
        number_ships += 1;
    }
    Ship* getships(){
        return this->ships;
    }
    int getnumbership(){
        return this->number_ships;
    }
    ~Manager(){
        delete[] ships;
    }
};

class Field{
enum Condition {dead, shot, alive, unknown};
private:
    int size;
    Manager* managerfield;
    int** fields;
public:
    Field(int size, Manager* managerfield){
        this->size = size;
        this -> managerfield = managerfield;
        this -> fields = new int*[size];
        for(int i = 0; i < size; i++){
            this -> fields[i] = new int[size];
        }
    }

    Field(const Field& other) {
        this->size = other.size;
        this->fields = new int*[size];
        for (int i = 0; i < size; i++) {
            this->fields[i] = new int[size];
            for (int j = 0; j < size; j++) {
                this->fields[i][j] = other.fields[i][j];
            }
        }
    }

    Field(Field&& other) {
            this->size = other.size;
            this->fields = other.fields;
            other.size = 0;
            other.fields = nullptr;
    }

    int is_field(int x, int y){
        if(x < 0 || y < 0 || x >= this->size || y >= this->size){
            return 0;
        }
        return 1;
    }

    int is_ship(int x, int y, int lenght, bool orientation){
        for(int i = 0; i < lenght; i++){
            if(orientation == 0){
                if(this->fields[y][x + i] == alive){
                    return 0;
                }
            }
            else{
                if(this->fields[y + i][x] == alive){
                    return 0;
                }
            }
        }
        return 1;
    }
    int is_closely(int x, int y, int lenght, bool orientation, bool first){
        int checkx;
        int checky;
        for(int i = -1; i < 2; i++){
            for(int j = -1; j < 2; j++){
                if((i == 0 && j == 0)){
                    continue;
                }
                checkx = x + i;
                checky  = y + j;
                if((is_field(checkx, checky) == 0) || (i == 1 && j == 0 && orientation == 0 && first == 1 && lenght != 1) || (i == -1 && j == 0 && orientation == 0 && first == 0 && lenght != 1)){
                    continue;
                }
                if((i == 0 && j == 1 && orientation == 1 && first == 1 && lenght != 1) || (i == 0 && j == -1 && orientation == 1 && first == 0 && lenght != 1)){
                    continue;
                }
                if(this->fields[checky][checkx] == alive){
                    cout << "Корабль слишком близко к другому!" << '\n';
                    return 0;
                }
            }
        }
        return 1;
    }
    int create_field(){
        for(int i = 0; i < this -> size; i++){
            for(int j = 0; j < this -> size; j++){
                this->fields[i][j] = unknown;
            }
        }
        Ship* array_ship = managerfield->getships();
        int quantity = managerfield->getnumbership();
        for(int k = 0; k < quantity; k++){
            vector<int> coordinates = array_ship[k].getcoordinates();
            if(is_field(coordinates[0], coordinates[1]) == 0){
                cout << "Координата находится за пределами поля!" << " " << coordinates[0] << " " << coordinates[1] << '\n';
                return 0;
            }
            bool orientation = array_ship[k].getorientation();
            int lennght = array_ship[k].getlenght();
            if(is_ship(coordinates[0], coordinates[1], lennght, orientation) == 0){
                cout << "Вы пытаетесь поставить корабль на другой корабль!" << '\n';
                return 0;
            }
            if(is_closely(coordinates[0], coordinates[1], lennght, orientation, 1) == 0){
                cout << "Вы пытаетесь поставить корабль слишком близко к другому!" << '\n';
                return 0;
            }
            if(orientation == 0){
                if(is_closely(coordinates[0] + lennght - 1, coordinates[1], lennght, orientation, 0) == 0){
                    cout << "Вы пытаетесь поставить корабль слишком близко к другому!" << '\n';
                    return 0;
                }
                if(is_field(coordinates[0] + lennght - 1, coordinates[1]) == 0){
                    cout << "Координата находится за пределами поля!" << " " << coordinates[0] << " " << coordinates[1] << '\n';
                    return 0;
                }
               
            }
            else{
                if(is_closely(coordinates[0], coordinates[1] + lennght - 1, lennght, orientation, 0) == 0){
                    cout << "Вы пытаетесь поставить корабль слишком близко к другому!" << '\n';
                    return 0;
                }
                if(is_field(coordinates[0], coordinates[1] + lennght - 1) == 0){
                    cout << "Координата находится за пределами поля!" << " " << coordinates[0] << " " << coordinates[1] << '\n';
                    return 0;
                }
            }
            for(int l = 0; l < lennght; l++){
                if(orientation == 0){
                        this ->fields[coordinates[1]] [coordinates[0] + l] = alive;
                }
                else{
                    this ->fields[coordinates[1] + l][coordinates[0]] = alive;
                }
            }
        }
        return 1;
    }
    void end_game(){
        int k = 0;
        Ship*  array_ship = managerfield->getships();
        for(int i = 0; i < managerfield->getnumbership(); i++){
            if(array_ship[i].dead_ship() == 0){
                break;
            }
            else{
                k += 1;
            }
        }
        if(k == managerfield->getnumbership()){
            cout << "the end." << '\n';
            exit(0);
        }
    }
    void attack_segment(int x, int y){
        if(is_field(x, y) == 0){
            cout << "Нет такой координаты." << '\n';
        }
        else{
            if(this->fields[y][x] == alive || this->fields[y][x] == shot){
                Ship* array_ship = managerfield->getships();
                int quantity = managerfield->getnumbership();
                for(int i = 0; i < quantity; i++){
                    vector<int> coordinates = array_ship[i].getcoordinates();;
                    bool orientation = array_ship[i].getorientation();
                    int lennght = array_ship[i].getlenght();
                    for(int l = 0; l < lennght; l++){
                        if(orientation == 0){
                            if(coordinates[0] + l == x && coordinates[1] == y){
                                array_ship[i].attack(l);
                                if(array_ship[i].dead_ship() == 1){
                                    cout << "Корабль убит." << '\n';
                                    end_game();
                                }
                            }
                        }
                        else{
                            if(coordinates[0] == x && coordinates[1] + l == y){
                                array_ship[i].attack(l);
                                if(array_ship[i].dead_ship() == 1){
                                    cout << "Корабль убит." << '\n';
                                    end_game();
                                }
                            }
                        }
                    }
                }
                if(this->fields[y][x] == alive){
                    this->fields[y][x] = shot;
                    cout << "Корабль ранен." << '\n';
                }
                else if(this->fields[y][x] == shot){
                    this->fields[y][x] = dead;
                }
            }
            else if(this->fields[y][x] == unknown){
                this->fields[y][x] = dead;
                cout << "Промах." << '\n';
            }
        }
    }
    void print_field_user(){
        for(int i = 0; i < this -> size; i++){
            for(int j = 0; j < this -> size; j++){
                if(this->fields[i][j] == unknown){
                    cout << "*" << " ";
                }
                else{
                    cout << this->fields[i][j] << " ";
                }
            }
            cout << '\n';
        }
    }
    void print_field_opponent(){
        for(int i = 0; i < this -> size; i++){
            for(int j = 0; j < this -> size; j++){
                if(this->fields[i][j] == unknown || this->fields[i][j] == alive){
                    cout << "*" << " ";
                }
                else{
                    cout << this->fields[i][j] << " ";
                }
            }
            cout << '\n';
        }
    }
    ~Field(){
        for (int i = 0; i < size; i++) {
            delete[] fields[i];
        }
        delete[] fields;
    }
};


int is_field(int x, int y, int size){
        if(x < 0 || y < 0 || x >= size || y >= size){
            return 0;
        }
        return 1;
    }

int main(){
    int size = -1;
    int flag_field;
    while(size < 2){
        cout << "Введите размер поля: ";
        cin >> size;
    }
    int ships[4];
    int x, y;
    bool oreintation;
    cout << "Игра морской бой начинается." << '\n';
    cout << "Введите количество однопалубных кораблей." << '\n';
    cin >> ships[0];
    cout << "Введите количество двухпалубных кораблей." << '\n';
    cin >> ships[1];
    cout << "Введите количество трехпалубных кораблей." << '\n';
    cin >> ships[2];
    cout << "Введите количество четырехпалубных кораблей." << '\n';
    cin >> ships[3];
    int qantity_ship = ships[0] + ships[1] + ships[2] + ships[3];
    Manager managers(qantity_ship, ships);
    if(ships[0] > 0){
        cout << "Введите координаты и ориентацию однопалубных кораблей в формате x y 0, где 0 обозначет горизатльное расположение, а 1 вертикальное." << '\n';
    }
    int flag = 0;
    for(int i = 0; i < ships[0]; i++){
        while(flag == 0){
            cout << "x y oreintation: ";
            cin >> x >> y >> oreintation;
            flag = is_field(x, y, size);
            if(flag == 0){
                cout << "Координаты выходят за поле! Введите их заново." << '\n';
            }
        }
        flag = 0;
        managers.create_ship(1, oreintation, x, y);
    }
    if(ships[1] > 0){
        cout << "Введите координаты и ориентацию двухпалубных кораблей в формате x y 0, где 0 обозначет горизатльное расположение, а 1 вертикальное." << '\n';
    }
    flag = 0;
    for(int i = 0; i < ships[1]; i++){
        while(flag == 0){
            cout << "x y oreintation: ";
            cin >> x >> y >> oreintation;
            flag = is_field(x, y, size);
            if(flag == 0){
                cout << "Координаты выходят за поле! Введите их заново." << '\n';
            }
        }
        flag = 0;
        managers.create_ship(2, oreintation, x, y);
    }
    if(ships[2] > 0){
        cout << "Введите координаты и ориентацию трехпалубных кораблей в формате x y 0, где 0 обозначет горизатльное расположение, а 1 вертикальное." << '\n';
    }
    for(int i = 0; i < ships[2]; i++){
        while(flag == 0){
            cout << "x y oreintation: ";
            cin >> x >> y >> oreintation;
            flag = is_field(x, y, size);
            if(flag == 0){
                cout << "Координаты выходят за поле! Введите их заново." << '\n';
            }
        }
        flag = 0;
        managers.create_ship(3, oreintation, x, y);
    }
    if(ships[3] > 0){
        cout << "Введите координаты и ориентацию четырехпалубных кораблей в формате x y 0, где 0 обозначет горизатльное расположение, а 1 вертикальное." << '\n';
    }
    for(int i = 0; i < ships[3]; i++){
        while(flag == 0){
            cout << "x y oreintation: ";
            cin >> x >> y >> oreintation;
            flag = is_field(x, y, size);
            if(flag == 0){
                cout << "Координаты выходят за поле! Введите их заново." << '\n';
            }
        }
        flag = 0;
        managers.create_ship(4, oreintation, x, y);
    }
    Field userfield(size, &managers);
    flag_field = userfield.create_field();
    if(flag_field == 0){
        cout << "При расстановке произошла ошибка." << '\n';
        return 0;
    }
    while(1){
        cout << "Введите координаты для атаки." << '\n';
        cout << "x y: ";
        cin >> x >> y;
        userfield.attack_segment(x,y);
        userfield.print_field_user();
    }
    return 0;
}
