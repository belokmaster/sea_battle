#ifndef BATTLE_FIELD_H
#define BATTLE_FIELD_H

#include <iostream>
#include <vector>


class Ship;
class ShipManager;

class BattleField {

private:
enum cell {
        NEAR_CELL,
        WATER_CELL,
        SHIP_CELL
    };

    int size;
    cell** field;

    bool double_damage = false; // добавили двойной дамаг

public:
    int shipsCount;

    BattleField(int size);
    BattleField(const BattleField& other);
    BattleField(BattleField&& other) noexcept;

    ~BattleField();

    BattleField& operator=(const BattleField& other);
    BattleField& operator=(BattleField&& other) noexcept;

    int getSize() const;
    ShipManager normalShipsCount();

    void drawField(ShipManager& manager);
    void placeShip(Ship& ship, int col, int row, std::string orientation);
    void markAroundDestroyedShip(Ship& ship);
    void attackShip(int col, int row, ShipManager& manager);

    bool getDoubleDamage();
    void setDoubleDamage(bool value);
};

#endif