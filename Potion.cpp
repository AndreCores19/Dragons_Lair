#include "Potion.h"
#include "Hunter.h"

Potion::Potion(string name, int value, double healAmount)
: Object(name, value), healAmount(healAmount) {}

Potion::~Potion() {}

double Potion::getHealAmount() const {
    return healAmount;
}
void Potion::use(Character* target) {
    if (target == nullptr || !target->isAlive())
        return;
    double currentLife = target->getLife();
    double maxLife = target->getMaxLife();
    double actualHeal = healAmount;

    //It heals, but without exceeding the maximum
    if (currentLife + healAmount > maxLife) {
        actualHeal = maxLife - currentLife;
    }
    target->setLife(currentLife + actualHeal);
    cout << target->getName() << " drinks " << name << " and recovers " << actualHeal << " HP!\n";
}
void Potion::describe() const {
    cout << "  [Potion] " << name
         << " | Heals: " << healAmount
         << " | Value: " << value << "\n";
}