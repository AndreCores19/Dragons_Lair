//
// Created by andre on 3/6/2026.
//

#ifndef DRAGONS_LAIR_LIST_H
#define DRAGONS_LAIR_LIST_H
#include <iostream>
#include "OutOfRangeError.h"
using namespace std;
template <typename T>
class List {
    T* data;
    int size;
    int capacity;
public:
    List() {
        data = nullptr;
        size = 0;
        capacity = 0;
    }

    ~List() {
        delete[] data;
    }

    List(const List& other) {
        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    List<T>&operator=(const List& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new T[capacity];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    void push_back(const T& value) {
        if (size == capacity) {
            capacity = (capacity == 0) ? 1 : capacity * 2;
            T* newData = new T[capacity];
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[size++] = value;
    }

    void pop_back() {
        if (size > 0) {
            size--;
        }
    }

    void removeAt(int index) {
        if (index < 0 || index >= size)
            throw OutOfRangeError(index, size);

        for (int i = index; i < size - 1; i++)
            data[i] = data[i + 1];

        size--;
    }

    T& at(int index) {
        if (index < 0 || index >= size)
            throw OutOfRangeError(index, size);
        return data[index];
    }

    const T& at(int index) const {
        if (index < 0 || index >= size)
            throw OutOfRangeError(index, size);
        return data[index];
    }

    T* begin() {
        return data;
    }

    T* end() {
        return data + size;
    }

    int getSize() const {
        return size;
    }

    int getCapacity() const {
        return capacity;
    }
};



#endif //DRAGONS_LAIR_LIST_H
