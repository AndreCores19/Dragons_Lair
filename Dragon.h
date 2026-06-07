

#ifndef DRAGONS_LAIR_DRAGON_H
#define DRAGONS_LAIR_DRAGON_H
#include "Character.h"
//hola
class Dragon : public Character {
protected:
    string region;
public:
    Dragon(string, double, int, int, string);
    virtual ~Dragon();
    string getRegion() const;
    virtual double calculateDamage() const = 0;
    virtual void specialAbility(Character*) = 0;
    void describe() const override;
};

#endif //DRAGONS_LAIR_DRAGON_H