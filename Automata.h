#ifndef NDFA04_AUTOMATA_H
#define NDFA04_AUTOMATA_H
#include "Transition.hpp"
#include "State.h"
#include "MyVector.hpp"
#include "MySet.hpp"
#include "MyString.h"


class Automata {
    size_t startState=0;
    MySet<char> alphabet;
    MySet<int > finalStates;
    // every state is unique and set guarantees that there are not going to be duplicates
    //they are ints for error catching (negative values)
    MyVector<State> states;
    //All states in the automata, every state has its own array of transitions;

    bool isMinimal= false;
    bool isTotal= false;
    bool isDeterminised= false;


public:
    Automata();
    Automata(size_t statesCount);
    Automata(const MyString& str);

    //build your own
    Automata& addTransition(size_t from, size_t dest,char key);
    Automata& addState();
    Automata& addLetter(char ch);
    Automata build(const MyString& str);

    void makeTotal();
    void makeDeterminized();
    void makeMinimal();

    MyString getRegularExpression()const;


    friend Automata U(const Automata& lhs, const Automata& rhs);
    friend Automata operator/(const Automata& lhs, const Automata& rhs);
    friend Automata operator*(const Automata& souce);

};

Automata Union(const Automata& lhs, const Automata& rhs);
Automata operator/(const Automata& lhs, const Automata& rhs);
Automata operator*(const Automata& source);


#endif //NDFA04_AUTOMATA_H
