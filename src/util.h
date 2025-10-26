#ifndef UTIL_H
#define UTIL_H

#include <X11/Xlib.h>

void die(const char *fmt, ...);
void checkotherwm(void);
int xerrorstart(Display *dpy, XErrorEvent *ee);

#endif // UTIL_H
