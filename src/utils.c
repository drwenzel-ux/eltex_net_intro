#include "utils.h"

void perror_die(const char *m, int ret) {
  perror(m);
  exit(0);
}