//
// Created by Gerald Quintero on 7/6/26.
//

#include "Logbook.h"

Logbook::Logbook(const string& ruta) : ruta(ruta), turnoActual(0) {
    archivo.open(ruta, ios::out);

    if (!archivo.is_open()) {
        throw FileNotFound(ruta);
    }
}

void Logbook::setTurno(int turno) {
    turnoActual = turno;
}

void Logbook::registrar(const string &msg) {
    if (!archivo.is_open()) {
        throw FileNotFound(ruta);
    }

    archivo << "[Turn " << setw(2) << setfill('0') << turnoActual << "] " << msg << endl;
}

void Logbook::cerrar() {
    if (archivo.is_open()) {
        archivo.close();
    }
}

string Logbook::getRuta() const {
    return ruta;
}