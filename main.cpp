#include <iostream>
#include "Automata.h"
#include "Command.h"

int main() {


    Automata fsa("(a+b)*");
    fsa.debug();
    std::cout<<"accept-"<<fsa.accept("aa")<<std::endl;
    std::cout<<"Pray to God -------------------------"<<std::endl;
//    fsa.getRegularExpression();


//    fsa.debug();

//    CommandFactory createCommand(input);
//    receiver.execute(command)
    return 0;
}
