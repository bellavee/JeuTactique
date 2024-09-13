#include "Golem.h"
#include <cstdlib>
#include <iostream>

Golem::Golem(int x, int y) : Monster(x, y, 50, 8, 'G', "Golem") {}

void Golem::SpecialAbility() {
    // 50% chance to resist attack
    if (rand() % 2 == 0) {
        std::cout << "Golem's special ability: Damage resistance activated!" << std::endl;
        // Implement resistance logic (e.g., reduce incoming damage)
    }
}

void Golem::Attack(Entity& target) {
    int damage = GetAttackPower();
    if (rand() % 2 == 0) {  // 50% chance to deal double damage
        std::cout << "Golem's special ability: Stone Fist activated! Double damage!" << std::endl;
        damage *= 2;
    }
    target.TakeDamage(damage);
}