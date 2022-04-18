#include <iostream>
#include <vector>
using namespace std;

#ifndef  GAME_H
#define GAME_H

class Game
{
private:
    vector<string> availibleCharacters;
    int citiesCaptured = 0;

public:
    void loseGame();
    void winGame();
    void takeOverCity(int cities);

    
};

#endif