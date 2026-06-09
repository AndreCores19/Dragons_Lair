//
// Created by andre on 3/6/2026.
//

#ifndef DRAGONS_LAIR_REGION_H
#define DRAGONS_LAIR_REGION_H
#include <iostream>
#include "List.h"
#include "Dragon.h"
#include "Villager.h"
using namespace std;

class Region {
    string name;
    string description;
    bool visited;
    List<string> connections;
    List<Dragon*> dragons;
    List<Object*> objects;
    List<Villager*> villagers;
public:
    Region(string, string);
    ~Region();
    void addConnection(string);
    void addDragon(Dragon* dragon);
    void addObject(Object* object);
    void addVillager(Villager* villager);
    void isVisited();
    bool wasVisited() const;
    string getName() const;
    string getDescription() const;
    const List<string>& getConnections() const;
    const List<Dragon*>& getDragons() const;
    const List<Object*>& getObjects() const;
    const List<Villager*>& getVillagers();
    Object* removeObject(int);
    bool hasBoss();
};


#endif //DRAGONS_LAIR_REGION_H