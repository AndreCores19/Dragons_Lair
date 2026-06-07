
#ifndef DRAGONS_LAIR_FIREDRAGON_H
#define DRAGONS_LAIR_FIREDRAGON_H
#include "Dragon.h"

class FireDragon : public Dragon {
private:
    double temperature;
public:
    FireDragon(string, double, int, int, string, double);
    ~FireDragon();
    double calculateDamage() const override;
    void specialAbility(Character*) override;
    void describe() const override;
};


#endif //DRAGONS_LAIR_FIREDRAGON_H