#include "bar.h"
#include "config.h"
#include "monitor.h"
#include "util.h"
#include "wm.h"
#include "drw.h"

void init_bar(void) {
  if (!drw_fontset_create(g_wm->drw, fonts, LENGTH(fonts)))
    die("no fonts could be loaded.");
  monitor_t *mon = g_wm->selmon;
  mon->bar.lrpad = g_wm->drw->fonts->h;
  mon->bar.bh = g_wm->drw->fonts->h + user_bh;
}
