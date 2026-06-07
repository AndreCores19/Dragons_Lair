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
    List(const List&);           // constructor de copia
    List& operator=(const List&); // operador de asignación
    void push_back(const T&);
    void pop_back();
    T& at(int);
    const T& at(int) const;
    T* begin();
    T* end();
    int getSize() const;
    int getCapacity() const;
    void removeAt(int index);
};



#endif //DRAGONS_LAIR_LIST_H
