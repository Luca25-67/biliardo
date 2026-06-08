#pragma once
#include "Campo.h"
#include "Tastiera.h"
#include "Posizione.h"
#include "Punto.h"
#include <string>
#include <thread>

using namespace std;

// ============================================================
//  InterfacciaUtente
//
//  Classe generale di input/output.
//  Non contiene logica specifica di un gioco.
//
//  Usa:
//  - Campo per preparare e disegnare la scena
//  - Tastiera per leggere input da utente
// ============================================================

class InterfacciaUtente {
public:
    // Riceve Campo e Tastiera dall'esterno.
    // Non li possiede: li usa tramite riferimento.
    InterfacciaUtente(Campo& campo, Tastiera& tastiera);

    // ── Ciclo di rendering ────────────────────────────────────

    // Cancella il contenuto della finestra con il colore di sfondo.
    // Da chiamare all'inizio di ogni frame.
    void pulisci();

    // Presenta il frame corrente sulla finestra.
    // Da chiamare quando si vuole visualizzare il frame.
    void disegna();

    // ========================================================
    // Prepara quanto deve essere mostrato sul campo da gioco
    // ========================================================

    void aggiungiTesto(Punto punto, wstring testo);
    void aggiungiTestoRigCol(Posizione posizione, wstring testo);
    void aggiungiTestoAlCentro(int pixY, wstring testo);
    void aggiungiTestoAlCentroRigCol(int riga, wstring testo);

    void aggiungiNumero(Punto punto, int numero);
    void aggiungiNumeroRigCol(Posizione posizione, int numero);
    void aggiungiNumero(Punto punto, double numero);
    void aggiungiNumeroRigCol(Posizione posizione, double numero);

    void aggiungiSimbolo(Punto punto, wchar_t simbolo);
    void aggiungiSimboloRigCol(Posizione posizione, wchar_t simbolo);

    void aggiungiLinea(Punto puntoInizio,
        Punto PuntoFine,
        sf::Color colore,
        float spessore);
    void aggiungiLineaRigCol(Posizione posizioneInizio,
        Posizione posizioneFine,
        sf::Color colore,
        float spessore);

    void aggiungiCerchio(Punto punto,
        float raggio,
        sf::Color colore);
    void aggiungiCerchioRigCol(Posizione centro,
        float raggio,
        sf::Color colore);

    // Cerchio vuoto (solo bordo) con centro (cx,cy).
    void aggiungiCerchioVuoto(Punto centro,
        float raggio,
        sf::Color colore,
        float spessore = 1.0f);
    void aggiungiCerchioVuotoRigCol(Posizione centro,
        float raggio,
        sf::Color colore,
        float spessore = 1.0f);

    // Rettangolo pieno. (x,y) è vertice in alto a sinistra.
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

    void aggiungiImmagine(Punto punto, string nomeImmagine, float scalaX = 1.0f, float scalaY = 1, float angolo = 0, int puntoRotaz = 0);
    void aggiungiImmagineRigCol(Posizione posizione, string nomeImmagine, float scalaX = 1.0f, float scalaY = 1, float angolo = 0, int puntoRotaz = 0);

	void sleep(int millisecondi);

    // ========================================================
	// Input stringhe e interi da tastiera
    // 
	// In questa versione testuale, i metodi di input leggono da tastiera oggetti di tipo wstring
	// e non di tipo string per permettere l'uso di caratteri accentati e simboli grafici.
    // ========================================================

    wstring leggiStringa(
        Posizione posizioneRisposta,
        Posizione posizioneDomanda,
        wstring domanda
    );

    int leggiIntero(
        Posizione posizioneRisposta,
        Posizione posizioneDomanda,
        wstring domanda,
        int valDefault,
        int minVal,
        int maxVal
    );

    // ========================================================
	// Input dei caratteri da tastiera
    // 
    // I metodi seguenti lavorano con il tipo int invece del tipo char perchè
    // non si vogliono leggere solo caratteri, ma anche :
    //    frecce
    //    ESC
    //    INVIO
    //    BACKSPACE
    //    tasti funzione
    //    combinazioni speciali
    // Questi spesso non sono rappresentabili con un singolo carattere, ma con due caratteri richiedendo per questo 
    // una variabile che occupa almeno due byte.
    // Per questo motivo si è scelto di usare il tipo int, che è in grado di rappresentare 
    // tutti i tasti speciali e i caratteri Unicode.
    // ========================================================

    int leggiTasto();
    int leggiTastoBloccante();

    bool tastoPremuto();
    void svuotaBuffer();

    bool isEsc(int codice);
    bool isInvio(int codice);

    bool isFreccia(int codice);
    bool isFrecciaSu(int codice);
    bool isFrecciaGiu(int codice);
    bool isFrecciaSinistra(int codice);
    bool isFrecciaDestra(int codice);

    bool isTastoFunzione(int codice);

    // ========================================================
    // Informazioni sul campo
    // ========================================================

    int getLarghezza();
    int getLarghezzaRigCol();
    int getAltezza();
    int getAltezzaRigCol();

private:
    Campo& campo;
    Tastiera& tastiera;
};
