#ifndef NDFA04_LOADFROMFILE_H
#define NDFA04_LOADFROMFILE_H
#include "Command.h"

class LoadFromFile:public Command {
    MyString name;
public:
    LoadFromFile(const MyString& name);
    void execute(Automata& aut)const override;
};


#endif //NDFA04_LOADFROMFILE_H
