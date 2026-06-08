#include "Campo.h"
#include "Tastiera.h"
#include "InterfacciaUtente.h"
#include "GameEngine.h"

// ============================================================
//  Costanti di gioco
// ============================================================

const int RIGA_TITOLO_MAIN = 1;

const int RIGA_DOMANDA_NOME = 20;
const int COL_DOMANDA_NOME = 4;

const int RIGA_RISPOSTA_NOME = 22;
const int COL_RISPOSTA_NOME = 4;

// ============================================================
//  main
// ============================================================

int main()
{
    // ── Campo e tastiera ──────────────────────────────────────
    // creo il Campo su cui disegnare
    Campo campo(LARGHEZZA_FINESTRA, ALTEZZA_FINESTRA,
        L"Biliardo — test",
        "C:/Windows/Fonts/seguisym.ttf");   // glifi Unicode
    // creo la Tastiera da cui ricevere l'input dell'utente
    Tastiera tastiera(campo);
    // inserisco Campo e Tastiera nella InterfacciaUtente
    InterfacciaUtente ui(campo, tastiera);

    // ------------------------------------------------------------
    // Richiesta nome giocatore
    // ------------------------------------------------------------
    wstring nomeGiocatore;

    nomeGiocatore = ui.leggiStringa(
        Posizione(RIGA_RISPOSTA_NOME, COL_RISPOSTA_NOME),
        Posizione(RIGA_DOMANDA_NOME, COL_DOMANDA_NOME),
        L"Come ti chiami?"
    );

    if (nomeGiocatore == L"") {
        nomeGiocatore = L"Giocatore";
    }

    // ------------------------------------------------------------
    // Saluto al giocatore e Schermata istruzioni
    // ------------------------------------------------------------

    ui.pulisci();

    ui.aggiungiTestoAlCentroRigCol(RIGA_TITOLO_MAIN, L"BILIARDO - TEST INTERFACCIA");

    ui.aggiungiTestoAlCentroRigCol(RIGA_DOMANDA_NOME - 5, L"Benvenuto " + nomeGiocatore + L" !");
    ui.aggiungiTestoAlCentroRigCol(RIGA_DOMANDA_NOME - 3, L"Frecce    \u2192  sposta stecca SU/GIU/DESTRA/SINISTRA di 10 px");
    ui.aggiungiTestoAlCentroRigCol(RIGA_DOMANDA_NOME - 2, L"'o' e 'a' \u2192  ruota orario e antiorario");
    ui.aggiungiTestoAlCentroRigCol(RIGA_DOMANDA_NOME - 1, L"'c' \u2192  colpisci la pallina");
    ui.aggiungiTestoAlCentroRigCol(RIGA_DOMANDA_NOME, L"premi ESC per terminare");
    ui.aggiungiTestoAlCentroRigCol(RIGA_DOMANDA_NOME + 1, L"Premi un tasto per iniziare a giocare");
    
    ui.disegna();

    ui.leggiTastoBloccante();

    // ------------------------------------------------------------
    // Avvio GameEngine
    // ------------------------------------------------------------

    GameEngine gioco(ui, nomeGiocatore);
    gioco.run();

    // ------------------------------------------------------------
    // Saluto finale
    // ------------------------------------------------------------

    ui.pulisci();

    ui.aggiungiTestoAlCentro(RIGA_TITOLO_MAIN, L"FINE TEST BILIARDO");

    ui.aggiungiTestoRigCol(Posizione(8, 8), L"Ciao ");
    ui.aggiungiTestoRigCol(Posizione(8, 14), nomeGiocatore);

    ui.aggiungiTestoRigCol(Posizione(14, 8), L"Premi ESC per terminare.");

    ui.disegna();

    // ------------------------------------------------------------
    // Attesa del tasto ESC ogni altro tasto non ha effetto
    // ------------------------------------------------------------
    int tasto;
    do {
        tasto = ui.leggiTastoBloccante();
    } while (campo.isAperta() && !ui.isEsc(tasto));

    return 0;
}