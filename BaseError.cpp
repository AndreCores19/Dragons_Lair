//
// Created by andre on 6/6/2026.
//

#include "BaseError.h"

BaseError::BaseError(string message) {
    this->message = message;
}

BaseError::BaseError() {
    message = "Invalid Operation";
}

string BaseError::getMessage() {
    return message;
}

const char* BaseError::what() const noexcept {
    return message.c_str();
}