#ifndef DRAGONS_LAIR_SIMULATION_H
#define DRAGONS_LAIR_SIMULATION_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include "World.h"
#include "Hunter.h"
#include "Logbook.h"
#include "HydraDragon.h"
#include "BaseError.h"
#include "Weapon.h"
#include <vector>
using namespace std;

class Simulation {
private:
    World* world;
    Hunter* hunter;
    Logbook* logbook;
    int currentTurn;
    bool finished;
    bool hydraDefeated;
    bool isFinalDragon(Dragon* dragon) const;
    bool moveToNextRegion(Region* currentRegion);
    bool regionHasDragonsAlive(Region* region) const;
    bool aliveDragonExists() const;
    void manageVillagers(Region* region);
    double randomDamage(double damage) const;
    bool probability(int percentage) const;

public:
    Simulation(World* world, Hunter* hunter, Logbook* logbook);

    void run();
    void executeTurn();
    bool checkAdventureEnd();
    void generateReport();
};

#endif //DRAGONS_LAIR_SIMULATION_H