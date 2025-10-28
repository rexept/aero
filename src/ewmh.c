#include "ewmh.h"
#include "wm.h"
#include <X11/X.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>

void init_ewmh_support_window(void) {
  Display *dpy = g_wm->dpy;
  Window *wmcheckwin = &(g_wm->wmcheckwin);
  Atom *netatom = g_wm->netatom;

  *wmcheckwin = XCreateSimpleWindow(dpy, g_wm->root, 0, 0, 1, 1, 0, 0, 0);
  XChangeProperty(dpy, *wmcheckwin, netatom[NetWMCheck], XA_WINDOW, 32,
                  PropModeReplace, (unsigned char *)&wmcheckwin, 1);
  XChangeProperty(dpy, *wmcheckwin, netatom[NetWMName], g_wm->utf8string, 8,
                  PropModeReplace, (unsigned char *)"aero", 3);
  XChangeProperty(dpy, g_wm->root, netatom[NetWMCheck], XA_WINDOW, 32,
                  PropModeReplace, (unsigned char *)&wmcheckwin, 1);
}

void init_ewmh_root_properties(void) {
  Display *dpy = g_wm->dpy;
  Window *root = &(g_wm->root);
  Atom *netatom = g_wm->netatom;

  XChangeProperty(dpy, *root, netatom[NetSupported], XA_ATOM, 32,
                  PropModeReplace, (unsigned char *)netatom, NetLast);
  XDeleteProperty(dpy, *root, g_wm->netatom[NetClientList]);
}
