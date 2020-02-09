/*
 * Profesor: Herminio P.
 * Author: Emilio Francesquini <e.francesquini@ufabc.edu.br>
 * 2018-10-01
 *
 * Adaptado de
 * https://stackoverflow.com/questions/11227809/why-is-it-faster-to-process-a-sorted-array-than-an-unsorted-array
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

  srand(time(NULL));
  int arraySize = 32768;
  int data[arraySize];

  for (int i = 0; i < arraySize; i++)
    data[i] = rand() % 256;

  /* Os acessos são feitos sequencialmente à um vetor com elementos
   * aleatórios. O branch predictor não é capaz de determinar se o
   * branch será tomado ou não na maior parte das vezes.
   */
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
