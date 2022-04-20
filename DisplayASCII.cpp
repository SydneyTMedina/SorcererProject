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

bool DisplayASCII::displayCard(Spell _spell) {
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
    
    for(int i = 0; i < cardData.size(); i++) {
        cout << cardData.at(i) << endl;
    }
    return true;
}

vector<string> DisplayASCII::getCardLineData(Spell _spell) {
    string fileName = "images/cardTemplate.txt";
    ifstream file;
    vector<string> cardData;
    file.open(fileName);
    if(!file.is_open()) return cardData;
    string line;
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
    return cardData;
}

bool DisplayASCII::displayHand(Player player) {
    cout << endl << "Your Availible Spells:" << endl << endl;
    if(player.getHandSize() == 0) {
        cout << "You have no spells! Memorize more" << endl;
        return false;
    }
    for(int i = 0; i < player.getHandSize(); i++) {
        cout << "------Spell " << i+1  << "------"<< endl;
        if(!displayCard(player.getSpell(i))) {
            return false;
        }
    }
    cout << endl << "Scroll up to look at your availible spells" << endl;
    return true;
}

bool DisplayASCII::displayBattleField(BattleField _battleField, Player player) {
    if(_battleField.getPlayerMinions().size() == 0) {
        cout << "You have no minions on the battle field! " << endl;
        return false;
    }
    for(int i = 0; i < _battleField.getPlayerMinions().size(); i++) {
        cout << "------Minion " << i+1  << "------"<< endl;
        if(!displayCard(player.getLibrary().getSpellAt(_battleField.getPlayerMinions().at(i)))) {
            return false;
        }
    }
    cout << endl << "Scroll up to look at your availible spells" << endl;
    return true;
}