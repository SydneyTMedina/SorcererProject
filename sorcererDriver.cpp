/*
CSCI1300 - Project 3
Luca Voeller
Sydney Medina
*/

#include "Library.h"
#include "Player.h"
#include "DisplayASCII.h"
#include "Game.h"
#include "Map.h"
#include "Spell.h"
#include "BattleField.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

/*
Takes a filename and the data to be added to the file
Opens the file stream and checks if it is open
If it is open, write the data to the file
Close the file
*/
void writeOutFile(string filename, string data) {
    ofstream file;
    file.open(filename);
    if(file.is_open()) {
        file << data;
        file.close();
    }
}

/*
Takes a filename and location
Opens the file stream and checks if it is open
If it is open, loop through all the data and write it to a vector
Return the data in the vector in the input location
*/
string readLineFile(string filename, int location) {
    string line = "";
    ifstream file;
    vector<string> fileOut;
    file.open(filename);
    if(file.is_open()) {
        while(getline(file, line)) {
            fileOut.push_back(line);
        }         
    }
    return fileOut.at(location);
}

//stores number of kills by adding to the file
void addKillsToFile(int kills) {
    int numKillsInFile = stoi(readLineFile("statsFiles/kills.txt", 0));
    numKillsInFile += kills;
    //File write
    writeOutFile("statsFiles/kills.txt", to_string(numKillsInFile));
}

/*
TO DO:
Add the rest of the menu options for the main menu like how to play - DONE
Add the story elements in the main function for when you reached a battlefield - DONE
Fix looping input bug - DONE
Finish abilities - DONE
Add sorting algorithm - DONE
Make sure code meets requirements
Add file output with the stats
SUBMIT
*/

//A little delay for pacing and readability
void waitForPlayer() {
    cout << endl << "Press any key + enter..." << endl;
    string ranIN = "";
    cin >> ranIN;
}

/*
for inputs 1-6 an if statement will correspond. Everything else is invalid
1-Start Game
2-How to play
3-Background story
4-Past game data
5-Prints Credit
6-Quit
*/
bool menu(DisplayASCII displayASCII) {
    while(true) {
        string selection = "";
        displayASCII.display("selectScreen.txt");
        cin >> selection;
        if(selection == "1") return true;
        else if(selection == "2") {//HOW TO PLAY   SECONDARY MENU
            bool status=true;
            string selection="";
            

          while(status==true){
            ifstream fin;
            fin.open("images/menuOpTwo.txt");
            string line=""; 
            if(!fin.is_open()) cout<<"NOT OPEN"<<endl;

               while(getline(fin,line)){//NESTED WHILE LOOP
                 cout<<line<<endl;
               }
               fin.close();
            cout<<"Please enter your selection: "<<endl;
            cin>>selection;
            if(selection=="1"){//1: How to move
              cout<<"Upon starting the game use (A,S,D) to move towards the next city (X)"<<endl;
              waitForPlayer();
            }
            else if(selection=="2"){//2: Player Action Phase
              cout<<"When you reach the city you will have 10 actions to cast spells, gain mana, or learn new spells."<<endl;
              cout<<"Each spell costs mana to cast, so be mindful! 10 actions goes fast."<<endl;
              cout<<"At the end of the 10 actions the damage phase will start. Select which spell you want to attack first."<<endl;
              cout<<"In order to defeat an enemy minion it's all or nothing! One shot it or it stays standing!"<<endl;
              waitForPlayer();
           }
           else if(selection=="3"){//3: NPC Action Phase
             cout<<"Your NPC opponent will also have 10 actions and their own spells to counter your attacks."<<endl;
             waitForPlayer();
           }
           else if(selection=="4"){//4: Battlefield damage
             cout<<"Once all minions on one side of the battlefield are defeated the battlefield will start to take damage."<<endl;
             cout<<"At the end of the 10 actions the damage phase will start. Select which spell you want to attack first."<<endl;
             cout<<"In order to defeat a player minion it's all or nothing as well!"<<endl;
             waitForPlayer();
           }
           else if(selection=="5"){//5: How to win 
             cout<<"To defeat your opponent, eliminate all enemies and deal damage the battlefield!"<<endl;
             waitForPlayer();
           }
           else if(selection=="6"){//quit
             status=false;
            }    
           else{
             cout<<"Invalid Input"<<endl;
             waitForPlayer();
           }
              }
        }
        else if(selection == "3") {     //BACKGROUND STORY
            cout<<"After being mocked by your fellow sorcerer scholars, you have decided to show them your true power."<<endl;
            cout<<"To prove to them who is the most powerful sorcerer in the land, you have decided to conquer all 3 major cities."<<endl;
            cout<<"By dominating the battlefield and destrying those who stand in your way, you will prove to all that you are the supreme sorcerer."<<endl;
            waitForPlayer();
        }
        else if(selection == "4") {  //Print previous games stats by reading the stats file
            cout << endl <<"---Last game stats---" << endl;
            cout << endl << "Played as: " << readLineFile("statsFiles/charName.txt", 0) << endl;
            cout << "Kills: " << readLineFile("statsFiles/kills.txt", 0) << endl;
            cout << "Sites Captured: " << readLineFile("statsFiles/sites.txt", 0) << endl;
            cout << "Game Outcome: " << readLineFile("statsFiles/gameOutCome.txt", 0) << endl;        
            waitForPlayer();    
        }
        else if(selection == "5") {
            displayASCII.display("credits.txt"); //PRINTS CREDITS
            waitForPlayer();
        }
        else if(selection == "6") return false;//QUIT
        else {
            cout << "Invalid input" << endl;
        }
    }
}

/*
1) Choose character
2) Choose lineage
3) Choose Domain
These choices effect the spells the player will get
*/
Player createPC(Game &game) {
    string input;
    vector<string> displayAtEnd;
    string deck1 = "";
    string deck2 = "";
    string deck3 = "";
    //CHARACTER
    while(true) {
        cout << endl << "Choose your character:" << endl << endl << "1 -> Miselda" << endl << "2 -> Tegu" << endl << "3 -> Zevrane" << endl << "4-> Ariaspes" << endl;
        cin >> input;
        if(input == "1") {
            deck1 = "Miselda.txt";
            displayAtEnd.push_back("Miselda");
            game.removeCharacter(0);
            break;
        }
        else if(input == "2") {
            deck1 = "Tegu.txt";
            displayAtEnd.push_back("Tegu");
            game.removeCharacter(1);
            break;
        }
        else if(input == "3") {
            deck1 = "Zevrane.txt";
            displayAtEnd.push_back("Zevrane");
            game.removeCharacter(2);
            break;
        }
        else if(input == "4") {
            deck1 = "Ariaspes.txt";
            displayAtEnd.push_back("Ariaspes");
            game.removeCharacter(3);
            break;
        }
        else {
            cout << "Invalid Input" << endl;
        }
    }
    //LINEAGE
    while(true) {
        cout << endl << "Choose your lineage:" << endl << endl << "1 -> The Necromancer" << endl << "2 -> The Demonologist" << endl << "3 -> The Bloodlord" << endl << "4-> The Animist" << endl;
        cin >> input;
        if(input == "1") {
            deck2 = "Necromancer.txt";
            displayAtEnd.push_back("The Necromancer");
            break;
        }
        else if(input == "2") {
            deck2 = "Demonologist.txt";
            displayAtEnd.push_back("The Demonologist");
            break;
        }
        else if(input == "3") {
            deck2 = "Bloodlord.txt";
            displayAtEnd.push_back("The Bloodlord");
            break;
        }
        else if(input == "4") {
            deck2 = "Animist.txt";
            displayAtEnd.push_back("The Animist");
            break;
        }
        else {
            cout << "Invalid Input" << endl;
        }
    }
    //DOMAIN
    while(true) {
        cout << endl << "Choose your Domain:" << endl << endl << "1 -> Forgotten Temple" << endl << "2 -> Outcast Sanctuary" << endl << "3 -> Screaming Coast" << endl << "4-> Haunted Forest" << endl;
        cin >> input;
        if(input == "1") {
            deck3 = "Forgotten_Temple.txt";
            displayAtEnd.push_back("Forgotten Temple");
            break;
        }
        else if(input == "2") {
            deck3 = "Outcast_Sanctuary.txt";
            displayAtEnd.push_back("Outcast Sanctuary");
            break;
        }
        else if(input == "3") {
            deck3 = "Screaming_Coast.txt";
            displayAtEnd.push_back("Screaming Coast");
            break;
        }
        else if(input == "4") {
            deck3 = "Haunted_Forest.txt";
            displayAtEnd.push_back("Haunted Forest");
            break;
        }
        else {
            cout << "Invalid Input" << endl;
        }
    }
    cout << endl << "Your character is: " << displayAtEnd.at(0) << " " << displayAtEnd.at(1) << " Of the " << displayAtEnd.at(2) << endl; 
    writeOutFile("statsFiles/charName.txt", displayAtEnd.at(0) + " " + displayAtEnd.at(1) + " Of the " + displayAtEnd.at(2));
    Library library = Library(deck1, deck2, deck3);//Make the player deck of spells
    Player player = Player(library, false, "", game);
    return player;
}

/*
Player always goes first, then NPC
If no minions are on either side, action phase starts again.
if no minions on enemy side, X2 damage
-Choose which spell to attack with
-Damage is dealt, enemies die
switch turn
reset option available
*/
int battlePhase(Player player, Player npc, BattleField battleField, DisplayASCII display) {
   
    int input = 0;
    cout << "You go first!" << endl;

    while(true) {
        if(battleField.getEnemyMinions().size() == 0 && battleField.getPlayerMinions().size() == 0) { //checks for no minions on either side
            cout << "No player has any minions on the battle field! Returing to prep-phase" << endl;
            player.resetPlayer();
            npc.resetPlayer();
            battleField.resetBattleField();
            return 1;
        }

        display.displayEnemyBattleField(battleField, npc);
        waitForPlayer();
        display.displayBattleField(battleField, player);
        if(battleField.getPlayerMinions().size() == 0) {//if no minions on enemy side, X2 damage
            cout << "You have no enemy minions on the battlefield! You will take DOUBLE (2x) damage this turn" << endl;
            battleField.setEnemyDamageMultiplier(2);
        }
        else { //choose which spell to attack with
            cout << endl << "Which creature do you want to attack with? (Or type -1 to draw and restart)" << endl;
            input = 0;
            cin >> input;
            if(cin.fail()) {
                cout << "Invalid input!" << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            if(input  == -1) {//reset
                player.resetPlayer();
                npc.resetPlayer();
                battleField.resetBattleField();
                return 1;
            }
            else if(input <= battleField.getPlayerMinions().size() && input >= 1) {//do damage with selection
                Spell spell = player.getLibrary().getSpellAt(battleField.getPlayerMinions().at(input-1));
                int kills = battleField.playerDealDamage(player, npc, spell);
                addKillsToFile(kills);
                waitForPlayer();

                if(battleField.getBattleFieldCondition() == 1) {
                    break;
                }
            }
            else {
                cout << "Invalid input!" << endl;
                continue;
            
            }
        }
        battleField.setPlayerDamageMultiplier(1);
        //NPC turn
        if(battleField.getEnemyMinions().size() == 0) {
                cout << npc.getName() << " has no enemy minions on the battlefield! They will take DOUBLE (2x) damage this turn" << endl;
                battleField.setPlayerDamageMultiplier(2);
        }
        else {
            Spell spell = npc.getLibrary().getSpellAt(battleField.getEnemyMinions().at(0));
            battleField.enemyDealDamage(player, npc, spell);
            waitForPlayer();
        }            
        battleField.setEnemyDamageMultiplier(1);
        
    }

    //Successfully captured the battlefield
    player.resetPlayer();
    cout << "Successfully captured the battlefield" << endl;

    return 0;
}

/*
10 actions, 4 choices
1-Cast spell
2-Get more spells
3-Get more mana
4-See current spells

Player goes first, then NPC
If a player or NPC runs out of cards, GAME ENDS
1-Spell checks that there is sufficient mana and if allowed will cast the spell
2-Will give the player/NPC 2 more spells in their hand
3-Will give player/NPC 2 more mana
4-Will display the players spells in ASCII card format

NPC
NPC is going to choose a random spell in their hand. If they dont have enough mana to play it, NPC will gain 2 mana
If they do have enough to play it, they will play it
If they have no cards in their hand they will get 2 spells
*/
int actionPhase(Player player, Player npc, BattleField battleField, DisplayASCII display) {
    int actions = 0;
    player.setActions(10);
    while(actions != 10) {//10 actions
        int input = 0;//choice time
        cout << endl << "What do you want to do?" << endl << endl << "1 -> Cast a spell" << endl << "2 -> Memorize spells" << 
        endl << "3 -> Gain energy" << endl << "4 -> See spells" << endl;
        player.displayGameInfo();
        cin >> input;
        if(cin.fail()) {
            cout << "Invalid input!" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if(input == 1) {//Cast spell
            if(display.displayHand(player) == false) continue;
            cout << endl <<"Choose what spell to cast:" << endl;
            cin >> input;
            if(cin.fail()) {
                cout << "Invalid input!" << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            if(battleField.playCard(input - 1, player) == false) {
                cout << "Invalid Input" << endl;
                continue;
            } 
        }
        else if(input == 2) {//Get 2 spells
            cout << "You memorized two spells!" << endl;
            player.drawSpells();
            player.drawSpells();
        }
        else if(input == 3) {//Get 2 mana
            cout << "You gained two mana" << endl;
            player.gainTwoMana();
        }
        else if(input == 4) {//show spells in ASCII Format
            display.displayHand(player); 
            continue;
        }
        else {
            cout << "Not a valid input" << endl;
            continue;
        }

        //NPC turn
        srand(time(0));
        int ranNum = 0;
        if(npc.getHandSize() != 0) {//generates a random spell choice
            ranNum = int(rand() % npc.getHandSize());
        }
        if(npc.getHandSize() == 0) {//checks that there are still spells to be played
            for(int i = 0; i < 2; i++) {
                if(npc.drawSpells() == 0) {
                    cout << "The enemy sorcer " << npc.getName() << " has run out of spells to cast! You won this battle field!" << endl;
                    return 1;
                }
            }
            cout << endl << npc.getName() << " memorized two spells!" << endl;
        }
        else if(npc.getMana() < npc.getSpellInHand(ranNum).getSpellManaCost()) {//not enough mana to play the card they want to play? get 2 mana
            npc.gainTwoMana();
            cout << endl << npc.getName() << " gained two mana!" << endl << endl;
        } 
        else if(npc.getMana() >= npc.getSpellInHand(ranNum).getSpellManaCost()) {//play spell if possible
            display.displayCard(npc.getSpellInHand(ranNum), true);
            cout << endl << npc.getName() << " cast " << npc.getSpellInHand(ranNum).getSpellName() << " on to the battle field!" << endl;
            battleField.playCard(ranNum, npc);
        }
        actions++;
        player.setActions(player.getActions() - 1);
    }
    cout << endl << "The action phase is over! Continuing to the battle phase..." << endl;
    waitForPlayer();
    if(battlePhase(player, npc, battleField, display) == 0) return 0;
    else(actionPhase(player, npc, battleField, display));
    return 1;    
}


//uses map class functions with player input to move the player around the map
Map moveAroundMap(Map map) {
    do {
        char movement;
        map.displayMap();
        cout << endl << "Use (A,S,D) to move your character" << endl;
        cin >> movement;
        if(!map.executeMove(movement)) {
            continue;
        }
    }
    while(!map.isSiteLocation(map.getPlayerRowPosition(), map.getPlayerColPosition()));
    return map;
}

int main() {
    Game game = Game();
    DisplayASCII displayASCII = DisplayASCII();
    Map map = Map();
    srand(time(0));
    BattleField battleField1 = BattleField(1);
    BattleField battleField2 = BattleField(1);
    BattleField battleField3 = BattleField(1);
    displayASCII.display("sorcererMainScreen.txt");
    string tempInput;
    cin >> tempInput;
    bool menuSelect = menu(displayASCII);
    if(menuSelect == false) return 0;
    
    //Create characters here
    Player player = createPC(game);

    //NPC 1
    Library npcLib1 = Library(game.getFirstCharacter() + ".txt", "Animist.txt", "Outcast_Sanctuary.txt");
    Player npc1 = Player(npcLib1, true, game.getFirstCharacter(), game);
    game.removeCharacter(0);

    //NPC 2
    Library npcLib2 = Library(game.getFirstCharacter() + ".txt", "Demonologist.txt", "Screaming_Coast.txt");
    Player npc2 = Player(npcLib2, true, game.getFirstCharacter(), game);
    game.removeCharacter(0);

    //NPC 3
    Library npcLib3 = Library(game.getFirstCharacter() + ".txt", "Necromancer.txt", "Haunted_Forest.txt");
    Player npc3 = Player(npcLib3, true, game.getFirstCharacter(), game);
    game.removeCharacter(0);

    //Clear previous files
    writeOutFile("statsFiles/kills.txt", "0");

    //Map loop here
    map.fillMap();
    map = moveAroundMap(map);
    writeOutFile("statsFiles/sites.txt", "1");
    //Story for first encounter 
    cout<<"You have reached the first city and see your foe waiting for your arrival"<<endl;
    cout<<"The first chapter in your story of fierce combat is about to begin!"<<endl;

    actionPhase(player, npc1, battleField1, displayASCII);
    map = moveAroundMap(map);
    writeOutFile("statsFiles/sites.txt", "2");
    //Story for second encounter here
     cout<<"You have reached the second city and see a sorcerer ready for a fight."<<endl;
     cout<<"They are going to be in for a nasty beat down..."<<endl;

    actionPhase(player, npc2, battleField2, displayASCII);
    map = moveAroundMap(map);
    writeOutFile("statsFiles/sites.txt", "3");
    //Story for third and final encounter here
     cout<<"You have reached the last city and see the last obstacle in your path to total domination."<<endl;
     cout<<"Your battle will be legendary!!!"<<endl;

    actionPhase(player, npc2, battleField3, displayASCII);
    game.winGame();
}