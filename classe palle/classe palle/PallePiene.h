#pragma once
#include <iostream>
#include <string>
using namespace std;
class PallePiene
{
private:
	int x, y;
	char colore;

public:
	PallePiene(int xIniziale, int yIniziale);
	void muoviPalle();
	void getColore(int colore);
	bool isVisibile();
	string toString();
};

