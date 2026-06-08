#include "FireDragon.h"

FireDragon::FireDragon(string name, double life, int maxLife, int level, string region)
    : Dragon(name, life, maxLife, level, region), temperature(200) {}

FireDragon::~FireDragon() {}

double FireDragon::calculateDamage() const {
    return 20.0 + (temperature / 10.0); //base damage: 20 + 1 damage per 10 degrees of temperature
}
void FireDragon::specialAbility(Character* target) {
    if (target == nullptr || !target->isAlive())
        return;
    double burnDamage = temperature * 0.15; //additional damage to the normal attack
    target->takeDamage(burnDamage);
    cout << name << " breathes fire! " << target->getName() << " burns for " << burnDamage << " damage!\n";
}
void FireDragon::describe() const {
    Dragon::describe();
    cout << "  Type        : Fire Dragon\n";
    cout << "  Temperature : " << temperature << "°C\n";
}