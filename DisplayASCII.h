#include <iostream>
#include <vector>
#include "Spell.h"
#include "Player.h"
#include "BattleField.h"
#include <vector>
using namespace std;

#ifndef  DISPLAYASCII_H
#define DISPLAYASCII_H


/*
Class definition for DisplayASCII
This has functions to display large amounts of text to the player for asthetic or informational purposes
*/
class DisplayASCII
{
private:
    vector<string> getCardLineData(Spell spell);
    vector<string> abilityDescriptions = {"", "Gives +1 attack", "Gives +2 attack", "Gives the opponent -1 attack", "Gives the opponent -2 attack", 
    "Removes the first enemy attack", "Memorizes three spells", "", "", "Gives +2 Mana", "Gives +4 Mana", "Removes the first enemy attack", 
    "Adds +3 Health to battlefield", "Adds +5 Health to battlefield", "Gives +4 Attack", "Doubles your total Damage", "Halves the enemies total damage", 
    "Kills all minions"};
public:
    DisplayASCII();
    bool display(string fileName);
    bool displayCard(Spell spell, bool _showAbility);
    bool displayHand(Player player);
    bool displayBattleField(BattleField battleField, Player player);
    bool displayEnemyBattleField(BattleField battleField, Player npc);
};

#endif
