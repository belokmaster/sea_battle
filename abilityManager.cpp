#include "abilityManager.h"
#include "ship.h"
#include "shipManager.h"
#include "ability.h"
#include "exception.h"
#include <algorithm>
#include <random>


AbilityManager::AbilityManager() {
    std::vector<std::unique_ptr<Ability>> available_abilities;
    available_abilities.emplace_back(std::make_unique<DoubleDamage>());
    available_abilities.emplace_back(std::make_unique<Scanner>());
    available_abilities.emplace_back(std::make_unique<Bombard>());

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(available_abilities.begin(), available_abilities.end(), gen);

    for (auto &ability : available_abilities) {
        abilities.push(std::move(ability));
    }
}

void AbilityManager::apply_ability(BattleField& field, int x, int y, ShipManager& manager) {
    try {
        if (!abilities.empty()) {
            abilities.front()->apply(field, x, y, manager);
            abilities.pop();
        } else {
            throw NoAbilitiesException("No abilities available.");
        }
    } catch (NoAbilitiesException& e) {
        std::cerr << e.what() << std::endl;
    }
}

std::string AbilityManager::next_abilities(bool flag) {
    std::string ability;

    if (!abilities.empty()) {
        if (!flag) {
            std::cout << "Next ability: ";
        }

        Ability* next_ability = abilities.front().get();

        if (dynamic_cast<DoubleDamage*>(next_ability)) {
            ability = "DoubleDamage";
        } else if (dynamic_cast<Scanner*>(next_ability)) {
            ability = "Scanner";
        } else if (dynamic_cast<Bombard*>(next_ability)) {
            ability = "Bombard";
        }

    } else {
        std::cout << "No abilities available." << std::endl;
    }

    return ability;
}
 
void AbilityManager::gain_random_ability() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 2);

    int random = dist(gen);
    std::unique_ptr<Ability> new_ability;

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