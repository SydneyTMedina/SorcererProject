#include <iostream>
#include <vector>
using namespace std;

#ifndef  GAME_H
#define GAME_H

class Game
{
private:
    vector<string> availibleCharacters = {"Miselda", "Tegu", "Zevrane", "Ariaspes"};
    int citiesCaptured = 0;
    bool wonGame = false;
public:
    Game();
    void loseGame(int condition);
    void winGame();
    void takeOverCity();
    void removeCharacter(int index);
};

#endif