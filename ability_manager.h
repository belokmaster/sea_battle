#include "abilities/ability.h"
#include "abilities/bombard.h"
#include "abilities/scanner.h"
#include "abilities/doubleDamage.h"


class AbilityManager{
private:
    Field* field;
    Manager* manager;
    vector <Ability*> queue_abilities;

public:
    AbilityManager(Field* field, Manager* manager);
    AbilityManager() = default;

    void applyAbility();
    void addAbility();
    bool isEmpty();
    
    json write_json();
    void load_json_ability(json j);
    ~AbilityManager();  
};