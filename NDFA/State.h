#ifndef NDFA04_STATE_H
#define NDFA04_STATE_H
#include "Transition.hpp"
#include "../data structures/MyVector.hpp"

struct State {
    MyVector<Transition> transitionsFromState;

    void addTransition(size_t dest, char key);
    void addTransition(const Transition& tr);
    size_t getCountOfTransitions()const;
    Transition& operator[](size_t n);
    const Transition& operator[](size_t n)const;
    bool hasTransition(char ch)const;
    bool hasTransition(int start, int end)const;

    State& operator+=(const State& other);
    void writeToFile(std::ofstream&ofs)const;
    void readFromFile(std::ifstream&ifs);
};

#endif //NDFA04_STATE_H
