#include "scanner.h"


Scanner::Scanner(Field* field) {
    this->field = field;
}

bool Scanner::checkArea(int x, int y) {
    // Проверяем клетки на позиции (x, y), (x + 1, y), (x, y + 1) и (x + 1, y + 1)
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (field->check_cell(x + i, y + j)) {
                return true;  // Если хотя бы одна клетка занята
            }
        }
    }
    return false;  // Если ни одна клетка не занята
}

void Scanner::useAbility() {
    output.printString("Use a Scanner ability.\n");
    output.printString("Enter coordinates (x y): ");
    
    // Считываем координаты
    pair<int, int> coordinates = input.inputCoordinates();
    x = get<0>(coordinates);
    y = get<1>(coordinates);
    
    // Используем метод для проверки области
    bool isOccupied = checkArea(x, y);
    
    // Выводим результат
    output.printScanner(x, y, isOccupied);
}

void Scanner::setCoordinates(int x, int y){
    this -> x = x;
    this -> y = y;
}