#ifndef DOUBLE_DAMAGE_H
#define DOUBLE_DAMAGE_H

#include "ability.h"

class DoubleDamage: public Ability {
private:
    Field* field;
    int x;
    int y;
    Output output;

public:
    DoubleDamage(Field* field);
    void useAbility();
    virtual ~DoubleDamage() = default;
};
#endif