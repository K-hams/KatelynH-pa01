// card.h
// Author: Katelyn Hamel
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H

#include <iostream>

//node aka card
class card{
    public:
        //default constructor
        card(): value('0'), name('a'), nextCard(nullptr){}
        //card with values
        card(char val, char n): value(val), name(n), nextCard(nullptr){}

        //funcs
        char getName() const;
        char getValue() const;
        card* getNext() const;
        void setNext(card* next);



      

        //overloaded operators
        //if equal
        bool operator==(const card& other) const;

        //printing
        friend std::ostream& operator<<(std::ostream& os, const card& c);

    private:
        char value;
        char name; 
        card* nextCard;
       


};







//
#endif
