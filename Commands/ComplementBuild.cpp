#include "ComplementBuild.h"


void ComplementBuild::execute(Automata &aut) {
    aut= Complement(aut);
}