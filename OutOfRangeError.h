//
// Created by andre on 6/6/2026.
//

#ifndef DRAGONS_LAIR_OUTOFRANGEERROR_H
#define DRAGONS_LAIR_OUTOFRANGEERROR_H
#include "BaseError.h"
using namespace std;

class OutOfRangeError : public BaseError {
public:
    OutOfRangeError(int index, int size)
        : BaseError("Index out of bounds: index=" + std::to_string(index) + ", size=" + std::to_string(size)) {}
};


#endif //DRAGONS_LAIR_OUTOFRANGEERROR_H