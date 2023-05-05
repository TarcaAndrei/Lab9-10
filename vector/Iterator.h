//
// Created by Andrei on 10.04.2023.
//

#ifndef VECTOR_ITERATOR_ITERATOR_H
#define VECTOR_ITERATOR_ITERATOR_H

#include "Vector.h"

template<typename T>
class Iterator {
    friend class Vector<T>;
private:
    int curent;
    const Vector<T>& vector;
    Iterator(const Vector<T>& vector1);
public:
    void begin();
    int end();
    T element();
    void next();
    bool valid();
    T operator*();
    T operator->();
    //void operator=(int position);
    int position();
    bool operator<(int position);
    void operator++(int ceva);
};

template<typename T>
T Iterator<T>::operator->() {
    return nullptr;
}

template<typename T>
int Iterator<T>::end() {
    return this->vector.end();
}

template<typename T>
int Iterator<T>::position() {
    return this->curent;
}

template<typename T>
void Iterator<T>::operator++(int ceva) {
    this->next();
}

//template<typename T>
//void Iterator<T>::operator++() {
//    this->curent = this->next();
//}

template<typename T>
bool Iterator<T>::operator<(int position) {
    return this->curent < position;
}

//template<typename T>
//void Iterator<T>::operator=(int position) {
//    this->curent = position;
//}

template<typename T>
T Iterator<T>::operator*() {
    return this->element();
}

template<typename T>
bool Iterator<T>::valid() {
    if(this->curent < this->vector.lungime)
        return true;
    return false;
}

template<typename T>
void Iterator<T>::next() {
    if(this->valid()){
        this->curent++;
    }
}

template<typename T>
T Iterator<T>::element() {
    if (this->valid())
        return this->vector.lista[this->curent];
    T X{};
    return X;
}


template<typename T>
void Iterator<T>::begin() {
    this->curent = 0;
}

template<typename T>
Iterator<T>::Iterator(const Vector<T> &vector1): vector(vector1){
    this->begin();
}


#endif //VECTOR_ITERATOR_ITERATOR_H
