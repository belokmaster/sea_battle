#include <iostream>
#include "game.h"

int main() {
    try {
        runGame();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
