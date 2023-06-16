#include <algorithm>
#include <vector>
#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	int rank, size, tama;
	vector<int> Global; //Vector a ordenar
	vector<int> *Local; //parte del vector

	MPI_Init(&argc, &argv); //iniciamos el entorno MPI
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); //obtenemos el identificador del proceso
	MPI_Comm_size(MPI_COMM_WORLD, &size); //obtenemos el numero de procesos

	if (size % 2 != 0) { //El numero de procesos deberia debe ser par para aplicar este algoritmo
		cout << "El numero de procesos debe ser par" << endl;
		MPI_Abort(MPI_COMM_WORLD, 1); //abandonamos la ejecucion.
	}

	if (argc < 2) {
		if (rank == 0)
			cout<<"No recibio parametro con el tamaño de vector, por defecto sera 1000"<< endl;
		tama = 1000;
	} else {
		tama = atoi(argv[1]);
	}

	if (rank == 0) { //el proceso 0 genera un vector desordenado.
		for (int i = 0; i < tama; ++i) {
			Global.push_back(rand() % 1000);
		}
	}
	Local = new vector<int>(tama / size); // reservamos espacio para el vector local a cada proceso.

	//Repartimos el vector entre todos los procesos.

	MPI_Scatter(&Global[0], tama / size, MPI_INT, &((*Local)[0]), tama / size,
			MPI_INT, 0, MPI_COMM_WORLD);

	//Cada proceso ordena su parte.
	sort(Local->begin(), Local->end());

	vector<int> *ordenado;
	MPI_Status status;
	int paso = 1;

	//Ahora comienza el proceso de mezcla.
	while (paso < size) {
		// Cada pareja de procesos
		if (rank % (2 * paso) == 0) // El izquierdo recibe el vector y mezcla
		{
			if (rank + paso < size) // los procesos sin pareja esperan.
					{
				vector<int> localVecino(Local->size());
				ordenado = new vector<int>(Local->size() * 2);

				MPI_Recv(&localVecino[0], localVecino.size(), MPI_INT,
						rank + paso, 0, MPI_COMM_WORLD, &status);
				merge(Local->begin(), Local->end(), localVecino.begin(),
						localVecino.end(), ordenado->begin());

				delete Local;
				Local = ordenado;
				ordenado = NULL;
			}
		} else // El derecho envia su vector ordenado y termina
		{
			int vecino = rank - paso;
			MPI_Send(&((*Local)[0]), Local->size(), MPI_INT, vecino, 0,
					MPI_COMM_WORLD);
			break; //Sale del bucle
		}
		paso = paso * 2; // el paso se duplica ya que el numero de procesos se reduce a la mitad.
	}

	if (rank == 0) {
		cout << endl << "[";
		for (unsigned int i = 0; i < Local->size(); ++i) {
			cout << (*Local)[i] << " , ";
		}
		cout << "]" << endl;
	}

	MPI_Finalize();
	return 0;
}
