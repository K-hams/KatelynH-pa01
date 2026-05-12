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
cardFile1.close();  


while (getline(cardFile2, line) && line.length() > 0) {
    if (!line.empty() && line.back() == '\r') line.pop_back();
    char suit = line[0];
    string face = line.substr(2);
    bob.getHand().insert(card(suit, face));
}
cardFile2.close();


    card* aliceCurr = alice.getHand().getHead();
    card* bobCurr = bob.getHand().getHead();


    while (true) {
        bool matchFound = false;


        // Alice's Turn: Search from where she left off
        while (aliceCurr != nullptr) {
            if (bob.getHand().search(*aliceCurr)) {
                card matched = *aliceCurr;
                cout << "Alice picked matching card " << matched << endl;


                // Move aliceCurr forward before the node is deleted
                card* nextAlice = aliceCurr->getNext();
               
                // If Bob was currently looking at the card that's about to be deleted,
                // move Bob's pointer forward as well.
                if (bobCurr != nullptr && *bobCurr == matched) {
                    bobCurr = bobCurr->getNext();
                }


                alice.getHand().remove(matched);
                bob.getHand().remove(matched);


                aliceCurr = nextAlice;
                matchFound = true;
                break; // Turn ends
            }
            aliceCurr = aliceCurr->getNext();
        }


        if (!matchFound) break; // End game if Alice finds no match
        matchFound = false;


        // Bob's Turn
        while (bobCurr != nullptr) {
            if (alice.getHand().search(*bobCurr)) {
                card matched = *bobCurr;
                cout << "Bob picked matching card " << matched << endl;


                card* nextBob = bobCurr->getNext();


                if (aliceCurr != nullptr && *aliceCurr == matched) {
                    aliceCurr = aliceCurr->getNext();
                }


                alice.getHand().remove(matched);
                bob.getHand().remove(matched);


                bobCurr = nextBob;
                matchFound = true;
                break; // Turn ends
            }
            bobCurr = bobCurr->getNext();
        }


        if (!matchFound) break;
    }

    cout << endl << "Alice's cards:" << endl;
    alice.getHand().print();
    cout << endl << "Bob's cards:" << endl;
    bob.getHand().print();


    return 0;
}

