//
// Created by Gerald Quintero on 7/6/26.
//

#include "Bitacora.h"

Bitacora::Bitacora(const string& ruta) : ruta(ruta), turnoActual(0) {
    archivo.open(ruta, ios::out);

    if (!archivo.is_open()) {
        throw FileNotFound(ruta);
    }
}

void Bitacora::setTurno(int turno) {
    turnoActual = turno;
}

void Bitacora::registrar(const string &msg) {
    if (!archivo.is_open()) {
        throw FileNotFound(ruta);
    }

    archivo << "[Turno " << setw(2) << setfill('0') << turnoActual << "] " << msg << endl;
}

void Bitacora::cerrar() {
    if (archivo.is_open()) {
        archivo.close();
    }
}

string Bitacora::getRuta() const {
    return ruta;
}