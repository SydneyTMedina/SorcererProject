#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include "Player.h"
#include "Library.h"
#include "BattleField.h"
using namespace std;

/*
Contructor for a player class. Sets the library for the player and if it is an npc or not
Sets the library
Initializes the player library by adding values to it up to the size of the library
Clears the grave yard
Shuffles the library and draws 5 cards
*/
Player::Player(Library deck, bool _isNPC) {
    isNPC = _isNPC;
    playerLibrary.setSpells(deck.getSpells());
    for(int i = 0; i < playerLibrary.getSpells().size(); i++) {
        playerDeck.push_back(i);
    }
    playerGraveyard.clear();
    shuffleDeck();
    for(int i = 0; i < 6; i++) {
        drawSpells();
    }
}

//Sets the number of actions a player has
void Player::setActions(int _numActions){
    actions = _numActions;
}

//Gets the number of actions a player has
int Player::getActions() {
    return actions;
}

//Gets the amount of mana
int Player::getMana() {
    return mana;
}

//Sets the amount of mana
void Player::setMana(int _mana) {
    mana = _mana;
}

//Draws spells from the library
int Player::drawSpells() {
    playerHand.push_back(playerDeck.at(0));
    playerDeck.erase(playerDeck.begin() + 0);
    return 0;
}

//Plays a card from the hand onto the battlefield
void Player::playCard(BattleField _battleField) {
    
}

//Removes a spell from the player hand at a certain index
void Player::removeSpellFromHand(int _index) {
    playerHand.erase(playerHand.begin() + _index);
}

/*
Shuffles the library
Creates a random seed based on the time, and sets a random engine to that seed
Shuffles the playerDeck library without repeats
*/
void Player::shuffleDeck() {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine e(seed);
    shuffle(playerDeck.begin(), playerDeck.end(), e);
}

//Sorts the player hand alphabetically
void Player::sortHand() {

}

//Gets the card in a specific index of the hand vector
int Player::getSpellInHandPos(int _pos) {
    if(_pos < 0 || _pos > playerHand.size()) return -1;
    return playerHand.at(_pos);
}

//Displays the players hand with all of the currently held spells and their stats
void Player::displayHand() {

}

//Displays crucial game info to the player
void Player::displayGameInfo() {
    cout << "You have " << getMana() << " mana and have " << getActions() << " actions left." << endl; 
}





