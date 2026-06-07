//
// Created by andre on 3/6/2026.
//

#include "List.h"

template <typename T>
List<T>::List() {
    data = nullptr;
    size = 0;
    capacity = 0;
}

template <typename T>
List<T>::~List() {
    delete[] data;
}

template <typename T>
List<T>::List(const List& other) {
    size = other.size;
    capacity = other.capacity;
    data = new T[capacity];
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
}

template <typename T>
List<T>& List<T>::operator=(const List& other) {
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

template <typename T>
void List<T>::push_back(const T& value) {
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

template <typename T>
void List<T>::pop_back() {
    if (size > 0) {
        size--;
    }
}

template <typename T>
T& List<T>::at(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}

template <typename T>
const T& List<T>::at(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}

template <typename T>
T* List<T>::begin() {
    return data;
}

template <typename T>
T* List<T>::end() {
    return data + size;
}

template <typename T>
int List<T>::getSize() const {
    return size;
}

template <typename T>
int List<T>::getCapacity() const {
    return capacity;
}