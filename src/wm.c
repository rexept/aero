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
