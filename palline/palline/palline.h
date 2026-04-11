#pragma once
#include <iostream>
#include <cmath>
using namespace std;

class Pallina {
private:
    float x, y;        
    float xspostamento, yspostamento;      
    bool isBuca;       

public:

    Pallina(float x, float y);

    void posizioneFinale();
    void setSpostamento(float sx, float sy);
    void isInBuca();
    // chat
    float distanza(const Pallina& p);
    // chat
    void collide(Pallina& p);
};