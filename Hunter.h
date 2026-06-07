//
// Created by julia on 6/6/2026.
//

#ifndef DRAGONS_LAIR_HUNTER_H
#define DRAGONS_LAIR_HUNTER_H
#include "Character.h"
#include "Object.h"
#include "List.h"
//hola
class Hunter : public Character {
private:
    List<Object*> inventory;
    int gold;
    double experience;
public:
    Hunter(string, double, int, int, int);
    ~Hunter();
    double calculateDamage() const override;
    void pickUp(Object*);
    void usePotion();
    void addExperience(double);
    void addGold(int);
    int getGold() const;
    double getExperience() const;
    void describe() const override;
};

#endif //DRAGONS_LAIR_HUNTER_H