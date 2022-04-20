#include <iostream>
#include <vector>
using namespace std;

#ifndef  GAME_H
#define GAME_H

class Game
{
private:
    vector<string> availibleCharacters = {"Miselda", "Tegu", "Zevrane", "Ariaspes"};
    bool wonGame = false;
public:
    Game();
    void loseGame(int condition);
    void winGame();
    void removeCharacter(int index);
    string getFirstCharacter();
};

#endif