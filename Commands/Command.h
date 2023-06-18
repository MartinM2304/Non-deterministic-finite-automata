#ifndef NDFA04_COMMAND_H
#define NDFA04_COMMAND_H
#include "../NDFA/Automata.h"

class Command{
public:
    virtual ~Command()=default;
    virtual void execute(Automata&aut)=0;
};




#endif //NDFA04_COMMAND_H
