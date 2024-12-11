#ifndef SCANNER_H
#define SCANNER_H

#include "ability.h"

class Scanner : public Ability {
public:
    void apply(GameField& field, int x, int y, ShipManager& manager) override;
};

#endif