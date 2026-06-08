#include "Campo.h"
#include "InterfacciaUtente.h"

Campo::Campo(
    int larghezzaPx,
    int altezzaPx,
    wstring titolo,
    string fontPath,
    int dimFont,
    sf::Color sfondo
) {
    this->larghezzaPx = larghezzaPx;
    this->altezzaPx = altezzaPx;
    this->dimFont = dimFont;
    this->coloreSfondo = sfondo;
	this->angoloRotazione = 0.0f;
    finestra.create(
        sf::VideoMode(larghezzaPx, altezzaPx),
        sf::String(titolo)
    );

    caricaFont(fontPath);
}

Campo::~Campo() {
    finestra.close();
}

float Campo::colonnaToX(int colonna) {
    return (float)(colonna * LARGHEZZA_CELLA);
}

float Campo::rigaToY(int riga) {
    return (float)(riga * ALTEZZA_CELLA);
}

void Campo::pulisci() {
    finestra.clear(coloreSfondo);
}

void Campo::ruota(float angoloDeg)
{
    this->angoloRotazione += angoloDeg;
}

// cancella un rettangolo con vertice in alto a sinistra in (x,y) 
// e dimensioni larghezzaPx x altezzaPx
void  Campo::cancellaArea(Punto punto,
    int larghezzaPx,
    int altezzaPx) {

    sf::RectangleShape rettangolo;

    rettangolo.setPosition(punto.getX(), punto.getY());
    rettangolo.setSize(sf::Vector2f(larghezzaPx, altezzaPx));
    rettangolo.setFillColor(coloreSfondo);

    finestra.draw(rettangolo);
}

void  Campo::cancellaAreaRigCol(Posizione posizione,
    int larghezza,
    int altezza) {

    int x = colonnaToX(posizione.getColonna());
    int y = rigaToY(posizione.getRiga());
    int larghezzaPx = larghezza * LARGHEZZA_CELLA;
    int altezzaPx = altezza * ALTEZZA_CELLA;

    cancellaArea(Punto(x, y), larghezzaPx, altezzaPx);
}

void Campo::disegna() {
    finestra.display();
}

void Campo::aggiungiTesto(Punto punto, wstring testo) {
    sf::Text oggettoTesto;

    oggettoTesto.setFont(font);
    oggettoTesto.setCharacterSize(dimFont);
    oggettoTesto.setFillColor(FG_BIANCO);
    oggettoTesto.setString(sf::String(testo));

	oggettoTesto.setPosition(punto.getX(), punto.getY());

    finestra.draw(oggettoTesto);
}

void Campo::aggiungiTestoRigCol(Posizione posizione, wstring testo) {
    int pixX = colonnaToX(posizione.getColonna());
    int pixY = rigaToY(posizione.getRiga());
    aggiungiTesto(Punto(pixX, pixY), testo);
}

void Campo::aggiungiTestoAlCentro(int pixY, wstring testo) {
    sf::Text oggettoTesto;

    oggettoTesto.setFont(font);
    oggettoTesto.setCharacterSize(dimFont);
    oggettoTesto.setString(sf::String(testo));

    sf::FloatRect bounds = oggettoTesto.getLocalBounds();

    int pixX = ((float)larghezzaPx - bounds.width) / 2.0f;

    aggiungiTesto(Punto(pixX, pixY), testo);
}

void Campo::aggiungiTestoAlCentroRigCol(int riga, wstring testo) {
    int pixY = rigaToY(riga);
    aggiungiTestoAlCentro(pixY, testo);
}

void Campo::aggiungiNumero(Punto punto, int numero) {
    aggiungiTesto(punto, to_wstring(numero));
}

void Campo::aggiungiNumeroRigCol(Posizione posizione, int numero) {
    aggiungiTestoRigCol(posizione, to_wstring(numero));
}

void Campo::aggiungiSimbolo(Punto punto, wchar_t simbolo) {
    wstring testo = L"" + simbolo;
    aggiungiTesto(punto, testo);
}

void Campo::aggiungiSimboloRigCol(Posizione posizione, wchar_t simbolo) {
    wstring testo = L"" + simbolo;
    aggiungiTestoRigCol(posizione, testo);
}

void Campo::aggiungiLinea(Punto puntoInizio,
    Punto puntoFine,
    sf::Color colore,
    float spessore
) {
    float dx = puntoFine.getX() - puntoInizio.getX();
    float dy = puntoFine.getY() - puntoInizio.getY();
    float lungh = std::sqrt(dx * dx + dy * dy);
    float angolo = std::atan2(dy, dx) * 180.0f / static_cast<float>(PIGRECO);

    sf::RectangleShape linea(sf::Vector2f(lungh, spessore));
    linea.setFillColor(colore);
    linea.setOrigin(0.0f, spessore / 2.0f);
    linea.setPosition(puntoInizio.getX(), puntoInizio.getY());
    linea.setRotation(angolo);

    this->finestra.draw(linea);
}

void Campo::aggiungiLineaRigCol(Posizione posizioneInizio,
    Posizione posizioneFine,
    sf::Color colore,
    float spessore
) {
    Punto puntoInizio = Punto(colonnaToX(posizioneInizio.getColonna()), rigaToY(posizioneInizio.getRiga()));
	Punto puntoFine = Punto(colonnaToX(posizioneFine.getColonna()), rigaToY(posizioneFine.getRiga()));
    aggiungiLinea(puntoInizio, puntoFine, colore, spessore);
}

void Campo::aggiungiCerchio(Punto centro,
    float raggio,
    sf::Color colore
) {
    sf::CircleShape cerchio(raggio);
    cerchio.setPosition(centro.getX(), centro.getY());
    cerchio.setFillColor(colore);
    this->finestra.draw(cerchio);
}

void Campo::aggiungiCerchioRigCol(Posizione centro,
    float raggio,
    sf::Color colore
) {
    Punto centroXY = Punto(colonnaToX(centro.getColonna()), rigaToY(centro.getRiga()));
    aggiungiCerchio(centroXY, raggio, colore);
}

// Cerchio vuoto (solo bordo) con centro (cx,cy).
void Campo::aggiungiCerchioVuoto(Punto centro,
    float raggio,
    sf::Color colore,
    float spessore
) {
    sf::CircleShape cerchio(raggio);
    cerchio.setPosition(centro.getX(), centro.getY());
    cerchio.setFillColor(sf::Color::Transparent);
    cerchio.setOutlineColor(colore);
    cerchio.setOutlineThickness(spessore);
    this->finestra.draw(cerchio);
}

void Campo::aggiungiCerchioVuotoRigCol(Posizione centro,
    float raggio,
    sf::Color colore,
    float spessore
) {
    Punto centroXY = Punto(colonnaToX(centro.getColonna()), rigaToY(centro.getRiga()));
	aggiungiCerchioVuoto(centroXY, raggio, colore, spessore);
}

// Rettangolo pieno. (x,y) è l'angolo in alto a sinistra.
void Campo::aggiungiRettangolo(Punto angoloAltoSinistra,
    int larghezzaPx, int altezzaPx,
    sf::Color colore)
{
    sf::RectangleShape rettangolo(sf::Vector2f(larghezzaPx, altezzaPx));
    rettangolo.setFillColor(colore);
    rettangolo.setPosition(angoloAltoSinistra.getX(), angoloAltoSinistra.getY());
    this->finestra.draw(rettangolo);
}

void Campo::aggiungiRettangoloRigCol(Posizione angoloAltoSinistra,
    int larghezza, int altezza,
    sf::Color colore
) {
    int larghezzaPx = larghezza * LARGHEZZA_CELLA;
    int altezzaPx = altezza * ALTEZZA_CELLA;
    sf::RectangleShape rettangolo(sf::Vector2f(larghezzaPx, altezzaPx));
    rettangolo.setFillColor(colore);
    rettangolo.setPosition(colonnaToX(angoloAltoSinistra.getColonna()), rigaToY(angoloAltoSinistra.getRiga()));
    this->finestra.draw(rettangolo);
}

// Rettangolo vuoto (solo bordo).
void Campo::aggiungiRettangoloVuoto(Punto angoloAltoSinistra,
    int larghezzaPx, int altezzaPx,
    sf::Color colore,
    float spessore
) {
    sf::RectangleShape rettangolo(sf::Vector2f(larghezzaPx, altezzaPx));
    rettangolo.setFillColor(sf::Color::Transparent);
    rettangolo.setOutlineColor(colore);
    rettangolo.setOutlineThickness(spessore);
    rettangolo.setPosition(angoloAltoSinistra.getX(), angoloAltoSinistra.getY());
    this->finestra.draw(rettangolo);
}

void Campo::aggiungiRettangoloVuotoRigCol(Posizione angoloAltoSinistra,
    int larghezza, int altezza,
    sf::Color colore,
    float spessore)
{
    float larghezzaPx = (float)(larghezza * LARGHEZZA_CELLA);
    float altezzaPx = (float)(altezza * ALTEZZA_CELLA);
    int pixX = colonnaToX(angoloAltoSinistra.getColonna());
    int pixY = rigaToY(angoloAltoSinistra.getRiga());
	aggiungiRettangoloVuoto(Punto(pixX, pixY), larghezzaPx, altezzaPx, colore, spessore);
}

void Campo::aggiungiImmagine(Punto punto, string nomeImmagine, float scalaX, float scalaY, float angolo, int puntoRotaz)
{
    wstring testo;

    sf::Texture tex;
    tex.loadFromFile(nomeImmagine);
    tex.setSmooth(true);
    sf::Sprite sprite(tex);

    // Rettangolo con le dimensioni locali dell'immagine
    sf::FloatRect bounds = sprite.getLocalBounds();
	// Imposta l'origine (punto di rotazione) in base al valore di puntoRotaz
    switch (puntoRotaz) {
        case CENTRO: 
            sprite.setOrigin(bounds.width / 2, bounds.height / 2 );
            break;
        case ALTO:
            sprite.setOrigin(bounds.width / 2, 0);
            break;
        case BASSO:
            sprite.setOrigin(bounds.width / 2, bounds.height);
            break;
        case DESTRA:
			sprite.setOrigin(bounds.width, bounds.height / 2);
            break;
        case SINISTRA:
            sprite.setOrigin(0, bounds.height / 2);
            break;
    }

    sprite.setScale(scalaX, scalaY);
    sprite.setPosition(punto.getX(), punto.getY());
    sprite.setRotation(angolo+90);
    this->finestra.draw(sprite);

    /******* rettangolo di debug
    sf::RectangleShape rect;
    rect.setSize({ bounds.width, bounds.height });
    rect.setOrigin(sprite.getOrigin());
    rect.setPosition(sprite.getPosition());
    rect.setRotation(sprite.getRotation());
    rect.setScale(sprite.getScale());

    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::Red);
    rect.setOutlineThickness(2.f);
    this->finestra.draw(rect);
    ***/
}

void Campo::aggiungiImmagineRigCol(Posizione posizione, string nomeImmagine, float scalaX, float scalaY, float angolo, int puntoRotaz) {
    int pixX = colonnaToX(posizione.getColonna());
    int pixY = rigaToY(posizione.getRiga());
    aggiungiImmagine(Punto(pixX, pixY), nomeImmagine, scalaX, scalaY, angolo, puntoRotaz);
}



int Campo::getLarghezza() {
    return larghezzaPx;
}

int Campo::getLarghezzaRigCol() {
    return larghezzaPx / LARGHEZZA_CELLA;
}

int Campo::getAltezza() {
    return altezzaPx;
}

int Campo::getAltezzaRigCol() {
    return altezzaPx / ALTEZZA_CELLA;
}

bool Campo::isAperta() {
    return finestra.isOpen();
}

bool Campo::pollEvent(sf::Event& ev) {
    return finestra.pollEvent(ev);
}

bool Campo::waitEvent(sf::Event& ev) {
    return finestra.waitEvent(ev);
}

// ============================================================
//  Helper interno — caricamento font con fallback di sistema
// ============================================================

void Campo::caricaFont(std::string fontPath)
{
    if (this->font.loadFromFile(fontPath))
        return;

    // Fallback su font monospace di sistema (Windows / Linux / macOS)
    bool caricato =
        this->font.loadFromFile("C:/Windows/Fonts/consola.ttf") ||
        this->font.loadFromFile("C:/Windows/Fonts/cour.ttf") ||
        this->font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf") ||
        this->font.loadFromFile("/System/Library/Fonts/Courier New.ttf");

    if (!caricato)
        exit(1);   // nessun font disponibile: impossibile proseguire
}
