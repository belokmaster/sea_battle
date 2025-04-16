#include "abilities/ability.h"
#include "abilities/bombard.h"
#include "abilities/scanner.h"
#include "abilities/doubleDamage.h"
#include "shipManager.h"

class AbilityManager{
private:
    Field* field;
    shipManager* manager;
    vector <Ability*> queue_abilities;

public:
    AbilityManager(Field* field, shipManager* manager);
    AbilityManager() = default;

    void applyAbility();
    void addAbility();
    bool isEmpty();
    
    json write_json();
    void load_json_ability(json j);
    ~AbilityManager();  
};