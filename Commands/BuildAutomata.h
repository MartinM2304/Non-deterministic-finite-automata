#ifndef NDFA04_BUILDAUTOMATA_H
#define NDFA04_BUILDAUTOMATA_H
#include "Command.h"

class BuildAutomata: public Command{
public:
    BuildAutomata()=default;
    BuildAutomata(const BuildAutomata&other)=delete;
    BuildAutomata& operator = (const BuildAutomata&other)=delete;

    void execute(Automata& ndfa) override;
};

#endif //NDFA04_BUILDAUTOMATA_H
