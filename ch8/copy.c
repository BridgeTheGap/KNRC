#include "syscalls.h"

int main() {
  char bug[BUFSIZ];
  int n;

  while ((n = read(0, buf, BUFSIZ)) > 0) {
    write(1, buf, n);
  }
  return 0;
}
