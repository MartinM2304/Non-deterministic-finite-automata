#include "KleeneStarAutomat.h"


void KleeneStarAutomat::execute(Automata &aut) {
    aut= KleeneStar(aut);
}