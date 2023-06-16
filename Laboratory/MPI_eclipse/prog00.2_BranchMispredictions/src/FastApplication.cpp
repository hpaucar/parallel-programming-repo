/*
 * Professor: Herminio P.
 * Author: Emilio Francesquini <e.francesquini@ufabc.edu.br>
 * 2018-10-01
 *
 * Adaptado de
 * https://stackoverflow.com/questions/11227809/why-is-it-faster-to-process-a-sorted-array-than-an-unsorted-array
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int compare(const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}

int main() {

  srand(time(NULL));
  int arraySize = 32768;
  int data[arraySize];

  for (int i = 0; i < arraySize; i++)
    data[i] = rand() % 256;

  /* Os acessos são feitos sequencialmente à um vetor com elementos
   * que apesar de aleatórios estão em ordem. Neste caso o branch
   * predictor é acerta se o branch será tomado na maioria dos
   * casos.
   */
  qsort(data, arraySize, sizeof(int), compare);

  clock_t start = clock();
  long long sum = 0;
  for (int i = 0; i < 100000; i++){
    for (int c = 0; c < arraySize; ++c) {
      if (data[c] >= 128)
        sum += data[c];
    }
  }
  double elapsedTime = (double)(clock() - start) / CLOCKS_PER_SEC;

  printf ("Tempo total: %lf\n", elapsedTime);
  printf ("Soma: %lld\n", sum);
}
