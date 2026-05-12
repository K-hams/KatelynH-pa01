// main.cpp
// Author: Katelyn Hamel
// Card game using a BST to store each player's hand

#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
using namespace std;

// Convert a face-value string from the file into an int
int parseValue(const string& val) {
    if (val == "a")  return 1;
    if (val == "j")  return 11;
    if (val == "q")  return 12;
    if (val == "k")  return 13;
    return stoi(val);
}

int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "Please provide 2 file names" << endl;
        return 1;
    }

    ifstream cardFile1(argv[1]);
    ifstream cardFile2(argv[2]);
    string line;

    if (cardFile1.fail() || cardFile2.fail()) {
        cout << "Could not open file " << argv[2] << endl;
        return 1;
    }

    CardBST alice, bob;

    while (getline(cardFile1, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.length() < 3) continue;
        alice.insert(Card(line[0], parseValue(line.substr(2))));
    }
    cardFile1.close();

    while (getline(cardFile2, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.length() < 3) continue;
        bob.insert(Card(line[0], parseValue(line.substr(2))));
    }
    cardFile2.close();

    // ── game loop ─────────────────────────────────────────────────────────
    // Alice scans from smallest card upward; Bob scans from largest downward.
    // Each player resumes where they left off each round.

    Card aliceCurr = alice.getSmallest();
    Card bobCurr   = bob.getLargest();

    bool matchFound = true;
    while (matchFound) {
        matchFound = false;

        // Alice's turn — walk her BST in ascending order
        Card ac = aliceCurr;
        while (true) {
            if (bob.contains(ac)) {
                cout << "Alice picked matching card " << ac << endl;
                Card matched = ac;
                ac = alice.getNext(ac);   // advance before remove
                if (bobCurr == matched)
                    bobCurr = bob.getPrev(matched);
                alice.remove(matched);
                bob.remove(matched);
                aliceCurr = ac;
                matchFound = true;
                break;
            }
            Card nx = alice.getNext(ac);
            if (nx == ac || alice.isEmpty()) break;  // no more cards
            ac = nx;
        }
        if (!matchFound) break;
        matchFound = false;

        // Bob's turn — walk his BST in descending order
        Card bc = bobCurr;
        while (true) {
            if (alice.contains(bc)) {
                cout << "Bob picked matching card " << bc << endl;
                Card matched = bc;
                bc = bob.getPrev(bc);     // advance before remove
                if (aliceCurr == matched)
                    aliceCurr = alice.getNext(matched);
                alice.remove(matched);
                bob.remove(matched);
                bobCurr = bc;
                matchFound = true;
                break;
            }
            Card pv = bob.getPrev(bc);
            if (pv == bc || bob.isEmpty()) break;
            bc = pv;
        }
    }

    cout << "\nAlice's cards:" << endl;
    alice.print();
    cout << "\nBob's cards:" << endl;
    bob.print();

    return 0;
}