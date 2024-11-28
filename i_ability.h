#ifndef I_ABILITY_H
#define I_ABILITY_H

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "field.h"
#include "manager.h"
using namespace std;


class iAbility {
public:
    virtual void use_ability() = 0;
    virtual ~iAbility() = 0;
};
#endif