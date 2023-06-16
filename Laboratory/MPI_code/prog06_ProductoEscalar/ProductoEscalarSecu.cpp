#include <vector>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	int tama;

	if (argc < 2) {
		cout << "No se ha especificado numero de elementos, por defecto sera "
				<< 100;
		cout << "\n Uso: <ejecutable> <cantidad>" << endl;
		tama = 100;
	} else {
		tama = atoi(argv[1]);
	}

	// Creacion y relleno de los vectores
	vector<long> VectorA, VectorB;
	VectorA.resize(tama, 0);
	VectorB.resize(tama, 0);
	for (long i = 0; i < tama; ++i) {
		VectorA[i] = i + 1; // Vector A recibe valores 1, 2, 3, ..., tama
		VectorB[i] = (i + 1) * 10; // Vector B recibe valores 10, 20, 30, ..., tama*10
	}

	// Calculo de la multiplicacion escalar entre vectores
	long total = 0;
	for (long i = 0; i < tama; ++i) {
		total += VectorA[i] * VectorB[i];
	}

	cout << "Total = " << total << endl;
	return 0;
}
