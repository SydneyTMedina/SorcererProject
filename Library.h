#include <iostream>
#include <vector>
#include "Spell.h"
using namespace std;
#ifndef LIBRARY_H
#define LIBRARY_H

/*
Has all the cards in a spell vector for refrence
All libraries are player specific, and custom built by choosing 3 decks
*/
class Library
{
private:
    vector<Spell> spells;
    void addDeck(string filename);

public:
    Library();
    Library(string file1, string file2, string file3);
    void setSpells(vector<Spell> newSpells);
    Spell getSpellAt(int pos);
    vector<Spell> getSpells();
    int getSpellId(Spell spell);
};

#endif

