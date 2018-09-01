#include "../libk.h"

void die(const char *s) {
  perror(s);
  printf("\n\r");
  exit(1);
}


