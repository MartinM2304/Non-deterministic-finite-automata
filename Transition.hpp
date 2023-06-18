#ifndef NDFA04_TRANSITION_HPP
#define NDFA04_TRANSITION_HPP
#include <iostream>
struct Transition{
    size_t destination;
    char key;

    Transition(){
        destination=-1;
        key=' ';
    }
    Transition(size_t n, char ch){
        destination=n;
        key=ch;
    }
    void changeDest(int newDest){
        destination=newDest;
    }

};

#endif //NDFA04_TRANSITION_HPP
