#ifndef MAP_H
#define MAP_H

#include <iostream>

using namespace std; 

class Map
{
     private:
          static const int num_rows = 12;
          static const int num_cols = 12;
          static const int num_sites = 7;

          int playerPosition[2];
          int npcPosition[2];
          int sites[num_sites][3];
          char mapData[num_rows][num_cols];

          bool npc_on_map;
          int site_count;

     public :
          Map();

          void resetMap();

          // getters
          int getPlayerRowPosition();
          int getPlayerColPosition();
          int getSiteCount();
          int getSiteTrait();
          bool isNPCLocation();
          bool isSiteLocation();
          bool isFreeSpace(int, int);

          // setters
          void setNPC(bool);
          void setPlayerRowPosition(int);
          void setPlayerColPosition(int);

          // other
          void displayMap();
          bool executeMove(char);
          bool spawnNPC(int, int);
          bool spawnSite(int, int, int);

};
 
#endif