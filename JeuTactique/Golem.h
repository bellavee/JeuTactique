#pragma once
#include "Monster.h"

class Golem : public Monster {
public:
    Golem(int x, int y);
    void SpecialAbility() override;
};