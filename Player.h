#include <iostream>
#include <vector>
#include "Library.h"
#include "Game.h"
#include "Spell.h"
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
    Library playerLibraryBackup;
    vector<int> playerDeck;
    vector<int> playerHand;
    vector<int> playerGraveyard;
    bool NPC = false;
    string name;
    Game game;
    int actions = 10;
    int mana = 6;
public:
    Player(Library &playerDeck, bool npc, string name, Game currentGame);
    int getActions();
    void setActions(int numActions);
    int getMana();
    void setMana(int mana);
    void resetPlayer();
    vector<int> getPlayerHand();

    int drawSpells();
    void removeSpellFromHand(int index);
    void putSpellInGraveyard(int index);
    bool compareFunction(int _a, int _b);

    void shuffleDeck();
    bool isNpc();
    int getSpellIDHandPos(int pos);
    Spell getSpellInHand(int pos);
    void sortHand();
    void displayHand();
    void displayGameInfo();

    int getHandSize();
    Library getLibrary();
    string getName();
    void gainTwoMana();
};
#endif