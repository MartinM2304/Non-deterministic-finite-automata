#ifndef NDFA_03_MYSET_H
#define NDFA_03_MYSET_H
#include <iostream>


template <class T>
class MySet {

    T*data;
    size_t size;
    size_t capacity;

    void copyFrom(const MySet&other){
        size=other.size;
        capacity=other.capacity;

        data=new T [capacity];
        for(int i=0;i<size;i++){
            data[i]=other.data[i];
        }
    }
    void free(){
        delete[]data;
    }
    void resize(){
        capacity*=2;

        T* temp = new T [capacity];
        for(int i=0;i<size;i++){
            temp[i]=data[i];
        }

        delete[]data;
        data=temp;
        temp= nullptr;
    }

public:
    MySet(): MySet(5){}
    MySet(size_t n){
        capacity=n;
        size=0;
        data=new T[n];
    }
    MySet(const MySet& other){
        copyFrom(other);
    }
    MySet& operator=(const MySet&other){
        if(this!=&other){
            free();
            copyFrom(other);
        }
        return *this;
    }
    ~MySet(){
        free();
    }

    T operator[](size_t n){
        return data[n];
    }
    MySet& push (T ch){
        if(size==capacity){
            resize();
        }
        for(int i=0;i<size;i++){
            if(data[i]==ch){
                return *this;
            }
        }

        data[size]=ch;
        size++;
        return *this;
    }

};


#endif //NDFA_03_MYSET_H
