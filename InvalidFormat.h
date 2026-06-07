//
// Created by andre on 6/6/2026.
//

#ifndef DRAGONS_LAIR_INVALIDFORMAT_H
#define DRAGONS_LAIR_INVALIDFORMAT_H
#include "BaseError.h"
using namespace std;

class InvalidFormat : public BaseError {
public:
    InvalidFormat(string message) : BaseError("Invalid Format: " + message) {}
};



#endif //DRAGONS_LAIR_INVALIDFORMAT_H