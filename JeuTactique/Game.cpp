#include "Game.h"
#include <iostream>
#include <conio.h>

#include "Golem.h"
#include "Reaper.h"
#include "Spectre.h"

Game::Game() : hero(1, 1), emptyCell('.') {
    // Initialize monsters
    monsters.push_back(new Golem(5, 5));
    InitializeGrid();
}

void Game::InitializeGrid() {
    // Initialize grid with empty cells
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            grid[i][j] = emptyCell;
        }
    }
}

void Game::Run() {
    while (!IsGameOver()) {
        Render();
        HandleInput();
        if (!IsGameOver()) {  // Check if the game ended during hero's turn
            ProcessMonstersTurn();
        }
        Update();
    }
    std::cout << "Game Over! You explored " << currentRoom << " rooms." << std::endl;
}

void Game::Update() {
    // Clear previous positions
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            grid[i][j] = emptyCell;
        }
    }

    // Update game state
    grid[hero.GetY()][hero.GetX()] = hero.GetSymbol();
    for (auto monster : monsters) {
        grid[monster->GetY()][monster->GetX()] = monster->GetSymbol();
    }

    // Check if all monsters are defeated
    if (monsters.empty()) {
        TransitionToNextRoom();
    }
}

void Game::Render() {
    system("cls");  // Clear console (Windows-specific)
    
    // Render the grid
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            std::cout << grid[i][j];
        }
        std::cout << std::endl;
    }
    
    // Render hero stats
    std::cout << "Hero HP: " << hero.GetHp() << " | Attack: " << hero.GetAttackPower() << std::endl;
    std::cout << "Current Room: " << currentRoom << std::endl;
    
    // Render combat log
    std::cout << "\nCombat Log:" << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    std::queue<std::string> tempLog = combatLog;
    while (!tempLog.empty()) {
        std::cout << tempLog.front() << std::endl;
        tempLog.pop();
    }
    std::cout << std::string(40, '-') << std::endl;
}

void Game::AddToLog(const std::string& message) {
    combatLog.push(message);
    if (combatLog.size() > LOG_SIZE) {
        combatLog.pop();
    }
}

bool Game::HandleInput() {
    char input = _getch();  // Get character input without Enter (Windows-specific)
    int dx = 0, dy = 0;
    switch (input) {
    case 'w': dy = -1; break;
    case 's': dy = 1; break;
    case 'a': dx = -1; break;
    case 'd': dx = 1; break;
    case ' ': 
        AttackMonster(); 
        return true;  // Turn taken
        default: 
            return false;  // Invalid input, turn not taken
    }
    
    int newX = hero.GetX() + dx;
    int newY = hero.GetY() + dy;
    
    if (IsValidMove(newX, newY)) {
        hero.Move(dx, dy);
        AddToLog("Hero moved.");
        return true;  // Turn taken
    } else {
        AddToLog("Hero cannot move there!");
        return false;  // Turn not taken
    }
}

void Game::MonsterAttack(Monster* monster) {
    int damage = monster->GetAttackPower();
    hero.TakeDamage(damage);
    AddToLog(monster->GetName() + " attacks hero for " + std::to_string(damage) + " damage.");
    AddToLog("Hero HP: " + std::to_string(hero.GetHp()));
}


bool Game::IsAdjacentToHero(const Monster* monster) const {
    int dx = abs(monster->GetX() - hero.GetX());
    int dy = abs(monster->GetY() - hero.GetY());
    return (dx == 1 && dy == 0) || (dx == 0 && dy == 1);
}

bool Game::IsValidMove(int x, int y) const {
    // Check if the position is within the grid bounds
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
        return false;
    }
    
    // Check if the position is occupied by a monster
    for (const auto& monster : monsters) {
        if (monster->GetX() == x && monster->GetY() == y) {
            return false;
        }
    }
    
    // The move is valid if we've passed all checks
    return true;
}

bool Game::IsValidMoveForMonster(int x, int y) const {
    // Check if the position is within the grid bounds
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
        return false;
    }
    
    // Check if the position or its adjacent cells are occupied by the hero or other monsters
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            int checkX = x + dx;
            int checkY = y + dy;
            if (checkX >= 0 && checkX < WIDTH && checkY >= 0 && checkY < HEIGHT) {
                if (checkX == hero.GetX() && checkY == hero.GetY()) {
                    return false;
                }
                for (const auto& monster : monsters) {
                    if (monster->GetX() == checkX && monster->GetY() == checkY) {
                        return false;
                    }
                }
            }
        }
    }
    
    // The move is valid if we've passed all checks
    return true;
}

void Game::AttackMonster() {
    Monster* target = GetAdjacentMonster();
    if (target) {
        int damage = hero.GetAttackPower();
        hero.Attack(*target);
        AddToLog("Hero attacks " + target->GetName() + " for " + std::to_string(damage) + " damage.");
        if (!target->IsAlive()) {
            AddToLog(target->GetName() + " is defeated!");
            monsters.erase(std::remove(monsters.begin(), monsters.end(), target), monsters.end());
            delete target;
        } else {
            AddToLog(target->GetName() + " HP: " + std::to_string(target->GetHp()));
        }
    } else {
        AddToLog("No monster in range to attack!");
    }
}

Monster* Game::GetAdjacentMonster() const {
    for (auto monster : monsters) {
        int dx = abs(monster->GetX() - hero.GetX());
        int dy = abs(monster->GetY() - hero.GetY());
        if ((dx == 1 && dy == 0) || (dx == 0 && dy == 1)) {
            return monster;
        }
    }
    return nullptr;
}

bool Game::IsGameOver() const {
    return !hero.IsAlive();
}

void Game::GenerateRoom() {
    InitializeGrid();
    
    // Clear existing monsters
    for (auto monster : monsters) {
        delete monster;
    }
    monsters.clear();

    // Randomly place monsters
    int numMonsters = std::uniform_int_distribution<>(2, 5)(rng);
    for (int i = 0; i < numMonsters; ++i) {
        int x, y;
        do {
            x = std::uniform_int_distribution<>(0, WIDTH - 1)(rng);
            y = std::uniform_int_distribution<>(0, HEIGHT - 1)(rng);
        } while (!IsValidMove(x, y) || (x == hero.GetX() && y == hero.GetY()));
        
        SpawnMonster(x, y);
    }
}

void Game::TransitionToNextRoom() {
    currentRoom++;
    std::cout << "Entering room " << currentRoom << "..." << std::endl;
    _getch();  // Wait for key press
    
    // Reset hero position
    hero.Move(1 - hero.GetX(), 1 - hero.GetY());  // Move hero to (1, 1)
    
    GenerateRoom();
}

void Game::SpawnMonster(int x, int y) {
    int monsterType = std::uniform_int_distribution<>(0, 2)(rng);
    Monster* monster = nullptr;
    switch (monsterType) {
    case 0:
        monster = new Golem(x, y);
        break;
    case 1:
        monster = new Spectre(x, y);
        break;
    case 2:
        monster = new Reaper(x, y);
        break;
    }
    if (monster) {
        monsters.push_back(monster);
    }
}

void Game::ProcessMonstersTurn() {
    for (auto& monster : monsters) {
        if (IsAdjacentToHero(monster)) {
            MonsterAttack(monster);
        } else {
            // Existing movement logic
            int monsterDx = 0, monsterDy = 0;
            
            // Calculate direction towards hero
            int directionX = hero.GetX() - monster->GetX();
            int directionY = hero.GetY() - monster->GetY();
            
            // Normalize direction
            if (directionX != 0) directionX = directionX > 0 ? 1 : -1;
            if (directionY != 0) directionY = directionY > 0 ? 1 : -1;

            if (dynamic_cast<Golem*>(monster)) {
                // Golem doesn't move
                continue;
            } else if (dynamic_cast<Spectre*>(monster)) {
                // Spectre moves away from hero
                monsterDx = -directionX;
                monsterDy = -directionY;
            } else if (dynamic_cast<Reaper*>(monster)) {
                // Reaper moves towards hero
                monsterDx = directionX;
                monsterDy = directionY;
            }

            // Check if the move is valid and perform it
            int newX = monster->GetX() + monsterDx;
            int newY = monster->GetY() + monsterDy;
            if (IsValidMoveForMonster(newX, newY)) {
                monster->Move(monsterDx, monsterDy);
                AddToLog(monster->GetName() + " moved.");
            }
        }
    }
}