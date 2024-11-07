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

void runGame();
Command getCommand(const std::string& command);
void placeShips(BattleField& field, ShipManager& manager);
void processCommand(Command command, BattleField& field, ShipManager& manager, AbilityManager& ability_manager);
void gameLoop(BattleField& field, ShipManager& manager, AbilityManager& ability_manager);

#endif // GAME_H
