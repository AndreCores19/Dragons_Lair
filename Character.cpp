
#include "Character.h"

Character::Character(string name, double life, int maxLife, int level)
    : Entity(name), life(life), maxLife(maxLife), level(level) {}

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
void Character::attack(Character* target) {
    if (target == nullptr || !target->isAlive()) return;
    double dmg = calculateDamage();  //each subclass defines how much
    target->takeDamage(dmg);
}
void Character::takeDamage(double dmg) {
    life -= dmg;
    if (life < 0) life = 0;
}
bool Character::operator>(const Character& other) const {
    return level>other.level;
}
bool Character::isAlive() const {
    return life > 0;
}
