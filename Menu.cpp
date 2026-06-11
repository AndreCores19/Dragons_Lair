#include "Menu.h"
#include <memory>

Menu::Menu() : basePath("data/") {}

string Menu::buildPath(const string& fileName) const {
    if (basePath.empty())
        return fileName;

    char last = basePath[basePath.size() - 1];

    if (last == '/' || last == '\\')
        return basePath + fileName;

    return basePath + "/" + fileName;
}

bool Menu::fileReadable(const string& path) const {
    ifstream file(path);
    return file.good();
}

void Menu::showWelcome() const {
    cout << "======================================" << endl;
    cout << "           DRAGONS' LAIR              " << endl;
    cout << "======================================" << endl;
    cout << "Welcome to the adventure." << endl;
    cout << "The program will load regions, dragons," << endl;
    cout << "objects, and the hunter from .txt files." << endl;
    cout << endl;
}

void Menu::requestPaths() {
    cout << "Current data path: " << basePath << endl;
    cout << "Expected files:" << endl;
    cout << "- regions.txt" << endl;
    cout << "- dragons.txt" << endl;
    cout << "- objects.txt" << endl;
    cout << "- hunter.txt" << endl;
    cout << "- villagers.txt" << endl;
    cout << endl;

    cout << "Do you want to change the base path? (y/n): ";

    char answer;
    cin >> answer;

    if (answer == 'y' || answer == 'Y') {
        cout << "Enter the new base path: ";
        cin >> basePath;
    }

    cout << endl;
}

void Menu::validateFiles() const {
    const string files[] = {
        "regions.txt",
        "dragons.txt",
        "objects.txt",
        "hunter.txt",
        "villagers.txt",
    };

    for (const string& name : files) {
        string fullPath = buildPath(name);

        if (!fileReadable(fullPath))
            throw FileNotFound(fullPath);
    }
}

void Menu::startSimulation() {
    showWelcome();
    requestPaths();
    validateFiles();

    cout << "Files validated successfully." << endl;
    cout << "Loading world..." << endl;

    unique_ptr<World> world(Reader::readRegions(buildPath("regions.txt")));
    Reader::readDragons(buildPath("dragons.txt"), world.get());
    Reader::readObjects(buildPath("objects.txt"), world.get());
    Reader::readVillagers(buildPath("villagers.txt"), world.get());

    unique_ptr<Hunter> hunter(Reader::readHunter(buildPath("hunter.txt")));
    unique_ptr<Logbook> logbook(new Logbook("logbook.txt"));

    Simulation simulation(world.get(), hunter.get(), logbook.get());
    simulation.run();
}