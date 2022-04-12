#include "Map.h"
#include <iostream>
using namespace std;

int main() {
    Map map = Map();
    map.spawnNPC(4,5);
    map.spawnSite(3,4,5);
    map.displayMap();
}