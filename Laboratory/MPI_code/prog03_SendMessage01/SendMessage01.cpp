/*
 ============================================================================
 Name        : SendMessage
 Author      : Herminio Paucar
 Version     :
 Copyright   : Your copyright notice
 Description : En este código de inicio se puede ver el funcionamiento de las
 	 	 	   funciones de envío y recepción. Lo que hace es que cada proceso
 	 	 	   se envía a sí mismo el mensaje deseado.
 Compile Command:
 	$ mpiCC -g -Wall -o <CodeName> <CodeName.cpp>
	$ mpiexec  ./<CodeName>
	$ mpiexec -n 10 ./<CodeName>
 ============================================================================
 */

#include "mpi.h"
#include <iostream>
using namespace std;
 
int main(int argc, char *argv[])
{
    int rank, contador;
    MPI_Status estado;

    MPI_Init(&argc, &argv); // Inicializamos la comunicacion de los procesos
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos el valor de nuestro identificador

    //Envia y recibe mensajes
    MPI_Send(&rank //referencia al vector de elementos a enviar
            ,1 // tamaño del vector a enviar
            ,MPI_INT // Tipo de dato que envias
            ,rank // pid del proceso destino
            ,0 //etiqueta
            ,MPI_COMM_WORLD); //Comunicador por el que se manda

    MPI_Recv(&contador // Referencia al vector donde se almacenara lo recibido
            ,1 // tamaño del vector a recibir
            ,MPI_INT // Tipo de dato que recibe
            ,rank // pid del proceso origen de la que se recibe
            ,0 // etiqueta
            ,MPI_COMM_WORLD // Comunicador por el que se recibe
            ,&estado); // estructura informativa del estado

	cout<< "Soy el proceso "<<rank<<" y he recibido "<<contador<<endl;

    MPI_Finalize();
    return 0;
}


