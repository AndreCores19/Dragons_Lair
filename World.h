//
// Created by andre on 3/6/2026.
//

#ifndef DRAGONS_LAIR_WORLD_H
#define DRAGONS_LAIR_WORLD_H
#include <list>

#include "Region.h"
#include "InvalidFormat.h"
using namespace std;

class World
{
    Region* currentRegion;
    List<Region*> regions;
public:
    World();
    ~World();
    void setCurrentRegion(Region*);
    Region* getCurrentRegion() const;
    Region* findRegionByName(const string& name) const;
    const List<Region*>& getRegions() const;
    bool moveHunter(string);
    bool connectionExists(string, string);
    void addRegion(Region*);
    void addDragonToRegion(const string&, Dragon*);
    void addObjectToRegion(const string&, Object*);
    void addVillagerToRegion(const string&, Villager*);
};


#endif //DRAGONS_LAIR_WORLD_H