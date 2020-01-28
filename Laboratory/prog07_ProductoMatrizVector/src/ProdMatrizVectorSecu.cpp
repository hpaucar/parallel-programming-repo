#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char * argv[]) {

	long 	**A, // Matriz a multiplicar
			*x, // Vector que vamos a multiplicar
			*comprueba; // Guarda el resultado final (calculado secuencialmente), su valor

	int n;
	if (argc <= 1) { // si no se pasa por parametro el tamaño de la matriz,
					 //se coge por defecto el numero de procesadores
		cout << "Falta el tamanio de la matriz, por defecto cogemos 10" << endl;
		n = 10;
	} else
		n = atoi(argv[1]);

	A = new long *[n];       //reservamos espacio para las n filas de la matriz.
	x = new long[n];                    //reservamos espacio para el vector.

	//Rellena la matriz
	A[0] = new long[n * n];
	for (unsigned int i = 1; i < n; i++) {
		A[i] = A[i - 1] + n;
	}

	// Rellena A y x con valores aleatorios
	srand(time(0));
	cout << "La matriz y el vector generados son " << endl;
	for (unsigned int i = 0; i < n; i++) {
		for (unsigned int j = 0; j < n; j++) {
			if (j == 0)
				cout << "[";
			A[i][j] = rand() % 1000;
			cout << A[i][j];
			if (j == n - 1)
				cout << "]";
			else
				cout << "  ";
		}
		x[i] = rand() % 100;
		cout << "\t  [" << x[i] << "]" << endl;
	}
	cout << "\n";

	comprueba = new long[n];
	//Calculamos la multiplicacion secuencial para
	//despues comprobar que es correcta la solucion.
	for (unsigned int i = 0; i < n; i++) {
		comprueba[i] = 0;
		for (unsigned int j = 0; j < n; j++) {
			comprueba[i] += A[i][j] * x[j];
		}
	}

	cout << "El resultado obtenido y el esperado son:" << endl;
	for (unsigned int i = 0; i < n; i++) {
		cout << comprueba[i] << endl;
	}

	delete[] comprueba;
	delete[] A[0];

	delete[] x;
	delete[] A;

	return 0;

}
