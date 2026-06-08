//
// Created by Gerald Quintero on 7/6/26.
//

#ifndef DRAGONS_LAIR_BITACORA_H
#define DRAGONS_LAIR_BITACORA_H
#include <fstream>
#include <string>
#include <iomanip>
#include "FileNotFound.h"
using namespace std;

class Bitacora {
private:
    ofstream archivo;
    string ruta;
    int turnoActual;

public:
    Bitacora(const string& ruta);

    void setTurno(int turno);
    void registrar(const string& msg);
    void cerrar();

    string getRuta() const;
};


#endif //DRAGONS_LAIR_BITACORA_H
