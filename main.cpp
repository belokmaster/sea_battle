#include <iostream>
#include <vector>
#include <limits>
#include "battleField.h"
#include "shipManager.h"
#include "abilityManager.h"

class Ship;
class ShipManager;

enum Command {
    ATTACK,
    STATE_SHIPS,
    FULL_FIELD,
    ENEMY_FIELD,
    ABILITIES,
    APPLY_ABILITY,
    HELP,
    QUIT,
    INVALID
};

Command get_command(const std::string& command) {
    if (command == "attack" || command == "a") return ATTACK;
    if (command == "state_ships" || command == "ss") return STATE_SHIPS;
    if (command == "full_field" || command == "ff") return FULL_FIELD;
    if (command == "enemy_field" || command == "ef") return ENEMY_FIELD;
    if (command == "abilities" || command == "ab") return ABILITIES;
    if (command == "apply_ability" || command == "aa") return APPLY_ABILITY;
    if (command == "help" || command == "h") return HELP;
    if (command == "quit" || command == "q") return QUIT;
    return INVALID;
}

int main() {
    try {
        int size;
        std::cout << "Enter field size: ";
        std::cin >> size;

        BattleField field(size);
        AbilityManager ability_manager;

        ShipManager manager = field.normalShipsCount();
        int ships_count = field.shipsCount;

        for (int i = 0; i < ships_count; ++i) {
            Ship& ship = manager.getShip(i);
            int x, y;
            std::string orientation;

            field.drawField(manager, false);
            std::cout << "Enter ship coordinates and orientation: ";
            std::cin >> x >> y >> orientation;

            field.placeShip(ship, x, y, orientation);
        }

        field.drawField(manager, false);

        while (true) {
            std::string command;
            std::cout << "Enter command: ";
            std::cin >> command;

            switch (get_command(command)) {
            case ATTACK: {
                std::cout << "Enter coordinates to attack: ";
                int x, y;
                std::cin >> x >> y;
                field.attackShip(x, y, manager, ability_manager);
                break;
            }
            case STATE_SHIPS:
                manager.printStates();
                break;
            case FULL_FIELD:
                field.drawField(manager, false);
                break;
            case ENEMY_FIELD:
                field.drawField(manager, true);
                break;
            case ABILITIES:
                ability_manager.next_abilities();
                break;
            case APPLY_ABILITY: {
                std::string ability = ability_manager.next_abilities(1);

                if (ability == "DoubleDamage") {
                    ability_manager.apply_ability(field, 0, 0, manager);
                }
                else if (ability == "Scanner") {
                    int x, y;
                    std::cout << "Coordinate for ability: ";
                    std::cin >> x >> y;
                    ability_manager.apply_ability(field, x, y, manager);
                }
                else if (ability == "Bombard") {
                    ability_manager.apply_ability(field, 0, 0, manager);
                }
                else {
                    std::cout << "No valid ability to apply." << std::endl;
                }
                break;
            }
            case HELP:
                std::cout << "Commands:\n"
                    << "attack or a - attack a cell\n"
                    << "state_ships or ss - show ships status\n"
                    << "quit or q - quit the game\n"
                    << "full_field or ff - show full field\n"
                    << "enemy_field or ef - show enemy field\n"
                    << "abilities or ab - view current ability\n"
                    << "apply_ability or aa - cast the next ability in the queue\n"
                    << std::endl;
                break;
            case QUIT:
                std::exit(0);
            case INVALID:
            default:
                std::cout << "Invalid command. Type \"help\" or \"h\" for a list of commands." << std::endl;
                break;
            }
        }

    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
