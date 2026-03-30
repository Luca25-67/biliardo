#include <string>
#include "asta.h"
using namespace std;

Asta::Asta()
{
    this->x = 0;
    this->y = 0;
    this->forma = '|';
    this->colore = 6;
}

Asta::Asta(int x, int y)
{
    this->x = x;
    this->y = y;
    this->forma = '|';
    this->colore = 6;
}

string Asta::toString()
{
    string s = "";
    s += "x: " + std::to_string(x);
    s += " y: " + std::to_string(y);
    s += " colore: " + std::to_string(colore);
    s += " forma: "; s += forma;
    return s;
}

bool Asta::muovi(int movex, int movey)
{
    x += movex;
    y += movey;
    return true;
}