/*
CSCI1300 - Project 3
Luca Voeller
Sydney Medina
*/

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include "Map.h"
#include <time.h>
#include "Game.h"

using namespace std;


//Defaut constructor for the map class
Map::Map()
{
    srand(time(NULL));
    mapVersion=((int)rand()%3)+1;//random num 1-3
    playerPosition[0] = 0; 
    playerPosition[1] = 0;
}

//takes the int generated and fills in the data using a corresponding text file
void Map::fillMap() {
    string mapName="";
    if(mapVersion==1)
    mapName="mapOne.txt";
    else if(mapVersion==2)
    mapName="mapTwo.txt";
    else
    mapName="mapThree.txt";

    ifstream fin;
    fin.open(mapName);
    string line=""; 
    int lineCount=0;
    while(getline(fin,line)){//filling in the data
        for(int j = 0; j < num_cols; j++){
            mapData[lineCount][j]=line.at(j);
        }
        lineCount++;
    }
}

// return player's row position
int Map::getPlayerRowPosition() {
    return playerPosition[0];
}

// return player's column position
int Map::getPlayerColPosition() {
    return playerPosition[1];
}

int Map::getSitesClaimed() {
    return sitesClaimed;
}

/*
 * Algorithm: Checks if the location is site  
 * if the spot has an 'X' return true
 * else
 * return false
 * Parameters: row, col
 * Return: boolean (bool)
 */
bool Map::isSiteLocation(int row, int col){
         if(mapData[row][col]=='X')
            return true;
    return false;
}

/*
 * Algorithm: Checks if the given row and column on map is a free space 
 * if row and column is not within the map boundaries
 *      return false
 * if its a '-' or 'X' you can move there
 * Parameters: row (int), col (int)
 * Return: boolean (bool)
 */
bool Map::isMovableSpace(int row, int col){
    if(row < 0 || row > 8 || col < 0 || col > 11){
        return false;
    }
    if (mapData[row][col]=='-'||mapData[row][col]=='X') {
        return true;
    }
    
    return false;
}

//sets player row
void Map::setPlayerRowPosition(int row) {
    playerPosition[0] = row;
}

//sets player column
void Map::setPlayerColPosition(int col) {
    playerPosition[1] = col;
}

/*
 * Algorithm: Make the player move based on the given command 
 * if user inputs s and if its not the bottom row of the map
 *      Move the player down by one row
 *      return true
 * if user inputs a and if its not the leftmost column
 *      Move the player left by one column
 *      return true
 * if user inputs d and if its not the rightmost column
 *      Move the player right by one column
 *      return true
 * 
 * NO MOVING UP SO NO W
 * 
 * Parameters: move (char)
 * Return: boolean (bool)
 */
bool Map::executeMove(char move){ 
    // if user inputs s, move down if it is an allowed move
    if(!(playerPosition[0] == (num_rows - 1))&& (tolower(move) == 's') && isMovableSpace(playerPosition[0]+1, playerPosition[1])==true){
        playerPosition[0] += 1;
        return true; 
    }
    // if user inputs a, move left if it is an allowed move
    else if(!(playerPosition[1] == 0)&& (tolower(move) == 'a') && isMovableSpace(playerPosition[0], playerPosition[1]-1)==true){
        playerPosition[1] -= 1;
        return true; 
    }
    // if user inputs d, move right if it is an allowed move
    else if(!(playerPosition[1] == (num_cols - 1))&& (tolower(move) == 'd') && isMovableSpace(playerPosition[0], playerPosition[1]+1)==true){
        playerPosition[1] += 1;
        return true; 
    }
    else{
        cout << "Invalid Move" << endl; 
        return false; 
    }
}

/*
 * Algorithm: This function prints a 2D map in the terminal.
 * Loop i from 0 to number of rows
 *      Loop j from 0 to number of columns
 *          if player position is at (i,j)
 *              print "P"
 *          else
 *              print the value of (i,j) in mapData
 * Parameters: none
 * Return: nothing (void)
 */
void Map::displayMap() {
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            if (playerPosition[0] == i && playerPosition[1] == j) 
                cout << "P";
            else {
                cout << mapData[i][j];
            }
        }
        cout << endl;
    }
}

//Sets to see if all the sites have been claimed, if they have, the player wins
void Map::setSitesClaimed(int sites) {
    sitesClaimed = sites;
    if(sitesClaimed >= 3) {
        Game game = Game();
        game.winGame();
    }
}
