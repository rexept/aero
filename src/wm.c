#include "wm.h"
#include <X11/Xlib.h>
#include <signal.h>
#include <stdio.h>

wm_t *g_wm = NULL;

void wm_init(wm_t *wm) {
  if (g_wm)
    fprintf(stderr, "warning: g_wm already initiliazed");
  g_wm = wm;
}
void quit(const Arg *arg) {
  FILE *fd = NULL;
  struct stat filestat;

  if ((fd = fopen(lockfile, "r")) && stat(lockfile, &filestat) == 0) {
    fclose(fd);

    if (filestat.st_ctime <= time(NULL) - 2)
      remove(lockfile);
  }

  if ((fd = fopen(lockfile, "r")) != NULL) {
    fclose(fd);
    remove(lockfile);
    g_wm->running = 0;
  } else {
    if ((fd = fopen(lockfile, "a")) != NULL)
      fclose(fd);
  }
}
