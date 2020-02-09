/*
 ============================================================================
 Name        : SendMessage
 Author      : Herminio Paucar
 Version     :
 Copyright   : Your copyright notice
 Description :
 Compile Command:
 	$ mpiCC -g -Wall -o <CodeName> <CodeName.cpp>
	$ mpiexec  ./<CodeName>
	$ mpiexec -n 10 ./<CodeName>
 ============================================================================
 */

#include "mpi.h"
#include <iostream>
#include <string>
#include <cstring>

using namespace std;
const int MAX_STRING = 100;

int main(int argc, char *argv[])
{
    int nday;
    int ndays [7] = {1, 5, 2, 0, 3, 6, 4};
    // Day's name in order
    std::string sdays []={"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};
    MPI_Status estado;
	char tradmsg[MAX_STRING];
	int comm_sz; /* Number of processes */
	int my_rank; /* My process rank */

    /* Iniciaizamos el MPI */
    	MPI_Init(NULL, NULL);
    	/* Calculamos el total de procesadores que vamos a usar*/
    	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    	/* Seleccionamos cada procesador */
    	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    	/* Hacemos esto para todos los procesadores diferentes del "0" */
    	if (my_rank != 0) {
    		/* Generamos el mensaje para cada procesador y lo guardamos en "tradmsg" */
    		nday = ndays[my_rank-1];
    		char cstr[sdays[nday].size() + 1]; // Declaramos el array "cstr"
    		std::strcpy(cstr, sdays[nday].c_str()); // copiamos el nombre del día a cstr
    		sprintf(tradmsg, "Proc_%d traducio %d en %s", my_rank ,nday ,cstr);
    		/* Enviamos el mensaje  al procesador "0"
    		 * Los tres primeros parametros son para las caracteristicas del mensaje
    		 * (mensaje, tamaño, tipo_mensaje
    		 * Los tres ultimos indican caracteristicas del destino
    		 * (destino, etiqueta, comunicador)*/
    		MPI_Send(tradmsg, strlen(tradmsg) + 1, MPI_CHAR, 0, 0,
    		MPI_COMM_WORLD);
    	} else {
    		/* Imprime el mensaje cabecera del proceso "0" y el total de procesos */
    		printf("Traducciones hechas por los %d procesadores y recibidas por el proc_%d \n"
    				,comm_sz ,my_rank);
    		/* Metodo que recibe el mensaje, posee los mismos 6 argumentos del metodo send */
    		for (int q = 1; q < comm_sz; q++) {
    			MPI_Recv(tradmsg, MAX_STRING, MPI_CHAR, q, 0, MPI_COMM_WORLD, &estado);
    			printf("%s \n", tradmsg);
    		}
    	}

    	MPI_Finalize();
    	return 0;
    } /* main */
