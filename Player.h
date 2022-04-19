#include <iostream>
#include <vector>
#include "Library.h"
#include "BattleField.h"
#include "Game.h"
#ifndef PLAYER_H
#define PLAYER_H

using namespace std;

/*
Player class definition
Stores data like the players hand, the deck data base, and different storage
Stores player specific game elements
Also stores if the player is an NPC or not, so we can reuse this class for an npc player
*/
class Player
{
private:
    Library playerLibrary;
    vector<int> playerDeck;
    vector<int> playerHand;
    vector<int> playerGraveyard;
    bool isNPC = false;
    string name;
    Game game;
    int actions = 6;
    int mana = 6;
public:
    Player(Library playerDeck, bool npc, string name, Game currentGame);
    int getActions();
    void setActions(int numActions);
    int getMana();
    void setMana(int mana);

    int drawSpells();
    void removeSpellFromHand(int index);
    void putSpellInGraveyard(int index);

    void shuffleDeck();
    bool playCard(int handIndex, BattleField _battleField);
    int getSpellInHandPos(int pos);
    void sortHand();
    void displayHand();
    void displayGameInfo();

    int getHandSize();
    Library getLibrary();
    string getName();
};
#endif