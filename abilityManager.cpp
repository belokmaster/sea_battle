#include "abilityManager.h"
#include "ship.h"
#include "shipManager.h"
#include "abilities/ability.h"
#include "exception.h"
#include <algorithm>
#include <random>


AbilityManager::AbilityManager() {
    std::vector<std::unique_ptr<Ability>> available_abilities;
    available_abilities.emplace_back(std::make_unique<DoubleDamage>());
    available_abilities.emplace_back(std::make_unique<Scanner>());
    available_abilities.emplace_back(std::make_unique<Bombard>());

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(available_abilities.begin(), available_abilities.end(), g);

    for(auto &ability : available_abilities) {
        abilities.push(move(ability));
    }
}

void AbilityManager::apply_ability(GameField& field, int x, int y, ShipManager& manager) {
    try {
        if (!abilities.empty()) {
            abilities.front()->apply(field, x, y, manager);
            abilities.pop();
            len_queue -= 1;
        } else {
            throw NoAbilitiesException("No abilities available.");
        }
    } catch (NoAbilitiesException& e) {
        std::cerr << e.what() << std::endl;
    }
}

std::string AbilityManager::next_abilities() {
    std::string ability = "";

    if (!abilities.empty()) {

        Ability* next_ability = abilities.front().get();

        if (dynamic_cast<DoubleDamage*>(next_ability)) {
            ability = "DoubleDamage";
        } else if (dynamic_cast<Scanner*>(next_ability)) {
            ability = "Scanner";
        } else if (dynamic_cast<Bombard*>(next_ability)) {
            ability = "Bombard";
        }
    }

    return ability;
}
 
void AbilityManager::gain_random_ability() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 2);

    int random = dist(gen);
    std::unique_ptr<Ability> new_ability;

    len_queue += 1;

    switch (random) {
        case 0:
            new_ability = std::make_unique<DoubleDamage>();
            break;
        case 1:
            new_ability = std::make_unique<Scanner>();
            break;
        case 2:
            new_ability = std::make_unique<Bombard>();
            break;
    }

    abilities.push(std::move(new_ability));
    std::cout << "A new ability has been gained." << std::endl;
}

int AbilityManager::get_len_queue() {
    return len_queue; 
}

void AbilityManager::set_len_queue(int value) {
    len_queue = value; 
}

json AbilityManager::to_json() {
    json j;
    std::vector<json> ability_list;
    std::vector<std::string> temp_ability;
    
    for(int i = 0; i < len_queue; i++) {
        if (dynamic_cast<DoubleDamage*>(abilities.front().get())) {
            ability_list.push_back({"type", "DoubleDamage"});
            temp_ability.push_back("DoubleDamage");

        } else if (dynamic_cast<Scanner*>(abilities.front().get())) {
            ability_list.push_back({"type", "Scanner"});
            temp_ability.push_back("Scanner");

        } else if (dynamic_cast<Bombard*>(abilities.front().get())) {
            ability_list.push_back({"type", "Bombard"});
            temp_ability.push_back("Bombard");

        }
        abilities.pop();
    }

    j["abilities"] = ability_list;

    for(int i = 0; i < temp_ability.size(); i++) {
        if(temp_ability[i] == "Bombard") {
            abilities.push(std::move(std::make_unique<Bombard>()));

        } else if (temp_ability[i] == "DoubleDamage") {
            abilities.push(std::move(std::make_unique<DoubleDamage>()));
        
        } else if (temp_ability[i] == "Scanner") {
            abilities.push(std::move(std::make_unique<Scanner>()));
        }
    }

    j["len_queue"] = len_queue;

    return j;
}

void AbilityManager::from_json(const json& j) {
    std::queue<std::unique_ptr<Ability>> empty;
    std::swap(abilities, empty);

    const auto& abilities_array = j["abilities"];
    for (const auto& ability_data : abilities_array) {
        std::string type = ability_data[1];

        if (type == "Bombard") {
            abilities.push(std::make_unique<Bombard>());
        
        } else if (type == "Scanner") {
            abilities.push(std::make_unique<Scanner>());
        
        } else if (type == "DoubleDamage") {
            abilities.push(std::make_unique<DoubleDamage>());
        
        } else {
            throw std::invalid_argument("Unknown ability type.");
        }
    }

    len_queue = j["len_queue"];
}