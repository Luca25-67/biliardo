#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Posizione.h"
#include "Punto.h"

using namespace std;

const int LARGHEZZA_CELLA = 20;
const int ALTEZZA_CELLA = 24;

// costanti con valori centro, alto, basso, sinistra, destra
const int CENTRO = 0;
const int ALTO = 1;
const int BASSO = -1;
const int SINISTRA = -2;
const int DESTRA = 2;

// ============================================================
// Palette colori (equivalente Windows Terminal)
// ============================================================

// ── Colori primo piano ────────────────────────────────────────
const sf::Color FG_NERO = sf::Color(12, 12, 12);
const sf::Color FG_BLU = sf::Color(0, 55, 218);
const sf::Color FG_VERDE = sf::Color(19, 161, 14);
const sf::Color FG_CIANO = sf::Color(58, 150, 221);
const sf::Color FG_ROSSO = sf::Color(197, 15, 31);
const sf::Color FG_MAGENTA = sf::Color(136, 23, 152);
const sf::Color FG_GIALLO = sf::Color(193, 156, 0);
const sf::Color FG_BIANCO = sf::Color(204, 204, 204);

const sf::Color FG_GRIGIO = sf::Color(118, 118, 118);
const sf::Color FG_BLU_I = sf::Color(59, 120, 255);
const sf::Color FG_VERDE_I = sf::Color(22, 198, 12);
const sf::Color FG_CIANO_I = sf::Color(97, 214, 214);
const sf::Color FG_ROSSO_I = sf::Color(231, 72, 86);
const sf::Color FG_MAGENTA_I = sf::Color(180, 0, 158);
const sf::Color FG_GIALLO_I = sf::Color(249, 241, 165);
const sf::Color FG_BIANCO_I = sf::Color(255, 255, 255);

// ── Colori sfondo ─────────────────────────────────────────────
const sf::Color BG_NERO = sf::Color(12, 12, 12);
const sf::Color BG_BLU = sf::Color(0, 55, 218);
const sf::Color BG_VERDE = sf::Color(19, 161, 14);
const sf::Color BG_CIANO = sf::Color(58, 150, 221);
const sf::Color BG_ROSSO = sf::Color(197, 15, 31);
const sf::Color BG_MAGENTA = sf::Color(136, 23, 152);
const sf::Color BG_GIALLO = sf::Color(193, 156, 0);
const sf::Color BG_BIANCO = sf::Color(204, 204, 204);

const sf::Color BG_GRIGIO = sf::Color(118, 118, 118);
const sf::Color BG_BLU_I = sf::Color(59, 120, 255);
const sf::Color BG_VERDE_I = sf::Color(22, 198, 12);
const sf::Color BG_CIANO_I = sf::Color(97, 214, 214);
const sf::Color BG_ROSSO_I = sf::Color(231, 72, 86);
const sf::Color BG_MAGENTA_I = sf::Color(180, 0, 158);
const sf::Color BG_GIALLO_I = sf::Color(249, 241, 165);
const sf::Color BG_BIANCO_I = sf::Color(255, 255, 255);

// ── Alias semantici ───────────────────────────────────────────
const sf::Color FG_ARANCIONE = FG_ROSSO_I;
const sf::Color FG_ORO = FG_GIALLO;
const sf::Color FG_DEFAULT = FG_BIANCO;
const sf::Color BG_DEFAULT = BG_NERO;
const sf::Color COLORE_DEFAULT = FG_BIANCO;

// ============================================================
//  Costanti matematiche
// ============================================================
const double PIGRECO = 3.14159265358979323846;

// ============================================================
//  Campo — canvas SFML per giochi con coordinate pixel
//
//  Espone metodi di disegno diretto (sprite, forme, testo)
//  in coordinate float (pixel).
//
//  Ciclo tipico per frame:
//      campo.pulisci();          // cancella con coloreSfondo
//      ... disegna oggetti ...
//      campo.disegna();          // mostra sulla finestra
// ============================================================

class Campo {
public:
    // ── Costruttore / Distruttore ─────────────────────────────

    // Crea la finestra SFML e carica il font.
    // Parametri:
    //   larghezzaPx  : larghezza finestra in pixel
    //   altezzaPx    : altezza  finestra in pixel
    //   titolo       : titolo della finestra
    //   fontPath     : percorso al file .ttf/.otf
    //   dimFont      : dimensione del font in punti
    //   coloreSfondo : colore usato da pulisci()
    Campo(
        int larghezzaPx,
        int altezzaPx,
        wstring titolo,
        string fontPath = "font.ttf",
        int dimFont = 18,
        sf::Color sfondo = BG_NERO
    );

    // Chiude la finestra SFML.
    ~Campo();

    // ── Ciclo di rendering ────────────────────────────────────

    // Cancella il contenuto della finestra con il colore di sfondo.
    // Da chiamare all'inizio di ogni frame.
    void pulisci();

    // Presenta il frame corrente sulla finestra.
    // Da chiamare alla fine di ogni frame.
    void disegna();

    // -─ Metodi di disegno ──────────────────────────────────────

    void aggiungiTesto(Punto punto, wstring testo);
    void aggiungiTestoRigCol(Posizione posizione, wstring testo);
    void aggiungiTestoAlCentro(int pixY, wstring testo);
    void aggiungiTestoAlCentroRigCol(int riga, wstring testo);

    void aggiungiNumero(Punto punto, int numero);
    void aggiungiNumeroRigCol(Posizione posizione, int numero);
    void aggiungiSimbolo(Punto punto, wchar_t simbolo);
    void aggiungiSimboloRigCol(Posizione posizione, wchar_t simbolo);

    void aggiungiLinea(Punto puntoInizio,
        Punto puntoFine,
        sf::Color colore,
        float spessore);
    void aggiungiLineaRigCol(Posizione posizioneInizio,
        Posizione posizioneFine,
        sf::Color colore,
        float spessore);

    void aggiungiCerchio(Punto centro,
        float raggio,
        sf::Color colore);
    void aggiungiCerchioRigCol(Posizione centro,
        float raggio,
        sf::Color colore);

    // Cerchio vuoto (solo bordo) con centro (centro).
    void aggiungiCerchioVuoto(Punto centro,
        float raggio,
        sf::Color colore,
        float spessore = 1.0f);
    void aggiungiCerchioVuotoRigCol(Posizione centro,
        float raggio,
        sf::Color colore,
        float spessore = 1.0f);

    // Rettangolo pieno, verticeAltoSinistra è il vertice in alto a sinistra.
    void aggiungiRettangolo(Punto verticeAltoSinistra,
        int larghezza, int altezza,
        sf::Color colore);
    void aggiungiRettangoloRigCol(Posizione verticeAltoSinistra,
        int larghezza, int altezza,
        sf::Color colore);

    // Rettangolo vuoto (solo bordo).
    void aggiungiRettangoloVuoto(Punto verticeAltoSinistra,
        int larghezza, int altezza,
        sf::Color colore,
        float spessore = 1.0f);
    void aggiungiRettangoloVuotoRigCol(Posizione verticeAltoSinistra,
        int larghezza, int altezza,
        sf::Color colore,
        float spessore = 1.0f);

	// Immagine (sprite) contenuta nel file nomeImmagine, scalata con scalaX, scalaY
    // ruotata di angolo rispetto al punto che può essere il centro o
    // il punto in alto a sinistra.
    void aggiungiImmagine(Punto punto, string nomeImmagine, float scalaX = 1.0f, float scalaY = 1.0f, float angolo = 0.0f, int puntoRotaz = CENTRO);
    void aggiungiImmagineRigCol(Posizione posizione, string nomeImmagine, float scalaX = 1.0f, float scalaY = 1.0f, float angolo = 0.0f, int puntoRotaz = CENTRO);

	void ruota(float angoloDeg);
    void cancellaArea(Punto punto,
        int larghezzaPx,
        int altezzaPx);
    void cancellaAreaRigCol(Posizione posizione,
        int larghezza,
        int altezza);


    // ── Stato finestra ────────────────────────────────────────

    int getLarghezza();
    int getLarghezzaRigCol();
    int getAltezza();
    int getAltezzaRigCol();
    bool isAperta();

    // ── Gestione eventi (usata da Tastiera) ───────────────────

    // Versione non bloccante: restituisce true se c'è un evento,
    // e lo copia in 'ev'. Deve essere chiamata nel game loop
    // per gestire sf::Event::Closed e simili.
    bool pollEvent(sf::Event& ev);

    // Versione bloccante: attende fino al prossimo evento.
    // Usata da Tastiera nei menu e nell'input di testo.
    bool waitEvent(sf::Event& ev);

private:
    // ── SFML ─────────────────────────────────────────────────
    sf::RenderWindow finestra;
    sf::Font font;
    int dimFont;
    sf::Color coloreSfondo;

    int larghezzaPx;
    int altezzaPx;
	float angoloRotazione;

    // ── Helper interni ────────────────────────────────────────

    // Carica il font dal percorso indicato; in caso di errore
    // tenta i percorsi di sistema più comuni.
    void caricaFont(string fontPath);

    float colonnaToX(int colonna);
    float rigaToY(int riga);
};
