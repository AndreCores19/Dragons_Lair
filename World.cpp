//
// Created by andre on 3/6/2026.
//

#include "World.h"

World::World() {
    currentRegion = nullptr;
}

World::~World() {
    for (int i = 0; i < regions.getSize(); i++)
        delete regions.at(i);
}

void World::setCurrentRegion(Region* region) {
    currentRegion = region;
}

Region* World::getCurrentRegion() const {
    return currentRegion;
}

Region* World::findRegionByName(const string& name) const {
    for (int i = 0; i < regions.getSize(); i++) {
        Region* region = regions.at(i);

        if (region != nullptr && region->getName() == name) {
            return region;
        }
    }
    return nullptr;
}

const List<Region*>& World::getRegions() const {
    return regions;
}

bool World::moveHunter(string destination) {
    // Verify the connection
    if (!connectionExists(currentRegion->getName(), destination))
        return false;
    // Look for the route
    for (int i = 0; i < regions.getSize(); i++) {
        if (regions.at(i)->getName() == destination) {
            currentRegion = regions.at(i);
            return true;
        }
    }
    return false;
}

bool World::connectionExists(string a, string b) {
    // look for the region in the list
    for (int i = 0; i < regions.getSize(); i++) {
        if (regions.at(i)->getName() == a) {
            // check the connections
            List<string> connections = regions.at(i)->getConnections();
            for (int j = 0; j < connections.getSize(); j++) {
                if (connections.at(j) == b)
                    return true; // found the region and is connected
            }
            return false; // found the region but b is not connected
        }
    }
    return false; // the region does not exist
}

void World::addRegion(Region* region) {
    regions.push_back(region);
}

void World::addDragonToRegion(const string& regionName, Dragon* dra) {
    for (int i = 0; i < regions.getSize(); i++) {
        if (regions.at(i)->getName() == regionName) {
            regions.at(i)->addDragon(dra);
            return;
        }
    }
    throw InvalidFormat("Region not found: " + regionName);
}

void World::addObjectToRegion(const string& regionName, Object* obj) {
    for (int i = 0; i < regions.getSize(); i++) {
        if (regions.at(i)->getName() == regionName) {
            regions.at(i)->addObject(obj);
            return;
        }
    }
    throw InvalidFormat("Region not found: " + regionName);
}

void World::addVillagerToRegion(const string& regionName, Villager* vil) {
    for (int i = 0; i < regions.getSize(); i++) {
        if (regions.at(i)->getName() == regionName) {
            regions.at(i)->addVillager(vil);
            return;
        }
    }
    throw InvalidFormat("Region not found: " + regionName);
}
