#include "input.h"

// Функция для ввода одного числа
int Input::inputSingleNumber() {
    int one;
    std::string inputString;
    while (true) {
        try {
            getline(std::cin, inputString); // Считываем строку из входного потока
            std::stringstream ss(inputString);
            // Проверяем, можно ли преобразовать строку в одно число
            if (!(ss >> one) || !ss.eof()) {
                throw IncorrectFieldSize("Некорректные данные, введите ещё раз!"); // Бросаем исключение при ошибке
            }
            break; // Выход из цикла при успешном вводе
        } catch (IncorrectFieldSize& e) {
            output.printErrorString(e.what()); // Выводим сообщение об ошибке
        }
    }
    return one; 
}

std::vector<int> Input::inputShipPlace() {
    int x, y, orientation;
    std::string inputString;
    while (true) {
        try {
            getline(std::cin, inputString); // Считываем строку из входного потока
            std::stringstream ss(inputString);
            if (!(ss >> x >> y >> orientation) || !ss.eof()) {
                throw IncorrectCoordinatesException("Некорректные данные, введите ещё раз!"); // Бросаем исключение при ошибке
            }
            break; // Выход из цикла при успешном вводе
        } catch (IncorrectCoordinatesException& e) {
            output.printErrorString(e.what()); // Выводим сообщение об ошибке
        }
    }
    return {x, y, orientation};
}

std::string Input::inputFlag() {
    std::string flag;
    std::string inputString;
    while (true) {
        try {
            getline(std::cin, inputString); // Считываем строку из входного потока
            std::stringstream ss(inputString);
            // Проверяем, можно ли преобразовать строку в одно слово
            if (!(ss >> flag) || ss.fail() || !ss.eof()) {
                throw IncorrectFieldSize("Некорректные данные, введите ещё раз!"); // Бросаем исключение при ошибке
            }
            break; // Выход из цикла при успешном вводе
        } catch (IncorrectFieldSize& e) {
            output.printErrorString(e.what()); 
        }
    }
    return flag;
}

std::pair<int, int> Input::inputCoordinates() {
    int x, y;
    std::string inputString;
    while (true) {
        try {
            getline(std::cin, inputString); 
            std::stringstream ss(inputString);
            if (!(ss >> x >> y) || ss.fail() || !ss.eof()) {
                throw IncorrectFieldSize("Некорректные данные, введите ещё раз!"); 
            }
            break; 
        } catch (IncorrectFieldSize& e) {
            output.printErrorString(e.what());
        }
    }
    return std::make_pair(x, y); 
}
