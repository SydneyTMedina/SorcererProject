#include <iostream>
#include "DisplayASCII.h"
#include <fstream>
#include <string>
#include <vector>
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

bool DisplayASCII::displayCard(string _cardName) {
    _cardName = "|" + _cardName;
    for(int i = 0; i < _cardName.size(); i++) {
        
    }
    string fileName = "images/cardTemplate.txt";
    ifstream file;
    file.open(fileName);
    if(!file.is_open()) return false;
    string line;
    vector<string> cardData;
    while(getline(file, line)) {
        cardData.push_back(line);
    }
    cardData.insert(cardData.begin() + 1, _cardName);
    for(int i = 0; i < cardData.size(); i++) {
        cout << cardData.at(i) << endl;
    }
    return true;
}