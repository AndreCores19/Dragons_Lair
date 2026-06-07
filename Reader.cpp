//
// Created by andre on 6/6/2026.
//

#include "Reader.h"

void Reader::readRegions(const string& route) {
    ifstream file(route);
    if (!file.is_open()) {
        throw FileNotFound(route);
    }
    World* world = new World();
    string line;
    List<string> connections;

    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string name, description, connectionStr;
        getline(ss, name, '|');
        getline(ss, description, '|');
        getline(ss, connectionStr);

        Region* r = new Region(trim(name), trim(description));

    }

}

void Reader::readDragons(const string& route, World* world) {

}

void Reader::readObjects(const string& route, World* world) {

}

Hunter* Reader::readHunter(const string& route) {

}

string Reader::trim(const string& s) {
    int start = s.find_first_not_of(" \t\r\n");
    int end = s.find_last_not_of(" \t\r\n");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}
