#include "bombard.h"

Bombard::Bombard(Manager* managerfield, Field* field) {
    this->managerfield = managerfield;
    this->field = field;
}

void Bombard::use_ability() {
    // Используем один раз srand для инициализации
    static bool randomSeedInitialized = false;
    if (!randomSeedInitialized) {
        srand(time(0));
        randomSeedInitialized = true;
    }

    output.print_string("Use a bombard ability!\n");

    // Выбор случайного корабля и сегмента
    int randomShipIndex = getRandomShipIndex();
    int randomSegmentIndex = getRandomSegmentIndex(randomShipIndex);
    
    // Доступ к выбранному кораблю и его сегменту
    vector<Ship>& ships = managerfield->getships();
    Ship& selectedShip = ships[randomShipIndex];
    selectedShip.attack(randomSegmentIndex);
    
    // Определение координат для бомбардировки
    int x = selectedShip.getcoordinates()[0];
    int y = selectedShip.getcoordinates()[1];
    if (selectedShip.getorientation() == 0) {  // горизонтально
        x += randomSegmentIndex;
    } else {  // вертикально
        y += randomSegmentIndex;
    }

    field->bombing(x, y);

    // Проверка уничтожен ли корабль после бомбардировки
    if (selectedShip.dead_ship() == 1) {
        managerfield->remove_ship(randomShipIndex);
        cout << "Ship is destroyed." << '\n';
    }
}

int Bombard::getRandomShipIndex() const {
    int numShips = managerfield->getnumbership();
    return rand() % numShips;
}

int Bombard::getRandomSegmentIndex(int shipIndex) const {
    return rand() % managerfield->getships()[shipIndex].getlenght();
}
