#include "LoadFromFile.h"

LoadFromFile::LoadFromFile(const MyString &name) {
    this->name=name;
}

void LoadFromFile::execute(Automata &aut)  {
    aut.readFromFile(name);
}