#ifndef DRAGONS_LAIR_ARMOR_H
#define DRAGONS_LAIR_ARMOR_H
#include "Object.h"

class Armor : public Object {
private:
    double defense;
    bool equipped;
public:
    Armor(string, int, double);
    ~Armor();
    double getDefense() const;
    bool isEquipped() const;
    void use(Character*) override;
    void describe() const override;
};


#endif //DRAGONS_LAIR_ARMOR_H