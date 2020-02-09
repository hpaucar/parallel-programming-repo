#include "mpi.h"
#include <vector>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	int rank, size;

	MPI_Init(&argc, &argv); //iniciamos el entorno MPI
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); //obtenemos el identificador del proceso
	MPI_Comm_size(MPI_COMM_WORLD, &size); //obtenemos el numero de procesos

	MPI_Comm comm // nuevo comunicador para pares o impares
			, comm_inverso; // nuevo para todos los procesos pero con rank inverso.
	int rank_inverso, size_inverso;
	int rank_nuevo, size_nuevo;
	int a;
	int b;

	if (rank == 0) {
		a = 2000;
		b = 1;
	} else {
		a = 0;
		b = 0;
	}

	int color = rank % 2;
	// creamos un nuevo cominicador
	MPI_Comm_split(MPI_COMM_WORLD // a partir del comunicador global.
			, color // los del mismo color entraran en el mismo comunicador
			// lo pares tiene color 0 y los impares 1.
			, rank, // indica el orden de asignacion de rango dentro de los nuevos comunicadores
			&comm); // Referencia al nuevo comunicador creado.
	// creamos un nuevo comunicador inverso.
	MPI_Comm_split(MPI_COMM_WORLD, // a partir del comunicador global.
			0 // el color es el mismo para todos.
			, -rank // el orden de asignacion para el nuevo rango es el inverso al actual.
			, &comm_inverso); // Referencia al nuevo comunicador creado.

	MPI_Comm_rank(comm, &rank_nuevo); // obtenemos el nuevo rango asignado dentro de comm
	MPI_Comm_size(comm, &size_nuevo); // obtenemos numero de procesos dentro del comunicador

	MPI_Comm_rank(comm_inverso, &rank_inverso); // obtenemos el nuevo rango asignado en comm_inverso
	MPI_Comm_size(comm_inverso, &size_inverso); // obtenemos numero de procesos dentro del comunicador

	//Probamos a enviar datos por distintos comunicadores
	MPI_Bcast(&b, 1, MPI_INT, size - 1, // el proceso con rango 0 dentro de MPI_COMM_WORLD sera root
	comm_inverso);
	MPI_Bcast(&a, 1, MPI_INT, 0, // el proceso con rango 0 dentro de comm sera root
			comm);

	cout << "Soy el proceso " << rank << " de " << size
			<< " dentro de MPI_COMM_WORLD,"
					"\n\t mi rango en COMM_nuevo es " << rank_nuevo << ", de "
			<< size_nuevo << ", aqui he recibido el valor " << a
			<< ",\n\ten COMM_inverso mi rango es " << rank_inverso << " de "
			<< size_inverso << " aqui he recibido el valor " << b << "\n"
			<< endl;

	MPI_Finalize();
	return 0;
}
