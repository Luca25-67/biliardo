#include "Posizione.h"

Posizione::Posizione(int riga, int colonna) {
    this->riga = riga;
    this->colonna = colonna;
}

int Posizione::getRiga() {
    return riga;
}

int Posizione::getColonna() {
    return colonna;
}