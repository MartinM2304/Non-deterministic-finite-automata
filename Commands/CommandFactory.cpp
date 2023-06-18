#include "CommandFactory.h"
#include "BuildAutomata.h"
#include "LoadFromFile.h"
#include "BuildUnion.h"
#include "ConcatAutomats.h"
#include "KleeneStarAutomat.h"
#include "InteresctionBuild.h"
#include "ComplementBuild.h"
#include "DifferenceBuild.h"

#include "../NDFA/Automata.h"


Command *CommandFactory::getCommand() const {


    std::cout << "Choose one of the following: " << std::endl;
    std::cout<< " 0 for exit "<<std::endl<<
    " 1 for Creating Automata"<<std::endl<<
    " 2 for Union of automats"<<std::endl<<
    "3 for Concat of automats"<<std::endl<<
    "4 for Kleene star"<<std::endl<<
    "5 to get Interesection of automats"<<std::endl<<
    "6 for Complementation of automats"<<std::endl<<
    "7 for Difference between automats"<<std::endl;
    int n;
    MyString input;
    std::cin>>n;
    switch (n) {
        case 0:
            break;
        case 1:
            return new BuildAutomata();
            break;
        case 2:
            return new  BuildUnion();
            break;
        case 3:
            return new ConcatAutomats();
            break;
        case 4:
            return new KleeneStarAutomat();
            break;
        case 5:
            return new InteresctionBuild();
            break;
        case 6:
            return  new ComplementBuild();
            break;
        case 7:
            return new DifferenceBuild();
            break;
        default:
            break;

    }

}