#ifndef ABILITY_H
#define ABILITY_H

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "../field.h"
#include "../shipManager.h"


class Ability {
public:
    virtual void useAbility() = 0;
    virtual ~Ability() = 0;
};
#endif