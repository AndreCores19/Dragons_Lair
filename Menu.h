#ifndef DRAGONS_LAIR_MENU_H
#define DRAGONS_LAIR_MENU_H
#include <iostream>
#include <string>
#include "FileNotFound.h"
#include "Reader.h"
#include "Simulation.h"
#include "Logbook.h"
using namespace std;

class Menu {
private:
    string basePath;
    string buildPath(const string& fileName) const;
    bool fileReadable(const string& path) const;

public:
    Menu();

    void showWelcome() const;
    void requestPaths();
    void validateFiles() const;
    void startSimulation();
};

#endif //DRAGONS_LAIR_MENU_H