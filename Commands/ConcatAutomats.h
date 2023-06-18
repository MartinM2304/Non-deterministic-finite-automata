#ifndef NDFA04_CONCATAUTOMATS_H
#define NDFA04_CONCATAUTOMATS_H
#include "Command.h"
#include "BuildAutomata.h"

class ConcatAutomats: public Command{
    Automata lhs;
    Automata rhs;
public:
    void execute(Automata& aut)override;
};

#endif //NDFA04_CONCATAUTOMATS_H
