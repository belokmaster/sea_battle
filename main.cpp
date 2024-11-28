#include <iostream>
#include "game.h"

int main() {
    try {
        int size;
        std::cout << "Enter the size of the field: ";
        std::cin >> size;

        // Создание объекта игры с размером поля
        Game game(size);
        
        // Запуск игры
        game.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}