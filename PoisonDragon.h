#ifndef DRAGONS_LAIR_POISONDRAGON_H
#define DRAGONS_LAIR_POISONDRAGON_H
#include "Dragon.h"

class PoisonDragon : public Dragon {
private:
    double toxicity;
    double poisonStacks;
public:
    PoisonDragon(string, double, int, int, string, double);
    ~PoisonDragon();
    double calculateDamage() const override;
    void specialAbility(Character*) override;
    void describe() const override;
    double getToxicity() const;
};


#endif //DRAGONS_LAIR_POISONDRAGON_H