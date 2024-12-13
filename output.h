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

    void main_menu_message();
    void width_and_height_message();
    void ship_coordinates_message();
    void ship_orientation_message();
    void ability_message(std::string ability);
    void scanner_coordinates_message();
    void attack_message();
    void your_attack_message();
    void enemy_attack_message();
    void save_message();
    void load_message();
    void win_message();
    void new_round_message();
    void defeat_message();
    void new_game_message();
    void exit_message();
    void error_message();

    void print_user_field(BattleField user_field);
    void print_enemy_field(BattleField enemy_field, ShipManager& enemy_manager);
    void print_states(ShipManager& user_manager);
};

#endif