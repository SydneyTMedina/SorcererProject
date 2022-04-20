#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Library.h"
#include "Spell.h"
using namespace std;

/*
Split function rewritten to use and return vectors so size can change
*/
vector<string> split(string inputString, char separator, vector<string> vect) {
    int currentSeparator = 0;
    if (inputString.size() == 0) return vect;
    inputString = inputString + separator;
    for(int i = 0; i < inputString.size(); i++) {
        if(inputString[i] == separator) {
            string toAdd = inputString.substr(currentSeparator, i-currentSeparator);
            vect.push_back(toAdd);
            currentSeparator = i + 1;
        }
    }
    return vect;
}
/*
1. Opens a file and checks if it is open or not. If it is not open, return
2. Loops through the file and using the split funtion, create a new spell and assign the data by the split data
3. Add cards to the spells vector
*/
void Library::addDeck(string filename) {
    filename = "decks/" + filename;
    fstream file;
    file.open(filename);
    if(!file.is_open()) {
        cout << "file did not open" << endl;
        return;
    }
    string line;
    while(getline(file, line)) {
        vector<string> lineData;
        lineData = split(line, ',', lineData);
        Spell card = Spell(lineData.at(0), stoi(lineData.at(1)), stoi(lineData.at(2)), stoi(lineData.at(3)), stoi(lineData.at(4)));
        spells.push_back(card);
    }
}

//Default constructor with no spells
Library::Library() {
    spells.clear();
}

//Constructor but with 3 decks. Adds the decks 1 by 1 by using add deck method
Library::Library(string _deck1, string _deck2, string _deck3) {
    addDeck(_deck1);
    addDeck(_deck2);
    addDeck(_deck3);
}

//Gets a copy of all the spells in the library class so we don't accidentally modify it
vector<Spell> Library::getSpells() {
    vector<Spell> toReturn;
    for(Spell spell : spells) {
        toReturn.push_back(spell);
    }
    return toReturn;
}

//Gets a spell at a specific location
Spell Library::getSpellAt(int _pos) {
        return spells.at(_pos);
}

//Takes a spell and returns its position in the vector
int Library::getSpellId(Spell _spell) {
    for(int i = 0; i < spells.size(); i++) {
        if(_spell.getSpellName() == spells.at(i).getSpellName()) return i;
    } 
    return -1;
}

//Resets the spell vector and assigns it to a new list of spells
void Library::setSpells(vector<Spell> _newSpells) {
    spells.clear();
    for(int i = 0; i < _newSpells.size(); i++) {
        spells.push_back(_newSpells.at(i));
    }
}