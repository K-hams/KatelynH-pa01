// card.h
// Author: Katelyn Hamel
// All class declarations related to defining a single card go here


#ifndef CARD_H
#define CARD_H


#include <iostream>
using namespace std;
//node aka card
class card {
public:
    card *left, *right;
    char suit;
    int value; 
    card() : left(nullptr), right(nullptr), suit(' '), value(0){}
    card(char s, int v) : left(nullptr), right(nullptr), suit(s), value(v){}

    char getSuit() const { return suit; }
    int getValue() const { return value; }

    // BST Overloads
    bool operator<(const card& other) const;
    bool operator>(const card& other) const;
    bool operator==(const card& other) const;

    friend std::ostream& operator<<(std::ostream& os, const card& c);

    

private:
    
    
};
/*
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
*/














//
#endif
