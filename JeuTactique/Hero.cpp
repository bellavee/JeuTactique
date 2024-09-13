#include "Hero.h"
#include <iostream>

Hero::Hero(int x, int y) : Entity(x, y, 100, 10, '@') {}

void Hero::Attack(Entity& target) {
    int damage = GetAttackPower();
    target.TakeDamage(damage);
    std::cout << "Hero deals " << damage << " damage!" << std::endl;
}

void Hero::LevelUp() {
    SetHp(GetHp() + 20);
    SetAttackPower(GetAttackPower() + 5);
}

void Hero::TakeDamage(int damage) {
    Entity::TakeDamage(damage);
    if (GetHp() <= 0) {
        std::cout << "Game Over! The hero has been defeated." << std::endl;
        // Implement game over logic
    }
}