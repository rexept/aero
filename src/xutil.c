#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xproto.h>
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
  uint dui;
  Window dummy;

  return XQueryPointer(g_wm->dpy, g_wm->root, &dummy, &dummy, x, y, &di, &di,
                       &dui);
}

int gettextprop(Window w, Atom atom, char *text, uint size) {
  char **list = NULL;
  int n;
  XTextProperty name;

  if (!text || size == 0)
    return 0;
  text[0] = '\0';
  if (!XGetTextProperty(g_wm->dpy, w, &name, atom) || !name.nitems)
    return 0;
  if (name.encoding == XA_STRING) {
    strncpy(text, (char *)name.value, size - 1);
  } else if (XmbTextPropertyToTextList(g_wm->dpy, &name, &list, &n) >= Success &&
             n > 0 && *list) {
    strncpy(text, *list, size - 1);
    XFreeStringList(list);
  }
  text[size - 1] = '\0';
  XFree(name.value);
  return 1;
}
