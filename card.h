// card.h
// Author: Katelyn Hamel
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H

#include <iostream>
using namespace std;
//node aka card
class card{
    public:
        //default constructor
        card(): value("0"), name('a'), nextCard(nullptr){}
        //card with values
        card(char val, string n): value(n), name(val), nextCard(nullptr){}

        //funcs
        char getName() const;
        string getValue() const;
        card* getNext() const;
        void setNext(card* next);



      

        //overloaded operators
        //if equal
        bool operator==(const card& other) const;

        //printing
        friend std::ostream& operator<<(std::ostream& os, const card& c);

    private:
        string value;
        char name; 
        card* nextCard;
       


};







//
#endif
