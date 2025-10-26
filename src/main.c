#include <X11/Xlib.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "wm.h"

int main(int argc, char *argv[]) {
  wm_t wm = {0};
  wm_init(&wm);

  if (argc == 2 && !strcmp("-v", argv[1]))
    die("aero-" VERSION);
  else if (argc != 1)
    die("usage: aero [-v]");

  if (!setlocale(LC_CTYPE, "") || !XSupportsLocale())
    fputs("warning: no locale support\n", stderr);

  if (!(wm.dpy = XOpenDisplay(NULL)))
    die("aero: cannot open display");

  checkotherwm();

  // Bring everything online
  wm_setup();

  XCloseDisplay(wm.dpy);
  return EXIT_SUCCESS;
}
