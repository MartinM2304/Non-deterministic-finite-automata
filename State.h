#ifndef NDFA04_STATE_H
#define NDFA04_STATE_H
#include "Transition.hpp"
#include "MyVector.hpp"

struct State {
    MyVector<Transition> transitionsFromState;

    void addTransition(size_t dest, char key);
    void addTransition(const Transition& tr);
};

void State::addTransition(size_t dest, char key) {
    Transition tr(dest,key);
    transitionsFromState.push(tr);
}

void State::addTransition(const Transition &tr) {
    transitionsFromState.push(tr);
}


#endif //NDFA04_STATE_H
