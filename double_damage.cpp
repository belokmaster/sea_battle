#include "double_damage.h"

DoubleDamage::DoubleDamage(Field* field){
    this->field = field;
}
void DoubleDamage::use_ability(){
    output.print_string("Используется способность DoubleDamage.\n");
    field->set_double_attack_flag();
}
