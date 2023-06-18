#include "CommandFactory.h"
#include "BuildAutomata.h"
#include "../NDFA/Automata.h"
#include "LoadFromFile.h"

Command *CommandFactory::getCommand() const {


//    std::cout << "Choose one of the following: " << std::endl;
//    std::cout<< " 0 for exit "<<std::endl<<" 1 for Creating Automata"<<std::endl
//    <<" 2 for loading automata from file"<<std::endl;
//    int n;
//    MyString input;
//    std::cin>>n;
//    switch (n) {
//        case 0:
//            break;
//        case 1:
//            std::cout<<"Enter a regex for your automata "<<std::endl;
//            std::cin>>input;
//            return new BuildAutomata(input);
//            break;
//        case 2:
//            std::cout<<"Enter the name of the file you want to load "<<std::endl;
//            std::cin>>input;
//            return new LoadFromFile(input);
//            break;
//        default:
//            break;
//
//    }
    return new BuildAutomata();

}