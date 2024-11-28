#ifndef GAME_H
#define GAME_H

#include "battleField.h"
#include "shipManager.h"
#include "abilityManager.h"

enum Command {
    ATTACK,
    STATE_SHIPS,
    PRINT_FIELD,
    ABILITIES,
    APPLY_ABILITY,
    HELP,
    QUIT,
    INVALID
};

class Game {
public:
    Game(int size);
    void run();
    
private:
    int fieldSize;
    BattleField field;
    ShipManager manager;
    AbilityManager abilityManager;

    void placeShips();
    void processCommand(Command command);
    void gameLoop();
    Command getCommand(const std::string& command);  // Добавлено объявление
};

#endif // GAME_H
