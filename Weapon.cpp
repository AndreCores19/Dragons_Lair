#include "Weapon.h"
#include "Hunter.h"

Weapon::Weapon(string name, int value, double damage)
    : Object(name, value), damage(damage), equipped(false) {}

Weapon::~Weapon() {}

double Weapon::getDamage() const {
    return damage;
}
bool Weapon::isEquipped() const {
    return equipped;
}
void Weapon::use(Character* target) {
    //dynamic_cast checks if target is actually a Hunter
    Hunter* hunter = dynamic_cast<Hunter*>(target);
    if (hunter == nullptr)
        return;
    equipped = true;
    cout << hunter->getName() << " equipped " << name<< " (+" << damage << " damage)\n";
}
void Weapon::describe() const {
    cout << "  [Weapon] " << name
         << " | Damage: " << damage
         << " | Value: " << value
         << " | ";
    if (equipped) {
        cout << "Equipped\n";
    } else {
        cout << "Not equipped\n";
    }
}


