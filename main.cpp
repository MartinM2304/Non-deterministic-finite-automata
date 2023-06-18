#include <iostream>
#include "Automata.h"
#include "Command.h"

int main() {


    Automata fsa("ab");
    fsa.debug();
    std::cout<<"accept-"<<fsa.accept("abb")<<std::endl;
    std::cout<<"Pray to God -------------------------"<<std::endl;
    //std::cout<<fsa.getRegularExpression();
    fsa.makeDeterminized();
    fsa.debug();
    std::cout<<"accept-"<<fsa.accept("ab")<<std::endl;


//    fsa.debug();

//    CommandFactory createCommand(input);
//    receiver.execute(command)
    return 0;
}
