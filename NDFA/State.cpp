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

bool State::hasTransition(int start, int end) const {
    for(int i=0;i<getCountOfTransitions();i++){
        if(transitionsFromState[i].destination==end){
            return true;
        }
    }
    return false;
}

void State::writeToFile(std::ofstream &ofs)const {
    ofs.write((const char*)transitionsFromState.getSize(), sizeof(size_t));
    for(int i=0;i<transitionsFromState.getSize();i++){
        transitionsFromState[i].writeToFile(ofs);
    }
}

void State::readFromFile(std::ifstream &ifs) {
    size_t size;
    ifs.read((char*)&size, sizeof(size));
    for(int i=0;i<size;i++){
        Transition temp;
        temp.readFromFile(ifs);
        transitionsFromState.push(temp);
    }
}