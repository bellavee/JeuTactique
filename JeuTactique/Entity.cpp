#include "Entity.h"

#include <algorithm>

Entity::Entity(int x, int y, int hp, int attackPower, char symbol)
    : x(x), y(y), hp(hp), attackPower(attackPower), symbol(symbol) {}

void Entity::Move(int dx, int dy) {
    x += dx;
    y += dy;
}

void Entity::Attack(Entity& target) {
    target.hp -= this->attackPower;
}

bool Entity::IsAlive() const {
    return hp > 0;
}

char Entity::GetSymbol() const {
    return symbol;
}

int Entity::GetX() const {
    return x;
}

int Entity::GetY() const {
    return y;
}

int Entity::GetHp() const {
    return hp;
}

int Entity::GetAttackPower() const {
    return attackPower;
}

void Entity::TakeDamage(int damage) {
    hp = std::max(0, hp - damage);
}

void Entity::SetHp(int newHp) {
    hp = newHp;
}

void Entity::SetAttackPower(int newAttackPower) {
    attackPower = newAttackPower;
}
