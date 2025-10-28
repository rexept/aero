#include "bar.h"
#include "client.h"
#include "config.h"
#include "drw.h"
#include "monitor.h"
#include "util.h"
#include "wm.h"
#include "xutil.h"
#include <X11/Xatom.h>
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

void updatestatus(void) {
  char *stext = g_wm->selmon->bar.stext;
  if (!gettextprop(g_wm->root, XA_WM_NAME, stext, sizeof(stext)))
    strcpy(stext, "aero-" VERSION);
  drawbar(g_wm->selmon);
}

void drawbar(monitor_t *m) {
  int indn;
  int x, w, tw = 0;
  int boxs = g_wm->drw->fonts->h / 9;
  int boxw = g_wm->drw->fonts->h / 6 + 2;
  unsigned int i, occ = 0, urg = 0;
  client_t *c;

  Drw *drw = g_wm->drw;
  monitor_t *mon = g_wm->selmon;

  if (!m->showbar)
    return;

  /* draw status first so it can be overdrawn by tags later */
  if (m == mon) { /* status is only drawn on selected monitor */
    drw_setscheme(drw, g_wm->scheme[SchemeNorm]);
    tw = TEXTW(m->bar.stext) - m->bar.lrpad + 2; /* 2px right padding */
    drw_text(drw, m->ww - tw, 0, tw, m->bar.bh, 0, m->bar.stext, 0);
  }

  for (c = m->clients; c; c = c->next) {
    occ |= c->tags == 255 ? 0 : c->tags;
    if (c->isurgent)
      urg |= c->tags;
  }
  x = 0;
  for (i = 0; i < LENGTH(tags); i++) {
    /* do not draw vacant tags */
    if (!(occ & 1 << i || m->tagset[m->seltags] & 1 << i))
      continue;

    indn = 0;
    w = TEXTW(tags[i]);
    drw_setscheme(
        drw,
        g_wm->scheme[m->tagset[m->seltags] & 1 << i ? SchemeSel : SchemeNorm]);
    drw_text(drw, x, 0, w, m->bar.bh, m->bar.lrpad / 2, tags[i], urg & 1 << i);
    for (c = m->clients; c; c = c->next) {
      if (c->tags & (1 << i)) {
        drw_rect(drw, x, 1 + (indn * 2), m->sel == c ? 6 : 1, 1, 1,
                 urg & 1 << i);
        indn++;
      }
    }

    x += w;
  }
  w = TEXTW(m->ltsymbol);
  drw_setscheme(drw, g_wm->scheme[SchemeNorm]);
  x = drw_text(drw, x, 0, w, m->bar.bh, m->bar.lrpad / 2, m->ltsymbol, 0);

  /* Draw swalsymbol next to ltsymbol. */
  if (m->sel && m->sel->swer) {
    w = TEXTW(swalsymbol);
    x = drw_text(drw, x, 0, w, m->bar.bh, m->bar.lrpad / 2, swalsymbol, 0);
  }

  if ((w = m->ww - tw - x) > m->bar.bh) {
    if (m->sel) {
      drw_setscheme(drw, g_wm->scheme[m == mon ? SchemeSel : SchemeNorm]);
      drw_text(drw, x, 0, w, m->bar.bh, m->bar.lrpad / 2, m->sel->name, 0);
      if (m->sel->isfloating)
        drw_rect(drw, x + boxs, boxs, boxw, boxw, m->sel->isfixed, 0);
    } else {
      drw_setscheme(drw, g_wm->scheme[SchemeNorm]);
      drw_rect(drw, x, 0, w, m->bar.bh, 1, 1);
    }
  }
  drw_map(drw, m->barwin, 0, 0, m->ww, m->bar.bh);
}
