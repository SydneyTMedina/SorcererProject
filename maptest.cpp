#include "Map.h"
#include <iostream>
using namespace std;

int main() {
    Map map = Map();
    map.fillMap();
    while(!map.isSiteLocation(map.getPlayerRowPosition(), map.getPlayerRowPosition())) {
        char movement;
        map.displayMap();
        cout << endl << "Use (W,A,S,D) to move your character" << endl;
        cin >> movement;
        if(!map.executeMove(movement)) {
            continue;
        }
    }
    cout << "You have hit a city!" << endl;
}