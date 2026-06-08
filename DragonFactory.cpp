//
// Created by andre on 7/6/2026.
//

#include "DragonFactory.h"

Dragon* DragonFactory::createDragon(const string& type, const string& name, double health, int damage, const string& region) {
    if (type == "fire")   return new FireDragon(name, health, damage, region);
    if (type == "poison") return new PoisonDragon(name, health, damage, region);
    if (type == "hydra")  return new HydraDragon(name, health, damage, region);
    throw InvalidFormatError("Unknown dragon type: " + type);
}