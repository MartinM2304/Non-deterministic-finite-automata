#ifndef NDFA04_AUTOMATA_H
#define NDFA04_AUTOMATA_H
#include "State.h"
#include "../data structures/MySet.hpp"
#include "../data structures/String.h"
#include "../data structures/MyQueue.hpp"
//https://youtu.be/qZWwwcIer-U

class Automata {
    size_t startState;
    MySet<char> alphabet;
    MySet<int > finalStates;
    // every final state is unique and set guarantees that there are not going to be duplicates
    MyVector<State> states;

public:
    Automata();
    Automata(size_t statesCount);
    Automata(const MyString& str);

    //build your own
    Automata& addTransition(size_t from, size_t dest,char key);
    Automata& addState();
    Automata& addLetter(char ch);
    Automata& makeLastStateStarting();
    void makeStateFinal(size_t ind);
    bool isReachable(int state)const;

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
    bool isEmptyLanguage()const;
    bool hasPathFromStartingToFinal(int currentState, MySet<int> visitedStaes)const;

    void changeStartingState(size_t n);
    void makeToOneAutomata(const Automata&other);
    void reverse();

    void makeTotal();
    void makeDeterminized();
    void makeMinimal();

    void print()const;

    MyString getRegularExpression()const;
    MyString getRegularExpression(int start, int end, int bound,bool epsilon )const;


    void readFromFile(const MyString& name);
    void writeToFile(const MyString&name)const;
    friend Automata Union(const Automata& lhs, const Automata& rhs);
    friend Automata Concat(const Automata& lhs, const Automata& rhs);
    friend Automata KleeneStar(const Automata& souce);
    friend Automata Intersect(const Automata&lhs, const Automata& rhs);
    friend Automata Complement(const Automata& source);

private:
    MySet<int> startingStates;
    bool makingMinimal= false;
    bool isStartFinal = false;
};

Automata Complement(const Automata& source);
Automata Intersect(const Automata&lhs, const Automata& rhs);
Automata Difference(const Automata& lhs,const Automata&rhs);
Automata Union(const Automata& lhs, const Automata& rhs);
Automata Concat(const Automata& lhs, const Automata& rhs);
Automata KleeneStar(const Automata& source);


#endif //NDFA04_AUTOMATA_H
