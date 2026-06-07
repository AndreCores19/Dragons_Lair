//
// Created by andre on 3/6/2026.
//

#ifndef DRAGONS_LAIR_WORLD_H
#define DRAGONS_LAIR_WORLD_H
#include "Region.h"
using namespace std;

class World {
    Region* currentRegion;
    List<Region*> regions;
public:
    World();
    ~World();
    void setCurrentRegion(Region* region);
    Region* getCurrentRegion() const;
    bool moveHunter(string);
    bool connectionExists(string, string);
};


#endif //DRAGONS_LAIR_WORLD_H