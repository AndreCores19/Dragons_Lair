

#include "HydraDragon.h"

HydraDragon::HydraDragon(string name, double life, int maxLife, int level, string region, int heads)
: Dragon(name, life, maxLife, level, region), heads(heads), maxHeads(heads) {}

HydraDragon::~HydraDragon() {}

double HydraDragon::calculateDamage() const {
    return 30.0 * heads; //base damage: 30 damage per head
}

void HydraDragon::specialAbility(Character* target) {
    if (!isAlive()) return;

    if (heads > 1) {
        heads--;
        double healAmount = maxLife * 0.15;
        life = min(life + healAmount, (double)maxLife); //It heals itself, but without exceeding the maximum
        cout << name << " regenerates! One head cut off, " << heads << " remaining.\n";
        cout << name << " healed for " << healAmount << " HP!\n";
    } else {
        //last head, unleash desperation attack
        if (target == nullptr || !target->isAlive()) return;
        double desperation = calculateDamage() * 2.0;
        target->takeDamage(desperation);
        cout << name << " unleashes a desperate final attack for " << desperation << " damage!\n";
    }
}
void HydraDragon::describe() const {
    Dragon::describe();
    cout << "  Type  : Hydra Dragon (Final Boss)\n";
    cout << "  Heads : " << heads << " / " << maxHeads << "\n";
}

int HydraDragon::getHeads() const {
    return heads;
}
