/*
 * Professor: Herminio P.
 * Author: Emilio Francesquini
 * 2018-10-01
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ONE_K 1024
#define ONE_M ONE_K * ONE_K

#define VSIZE (500 * ONE_M) // 500 M
#define ITERS (10 * ONE_M) // 10 M

int main() {

	srand(time(NULL));

	//Vetor com 100 MB
	unsigned char *vec = (unsigned char*) (malloc(VSIZE));
	for (int i = 0; i < VSIZE; i++) {
		vec[i] = rand() % 256;
	}

	/* O fato do acesso à memória ser aleatório causa problemas de mal
	 * uso da cache (falta localidade espacial e causa problemas ao
	 * prefetcher)
	 */
	clock_t start = clock();
	unsigned int sum = 0;
	for (int i = 0; i < ITERS; i++) {
		int pos = rand() % VSIZE;
		if (pos > VSIZE)
			printf("Impossivel. Apenas para forçar a manter pos.");
		else
			sum += vec[pos]; // Tomamos en consideración su posición aleatoria
	}
	double elapsedTime = (double) (clock() - start) / CLOCKS_PER_SEC;
	printf("Tempo total: %lf\n", elapsedTime);

	return 0;
}
