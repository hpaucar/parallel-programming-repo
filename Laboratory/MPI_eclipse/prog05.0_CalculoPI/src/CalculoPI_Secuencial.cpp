/*
 * https://es.wikipedia.org/wiki/N%C3%BAmero_%CF%80
 *  ============================================================================
 Name        : Calculate PI value
 Author      : Herminio Paucar
 Version     :
 Copyright   : Your copyright notice
 Description : Paralelizar el calculo de la aproximación del numero PI indicando un
 factor de precisión. El numero PI se define como la integral 0 a 1 de 4/(1+x*x), es
 decir, el área que forma.
 La aproximación de una integral mediante la suma de Riemann permite dividir el trabajo
 en unidades independientes, siendo un factor de precision el numero de divisiones.
 El factor de precisión puede pedirlo el proceso 0 y repartirlo a los otros procesos
 mediante MPI_Bcast. Despues de que cada proceso calcule su parte se han de reunir todas
 las partes en el proceso 0 para mostrar el resultado con MPI_Reduce.
 Objetivos	 : Repartir trabajo entre procesos, Aprender a usar MPI_Bcast y
 	 	 	   Aprender a usar MPI_Reduce.
 *
 * */
#include <math.h>
#include <cstdlib> // Incluido para el uso de atoi
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {

	// Calculo de PI
	int n;
	cout << "introduce la precision del calculo (n > 0): ";
	cin >> n;
	double PI25DT = 3.141592653589793238462643;
	double h = 1.0 / (double) n;
	double sum = 0.0;
	for (int i = 1; i <= n; i++) {
		double x = h * ((double) i - 0.5);
		sum += (4.0 / (1.0 + x * x));
		cout<<endl<<x;
	}
	double pi = sum * h;
	cout << "El valor aproximado de PI es: " << pi << ", con un error de "
			<< fabs(pi - PI25DT) << endl;
	return 0;

}
