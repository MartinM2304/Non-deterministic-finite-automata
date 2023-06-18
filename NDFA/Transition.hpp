#ifndef NDFA04_TRANSITION_HPP
#define NDFA04_TRANSITION_HPP
#include <iostream>
#include <fstream>
struct Transition{
    int destination;
    char key;

    Transition(){
        destination=-1;
        key=' ';
    }
    Transition(size_t n, char ch){
        destination=n;
        key=ch;
    }
    void changeDest(int newDest){
        destination=newDest;
    }

    void readFromFile(std::ifstream& ifs) {
        ifs.read((char*)&destination, sizeof(destination));
        ifs.read((char*)& key, sizeof(key));
    }
    void writeToFile(std::ofstream& ofs)const {
        ofs.write((const char*)&destination,sizeof (destination));
        ofs.write((const char*) &key, sizeof(key));
    }

};

#endif //NDFA04_TRANSITION_HPP
