#pragma once
#include <queue>
#include <random>
#include <vector>
#include "Hero.h"
#include "Monster.h"

class Game {
public:
    Game();
    void Run();
    
private:
    static const int WIDTH = 20;
    static const int HEIGHT = 10;
    Hero hero;
    std::vector<Monster*> monsters;
    char grid[HEIGHT][WIDTH];
    char emptyCell;
    int currentRoom;
    std::mt19937 rng;
    static const int LOG_SIZE = 5;  // Number of log messages to display
    std::queue<std::string> combatLog;
    
    void Update();
    void Render();
    bool HandleInput();
    bool IsGameOver() const;
    void InitializeGrid();
    void AttackMonster();
    Monster* GetAdjacentMonster() const;
    bool IsValidMove(int x, int y) const;
    void GenerateRoom();
    void TransitionToNextRoom();
    void SpawnMonster(int x, int y);
    bool IsValidMoveForMonster(int x, int y) const;
    void MonsterAttack(Monster* monster);
    bool IsAdjacentToHero(const Monster* monster) const;
    void ProcessMonstersTurn();
    void AddToLog(const std::string& message);

};