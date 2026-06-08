#pragma once
#include "InterfacciaUtente.h"

// ============================================================
//  OGGETTO MOBILE — versione con pixel
//
// Posizione e velocità sono in pixel float.
// Nel caso della pallina il rimbalzo usa i limiti in pixel del Campo.
// La posizione della pallina è rappresentata dal centro dell'oggetto, 
// per cui il rimbalzo tiene conto della dimensione (raggio) 
// dell'oggetto per evitare di uscire parzialmente dal campo.
// 
// Nel caso della stecca, la posizione è rappresentata dal centro del gommino,
// per cui la posizione nello schermo tiene conto della posizione del gommino 
// e non della dimensione della stecca, che invece è usata per il disegno.
// 
// La direzione è rappresentata da un angolo in gradi, 
// con 0°=destra, 90°=giù, 180°=sinistra, 270°=su.
// ============================================================

class OggettoMobile {
public:

    // ── Costruttori ──────────────────────────────────────────

    // Default: fermo in (0,0), dimensione 16x16, simbolo 'O'.
    OggettoMobile();

    // Completo.
    // posX, posY     : posizione di riferimento in pixel
    // vel            : modulo velocità (pixel/frame)
    // angoloDeg      : direzione (0°=destra, 90°=giù, 180°=sinistra, 270°=su)
	// imgFile        : percorso al file PNG (con trasparenza) da disegnare, se esiste
    // dimX, dimY     : usato per rimbalzo, disegno e collisioni
    // f              : carattere per modalità testo
    // coloreForma    : colore del carattere
    // coloreSfondo   : colore sfondo del cerchio (modalità testo)
    OggettoMobile(float posX, float PosY,
        float vel, float angoloDeg,
        string imgFile = "",
        float dimX = 20, float dimy = 20,
        wchar_t f = L'O',
        sf::Color coloreForma = sf::Color::White,
        sf::Color coloreSfondo = sf::Color::Black
        );

    // ── Getter ────────────────────────────────────────────────

    float getX();
    float getY();
    float getVelocita();
    float getDimX();
    float getDimY();

    // Angolo corrente in gradi (ricavato da spostX/spostY).
    float getAngolo();

    // ── Setter ────────────────────────────────────────────────

    // Sposta la posizione a (nuovaX, nuovaY) — controllando ai bordi.
    void impostaPosizione(float nuovaX, float nuovaY, int larghezza, int altezza);

    // Trasla la posizione di (dx, dy) — controllando ai bordi.
    void spostaStecca(float dx, float dy, int larghezza, int altezza);

    // Imposta il modulo della velocità mantenendo la direzione ricalcolando spostX/spostY.
    void impostaVelocita(float vel);

    // Imposta la direzione in gradi ricalcolando spostX/spostY.
    void impostaAngolo(float angoloDeg);

	// aggiorna angoloOgg e spostX/spostY, 
    // senza cambiare angoloImg
	void ruota(float angoloDeg);  // ruota solo l'oggetto (direzione di movimento)
    void ruotaImmagine(float angoloDeg);  // ruota solo l'immagine

    // Aumenta la velocità di 'delta' pixel.
    void accelera(float delta);

    // ── Movimento ─────────────────────────────────────────────

    // Muove oggetto usando spostX/spostY e gestisce il rimbalzo
    // sui quattro bordi del campo (usa il raggio per evitare di uscire parzialmente).
    void muoviConRimbalzoBordi(int largCampo, int altCampo);

    // ── Disegno ───────────────────────────────────────────────

	// Aggiunge al campo l'oggetto mobile pallina centrata in (x,y).
    void aggiungiOggettoMobilePallina(InterfacciaUtente& ui);
    // Aggiunge al campo l'oggetto mobile stecca centrata dove c'è il gommino.
    void aggiungiOggettoMobileStecca(InterfacciaUtente& ui);

private:
    float posX, posY;          // posizione in pixel
    float spostX, spostY;
    float velocita;
    float dimX, dimY;
    float angoloOgg;
    float angoloImg;

    // versione grafica con nome file di immagine
    string imgFile;

    void rimbalzaX();
    void rimbalzaY();

    // Controlla posizione entro i bordi del campo.
    bool controllaPosizionePallina(int largCampo, int altCampo);
    bool controllaPosizioneStecca(int largCampo, int altCampo);
};