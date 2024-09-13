#include "Monster.h"

Monster::Monster(int x, int y, int hp, int attackPower, char symbol, const std::string& name)
    : Entity(x, y, hp, attackPower, symbol), name(name) {}

const std::string& Monster::GetName() const {
    return name;
}