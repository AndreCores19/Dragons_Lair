
#ifndef DRAGONS_LAIR_HYDRADRAGON_H
#define DRAGONS_LAIR_HYDRADRAGON_H
#include "Dragon.h"

class HydraDragon : public Dragon {
private:
    int heads;
    int maxHeads;
public:
    HydraDragon(string, double, int, int, string, int);
    ~HydraDragon() override;
    double calculateDamage() const override;
    void specialAbility(Character*) override;
    void describe() const override;
    int getHeads() const;
};


#endif //DRAGONS_LAIR_HYDRADRAGON_H