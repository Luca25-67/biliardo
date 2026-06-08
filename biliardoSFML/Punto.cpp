#include "Punto.h"

Punto::Punto(int pixX, int pixY) {
    this->x = pixX;
    this->y = pixY;
}

int Punto::getX() {
    return x;
}

int Punto::getY() {
    return y;
}