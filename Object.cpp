//
// Created by julia on 6/6/2026.
//

#include "Object.h"

Object::Object(string name, int value, double weight)
    : Entity(name), value(value), weight(weight) {}
//hola
Object::~Object() {}

int Object::getValue() const {
    return value;
}
double Object::getWeight() const {
    return weight;
}

