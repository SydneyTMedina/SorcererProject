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
    int spellAbility;
    int fireTokens = 0;
    
public:
    Spell();
    Spell(string name, int health, int attack, int ability);
    string getSpellName();
    int getSpellHealth();
    int getSpellAttack();
    int getSpellAbility();
    void setSpellName(string name);
    void setSpellHealth(int health);
    void setSpellAttack(int attack);
    void setSpellAbility(int ability);

};

#endif
