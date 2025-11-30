#ifndef WM_H
#define WM_H

#include "drw.h"
#include "types.h"
#include <X11/Xlib.h>

struct wm_t {
  int screen;
  int sw, sh;
  Window root;
  Window wmcheckwin;
  Display *dpy;
  int running;
  int (*xerrorxlib)(Display *, XErrorEvent *);

  monitor_t *mons;
  monitor_t *selmon;
  monitor_t *prevmon;
  Drw *drw;
  Clr **scheme;

  Atom wmatom[WMLast];
  Atom netatom[NetLast];
  Atom utf8string;

  Cur *cursor[CurLast];
};
extern wm_t *g_wm;

void wm_init(wm_t *wm);
void wm_setup(void);
void quit(const Arg *arg);

#endif // WM_H
