#ifndef NDFA_03_MYVECTOR_HPP
#define NDFA_03_MYVECTOR_HPP
#include <iostream>

template <typename T>
class MyVector {
    T*data;
    size_t size;
    size_t capacity;

    void free();
    void copyFrom(const MyVector&other);
    void moveFrom(MyVector&&other);
    void resize();
public:

    MyVector();
    MyVector(size_t n);
    MyVector(const MyVector&other);
    MyVector& operator=(const MyVector&other);

    MyVector(MyVector&&other);
    MyVector& operator=(MyVector&&other);
    ~MyVector();

    MyVector& push(const T& element);
    MyVector& remove(const T& element);
    MyVector& remove(size_t ind);
    MyVector& popBack();
    const T& peek(size_t ind)const;
    const T& back()const;
    int find(const T& element)const;
    bool contains(const T& element)const;
    size_t getSize()const;
    size_t getCapacity()const;
    bool isEmpty()const;
    T& operator[](size_t n);
    const T& operator[](size_t n)const;
    MyVector& operator+=(const MyVector& rhs);
};

template <typename T>
MyVector<T> &MyVector<T>::push(const T &element) {
    if(size>=capacity){
        resize();
    }
    data[size]=element;
    size++;

    return *this;
}

template <typename T>
MyVector<T> &MyVector<T>::remove(const T &element) {
    if(isEmpty()){
        return *this;
    }
    for(int i=0;i<size;i++){
        if(data[i]==element){
            for(int j=i;j<size-1;j++){
                data[j]=data[j+1];
            }
            size--;
            break;
        }
    }
    return *this;
}

template <typename T>
MyVector<T> &MyVector<T>::remove(size_t ind) {
    if (isEmpty())
        return *this;

    if(ind >size){
        throw std::runtime_error("Invalid index");
    }

    for(int i=ind;i<size-1;i++){
        data[i]=data[i+1];
    }
    size--;
    return *this;
}

template <typename T>
MyVector<T> &MyVector<T>::popBack() {
    return remove(size-1);;
}

template <typename T>
const T &MyVector<T>::peek(size_t ind) const {
    if(ind<size){
        return data[ind];
    }else{
        throw std::runtime_error("Enter correct index");
    }
}

template <typename T>
const T &MyVector<T>::back() const {
    if(isEmpty()){

    }
    return data[size-1];
}
template <typename T>
int MyVector<T>::find(const T &element) const {
    for(int i=0;i<size;i++){
        if(data[i]==element){
            return i;
        }
    }
    return -1;
}
template <typename T>
size_t MyVector<T>::getSize() const {
    return size;
}

template <typename T>
size_t MyVector<T>::getCapacity() const {
    return capacity;
}

template <typename T>
bool MyVector<T>::isEmpty() const {
    return (getSize()==0);
}

template <typename T>
T &MyVector<T>::operator[](size_t n) {
    return data[n];
}

template <typename T>
const T &MyVector<T>::operator[](size_t n) const {
    return data[n];
}

template <typename T>
MyVector<T> &MyVector<T>::operator+=(const MyVector<T> &rhs) {
    size_t newSize = rhs.size+size;
    T*temp = new T[newSize];

    for(int i=0;i<size;i++){
        temp[i]=data[i];
    }
    for(int i=size,j=0;i<newSize;i++,j++){
        temp[i]=rhs.data[j];
    }
    size=newSize;
    capacity=newSize;

    delete[]data;
    data=temp;
    temp= nullptr;

    return *this;
}
template <typename T>
bool MyVector<T>::contains(const T &element)const {
    for(int i=0;i<size;i++){
        if(data[i]==element){
            return true;
        }
    }
    return false;
}

template <typename T>
MyVector<T>::MyVector(): MyVector(1){}

template <typename T>
MyVector<T>::MyVector(size_t n) {
    data=new T[n];
    size=0;
    capacity=n;
}

template <typename T>
void MyVector<T>::copyFrom(const MyVector<T> &other) {
    size=other.size;
    capacity=other.capacity;
    data= new T[capacity];
    for(int i=0;i<size;i++){
        data[i]=other.data[i];
    }
}

template <typename T>
void MyVector<T>::free() {
    delete[] data;
    data= nullptr;
    size=0;
    capacity=0;
}

template <typename T>
void MyVector<T>::moveFrom(MyVector<T> &&other) {
    data=other.data;
    other.data= nullptr;
    size=other.size;
    capacity=other.capacity;
}

template <typename T>
MyVector<T>::MyVector(const MyVector<T> &other) {
    copyFrom(other);
}

template <typename T>
MyVector<T> &MyVector<T>::operator=(const MyVector<T> &other) {
    if(this!=&other){
        free();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
MyVector<T>::MyVector(MyVector<T> &&other) {
    moveFrom(std::move(other));
}

template <typename T>
MyVector<T> &MyVector<T>::operator=(MyVector<T> &&other) {
    if(this!=&other){
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

template <typename T>
void MyVector<T>::resize() {
    capacity*=2;

    T*temp = new T[capacity];
    for(int i=0;i<size;i++){
        temp[i]=data[i];
    }
    delete[]data;
    data=temp;
    temp= nullptr;
}

template <typename T>
MyVector<T>::~MyVector() {
    //std::cout<<1;
    free();
}

#endif //NDFA_03_MYVECTOR_HPP
