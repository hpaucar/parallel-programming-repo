/*
 ============================================================================
 Name        : SendMessage
 Author      : Herminio Paucar
 Version     :
 Copyright   : Your copyright notice
 Description : Obtenido el numero de procesos (size) y el rango (rank) el envio
 del mensaje se realiza al proceso con un rango mayor en una unidad, por tanto
 el proceso con ese rango debe indicar que quiere recibir un mensaje del proceso
 con un rango inferior en una unidad al suyo.
 En nuestro programa debemos hacer una distinción ya que no todos los procesos hacen
 lo mismo, el primero no recibirá de nadie y el ultimo no enviara a nadie, esto se
 puede especificar mediante condiciones que filtren el rango del proceso.
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
    int rank, size, contador;
    MPI_Status estado;

    MPI_Init(&argc, &argv); // Inicializamos la comunicacion de los procesos
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el numero total de hebras
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos el valor de nuestro identificador

    if(rank == 0){

        MPI_Send(&rank //referencia al vector de elementos a enviar
                ,1 // tamaño del vector a enviar
                ,MPI_INT // Tipo de dato que envias
                ,rank+1 // pid del proceso destino
                ,0 //etiqueta
                ,MPI_COMM_WORLD); //Comunicador por el que se manda
    }else{
        MPI_Recv(&contador // Referencia al vector donde se almacenara lo recibido
                ,1 // tamaño del vector a recibir
                ,MPI_INT // Tipo de dato que recibe
                ,rank-1 // pid del proceso origen de la que se recibe
                ,0 // etiqueta
                ,MPI_COMM_WORLD // Comunicador por el que se recibe
                ,&estado); // estructura informativa del estado

        cout<<"Soy el proceso "<<rank<<" y he recibido "<<contador<<endl;
        contador++;
        if(rank != size-1)
            MPI_Send(&contador, 1 ,MPI_INT ,rank+1 , 0 ,MPI_COMM_WORLD);

    }

    // Terminamos la ejecucion de las hebras, despues de esto solo existira
    // la hebra 0
    // ¡Ojo! Esto no significa que las demas hebras no ejecuten el resto
    // de codigo despues de "Finalize", es conveniente asegurarnos con una
    // condicion si vamos a ejecutar mas codigo (Por ejemplo, con "if(rank==0)".
    MPI_Finalize();
    return 0;
}
