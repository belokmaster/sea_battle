#ifndef OUTPUT_H
#define OUTPUT_H

#include "ship.h"
#include "battleField.h"
#include "shipManager.h"

#include <iostream>
#include <sstream>
#include <string>
#include <utility>


class Output{
public:
    Output() = default;
    
    void printPlayerField(BattleField user_field);
    void printEnemyField(BattleField enemy_field, ShipManager& enemy_manager);
    void printCells(ShipManager& user_manager);

    void messageLoad();
    void enterSize();
    void messageShipCoords();
    void messageShipOrientation();
    void messageAbility(std::string ability);
    void messageScanner();
    void messageAttackCoords();
    void messagePlayerAttack();
    void messageEnemyAttack();

    void mesageSaveGame();
    void mesageLoadGame();
    void messageWin();
    void messageNewRound();
    void messageLose();
    void messageNewGame();
    void messageExit();
    void messageError();
};

#endif