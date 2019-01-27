// Zicheng He 1534763 zicheh@uw.edu
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

double term(int);

int main(int argc, char* argv[]) {
  if (argc > 2) {  // false input: more than one entry
    printf("too many entries\n");
    return 1;
  }
  const char* in = argv[1];

  for (int i = 0; i < strlen(in); i++) {  // false input: input is not integer
    if (((int) in[i] < 47) | ((int) in[i] > 58)) {
      printf("invalid input\n");
      return 1;
    }
  }

  int order = atoi(in);
  printf("Our estimate of Pi is %.20f\n", term(order));
  return 0;
}

double term(int order) {  // the recursive method
  if (order > 0) {
    double result = (2 * (order % 2) - 1) * 4 / (8 * order  * (order + 0.5) * (order + 1));
    return term(order - 1) + result;
  } else {
    return 3;
  }
}
