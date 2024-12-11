#include "field.h"


void Output::printString(std::string message) {
    std::cout << message;
}

void Output::printCountShips(int i) {
    std::cout << "Введите количество кораблей длиной " << i << ": ";
}

void Output::printErrorString(std::string message) {
    std::cerr << message << '\n';
}

void Output::printScanner(int x, int y, bool flag) {
    if (flag) {
        std::cout << "В квадрате (" << x << ", " << y << ") (" << x + 1 << ", " << y + 1 << ") находится корабль." << '\n';
    } else {
        std::cout << "В квадрате (" << x << ", " << y << ") (" << x + 1 << ", " << y + 1 << ") корабля нет." << '\n';
    }
}

void Output::printErrorWithXy(std::string msg, int x, int y) {
    std::cerr << msg << x << ' ' << y << '\n';
}

void Output::printFieldUser(Field* field, int size) {
    std::cout << "\nField looks like this: \n\n";

    std::cout << "   ";
    for (int x = 0; x < size; x++) {
        if (x < 10) {
            std::cout << " " << x << " ";
        } else {
            std::cout << x << " ";
        }
    }
    std::cout << std::endl;

    // Вывод строк поля с номерами строк
    for (int y = 0; y < size; y++) {
        if (y < 10) {
            std::cout << " " << y << " ";
        } else {
            std::cout << y << " ";
        }

        for (int x = 0; x < size; x++) {
            // Проверка состояния ячейки поля
            if (field->getCell(x, y) == Field::UNKNOWN) {
                std::cout << " ~ ";
            } else if (field->getCell(x, y) == Field::FOGWAR) {
                std::cout << " f ";
            } else {
                std::cout << " " << field->getCell(x, y) << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Output::printFieldEnemy(Field* field, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (field->getCell(j, i) == Field::UNKNOWN || field->getCell(j, i) == Field::ALIVE || field->getCell(j, i) == Field::FOGWAR) {
                std::cout << "~" << " ";
            } else {
                std::cout << field->getCell(j, i) << " ";
            }
        }
        std::cout << std::endl;
    }
}
