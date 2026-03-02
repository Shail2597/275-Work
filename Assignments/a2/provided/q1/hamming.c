#include <stdio.h>
#include <stdlib.h>

unsigned int string_to_uint(char *str) {
  unsigned int res = 0;
  int idx = 0;

  while (str[idx] != '\0') {
    res = res * 10 + (str[idx] - '0');
    idx++;
  }

  return res;
}

int main(int argc, char *argv[]) {

  unsigned int val1 = string_to_uint(argv[1]);
  unsigned int val2 = string_to_uint(argv[2]);
  unsigned int radix = string_to_uint(argv[3]);

  unsigned int diff_count = 0;

  int active1 = (val1 > 0);
  int active2 = (val2 > 0);

  while (active1 || active2) {
    unsigned int rem1 = val1 % radix;
    unsigned int rem2 = val2 % radix;

    if (active1 != active2) {
      diff_count++;
    } else if (rem1 != rem2) {
      diff_count++;
    }

    val1 = val1 / radix;
    val2 = val2 / radix;
    active1 = (val1 > 0);
    active2 = (val2 > 0);
  }

  printf("%u\n", diff_count);

  return 0;
}