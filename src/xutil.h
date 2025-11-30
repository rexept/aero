#ifndef XUTIL_H
#define XUTIL_H

#include <X11/Xlib.h>

int xerror(Display *dpy, XErrorEvent *ee);
int getrootptr(int *x, int *y);
int gettextprop(Window w, Atom atom, char *text, uint size);

#endif // XUTIL_H
