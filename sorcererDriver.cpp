#include "Library.h"
#include "Player.h"
#include "DisplayASCII.h"
#include <vector>

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

Player createPC() {
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
            break;
        }
        else if(input == "2") {
            deck1 = "Tegu.txt";
            displayAtEnd.push_back("Tegu");
            break;
        }
        else if(input == "3") {
            deck1 = "Zevrane.txt";
            displayAtEnd.push_back("Zevrane");
            break;
        }
        else if(input == "4") {
            deck1 = "Ariaspes.txt";
            displayAtEnd.push_back("Ariaspes");
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
    Player player = Player(library, false);
    return player;
}

void actionPhase(Player player, Player npc, BattleField battleField) {
    for(int i = 0; i < 6; i++) {
        string input = "";
        cout << "What do you want to do?" << endl << endl << "1 -> Cast a spell" << endl << "2 -> Memorize spells" << endl << "3 -> Gain energy" << endl;
        cin >> input;
    }
}

int main() {
    DisplayASCII displayASCII = DisplayASCII();
    displayASCII.display("sorcererMainScreen.txt");
    string tempInput;
    cin >> tempInput;
    bool menuSelect = menu(displayASCII);
    if(menuSelect == false) return 0;
    
    //Create characters here
    Player player = createPC();


}