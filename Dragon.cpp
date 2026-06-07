
#include "Dragon.h"

Dragon::Dragon(string name, double life, int maxLife, int level, string region)
    : Character(name, life, maxLife, level), region(region) {
    isBoss = false;
}

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

bool Dragon::GetIsBoss() const {
    return isBoss;
}

