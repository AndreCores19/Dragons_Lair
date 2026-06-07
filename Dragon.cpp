
#include "Dragon.h"
//hola
Dragon::Dragon(string name, double life, int maxLife, int level, string region)
    : Character(name, life, maxLife, level), region(region) {}

Dragon::~Dragon() {}

string Dragon::getRegion() const {
    return region;
}
void Dragon::describe() const {
    cout << "  Dragon: " << name << "\n";
    cout << "  Level  : " << level << "\n";
    cout << "  Life   : " << life << " / " << maxLife << "\n";
    cout << "  Region : " << region << "\n";
    cout << "  Status : " << (isAlive() ? "Alive" : "Defeated") << "\n";
}

