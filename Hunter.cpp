#include "Hunter.h"
#include "Weapon.h"
#include "Potion.h"

Hunter::Hunter(string name, double life, int maxLife, int level, int gold)
    : Character(name, life, maxLife, level), gold(gold), experience(0) {}

Hunter::~Hunter() {
    for (int i = 0; i < inventory.getSize(); i++)
        delete inventory.at(i);
}

int Hunter::getGold() const {
    return gold;
}
double Hunter::getExperience() const {
    return experience;
}
double Hunter::calculateDamage() const {
    double base = 10.0 + level * 2.0;
    for (int i = 0; i < inventory.getSize(); i++) {
        Weapon* weapon = dynamic_cast<Weapon*>(inventory.at(i));
        if (weapon != nullptr)
            return base + weapon->getDamage();
    }
    return base;
}
//Inventory
void Hunter::pickUp(Object* obj) {
    if (obj == nullptr) return;
    inventory.push_back(obj);
}
void Hunter::usePotion() {
    for (int i = 0; i < inventory.getSize(); i++) {
        Potion* potion = dynamic_cast<Potion*>(inventory.at(i));
        if (potion != nullptr) {
            potion->use(this);
            inventory.removeAt(i);  // potion consumed on use
            return;
        }
    }
    cout << name << " has no potions in inventory.\n";
}

void Hunter::addExperience(double exp) {
    experience += exp;
    if (experience >= level * 100.0) {
        level++;
        maxLife += 20;
        life = maxLife;   // full heal on level up
        experience = 0;
        cout << name << " leveled up! Now level " << level << ".\n";
    }
}
void Hunter::addGold(int amount) {
    if (amount < 0) return;
    gold += amount;
}
void Hunter::spendGold(int amount) {
    if (amount < 0) return;
    gold -= amount;
    if (gold < 0) gold = 0;
}

void Hunter::describe() const {
    cout << "  Hunter: " << name << "\n";
    cout << "  Level      : " << level << "\n";
    cout << "  Life       : " << life << " / " << maxLife << "\n";
    cout << "  Gold       : " << gold << "\n";
    cout << "  Experience : " << experience << " / " << level * 100.0 << "\n";
    cout << "  Inventory  : " << inventory.getSize() << " item(s)\n";
    for (int i = 0; i < inventory.getSize(); i++) {
        cout << "    - ";
        inventory.at(i)->describe();
    }
}



