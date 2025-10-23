#include <stdlib.h>
#include <string.h>

#include "util.h"
int main(int argc, char *argv[]) {
  if (argc == 2 && !strcmp("-v", argv[1]))
    die("aero"VERSION);
  else if (argc != 1)
    die("usage: aero [-v]");

  return EXIT_SUCCESS;
}
