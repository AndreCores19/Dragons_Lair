

#include "Entity.h"

Entity::Entity(string name) : name(name) {}

Entity::~Entity(){}

string Entity::getName() const {
    return name;
}


