/*
CSCI1300 - Project 3
Luca Voeller
Sydney Medina
*/

#include <iostream>
#include <vector>
#include <fstream>
#include "Game.h"

//Nothing to construct initially 
Game::Game() {
}

//removes the character at the given index
void Game::removeCharacter(int _index) {
    availibleCharacters.erase(availibleCharacters.begin() + _index);
}

//sets the wonGame status to true and reads the win message. Exits the game
void Game::winGame() {
    wonGame = true;
    cout << "You have captured all the cities! Congratulations, you have won and become the most powerful sorcerer in the world!" << endl;
    ofstream file;
    file.open("statsFiles/gameOutCome.txt");
    if(file.is_open()) {
        file << "Won";
        file.close();
    }
    exit(0);
}

//Keeps the wonGame status as false and reads one of 2 loose messages. Exits the game
void Game::loseGame(int _condition) {
    if(_condition == 1) {
        cout << "You have run out of spells to cast! By doing so, you have no more power and were killed." << endl << endl << "GAME OVER" << endl;
    }
    else if(_condition == 2) {
        cout << "Your opponent has captured the battlefield! You can no longer become the most powerful sorcerer." << endl << endl << "GAME OVER" << endl; 
    }
    ofstream file;
    file.open("statsFiles/gameOutCome.txt");
    if(file.is_open()) {
        file << "Lost";
        file.close();
    }
    exit(0);

}

//returns a string of the first availible character
string Game::getFirstCharacter() {
    string toReturn = availibleCharacters.at(0);
    return toReturn;
}