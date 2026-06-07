//
// Created by andre on 6/6/2026.
//

#ifndef DRAGONS_LAIR_READER_H
#define DRAGONS_LAIR_READER_H
#include <sstream>
#include <fstream>
#include "FileNotFound.h"
#include "InvalidFormat.h"
#include "World.h"
#include "Hunter.h"
using namespace std;

class Reader {
public:
    static World* readRegions(const string&);
    static void readDragons(const string&, World*);
    static void readObjects(const string&, World*);
    static Hunter* readHunter(const string&);
    static string trim(const string&);
};


#endif //DRAGONS_LAIR_READER_H