//
// Created by andre on 7/6/2026.
//

#include "DragonFactory.h"

Dragon* DragonFactory::createDragon(const string& type, const string& name, double health, int maxHealth, int level, const string& region) {
    if (type == "fire")
        return new FireDragon(name, health, maxHealth, level, region);
    if (type == "poison")
        return new PoisonDragon(name, health, maxHealth, level, region);
    if (type == "ice")
        return new IceDragon(name, health, maxHealth, level, region);
    if (type == "hydra")
        return new HydraDragon(name, health, maxHealth, level, region);
    throw InvalidFormat("Unknown dragon type: " + type);
}