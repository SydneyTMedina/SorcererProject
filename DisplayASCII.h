#include <iostream>
#include <vector>
#include "Spell.h"
#include "Player.h"
#include "BattleField.h"
using namespace std;

#ifndef  DISPLAYASCII_H
#define DISPLAYASCII_H

class DisplayASCII
{
private:
    vector<string> getCardLineData(Spell spell);
public:
    DisplayASCII();
    bool display(string fileName);
    bool displayCard(Spell spell);
    bool displayHand(Player player);
    bool displayBattleField(BattleField battleField, Player player);
};

#endif
