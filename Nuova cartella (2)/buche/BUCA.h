#pragma once
#include <iostream>
#include <string>
using namespace std;

class Buca {
private:
    int x, y;
    int raggio;
    bool piena;

public:
    Buca();
    Buca(int x, int y, int r);

    int getX();
    int getY();
    int getRaggio();
    bool isPiena();

    bool controllaIngresso(int px, int py);
    string toString();
};
