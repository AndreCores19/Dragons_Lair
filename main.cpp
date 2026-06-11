#include <iostream>
#include <exception>
#include <cstdlib>
#include <ctime>
#include "Menu.h"
using namespace std;

int main() {

    srand(time(nullptr));

    try
    {
        Menu menu;
        menu.startSimulation();
    } catch (const exception& e) {
        cerr << "Fatal Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}