#ifndef BATTLE_FIELD_H
#define BATTLE_FIELD_H

#include <iostream>
#include <vector>
#include <limits>


class Ship;
class ShipManager;
class AbilityManager;

class BattleField {
private:
    enum cell {
        UNKNOWN_CELL,
        EMPTY_CELL,
        SHIP_CELL
    };

    int size;
    cell** field;
    bool doubleDamage = false;

public:
    int shipsCount;

    BattleField(int size);
    BattleField(const BattleField& other);
    BattleField(BattleField&& other) noexcept;

    ~BattleField();

    BattleField& operator=(const BattleField& other);
    BattleField& operator=(BattleField&& other) noexcept;

    int getSize() const;
    int getCell(int x, int y);
    ShipManager normalShipsCount();

    void draw_all_field();
    void draw_enemy_field(ShipManager& manager);
    void placeShip(Ship& ship, int x, int y, std::string orientation);
    void attackShip(int x, int y, ShipManager& manager, AbilityManager& ability_manager);
    void markAroundDestroyedShip(Ship& ship);

    bool getDoubleDamage();
    void setDoubleDamage(bool value);
};

#endif