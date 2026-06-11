#ifndef DRAGONS_LAIR_LOGBOOK_H
#define DRAGONS_LAIR_LOGBOOK_H
#include <fstream>
#include <string>
#include <iomanip>
#include "FileNotFound.h"
using namespace std;

class Logbook {
private:
    ofstream file;
    string path;
    int currentTurn;

public:
    Logbook(const string& path);

    void setTurn(int turn);
    void log(const string& msg);
    void close();

    string getPath() const;
};

#endif //DRAGONS_LAIR_LOGBOOK_H