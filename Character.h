#ifndef DRAGONS_LAIR_CHARACTER_H
#define DRAGONS_LAIR_CHARACTER_H
#include "Entity.h"
//hola
class Character : public Entity {
protected:
    double life;
    int maxLife;
    int level;
public:
    Character(string, double, int, int);
    virtual ~Character();
    double getLife() const;
    int getMaxLife() const;
    int getLevel() const;
    void attack(Character*);
    void takeDamage(double);
    virtual double calculateDamage() const = 0;
    bool operator>(const Character&) const;
    bool isAlive() const;
};


#endif //DRAGONS_LAIR_CHARACTER_H