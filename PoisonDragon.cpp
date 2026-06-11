#include "PoisonDragon.h"

PoisonDragon::PoisonDragon(string name, double life, int maxLife, int level, string region)
    : Dragon(name, life, maxLife, level, region), toxicity(25.0), poisonStacks(0) {}

PoisonDragon::~PoisonDragon() {}

double PoisonDragon::calculateDamage() const {
    return 15.0 + toxicity + poisonStacks; //base damage: 15 + toxicity + poison stacks
}
void PoisonDragon::specialAbility(Character* target) {
    if (target == nullptr || !target->isAlive())
        return;
    poisonStacks += toxicity * 0.2;
    double poisonDamage = poisonStacks;
    target->takeDamage(poisonDamage);
    cout << name << " releases a toxic cloud! " << target->getName() << " is poisoned for " << poisonDamage << " damage! (stacks: " << poisonStacks << ")\n";
}
void PoisonDragon::describe() const {
    Dragon::describe();
    cout << "  Type         : Poison Dragon\n";
    cout << "  Toxicity     : " << toxicity << "\n";
    cout << "  Poison stacks: " << poisonStacks << "\n";
}

double PoisonDragon::getToxicity() const {
    return toxicity;
}
