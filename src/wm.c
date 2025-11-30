#include <X11/Xlib.h>
#include <stdio.h>
#include <time.h>

#include "atoms.h"
#include "bar.h"
#include "config.h"
#include "cursor.h"
#include "draw.h"
#include "ewmh.h"
#include "key.h"
#include "manage.h"
#include "signals.h"
#include "wm.h"
#include "xinit.h"

wm_t *g_wm = NULL;

void wm_init(wm_t *wm) {
  if (g_wm)
    fprintf(stderr, "warning: g_wm already initiliazed");
  g_wm = wm;
}

static void wm_init_screen(void) {
  g_wm->screen = DefaultScreen(g_wm->dpy);
  g_wm->sw = DisplayWidth(g_wm->dpy, g_wm->screen);
  g_wm->sh = DisplayHeight(g_wm->dpy, g_wm->screen);
  g_wm->root = RootWindow(g_wm->dpy, g_wm->screen);
  g_wm->drw =
      drw_create(g_wm->dpy, g_wm->screen, g_wm->root, g_wm->sw, g_wm->sh);
}

void wm_setup(void) {
  init_child_signals();
  wm_init_screen();
  init_bars();
  init_monitors();
  if (!g_wm->selmon)
    g_wm->selmon = g_wm->mons;
  init_atoms();
  init_cursors();
  init_colors();
  updatebars();
  updatestatus();
  init_ewmh_support_window();
  init_ewmh_root_properties();
  init_root_events();
  grabkeys();
  focus(NULL);
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
