#include "Buca.h"
#include <cmath>
using namespace std;

Buca::Buca() {
    this->x = 0;
    this->y = 0;
    this->raggio = 10;
    this->piena = false;
}

Buca::Buca(int x, int y, int r) {
    this->x = x;
    this->y = y;
    this->raggio = r;
    this->piena = false;
}

int Buca::getX() {
    return x;
}

int Buca::getY() {
    return y;
}

int Buca::getRaggio() {
    return raggio;
}

bool Buca::isPiena() {
    return piena;
}

bool Buca::controllaIngresso(int px, int py) {
    float dx = px - x;
    float dy = py - y;
    float dist = sqrt(dx * dx + dy * dy);

    if (dist <= raggio) {
        piena = true;
        return true;
    }
    return false;
}

string Buca::toString() {
    string s = "";
    s += "Buca in (" + to_string(x) + ", " + to_string(y) + ")";
    s += " raggio: " + to_string(raggio) + " ";

    if (piena) {
        s += "stato: piena";
    }
    else {
        s += "stato: vuota";
    }

    return s;
}