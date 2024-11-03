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
        unknown_state,
        empty_state,
        ship_state
    };

    int width, height;
    cell** field;
    bool double_damage = false;

public:
    int ships_count;

    BattleField(int width, int height);
    BattleField(const BattleField& other);
    BattleField(BattleField&& other) noexcept;

    BattleField& operator=(const BattleField& other);
    BattleField& operator=(BattleField&& other) noexcept;

    ~BattleField();

    int get_height() const;
    int get_width() const;
    int get_cell_status(int x, int y);
    bool get_double_damage();
    void set_double_damage(bool value);
    ShipManager ship_quantity_preset();

    void place_ship(Ship& ship, int x, int y, std::string orientation);
    void draw_all_field();
    void draw_enemy_field(ShipManager& manager);
    void attack(int x, int y, ShipManager& manager, AbilityManager& ability_manager);
};

#endif