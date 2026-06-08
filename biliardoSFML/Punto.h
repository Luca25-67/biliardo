#pragma once

// ============================================================
//  Posizione
//
//  Rappresenta una posizione nel campo tramite:
//  - pixel x
//  - pixel y
//
//  Serve per passare coordinate ai metodi senza usare
//  coppie di interi separate.
// ============================================================

class Punto {
public:
    Punto(int pixX, int pixY);

    int getX();
    int getY();

private:
    int x;
    int y;
};

