#include "Spectre.h"
#include <iostream>
#include <cstdlib>

Spectre::Spectre(int x, int y) : Monster(x, y, 30, 5, 'S', "Spectre") {}

void Spectre::SpecialAbility() {
    std::cout << "Spectre uses its special ability: Ethereal Dodge!" << std::endl;
    // Implement ethereal dodge logic here if needed
}

void Spectre::Move(int dx, int dy) {
    // Spectre moves in the opposite direction of the hero
    Monster::Move(-dx, -dy);
    std::cout << "Spectre flees in the opposite direction!" << std::endl;
}

void Spectre::Attack(Entity& target) {
    int damage = GetAttackPower();
    target.TakeDamage(damage);
    std::cout << "Spectre's special ability: Life Drain activated!" << std::endl;
    SetHp(GetHp() + damage / 2);  // Heal for half the damage dealt
}
