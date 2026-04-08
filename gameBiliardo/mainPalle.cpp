#include <iostream>
#include "PallePiene.h"
using namespace std;

void mainPalle() {
	int scelta = 0, sceltaPalla = 0, sceltaSeContinuareONo = 0;
	PallePiene rossa = PallePiene(100, 100);
	PallePiene gialla = PallePiene(200, 100);
	PallePiene verde = PallePiene(200, 200);
	rossa.getColore(1);
	gialla.getColore(4);
	verde.getColore(3);

	cout << rossa.toString() << endl;
	cout << gialla.toString() << endl;
	cout << verde.toString() << endl;

	do {
		do {
			cout << "vuoi muovere la pallina?" << endl;
			cout << "1) si" << endl;
			cout << "2) no" << endl;
			cin >> scelta;
		} while (scelta < 1 || scelta > 2);
		if (scelta == 1) {
			do {
				cout << "quale pallina vuoi spostare?" << endl;
				cout << "1) rossa" << endl;
				cout << "2) gialla" << endl;
				cout << "3) verde" << endl;
				cin >> sceltaPalla;
			} while (sceltaPalla < 1 || sceltaPalla > 3);
			cout << "dimmi di quanto vuoi spostare la palla (prima x poi y)" << endl;
			switch (sceltaPalla) {
			case 1: {
				rossa.muoviPalle();
				cout << rossa.toString();
				break;
			}
			case 2: {
				gialla.muoviPalle();
				cout << gialla.toString();
				break;
			}
			case 3: {
				verde.muoviPalle();
				cout << verde.toString();
				break;
			}
			default: {
				break;
			}
			}
		}
		do{
			cout << endl;
			cout << "vuoi continuare?" << endl;
			cout << "1) si" << endl;
			cout << "2) no" << endl;
			cin >> sceltaSeContinuareONo;
		} while (scelta < 1 || scelta > 2);
	} while (sceltaSeContinuareONo != 2);

}