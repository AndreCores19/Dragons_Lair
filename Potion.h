#ifndef DRAGONS_LAIR_POTION_H
#define DRAGONS_LAIR_POTION_H
#include "Object.h"

class Potion : public Object {
private:
    double healAmount;
public:
    Potion(string, int, double);
    ~Potion();
    double getHealAmount() const;
    void use(Character*) override;
    void describe() const override;
};



#endif //DRAGONS_LAIR_POTION_H
