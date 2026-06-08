#ifndef DRAGONS_LAIR_WEAPON_H
#define DRAGONS_LAIR_WEAPON_H
#include "Object.h"

class Weapon :public Object {
private:
    bool equipped;
    double damage;
public:
    Weapon(string, int, double);
    ~Weapon();
    double getDamage() const;
    bool isEquipped() const;
    void use(Character*) override;
    void describe() const override;
};


#endif //DRAGONS_LAIR_WEAPON_H