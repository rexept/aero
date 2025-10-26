#include "monitor.h"
#include "config.h"
#include "string.h"
#include "util.h"
#include "wm.h"
#include <X11/Xlib.h>

monitor_t *createmon(void) {
  monitor_t *m;

  m = ecalloc(1, sizeof(monitor_t));

  // first tag is selected by default
  m->tagset[0] = m->tagset[1] = 1;

  m->mfact = mfact;
  m->nmaster = nmaster;
  m->showbar = showbar;
  m->topbar = topbar;

  m->lt[0] = &layouts[0];
  m->lt[1] = &layouts[1 % LENGTH(layouts)];

  strncpy(m->ltsymbol, layouts[0].symbol, sizeof m->ltsymbol);

  return m;
}
void cleanupmon(monitor_t *mon) {
  monitor_t *m;

  if (mon == g_wm->mons) {
    g_wm->mons = g_wm->mons->next;
  } else {
    for (m = g_wm->mons; m && m->next != mon; m = m->next)
      ;
    m->next = mon->next;
  }

  XUnmapWindow(g_wm->dpy, mon->barwin);
  XDestroyWindow(g_wm->dpy, mon->barwin);
  free(mon);
}
