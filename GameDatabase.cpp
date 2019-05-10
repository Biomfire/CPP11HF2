//
// Created by Biomfire on 2019. 05. 08..
//

#include "GameDatabase.h"
//Base contructor
GameDatabase::GameDatabase() {
    //A jelenlegi megoldást kinullázzuk
    for (int i = 0; i < wordLenght; ++i)
        currentWord.push_back(' ');
}
//Ctor ha meg van adva az adatforrás
GameDatabase::GameDatabase(std::istream &is) {
    for (int i = 0; i < wordLenght; ++i)
        currentWord.push_back(' ');
    std::string word;
    while (is >> word) {
        stringDatabase.push_back(word);
    }
    init = true;
}
//Későbbi adatbetöltésre jó
void GameDatabase::loadData(std::istream &is) {
    std::string word;
    while (is >> word) {
        stringDatabase.
                push_back(word);
    }
    init = true;
}
//Új játék kezdésére jó
void GameDatabase::newGame(int _wordLenght) {
    if (!init) return;
    wordLenght = _wordLenght;
    possibleStrings.clear();
    for (const auto& word : stringDatabase) {
        if (word.length() == wordLenght)
            possibleStrings.push_back(word);
    }
    currentWord.clear();
    for (int i = 0; i < wordLenght; ++i)
        currentWord.push_back(' ');
}
//Leellenőrzi hogy jó-e a currentWord
bool GameDatabase::isCorrect() {
    //Ha több megoldási lehetőség van akkor biztos nem
    if(possibleStrings.size()>1)
        return false;
    //De ha egy van, akkor is csak ha minden betűt kitalált már
    bool istheSame = true;
    for(int i = 0; i < wordLenght; ++i) {
        if (currentWord[i] != possibleStrings[0][i])
            istheSame = false;
    }
    return istheSame;
}
// Kitalálja a karaktert
bool GameDatabase::guessChar(char c) {
    //Leellenőrizzük hogy volt-e már
    for (const auto& ch : usedLetters)
        if (c == ch)
            return false;
    for (const auto& ch : currentWord)
        if (c == ch)
            return true;
    std::pair<int, int> bestHit(-1, 0);
    std::string regex;
    //Csinálunk egy regexet, ami megnézi h mennyi szó van amiben nincs benne a betű, ez lesz az összehasonlításunk alapja
    for (int j = 0; j < wordLenght; ++j)
        regex.append("[^").append(1, c).append("]");
    std::regex exp(regex);
    for (const auto& word : possibleStrings) {
        if (std::regex_match(word, exp))
            bestHit.second++;
    }
    //Minden karakterre összehasonlítunk
    for (int i = 0; i < wordLenght; ++i) {
        int cnt = 0;
        //ez lesz a regexünk
        std::string regex;
        //Amit feltöltünk pontokkal, kivéve egy helyett
        for (int j = 0; j < wordLenght - 1; ++j)
            regex.append(".");
        //Ahova a karakter kerül
        regex.insert(i, 1, c);
        std::regex exp(regex);
        //Maximum keresés
        for (const auto& word : possibleStrings) {
            if (std::regex_match(word, exp))
                cnt++;
        }
        if (cnt > bestHit.second)
            bestHit = {i, cnt};
    }
    //Ha a nincs szó a legjobb megoldás
    if (bestHit.first == -1) {
        //Regexel kikeressük és töröljük a lehetséges szavak közül azokat amiben benne vannak
        std::string regex;
        for (int j = 0; j < wordLenght; ++j)
            regex.append("[^").append(1, c).append("]");
        std::regex exp(regex);
        int actual = 0;
        int originalSize = possibleStrings.size();
        for (int i = 0; i < originalSize; ++i) {
            if (std::regex_match(possibleStrings[actual], exp))
                actual++;
            else
                possibleStrings.erase(possibleStrings.begin() + actual);
        }
        //És elmenjtjük a sikertelen betűk közé
        usedLetters.push_back(c);
        return false;
    } else {
        //Itt is hasonlóan töröljük a nem megfelelő szavakat
        std::string regex;
        for (int j = 0; j < wordLenght - 1; ++j)
            regex.append(".");
        regex.insert(bestHit.first, 1, c);
        std::regex exp(regex);
        int actual = 0;
        int originalSize = possibleStrings.size();
        for (int i = 0; i < originalSize; ++i) {
            if (std::regex_match(possibleStrings[actual], exp))
                actual++;
            else
                possibleStrings.erase(possibleStrings.begin() + actual);
        }
        for (int i = 0; i < wordLenght; i++) {
            bool isinsideAll = true;
            for (auto word : possibleStrings) {
                if (word[i] != c)
                    isinsideAll = false;
            }
            if (isinsideAll) {
                currentWord[i] = c;
            }
        }
        return true;
    }
}