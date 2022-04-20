#ifndef MAP_H
#define MAP_H

#include <iostream>

using namespace std; 

class Map
{
     private:
          int mapVersion=0;
          static const int num_rows = 9;
          static const int num_cols = 12;
          static const int num_sites = 3;

          int playerPosition[2];
          char mapData[num_rows][num_cols];

          int sitesClaimed=0;

     public :
          Map();

          // getters
          int getPlayerRowPosition();
          int getPlayerColPosition();
          int getSitesClaimed();
          bool isSiteLocation(int row, int col);
          bool isMovableSpace(int row, int col);

          // setters
          void setPlayerRowPosition(int row);
          void setPlayerColPosition(int col);

          // other
          void displayMap();
          bool executeMove(char move);
          void fillMap();

};
 
#endif