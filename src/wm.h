#ifndef WM_H
#define WM_H

#include <X11/Xlib.h>

typedef struct {
  int screen;
  Display *dpy;
  int (*xerrorxlib)(Display *, XErrorEvent *);
} wm_t;
extern wm_t *g_wm;

void wm_init(wm_t *wm);

#endif // WM_H
