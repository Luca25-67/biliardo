#include "palline.h"
using namespace std;

Pallina::Pallina(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Pallina::posizioneFinale()
{
    if (isBuca == false) {
        this-> x += this-> xspostamento;
        this-> y += this-> yspostamento;
    }
    else
    {
        this-> x = 0;
        this-> y = 0;
    }
}

void Pallina::setSpostamento(float sx, float sy)
{
    this->xspostamento = sx;
    this->yspostamento = sy;
}

void Pallina::isInBuca()
{
    isBuca = true;
    this-> xspostamento = 0;
    this-> yspostamento = 0;
}

float Pallina::distanza(const Pallina& p)
{
    return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
}

void Pallina::collide(Pallina& p)
{
    float distTemp = distanza(p);
    if (distTemp <= 2) {
        float tempSx = this->xspostamento;
        float tempSy = this->yspostamento;

        this->xspostamento = p.xspostamento;
        this->yspostamento = p.yspostamento;

        p.xspostamento = tempSx;
        p.yspostamento = tempSy;
    }
}


