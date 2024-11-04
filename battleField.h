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

    int size;
    cell** field;
    bool double_damage = false;

public:
    int ships_count;

    BattleField(int size);
    BattleField(const BattleField& other);
    BattleField(BattleField&& other) noexcept;

    ~BattleField();

    BattleField& operator=(const BattleField& other);
    BattleField& operator=(BattleField&& other) noexcept;

    int get_size() const;
    int get_cell_status(int x, int y);
    ShipManager ship_quantity_preset();

    void draw_all_field();
    void draw_enemy_field(ShipManager& manager);
    void place_ship(Ship& ship, int x, int y, std::string orientation);
    void attack(int x, int y, ShipManager& manager, AbilityManager& ability_manager);

    bool get_double_damage();
    void set_double_damage(bool value);
};

#endif