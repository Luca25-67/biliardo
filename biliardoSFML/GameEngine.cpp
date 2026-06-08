#include "GameEngine.h"

// ============================================================
//  Costanti schermata
// ============================================================

const float DIAMETRO_PALLINA = 40.0f;
const float LUNG_STECCA = 220.0f;
const float LARGHEZZA_STECCA = 30.0f;


const float PASSO_TASTO = 5.0f;    // pixel per tasti freccia
const float PASSO_ANGOLO = 2.0f;   // gradi per tasti rotazione o/a (orario/antiorario)
const int   RITARDO_MS = 100;      // intervallo tra un frame e l'altro

const int RIGA_TITOLO = 1;
const int COL_TITOLO = 4;

GameEngine::GameEngine(InterfacciaUtente& ui, wstring nomeGiocatore)
    : ui(ui)    // qui GameEngine usa un riferimento a InterfacciaUtente, 
                // quindi nel costruttore è necessario usare la lista di inizializzazione : ui(ui)
{
    this->nomeGiocatore = nomeGiocatore;

    // ── Creazione stecca ─────────────────────────────────────
    // Il gommino è al centro del campo, 
    // stecca diretta in alto (270°),
    // velocità iniziale 0.
    float steccaX = ui.getLarghezza() / 2;
    float steccaY = ui.getAltezza() / 2;
	float steccaVel = 0.0f;
	float steccaAngolo  = 270.0f;

    this->stecca = OggettoMobile(steccaX, steccaY,
        steccaVel, steccaAngolo,
        "./images/stecca.png",  // immagine PNG della stecca (con trasparenza)
        LARGHEZZA_STECCA, LUNG_STECCA);

    // ── Creazione Palla8 ─────────────────────────────────────
    // Centrata al centro del campo, 
    // diretta nella stessa direzione della stecca,
    // velocità iniziale 0.
    float palla8X = ui.getLarghezza() / 2;
    float palla8Y = ui.getAltezza() / 2;
    float palla8Vel = 0.0f;
    float palla8Angolo = steccaAngolo;

    this->palla8 = OggettoMobile(palla8X, palla8Y,
        palla8Vel, palla8Angolo,
        "./images/palla8.png", // immagine PNG dellapalla (con trasparenza)
        DIAMETRO_PALLINA, DIAMETRO_PALLINA); 
}

void GameEngine::run() {
    bool finito = false;

	int larghezzaCampo = ui.getLarghezza();
	int altezzaCampo = ui.getAltezza();
    // ── Game loop ─────────────────────────────────────────────
    while (!finito)
    {
		// lettura tasto senza blocco/attesa: 
        // restituisce -1 se non c'è un tasto premuto
		// Le costanti TASTO_ESC, TASTO_SU, TASTO_GIU, TASTO_SINISTRA, TASTO_DESTRA
        // sono definite in Tastiera.h
        int tasto = ui.leggiTasto();

        // ── Uscita ────────────────────────────────────────────
        if (tasto == TASTO_ESC)
            finito = true;

        // ── Spostamento con frecce ────────────────────
        if (tasto == TASTO_SU)
            stecca.spostaStecca(0.0f, -PASSO_TASTO, larghezzaCampo, altezzaCampo);
        if (tasto == TASTO_GIU)
            stecca.spostaStecca(0.0f, PASSO_TASTO, larghezzaCampo, altezzaCampo);
        if (tasto == TASTO_SINISTRA)
            stecca.spostaStecca(-PASSO_TASTO, 0.0f, larghezzaCampo, altezzaCampo);
        if (tasto == TASTO_DESTRA)
            stecca.spostaStecca(PASSO_TASTO, 0.0f, larghezzaCampo, altezzaCampo);

        if (tasto == 'o') { // ruota in senso orario
            stecca.ruotaImmagine(4.0f);
            stecca.ruota(4.0f);
        }
        if (tasto == 'a') { // ruota in senso antiorario
            stecca.ruotaImmagine(-4.0f);
            stecca.ruota(-4.0f);
        }
        if (tasto == 'c') { // colpisci la palla8 con la stecca e accelera la palla8
            palla8.impostaAngolo(stecca.getAngolo());
            palla8.accelera(20.0f);
        }

		// ad ogni frame, la palla8 rallenta gradualmente fino a fermarsi
        palla8.accelera(-0.1f);

        // ── Spostamento legato alla velocità della pallina ────────────────
        palla8.muoviConRimbalzoBordi(larghezzaCampo, altezzaCampo);

        // ── Rendering di tutta la scena ─────────────────────────────────────────
        
		// prima di disegnare, è necessario pulire il campo
        ui.pulisci();

		// aggiunta dello sfondo (bordo decorativo e titolo)
        aggiungiSfondo();
        // aggiunta della Palla8
        palla8.aggiungiOggettoMobilePallina(ui);
        // aggiunta della Stecca
        stecca.aggiungiOggettoMobileStecca(ui);

		// rendering di tutto ciò che è stato aggiunto
        // al campo (sfondo, pallina, stecca)
        ui.disegna();

		// intervallo tra un frame e l'altro
        ui.sleep(RITARDO_MS);
    }
}

void GameEngine::aggiungiSfondo() {
	// Tappero verde con angolo in alto a sinistra (2,2) 
    // e margine di 2 pixel da ogni lato
    ui.aggiungiRettangolo(Punto(2, 2),
        ui.getLarghezza() - 4, ui.getAltezza() - 4,
        FG_VERDE_I);

    // aggiungi Titolo
    ui.aggiungiTestoAlCentro(RIGA_TITOLO, L"BILIARDO");

    wchar_t info[128];
    // aggiungi info: nome, posizione e direzione palla8
	// riga 2, colonna 2
    swprintf(info, 128,
        L"Giocatore: %ls  |  pos palla8 (%.0f, %.0f)  |  dir palla8 %.0f\u00B0  |  vel palla8 %.1f px/f",
        nomeGiocatore.c_str(),
        palla8.getX(), palla8.getY(),
        palla8.getAngolo(), palla8.getVelocita());
    ui.aggiungiTestoRigCol(Posizione(2, 2), info);

    // aggiungi info: nome, posizione e direzione stecca
	// riga 3, colonna 10
    swprintf(info, 128,
        L"pos stecca (%.0f, %.0f)  |  dir stecca %.0f\u00B0  |  vel stecca %.1f px/f",
        stecca.getX(), stecca.getY(),
        stecca.getAngolo(), stecca.getVelocita());
    ui.aggiungiTestoRigCol(Posizione(3, 10), info);
}
