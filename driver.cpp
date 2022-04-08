#include <iostream>
#include <cassert>
#include "Player.h"
using namespace std;

int main() {
    Library library = Library("Tegu.txt", "Necromancer.txt", "Haunted_Forest.txt");
    BattleField battleField = BattleField(20); 
    Player player = Player(library, false);
    //Prints You have 6 mana and have 6 actions left.
    player.displayGameInfo();
    player.setActions(2);
    player.setMana(0);
    //Prints You have 0 mana and have 2 actions left.
    player.displayGameInfo();
    //Prints a random spell in hand position 0
    cout << library.getSpellAt(player.getSpellInHandPos(0)).getSpellName() << endl;
    //Prints a new card after removing the first one from the first index
    player.removeSpellFromHand(0);
    cout << library.getSpellAt(player.getSpellInHandPos(0)).getSpellName() << endl;
    //Tests the drawing of spells functionality
    player.drawSpells();
    cout << library.getSpellAt(player.getSpellInHandPos(0)).getSpellName() << endl;
    //Tests the shuffling function, should return nothing
    player.shuffleDeck();
    //Tests getting specific aspects of cards from the library
    assert(library.getSpellAt(0).getSpellAttack() == 4);
    assert(library.getSpellAt(0).getSpellHealth() == 4);
    assert(library.getSpellAt(0).getSpellAbility() == 0);
    assert(library.getSpellAt(0).getSpellName() == "Narangerel");
    //Testing the battlefield functionality of the health getters/setters
    assert(battleField.getBattleFieldHealth() == 20);
    battleField.setBattleFieldHealth(10);
    assert(battleField.getBattleFieldHealth() == 10);
}
