#include "OggettoMobile.h"
#include <cmath>   // cos, sin, atan2, sqrt


// ============================================================
//  Costruttori
// ============================================================

OggettoMobile::OggettoMobile()
{
    this->posX = 0.0f;
    this->posY = 0.0f;
    this->spostX = 0.0f;
    this->spostY = 0.0f;
    this->dimX = 16.0f;
    this->dimY = 16.0f;
    this->velocita = 0.0f;

    this->imgFile = "";
	this->angoloImg = 0.0f;
	this->angoloOgg = this->angoloImg;
}

OggettoMobile::OggettoMobile(float startX, float startY,
    float vel, float angoloDeg,
    string imgFilePacMan,
    float dimX, float dimY,
    wchar_t f,
    sf::Color coloreForma,
    sf::Color coloreSfondo)
{
    this->posX = startX;
    this->posY = startY;
    this->dimX = dimX;
    this->dimY = dimY;
    this->velocita = vel;

    this->spostX = 0.0f;
    this->spostY = 0.0f;
    this->imgFile = imgFilePacMan;
    this->angoloImg = angoloDeg;
    impostaAngolo(this->angoloImg);
}


// ============================================================
//  Getter
// ============================================================

float OggettoMobile::getX()        { return this->posX; }
float OggettoMobile::getY()        { return this->posY; }
float OggettoMobile::getVelocita() { return this->velocita; }
float OggettoMobile::getDimX()     { return this->dimX; }
float OggettoMobile::getDimY()     { return this->dimY; }
float OggettoMobile::getAngolo()   { return this->angoloOgg; }

// ============================================================
//  Setter
// ====================================================={=======

void OggettoMobile::impostaPosizione(float nuovaX, float nuovaY,
    int largCampo, int altCampo)
{
    int oldCentroX = this->posX;
    int oldCentroY = this->posY; 
    this->posX = nuovaX;
    this->posY = nuovaY;
    if (!controllaPosizionePallina(largCampo, altCampo)) {
        this->posX = oldCentroX;
        this->posY = oldCentroY;
    }
}

void OggettoMobile::spostaStecca(float dx, float dy, int largCampo, int altCampo)
{
    int oldCentroX = this->posX;
    int oldCentroY = this->posY;
    this->posX += dx;
    this->posY += dy;
    if (!controllaPosizioneStecca(largCampo, altCampo)) {
        this->posX = oldCentroX;
        this->posY = oldCentroY;
    }
}

void OggettoMobile::impostaVelocita(float vel)
{
    if (vel < 0.0f) 
        vel = 0.0f;
    this->velocita = vel;
	// lo spostamento spostX/spostY dipende dalla velocità e dall'angolo, 
    // per cui si ricalcola usando cos e sin
	// angoloOgg è in gradi, si converte in radianti per cos e sin
	float rad = this->angoloOgg * static_cast<float>(PIGRECO) / 180.0f;
    this->spostX = std::cos(rad) * this->velocita;
    this->spostY = std::sin(rad) * this->velocita;
}

void OggettoMobile::impostaAngolo(float angoloDeg)
{
    if (angoloDeg < 0.0f)
		angoloDeg += 360.0f;
    else if (angoloDeg >= 360.0f)
		angoloDeg -= 360.0f;
    this->angoloOgg = angoloDeg;
    // lo spostamento spostX/spostY dipende dalla velocità e dall'angolo, 
    // per cui si ricalcola usando cos e sin
    // angoloOgg è in gradi, si converte in radianti per cos e sin
    float rad = this->angoloOgg * static_cast<float>(PIGRECO) / 180.0f;
    this->spostX = std::cos(rad) * this->velocita;
    this->spostY = std::sin(rad) * this->velocita;
}

void OggettoMobile::ruotaImmagine(float angoloDeg)
{
	this->angoloImg += angoloDeg;
}

void OggettoMobile::ruota(float angoloDeg)
{
    impostaAngolo(this->angoloOgg + angoloDeg);
}

void OggettoMobile::accelera(float delta)
{
    float velocita = this->velocita + delta;
    if (velocita < 0.0f) {
        velocita = 0.0f;
        this->spostX = 0.0f;
        this->spostY = 0.0f;
    }
    else {
		impostaVelocita(velocita);
    }
}

// ============================================================
//  Rimbalzo
// ============================================================

bool OggettoMobile::controllaPosizionePallina(int largCampo, int altCampo)
{
	// il centro della pallina deve essere a distanza 
    // di almeno dimX/2 dai bordi del campo
    if (this->posX - this->dimX / 2 < 0.0f)
        return false;
    if (this->posX + this->dimX / 2 > largCampo)
        return false;

    if (this->posY - this->dimY / 2 < 0.0f)
        return false;
    if (this->posY + this->dimY / 2 > altCampo)
        return false;
    return true;
}

bool OggettoMobile::controllaPosizioneStecca(int largCampo, int altCampo)
{
    // per la stecca si controlla che il gommino senza bordi
    // si trovi nel campo
    if (this->posX < 0.0f)
        return false;
    if (this->posX > largCampo)
        return false;

    if (this->posY < 0.0f)
        return false;
    if (this->posY > altCampo)
        return false;

    return true;
}

// ============================================================
//  Rimbalzo
// ============================================================

void OggettoMobile::rimbalzaX()
{
	// Inverte lo spostamento in X e ricalcola l'angolo di movimento
	this->spostX = -this->spostX;
	this->angoloOgg = std::atan2(this->spostY, this->spostX) * 180.0f / static_cast<float>(PIGRECO);
}

void OggettoMobile::rimbalzaY()
{
	// Inverte lo spostamento in Y e ricalcola l'angolo di movimento
    this->spostY = -this->spostY;
    this->angoloOgg = std::atan2(this->spostY, this->spostX) * 180.0f / static_cast<float>(PIGRECO);
}


// ============================================================
//  Movimento
// ============================================================

void OggettoMobile::muoviConRimbalzoBordi(int largCampo, int altCampo)
{
    int oldCentroX = this->posX;
    int oldCentroY = this->posY; 
    this->posX += this->spostX;
    this->posY += this->spostY;
    // ── Rimbalzo bordo sinistro / destro ──────────────────────
    if (this->posX - this->dimX / 2 < 0.0f)
    {
		// Se la pallina ha superato il bordo sinistro, 
        // si riposiziona alla vecchia posizione e si rimbalza
        this->posX = oldCentroX;
        rimbalzaX();
    }
    if (this->posX + this->dimX / 2 > largCampo)
    {
        // Se la pallina ha superato il bordo destro, 
        // si riposiziona alla vecchia posizione e si rimbalza
        this->posX = oldCentroX;
        rimbalzaX();
    }

    // ── Rimbalzo bordo superiore / inferiore ──────────────────
    if (this->posY - this->dimY / 2 < 0.0f)
    {
		// Se la pallina ha superato il bordo superiore,
        // si riposiziona alla vecchia posizione e si rimbalza
        this->posY = oldCentroY;
        rimbalzaY();
    }
    if (this->posY + this->dimY / 2 > altCampo)
    {
		// Se la pallina ha superato il bordo inferiore,
        // si riposiziona alla vecchia posizione e si rimbalza
        this->posY = oldCentroY;
        rimbalzaY();
    }

}

// ============================================================
//  Disegno
// ============================================================


void OggettoMobile::aggiungiOggettoMobilePallina(InterfacciaUtente& ui)
{
    if (!this->imgFile.empty())
    {
        // Scala l'immagine affinché la larghezza coincida con dimX/dimY
		// non si aggiorna dimY perchè si assume che l'immagine abbia proporzioni corrette 
        float scala = 0;

        sf::Texture texture;
        if (texture.loadFromFile(this->imgFile))
        {
            sf::Vector2u dimTex = texture.getSize();
            float larghezza = this->dimX;
            if (dimTex.x > 0)
                scala = larghezza / static_cast<float>(dimTex.x);
            else
                scala = 1.0f;
        }
		// disegnaSprite usando posX e posY come centro della pallina
        ui.aggiungiImmagine(Punto(this->posX, this->posY), this->imgFile, 
            scala, scala);
    }
}

void OggettoMobile::aggiungiOggettoMobileStecca(InterfacciaUtente& ui)
{
    if (!this->imgFile.empty())
    {
        // Scala l'immagine affinché la larghezza coincida con dimX/dimY
        // non si aggiorna dimY perchè si assume che l'immagine abbia proporzioni corrette 
        float scala = 0;

        sf::Texture texture;
        if (texture.loadFromFile(this->imgFile))
        {
            sf::Vector2u dimTex = texture.getSize();
            float larghezza = this->dimX;
            if (dimTex.x > 0)
                scala = larghezza / static_cast<float>(dimTex.x);
            else
                scala = 1.0f;
        }
        // nel caso della stecca il disegno dell'immagine
        // prevede di disegnare la steecca usando posX e posY come
        // posizione del gommino che si trova in ALTO
        // e che la stecca sia ruotata di this->angoloImg
        int pX = this->posX;
        int pY = this->posY;
        ui.aggiungiImmagine(Punto(this->posX, this->posY), this->imgFile, 
            scala, scala, this->angoloImg, ALTO);
    }
}