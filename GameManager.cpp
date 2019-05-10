
#include <fstream>
#include "GameManager.h"
void GameManager::GameLoop() {
    //Stringstreamből olvassuk be a tesztadatokat, mivel ez a legegyszerűbb, ofstream-et is lehet használni.
    std::string testdata = "aroma adoma apuka strand start zizeg zokni";
    std::stringstream test(testdata);
    // Betöltjük az adatokat az adatbázisba
    database.loadData(test);
    //És új játékot kezdünk 5 betű hosszúságú szavakkal
    database.newGame(5);
    //Kirajzolunk mindent amire szükségünk van
    display.drawCorrectLetters(database.getCurrentWord());
    display.drawHangman(misses);
    display.drawMissedLetters(database.getusedLetters());
    display.printScreen();
    //És elkezdjük a lööpöt
    while (!exit) {
        switch (state) {
            case MENU:
                break;
            case GAME:
                //Beolvasunk egy karaktert
                char c;
                std::cin >> c;
                //Amiről megnézzük hogy benne van-e a szóban
                if(database.guessChar(c)) {
                    //Ha igen akkor megnézzük hogy pontosan hányszor is
                    display.drawCorrectLetters(database.getCurrentWord());
                    //És megnézzük hogy eljutottunk-e jó megoldáshoz
                    if(database.isCorrect()) {
                        //Ha igen akkor kiirjuk, és kilépünk
                        display.drawText("Victory");
                        exit = true;
                    }
                }
                else {
                    //Ha nincs benne a szóban kirajzoljuk az új akasztott emberünket
                    misses++;
                    display.drawHangman(misses);
                    //És kiirjuk a használt betűt
                    display.drawMissedLetters(database.getusedLetters());
                    //Ha túllépjük a 6 lehetőséget akkor pedig vesztünk
                    if(misses == 6) {
                        display.drawText("Fail");
                        exit = true;
                    }
                }
                break;
            default:
                break;
        }
        //Minden ciklus végén újra rajzoljuk a képernyőt
        display.printScreen();
    }
}