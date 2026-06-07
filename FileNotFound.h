//
// Created by andre on 6/6/2026.
//

#ifndef DRAGONS_LAIR_FILENOTFOUND_H
#define DRAGONS_LAIR_FILENOTFOUND_H
#include "BaseError.h"
using namespace std;

class FileNotFound : public BaseError {
public:
    FileNotFound(string filename) : BaseError("File not found: " + filename) {}
};



#endif //DRAGONS_LAIR_FILENOTFOUND_H