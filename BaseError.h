//
// Created by andre on 6/6/2026.
//

#ifndef DRAGONS_LAIR_BASEERROR_H
#define DRAGONS_LAIR_BASEERROR_H
#include <iostream>
#include <exception>
using namespace std;

class BaseError : public exception {
protected:
    string message;
public:
    BaseError(string);
    BaseError();
    string getMessage();
    const char* what() const noexcept override;
};



#endif //DRAGONS_LAIR_BASEERROR_H