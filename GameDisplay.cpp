

#include "GameDisplay.h"
//initializálja a hangman ábrákat, nagyon sok sor, máshol zavaró
void GameDisplay::initHangmanStages(){
    hangmanStages = {{{"+---+ "},
                      {"|   | "},
                      {"|     "},
                      {"|     "},
                      {"|     "},
                      {"|     "},
                      {"===== "}},
                     {{"+---+ "},
                      {"|   | "},
                      {"|   o "},
                      {"|   | "},
                      {"|     "},
                      {"|     "},
                      {"===== "}},
                     {{"+---+ "},
                      {"|   | "},
                      {"|   o "},
                      {"|   |\\"},
                      {"|     "},
                      {"|     "},
                      {"===== "}},
                     {{"+---+ "},
                      {"|   | "},
                      {"|   o "},
                      {"|  /|\\"},
                      {"|     "},
                      {"|     "},
                      {"===== "}},
                     {{"+---+ "},
                      {"|   | "},
                      {"|   o "},
                      {"|  /|\\"},
                      {"|    \\"},
                      {"|     "},
                      {"===== "}},
                     {{"+---+ "},
                      {"|   | "},
                      {"|   o "},
                      {"|  /|\\"},
                      {"|  / \\"},
                      {"|     "},
                      {"===== "}}};
    }
//Ctor
GameDisplay::GameDisplay() {
    //Csinál egy üres képernyőt
    for(int i = 0; i < rows; ++i) {
        std::vector<char> tmp;
        for (int j = 0; j < colums; ++j)
            tmp.push_back(' ');
        screen.push_back(tmp);
    }
    initHangmanStages();
}
//Kirajzolja keretestül a képernyőt
void GameDisplay::printScreen(){
    std::cout<<'+';
    for(int i = 0; i < colums; ++i)
        std::cout<<'-';
    std::cout<<'+'<<'\n';
    for(const auto& row : screen) {
        std::cout << '|';
        for (auto c : row)
            std::cout << c;
        std::cout << '|' << '\n';
    }
    std::cout<<'+';
    for(int i = 0; i < colums; ++i)
        std::cout<<'-';
    std::cout<<'+'<<'\n';
}
//Kirajzolja az akasztott embert
void GameDisplay::drawHangman(const int stage){
    int x = colums/2,y=rows/5;
    for(int i = 0; i < hangmanStages[stage].size(); i++){
        for(int j = 0; j < hangmanStages[stage][i].size();++j){
            screen[i+y][j+x] = hangmanStages[stage][i][j];
        }
    }
}
//Kiirja a helyes betűket
void GameDisplay::drawCorrectLetters(const std::vector<char>& correctChars){
    int x = colums/2; int y = rows/3*2;
    for(int i = 0; i < correctChars.size(); ++i){
        screen[y][2*i+x] = correctChars[i];
        screen[y+1][2*i+x] = '=';
    }
}
//Kiirja a téves betűket
void GameDisplay::drawMissedLetters(const std::vector<char>& missedChars){
    int x = colums/4*3, y = rows/4*3;
    int xsiz = 5, ysiz = 4;
    for(int i = 0; i < missedChars.size(); i++){
        screen[y+i/xsiz][x+i%xsiz] = missedChars[i];
    }
}
//Kiir vmi random szöveget
void GameDisplay::drawText(std::string text){
    int x = colums/2; int y = rows/3*2+3;
    for(int i = 0; i < text.size(); ++i)
        screen[y][x+i] = text[i];
}