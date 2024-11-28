#include "ability_manager.h"


AbilityManager::AbilityManager(Field* field, Manager* manager){
    this -> field = field;
    this -> manager = manager;
    queue_abilities.push_back(new Bombardment(this->manager, this->field));
    queue_abilities.push_back(new DoubleDamage(this->field));
    queue_abilities.push_back(new Scanner(this->field));
    mt19937 g(static_cast<unsigned int>(time(0)));
    shuffle(queue_abilities.begin(), queue_abilities.end(), g);
}

void AbilityManager::add_ability(){
    srand(time(0));
    int random = rand() % 3;
    if(random == 0){
        queue_abilities.push_back(new Scanner(this->field));
    }
    else if(random == 1){
        queue_abilities.push_back(new DoubleDamage(this->field));
    }
    else if(random == 2){
        queue_abilities.push_back(new Bombardment(this->manager, this->field));
    }
}

bool AbilityManager::is_empty(){
    return this->queue_abilities.empty();
}

void AbilityManager::apply_ability(){
    queue_abilities[0] -> use_ability();
    queue_abilities.erase(queue_abilities.begin());
}

json AbilityManager::write_json() {
    json j;
    j["queue_size"] = this->queue_abilities.size();
    json ability_json = json::array(); 
    for (auto ability : queue_abilities) {
        string type;
        if (dynamic_cast<DoubleDamage*>(ability)) {
            type = "DoubleDamage";
        } else if (dynamic_cast<Scanner*>(ability)) {
            type = "Scanner";
        } else if (dynamic_cast<Bombardment*>(ability)) {
            type = "Bombardment";
        }
        json type_ability = {{"type", type}};
        ability_json.push_back(type_ability); 
    }
    j["queue_abilities"] = ability_json;
    return j;
}

void AbilityManager::load_json_ability(json j){
    queue_abilities.clear();
    auto queue_json = j["queue_abilities"];
    for(auto abilities: queue_json){
        string type = abilities["type"];
        if(type == "DoubleDamage"){
            queue_abilities.push_back(new DoubleDamage(this->field));
        }
        else if(type == "Scanner"){
            queue_abilities.push_back(new Scanner(this->field));
        }
        else if(type == "Bombardment"){
            queue_abilities.push_back(new Bombardment(this->manager, this->field));
        }
    }
}


AbilityManager::~AbilityManager(){
    int size_queue = this->queue_abilities.size();
    for(int i = 0; i < size_queue; i++){
        delete this->queue_abilities[i];
    }
}
