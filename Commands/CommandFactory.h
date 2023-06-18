#ifndef NDFA04_COMMANDFACTORY_H
#define NDFA04_COMMANDFACTORY_H
#include "Command.h"

class CommandFactory {
public:
    CommandFactory()=default;
CommandFactory(const CommandFactory&other)=delete;
    CommandFactory& operator=(const CommandFactory&other)=delete;

    Command* getCommand()const;
    //static CommandFactory& getInstance();

};


#endif //NDFA04_COMMANDFACTORY_H
