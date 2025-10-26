#include <X11/Xlib.h>
#include <stdio.h>

#include "wm.h"
#include "xutil.h"

int xerror(Display *dpy, XErrorEvent *ee) {
  // clang-format off
	if (ee->error_code == BadWindow
	|| (ee->request_code == X_SetInputFocus && ee->error_code == BadMatch)
	|| (ee->request_code == X_PolyText8 && ee->error_code == BadDrawable)
	|| (ee->request_code == X_PolyFillRectangle && ee->error_code == BadDrawable)
	|| (ee->request_code == X_PolySegment && ee->error_code == BadDrawable)
	|| (ee->request_code == X_ConfigureWindow && ee->error_code == BadMatch)
	|| (ee->request_code == X_GrabButton && ee->error_code == BadAccess)
	|| (ee->request_code == X_GrabKey && ee->error_code == BadAccess)
	|| (ee->request_code == X_CopyArea && ee->error_code == BadDrawable))
    // clang-format on
    return 0;
  fprintf(stderr, "aero: fatal error: request code=%d, error code=%d\n",
          ee->request_code, ee->error_code);
  return g_wm->xerrorxlib(dpy, ee);
}

int getrootptr(int *x, int *y) {
  int di;
  unsigned dui;
  Window dummy;

  return XQueryPointer(g_wm->dpy, g_wm->root, &dummy, &dummy, x, y, &di, &di,
                       &dui);
}
