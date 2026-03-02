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

  if (argc != 4) {
    fprintf(stderr, "Usage: ./hamming_sample n1 n2 base\n");
    return 1;
  }

  int startsWithInteger(char *str) {
    int i = 0;

    // Optional sign
    if (str[i] == '+' || str[i] == '-') {
        i++;
    }

    // Must have at least one digit
    if (str[i] < '0' || str[i] > '9') {
        return 0;   // false
    }

    return 1;       // true
}

if (!startsWithInteger(argv[1])) {
    fprintf(stderr, "First argument must be an integer\n");
    return 1;
}

if (!startsWithInteger(argv[2])) {
    fprintf(stderr, "Second argument must be an integer\n");
    return 1;
}

if (!startsWithInteger(argv[3])) {
    fprintf(stderr, "Third argument must be an integer\n");
    return 1;
}

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