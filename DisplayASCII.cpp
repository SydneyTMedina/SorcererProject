#include <iostream>
#include "DisplayASCII.h"
#include <fstream>
#include <string>
#include "Spell.h"
#include <vector>
#include "Player.h"

using namespace std;

DisplayASCII::DisplayASCII() {

}


/*
Takes a file as input and reads through it line by line
Prints every line it sees so we can easily print large amounts of text
*/
bool DisplayASCII::display(string _fileName) {
    _fileName = "images/" + _fileName;
    ifstream file;
    file.open(_fileName);
    if(!file.is_open()) return false;
    string line;
    while(getline(file, line)) {
        cout << line << endl;
    }
    return true;
}

/*
Starts with taking in the image template file, adding eachline to an array of string so it can be modified
Adds the corrisonding data needed to each card like health, attack, mana, ect.
Loops through that array and prints each string to display a card
*/
bool DisplayASCII::displayCard(Spell _spell, bool showAbility) {
    string fileName = "images/cardTemplate.txt";
    ifstream file;
    file.open(fileName);
    if(!file.is_open()) return false;
    string line;
    vector<string> cardData;
    while(getline(file, line)) {
        cardData.push_back(line);
    }
    cardData.insert(cardData.begin(), _spell.getSpellName());
    if(_spell.getSpellManaCost() < 10) {
        cardData.at(4).replace(12,2, "0" + to_string(_spell.getSpellManaCost()));
    }
    else {
        cardData.at(4).replace(12,2, to_string(_spell.getSpellManaCost()));
    }
    if(_spell.getSpellHealth() < 10) {
        cardData.at(6).replace(9,2, "0" + to_string(_spell.getSpellHealth()));
    }
    else {
        cardData.at(6).replace(9,2, to_string(_spell.getSpellHealth()));
    }
    cardData.at(8).replace(9,1, to_string(_spell.getSpellAttack()));
    if(showAbility) {
        if(_spell.getSpellAbility() != 0) {
            cardData.push_back("Ability:");
            cardData.push_back(abilityDescriptions.at(_spell.getSpellAbility()));
        }
    }
    for(int i = 0; i < cardData.size(); i++) {
        cout << cardData.at(i) << endl;
    }
    return true;
}

//Displays the players hand with corresponding data using the display card function
bool DisplayASCII::displayHand(Player player) {
    cout << endl << "Your Availible Spells:" << endl << endl;
    if(player.getHandSize() == 0) {
        cout << "You have no spells! Memorize more" << endl;
        return false;
    }
    for(int i = 0; i < player.getHandSize(); i++) {
        cout << "------Spell " << i+1  << "------"<< endl;
        if(!displayCard(player.getSpellInHand(i), true)) {
            return false;
        }
    }
    cout << endl << "Scroll up to look at your availible spells" << endl;
    return true;
}
//Uses the playersminions vector to print all the minions the player has currently on the battlefield
bool DisplayASCII::displayBattleField(BattleField _battleField, Player player) {
    if(_battleField.getPlayerMinions().size() == 0) {
        cout << "You have no minions on the battle field! " << endl;
        return false;
    }
    for(int i = 0; i < _battleField.getPlayerMinions().size(); i++) {
        cout << "------Minion " << i+1  << "------"<< endl;
        Spell spell = player.getLibrary().getSpellAt(_battleField.getPlayerMinions().at(i));
        displayCard(spell, false);        
    }
    cout << endl << "Scroll up to look at your minions" << endl;
    return true;
}
//Uses the enemyminions vector to print all the minions the player has currently on the battlefield
bool DisplayASCII::displayEnemyBattleField(BattleField _battleField, Player npc) {
    cout << "Enemy minions on the battlefield" << endl;
    if(_battleField.getEnemyMinions().size() == 0) {
        cout << "The enemy has no minions on the battle field! " << endl;
        return false;
    }
    for(int i = 0; i < _battleField.getEnemyMinions().size(); i++) {
        Spell spell = npc.getLibrary().getSpellAt(_battleField.getEnemyMinions().at(i));
        displayCard(spell,false);        
    }
    cout << endl << "Scroll up to look at the enemy minions on the battlefield" << endl;
    return true;
}