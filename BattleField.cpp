/*
CSCI1300 - Project 3
Luca Voeller
Sydney Medina
*/

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

//constructor that uses health to set both sides's health and the max health. Also sets damage adder to 0
BattleField::BattleField(int _health) {
    playerBattleFieldHealth = _health;
    enemyBattleFieldHealth = _health;
    maxBattleFieldHealth = _health;
    damageDifferenceNPC=0;
    damageDifferencePlayer=0;
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
Searches through entire list of player minions and finds a minion with a matching ID and removes them
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
Searches through entire list of enemy minions and finds a minion with a matching ID and removes them
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

//Sets the battle field health. If 0 NPC wins
void BattleField::setPlayerBattleFieldHealth(int _health) {
    playerBattleFieldHealth = _health;
    if(playerBattleFieldHealth <= 0) {
        //Player loses
        setBattleFieldCondition(-1);
        Game game = Game();
        game.loseGame(2);
    }
}

//Sets the battle field health. If 0 player wins
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

//Gets the battle field health
int BattleField::getEnemyBattleFieldHealth() {
    return enemyBattleFieldHealth;
}

//Gets the DamageMultiplier
double BattleField::getPlayerDamageMultiplier() {
    return playerDamageMultiplier;
}

//Gets the win or lose status of battlefield
int BattleField::getBattleFieldCondition() {
    return battleFieldCondition;
}

//Gets damage modifier for NPC
int BattleField::getDamageDifferenceNPC(){
    return damageDifferenceNPC;
}

//Gets damage modifier for Player
int BattleField::getDamageDifferencePlayer(){
    return damageDifferencePlayer;
}

//Gets damage multiplier for NPC
double BattleField::getEnemyDamageMultiplier() {
    return enemyDamageMultiplier;
}

//Sets damage multiplier for Player
void BattleField::setPlayerDamageMultiplier(double _multiplier) {
    playerDamageMultiplier = _multiplier;
}

//Sets battlefield condition
void BattleField::setBattleFieldCondition(int _condition) {
    battleFieldCondition = _condition;
}

//Sets damage modifier for NPC
void BattleField::setdamageDifferenceNPC(int damage){
    damageDifferenceNPC=damage;
}

//Sets damage modifier for Player
void BattleField::setdamageDifferencePlayer(int damage){
    damageDifferencePlayer=damage;
}

//Sets damage multiplier for NPC
void BattleField::setEnemyDamageMultiplier(double _multiplier) {
    enemyDamageMultiplier = _multiplier;
}

//reset the battlefield
void BattleField::resetBattleField() {
    playerBattleFieldHealth = maxBattleFieldHealth;
    enemyBattleFieldHealth = maxBattleFieldHealth;
    enemyDamageMultiplier = 1;
    playerDamageMultiplier = 1;
    playerMinions.clear();
    enemyMinions.clear();
}

/*
Executes the ability based on the assigned int
Includes attack bonuses, debuffs, extra cards, more mana...
*/
void BattleField::abilityExecute(int ability, bool isPlayer, Player &player){
    if(ability==1){//Add 1 attack
       if(isPlayer==true)
           damageDifferencePlayer= 1 + damageDifferencePlayer;
       else
           damageDifferenceNPC= 1 + damageDifferenceNPC;

    }
    else if(ability==2){//Add 2 attack
       if(isPlayer==true)
           damageDifferencePlayer= 2 + damageDifferencePlayer;
       else
           damageDifferenceNPC= 2 + damageDifferenceNPC;

    }
    else if(ability==3){//Subtract 1 attack from the enemy
       if(isPlayer==true)
           damageDifferenceNPC= damageDifferenceNPC - 1;
       else
          damageDifferencePlayer= damageDifferencePlayer - 1;

    }
    else if(ability==4){//Subtract 2 attack from the enemy
       if(isPlayer==true)
           damageDifferenceNPC= damageDifferenceNPC - 2;
       else
          damageDifferencePlayer= damageDifferencePlayer - 2;

    }
    else if(ability==5 || ability==11){//Remove enemy attack 
       if(isPlayer==true)
           enemyDamageMultiplier= 0;
       else
          playerDamageMultiplier = 0;

    }
    else if(ability==6){//Draw 3 Cards
           player.drawSpells();
           player.drawSpells();
           player.drawSpells();

    }
    else if(ability==9){//Add 2 mana
           player.gainTwoMana();
    }
    else if(ability==10){//Add 4 mana
           player.gainTwoMana();
           player.gainTwoMana();

    }
    else if(ability==12){//Gain 3 health for the battlefield
       if(isPlayer==true)
           playerBattleFieldHealth= playerBattleFieldHealth + 3;
       else
           enemyBattleFieldHealth= enemyBattleFieldHealth + 3;

    }
    else if(ability==13){//Gain 5 health for the battlefield
       if(isPlayer==true)
           playerBattleFieldHealth= playerBattleFieldHealth + 5;
       else
           enemyBattleFieldHealth= enemyBattleFieldHealth + 5;
    }
    else if(ability==14){//Add 4 attack
       if(isPlayer==true)
           damageDifferencePlayer= 4 + damageDifferencePlayer;
       else
           damageDifferenceNPC= 4 + damageDifferenceNPC;

    }
    else if(ability==15){//Damage Doubled
       if(isPlayer==true)
           playerDamageMultiplier=playerDamageMultiplier*2;
      else
           enemyDamageMultiplier=enemyDamageMultiplier*2;
    }
    else if(ability==16){//Damage Halfed
      if(isPlayer==true)
           enemyDamageMultiplier=enemyDamageMultiplier/2;
      else
           playerDamageMultiplier=playerDamageMultiplier/2;
    }
    else if(ability==17){//Clear Battlefield. Cards will not go to graveyard If no cards, do they get more actions?
        playerMinions.clear();
        enemyMinions.clear();
    }
}


//Plays a card from the hand onto the battlefield
/*
make sure that the choise is a valid spell choice
make sure that there is enough mana to play the spell
Not enough? return false
There's enough? Subtract the used mana from the mana pool
if its a spell only, just call the ability
if its a creature, call the ability AND add it to the battlefield
remove the cast spell
return true

Make 2 verions. 1 for Player 1 for NPC
*/
bool BattleField::playCard(int handIndex, Player &player) {
    if(handIndex < 0 || handIndex >= player.getHandSize()) {
        return false;
    }
    if(player.isNpc() == false) {//PLAYER
        Spell spell = player.getSpellInHand(handIndex);
        int cost = spell.getSpellManaCost();
        if(cost > player.getMana()) cout << "You don't have enough mana to play this card!" << endl;
        else {
            player.setMana(player.getMana() - cost);
            if(spell.getSpellAttack() <= 0 || spell.getSpellHealth() <= 0) {
                abilityExecute(spell.getSpellAbility(),player.isNpc(), player);
                cout << endl << "You cast " << spell.getSpellName() << endl;
            }
            else {
                cout << endl << "You summoned " << spell.getSpellName() << endl;
                abilityExecute(spell.getSpellAbility(),player.isNpc(), player);
                addPlayerMinions(player.getSpellIDHandPos(handIndex));
            }
            player.removeSpellFromHand(handIndex);
            return true;
        }   
    }
    else {//NPC
        Spell spell = player.getSpellInHand(handIndex);
        int cost = spell.getSpellManaCost();
        player.setMana(player.getMana() - cost);
        if(spell.getSpellAttack() <= 0 || spell.getSpellHealth() <= 0) {
            player.removeSpellFromHand(handIndex);
        }
        else {
            addEnemyMinions(player.getSpellIDHandPos(handIndex));
            player.removeSpellFromHand(handIndex);
        }        
        return true;
    }
    return false;
}

/*
Gather initial damage to be dealt
To keep track of kills, we are going to make a counter for that. set to 0
To calculate the actual amount of damage we are going to take the initial damage amount, add the damageDifference...
... and multiply all of that by the damageMultiplier

If there are no enemies, deal damage to the battlefield
If there are enemies:
we need to keep track of the enemies killed so lets make a vector for that
this vector will be used to keep track of what needs to be removed from the battlefield
if an enemy is killed it is removed from the battlefield and killCount is updated 
At the end, read out the damage dealt and # of enemies killed (if any were)

**reset damage multiplyer and difference at the end of the initial attack
*/
int BattleField::playerDealDamage(Player &player, Player &npc, Spell &spell) {
    int damageTotal = spell.getSpellAttack();
    int numKills = 0;
    damageTotal = (damageTotal+damageDifferencePlayer) * playerDamageMultiplier;
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
    playerDamageMultiplier = 1;
    damageDifferencePlayer = 0;
    return numKills;
}


/*
Gather initial damage to be dealt
To keep track of kills, we are going to make a counter for that. set to 0
To calculate the actual amount of damage we are going to take the initial damage amount, add the damageDifference...
... and multiply all of that by the damageMultiplier

If there are no enemies, deal damage to the battlefield
If there are enemies:
we need to keep track of the enemies killed so lets make a vector for that
this vector will be used to keep track of what needs to be removed from the battlefield
if an enemy is killed it is removed from the battlefield and killCount is updated 
At the end, read out the damage dealt and # of enemies killed (if any were)

**reset damage multiplyer and difference at the end of the initial attack
*/
int BattleField::enemyDealDamage(Player &player, Player &npc, Spell &spell) {
    int damageTotal = spell.getSpellAttack();
    int numKills = 0;
    damageTotal = (damageTotal+damageDifferenceNPC) * enemyDamageMultiplier;
    int maxDamage = damageTotal;
    damageDifferenceNPC = 0;

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
    enemyDamageMultiplier = 1;
    damageDifferenceNPC = 0;
    return numKills;
}