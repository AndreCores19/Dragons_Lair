//
// Created by andre on 6/6/2026.
//

#include "Reader.h"

World* Reader::readRegions(const string& route) {
    ifstream file(route);
    if (!file.is_open()) {
        throw FileNotFound(route);
    }
    World* world = new World();
    string line;
    List<string> connections;

    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string name, description, connectionStr;
        getline(ss, name, '|');
        getline(ss, description, '|');
        getline(ss, connectionStr);

        Region* r = new Region(trim(name), trim(description));
        stringstream sc(connectionStr);
        string connect;
        while (getline(sc, connect, ','))
            r->addConnection(trim(connect));

        world->addRegion(r);
    }
    file.close();
    return world;
}

void Reader::readDragons(const string& route, World* world) {
    ifstream file(route);
    if (!file.is_open()) {
        throw FileNotFound(route);
    }
    string line;
    getline(file, line); // skip header
    while (getline(file, line)) {
        stringstream ss(line);
        string name, type, HpStr, damageStr, region;
        getline(ss, type,    '|');
        getline(ss, name,  '|');
        getline(ss, HpStr, '|');
        getline(ss, damageStr, '|');
        getline(ss, region);

        type = trim(type);
        name = trim(name);
        region = trim(region);
        int hp = stoi(trim(HpStr));
        int damage = stoi(trim(damageStr));

        //Dragon *dragon = DragonFactory::create(type, name, hp, damage, region);
        //world->addDragonToRegion(region, dragon);
    }

}

void Reader::readObjects(const string& route, World* world) {
    ifstream file(route);
    if (!file.is_open()) {
        throw FileNotFound(route);
    }
    string line;
    getline(file, line); //skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string type, name, valueStr, Str, region;
    }

}

Hunter* Reader::readHunter(const string& route) {

}

string Reader::trim(const string& s) {
    int start = s.find_first_not_of(" \t\r\n");
    int end = s.find_last_not_of(" \t\r\n");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}
