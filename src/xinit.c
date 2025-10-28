#include "xinit.h"
#include "types.h"
#include "wm.h"
#include <X11/Xlib.h>

void init_root_events(void) {
    XSetWindowAttributes wa;
    wa.cursor = g_wm->cursor[CurNormal]->cursor;
    wa.event_mask = SubstructureRedirectMask|SubstructureNotifyMask
        |ButtonPressMask|PointerMotionMask|EnterWindowMask
        |LeaveWindowMask|StructureNotifyMask|PropertyChangeMask;

    XChangeWindowAttributes(g_wm->dpy, g_wm->root, CWEventMask|CWCursor, &wa);
    XSelectInput(g_wm->dpy, g_wm->root, wa.event_mask);
}
