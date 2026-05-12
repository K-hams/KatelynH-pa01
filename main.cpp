// This file should implement the game using a custom implementation of a BST (based on your earlier BST implementation)
#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
#include "card_list.h"
//Do not include set in this file

using namespace std;

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }


  player alice("Alice");
  player bob("Bob");
  
 while (getline(cardFile1, line) && line.length() > 0) {
    if (!line.empty() && line.back() == '\r') line.pop_back();
    char suit = line[0];
    string face = line.substr(2);
    alice.getHand().insert(card(suit, face));
}
cardFile1.close();  // add this back

while (getline(cardFile2, line) && line.length() > 0) {
    if (!line.empty() && line.back() == '\r') line.pop_back();
    char suit = line[0];
    string face = line.substr(2);
    bob.getHand().insert(card(suit, face));
}
cardFile2.close();

card* aliceCurr = alice.getHand().getHead();
card* bobCurr   = bob.getHand().getHead();

bool matchFound = true;
while (matchFound) {
    matchFound = false;

    // Alice's turn
    while (aliceCurr != nullptr) {
        card* nextAlice = aliceCurr->getNext();
        if (bob.getHand().search(*aliceCurr)) {
            card matched = *aliceCurr;
            alice.getHand().remove(matched);
            bob.getHand().remove(matched);
            aliceCurr = nextAlice;
            cout << "Alice picked matching card " << matched << endl;
            matchFound = true;
            break;
        }
        aliceCurr = nextAlice;  // use nextAlice, not getNext()
    }
    if (!matchFound) break;
    matchFound = false;

    // Bob's turn
    while (bobCurr != nullptr) {
        card* nextBob = bobCurr->getNext();
        if (alice.getHand().search(*bobCurr)) {
            card matched = *bobCurr;
            alice.getHand().remove(matched);
            bob.getHand().remove(matched);
            bobCurr = nextBob;
            cout << "Bob picked matching card " << matched << endl;
            matchFound = true;
            break;
        }
        bobCurr = nextBob;  // use nextBob, not getNext()
    }
}

cout << "\nAlice's cards:" << endl;
alice.getHand().print();
cout << "\nBob's cards:" << endl;
bob.getHand().print();

return 0;
}
