#include <stdio.h>

extern long sum_six_numbers(long a, long b, long c, long d, long e, long f);

int main() {
  long result = sum_six_numbers(1, 2, 3, 4, 5, 6);
  printf("%ld\n", result);
  return 0;
}
