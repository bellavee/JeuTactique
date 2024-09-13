#pragma once
#include "Monster.h"

class Reaper : public Monster {
public:
    Reaper(int x, int y);
    void SpecialAbility() override;
    void Move(int dx, int dy) override;
    void Attack(Entity& target) override;
};