#include "bombard.h"


Bombard::Bombard(shipManager* managerfield, Field* field) {
    this->managerfield = managerfield;
    this->field = field;
}

void Bombard::useAbility() {
    // Используем один раз srand для инициализации
    static bool randomSeedInitialized = false;
    if (!randomSeedInitialized) {
        srand(time(0));
        randomSeedInitialized = true;
    }

    output.print_string("Use a Bombard ability!\n");

    // Выбор случайного корабля и сегмента
    int randomShipIndex = getRandomShipIndex();
    int randomSegmentIndex = getRandomSegmentIndex(randomShipIndex);
    
    // Доступ к выбранному кораблю и его сегменту
    vector<Ship>& ships = managerfield->getShips();
    Ship& selectedShip = ships[randomShipIndex];
    selectedShip.attack(randomSegmentIndex);
    
    // Определение координат для бомбардировки
    int x = selectedShip.getCoordinates()[0];
    int y = selectedShip.getCoordinates()[1];
    if (selectedShip.getOrientation() == 0) {  // горизонтально
        x += randomSegmentIndex;
    } else {  // вертикально
        y += randomSegmentIndex;
    }

    field->bombing(x, y);

    // Проверка уничтожен ли корабль после бомбардировки
    if (selectedShip.destroyedShip() == 1) {
        managerfield->removeShip(randomShipIndex);
        cout << "Ship is destroyed." << '\n';
    }
}

int Bombard::getRandomShipIndex() const {
    int numShips = managerfield->getNumberShip();
    return rand() % numShips;
}

int Bombard::getRandomSegmentIndex(int shipIndex) const {
    return rand() % managerfield->getShips()[shipIndex].getLenght();
}
