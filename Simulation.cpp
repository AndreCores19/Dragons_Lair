#include "Simulation.h"

Simulation::Simulation(World* world, Hunter* hunter, Logbook* logbook)
    : world(world), hunter(hunter), logbook(logbook),
      currentTurn(0), finished(false), hydraDefeated(false) {
    if (world == nullptr)
        throw BaseError("Simulation received a null world");
    if (hunter == nullptr)
        throw BaseError("Simulation received a null hunter");
    if (logbook == nullptr)
        throw BaseError("Simulation received a null logbook");
    if (world->getCurrentRegion() == nullptr)
        throw BaseError("The world has no initial region.");
}

bool Simulation::isFinalDragon(Dragon* dragon) const {
    if (dragon == nullptr)
        return false;
    return dragon->GetIsBoss() || dynamic_cast<HydraDragon*>(dragon) != nullptr;
}

bool Simulation::regionHasDragonsAlive(Region* region) const {
    if (region == nullptr)
        return false;
    const List<Dragon*>& dragons = region->getDragons();
    for (int i = 0; i < dragons.getSize(); i++) {
        Dragon* dragon = dragons.at(i);
        if (dragon != nullptr && dragon->isAlive())
            return true;
    }
    return false;
}

bool Simulation::aliveDragonExists() const {
    if (world == nullptr)
        return false;
    const List<Region*>& regions = world->getRegions();
    for (int i = 0; i < regions.getSize(); i++) {
        Region* region = regions.at(i);
        if (regionHasDragonsAlive(region))
            return true;
    }
    return false;
}

bool Simulation::moveToNextRegion(Region* currentRegion) {
    if (currentRegion == nullptr)
        return false;

    const List<string>& connections = currentRegion->getConnections();

    vector<string> unvisited;
    vector<string> withLivingDragons;

    for (int i = 0; i < connections.getSize(); i++) {
        string destination = connections.at(i);
        Region* destinationRegion = world->findRegionByName(destination);

        if (destinationRegion == nullptr)
            continue;

        if (!destinationRegion->wasVisited())
            unvisited.push_back(destination);

        if (regionHasDragonsAlive(destinationRegion))
            withLivingDragons.push_back(destination);
    }

    if (!unvisited.empty()) {
        string destination = unvisited[rand() % unvisited.size()];
        if (world->moveHunter(destination)) {
            logbook->log("Hunter " + hunter->getName() + " moves to " + destination + ".");
            return true;
        }
    }

    if (!withLivingDragons.empty()) {
        string destination = withLivingDragons[rand() % withLivingDragons.size()];
        if (world->moveHunter(destination)) {
            logbook->log("Hunter " + hunter->getName() + " returns to " + destination + " because there are still living dragons.");
            return true;
        }
    }

    if (aliveDragonExists())
        logbook->log("Hunter " + hunter->getName() + " cannot find a direct path to another living dragon.");
    else
        logbook->log("Hunter " + hunter->getName() + " has no remaining dragons to fight.");

    finished = true;
    return false;
}

void Simulation::manageVillagers(Region* region) {
    if (region == nullptr)
        return;

    const List<Villager*>& villagers = region->getVillagers();
    if (villagers.getSize() == 0)
        return;

    for (int i = 0; i < villagers.getSize(); i++) {
        Villager* villager = villagers.at(i);
        if (villager == nullptr)
            continue;

        logbook->log("Hunter " + hunter->getName() + " meets villager " +
                     villager->getName() + " in " + region->getName() + ".");

        if (!probability(60)) {
            logbook->log("Hunter " + hunter->getName() + " decides not to buy from " + villager->getName() + ".");
            continue;
        }

        int goldBefore   = hunter->getGold();
        double lifeBefore = hunter->getLife();

        villager->sell(hunter, 0);

        int goldAfter   = hunter->getGold();
        double lifeAfter = hunter->getLife();

        if (goldAfter < goldBefore) {
            int price = goldBefore - goldAfter;
            logbook->log("Hunter " + hunter->getName() + " buys an item from " +
                         villager->getName() + " for " + to_string(price) + " gold.");
            if (lifeAfter > lifeBefore)
                logbook->log("Hunter " + hunter->getName() + " recovers " +
                             to_string((int)(lifeAfter - lifeBefore)) + " life points after using potion.");
        } else {
            logbook->log("Hunter " + hunter->getName() + " could not buy an item from " +
                         villager->getName() + ".");
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
    while (!checkAdventureEnd())
        executeTurn();
    generateReport();
    logbook->close();
    cout << "Simulation finished. Final report generated in final_report.txt" << endl;
}

void Simulation::executeTurn() {
    currentTurn++;
    logbook->setTurn(currentTurn);
    Region* region = world->getCurrentRegion();
    bool firstVisit = !region->wasVisited();

    if (region == nullptr) {
        finished = true;
        logbook->log("The simulation stopped because there is no current region.");
        return;
    }

    region->isVisited();
    logbook->log("Hunter " + hunter->getName() + " enters " + region->getName() + ".");

    if (firstVisit)
        manageVillagers(region);

    List<Dragon*>& dragons = const_cast<List<Dragon*>&>(region->getDragons());

    for (int i = 0; i < dragons.getSize(); i++) {
        Dragon* dragon = dragons.at(i);
        if (dragon == nullptr || !dragon->isAlive())
            continue;

        double hunterDamage = randomDamage(hunter->calculateDamage());
        dragon->takeDamage(hunterDamage);

        if (hunterDamage == 0) {
            logbook->log("Hunter " + hunter->getName() + " missed the attack!");
        } else {
            logbook->log(hunter->getName() + " attacks " + dragon->getName() +
                         " causing " + to_string((int)hunterDamage) + " damage.");

            if (!dragon->isAlive()) {
                logbook->log(dragon->getName() + " was defeated.");
                int levelBefore = hunter->getLevel();

                hunter->addExperience(dragon->getLevel() * 50.0);

                if (hunter->getLevel() > levelBefore)
                    logbook->log("Hunter levels up! - Maximum life increased by 20");

                int goldReward = dragon->getLevel() * 25;
                hunter->addGold(goldReward);
                logbook->log("Hunter " + hunter->getName() + " earns " +
                             to_string(goldReward) + " gold for defeating " + dragon->getName() + ".");

                if (isFinalDragon(dragon)) {
                    hydraDefeated = true;
                    finished = true;
                }
                continue;
            }
        }

        double dragonDamage = randomDamage(dragon->calculateDamage());
        hunter->takeDamage(dragonDamage);

        if (dragonDamage == 0) {
            logbook->log("Hunter " + hunter->getName() + " evaded " + dragon->getName() + "'s attack!");
        } else {
            logbook->log(dragon->getName() + " attacks " + hunter->getName() +
                         " causing " + to_string((int)dragonDamage) + " damage.");
            if (!hunter->isAlive()) {
                logbook->log("Hunter " + hunter->getName() + " has died.");
                finished = true;
                return;
            }
        }
    }

    List<Object*>& objects = const_cast<List<Object*>&>(region->getObjects());
    int index = 0;

    while (index < objects.getSize()) {
        Object* object = objects.at(index);
        if (object == nullptr) {
            index++;
            continue;
        }

        Weapon* weapon = dynamic_cast<Weapon*>(object);
        if (weapon != nullptr) {
            Object* pickedObject = region->removeObject(index);
            hunter->pickUp(pickedObject);
            logbook->log("Hunter " + hunter->getName() + " picks up weapon " + pickedObject->getName() + ".");
        } else {
            logbook->log("Hunter " + hunter->getName() + " ignores " + object->getName() + ".");
            index++;
        }
    }

    if (!finished) {
        if (regionHasDragonsAlive(region))
            logbook->log("Hunter " + hunter->getName() + " stays in " + region->getName() + " because there are still living dragons.");
        else
            moveToNextRegion(region);
    }
}

bool Simulation::checkAdventureEnd() {
    if (finished)
        return true;
    if (hunter == nullptr || !hunter->isAlive()) {
        finished = true;
        return true;
    }
    if (hydraDefeated) {
        finished = true;
        return true;
    }
    if (world == nullptr || world->getCurrentRegion() == nullptr) {
        finished = true;
        return true;
    }
    return false;
}

void Simulation::generateReport() {
    ofstream report("final_report.txt", ios::out);
    if (!report.is_open())
        throw BaseError("Could not create final_report.txt.");

    report << "===== FINAL REPORT - DRAGON'S LAIR =====" << endl;
    report << "Turns executed: " << currentTurn << endl;
    report << "Logbook file: " << logbook->getPath() << endl;
    report << endl;
    report << "Final hunter status:" << endl;
    report << "Name: "       << hunter->getName()       << endl;
    report << "Life: "       << hunter->getLife() << " / " << hunter->getMaxLife() << endl;
    report << "Level: "      << hunter->getLevel()      << endl;
    report << "Gold: "       << hunter->getGold()       << endl;
    report << "Experience: " << hunter->getExperience() << endl;
    report << endl;
    report << "Result: ";

    if (hydraDefeated)
        report << "Victory. The hunter defeated the Hydra." << endl;
    else if (!hunter->isAlive())
        report << "Defeat. The hunter died during the adventure." << endl;
    else
        report << "Adventure finished. There are no available movements." << endl;

    report.close();
}