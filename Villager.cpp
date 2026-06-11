#include "Villager.h"
#include "Hunter.h"

Villager::Villager(string name, string diaglog)
    :Entity(name), dialog(diaglog) {}

Villager::~Villager() {
    for (int i = 0; i < shop.getSize(); i++)
        delete shop.at(i);
}

void Villager::addItem(Object* item) {
    if (item == nullptr) return;
    shop.push_back(item);
}
void Villager::sell(Hunter* hunter, int index) {
    if (hunter == nullptr) return;
    if (index < 0 || index >= shop.getSize()) {
        cout << "Invalid item.\n";
        return;
    }
    Object* item = shop.at(index); //Get the item from the shop at the indicated position
    if (hunter->getGold() < item->getValue()) {
        cout << name << ": You don't have enough gold!\n";
        return;
    }
    hunter->spendGold(item->getValue());
    hunter->pickUp(item);
    shop.removeAt(index);

    cout << name << ": Here you go! Good luck out there.\n";
    cout << hunter->getName() << " bought " << item->getName() << " for " << item->getValue() << " gold.\n";
}

void Villager::showShop() const {
    cout << name << "'s Shop \n";
    if (shop.getSize() == 0) {
        cout << "  No items available.\n";
        return;
    }
    for (int i = 0; i < shop.getSize(); i++) {
        cout << "  [" << i << "] ";
        shop.at(i)->describe();
    }
}
void Villager::describe() const {
    cout << "  Villager: " << name << "\n";
    cout << "  Says : " << dialog << "\n";
    showShop();
}
