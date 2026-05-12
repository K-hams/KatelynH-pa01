// card_list.cpp
// Author: Katelyn Hamel
// Implementation of the classes defined in card_list.h

//ALL IMPLEMENTS FOR HAND
#include "card_list.h"
using namespace std;

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
        tail = newC;
    } else {
        tail->setNext(newC);
        tail = newC;
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






