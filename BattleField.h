#include <iostream>
#include <vector>
using namespace std;

#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

/*
Class definition for BattleField
This vector has arrays for playerMinions on that battle field and enemyMinions
Includes Battle field health which determines whether or not the player has captured that battle field
*/
class BattleField
{
private:
    int battleFieldHealth;
    vector<int> playerMinions;
    vector<int> enemyMinions;

public:
   BattleField(int health);
   void addPlayerMinions(int spell);
   void addEnemyMinions(int spell);
   bool removePlayerMinion(int spell);
   bool removeEnemyMinion(int spell);
   vector<int> getPlayerMinions();
   vector<int> getEnemyMinions();
   void setBattleFieldHealth(int health);
   int getBattleFieldHealth();

};

#endif
