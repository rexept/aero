#include "client.h"
#include "monitor.h"
#include "util.h"
#include "wm.h"
#include <string.h>

#ifdef XINERAMA
#include <X11/extensions/Xinerama.h>
#endif /* XINERAMA */

static void updatebarpos(monitor_t *m) {
  m->wy = m->my;
  m->wh = m->mh;
  if (m->showbar) {
    m->wh -= m->bh;
    m->by = m->topbar ? m->wy : m->wy + m->wh;
    m->wy = m->topbar ? m->wy + m->bh : m->wy;
  } else
    m->by = -m->bh;
}

#ifdef XINERAMA
static int isuniquegeom(XineramaScreenInfo *unique, size_t n,
                        XineramaScreenInfo *info) {
  while (n--)
    if (unique[n].x_org == info->x_org && unique[n].y_org == info->y_org &&
        unique[n].width == info->width && unique[n].height == info->height)
      return 0;
  return 1;
}
#endif /* XINERAMA */

/* setup monitors if compiled with XINERAMA
 * if not then the available screen space is set up as a single workspace that
 * spans all monitors. */
int updategeom(void) {
  int dirty = 0;

#ifdef XINERAMA
  if (XineramaIsActive(g_wm->dpy)) {
    int i, j, n, nn;
    client_t *c;
    monitor_t *m;
    XineramaScreenInfo *info = XineramaQueryScreens(g_wm->dpy, &nn);
    XineramaScreenInfo *unique = NULL;

    for (n = 0, m = g_wm->mons; m; m = m->next, n++)
      ;
    /* only consider unique geometries as separate screens */
    unique = ecalloc(nn, sizeof(XineramaScreenInfo));
    for (i = 0, j = 0; i < nn; i++)
      if (isuniquegeom(unique, j, &info[i]))
        memcpy(&unique[j++], &info[i], sizeof(XineramaScreenInfo));
    XFree(info);
    nn = j;

    /* new monitors if nn > n */
    for (i = n; i < nn; i++) {
      for (m = g_wm->mons; m && m->next; m = m->next)
        ;
      if (m)
        m->next = createmon();
      else
        g_wm->mons = createmon();
    }
    for (i = 0, m = g_wm->mons; i < nn && m; m = m->next, i++)
      if (i >= n || unique[i].x_org != m->mx || unique[i].y_org != m->my ||
          unique[i].width != m->mw || unique[i].height != m->mh) {
        dirty = 1;
        m->num = i;
        m->mx = m->wx = unique[i].x_org;
        m->my = m->wy = unique[i].y_org;
        m->mw = m->ww = unique[i].width;
        m->mh = m->wh = unique[i].height;
        updatebarpos(m);
      }
    /* removed monitors if n > nn */
    for (i = nn; i < n; i++) {
      for (m = g_wm->mons; m && m->next; m = m->next)
        ;
      while ((c = m->clients)) {
        dirty = 1;
        m->clients = c->next;
        detachstack(c);
        c->mon = g_wm->mons;
        attach(c);
        attachstack(c);
      }
      if (m == g_wm->selmon)
        g_wm->selmon = g_wm->mons;
      cleanupmon(m);
    }
    free(unique);
  } else
#endif /* XINERAMA */
  {    /* default monitor setup */
    if (!g_wm->mons)
      g_wm->mons = createmon();
    if (g_wm->mons->mw != g_wm->sw || g_wm->mons->mh != g_wm->sh) {
      dirty = 1;
      g_wm->mons->mw = g_wm->mons->ww = g_wm->sw;
      g_wm->mons->mh = g_wm->mons->wh = g_wm->sh;
      updatebarpos(g_wm->mons);
    }
  }
  if (dirty) {
    g_wm->selmon = g_wm->mons;
    g_wm->selmon = wintomon(g_wm->root);
  }
  return dirty;
}
