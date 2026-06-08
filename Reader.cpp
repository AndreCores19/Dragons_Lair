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
    getline(file,line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string type, name, valueStr, extraStr, region;
        getline(ss,type,'|');
        getline(ss,name,'|');
        getline(ss,valueStr,'|');
        getline(ss,extraStr,'|');
        getline(ss,region);

        type = trim(type);
        name = trim(name);
        region = trim(region);
        int value = stoi(trim(valueStr));
        double extra = stod(trim(extraStr));

        Object* obj = nullptr;
        if (type == "weapon")
            obj = new Weapon(name, value, extra);
        else if (type == "potion")
            obj = new Potion(name, value, extra);
        else if (type == "armor")
            obj = new Armor(name, value, extra);
        else
            throw InvalidFormat("Unknown object type: " + type);

        world->addObjectToRegion(region, obj);
    }
    file.close();
}

Hunter* Reader::readHunter(const string& route) {
    ifstream file(route);
    if (!file.is_open())
        throw FileNotFound(route);

    string name, line;
    double health = 0;
    int maxHealth = 0, level = 0, gold = 0;

    while (getline(file,line)) {
        if (line.rfind("name:",0) == 0)
            name = trim(line.substr(7));

        else if (line.rfind("health:",0) == 0)
            health = stod(trim(line.substr(5)));

        else if (line.rfind("maxHealth:",0) == 0)
            maxHealth = stoi(trim(line.substr(8)));

        else if (line.rfind("level:",0) == 0)
            level = stoi(trim(line.substr(6)));

        else if (line.rfind("Gold:",0) == 0)
            gold = stoi(trim(line.substr(4)));
    }
    file.close();
    return new Hunter(name, health, maxHealth, level, gold);

}

string Reader::trim(const string& s) {
    int start = s.find_first_not_of(" \t\r\n");
    int end = s.find_last_not_of(" \t\r\n");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}
