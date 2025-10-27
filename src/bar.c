#include "bar.h"
#include "config.h"
#include "drw.h"
#include "monitor.h"
#include "util.h"
#include "wm.h"
#include <X11/Xlib.h>

void init_bar(void) {
  if (!drw_fontset_create(g_wm->drw, fonts, LENGTH(fonts)))
    die("no fonts could be loaded.");
  monitor_t *mon = g_wm->selmon;
  mon->bar.lrpad = g_wm->drw->fonts->h;
  mon->bar.bh = g_wm->drw->fonts->h + user_bh;
}

void updatebars(void) {
  monitor_t *m;
  XSetWindowAttributes wa = {.override_redirect = True,
                             .background_pixmap = ParentRelative,
                             .event_mask = ButtonPressMask | ExposureMask};

  XClassHint ch = {"aero", "aero"};

  for (m = g_wm->mons; m; m = m->next) {
    if (m->barwin)
      continue;
    m->barwin =
        XCreateWindow(g_wm->dpy, g_wm->root, m->wx, m->by, m->ww, m->bh, 0,
                      DefaultDepth(g_wm->dpy, g_wm->screen), CopyFromParent,
                      DefaultVisual(g_wm->dpy, g_wm->screen),
                      CWOverrideRedirect | CWBackPixmap | CWEventMask, &wa);

    XDefineCursor(g_wm->dpy, m->barwin, g_wm->cursor[CurNormal]->cursor);
    XMapRaised(g_wm->dpy, m->barwin);
    XSetClassHint(g_wm->dpy, m->barwin, &ch);
  }
}
