#include <iostream>
#include <fstream>
#include <string>
#include "card_list.h"

using namespace std;

// Helper to convert card face strings to integers for BST sorting
int getVal(string s) {
    if (s == "a") return 1;
    if (s == "j") return 11;
    if (s == "q") return 12;
    if (s == "k") return 13;
    try {
        return stoi(s);
    } catch (...) {
        return 0; 
    }
}

int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "Please provide 2 file names" << endl;
        return 1;
    }

    ifstream f1(argv[1]);
    ifstream f2(argv[2]);

    if (f1.fail() || f2.fail()) {
        return 1;
    }

    player alice("Alice");
    player bob("Bob");

    char suit;
    string face;

    // Load Alice's cards into BST
    while (f1 >> suit >> face) {
        alice.getHand().insert(suit, getVal(face));
    }
    // Load Bob's cards into BST
    while (f2 >> suit >> face) {
        bob.getHand().insert(suit, getVal(face));
    }

    f1.close();
    f2.close();

    bool aliceTurn = true;
    while (true) {
        bool foundMatchInThisTurn = false;

        if (aliceTurn) {
            // Alice Turn: Smallest to Largest
            card* curr = alice.getHand().getMin(alice.getHand().getRoot());
            while (curr != nullptr) {
                // IMPORTANT: Save successor before removal
                card* nextInOrder = alice.getHand().successor(*curr);

                if (bob.getHand().search(*curr)) {
                    cout << "Alice picked matching card " << *curr << endl;
                    card match = *curr; // Create a copy of the data
                    
                    // Call the public wrapper: void remove(card target)
                    alice.getHand().remove(match);
                    bob.getHand().remove(match);
                    
                    foundMatchInThisTurn = true;
                    break; 
                }
                curr = nextInOrder;
            }
        } else {
            // Bob Turn: Largest to Smallest
            card* curr = bob.getHand().getMax(bob.getHand().getRoot());
            while (curr != nullptr) {
                // IMPORTANT: Save predecessor before removal
                card* prevInOrder = bob.getHand().predecessor(*curr);

                if (alice.getHand().search(*curr)) {
                    cout << "Bob picked matching card " << *curr << endl;
                    card match = *curr;
                    
                    alice.getHand().remove(match);
                    bob.getHand().remove(match);

                    foundMatchInThisTurn = true;
                    break; 
                }
                curr = prevInOrder;
            }
        }

        if (!foundMatchInThisTurn) break;
        aliceTurn = !aliceTurn;
    }

    // Output formatting for Gradescope
    cout << endl << "Alice's cards:" << endl;
    alice.getHand().print();
    cout << endl << "Bob's cards:" << endl;
    bob.getHand().print();

    return 0;
}
/*
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
card* bobCurr   = bob.getHand().getHead();

while (true) {
    bool foundMatch = false;

    // Alice's Turn
    while (aliceCurr != nullptr) {
        if (bob.getHand().search(*aliceCurr)) {
            card matched = *aliceCurr;
            cout << "Alice picked matching card " << matched << endl;

            // Move the marker before deleting
            card* nextAlice = aliceCurr->getNext();
            
            // Critical: If Bob's marker was on this card, move it!
            if (bobCurr != nullptr && *bobCurr == matched) {
                bobCurr = bobCurr->getNext();
            }

            alice.getHand().remove(matched);
            bob.getHand().remove(matched);

            aliceCurr = nextAlice;
            foundMatch = true;
            break; // Alice found one, Bob's turn
        }
        aliceCurr = aliceCurr->getNext();
    }

    if (!foundMatch) break; // Alice finished searching her hand and found nothing
    foundMatch = false; 

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
            foundMatch = true;
            break; // Bob found one, Alice's turn
        }
        bobCurr = bobCurr->getNext();
    }

    if (!foundMatch) break; // Bob finished searching his hand and found nothing
}

    cout << endl << "Alice's cards:" << endl;
    alice.getHand().print();
    cout << endl << "Bob's cards:" << endl;
    bob.getHand().print();


    return 0;
}
*/
