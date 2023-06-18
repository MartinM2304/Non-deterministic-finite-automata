#include <iostream>
#include "NDFA/Automata.h"
#include "Commands/CommandFactory.h"

int main() {

    Automata aut;
    CommandFactory cf;
    Command* ct =cf.getCommand();
    ct->execute(aut);


    //Automata fsa("1*");
    //fsa.debug();
    //std::cout<<"accept-"<<fsa.accept("111")<<std::endl;
    //std::cout<<"Pray to God -------------------------"<<std::endl;
    //std::cout<<fsa.getRegularExpression();
    //fsa.makeTotal();
    //fsa.debug();
    //std::cout<<"accept-"<<fsa.accept("abb")<<std::endl;


//    fsa.debug();

//    CommandFactory createCommand(input);
//    receiver.execute(command)
    return 0;
}
