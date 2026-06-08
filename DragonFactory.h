//
// Created by andre on 7/6/2026.
//

#ifndef DRAGONS_LAIR_DRAGONFACTORY_H
#define DRAGONS_LAIR_DRAGONFACTORY_H
#include "FireDragon.h"
#include "PoisonDragon.h"
#include "HydraDragon.h"
//#include "IceDragon.h"

class DragonFactory {
public:
    static Dragon* createDragon(const string&, const string&, double, int, const string&);
};


#endif //DRAGONS_LAIR_DRAGONFACTORY_H