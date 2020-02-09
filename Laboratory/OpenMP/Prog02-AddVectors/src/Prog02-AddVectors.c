/*
 ============================================================================
 Name        : Prog02-AddVectors.c
 Author      : Herminio
 Version     :
 Copyright   : Your copyright notice
 Description : Hello OpenMP World in C
 ============================================================================
 */

#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

	float A[2048];
	float B[2048];
	float C[2048];
	int i;
	for (i = 0; i < 2048; i++) {
		A[i] = 2;
		B[i] = 3;
	}

	#pragma omp parallel
	{
		int id = omp_get_thread_num();
		int nt = omp_get_num_threads();
		int size = (int) 2048 / nt;
		int ini = id * size;
		int fin = ini + size - 1;
		int j;
		for (j = ini; j <= fin; j++) {
			C[j] = A[j] + B[j];
		}
	}
	for (i = 0; i < 2048; i++) {
		printf("C[%d] = %f \n", i, C[i]);
	}

	return 0;
}

