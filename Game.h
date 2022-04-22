/*
CSCI1300 - Project 3
Luca Voeller
Sydney Medina
*/

#include <iostream>
#include <vector>
using namespace std;

#ifndef  GAME_H
#define GAME_H

/*
Class definition for Game
This vector has a vector for availible characters
Also has the game win or lose status
*/
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