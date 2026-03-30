#include "PallePiene.h"

PallePiene::PallePiene(int xIniziale, int yIniziale) {
	this->x = xIniziale;
	this->y = yIniziale;
}

void PallePiene::muoviPalle() {
	int spostx, sposty;
	cin >> spostx;
	cin >> sposty;
	this->x = x + spostx;
	this->y = y + sposty;
}

bool PallePiene::isVisibile() {
	if (x >= 0 && x <= 300 && y >= 0 && y <= 300) {
		return true;
	}
	else {
		return false;
	}
}

void PallePiene::getColore(int color) {
	this->colore = color;
}

string PallePiene::toString() {
	string s = "";
	s = "coordinate (" + to_string(x) +"; " + to_string(y) + ") colore: ";
	if (colore == 1) {
		s += "rosso ";
	}
	else if (colore == 2) {
		s += "blu ";
	}
	else if (colore == 3) {
		s += "verde ";
	}
	else if (colore == 4) {
		s += "giallo ";
	}
	else if (colore == 5) {
		s += "arancio ";
	}
	if (isVisibile) {
		s += "visibile ";
	}
	else {
		s += "invisibile ";
	}

	return s;
}