//
// Created by julia on 6/6/2026.
//

#include "Object.h"

Object::Object(string name, int value)
    : Entity(name), value(value) {}

Object::~Object() {}

int Object::getValue() const {
    return value;
}


