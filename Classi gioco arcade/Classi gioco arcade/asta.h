#pragma once
#include <iostream>
#include <string>
using namespace std;

class Asta {
private:
    int x, y;
    char forma;
    int colore;

public:

    Asta();
    Asta(int x, int y);
    int getX();
    int getY();
    char getForma();
    int getColore();
    bool muovi(int movex, int movey);
    string toString();
    
};
