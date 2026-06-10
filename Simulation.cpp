//
// Created by Gerald Quintero on 8/6/26.
//

#include "Simulation.h"

Simulation::Simulation(World* mundo, Hunter* cazador, Logbook* bitacora) : mundo(mundo), cazador(cazador), bitacora(bitacora)
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

bool Simulation::esDragonFinal(Dragon *dragon) const {
    if (dragon == nullptr) {
        return false;
    }

    return dragon->GetIsBoss() || dynamic_cast<HydraDragon*>(dragon) != nullptr;
}

bool Simulation::regionHasDragonsAlive(Region *region) const {
    if (region == nullptr) {
        return false;
    }

    const List<Dragon*>& dragons = region->getDragons();
    for (int i = 0; i < dragons.getSize(); i++) {
        Dragon* dragon = dragons.at(i);

        if (dragon != nullptr && dragon->isAlive()) {
            return true;
        }
    }
    return false;
}

bool Simulation::aliveDragonExists() const {
    if (mundo == nullptr) {
        return false;
    }

    const List<Region*>& regions = mundo->getRegions();
    for (int i = 0; i < regions.getSize(); i++) {
        Region* region = regions.at(i);

        if (regionHasDragonsAlive(region)) {
            return true;
        }
    }
    return false;
}

bool Simulation::moverASiguienteRegion(Region* regionActual) {
    if (regionActual == nullptr) {
        return false;
    }

    const List<string>& conexiones = regionActual->getConnections();

    vector<string> noVisitadas;
    vector<string> conDragonesVivos;

    for (int i = 0; i < conexiones.getSize(); i++) {
        string destino = conexiones.at(i);
        Region* regionDestino = mundo->findRegionByName(destino);

        if (regionDestino == nullptr) {
            continue;
        }

        if (!regionDestino->wasVisited()) {
            noVisitadas.push_back(destino);
        }

        if (regionHasDragonsAlive(regionDestino)) {
            conDragonesVivos.push_back(destino);
        }
    }

    if (!noVisitadas.empty()) {
        string destino = noVisitadas[rand() % noVisitadas.size()];

        if (mundo->moveHunter(destino)) {
            bitacora->registrar(
                "Hunter " + cazador->getName() + " moves to " + destino + "."
            );
            return true;
        }
    }

    if (!conDragonesVivos.empty()) {
        string destino = conDragonesVivos[rand() % conDragonesVivos.size()];

        if (mundo->moveHunter(destino)) {
            bitacora->registrar(
                "Hunter " + cazador->getName() +" returns to " + destino + " because there are still living dragons.");
            return true;
        }
    }

    if (aliveDragonExists()) {
        bitacora->registrar(
            "Hunter " + cazador->getName() +
            " cannot find a direct path to another living dragon."
        );
    } else {
        bitacora->registrar(
            "Hunter " + cazador->getName() +
            " has no remaining dragons to fight."
        );
    }

    finalizada = true;
    return false;
}


void Simulation::manageVillagers(Region *region) {
    if (region == nullptr) {
        return;
    }

    const List<Villager*>& villagers = region->getVillagers();

    if (villagers.getSize() == 0) {
        return;
    }

    for (int i = 0; i < villagers.getSize(); i++) {
        Villager* villager = villagers.at(i);

        if (villager == nullptr) {
            continue;
        }

        bitacora->registrar(
            "Hunter " + cazador->getName() + " meets villager " +
            villager->getName() + " in " + region->getName() + "."
        );

        if (!probability(60)) {
            bitacora->registrar("Hunter " + cazador->getName() + " decides not to buy from " + villager->getName() + ".");
            continue;
        }

        int goldBefore = cazador->getGold();
        double lifeBefore = cazador->getLife();

        villager->sell(cazador, 0);

        int goldAfter = cazador->getGold();
        double lifeAfter = cazador->getLife();

        if (goldAfter < goldBefore) {
            int price = goldBefore - goldAfter;

            bitacora->registrar(
                "Hunter " + cazador->getName() + " buys an item from " + villager->getName() + " for " + to_string(price) + " gold."
            );
            if (lifeAfter > lifeBefore) {
                bitacora->registrar("Hunter " + cazador->getName() + " recovers " + to_string((int)lifeAfter - lifeBefore) + " life points after using potion.");
            }
        } else {
            bitacora->registrar(
                "Hunter " + cazador->getName() + " could not buy an item from " +
                villager->getName() + "."
            );
        }
    }
}

double Simulation::randomDamage(double damage) const {
    int percentage = 80 + (rand() % 41);
    return damage * (percentage / 100.0);
}

bool Simulation::probability(int percentage) const {
    return (rand() % 100) < percentage;
}

void Simulation::run() {
    cout << "Starting simulation..." << endl;

    while (!verificarFinAventura()) {
        ejecutarTurno();
    }
    generarReporte();
    bitacora->cerrar();
    cout << "Simulation finished. Final report generated in final_report.txt" << endl;
}

void Simulation::ejecutarTurno() {
    turnoActual++;
    bitacora->setTurno(turnoActual);
    Region* region = mundo->getCurrentRegion();
    bool primeraVisita = !region->wasVisited();

    if (region == nullptr) {
        finalizada = true;
        bitacora->registrar("The simulation stopped because there is no current region.");
        return;
    }

    region->isVisited();
    bitacora->registrar("Hunter " + cazador->getName() + " enters " + region->getName() + ".");
    if (primeraVisita) {
        manageVillagers(region);
    }
    List<Dragon*>& dragones = const_cast<List<Dragon*>&>(region->getDragons());

    for (int i = 0; i < dragones.getSize(); i++) {
        Dragon* dragon = dragones.at(i);

        if (dragon == nullptr || !dragon->isAlive()) {
            continue;
        }

        double danoCazador = randomDamage(cazador->calculateDamage());
        dragon->takeDamage(danoCazador);
        if (danoCazador == 0) {
            bitacora->registrar("Hunter " + cazador->getName() + " missed the attack!");
        }
        else{
        bitacora->registrar(
            cazador->getName() + " attacks " + dragon->getName() +
            " causing " + to_string((int)danoCazador) + " damage.");

        if (!dragon->isAlive()) {
            bitacora->registrar(dragon->getName() + " was defeated.");
            int levelBefore = cazador->getLevel();

            cazador->addExperience(dragon->getLevel() * 50.0);

            if (cazador->getLevel() > levelBefore) {
                bitacora->registrar("Hunter levels up! - Maximum life increased by 20");
            }

            int goldReward = dragon->getLevel() * 25;
            cazador->addGold(goldReward);

            bitacora->registrar("Hunter " + cazador->getName() + " earns " + to_string(goldReward) + " gold for defeating " + dragon->getName() + ".");

            if (esDragonFinal(dragon)) {
                hydraDerrotada = true;
                finalizada = true;
            }
            continue;
        }
    }

        double danoDragon = randomDamage(dragon->calculateDamage());
        cazador->takeDamage(danoDragon);
        if (danoDragon == 0) {
            bitacora->registrar("Hunter " + cazador->getName() + " evaded " + dragon->getName() + "'s attack!");
        }
        else {
            bitacora->registrar(
          dragon->getName() + " attacks " + cazador->getName() +
          " causing " + to_string((int)danoDragon) + " damage.");

            if (!cazador->isAlive()) {
                bitacora->registrar("Hunter " + cazador->getName() + " has died.");
                finalizada = true;
                return;
            }
        }
    }

    List<Object*>& objetos = const_cast<List<Object*>&>(region->getObjects());

    int index = 0;

    while (index < objetos.getSize()) {
        Object* object = objetos.at(index);
        if (object == nullptr) {
            index++;
            continue;
        }

        Weapon* weapon = dynamic_cast<Weapon*>(object);
        if (weapon != nullptr) {
            Object* objectPicked = region->removeObject(index);
            cazador->pickUp(objectPicked);
            bitacora->registrar("Hunter " + cazador->getName() + " picks up weapon " + objectPicked->getName() + ".");
        }
        else {
            bitacora->registrar("Hunter " + cazador->getName() + " ignores " + object->getName() + ".");
            index++;
        }
    }

    if (!finalizada) {
        if (regionHasDragonsAlive(region)) {
            bitacora->registrar("Hunter " + cazador->getName() + " stays in " + region->getName() + " because there are still living dragons.");
        }
        else {
            moverASiguienteRegion(region);
        }
    }
}

bool Simulation::verificarFinAventura() {
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

void Simulation::generarReporte() {
    ofstream reporte("final_report.txt", ios::out);

    if (!reporte.is_open()) {
        throw BaseError("Could not create final_report.txt.");
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
