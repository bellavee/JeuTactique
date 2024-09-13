#include "Monster.h"
#include <iostream>

Monster::Monster(int x, int y, int hp, int attackPower, char symbol, const std::string& name)
    : Entity(x, y, hp, attackPower, symbol), name(name) {}

void Monster::Move(int dx, int dy) {
    x += dx;
    y += dy;
}

const std::string& Monster::GetName() const {
    return name;
}

void Monster::TakeDamage(int damage) {
    Entity::TakeDamage(damage);
    SpecialAbility();
}
