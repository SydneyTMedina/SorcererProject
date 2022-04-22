/*
CSCI1300 - Project 3
Luca Voeller
Sydney Medina
*/

#ifndef MAP_H
#define MAP_H

#include <iostream>
using namespace std; 

/*
Class definition for Map
Has an int to hold a randomly generated map
3 constants for the # or rows, columns, and sites
has a 1d array for the player position
has a 2d array for a copy of the map that can be modified
has a count for the number of sites won

respective getters/setters
also includes a funtion to display the map, execute a player's desired move (if valid), and a funtion to fill mapData up
*/

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
          void setSitesClaimed(int sites);

          // other
          void displayMap();
          bool executeMove(char move);
          void fillMap();

};
 
#endif