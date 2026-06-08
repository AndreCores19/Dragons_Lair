#ifndef DRAGONS_LAIR_CHARACTER_H
#define DRAGONS_LAIR_CHARACTER_H
#include "Entity.h"

class Character : public Entity {
protected:
    double life;
    int maxLife;
    int level;
    double defense;
public:
    Character(string, double, int, int);
    virtual ~Character();
    double getLife() const;
    int getMaxLife() const;
    int getLevel() const;
    void setDefense(double);
    void attack(Character*);
    void takeDamage(double);
    virtual double calculateDamage() const = 0;
    bool operator>(const Character&) const;
    bool isAlive() const;
    void setLife(double);
};


#endif //DRAGONS_LAIR_CHARACTER_H