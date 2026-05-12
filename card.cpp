// card.cpp
// Author: Katelyn Hamel
// Implementation of the classes defined in card.h
#include "card.h"





bool card::operator<(const card& other) const {
    if (suit != other.suit) return suit < other.suit;
    return value < other.value;
}

bool card::operator>(const card& other) const {
    return other < *this;
}

bool card::operator==(const card& other) const {
    return (suit == other.suit && value == other.value);
}

std::ostream& operator<<(std::ostream& os, const card& c) {
    std::string valStr;
    if (c.value == 1) valStr = "a";
    else if (c.value == 11) valStr = "j";
    else if (c.value == 12) valStr = "q";
    else if (c.value == 13) valStr = "k";
    else valStr = std::to_string(c.value);

    os << c.suit << " " << valStr;
    return os;
}

/*
char card::getName() const{
    return name;
}


string card::getValue() const{
    return value;
}


card* card::getNext()const{
    return nextCard;
}
void card::setNext(card* next){
    nextCard = next;
}


//overloaded operators
//if cards equal




bool card::operator==(const card& other) const {
    return (value == other.value && name == other.name);
   
}
std::ostream& operator<<(std::ostream& os, const card& c) {
    os << c.getName() << " " << c.getValue();
    return os;
}
    */










