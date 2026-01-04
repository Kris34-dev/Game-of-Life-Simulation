#include "Game.h"
#include <iostream>  // std::cout, std::endl
#include <vector>    // std::vector
#include <cstdlib>   // rand(), srand()
#include <ctime>     // time()
#include <thread>    // std::this_thread::sleep_for
#include <chrono>    // std::chrono::milliseconds

// Конструктор: Инициализира полето и генератора за случайни числа
Game::Game(int r, int c) : rows(r), cols(c) {
    // Инициализираме полето с необходимия размер, пълно с нули.
    grid.assign(rows, std::vector<int>(cols, 0));
    // Инициализираме правилата по подразбиране (празни).
    ruleBirth.assign(9, false);
    ruleSurvival.assign(9, false);
    // Инициализация на генератора за случайни числа.
    srand(time(0));
}

// Метод за задаване на персонализирани правила за раждане и оцеляване
void Game::setRules(const std::vector<int>& birth, const std::vector<int>& survival) {
    // Нулираме текущите правила
    ruleBirth.assign(9, false);
    ruleSurvival.assign(9, false);
    // Задаваме правилата за раждане
    for (int count : birth) {
        if (count >= 0 && count <= 8) {
            ruleBirth[count] = true;
        }
    }
    // Задаваме правилата за оцеляване
    for (int count : survival) {
        if (count >= 0 && count <= 8) {
            ruleSurvival[count] = true;
        }
    }
}

// Метод за запълване на полето със случайни живи/мъртви клетки
void Game::randomizeGrid() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = rand() % 2; // 50% вероятност за жива клетка
        }
    }
}

// Изчиства екрана на конзолата
void Game::clearScreen() const {
    // ANSI escape код за изчистване на екрана на конзолата. Работи на повечето терминали.
    std::cout << "\033[2J\033[1;1H";
}

// Отпечатва текущото състояние на полето
void Game::printGrid() const {
    clearScreen();
    std::cout << "--- Игра на живота (Персонализирани правила) ---" << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 1) std::cout << "O"; // Символ за жива клетка
            else std::cout << ".";                 // Символ за мъртва клетка
        }
        std::cout << std::endl;
    }
}

// Брои живите съседи на дадена клетка (x, y)
int Game::countNeighbors(int x, int y) const {
    int sum = 0;
    // Обхождаме всички 8 съседни клетки
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            // Пропускаме самата клетка
            if (i == 0 && j == 0) continue;

            // Формула за броене на съседи с "зацикляне" на полето (тороидна топология).
            // Ако клетката излезе от единия край, се появява от другия.
            int row = (x + i + rows) % rows;
            int col = (y + j + cols) % cols;

            sum += grid[row][col];
        }
    }
    return sum;
}

// Изчислява следващото поколение на играта
void Game::computeNextGeneration() {
    // Създаваме временен буфер за изчисляване на следващото състояние.
    std::vector<std::vector<int>> nextGrid = grid;

    // Обхождаме всяка клетка в текущата решетка
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int neighbors = countNeighbors(i, j); // Брой живи съседи

            if (grid[i][j] == 1) { // Ако текущата клетка е жива
                if (ruleSurvival[neighbors]) {
                    nextGrid[i][j] = 1; // Клетката оцелява
                } else {
                    nextGrid[i][j] = 0; // Клетката умира от глад или пренаселване
                }
            } else { // Ако текущата клетка е мъртва
                if (ruleBirth[neighbors]) {
                    nextGrid[i][j] = 1; // Клетката се ражда
                } else {
                    nextGrid[i][j] = 0; // Клетката остава мъртва
                }
            }
        }
    }
    // Актуализираме текущата решетка с новото състояние.
    grid = nextGrid;
}

// Основен цикъл на симулацията
void Game::run() {
    while (true) {
        printGrid();           // Отпечатва текущото поколение
        computeNextGeneration(); // Изчислява и преминава към следващото поколение
        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Пауза за визуализация на анимацията. 
    }
}