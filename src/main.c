#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>

#include "util.h"
int main(int argc, char *argv[]) {
  if (argc == 2 && !strcmp("-v", argv[1]))
    die("aero"VERSION);
  else if (argc != 1)
    die("usage: aero [-v]");

  if (!setlocale(LC_CTYPE, "") || !XSupportsLocale())
      fputs("warning: no locale support\n", stderr);

  return EXIT_SUCCESS;
}
