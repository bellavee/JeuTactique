#pragma once
#include "Entity.h"
#include <string>

class Monster : public Entity {
private:
    std::string name;

public:
    Monster(int x, int y, int hp, int attackPower, char symbol, const std::string& name);
    virtual void SpecialAbility() = 0;
    void Move(int dx, int dy) override;
    const std::string& GetName() const;
    void TakeDamage(int damage) override;
    virtual void Attack(Entity& target) = 0;
};