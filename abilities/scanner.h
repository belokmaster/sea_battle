#ifndef SCANNER_H
#define SCANNER_H

#include "ability.h"
#include "../input.h"


class Scanner: public Ability {
private:
    Field* field;
    int x;
    int y;
    Output output;
    Input input;

public:
    Scanner(Field* field);
    void use_ability();
    void setcoordinates(int x, int y);
    virtual ~Scanner() = default;
};
#endif