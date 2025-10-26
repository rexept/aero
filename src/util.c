#include <X11/X.h>
#include <X11/Xlib.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "wm.h"
#include "xutil.h"

void die(const char *fmt, ...) {
  va_list ap;
  int saved_errno;

  saved_errno = errno;

  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);

  if (fmt[0] && fmt[strlen(fmt) - 1] == ':')
    fprintf(stderr, " %s", strerror(saved_errno));
  fputc('\n', stderr);

  exit(1);
}

int xerrorstart(Display *dpy, XErrorEvent *ee) {
  die("dwm: another window manager is already running");
  return -1;
}

/*
 * Make sure no other wm is running and
 * if so then aero exits gracefully
 */
void checkotherwm(void) {
  g_wm->xerrorxlib = XSetErrorHandler(xerrorstart);
  XSelectInput(g_wm->dpy, DefaultRootWindow(g_wm->dpy),
               SubstructureRedirectMask);
  XSync(g_wm->dpy, False);
  XSetErrorHandler(xerror);
  XSync(g_wm->dpy, False);
}
