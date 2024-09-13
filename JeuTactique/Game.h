#pragma once
#include <vector>
#include "Hero.h"
#include "Monster.h"

class Game {
private:
    static const int WIDTH = 20;
    static const int HEIGHT = 10;
    Hero hero;
    std::vector<Monster*> monsters;
    char grid[HEIGHT][WIDTH];
    char emptyCell; 

    public:
    Game();
    void Run();
    void Update();
    void Render();
    void HandleInput();
    bool IsGameOver() const;
    void InitializeGrid();
    void AttackMonster();
    Monster* GetAdjacentMonster() const;
    bool IsValidMove(int x, int y) const;
};