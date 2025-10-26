#include "cursor.h"
#include "drw.h"
#include "wm.h"
#include <X11/cursorfont.h>

void init_cursors(void) {
  Drw *drw = g_wm->drw;

  g_wm->cursor[CurNormal] = drw_cur_create(drw, XC_left_ptr);
  g_wm->cursor[CurResize] = drw_cur_create(drw, XC_sizing);
  g_wm->cursor[CurMove] = drw_cur_create(drw, XC_fleur);
  g_wm->cursor[CurSwal] = drw_cur_create(drw, XC_bottom_side);
}
