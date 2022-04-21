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


/*
TO DO:
Add the rest of the menu options for the main menu like how to play
Add the story elements in the main function for when you reached a battlefield
Fix looping input bug - DONE
Finish abilities - DONE
Add sorting algorithm - DONE
Make sure code meets requirements
Add file output with the stats
SUBMIT
*/

using namespace std;

bool menu(DisplayASCII displayASCII) {
    while(true) {
        string selection = "";
        displayASCII.display("selectScreen.txt");
        cin >> selection;
        if(selection == "1") return true;
        else if(selection == "2") {
            //Prints how to play
        }
        else if(selection == "3") {
            //Prints the games story
        }
        else if(selection == "4") {
            //Print previous games stats by reading the stats file
        }
        else if(selection == "5") displayASCII.display("credits.txt");
        else if(selection == "6") return false;
        else {
            cout << "Invalid input" << endl;
        }
    }
}

Player createPC(Game &game) {
    string input;
    vector<string> displayAtEnd;
    string deck1 = "";
    string deck2 = "";
    string deck3 = "";
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
    Library library = Library(deck1, deck2, deck3);
    Player player = Player(library, false, "", game);
    return player;
}

void waitForPlayer() {
    cout << endl << "Press any key + enter..." << endl;
    string ranIN = "";
    cin >> ranIN;
}

int battlePhase(Player player, Player npc, BattleField battleField, DisplayASCII display) {
   
    int input = 0;
    cout << "You go first!" << endl;

    while(true) {
        if(battleField.getEnemyMinions().size() == 0 && battleField.getPlayerMinions().size() == 0) {
            cout << "No player has any minions on the battle field! Returing to prep-phase" << endl;
            player.resetPlayer();
            npc.resetPlayer();
            battleField.resetBattleField();
            return 1;
        }

        display.displayEnemyBattleField(battleField, npc);
        waitForPlayer();
        display.displayBattleField(battleField, player);
        if(battleField.getPlayerMinions().size() == 0) {
            cout << "You have no enemy minions on the battlefield! You will take DOUBLE (2x) damage this turn" << endl;
            battleField.setEnemyDamageMultiplier(2);
        }
        else { 
            cout << endl << "Which creature do you want to attack with? (Or type -1 to draw and restart)" << endl;
            input = 0;
            cin >> input;
            if(cin.fail()) {
                cout << "Invalid input!" << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            if(input  == -1) {
                player.resetPlayer();
                npc.resetPlayer();
                battleField.resetBattleField();
                return 1;
            }
            else if(input <= battleField.getPlayerMinions().size() && input >= 1) {
                Spell spell = player.getLibrary().getSpellAt(battleField.getPlayerMinions().at(input-1));
                battleField.playerDealDamage(player, npc, spell);
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

int actionPhase(Player player, Player npc, BattleField battleField, DisplayASCII display) {
    int actions = 0;
    player.setActions(10);
    while(actions != 10) {
        int input = 0;
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
        if(input == 1) {
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
        else if(input == 2) {
            cout << "You memorized two spells!" << endl;
            player.drawSpells();
            player.drawSpells();
        }
        else if(input == 3) {
            cout << "You gained two mana" << endl;
            player.gainTwoMana();
        }
        else if(input == 4) {
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
        if(npc.getHandSize() != 0) {
            ranNum = int(rand() % npc.getHandSize());
        }
        if(npc.getHandSize() == 0) {
            for(int i = 0; i < 2; i++) {
                if(npc.drawSpells() == 0) {
                    cout << "The enemy sorcer " << npc.getName() << " has run out of spells to cast! You won this battle field!" << endl;
                    return 1;
                }
            }
            cout << endl << npc.getName() << " memorized two spells!" << endl;
        }
        else if(npc.getMana() < npc.getSpellInHand(ranNum).getSpellManaCost()) {
            npc.gainTwoMana();
            cout << endl << npc.getName() << " gained two mana!" << endl << endl;
        } 
        else if(npc.getMana() >= npc.getSpellInHand(ranNum).getSpellManaCost()) {
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

    Library npcLib1 = Library(game.getFirstCharacter() + ".txt", "Animist.txt", "Outcast_Sanctuary.txt");
    Player npc1 = Player(npcLib1, true, game.getFirstCharacter(), game);
    game.removeCharacter(0);

    Library npcLib2 = Library(game.getFirstCharacter() + ".txt", "Demonologist.txt", "Screaming_Coast.txt");
    Player npc2 = Player(npcLib2, true, game.getFirstCharacter(), game);
    game.removeCharacter(0);

    Library npcLib3 = Library(game.getFirstCharacter() + ".txt", "Necromancer.txt", "Haunted_Forest.txt");
    Player npc3 = Player(npcLib3, true, game.getFirstCharacter(), game);
    game.removeCharacter(0);

    //Map loop here
    int battleFieldsHit = 0;
    map.fillMap();
    map = moveAroundMap(map);
    //Story for first encounter here
    actionPhase(player, npc1, battleField1, displayASCII);
    map = moveAroundMap(map);
    //Story for second encounter here
    actionPhase(player, npc2, battleField2, displayASCII);
    map = moveAroundMap(map);
    //Story for third and final encounter here
    actionPhase(player, npc2, battleField3, displayASCII);
    game.winGame();
}