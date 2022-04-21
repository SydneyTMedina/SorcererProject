#include <iostream>
#include <vector>
#include "BattleField.h"
#include "Spell.h"
#include "Player.h"
#include "Game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

BattleField::BattleField(int _health) {
    playerBattleFieldHealth = _health;
    enemyBattleFieldHealth = _health;
    maxBattleFieldHealth = _health;
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
void BattleField::setPlayerBattleFieldHealth(int _health) {
    playerBattleFieldHealth = _health;
    if(playerBattleFieldHealth <= 0) {
        //Player loses
        setBattleFieldCondition(-1);
        Game game = Game();
        game.loseGame(2);
    }
}

void BattleField::setEnemyBattleFieldHealth(int _health) {
    enemyBattleFieldHealth = _health;
    if(enemyBattleFieldHealth <= 0) {
        //Player win battle field
        setBattleFieldCondition(1);
    }
}

//Gets the battle field health
int BattleField::getPlayerBattleFieldHealth() {
    return playerBattleFieldHealth;
}

int BattleField::getEnemyBattleFieldHealth() {
    return enemyBattleFieldHealth;
}

int BattleField::getPlayerDamageMultiplier() {
    return playerDamageMultiplier;
}

void BattleField::setPlayerDamageMultiplier(int _multiplier) {
    playerDamageMultiplier = _multiplier;
}

int BattleField::getBattleFieldCondition() {
    return battleFieldCondition;
}

void BattleField::setBattleFieldCondition(int _condition) {
    battleFieldCondition = _condition;
}

int BattleField::getEnemyDamageMultiplier() {
    return enemyDamageMultiplier;
}

void BattleField::setEnemyDamageMultiplier(int _multiplier) {
    enemyDamageMultiplier = _multiplier;
}

void BattleField::resetBattleField() {
    playerBattleFieldHealth = maxBattleFieldHealth;
    enemyBattleFieldHealth = maxBattleFieldHealth;
    playerMinions.clear();
    enemyMinions.clear();
}

//Plays a card from the hand onto the battlefield
bool BattleField::playCard(int handIndex, Player &player) {
    if(handIndex < 0 || handIndex >= player.getHandSize()) {
        return false;
    }
    if(player.isNpc() == false) {
        Spell spell = player.getSpellInHand(handIndex);
        int cost = spell.getSpellManaCost();
        if(cost > player.getMana()) cout << "You don't have enough mana to play this card!" << endl;
        else {
            player.setMana(player.getMana() - cost);
            if(spell.getSpellHealth() == 0) {
                //Activate spell ablility
            }
            else {
                addPlayerMinions(player.getSpellIDHandPos(handIndex));
                //Activate spell ability
            }
            player.removeSpellFromHand(handIndex);
            return true;
        }   
    }
    else {
        Spell spell = player.getSpellInHand(handIndex);
        int cost = spell.getSpellManaCost();
        player.setMana(player.getMana() - cost);
        addEnemyMinions(player.getSpellIDHandPos(handIndex));
        player.removeSpellFromHand(handIndex);
        return true;
    }
    return false;
}

int BattleField::playerDealDamage(Player &player, Player &npc, Spell &spell) {
    int damageTotal = spell.getSpellAttack();
    spell.setIsTapped(true);
    int numKills = 0;
    damageTotal = damageTotal * playerDamageMultiplier;
    int maxDamage = damageTotal;

    if(enemyMinions.size() == 0) {
        cout << spell.getSpellName() << " delt " << damageTotal << " damage to the battle field" << endl;
        setEnemyBattleFieldHealth(getEnemyBattleFieldHealth() - damageTotal);
    }
    else {
        vector<int> minionsKilled;
        //Check for kill
        for(int i = 0; i < enemyMinions.size(); i++) {
            if(npc.getLibrary().getSpellAt(enemyMinions.at(i)).getSpellHealth() <= damageTotal) {
                minionsKilled.push_back(i);
                damageTotal = damageTotal - npc.getLibrary().getSpellAt(enemyMinions.at(i)).getSpellHealth();
            }
        }
        //If killed
        for(int i = 0; i < minionsKilled.size(); i++) {
            npc.putSpellInGraveyard(enemyMinions.at(0));
            removeEnemyMinion(enemyMinions.at(0));
            numKills++;
        }
        if(enemyMinions.size() == 0 && damageTotal > 0) {
            setEnemyBattleFieldHealth(getEnemyBattleFieldHealth() - damageTotal);
            cout << "You delt " << maxDamage << " damage to enemy minions and the battlefield and killed " << numKills << " of them!" << endl;
            return numKills;
        }
        if(numKills == 0) {
            cout << endl << "You delt " << maxDamage << " damage to the front line and killed none of them!" << endl;
            
        }
        else {
            cout << endl << "You delt " << maxDamage << " damage and killed " << numKills << " minions!" << endl;
        }
    
    }
    return numKills;
}

int BattleField::enemyDealDamage(Player &player, Player &npc, Spell &spell) {
    int damageTotal = spell.getSpellAttack();
    spell.setIsTapped(true);
    int numKills = 0;
    damageTotal = damageTotal * enemyDamageMultiplier;
    int maxDamage = damageTotal;

    if(playerMinions.size() == 0) {
        cout << spell.getSpellName() << " delt " << damageTotal << " damage to your battle field!" << endl;
        setPlayerBattleFieldHealth(getPlayerBattleFieldHealth() - damageTotal);
    }
    else {
        vector<int> minionsKilled;
        //Check for kill
        for(int i = 0; i < playerMinions.size(); i++) {
            if(player.getLibrary().getSpellAt(playerMinions.at(i)).getSpellHealth() <= damageTotal) {
                minionsKilled.push_back(i);
                damageTotal = damageTotal - player.getLibrary().getSpellAt(playerMinions.at(i)).getSpellHealth();
            }
        }
        //If killed
        for(int i = 0; i < minionsKilled.size(); i++) {
            player.putSpellInGraveyard(playerMinions.at(0));
            removePlayerMinion(playerMinions.at(0));
            numKills++;
        }
        if(playerMinions.size() == 0 && damageTotal > 0) {
            setPlayerBattleFieldHealth(getPlayerBattleFieldHealth() - damageTotal);
            cout << npc.getName() << " delt " << maxDamage << " damage to your minions and the battlefield and killed " << numKills << " of them!" << endl;
            return numKills;
        }
        if(numKills == 0) {
            cout << npc.getName() << " delt " << maxDamage << " damage to the front line and killed none of your minions!" << endl;
            
        }
        else {
            cout <<  npc.getName() << " delt " << maxDamage << " damage and killed " << numKills << " of your minions!" << endl;
        }
    }
    return numKills;
}