#pragma once

#include <SFML/Graphics.hpp>
#include <queue>
#include <string>
#include "Campo.h"
#include "Posizione.h"

using namespace std;

// ============================================================
//  Costanti per i tasti speciali
//  I tasti freccia e funzione impostano this->tastoSpeciale = true.
// ============================================================

const int TASTO_NESSUNO = -1;   // nessun tasto premuto (non bloccante)
const int TASTO_INVIO = 13;   // Enter
const int TASTO_BACKSPACE = 8;   // Backspace
const int TASTO_SPAZIO = 32;   // Barra spaziatrice
const int TASTO_ESC = 27;   // Escape

// Frecce
const int TASTO_SU = 72;
const int TASTO_GIU = 80;
const int TASTO_SINISTRA = 75;
const int TASTO_DESTRA = 77;

// Tasti funzione
const int TASTO_F1 = 59;
const int TASTO_F2 = 60;
const int TASTO_F3 = 61;
const int TASTO_F4 = 62;
const int TASTO_F5 = 63;
const int TASTO_F6 = 64;
const int TASTO_F7 = 65;
const int TASTO_F8 = 66;
const int TASTO_F9 = 67;
const int TASTO_F10 = 68;

// Lunghezza massima per la lettura di stringhe
const int MAX_LUNGHEZZA_TESTO = 64;

// ============================================================
//  Costanti di layout per la visualizzazione dell'input
//  (coordinate in pixel; la Y della risposta è sotto la domanda)
// ============================================================
const float INPUT_Y_DOMANDA = 60.0f;  // pixel dall'alto
const float INPUT_Y_RISPOSTA = 100.0f;
const float INPUT_X_START = 20.0f;    // pixel da sinistra

// ============================================================
//  Tastiera — versione SFML compatibile con InterfacciaUtente
//
//  Responsabilità:
//  - leggere tasti
//  - leggere stringhe
//  - leggere interi
//  - usare Campo solo quando serve mostrare domanda/risposta

//  Due modalità:
//    NON BLOCCANTE — game loop (leggi, tastoPremuto)
//    BLOCCANTE     — menu e input  (leggiBloccante, leggiStringa, leggiInt)

// ============================================================

class Tastiera {
public:
    Tastiera(Campo& campo);
    ~Tastiera();

    // ── Input NON BLOCCANTE — game loop ─────────────────────

    // Restituisce TASTO_NESSUNO se non c'è nessun tasto in attesa.
    int leggi();
    // Restituisce true se esiste almeno un tasto in attesa.
    bool tastoPremuto();
    // Svuota la coda interna e tutti gli eventi pendenti.
    void svuotaBuffer();

    // ── Input BLOCCANTE — menu e schermate statiche ──────────

    // Input bloccante: blocca finché non viene premuto un tasto gestito.
    int leggiBloccante();
    // Lettura testo semplice fino alla pressione di INVIO
    wstring leggiTesto(bool eco = true);

    // ── Input con visualizzazione su campo ───────────────────

    // Mostra 'domanda' sul campo con eco in tempo reale.
    // Copia il risultato in 'destinazione' (wchar_t*).
    wstring leggiStringa(
        Campo& campo,
        Posizione posizioneRisposta,
        Posizione posizioneDomanda,
        wstring domanda
    );

    // Come leggiStringa, ma restituisce un intero nel range [minVal, maxVal].
    // Se l'utente non inserisce nulla restituisce valDefault.
    int leggiIntero(
        Campo& campo,
        Posizione posizioneRisposta,
        Posizione posizioneDomanda,
        wstring domanda,
        int valDefault,
        int minVal,
        int maxVal
    );

    // restituisce il valore dell'ultimo tasto premuto dall'utente
    int getUltimoTasto();
    // Restituisce true se è un tasto speciale
    bool isSpeciale();
    // Restituisce true se il codice corrisponde a una freccia.
    bool isFreccia(int codice);

private:
    // ── Coda interna degli eventi tastiera ────────────────────
    queue<int> codaCodici;

    // ── Stato dell'ultimo tasto letto ─────────────────────────
    int ultimoTasto;
    bool tastoSpeciale;

    // ── Buffer testo  ───────────────────────────────────
    wstring bufferTesto;

    // ── Riferimento al campo (per eventi e disegno) ───────────
    Campo& campo;

    // ── Helper privati ────────────────────────────────────────

    // Mappa sf::Keyboard::Key → codice intero TASTO_*.
    int mappaTasto(sf::Keyboard::Key key, bool shift);
    // Drena pollEvent() e inserisce i KeyPressed nella coda.
    void aggiornaEventi();
};
