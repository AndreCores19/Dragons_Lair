
#ifndef DRAGONS_LAIR_OBJECT_H
#define DRAGONS_LAIR_OBJECT_H
#include "Entity.h"

class Character;
class Object : public Entity {
protected:
    int value;
public:
    Object(string, int);
    virtual ~Object();
    int getValue() const;
    virtual void use(Character*) = 0;
};

#endif //DRAGONS_LAIR_OBJECT_H