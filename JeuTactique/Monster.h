#pragma once
#include "Entity.h"
#include <string>

class Monster : public Entity {
private:
    std::string name;

public:
    Monster(int x, int y, int hp, int attackPower, char symbol, const std::string& name);
    virtual void SpecialAbility() = 0;
    const std::string& GetName() const;
};
