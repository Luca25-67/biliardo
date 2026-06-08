#pragma once
#include "OggettoMobile.h"
#include "InterfacciaUtente.h"
#include <string>

using namespace std;

const int LARGHEZZA_FINESTRA = 900;
const int ALTEZZA_FINESTRA = 600;

// ============================================================
//  GameEngine
//
//  Classe che gestisce il test del blackjack.
//  Per ora non usa ancora le classi Carta, Mazzo, Mano.
//  Simula solo il ciclo "dammi carta?".
// ============================================================

class GameEngine {
public:
    GameEngine(InterfacciaUtente& ui, wstring nomeGiocatore);

    void run();

private:
    InterfacciaUtente& ui;
    wstring nomeGiocatore;
    OggettoMobile stecca;
    OggettoMobile palla8;
    void aggiungiSfondo();
};
