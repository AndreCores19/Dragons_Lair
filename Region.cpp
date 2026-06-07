//
// Created by andre on 3/6/2026.
//

#include "Region.h"

Region::Region(string name, string description) {
    this->name = name;
    this->description = description;
    visited = false;
}

Region::~Region() {
    for (int i = 0; i < dragons.getSize(); i++)
        delete dragons.at(i);

    for (int i = 0; i < objects.getSize(); i++)
        delete objects.at(i);
}

void Region::addConnection(string region) {
    connections.push_back(region);
}

void Region::addDragon(Dragon* dragon) {
    dragons.push_back(dragon);
}

void Region::isVisited() {
    visited = true;
}

string Region::getName() const {
    return name;
}

string Region::getDescription() const {
    return description;
}

const List<string>& Region::getConnections() const {
    return connections;
}

bool Region::hasBoss() {
    for (int i = 0; i < dragons.getSize(); i++) {
        if (dragons.at(i)->GetIsBoss())
            return true;
    }
    return false;
}

Object* Region::removeObject(int index) {
    Object* obj = objects.at(index);
    return obj;
}
