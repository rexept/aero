#include "manage.h"
#include "bar.h"
#include "client.h"
#include "event.h"
#include "ewmh.h"
#include "key.h"
#include "monitor.h"
#include "types.h"
#include "util.h"
#include "wm.h"
#include <X11/X.h>
#include <X11/Xatom.h>

void focus(client_t *c) {
  monitor_t *selmon = g_wm->selmon;
  Display *dpy = g_wm->dpy;
  Window root = g_wm->root;

  if (!c || !ISVISIBLE(c))
    for (c = selmon->stack; c && !ISVISIBLE(c); c = c->snext)
      ;
  if (selmon->sel && selmon->sel != c)
    unfocus(selmon->sel, 0);

  if (!c) {
    XSetInputFocus(dpy, root, RevertToPointerRoot, CurrentTime);
    XDeleteProperty(dpy, root, g_wm->netatom[NetActiveWindow]);
    selmon->sel = c;
    drawbars();
    return;
  }

  if (c->cantfocus)
    return;

  if (c->mon != selmon) {
    g_wm->prevmon = selmon;
    selmon = c->mon;
  }

  if (c->isurgent)
    seturgent(c, 0);

  detachstack(c);
  attachstack(c);
  grabmbuttons(c, 1);
  XSetWindowBorder(dpy, c->win, g_wm->scheme[SchemeSel][ColBorder].pixel);
  setfocus(c);

  selmon->sel = c;
  drawbars();
}

void unfocus(client_t *c, int setfocus) {
  Display *dpy = g_wm->dpy;
  Window root = g_wm->root;

  if (!c)
    return;
  grabmbuttons(c, 0);
  XSetWindowBorder(dpy, c->win, g_wm->scheme[SchemeNorm][ColBorder].pixel);
  if (setfocus) {
    XSetInputFocus(dpy, root, RevertToPointerRoot, CurrentTime);
    XDeleteProperty(dpy, root, g_wm->netatom[NetActiveWindow]);
  }
}

void setfocus(client_t *c) {
  if (!c->neverfocus) {
    XSetInputFocus(g_wm->dpy, c->win, RevertToPointerRoot, CurrentTime);
    XChangeProperty(g_wm->dpy, g_wm->root, g_wm->netatom[NetActiveWindow],
                    XA_WINDOW, 32, PropModeReplace, (unsigned char *)&(c->win),
                    1);
  }
  sendevent(c, g_wm->wmatom[WMTakeFocus]);
}
