
#include "Character.h"

Character::Character(string name, double life, int maxLife, int level)
    : Entity(name), life(life), maxLife(maxLife), level(level), defense(0) {}

Character::~Character() {}

double Character::getLife() const {
    return life;
}
int Character::getMaxLife() const {
    return maxLife;
}
int Character::getLevel() const {
    return level;
}

double Character::getDefense() const {
    return defense;
}

void Character::setDefense(double def) {
    if (def < 0) def = 0;
    defense = def;
}
void Character::attack(Character* target) {
    if (target == nullptr || !target->isAlive()) return;
    double dmg = calculateDamage();
    target->takeDamage(dmg);
}
void Character::takeDamage(double dmg) {
    double reduced = dmg - defense;
    if (reduced < 0)
        reduced = 0;
    life -= reduced;
    if (life < 0)
        life = 0;
}
bool Character::operator>(const Character& other) const {
    return level>other.level;
}
bool Character::isAlive() const {
    return life > 0;
}
void Character::setLife(double newLife) {
    if (newLife > maxLife)
        newLife = maxLife;
    if (newLife < 0)
        newLife = 0;
    life = newLife;
}
