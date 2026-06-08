#include "IceDragon.h"


IceDragon::IceDragon(string name, double life, int maxLife, int level, string region)
    : Dragon(name, life, maxLife, level, region), freezeLevel (200) {}

IceDragon::~IceDragon() {}

double IceDragon::calculateDamage() const {
    return 20.0 + (freezeLevel / 10.0);
}
void IceDragon::specialAbility(Character* target) {
    if (target == nullptr || !target->isAlive())
        return;
    target->setDefense(target->getDefense() * 0.5);
    cout << name << " breathes ice! " << target->getName() << "'s defense is frozen and reduced to " << target->getDefense() << "!\n";
}
void IceDragon::describe() const {
    Dragon::describe();
    cout << "  Type        : Ice Dragon\n";
    cout << "  Freeze Level: " << freezeLevel << "°C\n";
}