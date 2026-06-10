//
// Created by Gerald Quintero on 8/6/26.
//

#ifndef DRAGONS_LAIR_SIMULACION_H
#define DRAGONS_LAIR_SIMULACION_H
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
using namespace std;

class Simulation {
private:
    World* mundo;
    Hunter* cazador;
    Logbook* bitacora;
    int turnoActual;
    bool finalizada;
    bool hydraDerrotada;
    bool esDragonFinal(Dragon* dragon) const;
    bool moverASiguienteRegion(Region* regionActual);
    bool regionHasDragonsAlive(Region* region) const;
    bool aliveDragonExists() const;
    void manageVillagers(Region* region);
    double randomDamage(double damage) const;
    bool probability(int percentage) const;

public:
    Simulation(World* mundo, Hunter* cazador, Logbook* bitacora);

    void run();
    void ejecutarTurno();
    bool verificarFinAventura();
    void generarReporte();

};


#endif //DRAGONS_LAIR_SIMULACION_H
