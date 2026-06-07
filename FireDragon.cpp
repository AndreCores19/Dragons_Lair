#include "FireDragon.h"

FireDragon::FireDragon(string name, double life, int maxLife, int level, string region, double temperature)
    : Dragon(name, life, maxLife, level, region), temperature(temperature) {}

FireDragon::~FireDragon() {}

double FireDragon::calculateDamage() const {
    return 20.0 + (temperature / 10.0);
}
void FireDragon::specialAbility(Character* target) {
    if (target == nullptr || !target->isAlive())
        return;
    double burnDamage = temperature * 0.15;
    target->takeDamage(burnDamage);
    cout << name << " breathes fire! " << target->getName() << " burns for " << burnDamage << " damage!\n";
}
void FireDragon::describe() const {
    Dragon::describe();
    cout << "  Type        : Fire Dragon\n";
    cout << "  Temperature : " << temperature << "°C\n";
}