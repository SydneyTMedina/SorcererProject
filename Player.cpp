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
#include "Game.h"
using namespace std;

/*
Contructor for a player class. Sets the library for the player and if it is an npc or not
Sets the library
Initializes the player library by adding values to it up to the size of the library
Clears the grave yard
Shuffles the library and draws 5 cards
*/
Player::Player(Library deck, bool _isNPC, string _name, Game _game) {
    game = _game;
    isNPC = _isNPC;
    name = _name;
    playerLibrary.setSpells(deck.getSpells());
    for(int i = 0; i < playerLibrary.getSpells().size(); i++) {
        playerDeck.push_back(i);
    }
    shuffleDeck();
    for(int i = 0; i < 4; i++) {
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
    if(isNPC == true) {
        if(playerDeck.empty()) {
            //Win battlefield
            return 0;
        }
    }
    if(playerDeck.empty()){
        game.loseGame(1);
    } 
    
    playerHand.push_back(playerDeck.at(0));
    playerDeck.erase(playerDeck.begin() + 0);
    return 1;
}

//Plays a card from the hand onto the battlefield
bool Player::playCard(int handIndex, BattleField _battleField) {
    if(handIndex < 0) {
        return false;
    }
    if(isNPC == false) {
        int cost = playerLibrary.getSpellAt(playerHand.at(handIndex)).getSpellManaCost();
        if(cost > mana) cout << "You don't have enough mana to play this card!" << endl;
        else {
            mana = mana - cost;
            _battleField.addPlayerMinions(playerHand.at(handIndex));
            //playerLibrary.getSpellAt(playerHand.at(handIndex)).getSpellManaCost();
            removeSpellFromHand(handIndex);
            return true;
        }   
    }
    else {
        int cost = playerLibrary.getSpellAt(playerHand.at(handIndex)).getSpellManaCost();
        mana = mana - cost;
        _battleField.addEnemyMinions(playerHand.at(handIndex));
        removeSpellFromHand(handIndex);
        return true;
    }
    return false;
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
int Player::getSpellIDHandPos(int _pos) {
    if(_pos < 0 || _pos > playerHand.size()) return -1;
    return playerHand.at(_pos);
}

//Displays crucial game info to the player
void Player::displayGameInfo() {
    cout << endl << "You have " << getMana() << " mana and have " << getActions() << " actions left." << endl; 
}

int Player::getHandSize() {
    return playerHand.size();
}

Library Player::getLibrary() {
    return playerLibrary;
}

string Player::getName() {
    return name;
}

Spell Player::getSpell(int _pos) {
    return playerLibrary.getSpellAt(playerHand.at(_pos));
}





