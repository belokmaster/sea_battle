#include <iostream>
#include <vector>
#include <random>
#include "field.h"
#include "manager.h"
using namespace std;


class iAbility {
public:
    virtual void use_ability() = 0;
    virtual void setcoordinates(int x, int y) = 0;
    virtual string getname() = 0;
};


class DoubleDamage: public iAbility {
private:
    Field* field;
    int x;
    int y;
public:
    DoubleDamage(Field* field){
        this->field = field;
    }
    void use_ability(){
        cout << "Используется способность DoubleDamage." << '\n';
        this->field->attack_segment(x, y, true);
    }
    void setcoordinates(int x, int y){
        this -> x = x;
        this -> y = y;
    }
    string getname(){
        return "DoubleDamage";
    }
};

class Scanner: public iAbility {
private:
    Field* field;
    int x;
    int y;
public:
    Scanner(Field* field){
        this->field = field;
    }
    void use_ability(){
        cout << "Используется способность Scanner." << '\n';
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                if(field->check_cell(x + i, y + j)){
                    cout << "В квадрате (" << x << ", " << y << ") (" << x + 1 << ", " << y + 1 << ")" << " находится корабль."<<'\n';
                    return;
                }
            }
        }
        cout << "В квадрате (" << x << ", " << y << ") (" << x + 1 << ", " << y + 1 << ")" << " корабля нет." << '\n';
    }
    void setcoordinates(int x, int y){
        this -> x = x;
        this -> y = y;
    }
    string getname(){
        return "Scanner";
    }
};


class Bombardment: public iAbility {
private:
    Field* field;
    Manager* managerfield;
public:
    Bombardment(Manager* managerfield, Field* field){
        this -> managerfield = managerfield;
        this -> field = field;
    }
    void use_ability(){
        srand(time(0));
        cout << "Используется способность Bombardment." << '\n';
        int random_ship = rand();
        random_ship = random_ship % managerfield -> getnumbership();
        vector<Ship>& array_ship = managerfield->getships();
        int random_segment = rand() % array_ship[random_ship].getlenght();
        array_ship[random_ship].attack(random_segment);
        int x = array_ship[random_ship].getcoordinates()[0];
        int y = array_ship[random_ship].getcoordinates()[1];
        if(array_ship[random_ship].getorientation() == 0){
            x = x + random_segment;
        }
        else{
            y = y + random_segment;
        }
        field->bombing(x, y);
        if(array_ship[random_ship].dead_ship() == 1){
            managerfield ->remove_ship(random_ship);
            cout << "Корабль убит." << '\n';
            field->end_game();
        }
    }
    void setcoordinates(int x, int y){
        (void)x;
        (void)y;
    }
    string getname(){
        return "Bombardment";
    }
};


class AbilityManager{
private:
    Field* field;
    Manager* manager;
    vector <iAbility*> queue_abilities;
public:
    AbilityManager(Field* field, Manager* manager){
        this -> field = field;
        this -> manager = manager;
        queue_abilities.push_back(new Bombardment(this->manager, this->field));
        queue_abilities.push_back(new DoubleDamage(this->field));
        queue_abilities.push_back(new Scanner(this->field));
        mt19937 g(static_cast<unsigned int>(time(0)));
        shuffle(queue_abilities.begin(), queue_abilities.end(), g);
    }
    
    void add_ability(){
        srand(time(0));
        int random = rand() % 3;
        if(random == 0){
            queue_abilities.push_back(new Scanner(this->field));
        }
        else if(random == 1){
            queue_abilities.push_back(new DoubleDamage(this->field));
        }
        else if(random == 2){
            queue_abilities.push_back(new Bombardment(this->manager, this->field));
        }
    }

    bool is_empty(){
        return this->queue_abilities.empty();
    }

    void apply_ability(){
        int x, y;
        if(queue_abilities[0]->getname() == "DoubleDamage" || queue_abilities[0]->getname() == "Scanner"){
            cout << "Введите координаты для способности " << queue_abilities[0]->getname() << ":" <<'\n'; 
            cin >> x >> y;
            queue_abilities[0] -> setcoordinates(x, y);
        }
        queue_abilities[0] -> use_ability();
        queue_abilities.erase(queue_abilities.begin());
    }
};