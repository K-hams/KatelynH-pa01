// card_list.h
// Author: Katelyn Hamel
// All class declarations related to defining a BST that represents a player's hand
/**/

#ifndef CARD_LIST_H
#define CARD_LIST_H

#include <iostream>
#include <string>

#include "card.h"

class hand {
public:
    hand() : root(nullptr) {}
    ~hand();

    void insert(char suit, int value);
    void remove(card target);
    bool search(card target) const;
    void print() const;

    card* getMin(card* node) const;
    card* getMax(card* node) const;
    card* getRoot() const { return root; }

    // Successor for Alice, Predecessor for Bob
    card* successor(card target) const;
    card* predecessor(card target) const;

private:
    card* root;
    card* insert(card* node, char suit, int value);
    card* remove(card* node, card target);
    void clear(card* node);
    void print(card* node) const;
    bool search(card* node, card target) const;
};

class player {
public:
    player(std::string n) : name(n) {}
    std::string getName() const { return name; }
    hand& getHand() { return myHand; }
    friend std::ostream& operator<<(std::ostream& os, player& p);

private:
    std::string name;
    hand myHand;
};

#endif

/*
//hand aka linked list
class hand{
    public:
        //construct
        hand(): root(nullptr){}
        hand(card* start): root(start){}

        ~hand(){
             card* curr = root;
            while (curr != nullptr) {
                card* next = curr->getNext();
                delete curr;
                curr = next;
            }
        }

        //funcs
        bool search(card target);
        void remove(card target);
        void insert(card newCard);
        void print() const;
        card currentCard();
        card* getHead() const{
            return root;
        }

    private:
        card* root;

};

//player holds a hand hand is a linked list of cards
class player{
    public:
    //consturctor
        player(): name("blank"){}

        player(std::string n){
            name = n;
       
        }

        std::string getName(){
            return name;
        }
        void setName(std::string nN){
            name = nN;
        }
        hand& getHand(){
            return myHand;
        }
    
        //operator overloading
        friend std::ostream& operator<<(std::ostream& os, const player& p);

    private:
        std::string name;
        hand myHand;



};

#endif
*/
