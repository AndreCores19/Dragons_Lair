#ifndef DRAGONS_LAIR_ICEDRAGON_H
#define DRAGONS_LAIR_ICEDRAGON_H
#include "Dragon.h"

class IceDragon : public Dragon {
private:
    double temperature;
public:
    IceDragon(string, double, int, int, string, double);
    ~IceDragon() override;
    double calculateDamage() const override;
    void specialAbility(Character*) override;
    void describe() const override;
};

#endif //DRAGONS_LAIR_ICEDRAGON_H