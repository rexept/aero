#ifndef WM_H
#define WM_H

#include <X11/Xlib.h>

typedef struct {
  int screen;
  Display *dpy;
  int (*xerrorxlib)(Display *, XErrorEvent *);
} wm_t;

void wm_init(wm_t *wm);

extern wm_t *g_wm;

#endif // WM_H
