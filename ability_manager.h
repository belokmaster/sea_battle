#include "i_ability.h"
#include "bombardment.h"
#include "scanner.h"
#include "double_damage.h"


class AbilityManager{
private:
    Field* field;
    Manager* manager;
    vector <iAbility*> queue_abilities;
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