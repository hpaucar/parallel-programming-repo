#include <stdio.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "mpi/mpi.h"
using namespace std;

#define TAMA 12
#define NP 9

int main(int argc, char** argv) {
	int rank, size, rank_cart, arriba, abajo, izq, der; //Vecinos en la topologia 2D.

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Status status;
	MPI_Comm COMM_CART; //Guardaremos el comunicador cartesiano.
	MPI_Datatype subImagen; //Tipo de dato para una submatriz.

	int dims[] = //tamaño de cada dimension del comunicador cartesiano
			{ ((int) sqrt(size)), size / ((int) sqrt(size)) };
	int periods[] = { 0, 0 }; //No sera periodica ninguna dimension.
	int tama_local = TAMA / dims[0];
	int coord[2]; //Podemos almacenar coordenadas 2D
	int origen; //almacenaremos el rango del proceso 0 dentro del COMM_CART
	int ImagenLocal[TAMA][TAMA];

	if (size != NP && rank == 0) {
		cout << "El numero de procesos debe ser :" << NP << endl;
		MPI_Abort(MPI_COMM_WORLD, 1);
	}

	MPI_Cart_create(MPI_COMM_WORLD //A partir de los procesos de COMM_WORLD.
			, 2 //Creamos una malla de 2 dimensiones.
			, dims //Indicamos el tamaño de cada dimension.
			, periods //Indicamos la periodicidad de cada dimension.
			, true //Permitimos que MPI organice los procesos.
			//ya no tienen porque tener el mismo rango que antes.
			, &COMM_CART);            //Guardamos el nuevo comunicador.

	//Si tubieramos mas procesos que espacio en la malla recibira MPI_COMM_NULL
	if (COMM_CART != MPI_COMM_NULL) {
		MPI_Comm_rank(COMM_CART, &rank_cart);         //Obtenemos el nuevo rango

		//Creamos el tipo de dato subImagen
		MPI_Type_vector(tama_local            //numero de bloques
				, tama_local           //numero de enteros dentro de cada bloque
				, TAMA            //Cada una fila se coge un nuevo bloque
				, MPI_INT            //Cogen enteros
				, &subImagen);            //Guardamos el tipo de dato
		MPI_Type_commit(&subImagen);    //Confirmamos el tipo para poder usarlo.

		if (rank == 0) {            //Proceso 0 genera La imagen y la reparte
			srand(time(NULL));
			for (int i = 0; i < TAMA; i++) {
				for (int j = 0; j < TAMA; j++) {
					ImagenLocal[i][j] = rand() % 256; //Imagen en blanco y negro.
					cout << "[" << ImagenLocal[i][j] << "]";
				}
				cout << endl;
			}

			int aux;
			for (int i = 0; i < dims[0]; i++)            //para cada proceso
				for (int j = 0; j < dims[1]; j++) {       // se reparte su parte
					coord[0] = i;
					coord[1] = j;
					MPI_Cart_rank(COMM_CART //Para un proceso en este comunicador
							, coord            //con estas coordenadas
							, &aux);            //Tiene el este rango.

					if (aux != rank_cart) {
						//enviamos las subimagenes.
						MPI_Send(&ImagenLocal[i * tama_local][j * tama_local],
								1, subImagen, aux, 0, COMM_CART);
					}
				}
			MPI_Cart_coords(COMM_CART      //Para un proceso en este comunicador
					, rank_cart            //con este rango
					, 2            //como maximo en 2 coordenadas
					, coord);            //Dame sus coordenadas
		} else {
			MPI_Cart_coords(COMM_CART, rank_cart, 2, coord);
			MPI_Recv(&ImagenLocal[tama_local * coord[0]][tama_local * coord[1]],
					1, subImagen, MPI_ANY_SOURCE, 0, COMM_CART, &status);
			origen = status.MPI_SOURCE;
		}

	}

	//creamos este tipo de dato para almacenar columnas
	MPI_Datatype vectorVertical;
	MPI_Type_vector(tama_local, 1, TAMA, MPI_INT, &vectorVertical);
	MPI_Type_commit(&vectorVertical);

	MPI_Cart_shift(COMM_CART            //en el comunicador cartesiano
			, 0 // en la dimension 0
			, 1 // con un desplazamiento de 1 sobre el actual
			, &arriba //dame los vecinos (origen)
			, &abajo); //dame los vecinos (destino)
	//lo mismo para la dimension 1
	MPI_Cart_shift(COMM_CART, 1, 1, &izq, &der);

	if (arriba != MPI_PROC_NULL) //si tengo vecino arriba mando mi fila superior
		MPI_Send(&ImagenLocal[tama_local * coord[0]][tama_local * coord[1]],
				tama_local, MPI_INT, arriba, 0, COMM_CART);

	if (abajo != MPI_PROC_NULL)  //si tengo vecino abajo recibo su fila superior
		MPI_Recv(
				&ImagenLocal[(tama_local * coord[0]) + tama_local][tama_local
						* coord[1]], tama_local, MPI_INT, abajo, 0, COMM_CART,
				&status);

	if (abajo != MPI_PROC_NULL)   //si tengo vecino abajo mando mi fila inferior
		MPI_Send(
				&ImagenLocal[(tama_local * coord[0]) + tama_local - 1][tama_local
						* coord[1]], tama_local, MPI_INT, abajo, 0, COMM_CART);

	if (arriba != MPI_PROC_NULL) //si tengo vecino arriba recibo su fila inferior
		MPI_Recv(
				&ImagenLocal[(tama_local * coord[0]) - 1][tama_local * coord[1]],
				tama_local, MPI_INT, arriba, 0, COMM_CART, &status);

	if (izq != MPI_PROC_NULL) //si tengo vecino izquierda mando mi columna izquida.
		MPI_Send(&ImagenLocal[tama_local * coord[0]][tama_local * coord[1]], 1,
				vectorVertical, izq, 0, COMM_CART);

	if (der != MPI_PROC_NULL) //si tengo vecino derecha recibo su columna derecha.
		MPI_Recv(
				&ImagenLocal[tama_local * coord[0]][(tama_local * coord[1])
						+ tama_local], 1, vectorVertical, der, 0, COMM_CART,
				&status);

	if (der != MPI_PROC_NULL) //si tengo vecino derecha mando mi columna derecha
		MPI_Send(
				&ImagenLocal[tama_local * coord[0]][(tama_local * coord[1])
						+ tama_local - 1], 1, vectorVertical, der, 0,
				COMM_CART);

	if (izq != MPI_PROC_NULL) //si tengo vecino izquierda recibo su columna derecha.
		MPI_Recv(
				&ImagenLocal[tama_local * coord[0]][(tama_local * coord[1]) - 1],
				1, vectorVertical, izq, 0, COMM_CART, &status);

	//APLICAMOS el filtro localmente.
	int local[tama_local][tama_local];
	for (int i = 0; i < tama_local; i++) {
		for (int j = 0; j < tama_local; j++) {
			int nuevo = ImagenLocal[tama_local * coord[0] + i][tama_local
					* coord[1] + j] * 2;
			int div = 2;
			if (coord[0] != 0) {    //Arriba
				nuevo += ImagenLocal[tama_local * coord[0] + i - 1][tama_local
						* coord[1] + j];
				div++;
			}
			if (coord[0] < dims[0] - 1) {    //Abajo
				nuevo += ImagenLocal[tama_local * coord[0] + i + 1][tama_local
						* coord[1] + j];
				div++;
			}
			if (coord[1] != 0) {    //Izquierda
				nuevo += ImagenLocal[tama_local * coord[0] + i][tama_local
						* coord[1] + j - 1];
				div++;
			}
			if (coord[1] < dims[0] - 1) {    //Derecha
				nuevo += ImagenLocal[tama_local * coord[0] + i][tama_local
						* coord[1] + j + 1];
				div++;
			}
			local[i][j] = (nuevo / div) % 256;
		}
	}

	if (rank != 0) {    //Si no soy el proceso 0 mando mi matriz
		MPI_Send(local, tama_local * tama_local, MPI_INT, origen, 0, COMM_CART);
	} else {    //Si soy el 0 recibo las partes de los demas procesos.
		for (int i = 0; i < tama_local; i++)
			for (int j = 0; j < tama_local; j++)
				ImagenLocal[(tama_local * coord[0]) + i][(tama_local * coord[1])
						+ j] = local[i][j];
		for (int i = 0; i < size - 1; i++) {
			MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, COMM_CART, &status);
			MPI_Cart_coords(COMM_CART, status.MPI_SOURCE, 2, coord);
			MPI_Recv(&ImagenLocal[tama_local * coord[0]][tama_local * coord[1]],
					1, subImagen, status.MPI_SOURCE, 0, COMM_CART, &status);

		}
		cout << "++++++++++++++++++++++RESULTADO+++++++++++++++++++++++++"
				<< endl;
		for (int i = 0; i < TAMA; i++) {
			for (int j = 0; j < TAMA; j++) {
				cout << "[" << ImagenLocal[i][j] << "]";
			}
			cout << endl;
		}
	}

	MPI_Type_free(&subImagen);    //liberamos el tipo de dato subImagen
	MPI_Type_free(&vectorVertical);    //liberamos el tipo dato vectorVertical
	MPI_Finalize();
	return 0;
}
