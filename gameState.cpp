#include "gameState.h"


void GameState::save(GameField& user_field, GameField& enemy_field, 
            ShipManager& user_manager, ShipManager& enemy_manager,
            AbilityManager& ability_manager) {
    json j;

    j["user_field"] = user_field.to_json();
    j["enemy_field"] = enemy_field.to_json();
    j["user_manager"] = user_manager.to_json();
    j["enemy_manager"] = enemy_manager.to_json();
    j["ability_manager"] = ability_manager.to_json();

    FileHandler file_handler(filename);
    file_handler.open_for_write();
    file_handler.write(j);
}

void GameState::load(GameField& user_field, GameField& enemy_field, 
            ShipManager& user_manager, ShipManager& enemy_manager,
            AbilityManager& ability_manager) {
    FileHandler file_handler(filename);
    file_handler.open_for_read();

    json j;
    file_handler.read(j);

    user_field = user_field.from_json_size(j["user_field"]);
    enemy_field = enemy_field.from_json_size(j["enemy_field"]);
    enemy_manager = enemy_field.ship_quantity_preset();
    user_manager = user_field.ship_quantity_preset();
    user_manager.from_json(j["user_manager"], user_field);
    enemy_manager.from_json(j["enemy_manager"], enemy_field);
    user_field.from_json_coord(j["user_field"]); 
    enemy_field.from_json_coord(j["enemy_field"]);
    ability_manager.from_json(j["ability_manager"]);
}

void GameState::write_state() {
    FileHandler file_handler(filename);
    file_handler.open_for_write();
    file_handler.write(saved_data);
}