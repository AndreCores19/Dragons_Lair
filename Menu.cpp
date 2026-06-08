//
// Created by Gerald Quintero on 8/6/26.
//

#include "Menu.h"
#include <memory>

Menu::Menu() : rutaBase("data/") {}

string Menu::construirRuta(const string& nombreArchivo) const {
    if (rutaBase.empty()) {
        return nombreArchivo;
    }

    char ultimo = rutaBase[rutaBase.size() - 1];

    if (ultimo == '/' || ultimo == '\\') {
        return rutaBase + nombreArchivo;
    }

    return rutaBase + "/" + nombreArchivo;
}

bool Menu::archivoLegible(const string& ruta) const {
    ifstream archivo(ruta);
    return archivo.good();
}

void Menu::mostrarBienvenida() const {
    cout << "======================================" << endl;
    cout << "           DRAGON'S LAIR              " << endl;
    cout << "======================================" << endl;
    cout << "Welcome to the adventure." << endl;
    cout << "The program will load regions, dragons," << endl;
    cout << "objects, and the hunter from .txt files." << endl;
    cout << endl;
}

void Menu::solicitarRutas() {
    cout << "Current data path: " << rutaBase << endl;
    cout << "Expected files:" << endl;
    cout << "- regions.txt" << endl;
    cout << "- dragons.txt" << endl;
    cout << "- objects.txt" << endl;
    cout << "- hunter.txt" << endl;
    cout << endl;

    cout << "Do you want to change the base path? (y/n): ";

    char respuesta;
    cin >> respuesta;

    if (respuesta == 'y' || respuesta == 'Y') {
        cout << "Enter the new base path: ";
        cin >> rutaBase;
    }

    cout << endl;
}

void Menu::validarArchivos() const {
    const string archivos[] = {
        "regions.txt",
        "dragons.txt",
        "objects.txt",
        "hunter.txt"
    };

    for (const string& nombre : archivos) {
        string rutaCompleta = construirRuta(nombre);

        if (!archivoLegible(rutaCompleta)) {
            throw FileNotFound(rutaCompleta);
        }
    }
}

void Menu::iniciarSimulacion() {
    mostrarBienvenida();
    solicitarRutas();

    validarArchivos();

    cout << "Files validated successfully." << endl;
    cout << "Loading world..." << endl;

    unique_ptr<World> mundo(Reader::readRegions(construirRuta("regions.txt")));
    Reader::readDragons(construirRuta("dragons.txt"), mundo.get());
    Reader::readObjects(construirRuta("objects.txt"), mundo.get());

    unique_ptr<Hunter> cazador(Reader::readHunter(construirRuta("hunter.txt")));
    unique_ptr<Bitacora> bitacora(new Bitacora("bitacora.txt"));

    Simulacion simulacion(mundo.get(), cazador.get(), bitacora.get());
    simulacion.run();
}