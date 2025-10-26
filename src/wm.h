#ifndef WM_H
#define WM_H

#include "client.h"
#include "drw.h"
#include "types.h"
#include <X11/Xlib.h>

typedef struct {
  int screen;
  int sw, sh;
  Window root;
  Display *dpy;
  int (*xerrorxlib)(Display *, XErrorEvent *);

  monitor_t *mons;
  monitor_t *selmon;
  Drw *drw;

  int running;
} wm_t;
extern wm_t *g_wm;

void wm_init(wm_t *wm);
void quit(const Arg *arg);
static void wm_init_screen(void);

#endif // WM_H
