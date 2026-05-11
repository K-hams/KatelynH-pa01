// card.cpp
// Author: Katelyn Hamel
// Implementation of the classes defined in card.h
#include "card.h"



char card::getName() const{
    return name;
}

char card::getValue() const{
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





