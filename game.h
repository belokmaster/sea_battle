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
    BattleField field;          // Игровое поле игрока
    BattleField enemyField;     // Игровое поле врага
    ShipManager manager;
    AbilityManager abilityManager;

    void placeShips();
    void processCommand(Command command);
    void gameLoop();
    Command getCommand(const std::string& command);  // Объявление метода для получения команды
};

#endif // GAME_H
