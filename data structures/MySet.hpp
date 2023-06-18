#ifndef NDFA_03_MYSET_H
#define NDFA_03_MYSET_H
#include <iostream>
#define TP template<typename T>

template <class T>
class MySet {

    T*data;
    size_t size;
    size_t capacity;


    void copyFrom(const MySet&other);
    void free();
    void resize();

public:
    MySet();
    MySet(size_t n);
    MySet(const MySet& other);
    MySet& operator=(const MySet&other);
    ~MySet();

    bool contains(const T&)const;
    T& operator[](size_t n);
    const T& operator[](size_t n )const;
    MySet& push (T ch);
    void clear();

    size_t getSize()const;
};

TP
MySet<T> Intersection(const MySet<T>&lhs,const MySet<T>&rhs){
    MySet<T> result;

    if(lhs.getSize()>rhs.getSize()) {

        for (int i = 0; i < rhs.getSize(); i++) {
            if (lhs.contains(rhs[i])) {
                result.push(rhs[i]);
            }
        }
    }else{
        for (int i = 0; i < lhs.getSize(); i++) {
            if (rhs.contains(lhs[i])) {
                result.push(lhs[i]);
            }
        }
    }

    return result;
}
TP
bool operator==(const MySet<T>&lhs, const MySet<T>& rhs){
    if(lhs.getSize()!=rhs.getSize()){
        return false;
    }
    for(int i=0;i<lhs.getSize();i++){
        if(lhs[i]!=rhs[i]){
            return false;
        }
    }
    return true;
}
TP
void MySet<T>::copyFrom(const MySet&other){
    size=other.size;
    capacity=other.capacity;

    data=new T [capacity];
    for(int i=0;i<other.size;i++){
        data[i]=other.data[i];
    }
}

TP
void MySet<T>::free() {
    size=0;
    capacity=0;
    delete[]data;
}

TP
void MySet<T>::resize(){
    capacity*=2;

    T* temp = new T [capacity];
    for(int i=0;i<size;i++){
        temp[i]=data[i];
    }

    delete[]data;
    data=temp;
    temp= nullptr;
}

TP
MySet<T>::MySet():MySet(5) {
}

TP
MySet<T>::MySet(size_t n) {
    capacity=n;
    size=0;
    data=new T[n];
}

TP
MySet<T>::MySet(const MySet<T> &other) {
    copyFrom(other);
}

TP
MySet<T> &MySet<T>::operator=(const MySet<T> &other) {
    if(this!=&other){
        free();
        copyFrom(other);
    }
    return *this;
}


TP
bool MySet<T>:: contains(const T&el)const{
    for(int i=0;i<size;i++){
        if(data[i]==el){
            return true;
        }
    }
    return false;
}

TP
T& MySet<T>::operator[](size_t n) {
    return data[n];
}



TP
const T &MySet<T>::operator[](size_t n) const {
    return data[n];
}

TP
size_t MySet<T>::getSize() const {
    return size;
}


TP
MySet<T> &MySet<T>::push(T ch) {
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

TP
void MySet<T>::clear() {
    free();
    capacity=5;
    data=new T[capacity];
}

TP
MySet<T>::~MySet(){
    free();
}

TP
MySet<T> operator+(const MySet<T>&lhs,const MySet<T>&rhs){
    MySet<T> result;
    for(int i=0;i<lhs.getSize();i++){
        result.push(lhs[i]);
    }
    for(int i=0;i<rhs.getSize();i++){
        result.push(rhs[i]);
    }
    return result;
}





#endif //NDFA_03_MYSET_H
