#include "Logbook.h"

Logbook::Logbook(const string& path) : path(path), currentTurn(0) {
    file.open(path, ios::out);

    if (!file.is_open()) {
        throw FileNotFound(path);
    }
}

void Logbook::setTurn(int turn) {
    currentTurn = turn;
}

void Logbook::log(const string& msg) {
    if (!file.is_open()) {
        throw FileNotFound(path);
    }

    file << "[Turn " << setw(2) << setfill('0') << currentTurn << "] " << msg << endl;
}

void Logbook::close() {
    if (file.is_open()) {
        file.close();
    }
}

string Logbook::getPath() const {
    return path;
}