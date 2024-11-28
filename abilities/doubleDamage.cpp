#include "doubleDamage.h"

DoubleDamage::DoubleDamage(Field* field){
    this->field = field;
}

void DoubleDamage::use_ability(){
    output.print_string("Next hit deals double damage.\n");
    field->set_double_attack_flag();
}
