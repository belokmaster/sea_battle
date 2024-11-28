#ifndef BOMBARDMENT_H
#define BOMBARDMENT_H

#include "i_ability.h"

class Bombardment: public iAbility {
private:
    Field* field;
    Manager* managerfield;
    Output output;
public:
    Bombardment(Manager* managerfield, Field* field);
    void use_ability();
    virtual ~Bombardment() = default;
};
#endif