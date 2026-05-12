// card_list.cpp
// Author: Katelyn Hamel
// Implementation of the classes defined in card_list.h

//ALL IMPLEMENTS FOR HAND


#include "card_list.h"
using namespace std;


hand::~hand() { clear(root); }
void hand::clear(card* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

void hand::insert(char suit, int value) { root = insert(root, suit, value); }
card* hand::insert(card* node, char suit, int value) {
    if (!node) return new card(suit, value);
    card temp(suit, value);
    if (temp < *node) node->left = insert(node->left, suit, value);
    else node->right = insert(node->right, suit, value);
    return node;
}

bool hand::search(card target) const { return search(root, target); }
bool hand::search(card* node, card target) const {
    if (!node) return false;
    if (*node == target) return true;
    if (target < *node) return search(node->left, target);
    return search(node->right, target);
}


void hand::remove(card target) {
    root = remove(root, target); // Calls the private recursive helper
}


card* hand::remove(card* node, card target) {
    if (!node) return nullptr;

    if (target < *node) {
        node->left = remove(node->left, target);
    } else if (target > *node) {
        node->right = remove(node->right, target);
    } else {
        // Node found! 
        // Case 1 & 2: One child or no child
        if (!node->left) {
            card* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) {
            card* temp = node->left;
            delete node;
            return temp;
        }

        // Case 3: Two children
        // Get the smallest in the right subtree
        card* temp = getMin(node->right);
        
    
        node->suit = temp->suit;
        node->value = temp->getValue();

        // Delete the successor node
        node->right = remove(node->right, *temp);
    }
    return node;
}
card* hand::getMin(card* node) const {
    while (node && node->left) node = node->left;
    return node;
}

card* hand::getMax(card* node) const {
    while (node && node->right) node = node->right;
    return node;
}

void hand::print() const { print(root); }
void hand::print(card* node) const {
    if (node) {
        print(node->left);
        cout << *node << endl;
        print(node->right);
    }
}

// Logic to find next card for game turns
card* hand::successor(card target) const {
    card* curr = root;
    card* succ = nullptr;
    while (curr != nullptr) {
        if (target < *curr) {
            succ = curr;       // This might be the successor
            curr = curr->left; // Look for a smaller successor
        } else {
            curr = curr->right;
        }
    }
    return succ;
}

card* hand::predecessor(card target) const {
    card* curr = root;
    card* pred = nullptr;
    while (curr != nullptr) {
        if (target > *curr) {
            pred = curr;        // This might be the predecessor
            curr = curr->right; // Look for a larger predecessor
        } else {
            curr = curr->left;
        }
    }
    return pred;
}
/*
bool hand::search(card target){
    card* curr = root;
    while (curr != nullptr){
        if (*curr == target){
            return true;
        }
        
        curr = curr->getNext();

    }
    return false;
}

void hand::insert(card newCard){
    card* newC = new card(newCard.getName(), newCard.getValue());
    
    if (root == nullptr) {
        root = newC;
    } else {
        // Find the tail
        card* curr = root;
        while (curr->getNext() != nullptr) {
            curr = curr->getNext();
        }
        curr->setNext(newC);
    }

}
void hand::remove(card target){
    card* curr = root;
    card* prev = nullptr;
    
    while (curr != nullptr){
        if(*curr == target){
            if (prev == nullptr){
                root = curr->getNext();
            }
            else{
                prev->setNext(curr->getNext());
            }
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->getNext();
    }
   return;

}


void hand::print() const{
    card* curr = root;
    while (curr !=nullptr){
        cout <<  *curr<<endl;
        curr = curr->getNext();
    }

}

card hand::currentCard(){
    return *root;
}

//ALL FOR PLAYER
  
std::ostream& operator<<(std::ostream& os, const player& p) {
    os << p.name << "'s cards:" << endl;
    p.myHand.print();  
    return os;
}
*/






