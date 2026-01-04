#ifndef GAME_H
#define GAME_H
#include <vector>

class Game {
public:
    // Конструктор
    Game(int rows, int cols);

    // Задава персонализирани правила за раждане и оцеляване
    void setRules(const std::vector<int>& birth,
                  const std::vector<int>& survival);

    // Запълва полето със случайни клетки
    void randomizeGrid();

    // Стартира симулацията
    void run();

private:
    int rows;
    int cols;

    std::vector<std::vector<int>> grid;
    std::vector<bool> ruleBirth;
    std::vector<bool> ruleSurvival;

    // Помощни методи
    void printGrid() const;
    void computeNextGeneration();
    int countNeighbors(int x, int y) const;
    void clearScreen() const;
};

#endif
