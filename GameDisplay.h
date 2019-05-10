#ifndef CPP11HF2_GAMEDISPLAY_H
#define CPP11HF2_GAMEDISPLAY_H

#include <iostream>
#include <vector>
#include <string>
#include <exception>
class GameDisplay {
    class DrawException : public std::exception{};
    int rows = 20;
    int colums = 110;
    std::vector<std::vector<char>> screen;
    std::vector<std::vector<std::string>> hangmanStages;
    void initHangmanStages();
public :
    GameDisplay();
    void printScreen() ;
    void drawHangman(int);
    void drawCorrectLetters(const std::vector<char>&);
    void drawMissedLetters(const std::vector<char>&);
    void drawText(std::string text);
};

#endif //CPP11HF2_GAMEDISPLAY_H
