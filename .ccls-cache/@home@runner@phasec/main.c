#include <complex.h>
#include <math.h>
#include <stdio.h>

// Compute the cross-correlation between two signals x and y
void cross_correlation(const double x[], const double y[], int N,
                       double result[]) {
  int n, k;

  // Clear the result array
  for (n = 0; n < 2 * N - 1; ++n)
    result[n] = 0;

  // Compute the cross-correlation
  for (k = -N + 1; k < N; ++k)
    for (n = 0; n < N; ++n)
      result[N + k - 1] += x[n] * y[n - k];
}

// Find the index of the maximum value in an array
int find_max_index(const double x[], int N) {
  int n, index = 0;
  double max_value = x[0];

  for (n = 1; n < N; ++n)
    if (x[n] > max_value) {
      max_value = x[n];
      index = n;
    }

  return index;
}

// Compute the phase shift between two signals x and y
double phase_shift(const double x[], const double y[], int N) {
  double result[2 * N - 1];
  int max_index;
  double phase_shift;

  cross_correlation(x, y, N, result);
  max_index = find_max_index(result, 2 * N - 1);
  phase_shift = (double)(max_index - N + 1) / N;

  return phase_shift;
}

int main(void) {
  double x[10] = {1, 2, 3, 4, 0, 5, 7, 8, 0, 0};
  double y[10] = {1, 2, 3, 4, 5, 0, 9, 8, 0, 0};
  double ret = phase_shift(x, y, 10);
  printf("%f\n", ret);
}