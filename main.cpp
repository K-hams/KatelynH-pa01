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
  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
    card newCard(line[0], line[2]);
    alice.getHand().insert(newCard);

  }
  cardFile1.close();


  while (getline (cardFile2, line) && (line.length() > 0)){
    card newCard(line[0], line[2]);
    bob.getHand().insert(newCard);
  }
  cardFile2.close();
  
  //starting the game here:
    card* aliceCurr = alice.getHand().getHead();
    card* bobCurr   = bob.getHand().getHead();

    bool matchFound = true;
    while (matchFound) {
        matchFound = false;

        // Alice's turn
        while (aliceCurr != nullptr) {
            card* nextAlice = aliceCurr->getNext();  // save BEFORE remove
            if (bob.getHand().search(*aliceCurr)) {
                cout << "Alice picked matching card " << *aliceCurr << endl;
                card matched = *aliceCurr;
                alice.getHand().remove(matched);
                bob.getHand().remove(matched);
                aliceCurr = nextAlice;
                matchFound = true;
                break;
            }
            aliceCurr = aliceCurr->getNext();
        }
        if (!matchFound) break;

        matchFound = false;

        // Bob's turn
        while (bobCurr != nullptr) {
            card* nextBob = bobCurr->getNext();      // save BEFORE remove
            if (alice.getHand().search(*bobCurr)) {
                cout << "Bob picked matching card " << *bobCurr << endl;
                card matched = *bobCurr;
                alice.getHand().remove(matched);
                bob.getHand().remove(matched);
                bobCurr = nextBob;
                matchFound = true;
                break;
            }
            bobCurr = bobCurr->getNext();
        }
    }

   
    cout << "\nAlice's cards:" << endl;
    alice.getHand().print();
    cout << "\nBob's cards:" << endl;
    bob.getHand().print();
  
  return 0;
}
