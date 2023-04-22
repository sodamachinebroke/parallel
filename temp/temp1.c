#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 20
#define NUM_THREADS 4

double a[N];
double product = 1.0;

void *calculate_product(void *arg) {
  int tid = *(int *)arg;
  int start = tid * N / NUM_THREADS;
  int end = (tid + 1) * N / NUM_THREADS;

  for (int i = start; i < end; i++) {
    product *= a[i];
  }

  pthread_exit(NULL);
}

int main() {
  int i, rc;
  pthread_t threads[NUM_THREADS];
  int thread_args[NUM_THREADS];

  // Fill array with random numbers between 0.1 and 10.0
  srand(12345);
  for (i = 0; i < N; i++) {
    a[i] = (double)rand() / (double)RAND_MAX * 9.9 + 0.1;
    printf("%lf\n", a[i]);
  }

  // Create threads and calculate product
  for (i = 0; i < NUM_THREADS; i++) {
    thread_args[i] = i;
    rc = pthread_create(&threads[i], NULL, calculate_product, &thread_args[i]);
    if (rc) {
      printf("ERROR: return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }

  // Wait for threads to finish and collect results
  for (i = 0; i < NUM_THREADS; i++) {
    rc = pthread_join(threads[i], NULL);
    if (rc) {
      printf("ERROR: return code from pthread_join() is %d\n", rc);
      exit(-1);
    }
  }

  printf("The product of the elements in the array is %lf\n", product);
  
  return 0;
}
