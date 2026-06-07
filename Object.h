
#ifndef DRAGONS_LAIR_OBJECT_H
#define DRAGONS_LAIR_OBJECT_H
#include "Entity.h"

class Character;
class Object : public Entity {
protected:
    int value;
    double weight;
public:
    Object(string, int, double);
    virtual ~Object();
    int getValue() const;
    double getWeight() const;
    virtual void use(Character*) = 0;
};

#endif //DRAGONS_LAIR_OBJECT_H