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
    /*for (int i = 0; i < dragons.getSize(); i++)
        delete dragons.at(i);

    for (int i = 0; i < objects.getSize(); i++)
        delete objects.at(i);
        */
}

void Region::addConnection(string region) {
    connections.push_back(region);
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

/*bool Region::hasBoss() {
    for (int i = 0; i < dragons.getSize(); i++) {
        if (dragons.at(i)->isBoss())
            return true;
    }
    return false;
}*/

/*Objeto* Region::removerObjeto(int index) {
    Objeto* obj = objetos.at(index);
    // eliminar de la lista sin delete
    return obj; // el cazador toma la propiedad
}*/
