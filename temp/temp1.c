#include <stdio.h>
#include <stdlib.h>

#define N 20
#define RECURSIVE_DEPTH 4

double recursive_product(double a[], int n, int depth) {
  if (n == 0) {
    return 1.0;
  } else if (n == 1 || depth == 0) {
    return a[0];
  } else {
    int mid = n / 2;
    return recursive_product(a, mid, depth - 1) * recursive_product(&a[mid], n - mid, depth - 1);
  }
}

int main() {
  int i;
  double a[N];
  
  // Fill array with random numbers between 0.1 and 10.0
  srand(12345);
  for (i = 0; i < N; i++) {
    a[i] = (double)rand() / (double)RAND_MAX * 9.9 + 0.1;
    printf("%lf\n", a[i]);
  }

  // Calculate product recursively
  double product = recursive_product(a, N, RECURSIVE_DEPTH);

  printf("The product of the elements in the array is %lf\n", product);
  
  return 0;
}
