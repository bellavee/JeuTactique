#pragma once
#include "Entity.h"

class Hero : public Entity {
public:
    Hero(int x, int y);
    void Attack(Entity& target) override;
    void LevelUp();
    void TakeDamage(int damage) override;
};