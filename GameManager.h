//
// Created by Biomfire on 2019. 05. 08..
//

#ifndef CPP11HF2_GAMEMANAGER_H
#define CPP11HF2_GAMEMANAGER_H

#include <iostream>
#include "GameDatabase.h"
#include "GameDisplay.h"

class GameManager {
    // A játék állapotát tároló adattipus
    enum State{
        MENU,
        GAME
    };
    //Az adatbázis
    GameDatabase database;
    //A megjelenítő
    GameDisplay display;
    State state = GAME;
    //Ki kell-e lépni
    bool exit = false;
    //Hányszor tévedet a játékos
    int misses = 0;
public:
    void GameLoop();


};


#endif //CPP11HF2_GAMEMANAGER_H
