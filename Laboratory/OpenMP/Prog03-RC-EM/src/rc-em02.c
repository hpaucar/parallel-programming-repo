/*
 ============================================================================
 Name        : FirstOpenMP.c
 Author      : Herminio
 Version     :
 Copyright   : Your copyright notice
 Description : Hello OpenMP World in C
 ============================================================================
 */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
/**
 * Hello OpenMP World prints the number of threads and the current thread id
 */
int main(int argc, char *argv[]) {

	printf("\n 01 Fuera de la region Paralela ... \n\n");
	int id, nt;

	/* This creates a team of threads; each thread has own copy of variables  */
	#pragma omp parallel private(id, nt)
	{
		id = omp_get_thread_num();
		nt = omp_get_num_threads();

		printf("From thread number %d de un total %d \n", id, nt);
	}

	printf("\n 02 Fuera de la region Paralela ...\n\n");

	return 0;
}


