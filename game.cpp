#include "game.h"
#include <iostream>
#include <string>

void runGame() {
    int size;
    std::cout << "Enter field size: ";
    std::cin >> size;

    BattleField field(size);
    AbilityManager ability_manager;
    ShipManager manager = field.normalShipsCount();

    placeShips(field, manager);
    gameLoop(field, manager, ability_manager);
}


Command getCommand(const std::string& command) {
    if (command == "help" || command == "h") return HELP;
    if (command == "printField" || command == "pf") return PRINT_FIELD;
    if (command == "attack" || command == "a") return ATTACK;
    if (command == "stateShips" || command == "ss") return STATE_SHIPS;
    if (command == "abilities" || command == "ab") return ABILITIES;
    if (command == "applyAbility" || command == "aa") return APPLY_ABILITY;
    if (command == "quit" || command == "q") return QUIT;
    return INVALID;
}


void placeShips(BattleField& field, ShipManager& manager) {
    int shipsCount = field.shipsCount;

    for (int i = 0; i < shipsCount; ++i) {
        Ship& ship = manager.getShip(i);
        int x, y;
        std::string orientation;

        field.drawField(manager, false);
        std::cout << "Enter ship coordinates and orientation: ";
        std::cin >> x >> y >> orientation;

        field.placeShip(ship, x, y, orientation);
    }

    field.drawField(manager, false);
}


void processCommand(Command command, BattleField& field, ShipManager& manager, AbilityManager& ability_manager) {
    switch (command) {
    case HELP:
        std::cout << "Commands:\n"
            << "[    attack / a     ] - attack a cell\n" 
            << "[  stateShips / ss  ] - show ships status\n" 
            << "[     quit / q      ] - quit the game\n"
            << "[  printField / pf  ] - show game field\n"
            << "[   abilities / ab  ] - view current ability\n"
            << "[ applyAbility / aa ] - cast the next ability in the queue" 
            << std::endl;
        break;
    case PRINT_FIELD:
        field.drawField(manager, false); 
        break;
    case ATTACK: {
        int x, y;
        std::cout << "Enter coordinates to attack: ";
        std::cin >> x >> y;
        field.attackShip(x, y, manager, ability_manager);
        break;
    }
    case STATE_SHIPS:
        manager.printStates();
        break;
    case ABILITIES:
        ability_manager.nextAbility();
        break;
    case APPLY_ABILITY: {
        std::string ability = ability_manager.nextAbility(1);

        if (ability == "DoubleDamage") {
            ability_manager.applyAbility(field, 0, 0, manager);
        }
        else if (ability == "Scanner") {
            int x, y;
            std::cout << "Coordinate for ability Scanner: ";
            std::cin >> x >> y;
            ability_manager.applyAbility(field, x, y, manager);
        }
        else if (ability == "Bombard") {
            ability_manager.applyAbility(field, 0, 0, manager);
        }
        else {
            std::cout << "No valid ability to apply." << std::endl;
        }
        break;
    }
    case QUIT:
        std::exit(0);
    case INVALID:
    default:
        std::cout << "Invalid command. Type \"help\" or \"h\" for a list of commands." << std::endl;
        break;
    }
}


void gameLoop(BattleField& field, ShipManager& manager, AbilityManager& ability_manager) {
    while (true) {
        std::string command;
        std::cout << "Enter command: ";
        std::cin >> command;
        processCommand(getCommand(command), field, manager, ability_manager);
    }
}
