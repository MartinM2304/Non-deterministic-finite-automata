#include "BuildAutomata.h"



void BuildAutomata::execute(Automata&aut) {
    std::cout<<"Choose 1 to build automata from regex"<<std::endl<<
    "Choose 2 to load from file"<<std::endl<<
    "Or anythig else in order not to change the automat"<<std::endl;
    int n;
    std::cin>>n;
    if(n==1) {
        MyString input;
        std::cout<<"Enter the regex"<<std::endl;
        std::cin>>input;
        aut = aut.build(input);
        std::cout<<"Done :0"<<std::endl;
    }else if(n==2){
        MyString input;
        std::cout<<"Enter the name of the file";
        std::cin>>input;
        aut.readFromFile(input);
        std::cout<<"Done :0"<<std::endl;
    }

    std::cout<<"enter 0 for exit"<<std::endl<<
    "enter 1 for determinization"<<std::endl<<
    "enter 2 for minimization"<<std::endl<<
    "enter 3 for totalization"<<std::endl<<
    "enter 4 for checking if word is accepted by the NDFA"<<std::endl<<
    "enter 5 for checking if the language of the NDFA is empty"<<std::endl<<
    "enter 6 for print of the automata"<<std::endl;
    while (n!=0){
        std::cin>>n;
        if(n==1){
            aut.makeDeterminized();
            std::cout<<"Done :0"<<std::endl;
        }else if(n==2){
            aut.makeMinimal();
            std::cout<<"Done :0"<<std::endl;
        }else if(n==3){
            aut.makeTotal();
            std::cout<<"Done :0"<<std::endl;
        }else if(n==4){
            MyString input;
            std::cout<<"Enter the word you want to check"<<std::endl;
            std::cin>>input;
            if(aut.accept(input)){
                std::cout<<"Yes :) the NDFA accepts your word"<<std::endl;
            }else{
                std::cout<<"No :( the NDFA doesnt accept your word"<<std::endl;
            }
        }else if(n==5){
            aut.isEmptyLanguage();
            std::cout<<"Done :0"<<std::endl;
        }else if(n==6){
            aut.print();
        }else if(n>6|| n<0){
            std::cout<<"Enter valid number"<<std::endl;
        }
    }
    std::cout<<"Thank you for using Automata - by Tedi Aleksandrova"<<std::endl;
}