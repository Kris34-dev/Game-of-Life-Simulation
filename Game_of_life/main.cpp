#include "Game.h"
#include <iostream>   // std::cout, std::endl
#include <vector>     // std::vector
#include <string>     // std::string
#include <sstream>    // std::stringstream

// Помощна функция за извличане на числа от въведен ред (напр. "2 3")
std::vector<int> getNumbersFromInput() {
    std::vector<int> numbers;
    std::string line;
    std::getline(std::cin, line); // Чете целия ред
    std::stringstream ss(line);  // Използва stringstream за парсване на числата
    int num;
    while (ss >> num) {          // Извлича числата едно по едно
        numbers.push_back(num);
    }
    return numbers;
}

// Главна функция на програмата
int main() {
    int rows = 20; // Височина на полето по подразбиране
    int cols = 40; // Ширина на полето по подразбиране

    std::cout << "--- Настройка на Играта на живота на Конуей ---" << std::endl;
    std::cout << "Размерът на полето по подразбиране е " << rows << "x" << cols << ". Натиснете Enter, за да го използвате." << std::endl;

    std::cout << "\nВъведете броя на съседите, при които мъртва клетка се РАЖДА (напр. '3' за стандартното правило): ";
    std::vector<int> birthRules = getNumbersFromInput();

    std::cout << "Въведете броя на съседите, при които жива клетка ОЦЕЛЯВА (напр. '2 3' за стандартното правило): ";
    std::vector<int> survivalRules = getNumbersFromInput();

    // Използване на стандартни правила, ако потребителят не е въвел нищо
    if (birthRules.empty()) birthRules.push_back(3);
    if (survivalRules.empty()) {
        survivalRules.push_back(2);
        survivalRules.push_back(3);
    }
    
    // Създаване на обект от класа Game
    Game game(rows, cols);
    // Задаване на правилата
    game.setRules(birthRules, survivalRules);
    // Запълване на полето със случайни клетки
    game.randomizeGrid();
    
    // Стартиране на симулацията
    game.run();

    return 0; // Програмата завърши успешно
}