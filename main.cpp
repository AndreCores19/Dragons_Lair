#include <iostream>
#include <exception>
#include "Menu.h"
using namespace std;

int main() {
    try {
        Menu menu;
        menu.iniciarSimulacion();
    } catch (const exception& e) {
        cerr << "Error fatal: " << e.what() << endl;
        return 1;
    }
    return 0;
}