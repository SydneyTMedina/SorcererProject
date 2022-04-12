#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Spell.h"
using namespace std;

//Default constructor for a spell
Spell::Spell() {
    spellName = "";
    spellHealth = 0;
    spellAttack = 0;
    spellManaCost = 0;
    spellAbility = 0;
}

//Perameterized constructor for spell. 
Spell::Spell(string name, int health, int attack, int manaCost, int ability) {
    spellName = name;
    spellHealth = health;
    spellManaCost = manaCost;
    spellAttack = attack;
    spellAbility = ability;
}

//Gets the spell name
string Spell::getSpellName() {
    return spellName;
}

//Gets the spell health
int Spell::getSpellHealth() {
    return spellHealth;
}

//Gets spell mana cost
int Spell::getSpellManaCost() {
    return spellManaCost;
}

//Gets the spell attack
int Spell::getSpellAttack() {
    return spellAttack;
}

//Gets the spell ability
int Spell::getSpellAbility() {
    return spellAbility;
}

//Sets the spell name
void Spell::setSpellName(string _name) {
    spellName = _name;
}

//Sets the spell health
void Spell::setSpellHealth(int _health) {
    spellHealth = _health;
}

//Sets the spell attack
void Spell::setSpellAttack(int _attack) {
    spellAttack = _attack;
}

void Spell::setSpellManaCost(int _manaCost) {
    spellManaCost = _manaCost;
}

//Sets the spell ability
void Spell::setSpellAbility(int _ability) {
    spellAbility = _ability;
}