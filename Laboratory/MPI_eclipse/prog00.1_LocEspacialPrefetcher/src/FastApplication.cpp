/*
 * Professor: Herminio P.
 * Author: Emilio Francesquini <e.francesquini@ufabc.edu.br>
 * 2018-10-01
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ONE_K 1024
#define ONE_M ONE_K * ONE_K

#define VSIZE (500 * ONE_M)
#define ITERS (10 * ONE_M)

int main() {

  srand(time(NULL));

  //Vetor com 100 MB
  unsigned char *vec = (unsigned char *) malloc (VSIZE);
  for (int i = 0; i < VSIZE; i++) {
    vec[i] = rand() % 256;
  }

  /* Apesar de fazermos o sorteio dos números aleatórios neste caso os
   * acessos são sequenciais. Privilegiam o prefetcher e tem uma boa
   * localidade espacial.
   */
  clock_t start = clock();
  unsigned int sum = 0;
  for (int i = 0; i < ITERS; i++) {
    int pos = rand() % VSIZE;
    if (pos > VSIZE)
      printf("Impossivel. Apenas para forçar a manter pos.");
    else
      sum += vec[i]; // Accedemos a cada elemento tomando en cuenta su indice
  }
  double elapsedTime = (double)(clock() - start) / CLOCKS_PER_SEC;
  printf ("Tempo total: %lf\n", elapsedTime);

  return 0;
}
