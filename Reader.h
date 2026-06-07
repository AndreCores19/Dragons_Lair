//
// Created by andre on 6/6/2026.
//

#ifndef DRAGONS_LAIR_READER_H
#define DRAGONS_LAIR_READER_H
#include <sstream>
#include "World.h"
//#include "Hunter.h"
using namespace std;

class Reader {
public:
    static void readRegions(const string& route);
    static void readDragons(const string& route, World *world);
    static void readObjects(const string& route, World *world);
    //static Hunter* readHunter(const string& route);

};


#endif //DRAGONS_LAIR_READER_H