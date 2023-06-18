#include "ConcatAutomats.h"



void ConcatAutomats::execute(Automata &aut) {
    std::cout<<"Choose parameters for the first automat"<<std::endl;
    BuildAutomata b1;
    b1.execute(lhs);
    std::cout<<"Choose parameters for the second automat"<<std::endl;
    BuildAutomata b2;
    b2.execute(rhs);

    aut= Concat(lhs,rhs);
}