#include <iostream>
#include <vector>
using namespace std;

#ifndef SPELL_H
#define SPELL_H

/*
Spell class definition
This class creates a specific spell to cast which includes its name, health, attack values, and abilities
Also includes card specific values like fire tokens
*/
class Spell
{
private:
    string spellName;
    int spellHealth;
    int spellAttack;
    int spellManaCost;
    int spellAbility;
    int fireTokens = 0;
    
public:
    Spell();
    Spell(string name, int health, int attack, int manaCost, int ability);
    string getSpellName();
    //getters
    int getSpellHealth();
    int getSpellAttack();
    int getSpellManaCost();
    int getSpellAbility();
    //setters
    void setSpellName(string name);
    void setSpellHealth(int health);
    void setSpellAttack(int attack);
    void setSpellManaCost(int mana);
    void setSpellAbility(int ability);
    void displaySpell();
};

#endif
