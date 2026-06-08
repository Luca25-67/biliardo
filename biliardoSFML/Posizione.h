#pragma once

// ============================================================
//  Posizione
//
//  Rappresenta una posizione nel campo tramite:
//  - riga
//  - colonna
//
//  Serve per passare coordinate ai metodi senza usare
//  coppie di interi separate.
// ============================================================

class Posizione {
public:
    Posizione(int riga, int colonna);

    int getRiga();
    int getColonna();

private:
    int riga;
    int colonna;
};

