#include "Game.h"
#include <iostream>
#include <conio.h>

#include "Golem.h"

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
        Update();
        Render();
        HandleInput();
    }
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
}

void Game::Render() {
    system("cls");  // Clear console (Windows-specific)
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            std::cout << grid[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << "Hero HP: " << hero.GetHp() << " | Attack: " << hero.GetAttackPower() << std::endl;
}

void Game::HandleInput() {
    char input = _getch();  // Get character input without Enter (Windows-specific)
    int dx = 0, dy = 0;
    switch (input) {
    case 'w': dy = -1; break;
    case 's': dy = 1; break;
    case 'a': dx = -1; break;
    case 'd': dx = 1; break;
    case ' ': AttackMonster(); return;  // Attack on space bar
    }
    
    int newX = hero.GetX() + dx;
    int newY = hero.GetY() + dy;
    
    if (IsValidMove(newX, newY)) {
        // Clear the hero's current position
        grid[hero.GetY()][hero.GetX()] = emptyCell;
        
        // Move the hero
        hero.Move(dx, dy);
        
        // Update the hero's new position
        grid[hero.GetY()][hero.GetX()] = hero.GetSymbol();
    } else {
        std::cout << "Cannot move there!" << std::endl;
        _getch();  // Wait for key press
    }
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

void Game::AttackMonster() {
    Monster* target = GetAdjacentMonster();
    if (target) {
        hero.Attack(*target);
        std::cout << "Hero attacks " << target->GetName() << "!" << std::endl;
        if (!target->IsAlive()) {
            std::cout << target->GetName() << " is defeated!" << std::endl;
            monsters.erase(std::remove(monsters.begin(), monsters.end(), target), monsters.end());
            delete target;
        } else {
            std::cout << target->GetName() << " has " << target->GetHp() << " HP left." << std::endl;
        }
        _getch();  // Wait for key press
    } else {
        std::cout << "No monster in range to attack!" << std::endl;
        _getch();  // Wait for key press
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
    return !hero.IsAlive() || monsters.empty();
}