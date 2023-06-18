#ifndef NDFA04_COMPLEMENTBUILD_H
#define NDFA04_COMPLEMENTBUILD_H
#include "Command.h"
#include "BuildAutomata.h"

class ComplementBuild: public Command{
public:
    void execute(Automata& aut)override;
};



#endif //NDFA04_COMPLEMENTBUILD_H
