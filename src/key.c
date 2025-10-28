#include "key.h"
#include "config.h"
#include "util.h"
#include "wm.h"
#include <X11/X.h>
#include <X11/Xlib.h>

static unsigned int numlockmask = 0;

static void updatenumlockmask(void) {
  numlockmask = 0;
  XModifierKeymap *modmap = XGetModifierMapping(g_wm->dpy);

  for (uint i = 0; i < 8; i++)
    for (uint j = 0; j < modmap->max_keypermod; j++)
      if (modmap->modifiermap[i * modmap->max_keypermod + j] ==
          XKeysymToKeycode(g_wm->dpy, XK_Num_Lock))
        numlockmask = (1 << i);
  XFreeModifiermap(modmap);
}

void grabkeys(void) {
  updatenumlockmask();

  int start, end, skip;
  unsigned int modifiers[] = {0, LockMask, numlockmask, numlockmask | LockMask};
  XUngrabKey(g_wm->dpy, AnyKey, AnyModifier, g_wm->root);
  XDisplayKeycodes(g_wm->dpy, &start, &end);

  KeySym *syms = XGetKeyboardMapping(g_wm->dpy, start, end - start + 1, &skip);
  if (!syms)
    return;

  for (uint k = start; k <= end; k++)
    for (uint i = 0; i < LENGTH(keys); i++)
      /* skip modifier codes, we do that ourselves */
      if (keys[i].keysym == syms[(k - start) * skip])
        for (uint j = 0; j < LENGTH(modifiers); j++)
          XGrabKey(g_wm->dpy, k, keys[i].mod | modifiers[j], g_wm->root, True,
                   GrabModeAsync, GrabModeAsync);

  XFree(syms);
}
