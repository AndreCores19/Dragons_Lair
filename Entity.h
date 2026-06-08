

#ifndef DRAGONS_LAIR_ENTITY_H
#define DRAGONS_LAIR_ENTITY_H
#include <iostream>
using namespace std;
#include <string>
#include <cmath>
class Entity {
protected:
    string name;
public:
    Entity(string);
    virtual ~Entity();
    string getName() const;
    virtual void describe() const = 0;
};

#endif //DRAGONS_LAIR_ENTITY_H