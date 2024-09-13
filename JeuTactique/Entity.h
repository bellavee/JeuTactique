#pragma once

class Entity {
protected:
    int x, y;
    int hp;
    int attackPower;
    char symbol;

public:
    virtual ~Entity() = default;
    Entity(int x, int y, int hp, int attackPower, char symbol);
    virtual void Move(int dx, int dy);
    virtual void Attack(Entity& target);
    bool IsAlive() const;
    char GetSymbol() const;
    int GetX() const;
    int GetY() const;
    int GetHp() const;
    int GetAttackPower() const;
    void TakeDamage(int damage);
    void SetHp(int newHp);
    void SetAttackPower(int newAttackPower);
};
