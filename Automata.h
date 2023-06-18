#ifndef NDFA04_AUTOMATA_H
#define NDFA04_AUTOMATA_H
#include "State.h"
#include "MySet.hpp"
#include "String.h"
#include "MyQueue.h"
//https://youtu.be/qZWwwcIer-U

class Automata {
    size_t startState;
    MySet<char> alphabet;
    MySet<int > finalStates;
    // every final state is unique and set guarantees that there are not going to be duplicates
    //they are ints for error catching (negative values)
    MyVector<State> states;
    //All states in the auto0mata, every state has its own array of transitions;

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
    Automata& makeLastStateStarting();
    //void makeState();
    void makeStateFinal(size_t ind);

    Automata build(const MyString& str)const;
    Automata buildSmallAutomata(char ch)const;
    void copyTransitions(int lhs,int rhs);

    MySet<int> getTransitions(int start, char ch)const;
    bool reachableStates(int start,const MyString&str)const;
    bool accept(const MyString& str)const;
    bool isStateFromstarting(const State& st);
    bool isFinal(int n)const;
    bool isDeterminized()const;
    bool isStateValid(size_t n)const;

    void changeStartingState(size_t n);
    void makeToOneAutomata(const Automata&other);
    void reverse();

    void makeTotal();
    void makeDeterminized();
    void makeMinimal();

    void debug()const;

    MyString getRegularExpression()const;
    MyString getRegularExpression(int start, int end, int bound,bool epsilon )const;

    friend Automata Union(const Automata& lhs, const Automata& rhs);
    friend Automata Concat(const Automata& lhs, const Automata& rhs);
    friend Automata KleeneStar(const Automata& souce);
    friend Automata Intersect(const Automata&lhs, const Automata& rhs);
    friend Automata Complement(const Automata& source);

private:
    MySet<int> startingStates;
    bool isStartingFinal= false;

};

Automata Complement(const Automata& source);
Automata Intersect(const Automata&lhs, const Automata& rhs);
Automata Union(const Automata& lhs, const Automata& rhs);
Automata Concat(const Automata& lhs, const Automata& rhs);
Automata KleeneStar(const Automata& source);


#endif //NDFA04_AUTOMATA_H
