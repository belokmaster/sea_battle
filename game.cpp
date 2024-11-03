#include "game.h"
#include <iostream>
#include <limits>

Game::Game() : field(nullptr), manager(0, std::vector<int>{}) {}

void Game::clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int Game::getValidatedInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin) {
            break;
        }
        clearInput();
        std::cout << "Invalid input. Please try again.\n";
    }
    return value;
}

void Game::getShipInput(int& x, int& y, std::string& orientation) {
    std::cout << "Enter ship's position (column and row) and orientation (horizontal or vertical): ";
    std::cin >> x >> y;

    if (!std::cin) {
        clearInput();
        std::cout << "Invalid coordinates. Please enter two integers for coordinates.\n";
        return;
    }

    if (std::cin.peek() == '\n') {
        orientation = "none"; 
    }
    else {
        std::cin >> orientation;
    }
}

void Game::commands() {
    std::string command;
    std::cout << "Enter command (you can use help): ";
    std::cin >> command;

    if (command == "attack" || command == "a") {
        int col = getValidatedInput("");
        int row = getValidatedInput("");
        try {
            field->attackShip(col, row, manager);
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
    else if (command == "field" || command == "f") {
        field->drawField(manager);
    }
    else if (command == "help" || command == "h") {
        displayHelp();
    }
    else if (command == "quit" || command == "q") {
        std::exit(0);
    }
    else {
        std::cout << "Invalid command. Type \"help\" or \"h\" for a list of commands." << std::endl;
    }
}

void Game::displayHelp() {
    std::cout << "Commands:\n"
        << "1) attack or a - attack a cell;\n"
        << "2) field or f - show game field.\n"
        << "3) quit or q - quit the game;\n"
        << std::endl;
}

void Game::run() {
    int size = 0;

    while (true) {
        size = getValidatedInput("Enter field size: ");
        try {
            field = std::make_unique<BattleField>(size);
            break;
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    manager = field->normalShipsCount();
    int ships_count = field->shipsCount;
    field->drawField(manager);

    for (int i = 0; i < ships_count; i++) {
        Ship& ship = manager.getShip(i);
        int x, y;
        std::string orientation;

        getShipInput(x, y, orientation);
        try {
            field->placeShip(ship, x, y, orientation);
            field->drawField(manager);
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            i--;
        }
    }

    field->drawField(manager);

    while (true) {
        commands();
    }
}
