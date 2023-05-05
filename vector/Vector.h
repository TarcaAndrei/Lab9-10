//
// Created by Andrei on 09.04.2023.
//

#ifndef VECTOR_ITERATOR_VECTOR_H
#define VECTOR_ITERATOR_VECTOR_H
#include <algorithm>
#include <functional>

template <typename T> class Iterator;

template <class T>

class Vector {
    friend class Iterator<T>;
private:
    int capacitate;
    int lungime;
    T* lista;
public:
    Vector();
    Vector(const Vector &v);    //copy constructor obligatoriu
    ~Vector();
    [[nodiscard]] int size() const;
    Iterator<T> begin() const;
    int end() const;
    T remove(int pozitie);
    void push_back(T valoare);
    T find(int pozitie) const;
    T &operator[](int pozitie) const;
    Vector<T> &operator=(const Vector<T>& vector);      // si overload la =
    Iterator<T> iterator() const;
    void sort(std::function<bool(const T&, const T&)> func);
};

template<class T>
void Vector<T>::sort(std::function<bool(const T &, const T &)> func) {
    std::sort(this->lista, this->lista + this->lungime, func);
}



template<class T>
Vector<T> &Vector<T>::operator=(const Vector<T> &vector1) {
//    if(&this == &vector1)
//        return *this;
    delete[]this->lista;
    this->lungime = vector1.lungime;
    this->capacitate = vector1.capacitate;
    this->lista = new T [this->capacitate];
    for(int i = 0 ; i < vector1.lungime; i++)
        this->lista[i] = vector1.lista[i];
    return *this;
}

template<class T>
Vector<T>::Vector(const Vector &vector1) {
    this->lungime = vector1.lungime;
    this->capacitate = vector1.capacitate;
    this->lista = new T [this->capacitate];
    for(int i = 0 ; i < vector1.lungime; i++)
        this->lista[i] = vector1.lista[i];
}

template<class T>
int Vector<T>::end() const {
    return this->lungime;
}

template<class T>
Iterator<T> Vector<T>::begin() const {
    return Iterator(*this);
}

template<class T>
T& Vector<T>::operator[](int pozitie) const {
    return this->lista[pozitie];
}

template<class T>
Iterator<T> Vector<T>::iterator() const {
    return Iterator<T>(*this);
}

template<class T>
void Vector<T>::push_back(T valoare) {
    if(this->lungime >= this->capacitate){
        return;
    }
    this->lista[this->lungime] = valoare;
    this->lungime++;
}

template<class T>
T Vector<T>::find(int pozitie) const {
    T X{};
    if(pozitie < 0 or pozitie > this->lungime)
        return X;
    return this->lista[pozitie];
}

template<class T>
T Vector<T>::remove(int pozitie) {
    T X{};
    if(pozitie < 0 or pozitie > this->lungime)
        return X;
    T elem_de_return = this->lista[pozitie];
    this->lungime--;
    for(int i = pozitie; i < this->lungime; ++i){
        this->lista[i] = this->lista[i+1];
    }
    return elem_de_return;
}

template<class T>
int Vector<T>::size() const {
    return this->lungime;
}

template<class T>
Vector<T>::~Vector() {
    delete [] this->lista;
}

template<class T>
Vector<T>::Vector() {
    this->lungime = 0;
    this->capacitate = 100;
    this->lista = new T [this->capacitate];
}


#endif //VECTOR_ITERATOR_VECTOR_H
