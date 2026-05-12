// cards.h
// Author: Katelyn Hamel
// Declarations for Card, BST node, and CardBST classes

#ifndef CARDS_H
#define CARDS_H

#include <iostream>
#include <string>

// ── Card ─────────────────────────────────────────────────────────────────────
struct Card {
    char suit;   // 'h', 'd', 'c', 's'
    int  value;  // 1=ace, 2-10, 11=jack, 12=queen, 13=king

    Card() : suit('a'), value(0) {}
    Card(char s, int v) : suit(s), value(v) {}

    bool operator==(const Card& other) const;
    bool operator<(const Card& other)  const;
    bool operator>(const Card& other)  const;

    friend std::ostream& operator<<(std::ostream& os, const Card& c);
};

// ── BST Node ─────────────────────────────────────────────────────────────────
struct Node {
    Card  card;
    Node* left;
    Node* right;
    Node(Card c) : card(c), left(nullptr), right(nullptr) {}
};

// ── CardBST ──────────────────────────────────────────────────────────────────
class CardBST {
public:
    CardBST() : root(nullptr) {}
    ~CardBST();

    void insert(Card c);
    bool contains(Card c) const;
    void remove(Card c);
    void print() const;

    // iterator support (in-order traversal)
    Card  getSmallest() const;
    Card  getLargest()  const;
    Card  getNext(Card c) const;   // next card in-order after c
    Card  getPrev(Card c) const;   // prev card in-order before c

    bool  isEmpty() const { return root == nullptr; }

private:
    Node* root;

    // recursive helpers
    Node* insertR(Node* n, Card c);
    bool  containsR(Node* n, Card c) const;
    Node* removeR(Node* n, Card c);
    void  printR(Node* n) const;
    void  destroyR(Node* n);
    Node* minNode(Node* n) const;
    Node* maxNode(Node* n) const;
    Card  getNextR(Node* n, Card c, Card* best) const;
    Card  getPrevR(Node* n, Card c, Card* best) const;
};

#endif