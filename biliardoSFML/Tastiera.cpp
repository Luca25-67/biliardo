#include "Tastiera.h"

// ============================================================
//  Costruttore / Distruttore
// ============================================================

Tastiera::Tastiera(Campo& campo) : campo(campo) {
    this->ultimoTasto = TASTO_NESSUNO;
    this->tastoSpeciale = false;
    this->bufferTesto = L"";
    // La coda std::queue<int> non necessita di inizializzazione manuale a nullptr.
}

Tastiera::~Tastiera() {
    // Nessuna risorsa da rilasciare.
}

// ============================================================
//  Mappa tasti SFML -> costanti del progetto
// ============================================================

int Tastiera::mappaTasto(sf::Keyboard::Key key, bool shift) {
    this->tastoSpeciale = false;

    if (key == sf::Keyboard::Return) return TASTO_INVIO;
    if (key == sf::Keyboard::Enter) return TASTO_INVIO;
    if (key == sf::Keyboard::Backspace) return TASTO_BACKSPACE;
    if (key == sf::Keyboard::Escape) return TASTO_ESC;
    if (key == sf::Keyboard::Space) return TASTO_SPAZIO;

    if (key == sf::Keyboard::Up) { this->tastoSpeciale = true; return TASTO_SU; }
    if (key == sf::Keyboard::Down) { this->tastoSpeciale = true; return TASTO_GIU; }
    if (key == sf::Keyboard::Left) { this->tastoSpeciale = true; return TASTO_SINISTRA; }
    if (key == sf::Keyboard::Right) { this->tastoSpeciale = true; return TASTO_DESTRA; }

    if (key == sf::Keyboard::F1) { this->tastoSpeciale = true; return TASTO_F1; }
    if (key == sf::Keyboard::F2) { this->tastoSpeciale = true; return TASTO_F2; }
    if (key == sf::Keyboard::F3) { this->tastoSpeciale = true; return TASTO_F3; }
    if (key == sf::Keyboard::F4) { this->tastoSpeciale = true; return TASTO_F4; }
    if (key == sf::Keyboard::F5) { this->tastoSpeciale = true; return TASTO_F5; }
    if (key == sf::Keyboard::F6) { this->tastoSpeciale = true; return TASTO_F6; }
    if (key == sf::Keyboard::F7) { this->tastoSpeciale = true; return TASTO_F7; }
    if (key == sf::Keyboard::F8) { this->tastoSpeciale = true; return TASTO_F8; }
    if (key == sf::Keyboard::F9) { this->tastoSpeciale = true; return TASTO_F9; }
    if (key == sf::Keyboard::F10) { this->tastoSpeciale = true; return TASTO_F10; }

    // ── Lettere A–Z ──────────────────────────────────────────
    if (key >= sf::Keyboard::A && key <= sf::Keyboard::Z) {
        int codice;
        codice = L'a' + (key - sf::Keyboard::A);

        if (shift) {
            codice = L'A' + (key - sf::Keyboard::A);
        }

        return codice;
    }

    // ── Cifre 0–9 ────────────────────────────────────────────
    if (key >= sf::Keyboard::Num0 && key <= sf::Keyboard::Num9) {
        return L'0' + (key - sf::Keyboard::Num0);
    }

    if (key >= sf::Keyboard::Numpad0 && key <= sf::Keyboard::Numpad9) {
        return L'0' + (key - sf::Keyboard::Numpad0);
    }

    return TASTO_NESSUNO;
}

// ============================================================
//  Aggiornamento eventi
// ============================================================

void Tastiera::aggiornaEventi() {
    sf::Event evento;

    while (campo.pollEvent(evento)) {
        if (evento.type == sf::Event::Closed) {
            codaCodici.push(TASTO_ESC);
        }

        if (evento.type == sf::Event::KeyPressed) {
            int codice;
            bool shift;

            shift = evento.key.shift;
            codice = mappaTasto(evento.key.code, shift);

            if (codice != TASTO_NESSUNO) {
                codaCodici.push(codice);
            }
        }
    }
}

// ============================================================
//  Input non bloccante
// ============================================================

bool Tastiera::tastoPremuto() {
    aggiornaEventi();
    return !codaCodici.empty();
}

int Tastiera::leggi() {
    aggiornaEventi();

    if (codaCodici.empty()) {
        this->ultimoTasto = TASTO_NESSUNO;
        this->tastoSpeciale = false;
        return TASTO_NESSUNO;
    }

    this->ultimoTasto = codaCodici.front();
    codaCodici.pop();

    this->tastoSpeciale = isFreccia(this->ultimoTasto);

    if (this->ultimoTasto >= TASTO_F1 && this->ultimoTasto <= TASTO_F10) {
        this->tastoSpeciale = true;
    }

    return this->ultimoTasto;
}

void Tastiera::svuotaBuffer() {
    while (!codaCodici.empty()) {
        codaCodici.pop();
    }

    aggiornaEventi();

    while (!codaCodici.empty()) {
        codaCodici.pop();
    }
}

// ============================================================
//  Input bloccante di un tasto
// ============================================================

int Tastiera::leggiBloccante() {
    sf::Event evento;
    int codice;
    bool finito;

    finito = false;
    codice = TASTO_NESSUNO;

    while (finito == false) {
        campo.waitEvent(evento);

        if (evento.type == sf::Event::Closed) {
            codice = TASTO_ESC;
            finito = true;
        }

        if (evento.type == sf::Event::KeyPressed) {
            codice = mappaTasto(evento.key.code, evento.key.shift);

            if (codice != TASTO_NESSUNO) {
                finito = true;
            }
        }
    }

    this->ultimoTasto = codice;
    this->tastoSpeciale = isFreccia(codice);

    if (codice >= TASTO_F1 && codice <= TASTO_F10) {
        this->tastoSpeciale = true;
    }

    return codice;
}

// ============================================================
//  Lettura stringa
// ============================================================

wstring Tastiera::leggiTesto(bool eco) {
    wstring testo;
    bool finito;

    testo = L"";
    finito = false;

    while (finito == false) {
        int tasto;

        tasto = leggiBloccante();

        if (tasto == TASTO_INVIO) {
            finito = true;
        }
        else if (tasto == TASTO_BACKSPACE) {
            if (testo.length() > 0) {
                testo.erase(testo.length() - 1, 1);
            }
        }
        else if (tasto == TASTO_ESC) {
            finito = true;
        }
        else if (tasto >= 32 && testo.length() < MAX_LUNGHEZZA_TESTO - 1) {
            testo = testo + (wchar_t)tasto;
        }
    }

    this->bufferTesto = testo;
    return testo;
}

// ============================================================
//  Lettura guidata con Campo
// ============================================================

wstring Tastiera::leggiStringa(
    Campo& campo,
    Posizione posizioneRisposta,
    Posizione posizioneDomanda,
    wstring domanda
) {
    campo.pulisci();
    if (domanda.length() > 0)
        campo.aggiungiTestoRigCol(posizioneDomanda, domanda);
    campo.aggiungiTestoRigCol(posizioneRisposta, L"> _");
    campo.disegna();

    wstring testo;
    bool finito;
    int lun = 0;

    testo = L"";
    finito = false;

    while (finito == false) {
        int tasto;

        tasto = leggiBloccante();

        if (tasto == TASTO_INVIO) {
            finito = true;
        }
        else if (tasto == TASTO_BACKSPACE) {
            if (testo.length() > 0) {
                testo.erase(testo.length() - 1, 1);
                lun = testo.length();
            }
        }
        else if (tasto == TASTO_ESC) {
            finito = true;
        }
        else if (tasto >= 32 && testo.length() < MAX_LUNGHEZZA_TESTO - 1) {
            testo = testo + (wchar_t)tasto;
        }

        campo.pulisci();
        if (domanda.length() > 0)
            campo.aggiungiTestoRigCol(posizioneDomanda, domanda);
        campo.cancellaAreaRigCol(posizioneRisposta, LARGHEZZA_CELLA * 50, ALTEZZA_CELLA);
        campo.aggiungiTestoRigCol(posizioneRisposta, L"> " + testo + L"_ ");
        campo.disegna();
    }

    this->bufferTesto = testo;
    return testo;
}

int Tastiera::leggiIntero(
    Campo& campo,
    Posizione posizioneRisposta,
    Posizione posizioneDomanda,
    wstring domanda,
    int valDefault,
    int minVal,
    int maxVal
) {
    wstring testo;
    int valore;

    testo = leggiStringa(
        campo,
        posizioneRisposta,
        posizioneDomanda,
        domanda
    );

    if (testo == L"") {
        valore = valDefault;
    }
    else {
        valore = _wtoi(testo.c_str());
    }

    if (valore < minVal) {
        valore = minVal;
    }

    if (valore > maxVal) {
        valore = maxVal;
    }

    return valore;
}

// ============================================================
//  Getter
// ============================================================

int Tastiera::getUltimoTasto() {
    return this->ultimoTasto;
}

bool Tastiera::isSpeciale() {
    return this->tastoSpeciale;
}

bool Tastiera::isFreccia(int codice) {
    if (codice == TASTO_SU) return true;
    if (codice == TASTO_GIU) return true;
    if (codice == TASTO_SINISTRA) return true;
    if (codice == TASTO_DESTRA) return true;

    return false;
}