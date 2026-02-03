#include <stdio.h>

int isws(char c) {
  return (c == ' ' || c == '\n' || c == '\t' || c == '\r');
}
int main() {
  int cc = 0;
  int wc = 0;
  int lc = 0;
  char c = 0;
  char prevChar = ' ';
  while ((c = getchar()) != EOF) {
    // techinically recall that getchar return an int
    // and I should be checking for all faliure there
    ++cc;
    if (c == '\n') ++lc;
    if (isws(prevChar) && !isws(c)) ++wc;
    prevChar = c;
  }
  printf("\t%d\t%d\t%d\n", lc, wc, cc);
}
