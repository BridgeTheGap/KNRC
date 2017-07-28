#include <stdio.h>

/* count digits, white space, others */

int main() {
    
  int c, nwhite, nother;
  int ndigits[10];

  for (int i = 0; i < 10; i++) {
    ndigits[i] = 0;
  }

  while ((c = getchar()) != EOF) {
    if (c >= '0' && c <= '9') {
      ++ndigits[c-'0'];
    } else if (c == ' ' || c == '\t' || c == '\n') {
      ++nwhite;
    } else {
      ++nother;
    }
  }

  for (int i = 0; i < 10; i++) {
    printf("%5d |", i);
    
    for (int j = 0; j < ndigits[i]; j++) {
      printf("=");
    }

    printf("\n");
  }

  printf("white |");
  for (int i = 0; i < nwhite; i++) {
    printf("=");
  }
  printf("\n");

  printf("other |");
  for (int i = 0; i < nother; i++) {
    printf("=");
  }
  printf("\n"); 
}