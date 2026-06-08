//
// Created by Gerald Quintero on 8/6/26.
//

#ifndef DRAGONS_LAIR_SIMULACION_H
#define DRAGONS_LAIR_SIMULACION_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "World.h"
#include "Hunter.h"
#include "Bitacora.h"
#include "HydraDragon.h"
#include "BaseError.h"
using namespace std;

class Simulacion {
private:
    World* mundo;
    Hunter* cazador;
    Bitacora* bitacora;
    int turnoActual;
    bool finalizada;
    bool hydraDerrotada;
    bool esDragonFinal(Dragon* dragon) const;
    bool moverASiguienteRegion(Region* regionActual);

public:
    Simulacion(World* mundo, Hunter* cazador, Bitacora* bitacora);

    void run();
    void ejecutarTurno();
    bool verificarFinAventura();
    void generarReporte();

};


#endif //DRAGONS_LAIR_SIMULACION_H
