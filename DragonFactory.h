//
// Created by andre on 7/6/2026.
//

#ifndef DRAGONS_LAIR_DRAGONFACTORY_H
#define DRAGONS_LAIR_DRAGONFACTORY_H
#include "FireDragon.h"
#include "PoisonDragon.h"
#include "HydraDragon.h"
#include "IceDragon.h"
#include "InvalidFormat.h"
using namespace std;
class DragonFactory {
public:
    static Dragon* createDragon(const string& type, const string& name, double health, int maxHealth, int level, const string& region);
};


#endif //DRAGONS_LAIR_DRAGONFACTORY_H