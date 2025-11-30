#include "key.h"
#include "client.h"
#include "config.h"
#include "types.h"
#include "util.h"
#include "wm.h"
#include <X11/X.h>
#include <X11/Xlib.h>

static uint numlockmask = 0;

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
  uint modifiers[] = {0, LockMask, numlockmask, numlockmask | LockMask};
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

void grabmbuttons(client_t *c, int focused) {
  updatenumlockmask();

  uint modifiers[] = {0, LockMask, numlockmask, numlockmask | LockMask};
  XUngrabKey(g_wm->dpy, AnyButton, AnyModifier, c->win);
  if (!focused)
    XGrabButton(g_wm->dpy, AnyButton, AnyModifier, c->win, False, BUTTONMASK,
                GrabModeSync, GrabModeSync, None, None);
  for (uint i = 0; i < LENGTH(buttons); i++)
    if (buttons[i].click == ClkClientWin)
      for (uint j = 0; j < LENGTH(modifiers); j++)
        XGrabButton(g_wm->dpy, buttons[i].button,
                    buttons[i].mask | modifiers[j], c->win, False, BUTTONMASK,
                    GrabModeAsync, GrabModeSync, None, None);
}
