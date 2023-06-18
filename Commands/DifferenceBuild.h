#ifndef NDFA04_DIFFERENCEBUILD_H
#define NDFA04_DIFFERENCEBUILD_H
#include "Command.h"
#include "BuildAutomata.h"

class DifferenceBuild: public Command{
    Automata lhs;
    Automata rhs;
public:
    void execute(Automata& aut)override;
};



#endif //NDFA04_DIFFERENCEBUILD_H
