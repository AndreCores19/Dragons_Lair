

#include "Entity.h"
//hola
Entity::Entity(string name) : name(name) {}

Entity::~Entity(){}

string Entity::getName() const {
    return name;
}


