#ifndef GAME_H
#define GAME_H

#include <memory>
#include "battleField.h"
#include "shipManager.h"

class Game {
public:
    Game();
    void run();

private:
    std::unique_ptr<BattleField> field;
    ShipManager manager;

    void clearInput();
    int getValidatedInput(const std::string& prompt);
    void getShipInput(int& x, int& y, std::string& orientation);
    void commands();
    void displayHelp();
};

#endif
