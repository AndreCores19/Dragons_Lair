//
// Created by Gerald Quintero on 8/6/26.
//

#ifndef DRAGONS_LAIR_MENU_H
#define DRAGONS_LAIR_MENU_H
#include <iostream>
#include <string>
#include "FileNotFound.h"
#include "Reader.h"
#include "Simulation.h"
#include "Logbook.h"
using namespace std;

class Menu {
private:
    string rutaBase;
    string construirRuta(const string& nombreArchivo) const;
    bool archivoLegible(const string& ruta) const;

public:
    Menu();

    void mostrarBienvenida() const;
    void solicitarRutas();
    void validarArchivos() const;
    void iniciarSimulacion();
};


#endif //DRAGONS_LAIR_MENU_H
