#include <iostream>
#include <vector>
#include "Game.h"

Game::Game() {
    
}

void Game::removeCharacter(int _index) {
    availibleCharacters.erase(availibleCharacters.begin() + _index);
}

void Game::winGame() {
    wonGame = true;
    cout << "You have captured all the cities! Congratulations, you have won and become the most powerful sorcerer in the world!" << endl;
    exit(0);
}

void Game::loseGame(int _condition) {
    if(_condition == 1) {
        cout << "You have run out of spells to cast! By doing so, you have no more power and were killed." << endl << endl << "GAME OVER" << endl;
    }
    else if(_condition == 2) {
        cout << "Your opponent has captured the battlefield! You can no longer become the most powerful sorcerer." << endl << endl << "GAME OVER" << endl; 
    }
    exit(0);

}

void Game::takeOverCity() {
    citiesCaptured++;
    if(citiesCaptured == 3) {
        winGame();
    }
}