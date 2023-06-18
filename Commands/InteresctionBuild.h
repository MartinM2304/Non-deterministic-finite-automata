#ifndef NDFA04_INTERESCTIONBUILD_H
#define NDFA04_INTERESCTIONBUILD_H
#include "Command.h"
#include "BuildAutomata.h"

class InteresctionBuild: public Command{
    Automata lhs;
    Automata rhs;
public:
    void execute(Automata& aut)override;
};


#endif //NDFA04_INTERESCTIONBUILD_H
