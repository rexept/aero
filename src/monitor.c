#include "monitor.h"
#include "client.h"
#include "config.h"
#include "string.h"
#include "util.h"
#include "wm.h"
#include "xutil.h"
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

monitor_t *wintomon(Window w) {
  int x, y;
  client_t *c;
  monitor_t *m;

  if (w == g_wm->root && getrootptr(&x, &y))
    return recttomon(x, y, 1, 1);

  for (m = g_wm->mons; m; m = m->next)
    if (w == m->barwin)
      return m;

  if ((c = wintoclient(w)))
    return c->mon;

  return g_wm->selmon;
}

/* Takes x and y coordinates as well as height and width and works out which
 * monitor this rectangle is on (or overlaps it the most if the rectangle spans
 * more than one window). */
monitor_t *recttomon(int x, int y, int w, int h) {
  monitor_t *m, *r = g_wm->selmon;
  int a, area = 0;

  for (m = g_wm->mons; m; m = m->next) {
    if ((a = INTERSECT(x, y, w, h, m)) > area) {
      area = a;
      r = m;
    }
  }
  return r;
}
