//
// Created by Biomfire on 2019. 05. 08..
//

#ifndef CPP11HF2_GAMEDATABASE_H
#define CPP11HF2_GAMEDATABASE_H

#include <vector>
#include <string>
#include <regex>
#include <iostream>
class GameDatabase {
    bool init = false;
    int wordLenght  = 5;
    std::vector<char> currentWord;
    std::vector<char> usedLetters;
    std::vector<std::string> stringDatabase;

public:
    bool isCorrect();
    std::vector<std::string> possibleStrings;
    const std::vector<char>& getCurrentWord() const{ return currentWord;}
    const std::vector<char>& getusedLetters() const{ return  usedLetters;}
    const int getWordLenght() const{return wordLenght;}
    GameDatabase();
    explicit GameDatabase(std::istream& is);
    void loadData(std::istream& is);
    void newGame(int _wordLenght);
    bool guessChar(char c);
};


#endif //CPP11HF2_GAMEDATABASE_H
