#include "Reaper.h"
#include <iostream>
#include <cmath>

Reaper::Reaper(int x, int y) : Monster(x, y, 40, 15, 'R', "Reaper") {}

void Reaper::SpecialAbility() {
    std::cout << "Reaper uses its special ability: Death's Embrace!" << std::endl;
    // Implement Death's Embrace logic here if needed
}

void Reaper::Move(int dx, int dy) {
    // Reaper moves towards the hero
    int moveX = dx > 0 ? 1 : (dx < 0 ? -1 : 0);
    int moveY = dy > 0 ? 1 : (dy < 0 ? -1 : 0);
    Monster::Move(moveX, moveY);
    std::cout << "Reaper moves closer, seeking its prey!" << std::endl;
}

void Reaper::Attack(Entity& target) {
    int damage = GetAttackPower();
    target.TakeDamage(damage);
    std::cout << "Reaper's special ability: Death Mark activated!" << std::endl;
    // Implement Death Mark logic (e.g., hero takes additional damage next turn)
}
