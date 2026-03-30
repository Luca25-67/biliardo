#include <iostream>
#include "asta.h"
using namespace std;

void main() {
    Asta stecca(1, 10);

    cout << "prima: " << stecca.toString() << endl;

    stecca.muovi(3, 5);

    cout << "dopo il movimento: " << stecca.toString() << endl;

}