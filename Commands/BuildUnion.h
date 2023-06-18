#ifndef NDFA04_BUILDUNION_H
#define NDFA04_BUILDUNION_H
#include "Command.h"
#include "BuildAutomata.h"

class BuildUnion:public Command {
    Automata lhs;
    Automata rhs;
public:
    void  execute(Automata& aut) override;
};



#endif //NDFA04_BUILDUNION_H
