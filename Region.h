//
// Created by andre on 3/6/2026.
//

#ifndef DRAGONS_LAIR_REGION_H
#define DRAGONS_LAIR_REGION_H
#include <iostream>
#include "List.h"
#include "Dragon.h"
#include "Hunter.h"
using namespace std;

class Region {
    string name;
    string description;
    bool visited;
    List<string> connections;
    List<Dragon*> dragons;
    List<Object*> objects;
public:
    Region(string, string);
    ~Region();
    void addConnection(string);
    void addDragon(Dragon* dragon);
    void addObject(Object* object);
    void isVisited();
    string getName() const;
    string getDescription() const;
    const List<string>& getConnections() const;
    const List<Dragon*>& getDragons() const;
    const List<Object*>& getObjects() const;
    Object* removeObject(int);
    bool hasBoss();
};


#endif //DRAGONS_LAIR_REGION_H