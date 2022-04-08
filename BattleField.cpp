#include <iostream>
#include <vector>
#include "BattleField.h"
#include "Spell.h"

using namespace std;

BattleField::BattleField(int _health) {
    battleFieldHealth = _health;
}

//Adds a player minion to the battlefield
void BattleField::addPlayerMinions(int _spell) {
    playerMinions.push_back(_spell);
}

//Adds enemy minion to the battlefield
void BattleField::addEnemyMinions(int _spell) {
    enemyMinions.push_back(_spell);
}

/*
Searches through entire list of player minions and finds a minion with a matching id and removes them
*/
bool BattleField::removePlayerMinion(int _spell) {
    for(int i = 0; i < playerMinions.size(); i++) {
        if(_spell == playerMinions.at(i)) {
            playerMinions.erase(playerMinions.begin() + i);
            return true;
        }
    } 
    return false;
}

/*
Searches through entire list of enemy minions and finds a minion with a matching id and removes them
*/
bool BattleField::removeEnemyMinion (int _spell) {
    for(int i = 0; i < enemyMinions.size(); i++) {
        if(_spell == enemyMinions.at(i)) {
            enemyMinions.erase(enemyMinions.begin() + i);
            return true;
        }
    }
    return false; 
}

//Gets a copy of player minions vector
vector<int> BattleField::getPlayerMinions() {
    vector<int> toReturn;
    for(int spell : playerMinions) {
        toReturn.push_back(spell);
    }
    return toReturn;
}

//Gets a copy of enemy minions vector
vector<int> BattleField::getEnemyMinions() {
    vector<int> toReturn;
    for(int spell : enemyMinions) {
        toReturn.push_back(spell);
    }
    return toReturn;
}

//Sets the battle field health
void BattleField::setBattleFieldHealth(int _health) {
    battleFieldHealth = _health;
}

//Gets the battle field health
int BattleField::getBattleFieldHealth() {
    return battleFieldHealth;
}