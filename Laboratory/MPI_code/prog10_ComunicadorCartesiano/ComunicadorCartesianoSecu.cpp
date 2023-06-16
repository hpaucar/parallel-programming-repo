#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

#define TAMA 12

int main(int argc, char** argv) {

    int Imagen[TAMA][TAMA];

    //Generamos la imagen
    srand ( time(NULL) );
    for (int i = 0; i < TAMA; i++) {
	for (int j = 0; j < TAMA; j++) {
	    Imagen[i][j] = rand()%256;//Imagen en blanco y negro.
	    cout << "[" << Imagen[i][j] << "]";
	}
	cout << endl;
    }

    int local[TAMA][TAMA];
    //Filtro para difunimar la imagen.
    for (int i = 0; i < TAMA; i++) {
        for (int j = 0; j < TAMA; j++) {
            int nuevo = Imagen[i][j]*2;
            int div = 2;
            if (i != 0) {//
                nuevo += Imagen[i - 1][j];
                div++;
            }
            if ( i < (TAMA-1) ) {//Abajo
                nuevo += Imagen[i + 1][j];
                div++;
            }
            if (j != 0) {//Izquierda
                nuevo += Imagen[i][j - 1];
                div++;
            }
            if (j < (TAMA-1)) {//Derecha
                nuevo += Imagen[i][j + 1];
                div++;
            }
            local[i][j] = (nuevo / div) % 256;
        }
    }

    cout << "++++++++++++++++++++++RESULTADO+++++++++++++++++++++++++" << endl;
    for (int i = 0; i < TAMA; i++) {
	for (int j = 0; j < TAMA; j++) {
	    cout << "[" << local[i][j] << "]";
	}
	cout << endl;
    }

    return 0;
}
