#ifndef NDFA04_KLEENESTARAUTOMAT_H
#define NDFA04_KLEENESTARAUTOMAT_H
#include "Command.h"

class KleeneStarAutomat:public Command {
public:
    void execute(Automata& aut)override;
};



#endif //NDFA04_KLEENESTARAUTOMAT_H
