#ifndef NDFA04_COMMAND_H
#define NDFA04_COMMAND_H
#include "Automata.h"

class Command{
public:
    virtual ~Command();
    virtual void execute()=0;
};

class addTransitionCommand:public Command{
private:
    Automata* aut;
    size_t from;
    size_t dest;
    char key;
public:
    addTransitionCommand(Automata* automata,size_t begin, size_t destiantion, char key):
    aut(automata),from(begin),dest(destiantion),key(key){}

    void execute() override{
        aut->addTransition(from,dest,key);
    }
};
#endif //NDFA04_COMMAND_H
