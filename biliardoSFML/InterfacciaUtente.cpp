#include "InterfacciaUtente.h"

// ============================================================
//  Costruttore
// ============================================================
InterfacciaUtente::InterfacciaUtente(Campo& campo, Tastiera& tastiera)
    : campo(campo), tastiera(tastiera)
{
}

// ============================================================
//  Ciclo di visualizzazione
// ============================================================

void InterfacciaUtente::pulisci() {
    campo.pulisci();
}

void InterfacciaUtente::disegna() {
    campo.disegna();
}

// ============================================================
//  Output generico
// ============================================================

void InterfacciaUtente::aggiungiTesto(Punto punto, wstring testo) {
    campo.aggiungiTesto(punto, testo);
}
void InterfacciaUtente::aggiungiTestoRigCol(Posizione posizione, wstring testo) {
    campo.aggiungiTestoRigCol(posizione, testo);
}

void InterfacciaUtente::aggiungiTestoAlCentro(int pixY, wstring testo) {
    campo.aggiungiTestoAlCentro(pixY, testo);
}

void InterfacciaUtente::aggiungiTestoAlCentroRigCol(int riga, wstring testo) {
    campo.aggiungiTestoAlCentroRigCol(riga, testo);
}

void InterfacciaUtente::aggiungiNumero(Punto punto, int numero) {
    campo.aggiungiTesto(punto, to_wstring(numero));
}

void InterfacciaUtente::aggiungiNumeroRigCol(Posizione posizione, int numero) {
    campo.aggiungiTestoRigCol(posizione, to_wstring(numero));
}

void InterfacciaUtente::aggiungiNumero(Punto punto, double numero) {
    campo.aggiungiTesto(punto, to_wstring(numero));
}

void InterfacciaUtente::aggiungiNumeroRigCol(Posizione posizione, double numero) {
    campo.aggiungiTestoRigCol(posizione, to_wstring(numero));
}

void InterfacciaUtente::aggiungiSimbolo(Punto punto, wchar_t simbolo) {
    wstring testo = L"" + simbolo;
    campo.aggiungiTesto(punto, testo);
}

void InterfacciaUtente::aggiungiSimboloRigCol(Posizione posizione, wchar_t simbolo) {
    wstring testo = L"" + simbolo;
    campo.aggiungiTestoRigCol(posizione, testo);
}

void InterfacciaUtente::aggiungiLinea(Punto puntoInizio, Punto puntoFine, sf::Color colore, float spessore) {
    campo.aggiungiLinea(puntoInizio, puntoFine, colore, spessore);
}

void InterfacciaUtente::aggiungiLineaRigCol(Posizione posizioneInizio, Posizione posizioneFine, sf::Color colore, float spessore) {
    campo.aggiungiLineaRigCol(posizioneInizio, posizioneFine, colore, spessore);
}

void InterfacciaUtente::aggiungiCerchio(Punto centro, float raggio, sf::Color colore) {
    campo.aggiungiCerchio(centro, raggio, colore);
}

void InterfacciaUtente::aggiungiCerchioRigCol(Posizione centro, float raggio, sf::Color colore) {
    campo.aggiungiCerchioRigCol(centro, raggio, colore);
}

void InterfacciaUtente::aggiungiCerchioVuoto(Punto centro, float raggio, sf::Color colore, float spessore) {
    campo.aggiungiCerchioVuoto(centro, raggio, colore, spessore);
}

void InterfacciaUtente::aggiungiCerchioVuotoRigCol(Posizione centro, float raggio, sf::Color colore, float spessore) {
    campo.aggiungiCerchioVuotoRigCol(centro, raggio, colore, spessore);
}

void InterfacciaUtente::aggiungiRettangolo(Punto verticeAltoSinistra, int larghezza, int altezza, sf::Color colore) {
    campo.aggiungiRettangolo(verticeAltoSinistra, larghezza, altezza, colore);
}

void InterfacciaUtente::aggiungiRettangoloRigCol(Posizione verticeAltoSinistra, int larghezza, int altezza, sf::Color colore) {
    campo.aggiungiRettangoloRigCol(verticeAltoSinistra, larghezza, altezza, colore);
}

void InterfacciaUtente::aggiungiRettangoloVuoto(Punto verticeAltoSinistra, int larghezza, int altezza, sf::Color colore, float spessore) {
    campo.aggiungiRettangoloVuoto(verticeAltoSinistra, larghezza, altezza, colore, spessore);
}

void InterfacciaUtente::aggiungiRettangoloVuotoRigCol(Posizione verticeAltoSinistra, int larghezza, int altezza, sf::Color colore, float spessore) {
    campo.aggiungiRettangoloVuotoRigCol(verticeAltoSinistra, larghezza, altezza, colore, spessore);
}


void InterfacciaUtente::aggiungiImmagine(Punto punto, string nomeImmagine, float scalaX, float scalaY, float angolo, int puntoRotaz) {
    campo.aggiungiImmagine(punto, nomeImmagine, scalaX, scalaY, angolo, puntoRotaz);
}

void InterfacciaUtente::aggiungiImmagineRigCol(Posizione posizione, string nomeImmagine, float scalaX, float scalaY, float angolo, int puntoRotaz) {
    campo.aggiungiImmagineRigCol(posizione, nomeImmagine, scalaX, scalaY, angolo, puntoRotaz);
}

void InterfacciaUtente::sleep(int millisecondi) {
    std::this_thread::sleep_for(std::chrono::milliseconds(millisecondi));
}

// ============================================================
//  Input testuale
// ============================================================

wstring InterfacciaUtente::leggiStringa(
    Posizione posizioneRisposta,
    Posizione posizioneDomanda,
    wstring domanda
) {
    return tastiera.leggiStringa(
        campo,
        posizioneRisposta,
        posizioneDomanda,
        domanda
    );
}

int InterfacciaUtente::leggiIntero(
    Posizione posizioneRisposta,
    Posizione posizioneDomanda,
    wstring domanda,
    int valDefault,
    int minVal,
    int maxVal
) {
    return tastiera.leggiIntero(
        campo,
        posizioneDomanda,
        posizioneRisposta,
        domanda,
        valDefault,
        minVal,
        maxVal
    );
}

// ============================================================
//  Input da tastiera
// ============================================================

int InterfacciaUtente::leggiTasto() {
    return tastiera.leggi();
}

int InterfacciaUtente::leggiTastoBloccante() {
    return tastiera.leggiBloccante();
}

bool InterfacciaUtente::tastoPremuto() {
    return tastiera.tastoPremuto();
}

void InterfacciaUtente::svuotaBuffer() {
    tastiera.svuotaBuffer();
}

bool InterfacciaUtente::isEsc(int codice) {
    return codice == TASTO_ESC;
}

bool InterfacciaUtente::isInvio(int codice) {
    return codice == TASTO_INVIO;
}

bool InterfacciaUtente::isFreccia(int codice) {
    return tastiera.isFreccia(codice);
}

bool InterfacciaUtente::isFrecciaSu(int codice) {
    return codice == TASTO_SU;
}

bool InterfacciaUtente::isFrecciaGiu(int codice) {
    return codice == TASTO_GIU;
}

bool InterfacciaUtente::isFrecciaSinistra(int codice) {
    return codice == TASTO_SINISTRA;
}

bool InterfacciaUtente::isFrecciaDestra(int codice) {
    return codice == TASTO_DESTRA;
}

bool InterfacciaUtente::isTastoFunzione(int codice) {
    if (codice == TASTO_F1) return true;
    if (codice == TASTO_F2) return true;
    if (codice == TASTO_F3) return true;
    if (codice == TASTO_F4) return true;
    if (codice == TASTO_F5) return true;
    if (codice == TASTO_F6) return true;
    if (codice == TASTO_F7) return true;
    if (codice == TASTO_F8) return true;
    if (codice == TASTO_F9) return true;
    if (codice == TASTO_F10) return true;

    return false;
}

// ============================================================
//  Informazioni sul campo
// ============================================================

int InterfacciaUtente::getLarghezza() {
    return campo.getLarghezza();
}

int InterfacciaUtente::getLarghezzaRigCol() {
    return campo.getLarghezzaRigCol();
}

int InterfacciaUtente::getAltezza() {
    return campo.getAltezza();
}

int InterfacciaUtente::getAltezzaRigCol() {
    return campo.getAltezzaRigCol();
}