#include "Armor.h"
#include "Hunter.h"

Armor::Armor(string name, int value, double defense)
: Object(name, value), defense(defense), equipped(false) {}

Armor::~Armor() {}

double Armor::getDefense() const {
    return defense;
}

bool Armor::isEquipped() const {
    return equipped;
}
void Armor::use(Character* target) {
    Hunter* hunter = dynamic_cast<Hunter*>(target);
    if (hunter == nullptr)
        return;
    equipped = true;
    hunter->setDefense(defense);
    cout << hunter->getName() << " equipped " << name << " (+" << defense << " defense)\n";
}
void Armor::describe() const {
    cout << "  [Armor] " << name
         << " | Defense: " << defense
         << " | Value: " << value
         << " | ";
    if (equipped) {
        cout << "Equipped\n";
    } else {
        cout << "Not equipped\n";
    }
}
