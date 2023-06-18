#include <iostream>
#include "NDFA/Automata.h"
#include "Commands/CommandFactory.h"
// Martin Marinkov 5MI0600202
//https://youtu.be/qZWwwcIer-U
// kompilira se na gcc -CLion
// ne sym osobeno siguren za command patterna dali trqbva da izglejda taka
// no inache funkciite rabotqt

int main() {

    Automata aut;
    CommandFactory cf;
    Command* ct =cf.getCommand();
    ct->execute(aut);

    aut.print();


    //Automata fsa("a*");
    //std::cout<<"accept-"<<fsa.accept("aa")<<std::endl;
    //std::cout<<"Pray to God -------------------------"<<std::endl;
    //std::cout<<fsa.getRegularExpression();
    //fsa.makeTotal();
    //fsa.print();
    //std::cout<<"accept-"<<fsa.accept("abb")<<std::endl;
//    fsa.print();

    return 0;
}
