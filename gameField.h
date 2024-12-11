#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include <iostream>
#include <vector>
#include <limits>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Ship;
class ShipManager;
class AbilityManager;

class GameField {
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
    bool gain_ability;
    
    GameField(int width, int height);

    GameField(const GameField& other);
    GameField(GameField&& other) noexcept;

    GameField& operator=(const GameField& other);

    GameField& operator=(GameField&& other) noexcept;

    void place_ship(Ship& ship, int x, int y, std::string orientation);

    ShipManager ship_quantity_preset();

    void draw_all_field();
    void draw_enemy_field(ShipManager& manager);
    int get_cell_status(int x, int y);
    void clean();

    void attack(int x, int y, ShipManager& manager, AbilityManager& ability_manager);

    int get_height() const;
    int get_width() const;

    bool get_double_damage();
    void set_double_damage(bool value);

    json to_json() const;

    GameField from_json_size(const json& j);

    void from_json_coord(const json& j);

    ~GameField();
};

#endif