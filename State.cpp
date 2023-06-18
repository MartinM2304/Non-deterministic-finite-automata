#include "State.h"

void State::addTransition(size_t dest, char key) {
    Transition tr(dest,key);
    transitionsFromState.push(tr);
}

void State::addTransition(const Transition &tr) {
    transitionsFromState.push(tr);
}

size_t State::getCountOfTransitions() const {
    return transitionsFromState.getSize();
}

Transition &State::operator[](size_t n) {
    return transitionsFromState[n];
}

const Transition &State::operator[](size_t n) const {
    return transitionsFromState[n];
}

State &State::operator+=(const State &other) {
    transitionsFromState+=other.transitionsFromState;
    //?
    return *this;
}

bool State::hasTransition(char ch) const {
    for(int i=0;i<transitionsFromState.getSize();i++){
        if(transitionsFromState[i].key==ch){
            return true;
        }
    }
    return false;
}