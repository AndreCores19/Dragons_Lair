//
// Created by Gerald Quintero on 8/6/26.
//

#include "Simulacion.h"

Simulacion::Simulacion(World* mundo, Hunter* cazador, Bitacora* bitacora) : mundo(mundo), cazador(cazador), bitacora(bitacora)
, turnoActual(0), finalizada(false), hydraDerrotada(false){
    if (mundo == nullptr) {
        throw BaseError("Simulation received a null world");
    }
    if (cazador == nullptr) {
        throw BaseError("Simulation received a null hunter");
    }
    if (bitacora == nullptr) {
        throw BaseError("Simulation ");
    }
    if (mundo->getCurrentRegion() == nullptr) {
        throw BaseError("El mundo no tiene una region inicial.");
    }
}

bool Simulacion::esDragonFinal(Dragon *dragon) const {
    if (dragon == nullptr) {
        return false;
    }

    return dragon->GetIsBoss() || dynamic_cast<HydraDragon*>(dragon) != nullptr;
}


bool Simulacion::moverASiguienteRegion(Region* regionActual) {
    if (regionActual == nullptr) {
        return false;
    }

    const List<string>& conexiones = regionActual->getConnections();
    for (int i = 0; i < conexiones.getSize(); i++) {
        string destino = conexiones.at(i);
        if (mundo->moveHunter(destino)) {
            bitacora->registrar("Hunter " + cazador->getName() + " moves to " + destino + ".");
            return true;
        }
    }

    bitacora->registrar("The hunter" + cazador->getName() + " has no available regions to move to.");
    finalizada = true;
    return false;
}

void Simulacion::run() {
    cout << "Starting simulation..." << endl;

    while (!verificarFinAventura()) {
        ejecutarTurno();
    }
    generarReporte();
    bitacora->cerrar();
    cout << "Simulation finished. Final report generated in reporte_final.txt" << endl;
}

void Simulacion::ejecutarTurno() {
    turnoActual++;
    bitacora->setTurno(turnoActual);
    Region* region = mundo->getCurrentRegion();

    if (region == nullptr) {
        finalizada = true;
        bitacora->registrar("The simulation stopped because there is no current region.");
        return;
    }

    region->isVisited();
    bitacora->registrar("Hunter " + cazador->getName() + " enters " + region->getName() + ".");
    List<Dragon*>& dragones = const_cast<List<Dragon*>&>(region->getDragons());

    for (int i = 0; i < dragones.getSize(); i++) {
        Dragon* dragon = dragones.at(i);

        if (dragon == nullptr || !dragon->isAlive()) {
            continue;
        }

        double danoCazador = cazador->calculateDamage();
        cazador->attack(dragon);
        bitacora->registrar(
            cazador->getName() + " attacks " + dragon->getName() +
            " causing " + to_string((int)danoCazador) + " damage.");

        if (!dragon->isAlive()) {
            bitacora->registrar(dragon->getName() + " was defeated.");
            cazador->addExperience(dragon->getLevel() * 50.0);

            if (esDragonFinal(dragon)) {
                hydraDerrotada = true;
                finalizada = true;
            }
            continue;
        }

        double danoDragon = dragon->calculateDamage();
        dragon->attack(cazador);
        bitacora->registrar(
            dragon->getName() + " attacks " + cazador->getName() +
            " causing " + to_string((int)danoDragon) + " damage.");

        if (!cazador->isAlive()) {
            bitacora->registrar("Hunter " + cazador->getName() + " has died.");
            finalizada = true;
            return;
        }
    }

    List<Object*>& objetos = const_cast<List<Object*>&>(region->getObjects());

    while (objetos.getSize() > 0) {
        Object* objeto = region->removeObject(0);

        if (objeto != nullptr) {
            cazador->pickUp(objeto);
            bitacora->registrar(
                "Hunter " + cazador->getName() + " picks up " + objeto->getName() + "."
            );
        }
    }

    if (!finalizada) {
        moverASiguienteRegion(region);
    }
}

bool Simulacion::verificarFinAventura() {
    if (finalizada) {
        return true;
    }

    if (cazador == nullptr || !cazador->isAlive()) {
        finalizada = true;
        return true;
    }

    if (hydraDerrotada) {
        finalizada = true;
        return true;
    }

    if (mundo == nullptr || mundo->getCurrentRegion() == nullptr) {
        finalizada = true;
        return true;
    }
    return false;
}

void Simulacion::generarReporte() {
    ofstream reporte("reporte_final.txt", ios::out);

    if (!reporte.is_open()) {
        throw BaseError("Could not create reporte_final.txt.");
    }

    reporte << "===== FINAL REPORT - DRAGON'S LAIR =====" << endl;
    reporte << "Turns executed: " << turnoActual << endl;
    reporte << "Logbook file: " << bitacora->getRuta() << endl;
    reporte << endl;
    reporte << "Final hunter status:" << endl;
    reporte << "Name: " << cazador->getName() << endl;
    reporte << "Life: " << cazador->getLife() << " / " << cazador->getMaxLife() << endl;
    reporte << "Level: " << cazador->getLevel() << endl;
    reporte << "Gold: " << cazador->getGold() << endl;
    reporte << "Experience: " << cazador->getExperience() << endl;
    reporte << endl;
    reporte << "Result: ";

    if (hydraDerrotada) {
        reporte << "Victory. The hunter defeated the Hydra." << endl;
    } else if (!cazador->isAlive()) {
        reporte << "Defeat. The hunter died during the adventure." << endl;
    } else {
        reporte << "Adventure finished. There are no available movements." << endl;
    }

    reporte.close();
}
