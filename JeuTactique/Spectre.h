#pragma once
#include "Monster.h"

class Spectre : public Monster {
public:
    Spectre(int x, int y);
    void SpecialAbility() override;
    void Move(int dx, int dy) override;
    void Attack(Entity& target) override;
    
};
