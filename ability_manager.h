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
    void add_ability();
    bool is_empty();
    void apply_ability();
    json write_json();
    void load_json_ability(json j);
    ~AbilityManager();  
};