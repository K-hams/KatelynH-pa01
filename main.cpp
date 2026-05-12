// This file should implement the game using a custom implementation of a BST (based on your earlier BST implementation)
#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
#include "card_list.h"
//Do not include set in this file


using namespace std;


int getVal(string s) {
    if (s == "a") return 1;
    if (s == "j") return 11;
    if (s == "q") return 12;
    if (s == "k") return 13;
    return stoi(s);
}

int main(int argc, char** argv) {
    if (argc < 3) return 1;
    ifstream f1(argv[1]), f2(argv[2]);
    player alice("Alice"), bob("Bob");
    string s, v; char suit;

    while (f1 >> suit >> v) alice.getHand().insert(suit, getVal(v));
    while (f2 >> suit >> v) bob.getHand().insert(suit, getVal(v));

    bool aliceTurn = true;
    while (true) {
        bool found = false;
        if (aliceTurn) {
            card* curr = alice.getHand().getMin(alice.getHand().getRoot());
            while (curr) {
                if (bob.getHand().search(*curr)) {
                    cout << "Alice picked matching card " << *curr << endl;
                    card match = *curr;
                    alice.getHand().remove(match);
                    bob.getHand().remove(match);
                    found = true; break;
                }
                curr = alice.getHand().successor(*curr);
            }
        } else {
            card* curr = bob.getHand().getMax(bob.getHand().getRoot());
            while (curr) {
                if (alice.getHand().search(*curr)) {
                    cout << "Bob picked matching card " << *curr << endl;
                    card match = *curr;
                    alice.getHand().remove(match);
                    bob.getHand().remove(match);
                    found = true; break;
                }
                curr = bob.getHand().predecessor(*curr);
            }
        }
        if (!found) break;
        aliceTurn = !aliceTurn;
    }

    cout << endl << "Alice's cards:" << endl; alice.getHand().print();
    cout << endl << "Bob's cards:" << endl; bob.getHand().print();
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
