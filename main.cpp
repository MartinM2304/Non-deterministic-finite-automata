#include <iostream>
#include "Automata.h"
#include "Command.h"

int main() {


    Automata fsa("a*bc");
    std::cout<<fsa.isDeterminized()<<std::endl;
    fsa.debug();
    std::cout<<"Pray to God -------------------------"<<std::endl;
    fsa.makeDeterminized();
    std::cout<<fsa.isDeterminized();
    //fsa.makeMinimal();
    //fsa.debug();

//    fsa.debug();

//    CommandFactory createCommand(input);
//    receiver.execute(command)
    return 0;
}
