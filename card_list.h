// card_list.h
// Author: Katelyn Hamel
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H

#include <iostream>
#include <string>

#include "card.h"
//hand aka linked list
class hand{
    public:
        //construct
        hand(): root(nullptr), tail(nullptr){}
        hand(card* start): root(start), tail(nullptr){}

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
        card* tail;
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
