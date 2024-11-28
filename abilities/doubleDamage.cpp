#include "doubleDamage.h"


DoubleDamage::DoubleDamage(Field* field){
    this->field = field;
}

void DoubleDamage::useAbility(){
    output.printString("Next hit deals double damage.\n");
    field->setDoubleAttackFlag();
}
