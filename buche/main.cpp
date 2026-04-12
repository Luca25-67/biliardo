#include <iostream>
#include "Buca.h"
using namespace std;

void main() {
    Buca b1(50, 50, 10);

    cout << b1.toString() << endl;

    int px, py;
    cout << "Inserisci coordinate pallina (x y): ";
    cin >> px >> py;

    if (b1.controllaIngresso(px, py)) {
        cout << "La pallina e entrata nella buca!" << endl;
    }
    else {
        cout << "La pallina NON ee entrata." << endl;
    }

    cout << b1.toString() << endl;
}