//
// Created by andre on 3/6/2026.
//

#ifndef DRAGONS_LAIR_LIST_H
#define DRAGONS_LAIR_LIST_H
#include <iostream>
using namespace std;
template <typename T>
class List {
    T* data;
    int size;
    int capacity;
public:
    List();
    ~List();
    List(const List& other);           // constructor de copia
    List& operator=(const List& other); // operador de asignación
    void push_back(const T& value);
    void pop_back();
    T& at(int index);
    const T& at(int index) const;
    T* begin();
    T* end();
    int getSize() const;
    int getCapacity() const;
};


#endif //DRAGONS_LAIR_LIST_H