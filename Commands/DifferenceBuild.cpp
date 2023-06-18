//
// Created by AZ on 18.06.2023 г..
//

#include "DifferenceBuild.h"

void DifferenceBuild::execute(Automata &aut) {
    std::cout<<"Choose parameters for the first automat"<<std::endl;
    BuildAutomata b1;
    b1.execute(lhs);
    std::cout<<"Choose parameters for the second automat"<<std::endl;
    BuildAutomata b2;
    b2.execute(rhs);

    aut= Difference(lhs,rhs);
}