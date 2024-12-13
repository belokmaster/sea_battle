#ifndef BATTLE_FIELD_H
#define BATTLE_FIELD_H

#include <iostream>
#include <vector>
#include <limits>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Ship;
class ShipManager;
class AbilityManager;

class BattleField {
private:
enum cell {
        UNKNOW_CELL,
        EMPTY_CELL,
        SHIP_CELL
    };

    int width, height;
    cell** field;

    bool double_damage = false;

public:
    int ships_count;
    bool gain_ability;
    
    BattleField(int width, int height);

    BattleField(const BattleField& other);
    BattleField(BattleField&& other) noexcept;

    BattleField& operator=(const BattleField& other);
    BattleField& operator=(BattleField&& other) noexcept;

    void place_ship(Ship& ship, int x, int y, std::string orientation);

    ShipManager normalCountShips();

    int getCell(int x, int y);
    void clean();

    void attack(int x, int y, ShipManager& manager, AbilityManager& ability_manager);
    bool getDoubleDamage();
    void setDoubleDamage(bool value);

    int getHeight() const;
    int getWidth() const;

    json to_json() const;
    BattleField from_json_size(const json& j);
    void from_json_coord(const json& j);

    ~BattleField();
};

#endif