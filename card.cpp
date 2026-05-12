// cards.cpp
// Author: Katelyn Hamel
// Implementation of Card and CardBST

#include "card.h"
#include <iostream>
using namespace std;

// ── Card helpers ─────────────────────────────────────────────────────────────
// Order: sort by value first, then by suit
bool Card::operator==(const Card& other) const {
    return suit == other.suit && value == other.value;
}
bool Card::operator<(const Card& other) const {
    if (value != other.value) return value < other.value;
    return suit < other.suit;
}
bool Card::operator>(const Card& other) const {
    return other < *this;
}

// Print as original file format: suit then face label
ostream& operator<<(ostream& os, const Card& c) {
    os << c.suit << " ";
    if      (c.value == 1)  os << "a";
    else if (c.value == 11) os << "j";
    else if (c.value == 12) os << "q";
    else if (c.value == 13) os << "k";
    else                    os << c.value;
    return os;
}

// ── CardBST ──────────────────────────────────────────────────────────────────
CardBST::~CardBST() { destroyR(root); }

void CardBST::destroyR(Node* n) {
    if (n == nullptr) return;
    destroyR(n->left);
    destroyR(n->right);
    delete n;
}

// ── insert ───────────────────────────────────────────────────────────────────
void CardBST::insert(Card c) { root = insertR(root, c); }

Node* CardBST::insertR(Node* n, Card c) {
    if (n == nullptr) return new Node(c);
    if (c < n->card)  n->left  = insertR(n->left,  c);
    else if (c > n->card) n->right = insertR(n->right, c);
    // equal: don't insert duplicates
    return n;
}

// ── contains ─────────────────────────────────────────────────────────────────
bool CardBST::contains(Card c) const { return containsR(root, c); }

bool CardBST::containsR(Node* n, Card c) const {
    if (n == nullptr)  return false;
    if (c == n->card)  return true;
    if (c < n->card)   return containsR(n->left,  c);
    return containsR(n->right, c);
}

// ── remove ───────────────────────────────────────────────────────────────────
void CardBST::remove(Card c) { root = removeR(root, c); }

Node* CardBST::removeR(Node* n, Card c) {
    if (n == nullptr) return nullptr;
    if (c < n->card) {
        n->left = removeR(n->left, c);
    } else if (c > n->card) {
        n->right = removeR(n->right, c);
    } else {
        // found — three cases
        if (n->left == nullptr) {
            Node* tmp = n->right;
            delete n;
            return tmp;
        }
        if (n->right == nullptr) {
            Node* tmp = n->left;
            delete n;
            return tmp;
        }
        // two children: replace with in-order successor
        Node* succ = minNode(n->right);
        n->card    = succ->card;
        n->right   = removeR(n->right, succ->card);
    }
    return n;
}

Node* CardBST::minNode(Node* n) const {
    while (n->left != nullptr) n = n->left;
    return n;
}
Node* CardBST::maxNode(Node* n) const {
    while (n->right != nullptr) n = n->right;
    return n;
}

// ── print (in-order) ─────────────────────────────────────────────────────────
void CardBST::print() const { printR(root); }

void CardBST::printR(Node* n) const {
    if (n == nullptr) return;
    printR(n->left);
    cout << n->card << endl;
    printR(n->right);
}

// ── getSmallest / getLargest ─────────────────────────────────────────────────
Card CardBST::getSmallest() const { return minNode(root)->card; }
Card CardBST::getLargest()  const { return maxNode(root)->card; }

// ── getNext: smallest card greater than c ────────────────────────────────────
Card CardBST::getNext(Card c) const {
    Card best;
    bool found = false;
    Node* n = root;
    while (n != nullptr) {
        if (n->card > c) {
            best  = n->card;
            found = true;
            n     = n->left;   // try to find something smaller but still > c
        } else {
            n = n->right;
        }
    }
    return best;  // caller must check isEmpty or compare
}

// ── getPrev: largest card less than c ────────────────────────────────────────
Card CardBST::getPrev(Card c) const {
    Card best;
    Node* n = root;
    while (n != nullptr) {
        if (n->card < c) {
            best = n->card;
            n    = n->right;  // try to find something larger but still < c
        } else {
            n = n->left;
        }
    }
    return best;
}