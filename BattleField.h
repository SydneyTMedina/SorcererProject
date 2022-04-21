#include <iostream>
#include <vector>
#include "Player.h"
using namespace std;

#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H


#include "Spell.h"

/*
Class definition for BattleField
This vector has arrays for playerMinions on that battle field and enemyMinions
Includes Battle field health which determines whether or not the player has captured that battle field
*/
class BattleField
{
private:
    int playerBattleFieldHealth;
    int enemyBattleFieldHealth;
    int maxBattleFieldHealth;
    int playerDamageMultiplier = 1;
    int enemyDamageMultiplier = 1;
    int battleFieldCondition = 0;
    vector<int> playerMinions;
    vector<int> enemyMinions;
    int playerUnTappedMinions;
    int enemyUnTappedMinions;
    int damageDifferenceNPC;
    int damageDifferencePlayer;

public:
   BattleField(int health);
   void addPlayerMinions(int spell);
   void addEnemyMinions(int spell);
   bool removePlayerMinion(int spell);
   bool removeEnemyMinion(int spell);
   vector<int> getPlayerMinions();
   vector<int> getEnemyMinions();

   void setPlayerBattleFieldHealth(int health);
   void setEnemyBattleFieldHealth(int health);
   void setdamageDifferenceNPC(int damage);
   void setdamageDifferencePlayer(int damage);

   int getPlayerBattleFieldHealth();
   int getEnemyBattleFieldHealth();
   int getDamageDifferenceNPC();
   int getDamageDifferencePlayer();


   void resetBattleField();

   int getPlayerDamageMultiplier();
   void setPlayerDamageMultiplier(int multipier);
   int getEnemyDamageMultiplier();
   void setEnemyDamageMultiplier(int multipier);
   int getBattleFieldCondition();
   void setBattleFieldCondition(int condition);
   bool playCard(int handIndex, Player &player);
   int playerDealDamage(Player &player, Player &npc, Spell &spell);
   int enemyDealDamage(Player &player, Player &npc, Spell &spell);
   void abilityExecute(int ability, bool isPlayer)
   

};

#endif
